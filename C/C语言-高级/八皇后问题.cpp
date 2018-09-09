#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define FALSE (1==0)
#define TRUE  (1==1)
#define SIZE 8

/*
八个1排8x8，不同行同列（八皇后问题）
*/

int eight_queen(char checkerboard[SIZE][SIZE], int sum);
int put_queen(char checkerboard[SIZE][SIZE], int row, int column);
int print(char checkerboard[SIZE][SIZE]);

int main(int argc, char *argv[])
 {
	char checkerboard[SIZE][SIZE];

	//init checkerboard
	int i, j;
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			checkerboard[i][j]='-';
		}
	}
	eight_queen(checkerboard, 0);
	system("pause");
	return 0;
}
int eight_queen(char checkerboard[SIZE][SIZE], int sum)
{
	int i, j, num;
	char array[SIZE][SIZE];
	char array1[SIZE][SIZE];

	//复制
	memcpy(array, checkerboard, SIZE*SIZE*sizeof(char));
	memcpy(array1, checkerboard, SIZE*SIZE*sizeof(char));

	if(sum == 8)
	{
		num++;
		printf("~~~~~~~~~第%d种~~~~~~~~~~~~\n",num);
		print(array1);
		//system("pause");
	}
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			if(TRUE == put_queen(array, i, j))
			{
				sum++;
				if(eight_queen(array, sum) == -1)
				{
					array1[i][j] = '0';
					memcpy(array, array1, SIZE*SIZE*sizeof(char));
					sum--;
				}
			}
		}
	}
	return -1;
}
int put_queen(char checkerboard[SIZE][SIZE], int row, int column)
{
	int i = 0;
	if(checkerboard[row][column]=='-')
	{
		for(i = 0; i < 8; i++)
		{
			checkerboard[row][i] = '0';
			checkerboard[i][column] = '0';
			if(row + i < SIZE && column + i < SIZE)
				checkerboard[row + i][column + i] = '0';
			if(row - i >= 0 && column - i >= 0)
				checkerboard[row - i][column - i] = '0';
			if(row - i >= 0 && column + i < SIZE)
				checkerboard[row - i][column + i] = '0';
			if(row + i < SIZE && column - i >= 0)
				checkerboard[row + i][column - i] = '0';
		}
		checkerboard[row][column] = '1';
		return TRUE;
	}
	return FALSE;
}
int print(char checkerboard[SIZE][SIZE])
{
	int i, j;
	for(i = 0; i < SIZE; i++)
	{
		for(j = 0; j < SIZE; j++)
		{
			printf("%c ",checkerboard[i][j]);
		}
		printf("\n\r");
	}
}

