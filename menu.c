#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Объявление тестовых функций
void test_int_matrix();
void test_float_matrix();
void test_linear_combination();

// Вспомогательная функция для очистки буфера ввода
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Функция для безопасного ввода целого числа
int safe_input_int(int* value, const char* prompt) {
    char buffer[100];
    
    while (1) {
        printf("%s", prompt);
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            clear_input_buffer();
            continue;
        }
        
        // Проверяем, не пустая ли строка
        if (buffer[0] == '\n') {
            printf("Ошибка! Введите целое число (только цифры)\n");
            continue;
        }
        
        int is_valid = 1;
        int has_digit = 0;
        
        // Проверяем каждый символ
        for (int i = 0; buffer[i] != '\n' && buffer[i] != '\0'; i++) {
            if (i == 0 && buffer[i] == '-') continue;  // Разрешаем минус в начале
            if (isdigit(buffer[i])) {
                has_digit = 1;
            } else if (buffer[i] != ' ') {  // Пробелы игнорируем
                is_valid = 0;
                break;
            }
        }
        
        if (is_valid && has_digit && sscanf(buffer, "%d", value) == 1) {
            return 1;
        }
        
        printf("Ошибка! Введите целое число (только цифры)\n");
    }
}

// Функция для безопасного ввода вещественного числа
int safe_input_float(float* value, const char* prompt) {
    char buffer[100];
    
    while (1) {
        printf("%s", prompt);
        
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            clear_input_buffer();
            continue;
        }
        
        // Проверяем, не пустая ли строка
        if (buffer[0] == '\n') {
            printf("Ошибка! Введите вещественное число (только цифры и точку)\n");
            continue;
        }
        
        int is_valid = 1;
        int dot_count = 0;
        int has_digit = 0;
        
        for (int i = 0; buffer[i] != '\n' && buffer[i] != '\0'; i++) {
            if (i == 0 && buffer[i] == '-') continue;  // Разрешаем минус в начале
            if (buffer[i] == '.') {
                dot_count++;
                if (dot_count > 1) {
                    is_valid = 0;
                    break;
                }
                continue;
            }
            if (isdigit(buffer[i])) {
                has_digit = 1;
            } else if (buffer[i] != ' ') {  // Пробелы игнорируем
                is_valid = 0;
                break;
            }
        }
        
        if (is_valid && has_digit && sscanf(buffer, "%f", value) == 1) {
            return 1;
        }
        
        printf("Ошибка! Введите вещественное число (только цифры и точку)\n");
    }
}

// Функция для безопасного ввода выбора меню
// Функция для безопасного ввода выбора меню
int safe_input_choice() {
    char buffer[100];
    
    while (1) {
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            clear_input_buffer();
            continue;
        }
        
        // Проверяем, не пустая ли строка
        if (buffer[0] == '\n') {
            printf("Ошибка! Ввод не может быть пустым.\n");
            printf("Выберите действие: ");
            continue;
        }
        
        int digit_count = 0;
        int value = 0;
        int has_invalid = 0;
        
        // Проверяем каждый символ
        for (int i = 0; buffer[i] != '\n' && buffer[i] != '\0'; i++) {
            if (isdigit(buffer[i])) {
                digit_count++;
                value = value * 10 + (buffer[i] - '0');
            } else if (buffer[i] != ' ' && buffer[i] != '\t') {
                has_invalid = 1;
                break;
            }
        }
        
        if (has_invalid) {
            printf("Ошибка! Введите только цифру.\n");
            printf("Выберите действие: ");
            continue;
        }
        
        if (digit_count == 1) {
            if (value >= 1 && value <= 9) {
                return value;
            } else {
                printf("Ошибка! Введите цифру от 1 до 9.\n");
                printf("Выберите действие: ");
            }
        } else if (digit_count > 1) {
            printf("Ошибка! Введите только одну цифру.\n");
            printf("Выберите действие: ");
        } else {
            printf("Ошибка! Введите цифру от 1 до 9.\n");
            printf("Выберите действие: ");
        }
    }
}

void display_menu() {
    printf("\n=== МЕНЮ ПРОГРАММЫ ===\n");
    printf("1. Создать первую матрицу\n");
    printf("2. Создать вторую матрицу\n");
    printf("3. Сложение матриц\n");
    printf("4. Умножение матриц\n");
    printf("5. Транспонирование первой матрицы\n");
    printf("6. Транспонирование второй матрицы\n");
    printf("7. Прибавление линейной комбинации\n");
    printf("8. Запуск тестов\n");
    printf("9. Выход\n");
    printf("Выберите действие: ");
}

