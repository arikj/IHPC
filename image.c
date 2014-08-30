#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mpi.h"
#include<math.h>
#include <complex.h> 


int n,m;
double xmax,xmin,ymax,ymin;
int iter;
double r;


double dist(double complex x)
{
double res = sqrt(creal(x)*creal(x) + cimag(x)*cimag(x));
return res;
}

int main()
{
int rank,nprocs;
int i;
int block = 0;
int pos;

MPI_Init(NULL,NULL);
MPI_Comm_rank (MPI_COMM_WORLD, &rank);
MPI_Comm_size (MPI_COMM_WORLD, &nprocs);
nprocs = 1;
if(rank == 0)
	scanf("%d %d %lf %lf %lf %lf %d %lf",&m,&n,&xmin,&xmax,&ymin,&ymax,&iter,&r);		
	
MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Bcast(&iter,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Bcast(&xmax,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
MPI_Bcast(&xmin,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
MPI_Bcast(&ymax,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
MPI_Bcast(&ymin,1,MPI_DOUBLE,0,MPI_COMM_WORLD);
MPI_Bcast(&r,1,MPI_DOUBLE,0,MPI_COMM_WORLD);

/*int **array;
array = (int**)malloc(nprocs*sizeof(int*));
for (i = 0; i < nprocs; i++)
  array[i] = (int*)malloc(m*sizeof(int));
*/

int array[200][5001];
int store[5001];
double complex z0[5001];

//int *store =  (int *)malloc(5001*sizeof(int));
//double complex *z0 = (double complex*)malloc(sizeof(double complex)*m);

double complex local;

if(rank == 0)
	{
	printf("P2\n%d\n%d\n255\n",m,n);
	}	
while(n>block*nprocs)
{
pos = block*nprocs + rank;
if(pos < n)
	{
	for(i=0;i<m;i++)
		{
		z0[i] = (xmin + i*((xmax-xmin)/(m-1))) + (ymax - pos*((ymax-ymin)/(n-1)))*I;
	 	//printf("(%lf,%lf) ",creal(z0[i]),cimag(z0[i]));
		}
	//printf("\n");
	}

for(i=0;i<m;i++)
	{
	int init = 0;
	local = z0[i];
	while(init < iter && cabs(local)<r)
		{
		local = local*local + z0[i];
		init++;
		}
	if(init == iter)
		store[i]=0;
	else
		store[i]=255;
	}
MPI_Gather(store, 5001, MPI_INT,array, 5001, MPI_INT,0, MPI_COMM_WORLD);
int min,j;
if(rank == 0)
	{
	if((block+1)*nprocs < n)
		min = (block+1)*nprocs;
	else
		min = n;
	
	
		for(i=block*nprocs;i<min;i++)
		{
		for(j=0;j<m-1;j++)
			printf("%d ",array[i-block*nprocs][j]);
		printf("%d\n",array[i-block*nprocs][j]);
		}
	
	}

block++;
}

MPI_Finalize();
return 0;
}
