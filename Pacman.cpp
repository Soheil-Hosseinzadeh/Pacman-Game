// S.H is the Owner
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include <unistd.h>
#include "movements.h"
using namespace std;

long long int max_score = 0;

void initializing_board(char a[row][column])
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            a[i][j] = ' ';
        }
    }
    constants(a);
    initializing_board_ambient(a);
    random_corners(a);
    random_areas(a);
    random_middle_shapes(a);
    middle_updown_shape(a, 4, column / 2 - 5);
    middle_updown_shape(a, row / 2 + 3, column / 2 - 5);
    ghosts_home(a);
    pacman_foods(a);
}

void print_board(char a[row][column])
{
    int i, j;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            if (a[i][j] == '.')
            {
                SetConsoleTextAttribute(hConsole, 10);
                cout << a[i][j] << " ";
            }
            else if (i == pacman_row && j == pacman_column)
            {
                SetConsoleTextAttribute(hConsole, 6);
                cout << a[i][j] << " ";
            }
            else if (i == red_ghost_row && j == red_ghost_column)
            {
                SetConsoleTextAttribute(hConsole, 12);
                cout << a[i][j] << " ";
            }
            else if (i == pink_ghost_row && j == pink_ghost_column)
            {
                SetConsoleTextAttribute(hConsole, 13);
                cout << a[i][j] << " ";
            }
            else if (i == blue_ghost_row && j == blue_ghost_column)
            {
                SetConsoleTextAttribute(hConsole, 11);
                cout << a[i][j] << " ";
            }
            else if (i == yellow_ghost_row && j == yellow_ghost_column)
            {
                SetConsoleTextAttribute(hConsole, 14);
                cout << a[i][j] << " ";
            }
            else if ((i == row / 2 - 1 || i == row / 2 + 1 || i == row / 2) && j > column / 2 - 4 && j < column / 2 + 3)
            {
                SetConsoleTextAttribute(hConsole, 10);
                cout << a[i][j] << " ";
            }
            else if (a[i][j] == '$')
            {
                SetConsoleTextAttribute(hConsole, 10);
                cout << a[i][j] << " ";
            }
            else if (a[i][j] == '#')
            {
                SetConsoleTextAttribute(hConsole, 136);
                cout << a[i][j] << " ";
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 15);
                cout << a[i][j] << " ";
            }
        }
        cout << endl;
    }
    SetConsoleTextAttribute(hConsole, 15);
}

void resetMap()
{
}

void max_score_calculater(char a[row][column])
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            if (a[i][j] == '.')
            {
                max_score += 10;
            }
        }
    }
    max_score += 250;
}

void gameStop(char button)
{
    if (button == 27) // Esc button
    {
        while (true)
        {
            button = getch();
            if (button == 27)
            {
                break;
            }
        }
    }
}

void levelReceiver(char &level)
{
    system("cls");
    cout << "Select the difficulty of the game" << endl
         << "Press 1 as Easy" << endl
         << "Press 2 as Medium" << endl
         << "Press 3 as Hard" << endl
         << "Play the game in CMD of windows";
    level = getch();
    while (!(level >= '1' && level <= '3'))
    {
        cout << "InValid input" << endl;
        level = getch();
    }
    system("cls");
}

