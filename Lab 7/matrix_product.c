#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
int n = 5, m = 3, p = 4;
int A[5][3]={{1,1,1},{1,0,0},{0,0,2},{1,3,2},{3,0,3}};
int B[3][4]={{1,2,2,1},{1,0,0,2},{3,3,2,1}};
int C[5][4];

void* product( void *v ){
	int *poz=(int*)v;
	for(int i=0;i<m;++i){
		C[poz[0]][poz[1]] += A[poz[0]][i] * B[i][poz[1]];
	}
	return NULL;
}
int main(int argc, char **argv){
	char *result;
	pthread_t thr[5][4];
	for(int i = 0; i<n;i++){
		for(int j = 0; j<p;++j){
			int* poz=(int*)malloc(2*sizeof(int));
			poz[0]=i;
			poz[1]=j;
			if ( pthread_create (&thr[i][j] , NULL , product , poz)) {
				perror ( NULL );
				return errno ;
			}
		}
	}
	for(int i = 0; i<n;i++){
		for(int j = 0; j<p;++j){
			if ( pthread_join ( thr[i][j] , (void**)&result )) {
				perror ( NULL );
				return errno ;
			}
		}
	}
	for(int i=0;i<n;++i){
		for(int j=0;j<p;++j){
			printf("%d ",C[i][j]);
		}
		printf("\n");
	}
	return 0;
}
