#include <stdio.h>
#include <sys/select.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>


/*
1. Отримує аргументом командної строки довільний строковий ідентифікатор.
2. Налаштовує системний виклик select для очікування читання у вхідному потоці (
файловий дескріптор STDIN_FILENO ) з таймаутом 5 секунд.
3. При отриманні можливості читання, прочитати з потоку буфер довжиною не більше
1024 байта та вивести його у вихідний потік з поміткою у вигляді ідентифікатора п.1.
4. При спливанні таймауту, вивести у потік помилок повідомлення про це з поміткою у
вигляді ідентифікатора п.1 та знову налаштувати системний виклик select (п.2).
5. Протестувати роботу програми отримуючи через вхідний потік результати вводу з
клавіатури.
*/
void throwError(){
	if(errno){
		perror("Error: ");
		exit(errno);
	}
}
int inputTimeout(int fd, unsigned int sec){
	fd_set set;
	struct timeval timeout;

	FD_ZERO(&set);
	FD_SET(fd, &set);

	timeout.tv_sec = sec;
	timeout.tv_usec = 0;

	return select(fd + 1, &set, NULL, NULL, &timeout);
}
int main(int argc, char **argv){
	if(argc != 2) return -1;

	errno = 0;

	char* strIdent = argv[1];
	int strIdentLen = strlen(strIdent);

	char buffer[1024];

	while(1){
		int waitRes = inputTimeout(STDIN_FILENO, 5);

		throwError();

		if(waitRes > 0){
			int buffLen = read(STDIN_FILENO, buffer, sizeof(buffer)/sizeof(char));
			write(STDOUT_FILENO, strIdent, strIdentLen);
			write(STDOUT_FILENO, buffer, buffLen);	
			break;		
		}else{
			write(STDERR_FILENO, strIdent, strIdentLen);
		}

		throwError();
	}

	return 0;
}
