#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#define ASSERT_EQ(x, y) assert((x) == (y))
#define EPSILON 0.0001
void test_int_matrix(){
    printf("ТЕСТЫ ЦЕЛОЧИСЛЕННХ МАТРИЦ\n");
    printf("Создание матрицы 2*3\n");
    Matrix*mat = create_matrix(2, 3, 0);
    assert(mat != NULL);
    ASSERT_EQ(mat -> line, 2);
    ASSERT_EQ(mat -> column, 3);
    ASSERT_EQ(mat -> type, 0);
    printf("Заполняем матрцу\n");
    int values1[] = {1, 2, 3, 4, 5, 6};
    int k = 0;
    for(int i = 0; i < mat -> line; i++) {
        for(int j = 0; j < mat -> column; j++) {
            ((int**)mat->data)[i][j] = values1[k++];
        }
    }
    printf("Матрица А (2*3)\n");
    print_matrix(mat);
    printf("Проверка введенных значений");
    k = 0;
    for(int i = 0; i < mat -> line; i++) {
        for(int j = 0; j < mat -> column; j++) {
            ASSERT_EQ(((int**)mat -> data)[i][j], values1[k++]);
        }
    }
    printf("Создание второй матрицы 3*2");
    Matrix*mat2 = create_matrix(3, 2, 0);
    int values2[] = {7, 8, 9, 10, 11, 12};
    int f = 0;
    for(int i = 0; i < mat2 -> line; i++) {
        for(int j = 0; j < mat2 -> column; j++) {
            ((int**)mat2 -> data)[i][j] = values2[f++];
        }
    }   
    printf("Матрица B (3*2)\n");
    print_matrix(mat2);
     printf("Тест умножения прямоугольных матриц (2x3 * 3x2 = 2x2)\n");
    Matrix* result1 = multiplication_matrices(mat, mat2);
    assert(result1 != NULL);
    ASSERT_EQ(result1 -> line, 2);
    ASSERT_EQ(result1 -> column, 2);
    printf("Результат умножения A(2x3) * B(3x2):\n");
    print_matrix(result1);
    int expected_result1[] = {58, 64, 139, 154};
    int e = 0;
    for(int i = 0; i < result1 ->   line; i++) {
        for(int j = 0; j < result1 -> column; j++) {
            ASSERT_EQ(((int**)result1 -> data)[i][j], expected_result1[e++]);
        }
    }
    printf("Транспонирование прямоугольной матрицы\n");
    Matrix*result2 = transposition_matrix(mat);
    assert(result2 != NULL);
    ASSERT_EQ(result2 -> line, 3);
    ASSERT_EQ(result2 -> column, 2);
    printf("Транспонированная матрица\n");
    print_matrix(result2);
    ASSERT_EQ(((int**)result2 -> data)[0][0], 1);
    ASSERT_EQ(((int**)result2 -> data)[0][1], 4); 
    ASSERT_EQ(((int**)result2 -> data)[1][0], 2); 
    ASSERT_EQ(((int**)result2 -> data)[1][1], 5); 
    ASSERT_EQ(((int**)result2 -> data)[2][0], 3); 
    ASSERT_EQ(((int**)result2 -> data)[2][1], 6); 
    printf("Очистка памяти\n");
    free_matrix(mat);
    free_matrix(mat2);
    free_matrix(result1);
    free_matrix(result2);
    printf("Тестирование целочисленных матриц завершено\n");
}    
void test_float_matrix(){
    printf("ТЕСТЫ ВЕЩЕСТВЕННЫХ МАТРИЦ\n");
    printf("Создание матрицы 2*3\n");
    Matrix*mat = create_matrix(2, 3, 1);
    assert(mat != NULL);
    ASSERT_EQ(mat -> line, 2);
    ASSERT_EQ(mat -> column, 3);
    ASSERT_EQ(mat -> type, 1);
    printf("Заполняем матрицу\n");
    float values1[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6};
    int a = 0;
    for(int i = 0; i < mat -> line; i++) {
        for(int j = 0; j < mat -> column; j++) {
            ((float**)mat -> data)[i][j] = values1[a++];
        }
    }
    printf("Матрица А 2*3\n");
    print_matrix(mat);
    printf("Создание матрицы 3*2\n");
    Matrix*mat2 = create_matrix(3, 2, 1);
    assert(mat2 != NULL);
    ASSERT_EQ(mat2 -> line, 3);
    ASSERT_EQ(mat2 -> column, 2);
    ASSERT_EQ(mat2 -> type, 1);
    printf("Заполняем матрицу\n");
    float values2[] = {7.7, 8.8, 9.9, 10.1, 11.2, 12.3};
    int c = 0;
    for(int i = 0; i < mat2 -> line; i++) {
        for(int j = 0; j < mat2 -> column; j++) {
            ((float**)mat2 -> data)[i][j] = values2[c++];
        }
    }
    printf("Матрица B 3*2\n");
    print_matrix(mat2);
    printf("Умножение матриц\n");
    Matrix*result1 = multiplication_matrices(mat, mat2);
    assert(result1 != NULL);
    ASSERT_EQ(result1->line, 2);
    ASSERT_EQ(result1->column, 2);
    printf("Результат умножения:\n");
    print_matrix(result1);
    printf("Транспонирование матрицы\n");
    Matrix*result2 = transposition_matrix(mat);
    assert(result2 != NULL);
    ASSERT_EQ(result2->line, 3);
    ASSERT_EQ(result2->column, 2);
    printf("Транспонированная матрица:\n");
    print_matrix(result2);
    printf("6. Очистка памяти\n");
    free_matrix(result1);
    free_matrix(result2);
    free_matrix(mat);
    free_matrix(mat2);
    printf("Тестирование вещественных матриц завершенно\n");
}
void test_linear_combination(){
    printf("Тестирование работы с линейными комбинациями\n");
    printf("Создание матрицы 3*4\n");
    Matrix* mat = create_matrix(3, 4, 0);
    int val = 1;
    for(int i = 0; i < mat->line; i++) {
        for(int j = 0; j < mat->column; j++) {
            ((int**)mat->data)[i][j] = val++;
        }
    }
    printf("Исходная матрица 3*4\n");
    print_matrix(mat);
    printf("Линейная комбинация: строка 0 = строка0 + 2*строка1 + 3*строка2\n");
    int c1 = 2, c2 = 3;
    int result = AddLinearCombination(mat, 0, 1, 2, &c1, &c2);
    assert(result == 0);
    printf("Матрица после операции:\n");
    print_matrix(mat);
    assert(((int**)mat->data)[0][0] == 38);
    assert(((int**)mat->data)[0][1] == 44);
    assert(((int**)mat->data)[0][2] == 50);
    assert(((int**)mat->data)[0][3] == 56);
    assert(((int**)mat->data)[1][0] == 5);
    assert(((int**)mat->data)[2][0] == 9);
    free_matrix(mat);
    printf("Тестрирование завершено\n");
}