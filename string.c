#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mpi.h"

short int a[5000][5000];

int check(char a[], char b[],int n)
{
int count=0;
while(b = strstr(b,a))
	{
	count++;
	b++;
	}
return count;
}

int main()
{
int rank,nprocs;
MPI_Init(NULL,NULL);
MPI_Comm_rank (MPI_COMM_WORLD, &rank);
MPI_Comm_size (MPI_COMM_WORLD, &nprocs);
int t,per;

if(rank==0)
	scanf("%d",&t);

MPI_Bcast(&t,1,MPI_INT,0,MPI_COMM_WORLD);

char arr[60001];
int query;
char str[500][101];
int i,j,len;

for(j=0;j<t;j++){
if(rank == 0)
	{
	scanf("%s",arr);
	scanf("%d",&query);
	per = query/nprocs + 1;
	len = strlen(arr);
	for(i=0;i<query;i++)
		scanf("%s",str[i]);
		
	}
MPI_Bcast(&per,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Bcast(&len,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Bcast(arr,len,MPI_CHAR,0,MPI_COMM_WORLD);
char newstr[500][101];

MPI_Scatter(str, per*101, MPI_CHAR,
            newstr, per*101, MPI_CHAR,
           0, MPI_COMM_WORLD);
int tot[500];
int *count = (int *)malloc(sizeof(int)*per);
for(i=0;i<per;i++)
	{
	count[i]=0;
	if(newstr[i][0]!='\0')
		count[i] = check(newstr[i],arr,len);
	}
MPI_Gather(count, per, MPI_INT,
           tot, per, MPI_INT,
           0, MPI_COMM_WORLD);
if(rank == 0)
	{
	printf("%d\n",nprocs);
	for(i=0;i<query;i++)
		printf("%d ",tot[i]);
	printf("\n");
	}
}	
MPI_Finalize();
return 0;
}
