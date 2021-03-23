#include<stdio.h>
//Bankers algorithm is a mechanism to prevent deadlock in a multi resource scenario
//for single resource it is enough to check if there is a cycle in thr RAG
//for multi recourse if a cycle exists, deadlock may exist
//If the processes will go into a deadlock it returns that else returns a safe sequence of execution

/*
ALLOCATED : MATRIX OF ALLOCATED RESOURCES OFEACH TYPE FOR EACH PROCESS
NEED : HOW MUCH IS REQUIRED AT A GIVEN TIME FOR EACH PROCESS EACH TYPE
MAX NEEDED : MATRIX OF HOW MUCH NEEDED OF EACH TYPE TO FULFILL DEMAND
AVAILBLE : ARRAY OF RESOUCES PRESENT AT A POINT OF TIME

NEED = MX NEEDED - ALLOCATED

THE working is as :
- The need matrix is generatd based on the max needed - allocated
- The availble array is calculated as (resource[i] - sum(all resource instances of type[i]))
- Each process is scanned serially and checked whether the need row, corresponding to the process can be satisfied 
with the resources present in available
- IF so, then the processes are scaneed for and checked, if the request is satisfied, 
then the allocated resources are added to the available matrix
*/


int main()
{
	int process, resources;
	int i, j, k = 0, count1 = 0, count2 = 0;
	
	printf("\nEnter the number of processes: ");
	scanf("%d",&process);
	
	printf("\nEnter the number of resources: ");
	scanf("%d",&resources);
	
	int max [process] [resources], allocated[process] [resources], need [process] [resources], available[resources], completed [process], resource_instances[resources];
	
	printf("\nEnter the resource instances:\n");
	for(i = 0; i < resources; i++){
		scanf("%d", &resource_instances[i]);
	}
	for(i = 0; i < process; i++){
		completed[i] = 0;
	}
	
	for(i = 0; i < resources; i++)
	{
		available[i] = 0;
	}
	
	printf("\nEnter max no. of instances of resource that a [process needs]:\n");
	for(i = 0; i < process; i++)
	{
		printf("For P[%d]: ",i);
		for(j = 0; j < resources; j++)
		{
			scanf("%d",&max[i][j]);
		}
	}
	
	printf("\nEnter the allocated matrix\n");
	for(i = 0; i < process; i++)
	{
		printf("For p[%d]: ", i);
		for(j = 0;j < resources; j++)
		{
			scanf("%d", &allocated[i][j]);
		}
	}
	
	for(i = 0; i < process; i++)
	{
		for(j = 0; j < resources; j++)
		{
			need[i][j] = max[i][j] - allocated[i][j];
		}
	}
	
	for(i = 0; i < resources; i++)
	{
		for(j = 0; j < process; j++)
		{
			available[i] = available[i] + allocated[j][i];
		}
	}
	
	for(i = 0;i < resources; i++)
	{
		available[i] = resource_instances[i] - available[i];
	}
	
	printf("\nExecution Sequence\n");
	
	//when it comes back to the process again, after a loop
	while(count1 != process)
	{
		count2 = count1;
		//if the value of count hasnt changed from the beginning and 
		//no process has been completed, this means there is a deadlock as 
		//each of the process is waiting on another process 
		
		//in this nested for loop, it is checked whether a given process can be satisfied
		//it will exit either when count1 == process count or when count1 == count2, indicating no progress has been made
		for(i = 0; i < process; i++)
		{
			for(j = 0; j < resources; j++)
			{
				if(need[i][j] <= available[j])
				{
					k++;
				}
			}
			if(k == resources && completed[i]==0)
			{
				completed[i] = 1;
				for(j = 0;j < resources; j++)
				{
					available[j] = allocated[i][j] + available[j];
				}
				printf("p[%d]\n", i);
				count1++;
			}
			k = 0;
		}
		if(count1 == count2)
		{
			printf("%d %d\n", count1, count2);
			printf("Not Safe - DEADLOCK..\n");
			break;
		}
	}
	
	//if the value of count1 is not count2, then all have been completed sucessfully
	if(count1 != count2)
	{
		printf("%d %d\n", count1, count2);
		printf("Safe State - No DEADLOCK\n");
	}	
	return 0;
}
