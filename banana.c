#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mpi.h"

#define size 10000

char str[size*10];
short int *arr;

int reg ;
int flagreg ;
int value[size];
int curr;
char res[size];
int pos;
int command[size];
int len;

int ind(int i,int j)
{
return (i*size + j);
}

int execute(int comm,int j)
{
int i,k;
char ch[1000];
switch(comm)
	{
	case 1:curr--;j++;
	break;

	case 2:curr++;j++;
        break; 

	case 3:if(value[curr]!=3)
			execute(value[curr],j);
		else
			j++;
        break; 

	case 4:if(value[curr]!=0)
			{
			res[pos++] = (char)value[curr];
//			printf("val : %d\n",value[curr]);
			}
		j++;
        break;	 

	case 5:value[curr]--;j++;
        break; 

	case 6:value[curr]++;j++;
 	       break; 

	case 7:value[curr]=0;j++;
        break; 

	case 8:if(flagreg == 0)
		{
		reg = value[curr];	
		flagreg = 1;
		}
		else
		{
		value[curr] = reg;
		flagreg = 0;
		}
		j++;
        break; 

	case 9:k = value[curr];
		i=0;
		while(k>0)
			{
			ch[i++] = k%10 + '0';
			k=k/10;
			}
		ch[i]='\0';
		for(k=0;k<i;k++)
			res[pos+k] = ch[i-k-1];
		pos+=i;
		j++;
        break; 

	case 10:j-=2;
		while(command[j]!=11)
			j--;		
	break;

	case 11:if(value[curr]==0)
			{
			j+=2;
			while(command[j]!=10)
				j++;
			j++;
			}
		else
			j++;
		
	break;
	}
return j;
}

int func(char ch[])
{
if(strcmp(ch,"baNAna")==0)
	return 1;
if(strcmp(ch,"banaNA")==0)
        return 2;
if(strcmp(ch,"baNANA")==0)
        return 3;
if(strcmp(ch,"BAnana")==0)
        return 4;
if(strcmp(ch,"BANAna")==0)
        return 5;
if(strcmp(ch,"BAnaNA")==0)
        return 6;
if(strcmp(ch,"BaNana")==0)
        return 7;
if(strcmp(ch,"bAnAna")==0)
        return 8;
if(strcmp(ch,"baNaNa")==0)
        return 9;
if(strcmp(ch,"banana")==0)
        return 10;
if(strcmp(ch,"BANANA")==0)
        return 11;
else return 0;
}

void convert(int i,char a[], int n)
{
int j,k;
char ch[7];
for(j=0;j<=n-6;j=j+6)
	{
	k=0;
	while(k<6)
		{
		ch[k]=a[j+k];
		k++;
		}
	ch[k]='\0';
	arr[ind(i,j/6)] = func(ch);
	}
arr[ind(i,j/6)]=-1;
}

int main()
{
int rank,nprocs;
int i,j,n,last;
MPI_Init(NULL,NULL);
MPI_Comm_rank (MPI_COMM_WORLD, &rank);
MPI_Comm_size (MPI_COMM_WORLD, &nprocs);

char *result = malloc(sizeof(char)*nprocs*size);

arr = (short int *)malloc(sizeof(short int)*nprocs*size);

if(rank == 0)
	scanf("%d",&n);

MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
int tot = n;
int done = 0;
while(done < tot)
{
if(rank == 0)
	{
	for(i=0;i<nprocs;i++)
		arr[ind(i,0)]=-1;

	if(done+nprocs < tot)
		last = done+nprocs;
	else
		last = tot;
	for(i=done;i<last;i++)
		{
		scanf("%s",str);
		convert(i-done,str,strlen(str));
		}
	}
MPI_Bcast(arr,nprocs*size,MPI_SHORT,0,MPI_COMM_WORLD);
len=0;
reg=0;
flagreg=0;
curr=0;
pos=0;
while(arr[ind(rank,len)]!=-1)
	{
//	printf("%d ",arr[ind(rank,len)]);
	command[len] = arr[ind(rank,len)];
	len++;
	}

j=0;
while(j<len)
	{
	j=execute(command[j],j);
	}

res[pos+1]='\0';
//printf("\n%d : %s\n",rank,res);
MPI_Gather(res, size, MPI_CHAR,result, size, MPI_CHAR,0, MPI_COMM_WORLD);

if(rank==0)
	{
	for(i=done;i<last;i++)
		{
		j=0;
		while(result[ind(i-done,j)]!='\0')
			{
			printf("%c",result[ind(i-done,j)]);
			j++;
			}
		printf("\n");
		}
	}	
done+=nprocs;
}
MPI_Finalize();
return 0;
}
