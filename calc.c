#include <stdio.h>
#include <stdlib.h>

#define TOTAL 4

void main_menu(int*);
int** create_matrix();
void modify_matrix(int**);
void loop(int*, int**, int**);
void operate_matrix(int**);
void print_matrix(int**);
void remove_matrix(int**);

int main( void ){
	int *a = (int*)malloc(sizeof(char));
	int **matrix1 = NULL, **matrix2 = NULL;
	while(1){
		loop(a, matrix1, matrix2);
	}
	return 0;
}

void loop(int* a, int** matrix1, int** matrix2){
	
	main_menu(a);

	if(*a == 1){
		if(matrix1 == NULL){
			matrix1 = create_matrix();
			printf("\nAdding matrix: \n");
			print_matrix(matrix1);
		}else{
			matrix2 = create_matrix();
			printf("Adding matrix: \n");
			print_matrix(matrix2);
		}
	}else if(*a == 2){
		remove_matrix(matrix1);
	}else if(*a == 3){
		print_matrix(matrix1);	
	}else if(*a == 4){
		modify_matrix(matrix1);
	}else if(*a == 5){
		operate_matrix(matrix1);
	}else if(*a == 6){
		// Cleanup before quitting
		if(matrix1 != NULL){
			remove_matrix(matrix1);
		}
		free(matrix1);
		free(a);
		exit(0);
	}else{
		printf("\nNumber %d not found, try again!\n", *a);
	}
	return;
}

void main_menu(int *a){
	printf("\n");
	printf("Please select a operation:\n");
	printf("1) Add matrix\n2) Remove Matrix\n3) List Matrix\n4) Modify Matrix\n5) Operate matrix\n6) Quit\n$> ");

	scanf("%d", a);
	return;
}

int** create_matrix(){
	int m, n;
	printf("\nEnter the size of matrix: m x n\n");
	printf("m = ");
	scanf("%d", &m);
	printf("n = ");
	scanf("%d", &n);

	int **matrix = (int**) malloc(sizeof(int*) * (m + 1));

	matrix[0] = (int*)malloc(sizeof(int) * 2);
	matrix[0][0] = m;
	matrix[0][1] = n;

	for(int i = 1; i < n + 1; i++){
		matrix[i] = (int*)malloc(sizeof(int) * n);
	}

	// Fill matrix
	for(int i = 1; i < m + 1; i++){
		for(int j = 0; j < n; j++){
			printf("[%d][%d] = ", i - 1, j);
			scanf("%d", &matrix[i][j]);
		}
	}
	return matrix;
}

void operate_matrix(int** matrix){
	char* op = NULL;

	printf("[0][0] is : %d\n", matrix[0][0]);

	printf("\n");
	print_matrix(matrix);
	printf("Enter operation: ");
	scanf("%s", op);
	printf("The operation is: %s", op);
	return;
}

void modify_matrix(int** matrix){
	int j, k, l;
	printf("Enter spot to be edited j,k (-1 for all): ");
	scanf("%d,", &j);
	if(j == -1){
		printf("WIP");
		return;
	}
	scanf("%d", &k);

	printf("[%d][%d] Old value: %d\n", j, k, matrix[j][k]);
	printf("Enter new value: ");
	scanf("%d", &l);
	matrix[j + 1][k] = l;

	printf("The new matrix is:\n");
	print_matrix(matrix);

	return;
}

void print_matrix(int** matrix){
	printf("m = %d 	n = %d\n", matrix[0][0], matrix[0][1]);

	// Print the matrix
	for(int i = 1; i < matrix[0][1] + 1; i++){
		for(int j = 0; j < matrix[0][0]; j++){
			printf("[%d] ", matrix[i][j]);
		}
		printf("\n");
	}
	
	return;
}

void remove_matrix(int** matrix){
	int m = matrix[0][0];

	for(int i = 0; i < m + 1; i++){
		free(matrix[i]);
		printf("Freeing: matrix[%d]\n", i);
	}
	
	return;	
}