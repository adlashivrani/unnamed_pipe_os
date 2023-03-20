#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX 128

int main()
{
	int fd[2];
	if (pipe(fd) == -1) { //creating pipe
		exit(1);
	}
	int pid;
	pid = fork();
	if (pid == -1) {
		exit(1);
	} 
	if (pid == 0) {
		close(fd[0]);
		FILE *fp;
		char buff[MAX];
		if ((fp = fopen("input.txt","w")) == NULL) {
			exit(1);
		}
		printf("\nEnter data\n");
		fgets(buff, MAX, stdin);
		fprintf(fp,"%s",buff);
		if (write(fd[1],buff,MAX) == -1) {
			exit(1);
		}
		close(fd[1]);
		fclose(fp);
	} else {
		wait(NULL);
		close(fd[1]);
		FILE *fpp;
		char pbuff[MAX];
		fpp = fopen("output.txt", "w+");
		if (read(fd[0],pbuff,MAX) == -1) {
			exit(1);
		}
		printf("%s\n", pbuff);
		fprintf(fpp,"%s",pbuff);
		close(fd[0]);
		fclose(fpp);
	}
	return 0;
}
