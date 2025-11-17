#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;
const int SPEED = 150;

bool gameOver;
int score;
int x, y;
int fruitX, fruitY;
vector<pair<int, int>> tail;
int tailLength;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

void Setup() {
    gameOver = false;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    tail.clear();
    tailLength = 0;
}

void Draw() {
    system("cls");
    
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0)
                cout << "#";
                
            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                bool printTail = false;
                for (int k = 0; k < tail.size(); k++) {
                    if (tail[k].first == j && tail[k].second == i) {
                        cout << "o";
                        printTail = true;
                    }
                }
                if (!printTail)
                    cout << " ";
            }

            if (j == WIDTH - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;
    
    cout << "Score: " << score << endl;
}

void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                if (dir != RIGHT) dir = LEFT;
                break;
            case 'd':
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'w':
                if (dir != DOWN) dir = UP;
                break;
            case 's':
                if (dir != UP) dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void Logic() {
    pair<int, int> prev = {x, y};
    pair<int, int> prev2;
    
    if (tail.size() > 0) {
        tail[0] = prev;
        for (int i = 1; i < tail.size(); i++) {
            prev2 = tail[i];
            tail[i] = prev;
            prev = prev2;
        }
    }

    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }

    if (x >= WIDTH) x = 0;
    else if (x < 0) x = WIDTH - 1;
    if (y >= HEIGHT) y = 0;
    else if (y < 0) y = HEIGHT - 1;

    for (int i = 0; i < tail.size(); i++) {
        if (tail[i].first == x && tail[i].second == y)
            gameOver = true;
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        tailLength++;
        tail.push_back({x, y});
    }
}

int main() {
    srand(time(0));
    Setup();
    
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(SPEED);
    }
    
    cout << "Game Over!" << endl;
    cout << "Final Score: " << score << endl;
    cout << "Press any key to exit...";
    _getch();
    
    return 0;
}
