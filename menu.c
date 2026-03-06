#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
void display_menu() {
    printf("МЕНЮ ПРОГРАММЫ\n");
    printf("1. Создать первую матрицу\n");
    printf("2. Создать вторую матрицу\n");
    printf("3. Сложение матриц\n");
    printf("4. Умножение матриц\n");
    printf("5. Транспонирование первой матрицы\n");
    printf("6. Транспонирование второй матрицы\n");
    printf("7.Прибавление линейной комбинации в первой матрице\n");
    printf("8. Выход\n");
    printf("Выберите действие: ");
}
Matrix* create_input_matrix() {
    int line, column, type;
    
    printf("Введите количество строк и столбцов в матрице: ");
    scanf("%d %d", &line, &column);
    
    printf("Выберите тип матрицы (0 - целые числа, 1 - вещественные числа): ");
    scanf("%d", &type);
    Matrix* mat = create_matrix(line, column, type);
    if (!mat) {
        printf("Ошибка создания матрицы!\n");
        return NULL;
    }
    input_matrix(mat);
    printf("\nМатрица создана:\n");
    print_matrix(mat);
    return mat;
}
int line_combination(Matrix*mat, char matrix_name){
    if (!mat){
        printf("Матрица не создана\n");
        return 1;
    }
    int target_line, line1, line2;
    printf("Текущая матрица %s:\n", matrix_name);
    print_matrix(mat);
    printf("Введите номер целевой строки от (0 - %d)\n", mat -> line - 1);
    if(scanf("%d", &target_line) != 1){
        printf("Ошибка ввода!\n");
        return 1;
    }
    printf("Введите номер первой исходной строки от (0 - %d)\n", mat -> line - 1);
    if(scanf("%d", &line1) != 1){
        printf("Ошибка ввода\n");
        return 1;
    }
    printf("Введите номер второй исходной строки от (0 - %d)\n", mat -> line - 1);
    if (scanf("%d", &line2) != 1){
        printf("Ошибка ввода\n");
        return 1;
    }
    if (mat -> type == 0){
        int c1, c2;
        printf("Введите целочисленный коэффицент для первой строки: \n");
        if (scanf("%d", &c1) != 1){
            printf("Ошибка ввода\n");
        }
        printf("Введите целочисленный коэффицент для второй строки: \n");
        if (scanf("%d", &c2) != 1){
            printf("Ошибка ввода\n");
        }
        int result = AddLinearCombination(mat, target_line, line1, line2, &c1, &c2);
        if (result == 0){
            printf("Матрица после операции\n", matrix_name);
            print_matrix(mat);
        }
        return result;
    }
    else{
        float c1, c2;
        printf("Введите вещественный коэффицент для первой строки: \n");
        if (scanf("%f", &c1) != 1){
            printf("Ошибка ввода\n");
        }
        printf("Введите вещественный коэффицент для первой строки: \n");
        if (scanf("%f", &c2) != 1){
            printf("Ошибка ввода\n");
        }
        int result = AddLinearCombination(mat, target_line, line1, line2, &c1, &c2);
        if (result == 0){
            printf("Матрица после операции\n", matrix_name);
            print_matrix(mat);
        }
        return result;
    }
}

void menu_choice(int choice, Matrix** mat1, Matrix** mat2) {
    Matrix* result = NULL;
    int matrix_choice;
    
    switch(choice) {
        case 1:
            if (*mat1) {
                free_matrix(*mat1);
                *mat1 = NULL;
            }
            *mat1 = create_input_matrix();
            break;  
        case 2:
            if (*mat2) {
                free_matrix(*mat2);
                *mat2 = NULL;
            }
            *mat2 = create_input_matrix();
            break;
        case 3:
            if (!*mat1) {
                printf("\nПервая матрица не создана. Создайте её:\n");
                *mat1 = create_input_matrix();
            }
            
            if (!*mat2) {
                printf("\nВторая матрица не создана. Создайте её:\n");
                *mat2 = create_input_matrix();
            }
            if (*mat1 && *mat2) {
                result = add_matrices(*mat1, *mat2);
                if (result) {
                    printf("\nРезультат сложения:\n");
                    print_matrix(result);
                    free_matrix(result);
                }
            }
            break;
            
        case 4:
            if (!*mat1) {
                printf("\nПервая матрица не создана. Создайте её:\n");
                *mat1 = create_input_matrix();
            }
            
            if (!*mat2) {
                printf("\nВторая матрица не создана. Создайте её:\n");
                *mat2 = create_input_matrix();
            }
            if (*mat1 && *mat2) {
                result = multiplication_matrices(*mat1, *mat2);
                if (result) {
                    printf("\nРезультат умножения:\n");
                    print_matrix(result);
                    free_matrix(result);
                }
            }
            break; 
        case 5:
            if (!*mat1) {
                printf("\nПервая матрица не создана. Создайте её:\n");
                *mat1 = create_input_matrix();
            }
            if (*mat1) {
                result = transposition_matrix(*mat1);
                if (result) {
                    printf("\nТранспонированная матрица:\n");
                    print_matrix(result);
                    free_matrix(result);
                }
            }
            break;  
        case 6:
            if (!*mat2) {
                printf("\nВторая матрица не создана. Создайте её:\n");
                *mat2 = create_input_matrix();
            }           
            if (*mat2) {
                result = transposition_matrix(*mat2);
                if (result) {
                    printf("\nТранспонированная матрица:\n");
                    print_matrix(result);
                    free_matrix(result);
                }
            }
            break;
        case 7:
            printf("Выберите матрицу для операции:\n");
            printf("Первую матрицу\n");
            printf("Вторую матрицу");
            if (scanf("%d", &matrix_choice) !=1){
                printf("Ошибка ввода\n");
                break;
            }
            if (matrix_choice == 1){
                if (!*mat1){
                    printf("Матрица не создана. Создайте её\n");
                    *mat1 = create_input_matrix();
                }
                line_combination(*mat1, "первая");
            }
            else if(matrix_choice == 2){
                if (!*mat2){
                    printf("Матрица не создана. Создайте её\n");
                    *mat2 = create_input_matrix();
                }
                line_combination(*mat2, "вторая");
            }
        case 8:
            printf("Работа программы завершена\n");
            break;          
        default:
            printf("Неверный ввод! Введите число от 1 до 7\n");
    }
}
void run_prog() {
    Matrix* mat1 = NULL;
    Matrix* mat2 = NULL;
    int choice;
    while(1) {
        display_menu();
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Ошибка ввода! Введите число.\n");
            continue;
        }
        if (choice == 7) {
            if (mat1) {
                free_matrix(mat1);
                mat1 = NULL;
            }
            if (mat2) {
                free_matrix(mat2);
                mat2 = NULL;
            }
            break;
        }
         menu_choice(choice, &mat1, &mat2);
    }
}