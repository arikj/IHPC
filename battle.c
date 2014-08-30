#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mpi.h"
#include<stdbool.h>

bool a1[1000][1000][2];
bool a2[1000][1000][2];
bool a3[1000][1000][2];
bool a4[1000][1000][2];
bool a5[1000][1000][2];
int n,m,t;
int i,j,k,x,y;

int min(int a,int b)
{
if(a<b)
	return a;
else 	
	return b;
}

int max(int a,int b)
{
if(a>b)
        return a;
else
        return b;
}

bool reverse(bool x)
{
if(x==0)
	return 1;
else
	return 0;
}

void ground1()
{
int evil = 0;
bool read =0;
bool write = 1;

for(k=0;k<t;k++)
{

	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			evil = 0;
			//printf("%d ",a1[i][j][read]);
			for(x=max(i-1,0);x<=min(i+1,m);x++)
				{
				for(y=max(j-1,0);y<=min(j+1,n);y++)	
					evil+=a1[x][y][read];
				}
			//printf("%d ",evil);
			if(a1[i][j][read] == 1)
				{
				evil-=1;
				if(evil < 2 || evil>3)
					a1[i][j][write]=0;
				else 
					a1[i][j][write]=1;
				}	
			else
				{
				if(evil==3)
					a1[i][j][write]=1;
				else
					a1[i][j][write]=0;
				}	
		}
	//printf("\n");		
	}		
	read = reverse(read);
	write = reverse(write);

//printf("\n\n");
}
}
void ground2()
{
int evil = 0;
bool read =0;
bool write = 1;

for(k=0;k<t;k++)
{
        for(i=0;i<n;i++)
        {
                for(j=0;j<m;j++)
                {
                        evil = 0;
                        for(x=max(i-1,0);x<=min(i+1,m);x++)
                                {
                                for(y=max(j-1,0);y<=min(j+1,n);y++)
                                        evil+=a2[x][y][read];
                                }
                        if(a2[i][j][read] == 1)         
                                {
                                        a2[i][j][write]=1;
                        
                                }
                        else
                                {
                                if(evil==3)
                                        a2[i][j][write]=1;

				 else
                                        a2[i][j][write]=0;

                                }
                }
        }
        read = reverse(read);
        write = reverse(write);
}
}

void ground3()
{
int evil = 0;
bool read =0;
bool write = 1;

for(k=0;k<t;k++)
{
        for(i=0;i<n;i++)
        {
                for(j=0;j<m;j++)
                {
                        evil = 0;
                        for(x=max(i-1,0);x<=min(i+1,m);x++)
                                {
                                for(y=max(j-1,0);y<=min(j+1,n);y++)
                                        evil+=a3[x][y][read];
                                }
                        if(a3[i][j][read] == 1)         
                                {
                                evil-=1;
                                if(evil == 2)
                                        a3[i][j][write]=1;
                                else 
                                        a3[i][j][write]=0;
                                }
                        else
                                {
                                if(evil==2)
                                        a3[i][j][write]=1;

				 else
                                        a3[i][j][write]=0;

                                }
                }
        }
        read = reverse(read);
        write = reverse(write);
}
}

void ground4()
{
int evil = 0;
bool read =0;
bool write = 1;

for(k=0;k<t;k++)
{
        for(i=0;i<n;i++)
        {
                for(j=0;j<m;j++)
                {
                        evil = 0;
                        for(x=max(i-1,0);x<=min(i+1,m);x++)
                                {
                                for(y=max(j-1,0);y<=min(j+1,n);y++)
                                        evil+=a4[x][y][read];
                                }
                        if(a4[i][j][read] == 1)         
                                {
                                evil-=1;
                                if(evil == 2 || evil == 3)
                                        a4[i][j][write]=1;
                                else 
                                        a4[i][j][write]=0;
                                }
                        else
                                {
                                if(evil==3 || evil==6)
                                        a4[i][j][write]=1;

				 else
                                        a4[i][j][write]=0;

                                }
                }
        }
        read = reverse(read);
        write = reverse(write);
}
}

void ground5()
{
int evil = 0;
bool read =0;
bool write = 1;

for(k=0;k<t;k++)
{
        for(i=0;i<n;i++)
        {
                for(j=0;j<m;j++)
                {
                        evil = 0;
                        for(x=max(i-1,0);x<=min(i+1,m);x++)
                                {
                                for(y=max(j-1,0);y<=min(j+1,n);y++)
                                        evil+=a5[x][y][read];
                                }
                        if(a5[i][j][read] == 1)         
                                {
                                evil-=1;
                                if( evil ==3 ||  evil ==4 || evil ==6 || evil ==7 || evil ==8)
                                        a5[i][j][write]=1;
                                else 
                                        a5[i][j][write]=0;
                                }
                        else
                                {
                                if(evil==3 || evil ==6 || evil ==7 || evil ==8)
                                        a5[i][j][write]=1;
                        
				 else
                                        a5[i][j][write]=0;

			        }
                }
        }
        read = reverse(read);
        write = reverse(write);
}


}

