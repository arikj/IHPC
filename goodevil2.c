#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
 
int min(int a,int b)
{
if(a<b)
	return a;
else 
	return b;
}

int main () 
{
  	int rank, nprocs;
	int n,i,j,m,k;
	char ch[1000];
	int arr[22][26][2];
	int p,e;
	time_t t;
	int x;
	srand((unsigned) time(&t));
	MPI_Init (NULL, NULL);	
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);	
	MPI_Comm_size (MPI_COMM_WORLD, &nprocs);
	 for(i=0;i<22;i++)
			
                        for(j=0;j<26;j++)
				for(k=0;k<2;k++)
					arr[i][j][k]=0;		
			
                        

	if(rank==0)
		{
		scanf("%d",&n);
		scanf("%c",&ch[0]);
		for(i=0;i<n;i++)
			{
			gets(ch);
			for(j=0;j<22;j++)
				{
				if(ch[44]=='p')
					arr[j][ch[2*j]-'a'][0]+=1;
				else
					arr[j][ch[2*j]-'a'][1]+=1;
				}
			}

/*		for(i=0;i<22;i++)
			{
			for(j=0;j<26;j++)
					printf("%d ",arr[i][j][0]);
			printf("\n");
			}
			printf("\n\n");
		                for(i=0;i<22;i++)
                        {
                        for(j=0;j<26;j++)
                                        printf("%d ",arr[i][j][1]);
                        printf("\n");
                        }
*/
		scanf("%d",&m);
		scanf("%c",&ch[0]);
		for(i=0;i<m;i++)
			{
			p=0;	
			e=0;
			gets(ch);
			for(j=0;j<22;j++)
				{
				if(arr[j][ch[2*j]-'a'][0] > arr[j][ch[2*j]-'a'][1])
					p+= min((arr[j][ch[2*j]-'a'][0])/(arr[j][ch[2*j]-'a'][0] - arr[j][ch[2*j]-'a'][1]) , arr[j][ch[2*j]-'a'][0]);
				 if(arr[j][ch[2*j]-'a'][0] < arr[j][ch[2*j]-'a'][1])
                                        e+= min((arr[j][ch[2*j]-'a'][1])/(arr[j][ch[2*j]-'a'][1] - arr[j][ch[2*j]-'a'][0]) , arr[j][ch[2*j]-'a'][1]);

				/*if(arr[j][ch[2*j]-'a'][0] > arr[j][ch[2*j]-'a'][1])
					p+=1;
				else if(arr[j][ch[2*j]-'a'][0] < arr[j][ch[2*j]-'a'][1])
					e+=1;
				*/
				}
			if(p>=e)
				printf("p\n");
			else
				printf("e\n");
			}
		}
	MPI_Finalize();
	return 0;			
}
