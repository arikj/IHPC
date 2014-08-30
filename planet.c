#include<stdio.h>
#include<stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
int rank,nprocs,n;
int *arr,i,per,t,j;
MPI_Init(&argc,&argv);
MPI_Comm_rank (MPI_COMM_WORLD, &rank);
MPI_Comm_size (MPI_COMM_WORLD, &nprocs);
if(rank==0)
	scanf("%d",&t);
MPI_Bcast(&t,1,MPI_INT,0,MPI_COMM_WORLD);
for(j=0;j<t;j++){
if(rank == 0)
	{
	scanf("%d",&n);
	per = n/nprocs + 1;
	arr = (int *)malloc(sizeof(int)*(2*n+32));
	for(i=0;i<n;i++)
		scanf("%d",&arr[i*2]);
	for(i=0;i<n;i++)
		scanf("%d",&arr[2*i+1]);
	}
MPI_Bcast(&per,1,MPI_INT,0,MPI_COMM_WORLD);

int *client_arr = (int *)malloc(sizeof(int)*2*per);
int *res = (int *)malloc(sizeof(int)*per);
MPI_Scatter(arr, 2*per, MPI_INT, client_arr,
            2*per, MPI_INT, 0, MPI_COMM_WORLD);

for(i=0;i<per;i++)
	res[i] = client_arr[2*i+1] - client_arr[2*i];

MPI_Gather(res, per, MPI_INT, arr, per, MPI_INT, 0,
           MPI_COMM_WORLD);

if(rank == 0)
	{
	for(i=0;i<n;i++)
		printf("%d ",arr[i]);
	printf("\n");
	}
}
/*if(rank == 0)
	{
	int i;
	for(i=1;i<nprocs;i++)
		MPI_Send(&arr[i], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
	
	}*/
/*if(rank!=0)
	{
	int x;
	MPI_Recv(&x,1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	printf("%d: %d\n",rank,x);
	}
*/
 MPI_Finalize();
  return 0;
}
