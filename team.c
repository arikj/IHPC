#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "mpi.h"

double training_data[10000][90];
double test_data[1000][90];

double distance(double A[][90],double B[][90],int i,int j) {
	double sum=0;
	int x;
	for(x=0;x<90;x++) {
		sum += pow(A[i][x]-B[j][x],2);
	}
	return pow(sum,.5);
}


int find_class(double A[][90],double B[][90],int class[],int training_size,int test_no) {
	int k = 5,i;
	double Data[k][2];
	
	for(i=0; i<k;i++)
		Data[i][0] = 100000.0;
#ifdef debug 
	printf("new test data: ");
	for(i=0;i<90;i++)
		printf("%lf ",B[test_no][i]);
	printf("\n");
#endif	
	for(i=0;i<training_size;i++) {
		double temp_distance = distance(A,B,i,test_no);
		if(temp_distance==0)
			return class[i];
#ifdef debug
		printf("distance(data,%d) = %lf Data[k-1][0]=%lf\n",i,temp_distance,Data[k-1][0]);
#endif
		int index = k-1;
		if(temp_distance < Data[k-1][0]) {
			Data[k-1][0] = temp_distance;
			Data[k-1][1] = class[i];
#ifdef debug
		printf("distance(data,%d) = %lf\n",i,temp_distance);
#endif
			while(Data[index-1][0] > Data[index][0]) {
				int temp[2];
				temp[0]=Data[index-1][0];
				temp[1]=Data[index-1][1];
				Data[index-1][0]=Data[index][0];
				Data[index-1][1]=Data[index][1];
				Data[index][0]= temp[0];
				Data[index][1]= temp[1];
#ifdef debug 
				printf("new index=%d\n",i);
#endif
				if(index==1)
					break;
				index--;
			}
		}
	}
	int count[90];
	memset(count,0,sizeof(count));
	for(i=0;i<k;i++) {
#ifdef debug
		printf("class = %d\n",(int)Data[i][1]);
#endif
		count[(int)Data[i][1]]++;
	}
	int ans=1,max=-1;
	/*
	for(i=0;i<90;i++) {
		if(max<count[i]) {
			max= count[i];
			ans =i;
		}
	}*/

	for(i=0;i<k;i++)
		{
		if(max<count[(int)Data[i][1]])
			{
			ans = (int)Data[i][1];
			max = count[(int)Data[i][1]];
			}
		}
	return ans;
}

int main()
{
int rank,nprocs;
int result[1000];
int class[10000];
MPI_Init(NULL,NULL);
MPI_Comm_rank (MPI_COMM_WORLD, &rank);
MPI_Comm_size (MPI_COMM_WORLD, &nprocs);

int i,j,n,m;
if(rank == 0)
	scanf("%d",&n);

MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);

if(rank==0)
	{
	for(i=0;i<n;i++) {
		for(j=0;j<90;j++) {
			scanf("%lf",&training_data[i][j]);
		}
		scanf("%d",&class[i]);
		}
	scanf("%d",&m);
	}
MPI_Bcast(class,n,MPI_INT,0,MPI_COMM_WORLD);
MPI_Bcast(training_data,n*90,MPI_DOUBLE,0,MPI_COMM_WORLD);
MPI_Bcast(&m,1,MPI_INT,0,MPI_COMM_WORLD);
int tot = m;
int done = 0;
int last;

while(done < tot)
	{
	if(rank == 0)
		{
		if(done + nprocs < tot)
			last = done+nprocs;
		else
			last = tot;
		for(i=done;i<last;i++)
			{
			for(j=0;j<90;j++) {
				scanf("%lf",&test_data[i-done][j]);
			}
			}
		}
	
int ans;
MPI_Bcast(test_data,nprocs*90,MPI_DOUBLE,0,MPI_COMM_WORLD);
ans = find_class(training_data,test_data,class,n,rank);
MPI_Gather(&ans, 1, MPI_INT,result, 1, MPI_INT,0, MPI_COMM_WORLD);
if(rank==0)
	{
	for(i=done;i<last;i++)
		printf("%d\n",result[i-done]);
		
	}

done+=nprocs;
}
MPI_Finalize();
return 0;
}
