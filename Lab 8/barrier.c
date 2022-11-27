#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
sem_t sem;
pthread_mutex_t mtx;
int n_threads=5, S;
int barrier_point(){
	int s_barrier;
	pthread_mutex_lock(&mtx);
	S++;
	s_barrier = S;
	pthread_mutex_unlock(&mtx );
	if(s_barrier<n_threads){
		if ( sem_wait (& sem )) {
			perror ( NULL );
			return errno ;
		}
	}
	else
		for(int i=0;i<n_threads;++i)
			sem_post(&sem);
}
void *tfun ( void *v )
{
	int *tid = ( int *) v ;
	printf ("%d reached the barrier\n" , *tid );
	barrier_point();
	printf ("%d passed the barrier\n" , *tid );
	free ( tid );
	return NULL ;
}
int main(){
	if ( pthread_mutex_init(&mtx , NULL )) {
		perror( NULL );
		return errno ;
	}
	if ( sem_init (&sem , 0 , S )) {
		perror ( NULL );
		return errno ;
	}
	pthread_t thr[5];
	for(int i = 0; i<n_threads;++i){
		int *c=(int *)malloc(sizeof(int));
		*c=i;
		if ( pthread_create (&thr[i] , NULL , tfun , c)) {
				perror ( NULL );
				return errno ;
			}
	}
	for(int i = 0; i<n_threads;++i){
		
		if ( pthread_join (thr[i] , NULL)) {
				perror ( NULL );
				return errno ;
			}
	}
	pthread_mutex_destroy(&mtx);
	sem_destroy (&sem );
	return 0;
}
