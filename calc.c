#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 32

void main_menu();
char*** create_matrix();
void modify_matrix(char***);
void loop(char*, char***);
void operate_matrix(char***);
void print_matrix(char***);
void remove_matrix(char***);

int main( void ){
	char a[STRLEN];
	char*** matrix1;
	loop(a, matrix1);
	return 0;
}

void loop(char* a, char*** matrix1){

	// Print the menu
	main_menu();

	// Get user input
	scanf("%s", a);

	if(*a == '1'){
		if(matrix1 == NULL){
			matrix1 = create_matrix();
			printf("\nAdding matrix: \n");
			print_matrix(matrix1);
		}else{
			printf("Matrix Full");
		}
	}else if(*a == '2'){
		remove_matrix(matrix1);
	}else if(*a == '3'){
		print_matrix(matrix1);	
	}else if(*a == '4'){
		modify_matrix(matrix1);
	}else if(*a == '5'){
		operate_matrix(matrix1);
	}else if(*a == '6'){
		// Cleanup before quitting
		if(matrix1 != NULL){
			remove_matrix(matrix1);
		}
		free(matrix1);
		exit(0);
	}else{
		printf("\nChoice [ %s ] not found, try again!\n", a);
	}

	loop(a, matrix1);
	
	return;
}

void main_menu(){
	printf("\n");
	printf("Please select a operation:\n");
	printf("1) Add matrix\n2) Remove Matrix\n3) List Matrix\n4) Modify Matrix\n5) Operate matrix\n6) Quit\n$> ");

	return;
}

char*** create_matrix(){
	//char *m = (char*)malloc(STRLEN), *n = (char*)malloc(STRLEN);
	int m, n;
	unsigned int max_str_length = 0;

	// Get size of array m x n
	printf("\nEnter the size of matrix: m,n\n");
	scanf("%d,", &m);
	scanf("%d", &n);

	// Pointers to array pointers
	char*** matrix = (char***)malloc(sizeof(char**) * (m + 1));

	// Matrix size stored in first array
	// This array is [0] = size m ; [1] = size n; [2] = largest string len
	matrix[0] = (char**)malloc(sizeof(char*) * 3);
	char *cm = (char*)malloc(STRLEN), *cn = (char*)malloc(STRLEN);
	sprintf(cm, "%d", m);
	sprintf(cn, "%d", n);
	matrix[0][0] = cm;
	matrix[0][1] = cn;

	// Allocate space for numbers
	for(int i = 1; i < m + 1; i++){
		printf("Allocating size: %lu ;  N is : %d ; i is %d\n", sizeof(char*)*n, n, i);
		matrix[i] = (char**)malloc(sizeof(char*) * n);
	}

	// Fill matrix
	for(int i = 1; i < m + 1; i++){
		printf("Row %d\n", i);
		for(int j = 0; j < n; j++){

			char* l = (char*)malloc(STRLEN);
		
			printf("[%d][%d] = ", i - 1, j);
			scanf("%s", l);

			if(max_str_length < strlen(l)){
				max_str_length = strlen(l);
			}

			matrix[i][j] = l;
		}
		printf("\n");
	}

	// Apped the max string length to the array
	char* l = (char*)malloc(STRLEN);
	sprintf(l, "%u", max_str_length);
	matrix[0][2] = l;

	return matrix;
}

void operate_matrix(char*** matrix){
	char op[STRLEN];

	printf("\n");
	print_matrix(matrix);
	printf("Enter operation: ");
	scanf("%s", op);
	printf("The operation is: %s\n", op);

	if(op[0] == 'R' || op[0] == 'r'){
		int r1 = (int)op[1];

		printf("The first row is: %d\n", r1);
	}

	return;
}

void modify_matrix(char*** matrix){
	int j, k;
	char* l = malloc(STRLEN);
	printf("Enter spot to be edited j,k (-1 for all): ");
	scanf("%d,", &j);

	if(j == -1){
		printf("WIP");
		return;
	}

	scanf("%d", &k);

	printf("[%d][%d] Old value: %s\n", j, k, matrix[j + 1][k]);
	printf("Enter new value: ");
	scanf("%s", l);

	// Free old value
	free(matrix[j + 1][k]);
	
	matrix[j + 1][k] = l;

	printf("The new matrix is:\n");
	print_matrix(matrix);

	return;
}

void print_matrix(char*** matrix){
	printf("\n");

	// Print the size of the matrix
	printf("m = %s 	n = %s\n", matrix[0][0], matrix[0][1]);

	int m, n;

	// Load the size from matirx into int variables
	sscanf(matrix[0][0], "%d", &m);
	sscanf(matrix[0][1], "%d", &n);

	// Formatting to to pass to printf, better aligns text
	char format[STRLEN] = "[%", end[] = "s] ";
	strcat(format, matrix[0][2]);
	strcat(format, end);

	// Print the matrix
	for(int i = 1; i < m + 1; i++){
		printf("R%d : ", i);
		for(int j = 0; j < n; j++){
			printf(format, matrix[i][j]);
		}
		printf("\n");
	}
	
	return;
}

void remove_matrix(char*** matrix){
	int m, n;
	sscanf(matrix[0][0], "%d", &m);
	sscanf(matrix[0][1], "%d", &n);

	for(int i = 0; i < m + 1; i++){
		for(int j = 0; j < n; j++){
			free(matrix[i][j]);
		}
		free(matrix[i]);
	}

	free(matrix);
	
	return;	
}
