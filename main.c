#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "queue.h"
#include "sorting.h"
#include "file.h"
#include "benchmark.h"

int* input_array_dynamic(int* size) {
    printf("Введите элементы массива через пробел (для завершения нажмите Enter):\n");
    printf("> ");
    
    char line[1024];
    if (fgets(line, sizeof(line), stdin) == NULL) {
        return NULL;
    }
    
    // Удаляем символ новой строки
    line[strcspn(line, "\n")] = 0;
    
    if (strlen(line) == 0) {
        printf("Не введено ни одного числа!\n");
        return NULL;
    }
    
    // Проверка на наличие букв или недопустимых символов
    for (int i = 0; line[i] != '\0'; i++) {
        // Разрешаем: цифры, пробелы, табуляции, знаки + и - (для отрицательных чисел)
        if (!isdigit(line[i]) && 
            line[i] != ' ' && 
            line[i] != '\t' && 
            line[i] != '+' && 
            line[i] != '-' &&
            line[i] != '\0') {
            
            // Если это знак + или -, проверяем следующий символ
            if ((line[i] == '+' || line[i] == '-') && 
                i + 1 < strlen(line) && 
                isdigit(line[i + 1])) {
                // Это допустимо: знак перед числом
                continue;
            }
            
            printf("Ошибка: обнаружен недопустимый символ в \n");
            printf("Вводите только целые числа и пробелы!\n");
            return NULL;
        }
    }
    
    // Подсчитываем количество чисел
    int count = 0;
    char* ptr = line;
    while (*ptr) {
        // Пропускаем пробелы
        while (*ptr && isspace(*ptr)) ptr++;
        
        // Если нашли число
        if (*ptr && !isspace(*ptr)) {
            // Проверяем, что это действительно начало числа
            if (*ptr == '+' || *ptr == '-' || isdigit(*ptr)) {
                count++;
            }
            // Пропускаем число
            while (*ptr && !isspace(*ptr)) ptr++;
        }
    }
    
    if (count == 0) {
        printf("Не найдено чисел во вводе!\n");
        return NULL;
    }
    
    // Выделяем память под массив
    int* arr = (int*)malloc(count * sizeof(int));
    if (arr == NULL) {
        printf("Ошибка выделения памяти!\n");
        return NULL;
    }
    
    // Считываем числа с дополнительной проверкой
    ptr = line;
    int index = 0;
    
    while (*ptr && index < count) {
        // Пропускаем пробелы
        while (*ptr && isspace(*ptr)) ptr++;
        
        if (*ptr) {
            // Считываем одно число
            int value;
            int chars_read;
            
            // Пробуем прочитать число
            if (sscanf(ptr, "%d%n", &value, &chars_read) == 1) {
                // Проверяем, что прочитали все символы числа
                char temp[20];
                sprintf(temp, "%d", value);
                int expected_chars = strlen(temp);
                
                // Учитываем возможный знак
                if (ptr[0] == '+' || ptr[0] == '-') {
                    expected_chars++;
                }
                
                // Если прочитали меньше символов, чем ожидалось, значит была ошибка
                if (chars_read < expected_chars) {
                    printf("Ошибка: в позиции %ld обнаружен недопустимый символ в числе\n", 
                           (ptr - line) + chars_read + 1);
                    free(arr);
                    return NULL;
                }
                
                arr[index] = value;
                index++;
                ptr += chars_read;
            } else {
                // Если не удалось прочитать число
                printf("Ошибка: невозможно прочитать число в позиции %ld\n", ptr - line + 1);
                free(arr);
                return NULL;
            }
        }
    }
    
    *size = count;
    printf("✅ Успешно считано %d чисел\n", count);
    return arr;
}

void print_array(int arr[], int size) {
    if (size <= 20) {
        // Полный вывод для маленьких массивов
        printf("[");
        for (int i = 0; i < size; i++) {
            printf("%d", arr[i]);
            if (i < size - 1) printf(", ");
        }
        printf("]\n");
    } else {
        // Сокращенный вывод для больших массивов
        printf("[");
        for (int i = 0; i < 5; i++) {
            printf("%d, ", arr[i]);
        }
        printf("..., ");
        for (int i = size - 5; i < size; i++) {
            printf("%d", arr[i]);
            if (i < size - 1) printf(", ");
        }
        printf("]\n");
    }
}

void print_time(double time_ms, const char* sort_name) {
    if (time_ms < 1.0) {
        printf("%s: %.3f мс (%.0f мкс)\n", sort_name, time_ms, time_ms * 1000);
    } else if (time_ms < 1000.0) {
        printf("%s: %.3f мс\n", sort_name, time_ms);
    } else {
        printf("%s: %.3f мс (%.3f с)\n", sort_name, time_ms, time_ms / 1000.0);
    }
}

