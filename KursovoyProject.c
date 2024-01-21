#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int N = 4; // �� ��������� ������������� ������ �������� ���� 4x4

int grid[8][8]; // ������������ ������ �������� ����

// ������� ��� ����������� �������� ��������� �������� ����
void printGrid() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}
// ������� ��� ��������, �������� �� ������������ ����� ���������� ��� ���������� � ��������� ������
int isSafe(int row, int col, int num) {
    // ���������, ��� ����� num �� ����������� � ������� ������ � �������
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return 0;
        }
    }
    return 1;// ����� ���������
}

// ������� ��� ������� �������� ���� ������� "Backtracking"
int solveGrid(int row, int col) {
    if (row == N) {
        return 1;// ������� ���� ������
    }

    for (int num = 1; num <= N; num++) {
        if (isSafe(row, col, num)) {
            grid[row][col] = num;
            if (col + 1 < N) {
                if (solveGrid(row, col + 1)) {
                    return 1;// ������� �������
                }
            }
            else {
                if (solveGrid(row + 1, 0)) {
                    return 1;// ������� �������
                }
            }
            grid[row][col] = 0;// ������� ������, ���� ����� �� ��������
        }
    }

    return 0;
}
// ������� ��� ���������� ������ �� ���� � ����
void saveGridToFile() {
    FILE* file = fopen("game_data.txt", "w");
    if (file == NULL) {
        printf("������ �������� ����� ��� ������\n");
        return;
    }

    fprintf(file, "������ �������� ����: %d x %d\n", N, N);
    fprintf(file, "��������� �������� ����:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(file, "%d ", grid[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// ������� ����� ������� ���������� ������ � ���� � ������ �� ��������� ���������:

void createRandomGrid() { // ������� ��� �������� ���������� �������� ����
    srand(time(0));
    if (solveGrid(0, 0)) {
        printf("��������� ������� ���� �������:\n");
        printGrid();
        saveGridToFile(); // ��������� ������ �� ���� � ����
    }
    else {
        printf("�� ������� ������� ��������� ������� ����.\n");
    }
}

void fillManualGrid() { // ������� ��� ���������� �������� ���� �������
    printf("������� %d ����� ��� ���������� �������� ����:\n", N * N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    printf("������� ���� ��������� �������:\n");
    printGrid();
    saveGridToFile(); // ��������� ������ �� ���� � ����
}

// ������� ��� ��������� ������ ���������
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

void chooseDifficulty() { // ������� ��� ������ ������ ���������
    int difficulty;
    printf("�������� ������� ���������:\n");
    printf("1. ������\n");
    printf("2. �������\n");
    printf("3. �������\n");
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
        printf("������������ �����, ���������� ������� ��������� �� ���������.\n");
        setMediumDifficulty(); // ��������� ������� ������� ��������� �� ���������
    }

    printf("������� ��������� ������. ������ �������� ����: %d x %d\n", N, N);
    saveGridToFile(); // ��������� ������ �� ���� � ���� ����� ������ ������ ���������
}
int main() {
    setlocale(LC_ALL, "RUS");
    int choice; printf("����� ���������� � ����������� �������.\n");
    printf("���� ���� - ����� ���������� ������������� ����� �� ������� � ������������ � ���������� ���������.\n");
    printf("��� ������� ����:\n");
    printf("� ������ ������ � � ������ ������� ������ �������������� ��� ����� �� 1 �� N (��� N - ������ ������� �������� ����) ��� ����������.\n");
    printf("������ � ����������� ������� �� ����� ���������� ����� ���� � ������ �� ��������� ��� �����������.\n");


    do {
        printf("\n�������� ��������:\n");
        printf("1. ������� ��������� ������� ����\n");
        printf("2. ��������� ������� ���� �������\n");
        printf("3. ������� ������� ���������\n");
        printf("4. �����\n");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            createRandomGrid(); // �������� ���������� �������� ����
            break;
        case 2:
            fillManualGrid();// ���������� �������� ���� �������
            
            break;
        case 3:
            chooseDifficulty(); // ����� ������ ���������
            break;
        case 4:
            printf("�� ��������!\n"); // ��������� ���������
            break;
        default:
            printf("������������ �����, ���������� ��� ���.\n");
        }
    } while (choice != 4); // ��������� �� ������ "�����"

    return 0;
}