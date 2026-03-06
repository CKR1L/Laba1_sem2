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
            mat -> data[i] = (int*)malloc(column * sizeof(int));
        }
        else {
            mat -> data[i] = (float*)malloc(column * sizeof(float));
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
    if(!mat -> data) return;
    for(int i = 0; i < mat -> line; i++){
        if(mat -> data[i]){
            free(mat -> data[i]);
        }
    } 
    free(mat -> data);
    free(mat);   
}
int input_matrix(Matrix* mat){
    if(!mat) {
        printf("Ошибка: матрица не инициализирована!\n");
        return 1;
    }
    printf("Введите элементы матрицы размера (%d * %d):\n", mat->line, mat->column);
    for (int i = 0; i < mat -> line; i++){
        for (int j = 0; j < mat -> column; j++){
            if (mat -> type == 0){
                printf("mat[%d][%d] int: ", i, j);
                if (scanf("%d", &((int**)mat->data)[i][j]) != 1) {
                    printf("Ошибка ввода целого числа!\n");
                    return 1;
                }
            } else {
                printf("mat[%d][%d] float: ", i, j);
                if (scanf("%f", &((float**)mat->data)[i][j]) != 1) {
                    printf("Ошибка ввода вещественного числа!\n");
                    return 1;
                }
            }
        }
    }
    return 0;
}
int check_type_matrix(Matrix*a, Matrix*b){
    if(!a||!b) return 0;
    return a -> type == b -> type;
}
int print_matrix(Matrix* mat){
    if(!mat) {
        printf("Ошибка: матрица не инициализирована!\n");
        return 1;
    }
    for (int i = 0; i < mat->line; i++){
        printf("|");
        for (int j = 0; j < mat->column; j++){
            if(mat->type == 0){
                printf("%d ", ((int**)mat->data)[i][j]);
            } else {
                printf("%.2f ", ((float**)mat->data)[i][j]);
            }
        }
        printf("|\n");
    }
    return 0;
}
Matrix* add_matrices(Matrix*a, Matrix*b){
    if(!a || !b){
        printf("Матрицы не инициализированы!\n");
        return 0;
    }
    if((a -> line != b -> line)|| (a ->column != b->column)){
        printf("Размерность матриц не совпадает (необходимое условие для сложения)!");
        return 0;
    }
    if(!check_type_matrix(a, b)){
        printf("Ошибка! Матрицы должны быть одного типа (необходимое условие для сложения)!");
        return 0;
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
                    ((float**)result -> data)[i][j] += ((float**)a -> data)[i][k] * ((float**)b -> data)[k][j];
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
                ((int**)result -> data)[j][i] = ((int**)mat -> data)[i][j];
            }else{
                ((float**)result -> data)[j][i] = ((float**)mat -> data)[i][j];
            }
        }
    }
    return result;
}
int AddLinearCombination(Matrix*mat, int target_line, int line1, int line2, void* coeff1, void* coeff2){
    if (!mat){
        printf("Матрица не иницилизирована\n");
        return 1;
    }
    if (target_line < 0 || target_line >= mat -> line || line1 < 0 || line1 >= mat -> line || line2 < 0 || line2 >= mat -> line ){
        printf("Ошибка! Неверный индекс строки!\n");
        return 1;
    }
    if (!coeff1 || !coeff2){
        printf("Коэффиценты не могут быть равны 0\n");
        return 1;
    }
    if (mat -> type == 0){
        int** int_data = (int**)mat -> data;
        int c1 = *(int*)coeff1;
        int c2 = *(int*)coeff2;
        printf("Используйте целочисленные коэффиценты: %d и %d\n", c1, c2);
    
        for (int j = 0; j < mat -> column; j++){
            int_data[target_line][j] += c1 * int_data[line1][j] + c2 * int_data[line2][j];
        }  
    }
    else{
        float** float_data = (float**)mat -> data;
        float c1 = *(float*)coeff1;
        float c2 = *(float*)coeff2;
        printf("Используйте вещественные коэффиценты: %f и %f\n", c1, c2);
        for (int j = 0; j < mat -> column; j++){
            float_data[target_line][j] += c1 * float_data[line1][j] + c2 * float_data[line2][j];
        }
    }
    printf("Операция выполнена!\n");
    return 0;
}   