// Snake Game in C
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 
#include <windows.h> 
#define WIDTH 40
#define HEIGHT 20
#define MAX_LENGTH 100
int gameOver;
int score;
int x, y; //Snake coordinates
int fruitX, fruitY; // Fruit coordinates
int tailX[MAX_LENGTH], tailY[MAX_LENGTH]; // Snake tail coordinates
int nTail; // Length of the tail
char direction; // Snake direction: 'w', 'a', 's', 'd'
// Functions
void setup();
void draw();
void input();
void logic();

void setup() {
    gameOver = 0;
    direction = 'd';
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
}

void draw() {
    system("cls");
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    // Draw the game board
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) // Left border
                printf("#");

            if (i == y && j == x)
                printf("O"); // Snake head
            else if (i == fruitY && j == fruitX)
                printf("F"); // Fruit
            else {
                int print = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("o"); // Snake tail
                        print = 1;
                    }
                }
                if (!print)
                    printf(" ");
            }

            if (j == WIDTH - 1) // Right border
                printf("#");
        }
        printf("\n");
    }

    // Draw bottom border
    for (int i = 0; i < WIDTH + 2; i++)
        printf("#");
    printf("\n");

    printf("Score: %d\n", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w':
                direction = 'w';
                break;
            case 'a':
                direction = 'a';
                break;
            case 's':
                direction = 's';
                break;
            case 'd':
                direction = 'd';
                break;
            case 'x':
                gameOver = 1;
                break;
        }
    }
}

void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (direction) {
        case 'w':
            y--;
            break;
        case 'a':
            x--;
            break;
        case 's':
            y++;
            break;
        case 'd':
            x++;
            break;
    }

    // Check collision with walls
    if (x >= WIDTH || x < 0 || y >= HEIGHT || y < 0)
        gameOver = 1;

    // Check collision with tail
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;
    }

    // Check if fruit is eaten
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;
    }
}

int main() {
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(50); 
    }

    printf("Game Over! Your Score: %d\n", score);
    getch();
    return 0;
}
