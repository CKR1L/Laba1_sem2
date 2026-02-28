#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"
Matrix* create_matrix(int line, int column, int type){
    Matrix *mat = (Matrix*)malloc(sizeof(Matrix));
    if (!mat) return 0;
    mat -> line = line;
    mat -> column = column;
    mat -> type = type;
    mat -> data = (void**)malloc(line*sizeof(void*));
    if (!mat -> data){
        free(mat);
        return 0;
    }
    for(int i = 0; i < line; i++){
        if(type == 0){
            mat -> data[i] = (int*)malloc(line * sizeof(int));
        }
        else {
            mat -> data[i] = (float*)malloc(line * sizeof(float));
        }
        if(!mat -> data[i]){
            for(int j = 0; j < i; j++){
                free(mat -> data[j]);
            }
            free(mat -> data);
            free(mat);
            return 0;
        }
    }
    return mat; 
}
void free_matrix(Matrix*mat){
    if(!mat -> data) return 0;
    for(int i = 0; i < mat -> line; i++){
        if(mat -> data[i]){
            free(mat -> data[i]);
        }
    } 
    free(mat -> data);
    free(mat);   
}
void input_matrix(Matrix*mat){
    if(!mat) return 0;
    printf("Введите элементы матрицы размера (%d * %d):\n", mat -> line, mat -> column );
    for (int i = 0; i < mat -> line; i++){
        for (int j = 0; i < mat -> column; i++){
            if (mat -> type == 0){
                printf("mat[%d][%d] int: ", i, j);
                scanf("%d", &((int**)mat -> data)[i][j]);
            }else{
                printf("mat[%d][%d] float: ", i, j);
                scanf("%f", &((float**)mat -> data)[i][j]);
            }
        }
    }
}
int check_type_matrix(Matrix*a, Matrix*b){
    if(!a||!b) return 0;
    return a -> type == b -> type;
}
void print_matrix(Matrix*mat){
    if(!mat) return 0;
    for (int i = 0; i < mat -> line; i++){
        for (int j = 0; i < mat -> column; i++){
            if(mat -> type == 0){
                printf("%d", ((int**)mat -> data)[i][j]);
            }else{
                printf("%f", ((float**)mat -> data)[i][j]);
            }
        }
        printf("\n");
    }
}
Matrix* add_matrices(Matrix*a, Matrix*b){
    if(!a || !b){
        printf("Матрицы не инициализированы!\n");
        return 0;
    }
    if((a -> line != b -> line)|| (a ->column != b->column)){
        printf("Размерность матриц не совпадает (необходимое условие для сложения)!");
    }
    if(!check_type_matrix(a, b)){
        printf("Ошибка! Матрицы должны быть одного типа (необходимое условие для сложения)!");
    }
    Matrix*result = create_matrix(a -> line, a -> column, a -> type);
    if(!result) return 0;
    for (int i = 0; i < a -> line; i++){
        for (int j = 0; j < a -> column; j++){
            if (a -> type == 0){
                ((int**)result -> data)[i][j] = ((int**)a -> data)[i][j] + ((int**)b -> data)[i][j];
            }else{
                ((float**)result -> data)[i][j] = ((float**)a -> data)[i][j] + ((float**)b -> data)[i][j];
            }
        }
    }
    return result;
}
Matrix* multiplication_matrices(Matrix*a, Matrix*b){
    if(!a || !b){
        printf("Матрицы не инициализированы!\n");
        return 0;
    }
    if(a -> column != b -> line){
        printf("Ошибка! Число столбцов первой матрицы должно быть равно числу строк второй матрицы (необходимое условие умножения матриц)");
        return 0;
    }
    Matrix *result = create_matrix(a -> line, a -> column, a -> type);
    if(!result) return 0;
    for (int i = 0; i < a -> line; i++){
        for (int j = 0; j < a -> column; j++){
            if (a -> type == 0){
                ((int **)result -> data)[i][j] = 0;
                for (int k = 0; k < a -> column; k++){
                    ((int**)result -> data)[i][j] += ((int**)a -> data)[i][k] * ((int**)b -> data)[k][j];
                }
            }else{
                ((float**)result -> data)[i][j] = 0.0;
                for (int k = 0; k < a -> column; k++){
                    ((float**)result -> data)[i][j] += ((float**)a -> column)[i][k] * ((float**)b -> column)[k][j];
                }
            }
        }
    }
    return result;
}
Matrix*transposition_matrix(Matrix*mat){
    Matrix*result = create_matrix(mat -> line, mat -> column, mat -> type);
    for (int i = 0; i < mat -> line; i++){
        for (int j = 0; j < mat -> column; j++){
            if (mat -> type == 0){
                ((int**)result -> data)[j][i] == ((int**)mat -> data)[i][j];
            }else{
                ((float**)result -> data)[j][i] == ((float**)mat -> data)[i][j];
            }
        }
    }
    return result;
}