#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int N = 4; // По умолчанию устанавливаем размер игрового поля 4x4

int grid[8][8]; // Максимальный размер игрового поля

// Функция для отображения текущего состояния игрового поля
void printGrid() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}
// Функция для проверки, является ли определенное число безопасным для размещения в указанной ячейке
int isSafe(int row, int col, int num) {
    // Проверяем, что число num не встречается в текущей строке и столбце
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return 0;
        }
    }
    return 1;// Число безопасно
}

// Функция для решения игрового поля методом "Backtracking"
int solveGrid(int row, int col) {
    if (row == N) {
        return 1;// Игровое поле решено
    }

    for (int num = 1; num <= N; num++) {
        if (isSafe(row, col, num)) {
            grid[row][col] = num;
            if (col + 1 < N) {
                if (solveGrid(row, col + 1)) {
                    return 1;// Решение найдено
                }
            }
            else {
                if (solveGrid(row + 1, 0)) {
                    return 1;// Решение найдено
                }
            }
            grid[row][col] = 0;// Очистка ячейки, если число не подходит
        }
    }

    return 0;
}
// Функция для сохранения данных об игре в файл
void saveGridToFile() {
    FILE* file = fopen("game_data.txt", "w");
    if (file == NULL) {
        printf("Ошибка открытия файла для записи\n");
        return;
    }

    fprintf(file, "Размер игрового поля: %d x %d\n", N, N);
    fprintf(file, "Состояние игрового поля:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(file, "%d ", grid[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Добавим вызов функции сохранения данных в файл в каждом из сценариев программы:

void createRandomGrid() { // Функция для создания случайного игрового поля
    srand(time(0));
    if (solveGrid(0, 0)) {
        printf("Случайное игровое поле создано:\n");
        printGrid();
        saveGridToFile(); // Сохраняем данные об игре в файл
    }
    else {
        printf("Не удалось создать случайное игровое поле.\n");
    }
}

void fillManualGrid() { // Функция для заполнения игрового поля вручную
    printf("Введите %d чисел для заполнения игрового поля:\n", N * N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    printf("Игровое поле заполнено вручную:\n");
    printGrid();
    saveGridToFile(); // Сохраняем данные об игре в файл
}

// Функции для установки уровня сложности
void setEasyDifficulty() {
    N = 4;
    createRandomGrid();
}

void setMediumDifficulty() {
    N = 6;
    createRandomGrid();
}

void setHardDifficulty() {
    N = 8;
    createRandomGrid();
}

void chooseDifficulty() { // Функция для выбора уровня сложности
    int difficulty;
    printf("Выберите уровень сложности:\n");
    printf("1. Легкий\n");
    printf("2. Средний\n");
    printf("3. Сложный\n");
    scanf("%d", &difficulty);

    switch (difficulty) {
    case 1:
        setEasyDifficulty();
        break;
    case 2:
        setMediumDifficulty();
        break;
    case 3:
        setHardDifficulty();
        break;
    default:
        printf("Некорректный выбор, установлен уровень сложности по умолчанию.\n");
        setMediumDifficulty(); // Установим средний уровень сложности по умолчанию
    }

    printf("Уровень сложности выбран. Размер игрового поля: %d x %d\n", N, N);
    saveGridToFile(); // Сохраняем данные об игре в файл после выбора уровня сложности
}
int main() {
    setlocale(LC_ALL, "RUS");
    int choice; printf("Добро пожаловать в головоломку Куротто.\n");
    printf("Цель игры - найти правильное распределение чисел по ячейкам в соответствии с указанными правилами.\n");
    printf("Вот правила игры:\n");
    printf("В каждой строке и в каждом столбце должны присутствовать все числа от 1 до N (где N - размер стороны игрового поля) без повторений.\n");
    printf("Ячейки с одинаковыми числами не могут находиться рядом друг с другом по вертикали или горизонтали.\n");


    do {
        printf("\nВыберите действие:\n");
        printf("1. Создать случайное игровое поле\n");
        printf("2. Заполнить игровое поле вручную\n");
        printf("3. Выбрать уровень сложности\n");
        printf("4. Выйти\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            createRandomGrid(); // Создание случайного игрового поля
            break;
        case 2:
            fillManualGrid();// Заполнение игрового поля вручную
            
            break;
        case 3:
            chooseDifficulty(); // Выбор уровня сложности
            break;
        case 4:
            printf("До свидания!\n"); // Завершаем программу
            break;
        default:
            printf("Некорректный выбор, попробуйте еще раз.\n");
        }
    } while (choice != 4); // Повторяем до выбора "Выйти"

    return 0;
}