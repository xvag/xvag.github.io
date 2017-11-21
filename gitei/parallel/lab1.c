#include <stdio.h>
#include "mpi.h"

int main(int argc, char** argv)
{
	int my_rank, rank;
	int p,k,num;
	int sum,finsum;
	float sum2,finsum2;
	int tag1=10,tag2=20,tag3=30,tag4=40,tag5=50,tag6=60,tag7=70,tag8=80,tag9=90;
	int n;
	float m;
	float var;

	int max,min;
	int max_x[10];
	int min_x[10];

	int x[100];
	int x_loc[100];
	float d[100];

	MPI_Status status;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&p);

	if(my_rank==0)
	{
		printf("Dose plithos aritmon:\n");
		scanf("%d",&n);
		printf("Dose tous %d arithmous:\n",n);
		for(k=0;k<n;k++)
			scanf("%d",&x[k]);

		num=n/p;
		for(rank=1;rank<p;rank++)
			MPI_Send(&num,1,MPI_INT,rank,tag1,MPI_COMM_WORLD);
		
		k=num;
		for(rank=1;rank<p;rank++)
		{
			MPI_Send(&x[k],num,MPI_INT,rank,tag2,MPI_COMM_WORLD);
			k+=num;
		}

		for(k=0;k<num;k++)
			x_loc[k]=x[k];
	}
	else
	{
		MPI_Recv(&num,1,MPI_INT,0,tag1,MPI_COMM_WORLD,&status);
		MPI_Recv(&x_loc[0],num,MPI_INT,0,tag2,MPI_COMM_WORLD,&status);
	}

	sum=0;
	min_x[my_rank]=x_loc[0];
	max_x[my_rank]=x_loc[0];
	for(k=0;k<num;k++)
	{
		sum+=x_loc[k];

		if(x_loc[k]<min_x[my_rank])
			min_x[my_rank]=x_loc[k];

		if(x_loc[k]>max_x[my_rank])
			max_x[my_rank]=x_loc[k];
	}
	
	if(my_rank!=0)
	{
		MPI_Send(&sum,1,MPI_INT,0,tag3,MPI_COMM_WORLD);
		MPI_Send(&min_x[my_rank],1,MPI_INT,0,tag6,MPI_COMM_WORLD);
		MPI_Send(&max_x[my_rank],1,MPI_INT,0,tag7,MPI_COMM_WORLD);
	}
	else
	{
		finsum=sum;
		min=min_x[0];
		max=max_x[0];
		printf("Calculating average: Result of process %d: %d\n",my_rank,sum);
		for(rank=1;rank<p;rank++)
		{
			MPI_Recv(&min_x[rank],1,MPI_INT,rank,tag6,MPI_COMM_WORLD,&status);
			MPI_Recv(&max_x[rank],1,MPI_INT,rank,tag7,MPI_COMM_WORLD,&status);
			MPI_Recv(&sum,1,MPI_INT,rank,tag3,MPI_COMM_WORLD,&status);
			finsum=finsum+sum;
			printf("Calculating average: Result of process %d: %d\n",rank,sum);
			if(min_x[rank]<min)
				min=min_x[rank];
			if(max_x[rank]>max)
				max=max_x[rank];
		}
		m = (float) finsum/ (float) n;
		printf("Average= %f\n",m);

		int i;
		for(i=0;i<p;i++)
			printf("min:%d max:%d\n",min_x[i],max_x[i]);

		printf("MIN=%d\n",min);
		printf("MAX=%d\n",max);

		for(rank=1;rank<p;rank++)
		{
			MPI_Send(&m,1,MPI_FLOAT,rank,tag4,MPI_COMM_WORLD);
			MPI_Send(&min,1,MPI_INT,rank,tag8,MPI_COMM_WORLD);
			MPI_Send(&max,1,MPI_INT,rank,tag9,MPI_COMM_WORLD);			
		}
	}

	if(my_rank!=0)
	{
		MPI_Recv(&m,1,MPI_FLOAT,0,tag4,MPI_COMM_WORLD,&status);
		MPI_Recv(&min,1,MPI_INT,0,tag8,MPI_COMM_WORLD,&status);
		MPI_Recv(&max,1,MPI_INT,0,tag9,MPI_COMM_WORLD,&status);
	}		


	sum2=0.0;
	for(k=0;k<num;k++)
	{
		sum2+=(((float)x_loc[k]-m)*((float)x_loc[k]-m));
		d[k]=((float)x_loc[k]/((float)max-(float)min))*(float)100;
		printf("%f ",d[k]);
	}

	if(my_rank!=0)
		MPI_Send(&sum2,1,MPI_FLOAT,0,tag5,MPI_COMM_WORLD);
	else
	{
		finsum2=sum2;
		printf("Calculating diaspora: Result of process %d: %f\n",my_rank,sum2);
		for(rank=1;rank<p;rank++)
		{
			MPI_Recv(&sum2,1,MPI_FLOAT,rank,tag5,MPI_COMM_WORLD,&status);
			finsum2=finsum2+sum2;
			printf("Calculating Diaspora: Result of process %d: %f\n",rank,sum2);
		}
		var=finsum2/(float)n;
		printf("Diaspora= %f\n",var);
	}

	int r;
	for(r=0;r<n;r++)
		printf("\n%f \n",d[r]);
	
	MPI_Finalize();
	return 0;
}
