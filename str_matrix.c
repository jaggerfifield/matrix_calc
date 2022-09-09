#include <stdio.h>
#include <stdlib.h>

int main( void ){

	int m, n;

	printf("Enter matrix size m,n: ");

	scanf("%d,", &m);
	scanf("%d", &n);

	char*** matrix = (char***)malloc(sizeof(char**) * m);

	for(int i = 0; i < m; i++){
		matrix[i] = (char**)malloc(sizeof(char*) * n);
	}

	// Fill the matrix:
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){

			char *l = (char*)malloc(32);

			printf("[%d][%d]: ", i, j);
			scanf("%s", l);
		
			matrix[i][j] = l;
		}
	}

	printf("The Matrix is: \n");

	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			printf("[%s] ", matrix[i][j]);
		}
		printf("\n");
	}

	// Free memory
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			free(matrix[i][j]);
		}
		free(matrix[i]);
	}

	free(matrix);

	return 0;
}
