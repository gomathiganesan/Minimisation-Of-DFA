#include"minimiseDFA.h"
int main()
{
	int n,i,f,k=0,flag,j;
	printf("Enter the no.of states\n");
	scanf("%d",&n);
	char *states=(char*)malloc(sizeof(char)*n);
	char **transitionTable=(char**)malloc(sizeof(char*)*n);
	for(i=0;i<n;i++)
		transitionTable[i]=(char*)malloc(sizeof(char)*2);
	for(i=0;i<n;i++)
	{
		states[i]='A'+i;
	}
	for(i=0;i<n;i++)
	{
		printf("For state %c:\n",states[i]);
		printf("Enter the next state\n");
		printf("When 'a' is the input\n");
		scanf(" %c",&transitionTable[i][0]);
		printf("When 'b' is the input\n");
		scanf(" %c",&transitionTable[i][1]);
	}
	printf("Enter the no of final states\n");
	scanf("%d",&f);
	char* final=(char*)malloc(sizeof(char)*f);
	printf("Enter the final states\n");
	for(i=0;i<f;i++)
	{
		scanf(" %c",&final[i]);
	}
	char* nonfinal=(char*)malloc(sizeof(char)*(n-f));
	int* partition=(int*)malloc(sizeof(int)*n);
	for(i=0;i<n;i++)
	{
		flag=0;
		for(j=0;j<f;j++)
		{
			if(states[i]==final[j])
			{
				flag=1;
				partition[i]=2;
				break;
			}
		}
		if(!flag)
		{
			nonfinal[k++]=states[i];
			partition[i]=1;
		}
	}
	printf("Initial transition table\n");
	printf("States\tInput 'a'  Input 'b'\n");
	for(i=0;i<n;i++)
	{
		printf("%c\t%c\t%c\n",states[i],transitionTable[i][0],transitionTable[i][1]);
	}
	
	printf("Minimizing the DFA\n");
	int** transitionTable_partNo=(int**)malloc(sizeof(int*)*n);
	for(i=0;i<n;i++)
		transitionTable_partNo[i]=(int*)malloc(sizeof(int)*2);
	minimise(states,transitionTable,n,partition,transitionTable_partNo,2);
}

