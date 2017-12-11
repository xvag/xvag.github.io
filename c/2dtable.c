#include <stdio.h>

int main() {

	int arr[100][100];
	int n,i,j;

	printf("Give N: ");
	scanf("%d",&n);

	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			arr[i][j]=i+j+10;

	for(i=0; i<n; i++) {
		printf("\n");
		for(j=0; j<n; j++)
			printf("[%d,%d]:%d ",i,j,arr[i][j]);
	}

	return 0;
}
