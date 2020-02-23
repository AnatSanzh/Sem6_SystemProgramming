#include <stdio.h>
#include <sys/select.h>
#include <time.h>
#include <fcntl.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>


/*
1. Отримує аргументами командної строки два імені файлів
2. Перший файл відкриває для читання, другий до перезапису, або створює, якщо його
не існує (для створення використати атрибути 0644)
3. Послідовно читає дані з першого файлу буферами фіксованого об’єму (наприклад
512 байт) та записує у другий.
4. Перед записом із вмістом буферу проводить таке перетворення – усі рядкові літери
латинського алфавіту перетворює на відповідні прописні. Для цього розрахувати
відповідний зсув за таблицею ASCII (див. man ascii).
5. В процесі перезапису проводить підрахунок перезаписаних байт, та наприкінці
виводить у вихідний потік сумарний обсяг переписаних даних.
*/
void throwError(){
	if(errno){
		perror("Error: ");
		exit(errno);
	}
}

int main(int argc, char **argv){
	if(argc != 3) return -1;

	errno = 0;

	char* file1Name = argv[1];
	char* file2Name = argv[2];

	int file1Desc = open(file1Name, O_RDONLY);
	int file2Desc = open(file2Name, O_WRONLY | O_APPEND | O_CREAT, 0644);

	throwError();

	char buffer[512];
	long buffLen = 0;
	long totalLen = 0;

	while(buffLen = read(file1Desc, buffer, sizeof(buffer)/sizeof(char))){
		throwError();
		for(int i=0;i<buffLen;i++){
			if(buffer[i]) buffer[i]=toupper(buffer[i]);
		}
		
		write(file2Desc, buffer, buffLen);
		throwError();
		
		totalLen += buffLen;
	}

	close(file1Desc);
	close(file2Desc);

	printf("%li\n",totalLen);

	return 0;
}
