#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <math.h>
 
// Объявление функций
void count_statistic( int array[12],  int rus_points[],  int math_points[],  int phis_points[],  int inf_points[],  int benefit[],  int stud_count,  int error_of_input);
int read_repeat();
int read_statistic(FILE* file,  int rus[],  int math[],  int phis[],  int inf[],  int benefit[], char name_of_sub[],  int* error_of_input,  int* stud_count);
 
int main(){
    setlocale(LC_ALL,"Rus");
 
    // Объявление переменных для данных студентов
    int rus[50];
    int math[50];
    int phis[50];
    int inf[50];
    int benefit[50];
    
    FILE* file;
    file = fopen("list.txt","r"); // Исправляем путь
    
    if(file == NULL) {
        file = fopen("../list.txt","r"); // Пробуем альтернативный путь
        if(file == NULL) {
            printf("Ошибка открытия файла!\n");
            return 1;
        }
    }
 
    // Объявление массива для статистики
    int answers[12];
    char name_of_sub[13];
 
    int error_of_input = 0;
    int stud_count = 0;
    int num_of_sub = 0;
 
    while(1)
    {
        num_of_sub = 0;
        
        // Заголовок таблицы
        printf("| Направление |Средний балл без льгот|Средний балл с льготами|Минимальный балл без льгот|Максимальный балл без льгот|Количество льготников(БВ,ЦП,ОП)|Баллы за экзамены(М,Р,И,Ф)|Ошибки|Студенты|\n");
        
        // Перемотка файла в начало
        rewind(file);
        
        while(1)
        {
            memset(name_of_sub, 0, sizeof(name_of_sub));
            for(int i = 0; i < 12; i++) answers[i] = 0;
            answers[3] = 300; // Инициализация минимального балла
 
            // Читаем данные для следующего направления
            int result = read_statistic(file, rus, math, phis, inf, benefit, name_of_sub, &error_of_input, &stud_count);
            if(result == 0) break; // Конец файла
            if(result == -1) continue; // Ошибка чтения
 
            printf("|%13.13s|", name_of_sub);
            count_statistic(answers, rus, math, phis, inf, benefit, stud_count, error_of_input);
            printf("%23d|%22d|%24d|%25d|%25d,%2d,%2d|%24d,%2d,%2d,%2d|%6d|%9d|\n",
                   answers[1], answers[2], answers[3], answers[4], answers[5],
                   answers[6], answers[7], answers[8], answers[9], answers[10],
                   answers[11], error_of_input, stud_count);
            
            num_of_sub++;
        }
        
        printf("Всего найдено %d направлений\n", num_of_sub);
        fclose(file);
        
        if(read_repeat() == 0) break;
        
        // Открываем файл заново для повторения
        file = fopen("list.txt", "r");
        if(file == NULL) {
            printf("Ошибка открытия файла!\n");
            break;
        }
    }
    
    if(file != NULL) fclose(file);
    return 0;
}
 
// Реализация функции чтения статистики
int read_statistic(FILE* file,  int rus[],  int math[], int phis[],  int inf[], int benefit[], char name_of_sub[], int* error_of_input,  int* stud_count) {
    char buffer[256];
    *stud_count = 0;
    *error_of_input = 0;
 
    // Читаем название направления
    if(fgets(buffer, sizeof(buffer), file) == NULL) {
        return 0; // Конец файла
    }
 
    // Удаляем символ новой строки
    buffer[strcspn(buffer, "\n")] = 0;
    
    // Проверяем, что это название направления (заканчивается на точку)
    if(buffer[strlen(buffer)-1] != '.') {
        // Это не название направления, пропускаем
        return -1;
    }
 
    // Копируем название без точки
    strncpy(name_of_sub, buffer, strlen(buffer)-1);
    name_of_sub[strlen(buffer)-1] = '\0';
 
    // Читаем данные студентов
    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        // Проверяем, не начинается ли следующее направление
        if(buffer[strlen(buffer)-1] == '.') {
            // Возвращаемся на одну строку назад
            fseek(file, -strlen(buffer), SEEK_CUR);
            break;
        }
 
        // Парсим данные студента
        char name[100];
        int r, m, p, i, b;
        
        // Упрощенный парсинг - адаптируйте под ваш формат
        int parsed = sscanf(buffer, "%[^,], %d, %d, %d, %d, %d", 
                           name, &r, &m, &p, &i, &b);
        
        if(parsed >= 5) { // Минимум 5 полей
            rus[*stud_count] = r;
            math[*stud_count] = m;
            phis[*stud_count] = p;
            inf[*stud_count] = i;
            benefit[*stud_count] = (parsed == 6) ? b : 0;
            
            (*stud_count)++;
            
            if(*stud_count >= 50) break; // Не превышаем размер массива
        } else {
            (*error_of_input)++;
        }
    }
 
    return 1; // Успешное чтение
}
 
// Исправленная функция подсчета статистики
void count_statistic(int array[12],int rus_points[], int math_points[], int phis_points[],int inf_points[],int benefit[], int stud_count, int error_of_input){
    if(stud_count == 0) return;
 
    // Инициализация
    array[1] = 0; // Средний без льгот
    array[2] = 0; // Средний с льготами
    array[3] = 300; // Минимальный (начинаем с максимально возможного)
    array[4] = 0; // Максимальный
    array[5] = 0; // БВ
    array[6] = 0; // ЦП
    array[7] = 0; // ОП
    array[8] = 0; // Математика
    array[9] = 0; // Русский
    array[10] = 0; // Информатика
    array[11] = 0; // Физика
 
    for(int i = 0; i < stud_count; i++){
        int total_without_benefit = rus_points[i] + math_points[i] + fmax(inf_points[i], phis_points[i]);
        int total_with_benefit;
 
        if(benefit[i] == 4){
            total_with_benefit = 300; // Особый случай льготы
        } else {
            total_with_benefit = total_without_benefit;
        }
 
        array[1] += total_without_benefit;
        array[2] += total_with_benefit;
 
        if(total_without_benefit < array[3]){
            array[3] = total_without_benefit;
        }
        if(total_without_benefit > array[4]){
            array[4] = total_without_benefit;
        }
 
        // Подсчет льготников
        if(benefit[i] == 1) array[5]++; // БВ
        if(benefit[i] == 2) array[6]++; // ЦП
        if(benefit[i] == 3) array[7]++; // ОП
 
        // Суммируем баллы по предметам
        array[8] += math_points[i];
        array[9] += rus_points[i];
        array[10] += inf_points[i];
        array[11] += phis_points[i];
    }
 
    // Вычисление средних значений
    array[1] /= stud_count;
    array[2] /= stud_count;
    array[8] /= stud_count;
    array[9] /= stud_count;
    array[10] /= stud_count;
    array[11] /= stud_count;
}
 
int read_repeat() {
    printf("Повторить? (1 - да, 0 - нет): ");
    int answer;
    scanf("%d", &answer);
    return answer;
}