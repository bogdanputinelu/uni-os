#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
void* reverse( void *v ){
	char *word = (char*) v;
	char *rev=(char*)malloc(strlen(word)*sizeof(char));
	int n = strlen(word);
    	for(int i = n-1;i>=0;--i){
        	rev[n-1-i]=word[i];
    	}
	return rev;
}
int main(int argc, char **argv){
	char *word = argv[1];
	char *result;
	pthread_t thr;
	if ( pthread_create (&thr , NULL , reverse , word)) {
		perror ( NULL );
		return errno ;
	}
	if ( pthread_join ( thr , (void**)&result )) {
		perror ( NULL );
		return errno ;
	}
	printf("%s",result);
	return 0;
}
