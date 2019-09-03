/*
 µœ÷æÿ’Û≥À∑®
*/

#include <stdio.h>
int main()
{
	int a[4][3] = {{1,2,3},{2,3,4},{3,4,5}};
	int b[3][2] = {{1,8},{2,6},{3,4}};
	int c[4][2];
	int temp = 0,i,j,k;
	for( i = 0;i < 4;i ++ )	
	{
	    for( k = 0;k < 2;k ++ )
		{
			for( j = 0;j < 3;j ++ )
			{	
			    temp += a[i][j] * b[j][k];
		    }
		    c[4][2] = temp;	
		    printf("%d\t",c[4][2]);
	    }
		printf("\n");
	}
	return 0;
}

