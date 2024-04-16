#include <stdio.h>
#include <conio.h>
#include <windows.h>
// размер мира
#define WIDTH 40 
#define HEIGHT 20

#define PLAYER_CHAR 'P' // персонаж
#define BLOCK_CHAR '#' // блок
#define BLOCKONE_CHAR '-' // блок
#define BLOCKTWO_CHAR '*' // блок
#define EMPTY_CHAR '.' // земля

char world[HEIGHT][WIDTH];
int playerX = 0, playerY = 0;

void initializeWorld() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            world[y][x] = EMPTY_CHAR;
        }
    }
}

void placeBlock() {
    if (world[playerY][playerX] == EMPTY_CHAR) {
        world[playerY][playerX] = BLOCK_CHAR;
    }
}
void placeBlockOne() {
    if (world[playerY][playerX] == EMPTY_CHAR) {
        world[playerY][playerX] = BLOCKONE_CHAR;
    }
}
void placeBlockTwo() {
    if (world[playerY][playerX] == EMPTY_CHAR) {
        world[playerY][playerX] = BLOCKTWO_CHAR;
    }
}
void movePlayer(int dx, int dy) {
    int newPlayerX = playerX + dx;
    int newPlayerY = playerY + dy;

    if (newPlayerX >= 0 && newPlayerX < WIDTH && newPlayerY >= 0 && newPlayerY < HEIGHT) {
        playerX = newPlayerX;
        playerY = newPlayerY;
    }
}
// цвет и вывод на экран
void printWorld(char worldToPrint[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == playerX && y == playerY) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
                printf("%c ", PLAYER_CHAR);
            } else if (worldToPrint[y][x] == BLOCKONE_CHAR) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("%c ", BLOCKONE_CHAR);
			} else if (worldToPrint[y][x] == BLOCK_CHAR) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("%c ", BLOCK_CHAR);
			} else if (worldToPrint[y][x] == BLOCKTWO_CHAR) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
                printf("%c ", BLOCKTWO_CHAR);
            } else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
                printf("%c ", EMPTY_CHAR);
            }
        }
        printf("\n");
    }
}
// сохранение
void saveWorldToFile() {
    FILE *file = fopen("save_word.txt", "w");
    if (file == NULL) {
        printf("Ошибка открытия файла для записи.\n");
        return;
    }

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            fprintf(file, "%c", world[y][x]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}
void loadWorldFromFile() {
    FILE *file = fopen("save_word.txt", "r");
    if (file == NULL) {
        printf("Ошибка открытия файла для чтения.\n");
        return;
    }

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            fscanf(file, " %c", &world[y][x]); // Пробел перед %c для пропуска пробелов и переводов строк
        }
    }

    fclose(file);
}
// главный
int main() {
    SetConsoleOutputCP(CP_UTF8);
    initializeWorld();
    char input;
    while (1) {
        system("cls"); // Очистка экрана перед каждым обновлением мира
        printWorld(world);
		printf("Внимание! Меняйте раскладку на англискую!\n");
        printf("Управление(w/a/s/d-ходить, b/n-поставить блок,F1-сохранить мир(файл save_word.txt),F2-загрузить мир q-выйти): ");
        input = _getch();
		// настройка клавиатуры
        switch(input) {
            case 'w':
                movePlayer(0, -1);
                break;
            case 'a':
                movePlayer(-1, 0);
                break;
            case 's':
                movePlayer(0, 1);
                break;
            case 'd':
                movePlayer(1, 0);
                break;
            case 'b':
                placeBlock();
                break;
			case 'n':
				placeBlockOne();
				break;
			case 'm':
                placeBlockTwo();
                break;
			case 59:
				saveWorldToFile();
				break;
			case 60:
				loadWorldFromFile();
				break;
            case 'q':
                return 0;
        }

        Sleep(0); // Добавляем небольшую задержку
    }

    return 0;
}