void show_menu() {
    printf("\n═══════════════════════════════════════════════════════════\n");
    printf("                МЕНЮ ПРОГРАММЫ СОРТИРОВКИ                \n");
    printf("═══════════════════════════════════════════════════════════\n");
    printf("1. Ввести массив вручную и отсортировать\n");
    printf("2. Запустить тестирование на тестовых файлах\n");
    printf("3. Выйти из программы\n");
    printf("\nВыберите действие (1-3): ");
}

// Функция для запуска Python-скрипта построения графика
void show_graph() {
    printf("\n📊 Запуск построения графика...\n");
    
    // Проверяем наличие файла results.txt
    FILE* results_file = fopen("results.txt", "r");
    if (results_file == NULL) {
        printf("⚠️  Файл results.txt не найден.\n");
        printf("   Сначала запустите тестирование для создания файла с результатами.\n");
        return;
    }
    fclose(results_file);
    
    // Проверяем наличие файла graph.py
    FILE* graph_script = fopen("graph.py", "r");
    if (graph_script == NULL) {
        printf("⚠️  Файл graph.py не найден в текущей директории.\n");
        printf("   Убедитесь, что graph.py находится в той же папке, что и эта программа.\n");
        return;
    }
    fclose(graph_script);
    
    printf("✅ Запускаю Python-скрипт для построения графика...\n");
    printf("   (Откроется новое окно с графиком)\n\n");
    
    // Запускаем Python-скрипт
    int result = system("python3 graph.py");
    
    if (result == 0) {
        printf("\n✅ График успешно построен и сохранен как graph.png\n");
        printf("   Результаты также сохранены в файле results.txt\n");
    } else {
        printf("\n⚠️  Не удалось построить график.\n");
        printf("   Убедитесь, что установлен Python и библиотека matplotlib.\n");
        printf("   Для установки matplotlib выполните: pip install matplotlib\n");
    }
}