int main()
{
int rank,nprocs;

MPI_Init(NULL,NULL);
MPI_Comm_rank (MPI_COMM_WORLD, &rank);
MPI_Comm_size (MPI_COMM_WORLD, &nprocs);

if(rank==0)
	scanf("%d %d %d",&n,&m,&t);


MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
MPI_Bcast(&t,1,MPI_INT,0,MPI_COMM_WORLD);

if(rank == 0)
	{
	
		for(i=0;i<n;i++)
			for(j=0;j<m;j++)
				{
				scanf("%d",&k);
				a1[i][j][0] = (bool)k;
				}

	 	for(i=0;i<n;i++)
                        for(j=0;j<m;j++)
                                {
                                scanf("%d",&k);
                                a2[i][j][0] = (bool)k;
                                }
 		for(i=0;i<n;i++)
                        for(j=0;j<m;j++)
                                {
                                scanf("%d",&k);
                                a3[i][j][0] = (bool)k;
                                }

		 for(i=0;i<n;i++)
                        for(j=0;j<m;j++)
                                {
                                scanf("%d",&k);
                                a4[i][j][0] = (bool)k;
                                }

		 for(i=0;i<n;i++)
                        for(j=0;j<m;j++)
                                {
                                scanf("%d",&k);
                                a5[i][j][0] = (bool)k;
                                }

		}
		MPI_Bcast(a1,(1000*1000*2)/4,MPI_BYTE,0,MPI_COMM_WORLD);
		MPI_Bcast(a2,(1000*1000*2)/4,MPI_BYTE,0,MPI_COMM_WORLD);
		MPI_Bcast(a3,(1000*1000*2)/4,MPI_BYTE,0,MPI_COMM_WORLD);
		MPI_Bcast(a4,(1000*1000*2)/4,MPI_BYTE,0,MPI_COMM_WORLD);
		MPI_Bcast(a5,(1000*1000*2)/4,MPI_BYTE,0,MPI_COMM_WORLD);
		/*MPI_Bcast(list,3,MPI_INT,0,MPI_COMM_WORLD);
		MPI_Bcast(list,3,MPI_INT,0,MPI_COMM_WORLD);
		MPI_Bcast(list,3,MPI_INT,0,MPI_COMM_WORLD);
		MPI_Bcast(list,3,MPI_INT,0,MPI_COMM_WORLD);
		*/if(nprocs < 5 && rank == 0)
		{
		ground1();
		ground2();
		ground3();
		ground4();
		ground5();
		}

		
		else if(nprocs > 5)
			{
			if(rank == 0)
				{
				ground1();
				MPI_Recv(a2, (1000*1000*2)/4, MPI_BYTE, 1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				 MPI_Recv(a3, (1000*1000*2)/4, MPI_BYTE, 2,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				 MPI_Recv(a4, (1000*1000*2)/4, MPI_BYTE, 3,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				 MPI_Recv(a5, (1000*1000*2)/4, MPI_BYTE, 4,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

				}
			if(rank == 1)
				{
                                ground2();
				MPI_Send(a2, (1000*1000*2)/4, MPI_BYTE, 0,0,MPI_COMM_WORLD);	
				}
				
			if(rank == 2)
				{
                                ground3();
				MPI_Send(a3, (1000*1000*2)/4, MPI_BYTE, 0,0,MPI_COMM_WORLD);
				}
			if(rank == 3)
				{
                                ground4();
				MPI_Send(a4, (1000*1000*2)/4, MPI_BYTE, 0,0,MPI_COMM_WORLD);
				}	
			if(rank == 4)
				{
                                ground5();
				MPI_Send(a5, (1000*1000*2)/4, MPI_BYTE, 0,0,MPI_COMM_WORLD);
				}

			}
		//printf("\n\n");


if(rank == 0)
	{

		
		for(i=0;i<n;i++)
			{
                        for(j=0;j<m;j++)
				printf("%d ",a1[i][j][t%2]);
			printf("\n");
			}
		
		for(i=0;i<n;i++)
                        {
                        for(j=0;j<m;j++)
                                printf("%d ",a2[i][j][t%2]);
			printf("\n");
                        }


		for(i=0;i<n;i++)
                        {
                        for(j=0;j<m;j++)
                                printf("%d ",a3[i][j][t%2]);
			printf("\n");
                        }


		for(i=0;i<n;i++)
                        {
                        for(j=0;j<m;j++)
                                printf("%d ",a4[i][j][t%2]);
			printf("\n");
                        }

		for(i=0;i<n;i++)
                        {
                        for(j=0;j<m;j++)
                                printf("%d ",a5[i][j][t%2]);
			printf("\n");
                        }
		
		}

MPI_Finalize();
return 0;
}
