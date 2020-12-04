#include<stdio.h>
#include<conio.h>

void main()
{
	int i_rows,j_columns,m,n;

	printf("\nEnter The Number Of Processes : ");
	scanf("%d",&i_rows);

	printf("\nEnter The Number Of Resources : ");
	scanf("%d",&j_columns);

	int ProcessNumber[i_rows],ResourcNumber[j_columns];
	printf("\nEnter Process Numbers for %d Processes : ",i_rows);
	for(m=0;m<i_rows;m++)
	{
		scanf("%d",&ProcessNumber[m]);
	}

	printf("\nEnter Resource ID for %d Resources : ",j_columns);
	for(m=0;m<j_columns;m++)
	{
		scanf("%d",&ResourcNumber[m]);
	}

	printf("\nProcess ID : ");
	for(m=0;m<i_rows;m++)
	{
		printf("[ %d ] ",ProcessNumber[m]);
	}

	printf("\nResource ID with Name : ");
	for(m=0;m<j_columns;m++)
	{
		printf("[ %d , %c ] ",ResourcNumber[m],ResourcNumber[m]+65);
	}

	int Allocation[i_rows][j_columns],Max[i_rows][j_columns],Need[i_rows][j_columns],Available[j_columns];

	printf("\nEnter The Data For Available matrix ");
	for(n=0;n<j_columns;n++)
	{
		scanf("%d",&Available[n]);
	}

	printf("\nEnter The Data For Allocation matrix ");
	for(m=0;m<i_rows;m++)
	{
		printf("\nEnter The Number Of Resources Allocated for Process %d ",ProcessNumber[m]);
		for(n=0;n<j_columns;n++)
		{
			printf("\nHow Many Instance Have Been Allocated From Resource %c ",ResourcNumber[n]+65);
			scanf("%d",&Allocation[m][n]);
		}
	}

	printf("\nEnter The Data For Max matrix ");
	for(m=0;m<i_rows;m++)
	{
		printf("\nEnter The Total Number Of Resources Required for Process %d ",ProcessNumber[m]);
		for(n=0;n<j_columns;n++)
		{
			printf("\nHow Much Total Instances is Required of Resource %c ",ResourcNumber[n]+65);
			scanf("%d",&Max[m][n]);
		}
	}

	for(m=0;m<i_rows;m++)
	{
		for(n=0;n<j_columns;n++)
		{
			Need[m][n] = Max[m][n] - Allocation[m][n];
		}
	}

	printf("\n\t-Allocation matrix- \t\t\t -Max matrix- \n");
	printf("\t");
	for(n=0;n<j_columns;n++)
	{
		printf("%c\t",ResourcNumber[n]+65);
	}
	printf("\t\t");
	for(n=0;n<j_columns;n++)
	{
		printf("%c\t",ResourcNumber[n]+65);
	}

	printf("\n");
	for(m=0;m<i_rows;m++)
	{
		printf("P%d      ",ProcessNumber[m]);
		for(n=0;n<j_columns;n++)
		{
			printf("%d       ",Allocation[m][n]);
		}
		printf("\t\t");
		for(n=0;n<j_columns;n++)
		{
			printf("%d\t",Max[m][n]);
		}
		printf("\n");
	}


	printf("\n\t-Need matrix-\n");
	printf("\t");
	for(n=0;n<j_columns;n++)
	{
		printf("%c\t",ResourcNumber[n]+65);
	}
	printf("\n");
	for(m=0;m<i_rows;m++)
	{
		printf("P%d      ",ProcessNumber[m]);
		for(n=0;n<j_columns;n++)
		{
			printf("%d       ",Need[m][n]);
		}
		printf("\n");
	}

	printf("\nAvailable Vector = [");
	for(n=0;n<j_columns;n++)
	{
		printf(" %d ",Available[n]);
	}

	printf("]\n");

	int success = 0,skip = 0,deadLock = 0,iteration = 0;
	int alreadyExecuted[i_rows],safeStateArray[i_rows];
	int index = 0,k;

	while(1)
	{
		for(m=0;m<i_rows;m++)
		{
			success = 0;

			if(index != 0)
			{
				for(k=0;k<index;k++)
				{
					if(m == alreadyExecuted[k])
					{
						skip = 1;
						break;
					}
				}

				if(skip == 1)
				{
					skip = 0;
					continue;
				}
			}

			for(n=0;n<j_columns;n++)
			{
				if(Available[n] >= Need[m][n])
				{
					success++;
				}
			}

			if(success == j_columns)
			{
				safeStateArray[index] = ProcessNumber[m];

				alreadyExecuted[index] = m;
				index++;

				for(n=0;n<j_columns;n++)
				{
					Available[n] = Available[n] + Allocation[m][n];
				}
			}
		}

		if(index == i_rows)
		{
			break;
		}

		iteration++;
		if(index == 0 || iteration == i_rows)
		{
			deadLock = 1;
			printf("\nDEADLOCK ALERT..!!");
			break;
		}
	}

	if(deadLock != 1)
	{
		printf("\nsafe sequence = [");
		for(m=0;m<i_rows;m++)
		{
			printf(" %d ",safeStateArray[m]);
		}
		printf("]");
	}
}