Matrix* create_input_matrix() {
    int line, column, type;
    
    printf("\n--- Создание новой матрицы ---\n");
    
    if (!safe_input_int(&line, "Введите количество строк: ")) {
        return NULL;
    }
    if (line <= 0) {
        printf("Ошибка! Количество строк должно быть положительным\n");
        return NULL;
    }
    
    if (!safe_input_int(&column, "Введите количество столбцов: ")) {
        return NULL;
    }
    if (column <= 0) {
        printf("Ошибка! Количество столбцов должно быть положительным\n");
        return NULL;
    }
    
    printf("Выберите тип матрицы:\n");
    printf("0 - целые числа\n");
    printf("1 - вещественные числа\n");
    
    if (!safe_input_int(&type, "Ваш выбор: ")) {
        return NULL;
    }
    if (type != 0 && type != 1) {
        printf("Неверный тип матрицы. Выберите 0 или 1\n");
        return NULL;
    }
    
    Matrix* mat = create_matrix(line, column, type);
    if (!mat) {
        printf("Ошибка создания матрицы!\n");
        return NULL;
    }
    
    if (input_matrix(mat) != 0) {
        free_matrix(mat);
        return NULL;
    }
    
    printf("\nМатрица создана:\n");
    print_matrix(mat);
    return mat;
}

int line_combination(Matrix* mat, const char* matrix_name) {
    if (!mat) {
        printf("Матрица не создана\n");
        return 1;
    }
    
    int target_line, line1, line2;
    float c1_f, c2_f;
    int c1_i, c2_i;
    
    printf("\nТекущая матрица %s:\n", matrix_name);
    print_matrix(mat);
    
    char prompt[100];
    sprintf(prompt, "Введите номер целевой строки (0 - %d): ", mat->line - 1);
    if (!safe_input_int(&target_line, prompt)) {
        return 1;
    }
    
    sprintf(prompt, "Введите номер первой исходной строки (0 - %d): ", mat->line - 1);
    if (!safe_input_int(&line1, prompt)) {
        return 1;
    }
    
    sprintf(prompt, "Введите номер второй исходной строки (0 - %d): ", mat->line - 1);
    if (!safe_input_int(&line2, prompt)) {
        return 1;
    }
    
    // Проверка корректности индексов
    if (target_line < 0 || target_line >= mat->line ||
        line1 < 0 || line1 >= mat->line ||
        line2 < 0 || line2 >= mat->line) {
        printf("Ошибка! Индексы строк вне допустимого диапазона.\n");
        return 1;
    }
    
    if (mat->type == 0) {
        if (!safe_input_int(&c1_i, "Введите целочисленный коэффициент для первой строки: ")) {
            return 1;
        }
        if (!safe_input_int(&c2_i, "Введите целочисленный коэффициент для второй строки: ")) {
            return 1;
        }
        int result = AddLinearCombination(mat, target_line, line1, line2, &c1_i, &c2_i);
        if (result == 0) {
            printf("\nМатрица после операции %s:\n", matrix_name);
            print_matrix(mat);
        }
        return result;
    } else {
        if (!safe_input_float(&c1_f, "Введите вещественный коэффициент для первой строки: ")) {
            return 1;
        }
        if (!safe_input_float(&c2_f, "Введите вещественный коэффициент для второй строки: ")) {
            return 1;
        }
        int result = AddLinearCombination(mat, target_line, line1, line2, &c1_f, &c2_f);
        if (result == 0) {
            printf("\nМатрица после операции %s:\n", matrix_name);
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
            printf("\nВыберите матрицу для операции:\n");
            printf("1 - первую матрицу\n");
            printf("2 - вторую матрицу\n");
            if (!safe_input_int(&matrix_choice, "Ваш выбор: ")) {
                break;
            }
            
            if (matrix_choice == 1) {
                if (!*mat1) {
                    printf("Матрица не создана. Создайте её\n");
                    *mat1 = create_input_matrix();
                }
                if (*mat1) {
                    line_combination(*mat1, "первая");
                }
            } else if (matrix_choice == 2) {
                if (!*mat2) {
                    printf("Матрица не создана. Создайте её\n");
                    *mat2 = create_input_matrix();
                }
                if (*mat2) {
                    line_combination(*mat2, "вторая");
                }
            } else {
                printf("Неверный выбор! Введите 1 или 2.\n");
            }
            break;
            
        case 8:
            printf("\n=== ЗАПУСК ТЕСТОВ ===\n");
            run_test();
            break;
            
        case 9:
            printf("Работа программы завершена\n");
            break;
            
        default:
            printf("Неверный ввод! Введите число от 1 до 9\n");
    }
}

void run_prog() {
    Matrix* mat1 = NULL;
    Matrix* mat2 = NULL;
    int choice;
    
    while(1) {
        display_menu();
        clear_input_buffer();
        choice = safe_input_choice();
        
        if (choice == 9) {
            if (mat1) {
                free_matrix(mat1);
                mat1 = NULL;
            }
            if (mat2) {
                free_matrix(mat2);
                mat2 = NULL;
            }
            printf("Программа завершена. До свидания!\n");
            break;
        }
        
        menu_choice(choice, &mat1, &mat2);
    }
}

void run_test() {
    printf("\n--- Тестирование целочисленных матриц ---\n");
    test_int_matrix();
    
    printf("\n--- Тестирование вещественных матриц ---\n");
    test_float_matrix();
    
    printf("\n--- Тестирование линейных комбинаций ---\n");
    test_linear_combination();
    printf("\n=== ВСЕ ТЕСТЫ ЗАВЕРШЕНЫ ===\n");
}