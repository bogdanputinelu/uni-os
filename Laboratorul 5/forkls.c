#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
int main(){
	pid_t pid = fork ();
	if ( pid < 0)
		return errno;
	else 
	if ( pid == 0){
		char *argv[] = {"ls",NULL };
		execve("/usr/bin/ls",argv,NULL );
		perror(NULL);
	}
	else{	
		printf("Child PID=%d\n",pid);
		wait(NULL);
		printf("My ID=%d\n",getpid());
	}
	return 0;
}
