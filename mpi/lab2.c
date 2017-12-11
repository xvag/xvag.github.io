#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv) {

	int my_rank, rank;
	int p, n;
	int nperp;
	int q;
	int i, j;
	int k, l, x, y;

	int C[10000];
	int D[10000];
	int C_loc[10000];
	int D_loc[10000];
	int CD[10000];
	int CD_loc[10000];

	char proc_name[MPI_MAX_PROCESSOR_NAME];
	int namelen;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);
	MPI_Get_processor_name(proc_name, &namelen);

	if(my_rank==0) {
		printf("Give N: \n");
		scanf("%d",&n);

		for (i=0; i<n*n; i++) {
			C[i] = i+1;
			D[i] = i+1;
		}

		for (i=0; i<n*n; i++){
			if (i%n==0)
				printf("\n");
			printf("%d ", C[i]);
		}

		printf("\n");
		for (i=0; i<n*n; i++){
			if (i%n==0)
				printf("\n");
			printf("%d ", D[i]);
		}

	}

	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	//MPI_Bcast(&nperp, 1, MPI_INT, 0, MPI_COMM_WORLD);

	nperp = n/p;
	q = nperp*n;

	MPI_Scatter(C, q, MPI_INT, C_loc, q, MPI_INT, 0, MPI_COMM_WORLD);

	/*for (i=0; i<q; i++)
		CD_loc[i] = 10; //C_loc[k][l] + D_loc[k][l];*/
	
	printf("Proc %d on %s:\n",my_rank, proc_name);

	for (i=0; i<q; i++){
		if (i%n==0)
			printf("\n");
		printf("%d ",C_loc[i]);
	}

	/*MPI_Gather(CD_loc, q, MPI_INT, CD, q, MPI_INT, 0, MPI_COMM_WORLD);

	if (my_rank==0) {
		printf("\nFinal result: C+D =\n");
		for (i=0; i<n; i++) {
			printf("\n");
			for (j=0; j<n; j++)
				printf("%d ", CD[i][j]);
		}
		printf("\n");
	}*/

	MPI_Finalize();
	
	return 0;
}
