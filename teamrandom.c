#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "mpi.h"

int main()
{
int rank,nprocs;
int x;
double y;
MPI_Init(NULL,NULL);
MPI_Comm_rank (MPI_COMM_WORLD, &rank);
MPI_Comm_size (MPI_COMM_WORLD, &nprocs);

int i,j,n,m;
if(rank == 0)
	{
	scanf("%d",&n);
	for(i=0;i<n;i++) {
		for(j=0;j<90;j++) {
			scanf("%lf",&y);
		}
		scanf("%d",&x);
		}
	scanf("%d",&m);
	for(i=0;i<m;i++)
		{
		for(j=0;j<90;j++)
			scanf("%lf",&y);
		}

	for(i=0;i<m;i++)
		printf("%d\n",(rand()%90)+1);
	}

MPI_Finalize();
return 0;
}
