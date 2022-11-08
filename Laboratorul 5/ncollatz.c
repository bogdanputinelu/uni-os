#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(int argc, char **argv){
	for(int i=1;i<argc;++i){
		int n=atoi(argv[i]);
		pid_t pid = fork();
		if ( pid < 0)
			return errno;
		else 
		if ( pid == 0){
			while(n!=1){
				printf("%d ",n);
				if(n%2==0)
					n/=2;
				else
					n=3*n+1;
			}
			printf("1\n");
			exit(0);
		}
	}
	for(int i=1;i<argc;++i){
		int c=wait(NULL);
		printf("My ID=%d Child PID=%d finished\n",getpid(),c);
	}
	return 0;
}
