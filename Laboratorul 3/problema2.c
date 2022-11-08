#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char **argv){
	int n,intrare,iesire;
	char buf[50];
	intrare=open(argv[1],O_RDONLY);
	n=read(intrare,buf,20);
	iesire=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU);
	while(n>0){
		write(iesire,buf,n);
		n=read(intrare,buf,20);
	}
	return 0;
}
