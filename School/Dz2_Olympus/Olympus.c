#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>


uint8_t __exit=0;

//Вывести квадратную матрицу заданого размера с поэлементым заполнением
//числами в порядке их возрастания
void _task1()
{
	//Динамическое выделение памяти подглядел в интеренете
	uint32_t MSize=0;
	uint8_t **M;

	printf("Enter size of matrix:");
	scanf("%d", &MSize);

	M=(uint8_t**)malloc(MSize*sizeof(uint8_t*));
	for(uint8_t i=0; i<MSize; i++)
		M[i]=(uint8_t*)malloc(MSize*sizeof(uint8_t));

	for(uint8_t i=0; i<MSize; i++)
	{
		for(uint8_t j=0; j<MSize; j++)
			M[i][j]=i*MSize+j;
	}

	printf("\n");



	for(uint8_t i=0; i<MSize; i++)
	{
		for(uint8_t j=0; j<MSize; j++)
			printf("%5d", M[i][j]);
		printf("\n");
	}
	free(M);
}

void _task2()
{
	uint32_t ArraySize=0;
	uint8_t *A, *nA;

	printf("Enter size of array:");
	scanf("%d", &ArraySize);

	A=(uint8_t*)malloc(ArraySize*sizeof(uint8_t));

	for(uint8_t i=0; i<ArraySize; i++)
		A[i]=i;

	for(uint8_t i=0; i<ArraySize; i++)
		printf("%5d", A[i]);
	printf("\n");

	nA=(uint8_t*)malloc(ArraySize*sizeof(uint8_t));
	for(uint8_t i=0; i<ArraySize; i++)
		nA[i]=A[sizeof(A)-i+1];

	for(uint8_t i=0; i<ArraySize; i++)
		printf("%5d", nA[i]);
	printf("\n");

	free(A);
}

void _task3()
{
	uint32_t MSize=0;
	uint8_t **M;

	printf("Enter size of matrix:");
	scanf("%d", &MSize);

	M=(uint8_t**)malloc(MSize*sizeof(uint8_t*));
	for(uint8_t i=0; i<MSize; i++)
		M[i]=(uint8_t*)malloc(MSize*sizeof(uint8_t));

	for(uint8_t i=0; i<MSize; i++)
	{
		for(uint8_t j=0; j<MSize; j++)
		{
			if(j>=i)
				M[i][j]=0;
			else
				M[i][j]=1;
		}
	}

	printf("\n");
	for(uint8_t i=0; i<MSize; i++)
	{
		for(uint8_t j=0; j<MSize; j++)
		{
			printf("%5d", M[i][j]);
		}
		printf("\n");
	}
	free(M);

}

void _task4()
{
/*
 *	0	1	2	3	4
 *
 *	15	16	17	18	5
 *
 *	14	23	24	19	6
 *
 *	13	22	21	20	7
 *	
 *	12	11	10	9	8
 * */

	uint32_t MSize=0;
	uint8_t **M;
	uint8_t s=1; 
	int x=1, y=1;

	printf("Enter size of matrix:");
	scanf("%d", &MSize);

	M=(uint8_t**)malloc(MSize*sizeof(uint8_t*));
	for(uint8_t i=0; i<MSize; i++)
		M[i]=(uint8_t*)malloc(MSize*sizeof(uint8_t));

	for(uint8_t i=0; i<MSize*MSize; i++)
		M[i%MSize][i/MSize]=0;


	for(uint8_t i=0; i<MSize; i++)
	{
		for(uint8_t j=0; j<MSize; j++)
			printf("%5d", M[i][j]);
		printf("\n");
	}
	printf("\n");
	

	for(int k=0; k<MSize; k++)
	{
		M[0][k]=s;
		s++;
	}
	for(int k=1; k<MSize; k++)
	{
		M[k][MSize-1]=s;
		s++;
	}
	for(int k=0; k<=MSize; k++)
	{
		M[MSize-1][MSize-k]=s;
		s++;
	}
	for(int k=0; k<MSize-1; k++)
	{
		M[MSize-k-1][0]=s;
		s++;
	}
	

	while(s<MSize*MSize)
	{
		while(M[y][x+1]==0)
		{
			M[y][x]=s;
			s++;
			x++;
		}
		while(M[y+1][x]==0)
		{
			M[y][x]=s;
			s++;
			y++;
		}
		
		while(M[y][x-1]==0)
		{
			M[y][x]=s;
			s++;
			x--;
		}
		while(M[y-1][x]==0)
		{
			M[y][x]=s;
			s++;
			y--;
		}
	}

	for(uint8_t i=0; i<MSize; i++)
		for(uint8_t j=0; j<MSize; j++)
			if(M[i][j]==0)
				M[i][j]=s;


	for(uint8_t i=0; i<MSize; i++)
	{
		for(uint8_t j=0; j<MSize; j++)
			printf("%5d", M[i][j]);
		printf("\n");
	}

	printf("\n");
	free(M);
}



void Decision(uint8_t task)
{
	switch (task)
	{
		case 0:
		_task1();
		break;

		case 1:
		_task2();
		break;

		case 2:
		_task3();
		break;

		case 3:
		_task4();
		break;
	
		default:
		__exit=1;
	}

}

int main(void)
{
	uint32_t TheTask=0;

	while(__exit!=1)
	{
		printf("Enter number of task:");
		scanf("%d", &TheTask);
		Decision((uint8_t)TheTask);
	}


	return 0;
}
