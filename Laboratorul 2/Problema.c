#include <stdio.h>
#include <stdlib.h>
int main(){
	int n, *mat;
	printf("n=");
	scanf("%d",&n);
	mat = (int*)malloc(n*n*sizeof(int));
	for(int i = 0; i < n; ++i)
		for(int j = 0; j<n;++j)
			scanf("%d", (mat+n*i+j));
	printf("Elementele matricii:\n");
	for(int i = 0; i < n; ++i){
		for(int j = 0; j<n;++j)
			printf("%d ", *(mat+n*i+j));
		printf("\n");
		}
	if(n%2){
		printf("Elementul de la intersectia diagonalelor este: %d\n", *(mat + n/2*n+n/2));
	}
	printf("Elementele matricii de pe diagonala principala:\n");
	for(int i = 0; i<n;++i)
		printf("%d ",*(mat+n*i+i));
	printf("\n");
	printf("Elementele matricii de pe diagonala secundara:\n");
	for(int i = 0; i<n;++i)
		printf("%d ",*(mat+n*i+n-i-1));
	return 0;
}
