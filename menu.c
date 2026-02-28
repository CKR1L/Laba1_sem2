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
    printf("7. Выход\n");
    printf("Выберите действие: ");
}
Matrix* create_input_matrix() {
    int line;
    int column;
    int type;
    printf("Введите количество строк и столбцов в матрице\n");
    scanf("%d, %d ", &line, &column);
    printf("Выберите тип матрицы (0 - целые числа, 1 - вещественные числа)");
    scanf("%d", &type);
    Matrix* mat = create_matrix(line, column, type);
    if (!mat){
        printf("Ошибка создания матрицы!\n");
        return 0;
    }
    input_matrix(mat);
    printf("Матрица создана\n");
    print_matrix(mat);
    return mat;
}
void menu_choice(int choice, Matrix*mat1, Matrix*mat2){
    Matrix*result = NULL;
    switch(choice){
        case 1:
            if (mat1) free_matrix(mat1);
            mat1 = create_input_matrix();
            break;
        case 2:
            if (mat2) free_matrix(mat2);
            mat2 = create_input_matrix();
            break;
        case 3:
            if (!mat1 || !mat2){
                printf("Сначала создайте  две матрицы\n");
                break;
            }
            result = add_matrices(mat1, mat2);
            if (result){
                printf("Результат сложения\n");
                print_matrix(result);
                free_matrix(result);
            }
            break;
        case 4:
            if (!mat1 || !mat2){
                printf("Сначала создайте две матрицы\n");
                break;
            }
            result = multiplication_matrices(mat1, mat2);
            if (result){
                printf("Результат умножения\n");
                print_matrix(result);
                free_matrix(result);
            }
            break;
        case 5:
            if(!mat1){
                printf("Сначала создайте матрицу\n");
                break;
            }
            result = transposition_matrix(mat1);
            if (result){
                printf("Транспонированная матрица\n");
                print_matrix(result);
                free_matrix(result);
            }
            break;
        case 6:
            if(!mat2){
                printf("Сначала создайте матрицу\n");
                break;
            }
            result = transposition_matrix(mat2);
            if (result){
                printf("Транспонированная матрица\n");
                print_matrix(result);
                free_matrix(result);
            }
            break;
        case 7:
            printf("Работа программы завершена\n");
            break;
        default:
            printf("Неверный ввод! Введите число от 1-7");           
    }       
}
void run_prog(){
    Matrix* mat1 = NULL;
    Matrix* mat2 = NULL;
    int choice;
    while(1){
        display_menu();
        scanf("%d", &choice);
        if (choice == 7){
            if (mat1) free_matrix(mat1);
            if (mat2) free_matrix(mat2);
            break;
        }
        menu_choice(choice, mat1, mat2);
    }
}