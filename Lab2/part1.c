#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/*1. Отримує та друкує інформацію про параметри свого процесу за допомогою системних
викликів getpid(), getgid(), getsid() тощо.
2. Виконує розгалудження процесу за допомогою системного виклику fork().
3. Для процесу-батька та процесу-нащадка окремо роздруковує їхні ідентифікатори у
циклі.
4. Виконати очікування процесом-батьком завершення нащадка.
5. Повідомляє про завершення процесів — батька та нащадка.
6. Пояснити отримані результати*/
int main(){
	gid_t currGid = getgid();
	pid_t currPid = getpid();
	pid_t currParentPid = getppid();
	uid_t currUid = getuid();

	printf("Process ID: %i\n", currPid);
	printf("Process Parent ID: %i\n", currParentPid);
	printf("User ID: %i\n", currUid);
	printf("Group ID: %i\n", currGid);

	printf("Cloning...\n");

	if(fork() > 0){ // parent
		printf("Parent Process ID: %i\n", currPid);

		wait(NULL);
	}else{ //child
		printf("Child Process ID: %i\n", getpid());

		exit(0);
	}

	printf("Parent and child finished\n");

	return 0;
}
