#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES;
pthread_mutex_t mtx;
int decrease_count ( int count ){
	while(1){
		pthread_mutex_lock(&mtx);
		if ( available_resources < count ){
			pthread_mutex_unlock(&mtx );
		}
		else{
			available_resources -= count ;
			printf("Got %d resources %d remaining\n",count,available_resources);
			pthread_mutex_unlock(&mtx );
			return 0;
			}
	}
}
int increase_count ( int count ){
	pthread_mutex_lock(&mtx);
	available_resources += count ;
	printf("Released %d resources %d remaining\n",count,available_resources);
	pthread_mutex_unlock(&mtx );
	return 0;
}
void* count(void *v){
	int* count = (int*) v;
	decrease_count(*count);
	increase_count(*count);
}
int main(){
	if ( pthread_mutex_init(&mtx , NULL )) {
		perror( NULL );
		return errno ;
	}
	printf("MAX_RESOURCES=%d\n",available_resources);
	pthread_t thr[5];
	for(int i = 0; i<5;++i){
		int *c=(int *)malloc(sizeof(int));
		*c=rand()%(available_resources+1);
		if ( pthread_create (&thr[i] , NULL , count , c)) {
				perror ( NULL );
				return errno ;
			}
	}
	for(int i = 0; i<5;++i){
		
		if ( pthread_join (thr[i] , NULL)) {
				perror ( NULL );
				return errno ;
			}
	}
	pthread_mutex_destroy(&mtx);
	return 0;
}
