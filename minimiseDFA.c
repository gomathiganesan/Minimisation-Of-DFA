#include"minimiseDFA.h"
void minimise(char* states,char** transitionTable,int n,int* partition,int** transitionTable_partNo,int partitionNo)
{
	int i,j,res=0;
	char* resultStates=(char*)malloc(sizeof(char)*n);
	int l=0,z;
	int* visited=(int*)malloc(sizeof(int)*n);
	int* oldPartition=(int*)malloc(sizeof(int)*n);
	modifyPartitionIntransitionTable(partition,transitionTable_partNo,transitionTable,n);
	int oldPartitionNo;
	while(1)
	{
		oldPartitionNo=partitionNo;
		partitionNo=generateNewPartition(partition,partitionNo,transitionTable_partNo,n);
		modifyPartitionIntransitionTable(partition,transitionTable_partNo,transitionTable,n);
		res=isSamePartition(oldPartition,partition,n);	
		if(!res)
		{
			for(i=0;i<n;i++)
			{	
				oldPartition[i]=partition[i];
			}
		}
		else
			break;
		
	}
	printEquivalentStates(partition,n);
	l=eliminateDuplicateStates(states,resultStates,partition,transitionTable,n);
	printf("The transition table is\n");
	printf("State\tInput 'a'  Input 'b'\n");
	printMinimisedTransTable(states,transitionTable,n);
}
int isSamePartition(int *oldPartition,int *partition,int n)
{
	int i;
	int*p=(int*)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	{
		p[i]=partition[i]-oldPartition[i];
	}
	int b=p[0];
	for(i=1;b==p[i];i++)
		if(i==n-1)
			return 1;
	return 0;
}
int generateNewPartition(int* partition,int partitionNo,int** transitionTable_partNo,int n)
{
	int i,j;
	int* visited=(int*)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
		visited[i]=0;
	for(i=0;i<n;i++)
	{
		if(!visited[i])
		{
			partition[i]=++partitionNo;
			visited[i]=1;
			for(j=i+1;j<n;j++)
			{
				if(transitionTable_partNo[i][0]==transitionTable_partNo[j][0] && 
					transitionTable_partNo[i][1]==transitionTable_partNo[j][1] && !visited[j])
				{
					visited[j]=1;
					partition[j]=partition[i];
				}
			}
		}
	}
	return partitionNo;
}
void modifyPartitionIntransitionTable(int* partition,int** transitionTable_partNo,char** transitionTable,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		transitionTable_partNo[i][0]=partition[transitionTable[i][0]-'A'];
		transitionTable_partNo[i][1]=partition[transitionTable[i][1]-'A'];
	}
}
void printEquivalentStates(int* partition,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{	
		for(j=0;j<n;j++)
		{
			if(i!=j && partition[i]==partition[j])
				printf("State %c is equivalent to state %c\n",i+'A',j+'A');
		}
	}
}

int eliminateDuplicateStates(char* states,char* resultStates,int* partition,char** transitionTable,int n)
{
	int i,j,l=0,z;
	int* visited=(int*)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
		visited[i]=0;
	for(i=0;i<n;i++)
	{	
		if(!visited[i])
		{
			resultStates[l++]=states[i];
			for(j=0;j<n;j++)
			{
				if(i!=j && partition[i]==partition[j])
				{	visited[j]=1;
					states[j]=states[i];
					for(z=0;z<n;z++)
					{
						if(transitionTable[z][0]-'A'==j)
							transitionTable[z][0]='A'+i;
						if(transitionTable[z][1]-'A'==j)
							transitionTable[z][1]='A'+i;
					}
				}
						
			}
		}
	}
	return l;
}
void printMinimisedTransTable(char* states,char** transitionTable,int n)
{
	int i,j;
	int *visited=(int*)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
		visited[i]=0;
	for(i=0;i<n;i++)
	{
		if(!visited[i])
		{	
			visited[i]=1;
			printf("%c\t%c\t%c\n",states[i],transitionTable[i][0],transitionTable[i][1]);
		}
		for(j=i+1;j<n;j++)
		{
			if(states[i]==states[j] && transitionTable[i][0]==transitionTable[j][0] && 
					transitionTable[i][1]==transitionTable[j][1])
				visited[j]=1;
		}
	}
}
