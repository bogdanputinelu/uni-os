#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/mman.h>
#include <sys/stat.h>    
#include <fcntl.h> 
int main(int argc, char **argv){

	
			char shm_name[]="myshm";
			int shm_fd;
			shm_fd = shm_open ( shm_name , O_CREAT | O_RDWR , S_IRUSR | S_IWUSR );
			if ( shm_fd < 0) {
				perror (NULL);
				return errno ;
			}
			size_t pagesize=getpagesize();
			size_t shm_size = (argc-1) * pagesize;
			if ( ftruncate ( shm_fd , shm_size ) == -1) {
				perror ( NULL );
				shm_unlink ( shm_name );
				return errno ;
			}
			char *shm_ptr;
			for(int i=1;i<argc;++i){
				
				
				int n=atoi(argv[i]);
				pid_t pid = fork();
				
				if ( pid < 0)
					return errno;
				else 
				if ( pid == 0){
					shm_ptr=mmap(NULL,pagesize,PROT_WRITE,MAP_SHARED,shm_fd,(i-1)*pagesize);
				
					if ( shm_ptr == MAP_FAILED ) {
						perror ( NULL );
						shm_unlink ( shm_name );
						return errno ;
					}
					shm_ptr += sprintf(shm_ptr,"%d: ",n);
					while(n!=1){
						shm_ptr += sprintf(shm_ptr,"%d ",n);
						if(n%2==0)
							n/=2;
						else
							n=3*n+1;
					}
					shm_ptr+= sprintf(shm_ptr,"1\n");
					printf("Done Parent %d Me %d\n",getppid(),getpid());
					
					munmap(shm_ptr,shm_size);
					exit(0);
				}
			}
			for(int i=1;i<argc;++i){
				wait(NULL);
			}
			for(int i=1; i<argc;++i){
				shm_ptr=mmap(NULL,pagesize,PROT_READ,MAP_SHARED,shm_fd,(i-1)*pagesize);
				if ( shm_ptr == MAP_FAILED ) {
					perror ( NULL );
					shm_unlink ( shm_name );
					return errno ;
				}
				printf("%s",shm_ptr);
				munmap(shm_ptr,pagesize);
			}
			shm_unlink(shm_name);
			printf("Done Parent %d Me %d\n",getppid(),getpid());
	
	return 0;
}
