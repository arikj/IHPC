#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
 
int main () 
{
  	int rank, nprocs;
	int n,i,j,m;
	char ch[1000];
	time_t t;
	int x;
	srand((unsigned) time(&t));
	MPI_Init (NULL, NULL);	
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);	
	MPI_Comm_size (MPI_COMM_WORLD, &nprocs);
	if(rank==0)
		{
		scanf("%d",&n);
		scanf("%c",&ch[0]);
		for(i=0;i<n;i++)
			{
			gets(ch);
			}
		scanf("%d",&m);
		scanf("%c",&ch[0]);

		for(i=0;i<m;i++)
			{
			 gets(ch);

			}
		for(i=0;i<m;i++)
			{
			x = rand()%2;
			if(x==0)
				printf("p\n");
			else	
				printf("e\n");		
			}	
		}
	MPI_Finalize();
	return 0;			
}