int main() {
    int choice;
    
    printf("═══════════════════════════════════════════════════════════\n");
    printf("                ПРОГРАММА СОРТИРОВКИ МАССИВОВ             \n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    while (1) {
        show_menu();
        
        if (scanf("%d", &choice) != 1) {
            // Очистка буфера ввода
            while (getchar() != '\n');
            printf("Неверный ввод. Введите число от 1 до 3.\n");
            continue;
        }
        
        // Очистка буфера после scanf
        while (getchar() != '\n');
        
        if (choice == 1) {
            // Режим 1: ручной ввод
            printf("\n═══════════════════════════════════════════════════════════\n");
            printf("               РЕЖИМ 1: РУЧНОЙ ВВОД МАССИВА              \n");
            printf("═══════════════════════════════════════════════════════════\n\n");
            
            int size;
            int* arr = input_array_dynamic(&size);
            
            if (arr == NULL) {
                printf("Пожалуйста, попробуйте снова.\n");
                continue;
            }
            
            printf("\nИсходный массив: ");
            print_array(arr, size);
            
            // Создаем очередь из массива
            Queue* p = array_to_queue(arr, size);
            printf("Очередь из массива: ");
            print_queue(p);
            printf("\n");
            
            // Копии массивов для сортировок
            int* arr_selection = (int*)malloc(size * sizeof(int));
            int* arr_quick = (int*)malloc(size * sizeof(int));
            
            if (arr_selection == NULL || arr_quick == NULL) {
                printf("Ошибка выделения памяти!\n");
                free(arr);
                if (arr_selection) free(arr_selection);
                if (arr_quick) free(arr_quick);
                free_queue(p);
                continue;
            }
            
            memcpy(arr_selection, arr, size * sizeof(int));
            memcpy(arr_quick, arr, size * sizeof(int));
            
            // Измерение времени сортировки выбором
            clock_t start = clock();
            selection_sort(arr_selection, size);
            clock_t end = clock();
            double selection_time = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
            
            // Измерение времени быстрой сортировки
            start = clock();
            quick_sort(arr_quick, 0, size - 1);
            end = clock();
            double quick_time = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
            
            printf("═╦═══════════════════════════════════════\n");
            printf(" ║ 📊 РЕЗУЛЬТАТЫ СОРТИРОВКИ:\n");
            printf("═╩═══════════════════════════════════════\n");
            
            printf("\n⏱️  ВРЕМЯ ВЫПОЛНЕНИЯ:\n");
            printf("─────────────────────────────────────\n");
            print_time(selection_time, "Сортировка выбором");
            print_time(quick_time, "Быстрая сортировка");
            
            if (selection_time > 0 && quick_time > 0) {
                double speedup = selection_time / quick_time;
                printf("─────────────────────────────────────\n");
                printf("📈 Быстрая сортировка быстрее в %.2f раз\n", speedup);
            }
            
            printf("\n📋 ОТСОРТИРОВАННЫЕ МАССИВЫ:\n");
            printf("─────────────────────────────────────\n");
            printf("Сортировка выбором:   ");
            print_array(arr_selection, size);
            
            printf("Быстрая сортировка:   ");
            print_array(arr_quick, size);
            
            // Проверка корректности сортировки
            int correct = 1;
            for (int i = 0; i < size - 1; i++) {
                if (arr_selection[i] > arr_selection[i + 1]) {
                    correct = 0;
                    break;
                }
            }
            
            printf("\n✅ ");
            if (correct) {
                printf("Массивы отсортированы корректно (проверено)");
            } else {
                printf("Обнаружена ошибка в сортировке!");
            }
            printf("\n");
            
            // Сохранение в файлы
            write_array_to_file(arr, size, "orig.txt");
            write_array_to_file(arr_selection, size, "sorted_selection.txt");
            write_array_to_file(arr_quick, size, "sorted_quick.txt");
            
            printf("\n💾 ФАЙЛЫ СОХРАНЕНЫ:\n");
            printf("─────────────────────────────────────\n");
            printf("  • Исходный массив:           orig.txt\n");
            printf("  • Сортировка выбором:        sorted_selection.txt\n");
            printf("  • Быстрая сортировка:        sorted_quick.txt\n");
            
            // Освобождение памяти
            free(arr);
            free(arr_selection);
            free(arr_quick);
            free_queue(p);
            
            printf("\nНажмите Enter для возврата в меню...");
            getchar();
            
        } else if (choice == 2) {
            // Режим 2: тестирование на тестовых файлах
            printf("\n═══════════════════════════════════════════════════════════\n");
            printf("          РЕЖИМ 2: ТЕСТИРОВАНИЕ НА ТЕСТОВЫХ ФАЙЛАХ        \n");
            printf("═══════════════════════════════════════════════════════════\n\n");
            
            // Проверяем существование тестовых файлов
            printf("Проверка тестовых файлов...\n");
            int test_sizes[] = {100, 500, 1000, 5000, 10000};
            int num_tests = sizeof(test_sizes) / sizeof(test_sizes[0]);
            
            int all_files_exist = 1;
            for (int i = 0; i < num_tests; i++) {
                char filename[50];
                sprintf(filename, "test_data%d.txt", test_sizes[i]);
                FILE* f = fopen(filename, "r");
                if (f == NULL) {
                    printf("❌ Файл %s не найден!\n", filename);
                    all_files_exist = 0;
                } else {
                    fclose(f);
                    printf("✅ Файл %s найден\n", filename);
                }
            }
            
            if (!all_files_exist) {
                printf("\n⚠️  Не все тестовые файлы найдены.\n");
                printf("   Для тестирования создайте файлы: test_data100.txt, test_data500.txt и т.д.\n");
                printf("   Либо выберите режим 1 для ручного ввода.\n");
                
                printf("\nНажмите Enter для возврата в меню...");
                getchar();
                continue;
            }
            
            printf("\n🚀 Запуск тестирования производительности...\n\n");
            
            // Запускаем benchmark
            benchmark_sorting();
            
            // После тестирования предлагаем показать график
            printf("\n═══════════════════════════════════════════════════════════\n");
            printf("          ПОКАЗАТЬ ГРАФИК РЕЗУЛЬТАТОВ?                   \n");
            printf("═══════════════════════════════════════════════════════════\n");
            printf("Хотите увидеть график сравнения производительности?\n");
            printf("1. Да, показать график\n");
            printf("2. Нет, вернуться в меню\n");
            printf("\nВыберите действие (1-2): ");
            
            int graph_choice;
            if (scanf("%d", &graph_choice) != 1) {
                while (getchar() != '\n');
                printf("Неверный ввод.\n");
            } else {
                while (getchar() != '\n'); // Очистка буфера
                
                if (graph_choice == 1) {
                    show_graph();
                }
            }
            
            printf("\nНажмите Enter для возврата в меню...");
            getchar();
            
        } else if (choice == 3) {
            // Режим 3: выход
            printf("\n═══════════════════════════════════════════════════════════\n");
            printf("               ВЫХОД ИЗ ПРОГРАММЫ                       \n");
            printf("═══════════════════════════════════════════════════════════\n\n");
            printf("Спасибо за использование программы! До свидания!\n");
            break;
            
        } else {
            printf("Неверный выбор. Пожалуйста, введите число от 1 до 3.\n");
        }
    }
    
    return 0;
}