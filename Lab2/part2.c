#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

/*1. Відкриває на запис текстовий файл логу та робить у нього запис про старт програми.
2. Виконує демонізацію свого функціоналу за таким алгоритмом:
 Виконує fork()
 Для процесу-батька робить запис у лог про породження нащадка та закриває
себе викликом exit().
 Для поцесу-нащадка:
 робить setsid()
 змінює поточний каталог на “/”
 закриває усі відкриті батьком дескриптори
 відкриває “/dev/null” на запис для трьох стандартних потоків
3. Відкриває лог та робить у нього запис про параметри демонізованого процесу.
4. Виконує витримку часу у нескінченному циклі.
5. Пояснити отримані результати*/

#define LOG_WRITE(BUFF) {\
		int logFileDesc = open("log.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);\
		write(logFileDesc, BUFF, sizeof(BUFF)/sizeof(char));\
		close(logFileDesc);\
	}


int main(){
	LOG_WRITE("Program started\n");


	if(fork() == 0){
		pid_t ssid = setsid();


	}else{
		LOG_WRITE("Child is created\n");
		exit(0);
	}

	LOG_WRITE("\n");
	

	return 0;
}
