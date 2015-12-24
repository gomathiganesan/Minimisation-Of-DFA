#include<stdio.h>
#include<stdlib.h>
void minimise(char*,char**,int,int*,int**,int);
int isSamePartition(int *,int *,int);
int generateNewPartition(int*,int,int**,int);
void modifyPartitionIntransitionTable(int*,int**,char**,int);
void printEquivalentStates(int*,int);
int eliminateDuplicateStates(char*,char*,int*,char**,int);
void printMinimisedTransTable(char*,char**,int);