bool gameOver(char a[row][column], bool &isLosing, int &hearts, bool &firstTime)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    hearts--;
    set_cursor(0, row + 1);
    SetConsoleTextAttribute(hConsole, 12);
    cout << hearts;
    if (hearts == 0)
    {
        return true;
    }
    isFoodDoornow(isFoodRed, isAngerFoodRed, isDoorRed, a, red_ghost_row, red_ghost_column);
    isFoodDoornow(isFoodPink, isAngerFoodPink, isDoorPink, a, pink_ghost_row, pink_ghost_column);
    isFoodDoornow(isFoodBlue, isAngerFoodBlue, isDoorBlue, a, blue_ghost_row, blue_ghost_column);
    isFoodDoornow(isFoodYellow, isAngerFoodYellow, isDoorYellow, a, yellow_ghost_row, yellow_ghost_column);

    isFoodRed = false, isAngerFoodRed = false, isDoorRed = false;
    isFoodPink = false, isAngerFoodPink = false, isDoorPink = false;
    isFoodBlue = false, isAngerFoodBlue = false, isDoorBlue = false;
    isFoodYellow = false, isAngerFoodYellow = false, isDoorYellow = false;

    pacman_row = row - 2;
    pacman_column = column - 2;
    red_ghost_row = row / 2;
    red_ghost_column = column / 2 - 2;
    pink_ghost_row = row / 2;
    pink_ghost_column = column / 2 - 1;
    blue_ghost_row = row / 2;
    blue_ghost_column = column / 2;
    yellow_ghost_row = row / 2;
    yellow_ghost_column = column / 2 + 1;
    pacman_position(a, pacman_row, pacman_column);
    ghostPosition(a, red_ghost_row, red_ghost_column);
    ghostPosition(a, pink_ghost_row, pink_ghost_column);
    ghostPosition(a, blue_ghost_row, blue_ghost_column);
    ghostPosition(a, yellow_ghost_row, yellow_ghost_column);
    ghostMoves = 0;
    scaryTimeStart = 0;
    firstTime = true;
    isLosing = false;
    set_cursor(0, 0);
    print_board(a);
    return false;
}

bool winning()
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            if (foods[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char level;
    levelReceiver(level);
    char board[row][column];
    char button = 'S';
    initializing_board(board);
    pacman_position(board, pacman_row, pacman_column);
    ghostPosition(board, red_ghost_row, red_ghost_column);
    ghostPosition(board, pink_ghost_row, pink_ghost_column);
    ghostPosition(board, blue_ghost_row, blue_ghost_column);
    ghostPosition(board, yellow_ghost_row, yellow_ghost_column);
    max_score_calculater(board);
    print_board(board);
    SetConsoleTextAttribute(hConsole, 15);
    set_cursor(0, row + 2);
    cout << "Press Esc to stop or resume the game";
    set_cursor(2 * column - 17, row);
    cout << "angry moves : 0";
    set_cursor(0, row);
    cout << "Score : " << score;
    bool isLosing = false;
    bool firstTime = true;
    int hearts = 3;
    bool angerFood = false;
    set_cursor(0, row + 1);
    SetConsoleTextAttribute(hConsole, 12);
    cout << hearts;
    SetConsoleTextAttribute(hConsole, 15);
    cout << " hearts left";
    srand(time(NULL));
    while (true)
    {
        if (firstTime)
        {
            button = getch();
            firstTime = false;
        }
        if (kbhit() && !firstTime)
        {
            button = getch();
            if (button == 27)
            {
                gameStop(button);
            }
        }
        pacman_movement(board, button, isLosing, angerFood);
        if (isLosing)
        {
            usleep(100000 * 10);
            if (gameOver(board, isLosing, hearts, firstTime))
            {
                break;
            }
            else
            {
                continue;
            }
        }
        if (winning())
        {
            break;
        }
        ghostsMovement(board, isLosing, level, angerFood);
        ghostMoves++;
        if (angerFood)
        {
            set_cursor(2 * column - 3, row);
            cout << "  ";
            set_cursor(2 * column - 3, row);
            SetConsoleTextAttribute(hConsole, 12);
            cout << 33 - (ghostMoves - scaryTimeStart);
        }
        if (isLosing)
        {
            usleep(100000 * 10);
            if (gameOver(board, isLosing, hearts, firstTime))
            {
                break;
            }
            else
            {
                continue;
            }
        }
        set_cursor(8, row);
        SetConsoleTextAttribute(hConsole, 14);
        cout << score;
        usleep(100000 * 2.5);
    }
    if (isLosing)
    {
        set_cursor(14, row);
        SetConsoleTextAttribute(hConsole, 12);
        cout << "Game Over";
    }
    else
    {
        set_cursor(14, row);
        SetConsoleTextAttribute(hConsole, 10);
        cout << "YOU WON";
    }
    set_cursor(0, row + 3);
    SetConsoleTextAttribute(hConsole, 9);
    cout << "Press any Key to exit";
    getch();
    return 0;
}