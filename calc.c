#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#define STRLEN 32

// TODO
// char** export_matrix(cahr***);
// char** import_matrix(char*);

void main_menu();
char*** create_matrix();
char*** modify_matrix(char***);
char*** loop(char***);
void operate_matrix(char***);
double add(double, double);
int is_row_digit(char**, int);
void print_matrix(char***);
char*** remove_matrix(char***);

int main( void ){
	char*** matrix1 = NULL;
	
	while(1){
		matrix1 = loop(matrix1);
	}
	
	return 0;
}

char*** loop(char*** matrix1){
	char a[STRLEN];
	
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
		matrix1 = remove_matrix(matrix1);
	}else if(*a == '3'){
		print_matrix(matrix1);	
	}else if(*a == '4'){
		matrix1 = modify_matrix(matrix1);
	}else if(*a == '5'){
		operate_matrix(matrix1);
	}else if(*a == '6'){
		// Cleanup before quitting
		if(matrix1 != NULL){
			matrix1 = remove_matrix(matrix1);
		}
		exit(0);
	}else{
		printf("\nChoice [ %s ] not found, try again!\n", a);
	}

	return matrix1;
}

void main_menu(){
	printf("\n");
	printf("Please select a operation:\n");
	printf("1) Add matrix\n2) Remove Matrix\n3) List Matrix\n4) Modify Matrix\n5) Operate matrix\n6) Quit\n$> ");

	return;
}

char*** create_matrix(){
	int m, n;
	char *name = (char*)malloc(STRLEN);
	unsigned int max_str_length = 0;

	// Get matrix name
	printf("Enter matrix name: ");
	scanf("%s", name);

	// Get size of array m x n
	printf("\nEnter the size of matrix: m,n\n");
	scanf("%d,", &m);
	scanf("%d", &n);

	// Pointers to array pointers
	char*** matrix = (char***)malloc(sizeof(char**) * (m + 1));

	// Matrix size stored in first array
	// This array is [0] = size m ; [1] = size n; [2] = largest string len
	matrix[0] = (char**)malloc(sizeof(char*) * 4);
	char *cm = (char*)malloc(STRLEN), *cn = (char*)malloc(STRLEN);
	sprintf(cm, "%d", m);
	sprintf(cn, "%d", n);
	matrix[0][0] = cm;
	matrix[0][1] = cn;

	matrix[0][3] = name;

	// Allocate space for numbers
	for(int i = 1; i < m + 1; i++){
		printf("Allocating [%llu] bits for row [%d]\n", sizeof(char*)*n*CHAR_BIT, i);
		matrix[i] = (char**)malloc(sizeof(char*) * n);
	}

	// Fill matrix
	for(int i = 1; i < m + 1; i++){
		printf("Row %d : \n", i);
		for(int j = 0; j < n; j++){

			char* l = (char*)malloc(STRLEN);

			// The matrix is displayed differently than it is stored 
			printf("[%d][%d] = ", i, j + 1);
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

	int a, m, n, row1, row2;

	// Load the size from matirx into int variables
	sscanf(matrix[0][0], "%d", &m);
	sscanf(matrix[0][1], "%d", &n);

	printf("\n");
	print_matrix(matrix);

	// Get input
	printf("Enter operation:\n1) ADD\t2)SUB\t3)sMUL\n$> ");
	scanf("%d", &a);

	if(a < 1 || a > 4){
		printf("Bad selection, try again!\n");
		return;
	}
	
	printf("Enter first row: ");
	scanf("%d", &row1);

	if(a != 3){
		printf("Enter second row: ");
		scanf("%d", &row2);
	}

	// Operate on matrix
	if(a == 1){
		printf("First row digit check: %d\n", is_row_digit(matrix[row1], n));
		printf("Second row digit check: %d\n", is_row_digit(matrix[row2], n));	

		if(is_row_digit(matrix[row1], n) && is_row_digit(matrix[row2], n)){
			for(int i = 0; i < n; i++){
				double a, b, ans;

				// Get and convert the values to double for addition
				sscanf(matrix[row1][i], "%lf", &a);
				sscanf(matrix[row2][i], "%lf", &b);

				ans = add(a, b);

				sprintf(matrix[row1][i], "%f", ans);

			}
		}
	}
	return;
}

double add(double a, double b){

	return a + b;
}

char* add_string(char* a, char* b){
	a = strcat(a, "+");
	a = strcat(a, b);
	return a;
}

int is_row_digit(char** row, int n){
	int is_digit, row_size;

	for(int j = 0; j < n; j++){
		row_size = strlen(row[j]);
		for(int k = 0; k < row_size; k++){
			is_digit = 1;
			if(!isdigit(row[j][k])){
				if(row[j][k] == '.' || row[j][k] == '/' || row[j][k] == '-'){
					continue;
				}else{
					is_digit = 0;	
				}
			}
		}			
	}
	
	return is_digit;
}

char*** modify_matrix(char*** matrix){
	int j, k, m, n;

	// Load the size from matirx into int variables
	sscanf(matrix[0][0], "%d", &m);
	sscanf(matrix[0][1], "%d", &n);

	printf("Enter spot to be edited j,k (-1 for all): ");
	scanf("%d,", &j);

	if(j == -1){
		for(int x = 1; x < m + 1; x++){
			for(int y = 0; y < n; y++){
				char* l = (char*)malloc(STRLEN);
				printf("[%d][%d] Old value: %s\n", x, y + 1, matrix[x][y]);
				printf("Enter new value or . to keep: ");
				scanf("%s", l);

				if(*l != '.'){
					// Free old value
					free(matrix[x][y]);	
					matrix[x][y] = l;
				}else{
					free(l);
				}					
			}
		}
		return matrix;
	}

	scanf("%d", &k);

	if(j > m || k > n || j < 1 || k < 1){
		printf("Invalid selection!\n");
		return matrix;
	}

	char* l = (char*)malloc(STRLEN);
	
	printf("[%d][%d] Old value: %s\n", j, k, matrix[j][k - 1]);
	printf("Enter new value: ");
	scanf("%s", l);

	// Free old value
	free(matrix[j][k - 1]);
	
	matrix[j][k - 1] = l;

	printf("The new matrix is:\n");
	print_matrix(matrix);

	return matrix;
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

char*** remove_matrix(char*** matrix){
	int m, n;
	sscanf(matrix[0][0], "%d", &m);
	sscanf(matrix[0][1], "%d", &n);

	printf("\n");

	// Free matrix header, this is needed b/c the matrix could be a different size
	free(matrix[0][0]);		// m Size
	free(matrix[0][1]);		// n Size
	free(matrix[0][2]);		// max_str_length
	free(matrix[0][3]);		// Matrix name
	free(matrix[0]);

	// Free matrix
	for(int i = 1; i < m+1; i++){
		for(int j = 0; j < n; j++){
			printf("Freeing: [%d][%d] = %s\n", i, j, matrix[i][j]);
			free(matrix[i][j]);
		}
		free(matrix[i]);
	}

	free(matrix);
	
	return NULL;	
}
