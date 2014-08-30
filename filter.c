#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mpi.h"

short int a[5002*5002];
int list[3];
int store[5000];
//int newstore[5002];

int ind(int i, int j)
{
return (i*(list[0]+2) + j);
}

int average(int i, int j)
{
int sum = a[ind(i,j)]+a[ind(i-1,j)]+a[ind(i-1,j-1)]+a[ind(i-1,j+1)]+a[ind(i+1,j)]+a[ind(i+1,j-1)]+a[ind(i+1,j+1)]+a[ind(i,j-1)]+a[ind(i,j+1)];
int count;
if(i==1 || i==list[1])
	{
	if(j==1 || j==list[0])
		count = 4;
	else 
		count = 6;
	}
else
	{
	if(j==1 || j==list[0])
                count = 6;
        else
                count = 9;
	}
sum = sum/count;
return sum%10;
}

int main()
{
int rank,nprocs;
int i,j,k,per,x;
int sum,tmp;
int *newstore;

MPI_Init(NULL,NULL);
MPI_Comm_rank (MPI_COMM_WORLD, &rank);
MPI_Comm_size (MPI_COMM_WORLD, &nprocs);

if(rank == 0)
	scanf("%d %d %d",&list[0],&list[1],&list[2]);

MPI_Bcast(list,3,MPI_INT,0,MPI_COMM_WORLD);

for(i=0;i<list[2];i++)
{
if(rank == 0)
	{

	for(j=1;j<=list[1];j++)
		{
		for(k=1;k<=list[0];k++)
			scanf("%hd",&a[ind(j,k)]);
		}

	for(j=0;j<list[1]+2;j++)
		{
		a[ind(j,0)]=0;
		a[ind(j,list[0]+1)]=0;
		}

	  for(j=0;j<list[0]+2;j++)
                {
                a[ind(0,j)]=0;
                a[ind(list[1]+1,j)]=0;
                }

	
	}
MPI_Bcast(a,(list[0]+2)*(list[1]+2),MPI_SHORT,0,MPI_COMM_WORLD);

per = list[1]/nprocs + 1;
newstore = (int *)malloc(sizeof(int)*per);
x = 0;
for(j = rank*per+1;j<=(rank+1)*per;j++)
	{
	newstore[x]=0;
	if(j>list[1])
		break;
	for(k=1;k<=list[0];k++)
		newstore[x]=newstore[x]+average(j,k);
	x++;		
	}

MPI_Gather(newstore, per , MPI_INT,store, per, MPI_INT, 0, MPI_COMM_WORLD);
if(rank == 0)
	{
	for(j=0;j<list[1];j++)
		printf("%d\n",store[j]);
	}

}

MPI_Finalize();
return 0;
}
