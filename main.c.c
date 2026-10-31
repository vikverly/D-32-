/*
Студент: Черных Виктория Александровна
Группа: ПИ-1-1
ДЗ2
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 100

// Структура для хранения одной записи (id и балл)
typedef struct {
    int id;
    int score;
} Result;

int main(void) {
    Result data[MAX_RECORDS];
    int size = 0;

    // 1. ЗАГРУЗКА ДАННЫХ ИЗ ФАЙЛА results.txt
    FILE *f = fopen("results.txt", "r");
    if (f != NULL) {
        int id, score;
        // Читаем пары чисел до конца файла
        while (fscanf(f, "%d", &id) == 1) {
            if (fscanf(f, "%d", &score) != 1) {
                printf("Load error\n");
                fclose(f);
                return 0; // Ошибка: неполная пара
            }

            // Проверка диапазонов
            if (id < 1 || id > 9999 || score < 0 || score > 100 || size >= MAX_RECORDS) {
                printf("Load error\n");
                fclose(f);
                return 0;
            }

            // Проверка на уникальность ID
            for (int i = 0; i < size; i++) {
                if (data[i].id == id) {
                    printf("Load error\n");
                    fclose(f);
                    return 0;
                }
            }

            // Сохраняем в массив
            data[size].id = id;
            data[size].score = score;
            size++;
        }
        fclose(f);
    }
    // Если файла нет (size == 0), это допускается условием

    // 2. МЕНЮ ПРОГРАММЫ
    int cmd;
    while (1) {
        // Читаем команду от пользователя
        if (scanf("%d", &cmd) != 1) {
            printf("Input error\n");
            return 0; // Ошибка, если ввели буквы вместо цифры команды
        }

        // Команда 0: Выход
        if (cmd == 0) {
            break;
        } 
        
        // Команда 1: Показать все записи
        else if (cmd == 1) {
            if (size == 0) {
                printf("No data\n");
            } else {
                for (int i = 0; i < size; i++) {
                    printf("%d %d\n", data[i].id, data[i].score);
                }
            }
        } 
        
        // Команда 2: Статистика
        else if (cmd == 2) {
            if (size == 0) {
                printf("No data\n");
            } else {
                long long sum = 0;
                int passed = 0;
                int min_idx = 0;
                int max_idx = 0;

                for (int i = 0; i < size; i++) {
                    sum += data[i].score;
                    if (data[i].score >= 60) {
                        passed++;
                    }
                    if (data[i].score < data[min_idx].score) {
                        min_idx = i;
                    }
                    if (data[i].score > data[max_idx].score) {
                        max_idx = i;
                    }
                }

                double avg = (double)sum / size;
                printf("Count: %d\n", size);
                printf("Average: %.2f\n", avg);
                printf("Passed (score >= 60): %d\n", passed);
                printf("Min: %d %d\n", data[min_idx].id, data[min_idx].score);
                printf("Max: %d %d\n", data[max_idx].id, data[max_idx].score);
            }
        } 
        
        // Команда 3: Поиск по ID[cite: 3]
        else if (cmd == 3) {
            int search_id;
            if (scanf("%d", &search_id) != 1) {
                printf("Input error\n");
                return 0;
            }

            int found = 0;
            for (int i = 0; i < size; i++) {
                if (data[i].id == search_id) {
                    printf("%d %d\n", data[i].id, data[i].score);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("Not found\n");
            }
        } 
        
        //индивидуальный Вариант 7 
        else if (cmd == 4) {
            if (size == 0) {
                printf("No data\n");
            } else {
                // Сначала вычисляем сумму для поиска среднего
                long long sum = 0;
                for (int i = 0; i < size; i++) {
                    sum += data[i].score;
                }
                double avg = (double)sum / size; // без предварительного округления

                int matches = 0;
                for (int i = 0; i < size; i++) {
                    if ((double)data[i].score > avg) { // Строго выше среднего
                        printf("%d %d\n", data[i].id, data[i].score);
                        matches++;
                    }
                }
                if (matches == 0) {
                    printf("No matches\n");
                }
            }
        } 
        
        // Команда 5: Сохранение в report.txt
        else if (cmd == 5) {
            FILE *out = fopen("report.txt", "w");
            if (out == NULL) {
                printf("Save error\n");
            } else {
                for (int i = 0; i < size; i++) {
                    fprintf(out, "%d %d\n", data[i].id, data[i].score);
                }
                fclose(out);
                printf("Saved successfully\n");
            }
        } 
        
        // Неизвестная команда
        else {
            printf("Unknown command\n");
        }
    }

    return 0;
}