#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define  MAX_COL 512
#define  MAX_ROW 512

#define TRUE 1
#define FALSE 0

int** create_matrix(int arraySizeX, int arraySizeY);
int ** initialize(int ** M, int value);
int ** multiply(int ** A, int ** B);
int ** transpose(int ** M);
int ** t_optimized_mutlitply(int ** A, int ** B);
int are_equal(int ** A, int ** B);

int main(int arg, char ** args){
    clock_t begin, end;

    int  ** A = NULL;
    int  ** B = NULL;
    int  ** product = NULL;
    int  ** product1 = NULL;
    
    A = create_matrix(MAX_ROW, MAX_COL);
    B = create_matrix(MAX_ROW, MAX_COL);

    A = initialize(A, 1);
    B = initialize(B, 1);

    printf("Call naive multiplication function\n");
    begin = clock();
    product = multiply(A, B);
    end = clock();
    printf("Multiplication ended\n");
    printf("Time elapsed is %f\n", (float)(end - begin)  / CLOCKS_PER_SEC);

    printf("Call tranpositiion optimisation multiplication function\n");
    begin = clock();
    product1 = t_optimized_mutlitply(A, B);
    end = clock();
    printf("Multiplication ended\n");
    printf("Time elapsed is %f\n", (float)(end - begin)  / CLOCKS_PER_SEC);
    
    printf("Got the same result?");
    if (are_equal(product, product))
        printf(" YES.");
    else printf(" NO.");
    printf("\n");
    return 0;
}

int** create_matrix(int arraySizeX, int arraySizeY) {
int** array;
array = (int**) malloc(arraySizeX*sizeof(int*));
for (int i = 0; i < arraySizeX; i++)
   array[i] = (int*) malloc(arraySizeY*sizeof(int));
   return array;
} 

int ** initialize(int ** M, int value){
    for (int i = 0;  i < MAX_ROW; i++)
       for (int j = 0;  j < MAX_ROW; j++)
            M[i][j] += value;
    return M;
}


int ** multiply(int ** A, int ** B)
{

    int ** C = create_matrix(MAX_ROW, MAX_COL);
    C = initialize(C, 0);
    for (int i = 0; i < MAX_COL; i++)
        for (int j = 0;  j < MAX_ROW; j++)
            for (int k = 0;  k < MAX_ROW; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

int ** transpose(int ** M){
    int ** T = create_matrix(MAX_ROW, MAX_COL);
    for (int i = 0; i < MAX_COL; i++)
        for (int j = 0;  j < MAX_ROW; j++)
                T[i][j] = M[j][i];
    return T;
}


int ** t_optimized_mutlitply(int ** A, int ** B){
    int ** C = create_matrix(MAX_ROW, MAX_COL);
    C = initialize(C, 0);
    B = transpose(B);

    for (int i = 0; i < MAX_COL; i++)
        for (int j = 0;  j < MAX_ROW; j++)
            for (int k = 0;  k < MAX_ROW; k++)
                C[i][j] += A[i][k] * B[j][k];
    return C;
}


int are_equal(int ** A, int ** B){
     
    for (int i = 0; i < MAX_COL; i++)
        for (int j = 0;  j < MAX_ROW; j++)
            if (A[i][j] != B[i][j])
                return FALSE;
    return TRUE;
}
