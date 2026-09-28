#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <set>
#include "Astar.h"
using namespace std;
int score = 0;
int pacman_row = row - 2, pacman_column = column - 2;
int red_ghost_row = row / 2, red_ghost_column = column / 2 - 2;
int pink_ghost_row = row / 2, pink_ghost_column = column / 2 - 1;
int blue_ghost_row = row / 2, blue_ghost_column = column / 2;
int yellow_ghost_row = row / 2, yellow_ghost_column = column / 2 + 1;
unsigned long long int scaryTimeStart; // Wild Pacman
unsigned long long int homeTimeStartRed;
unsigned long long int homeTimeStartPink;
unsigned long long int homeTimeStartBlue;
unsigned long long int homeTimeStartYellow;
unsigned long long int ghostMoves = 0;

bool isFoodRed = false, isAngerFoodRed = false, isDoorRed = false;
bool isFoodPink = false, isAngerFoodPink = false, isDoorPink = false;
bool isFoodBlue = false, isAngerFoodBlue = false, isDoorBlue = false;
bool isFoodYellow = false, isAngerFoodYellow = false, isDoorYellow = false;

bool redEaten = false, pinkEaten = false, blueEaten = false, yellowEaten = false;

void set_cursor(int x, int y)
{
    HANDLE handle;
    COORD coordinates;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(handle, coordinates);
}

void ghostPosition(char a[row][column], int ghostRow, int ghostCol)
{
    a[ghostRow][ghostCol] = 'G';
}

void pacman_position(char a[row][column], int pacman_row, int pacman_column)
{
    a[pacman_row][pacman_column] = 'O';
}

bool losing()
{
    pair<int, int> pacman, redGhost, pinkGhost, blueGhost, yellowGhost;
    pacman = make_pair(pacman_row, pacman_column);
    redGhost = make_pair(red_ghost_row, red_ghost_column);
    pinkGhost = make_pair(pink_ghost_row, pink_ghost_column);
    blueGhost = make_pair(blue_ghost_row, blue_ghost_column);
    yellowGhost = make_pair(yellow_ghost_row, yellow_ghost_column);
    if (pacman == redGhost || pacman == pinkGhost || pacman == blueGhost || pacman == yellowGhost)
    {
        return 1;
    }
    return 0;
}

void scorePlus(char a[row][column], int i, int j, bool &angerFood)
{
    if (a[i][j] == '.')
    {
        score += 10;
    }
    else if (a[i][j] == '$')
    {
        angerFood = true;
        scaryTimeStart = ghostMoves;
        score += 50;
    }
}

void scaryModeTimer(bool &angerFood)
{
    if (ghostMoves - scaryTimeStart == 33)
    {
        angerFood = false;
        redEaten = false, pinkEaten = false, blueEaten = false, yellowEaten = false;
    }
}

void homeStayingTimer()
{
    if (redEaten)
    {
        if (ghostMoves - homeTimeStartRed == 20)
        {
            redEaten = false;
        }
    }
    if (pinkEaten)
    {
        if (ghostMoves - homeTimeStartPink == 20)
        {
            pinkEaten = false;
        }
    }
    if (blueEaten)
    {
        if (ghostMoves - homeTimeStartBlue == 20)
        {
            blueEaten = false;
        }
    }
    if (yellowEaten)
    {
        if (ghostMoves - homeTimeStartYellow == 20)
        {
            yellowEaten = false;
        }
    }
}

void timer(bool &angerFood)
{
    scaryModeTimer(angerFood);
    homeStayingTimer();
}

bool eatingGhosts(char a[row][column])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    pair<int, int> pacman = make_pair(pacman_row, pacman_column);
    pair<int, int> redGhost = make_pair(red_ghost_row, red_ghost_column);
    pair<int, int> pinkGhost = make_pair(pink_ghost_row, pink_ghost_column);
    pair<int, int> blueGhost = make_pair(blue_ghost_row, blue_ghost_column);
    pair<int, int> yellowGhost = make_pair(yellow_ghost_row, yellow_ghost_column);
    if (pacman == redGhost)
    {
        score += 200;
        homeTimeStartRed = ghostMoves;
        redEaten = true;
        red_ghost_row = row / 2, red_ghost_column = column / 2 - 2;
        ghostPosition(a, red_ghost_row, red_ghost_column);
        isFoodRed = false, isAngerFoodRed = false, isDoorRed = false;
        set_cursor(2 * red_ghost_column, red_ghost_row);
        SetConsoleTextAttribute(hConsole, 12);
        cout << "G";
        return true;
    }
    else if (pacman == pinkGhost)
    {
        score += 200;
        homeTimeStartPink = ghostMoves;
        pinkEaten = true;
        pink_ghost_row = row / 2, pink_ghost_column = column / 2 - 1;
        ghostPosition(a, pink_ghost_row, pink_ghost_column);
        isFoodPink = false, isAngerFoodPink = false, isDoorPink = false;
        set_cursor(2 * pink_ghost_column, pink_ghost_row);
        SetConsoleTextAttribute(hConsole, 13);
        cout << "G";
        return true;
    }
    else if (pacman == blueGhost)
    {
        score += 200;
        homeTimeStartBlue = ghostMoves;
        blueEaten = true;
        blue_ghost_row = row / 2, blue_ghost_column = column / 2;
        ghostPosition(a, blue_ghost_row, blue_ghost_column);
        isFoodBlue = false, isAngerFoodBlue = false, isDoorBlue = false;
        set_cursor(2 * blue_ghost_column, blue_ghost_row);
        SetConsoleTextAttribute(hConsole, 11);
        cout << "G";
        return true;
    }
    else if (pacman == yellowGhost)
    {
        score += 200;
        homeTimeStartYellow = ghostMoves;
        yellowEaten = true;
        yellow_ghost_row = row / 2, yellow_ghost_column = column / 2 + 1;
        ghostPosition(a, yellow_ghost_row, yellow_ghost_column);
        isFoodYellow = false, isAngerFoodYellow = false, isDoorYellow = false;
        set_cursor(2 * yellow_ghost_column, yellow_ghost_row);
        SetConsoleTextAttribute(hConsole, 14);
        cout << "G";
        return true;
    }
    return false;
}

// Pacman movement

void pacman_onestep_move(char a[row][column], char button, bool &isLosing, bool &angerFood)
{
    switch (button)
    {
    case 'w':
        if (a[pacman_row - 1][pacman_column] != '#' && a[pacman_row - 1][pacman_column] != '-')
        {
            scorePlus(a, pacman_row - 1, pacman_column, angerFood);
            set_cursor(0, row);
            a[pacman_row][pacman_column] = ' ';
            set_cursor(2 * pacman_column, pacman_row);
            cout << " ";
            pacman_row -= 1;
            if (losing() && !angerFood)
            {
                isLosing = true;
                return;
            }
            pacman_position(a, pacman_row, pacman_column);
            foods[pacman_row][pacman_column] = 0;
            set_cursor(2 * pacman_column, pacman_row);
            cout << "O";
            set_cursor(8, row);
        }
        break;
    case 'a':
        if (a[pacman_row][pacman_column - 1] != '#' && a[pacman_row][pacman_column - 1] != '-')
        {
            scorePlus(a, pacman_row, pacman_column - 1, angerFood);
            set_cursor(0, row);
            a[pacman_row][pacman_column] = ' ';
            set_cursor(2 * pacman_column, pacman_row);
            cout << " ";
            pacman_column -= 1;
            if (losing() && !angerFood)
            {
                isLosing = true;
                return;
            }
            pacman_position(a, pacman_row, pacman_column);
            foods[pacman_row][pacman_column] = 0;
            set_cursor(2 * pacman_column, pacman_row);
            cout << "O";
            set_cursor(8, row);
        }
        break;
    case 'd':
        if (a[pacman_row][pacman_column + 1] != '#' && a[pacman_row][pacman_column + 1] != '-')
        {
            scorePlus(a, pacman_row, pacman_column + 1, angerFood);
            set_cursor(0, row);
            a[pacman_row][pacman_column] = ' ';
            set_cursor(2 * pacman_column, pacman_row);
            cout << " ";
            pacman_column += 1;
            if (losing() && !angerFood)
            {
                isLosing = true;
                return;
            }
            pacman_position(a, pacman_row, pacman_column);
            foods[pacman_row][pacman_column] = 0;
            set_cursor(2 * pacman_column, pacman_row);
            cout << "O";
            set_cursor(8, row);
        }
        break;
    case 's':
        if (a[pacman_row + 1][pacman_column] != '#' && a[pacman_row + 1][pacman_column] != '-')
        {
            scorePlus(a, pacman_row + 1, pacman_column, angerFood);
            set_cursor(0, row);
            a[pacman_row][pacman_column] = ' ';
            set_cursor(2 * pacman_column, pacman_row);
            cout << " ";
            pacman_row += 1;
            if (losing() && !angerFood)
            {
                isLosing = true;
                return;
            }
            pacman_position(a, pacman_row, pacman_column);
            foods[pacman_row][pacman_column] = 0;
            set_cursor(2 * pacman_column, pacman_row);
            cout << "O";
            set_cursor(8, row);
        }
        break;
    default:
        break;
    }
    if (angerFood)
    {
        if (eatingGhosts(a))
        {
            // Nothing :)
        }
    }
}

void pacman_teleport(char a[row][column], char button, bool &isLosing, bool &angerFood)
{
    if (pacman_column == 0)
    {
        scorePlus(a, pacman_row, column - 1, angerFood);
        set_cursor(0, row);
        a[pacman_row][pacman_column] = ' ';
        set_cursor(2 * pacman_column, pacman_row);
        cout << " ";
        pacman_column = column - 1;
        if (losing() && !angerFood)
        {
            isLosing = true;
            return;
        }
        pacman_position(a, pacman_row, pacman_column);
        foods[pacman_row][pacman_column] = 0;
        set_cursor(2 * pacman_column, pacman_row);
        cout << "O";
        set_cursor(8, row);
    }
    else if (pacman_column == column - 1)
    {
        scorePlus(a, pacman_row, 0, angerFood);
        set_cursor(0, row);
        a[pacman_row][pacman_column] = ' ';
        set_cursor(2 * pacman_column, pacman_row);
        cout << " ";
        pacman_column = 0;
        if (losing() && !angerFood)
        {
            isLosing = true;
            return;
        }
        pacman_position(a, pacman_row, pacman_column);
        foods[pacman_row][pacman_column] = 0;
        set_cursor(2 * pacman_column, pacman_row);
        cout << "O";
        set_cursor(8, row);
    }
    if (angerFood)
    {
        if (eatingGhosts(a))
        {
            // Nothing :)
        }
    }
}

void pacman_movement(char a[row][column], char button, bool &isLosing, bool &angerFood)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (angerFood)
    {
        timer(angerFood);
        SetConsoleTextAttribute(hConsole, 12);
    }
    else
    {
        SetConsoleTextAttribute(hConsole, 6);
    }
    if ((pacman_column == 0 && button == 'a') || (pacman_column == column - 1 && button == 'd'))
    {
        pacman_teleport(a, button, isLosing, angerFood);
        return;
    }
    pacman_onestep_move(a, button, isLosing, angerFood);
}

// Ghosts_movement

bool is_Path[row][column];
void path(char a[row][column])
{
    int i, j;
    int counter = 0;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            if (a[i][j] != '#' && a[i][j] != 'G')
            {
                is_Path[i][j] = 1;
            }
            else
            {
                is_Path[i][j] = 0;
            }
        }
    }
}

// Chasing Algorithms

double destinationCal(int a, int b, int c, int d)
{
    double ans;
    ans = sqrt((a - c) * (a - c) + (b - d) * (b - d));
    return ans;
}

bool isValid(int i, int j)
{
    if (i >= 0 && i < row && j >= 0 && j < column)
    {
        return true;
    }
    return false;
}

pair<int, int> redTarget = make_pair(red_ghost_row, red_ghost_column);
pair<int, int> pinkTarget = make_pair(pink_ghost_row, pink_ghost_column);
pair<int, int> blueTarget = make_pair(blue_ghost_row, blue_ghost_column);
pair<int, int> yellowTarget = make_pair(yellow_ghost_row, yellow_ghost_column);

// _______________HardLevel_______________

void hardAlgorithm(int ghostRow, int ghostCol, pair<int, int> &nextPlace)
{
    nextPlace = nextCellAstar(is_Path, ghostRow, ghostCol, pacman_row, pacman_column);
}

// _______________mediumLevel_______________

pair<int, int> mediumRandomTargets(int ghostRow, int ghostCol)
{
    pair<int, int> target;
    int i, j;
    for (i = pacman_row - 20; i <= pacman_row + 20; i++)
    {
        for (j = pacman_column - 30; j <= pacman_column + 30; j++)
        {
            if (isValid(i, j) && is_Path[i][j] && rand() % 3700 == 0 && destinationCal(i, j, ghostRow, ghostCol) > 7)
            {
                target.first = i;
                target.second = j;
                return target;
            }
        }
    }
    return mediumRandomTargets(ghostRow, ghostCol);
}

bool smartGhostMedium(int ghostRow, int ghostCol, pair<int, int> &nextPlace)
{
    if (ghostRow == red_ghost_row && ghostCol == red_ghost_column && (ghostMoves % 120 <= 29 || (destinationCal(ghostRow, ghostCol, pacman_row, pacman_column) <= 4 && rand() % 2 == 0)))
    {
        nextPlace = nextCellAstar(is_Path, ghostRow, ghostCol, pacman_row, pacman_column);
        return true;
    }
    else if (ghostRow == pink_ghost_row && ghostCol == pink_ghost_column && ((ghostMoves % 120 >= 30 && ghostMoves % 120 <= 59) || (destinationCal(ghostRow, ghostCol, pacman_row, pacman_column) <= 4 && rand() % 2 == 0)))
    {
        nextPlace = nextCellAstar(is_Path, ghostRow, ghostCol, pacman_row, pacman_column);
        return true;
    }
    else if (ghostRow == blue_ghost_row && ghostCol == blue_ghost_column && ((ghostMoves % 120 >= 60 && ghostMoves % 120 <= 89) || (destinationCal(ghostRow, ghostCol, pacman_row, pacman_column) <= 4 && rand() % 2 == 0)))
    {
        nextPlace = nextCellAstar(is_Path, ghostRow, ghostCol, pacman_row, pacman_column);
        return true;
    }
    else if (ghostRow == yellow_ghost_row && ghostCol == yellow_ghost_column && ((ghostMoves % 120 >= 90 && ghostMoves % 120 <= 119) || (destinationCal(ghostRow, ghostCol, pacman_row, pacman_column) <= 4 && rand() % 2 == 0)))
    {
        nextPlace = nextCellAstar(is_Path, ghostRow, ghostCol, pacman_row, pacman_column);
        return true;
    }
    return false;
}

void idiotGhostMedium(int ghostRow, int ghostCol, pair<int, int> &nextPlace)
{
    if (ghostRow == red_ghost_row && ghostCol == red_ghost_column)
    {
        if (make_pair(red_ghost_row, red_ghost_column) == make_pair(redTarget.first, redTarget.second))
        {
            redTarget = mediumRandomTargets(ghostRow, ghostCol);
        }
        nextPlace = nextCellAstar(is_Path, ghostRow, ghostCol, redTarget.first, redTarget.second);
        return;
    }
    else if (ghostRow == pink_ghost_row && ghostCol == pink_ghost_column)
    {
        if (make_pair(pink_ghost_row, pink_ghost_column) == make_pair(pinkTarget.first, pinkTarget.second))
        {
            pinkTarget = mediumRandomTargets(ghostRow, ghostCol);
        }
        nextPlace = nextCellAstar(is_Path, ghostRow, ghostCol, pinkTarget.first, pinkTarget.second);
        return;
    }
    else if (ghostRow == blue_ghost_row && ghostCol == blue_ghost_column)
    {
        if (make_pair(blue_ghost_row, blue_ghost_column) == make_pair(blueTarget.first, blueTarget.second))
        {
            blueTarget = mediumRandomTargets(ghostRow, ghostCol);
        }
        nextPlace = nextCellAstar(is_Path, ghostRow, ghostCol, blueTarget.first, blueTarget.second);
        return;
    }
    // It's surly the yellow ghost
    if (make_pair(yellow_ghost_row, yellow_ghost_column) == make_pair(yellowTarget.first, yellowTarget.second))
    {
        yellowTarget = mediumRandomTargets(ghostRow, ghostCol);
    }
    nextPlace = nextCellAstar(is_Path, ghostRow, ghostCol, yellowTarget.first, yellowTarget.second);
    return;
}

void mediumAlgorithm(int ghostRow, int ghostCol, pair<int, int> &nextPlace)
{
    if (ghostMoves != 0 && ghostMoves != 20 && ghostMoves != 40 && ghostMoves != 60)
    {
        if (smartGhostMedium(ghostRow, ghostCol, nextPlace))
        {
            return;
        }
    }
    idiotGhostMedium(ghostRow, ghostCol, nextPlace);
}

// _______________easyLevel_______________

pair<int, int> easyRandomTargets(int ghostRow, int ghostCol)
{
    pair<int, int> target;
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            if (isValid(i, j) && is_Path[i][j] && rand() % (row * column) == 0 && destinationCal(i, j, ghostRow, ghostCol) > 7)
            {
                target.first = i;
                target.second = j;
                return target;
            }
        }
    }
    return easyRandomTargets(ghostRow, ghostCol);
}

bool smartGhostEasy(int ghostRow, int ghostCol, pair<int, int> &nextPlace)
{
    if (ghostRow == red_ghost_row && ghostCol == red_ghost_column && destinationCal(ghostRow, ghostCol, pacman_row, pacman_column) <= 2 && rand() % 3 == 0)
    {
        nextPlace = nextCellAstar(is_Path, ghostRow, ghostCol, pacman_row, pacman_column);
        return true;
    }
    else if (ghostRow == pink_ghost_row && ghostCol == pink_ghost_column && destinationCal(ghostRow, ghostCol, pacman_row, pacman_column) <= 2 && rand() % 3 == 0)
    {
        nextPlace = nextCellAstar(is_Path, ghostRow, ghostCol, pacman_row, pacman_column);
        return true;
    }
    else if (ghostRow == blue_ghost_row && ghostCol == blue_ghost_column && destinationCal(ghostRow, ghostCol, pacman_row, pacman_column) <= 2 && rand() % 3 == 0)
    {
        nextPlace = nextCellAstar(is_Path, ghostRow, ghostCol, pacman_row, pacman_column);
        return true;
    }
    else if (ghostRow == yellow_ghost_row && ghostCol == yellow_ghost_column && destinationCal(ghostRow, ghostCol, pacman_row, pacman_column) <= 2 && rand() % 3 == 0)
    {
        nextPlace = nextCellAstar(is_Path, ghostRow, ghostCol, pacman_row, pacman_column);
        return true;
    }
    return false;
}

void idiotGhostEasy(int ghostRow, int ghostCol, pair<int, int> &nextPlace)
{
    if (ghostRow == red_ghost_row && ghostCol == red_ghost_column)
    {
        if (make_pair(red_ghost_row, red_ghost_column) == make_pair(redTarget.first, redTarget.second))
        {
            redTarget = easyRandomTargets(ghostRow, ghostCol);
        }
        nextPlace = nextCellAstar(is_Path, ghostRow, ghostCol, redTarget.first, redTarget.second);
        return;
    }
    else if (ghostRow == pink_ghost_row && ghostCol == pink_ghost_column)
    {
        if (make_pair(pink_ghost_row, pink_ghost_column) == make_pair(pinkTarget.first, pinkTarget.second))
        {
            pinkTarget = easyRandomTargets(ghostRow, ghostCol);
        }
        nextPlace = nextCellAstar(is_Path, ghostRow, ghostCol, pinkTarget.first, pinkTarget.second);
        return;
    }
    else if (ghostRow == blue_ghost_row && ghostCol == blue_ghost_column)
    {
        if (make_pair(blue_ghost_row, blue_ghost_column) == make_pair(blueTarget.first, blueTarget.second))
        {
            blueTarget = easyRandomTargets(ghostRow, ghostCol);
        }
        nextPlace = nextCellAstar(is_Path, ghostRow, ghostCol, blueTarget.first, blueTarget.second);
        return;
    }
    // It's surly the yellow ghost
    if (make_pair(yellow_ghost_row, yellow_ghost_column) == make_pair(yellowTarget.first, yellowTarget.second))
    {
        yellowTarget = easyRandomTargets(ghostRow, ghostCol);
    }
    nextPlace = nextCellAstar(is_Path, ghostRow, ghostCol, yellowTarget.first, yellowTarget.second);
    return;
}

void easyAlgorithm(int ghostRow, int ghostCol, pair<int, int> &nextPlace)
{
    if (ghostMoves != 0 && ghostMoves != 20 && ghostMoves != 40 && ghostMoves != 60)
    {
        if (smartGhostEasy(ghostRow, ghostCol, nextPlace))
        {
            return;
        }
    }
    idiotGhostEasy(ghostRow, ghostCol, nextPlace);
}

void findLevelOfAlgorithm(char level, int ghostRow, int ghostCol, pair<int, int> &nextPlace)
{
    switch (level)
    {
    case '1':
        easyAlgorithm(ghostRow, ghostCol, nextPlace);
        break;
    case '2':
        mediumAlgorithm(ghostRow, ghostCol, nextPlace);
        break;
    case '3':
        hardAlgorithm(ghostRow, ghostCol, nextPlace);
        break;
    default:
        break;
    }
}

set<pair<double, pair<int, int>>> peripheralCells;

void peripheralCellsCollector(int ghostRow, int ghostCol)
{
    bool found = false;
    pair<int, pair<int, int>> escapeCell;
    int i, j;
    if (is_Path[ghostRow - 1][ghostCol] && isValid(ghostRow - 1, ghostCol) && (ghostRow - 1 != pacman_row || ghostCol != pacman_column))
    {
        i = ghostRow - 1;
        j = ghostCol;
        escapeCell.first = hCalculator(i, j, pacman_row, pacman_column);
        escapeCell.second = make_pair(i, j);
        peripheralCells.insert(escapeCell);
        found = true;
    }
    if (is_Path[ghostRow][ghostCol + 1] && isValid(ghostRow, ghostCol + 1) && (ghostRow != pacman_row || ghostCol + 1 != pacman_column))
    {
        i = ghostRow;
        j = ghostCol + 1;
        escapeCell.first = hCalculator(i, j, pacman_row, pacman_column);
        escapeCell.second = make_pair(i, j);
        peripheralCells.insert(escapeCell);
        found = true;
    }
    if (is_Path[ghostRow + 1][ghostCol] && isValid(ghostRow + 1, ghostCol) && (ghostRow + 1 != pacman_row || ghostCol != pacman_column))
    {
        i = ghostRow + 1;
        j = ghostCol;
        escapeCell.first = hCalculator(i, j, pacman_row, pacman_column);
        escapeCell.second = make_pair(i, j);
        peripheralCells.insert(escapeCell);
        found = true;
    }
    if (is_Path[ghostRow][ghostCol - 1] && isValid(ghostRow, ghostCol - 1) && (ghostRow != pacman_row || ghostCol - 1 != pacman_column))
    {
        i = ghostRow;
        j = ghostCol - 1;
        escapeCell.first = hCalculator(i, j, pacman_row, pacman_column);
        escapeCell.second = make_pair(i, j);
        peripheralCells.insert(escapeCell);
        found = true;
    }
    if (!found)
    {
        i = ghostRow;
        j = ghostCol;
        escapeCell.first = hCalculator(i, j, pacman_row, pacman_column);
        escapeCell.second = make_pair(i, j);
        peripheralCells.insert(escapeCell);
    }
}

void scaredGhostAlgorithm(int ghostRow, int ghostCol, pair<int, int> &nextPlace)
{
    peripheralCells.clear();
    peripheralCellsCollector(ghostRow, ghostCol);
    pair<int, pair<int, int>> escapeCell;
    if (rand() % 5 > 0)
    {
        escapeCell = *peripheralCells.rbegin();
        nextPlace = escapeCell.second;
    }
    else
    {
        // escapeCell = *peripheralCells.begin();
        idiotGhostEasy(ghostRow, ghostCol, nextPlace);
    }
}

// _______________end Of Algorithms_______________

void isFoodDoornow(bool isFood, bool isAngerFood, bool isDoor, char a[row][column], int ghostRow, int ghostCol)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    set_cursor(0, row + 1);
    set_cursor(2 * ghostCol, ghostRow);
    if (isFood == true)
    {
        a[ghostRow][ghostCol] = '.';
        SetConsoleTextAttribute(hConsole, 10);
        cout << ".";
    }
    else if (isAngerFood == true)
    {
        a[ghostRow][ghostCol] = '$';
        SetConsoleTextAttribute(hConsole, 10);
        cout << "$";
    }
    else if (isDoor == true)
    {
        a[ghostRow][ghostCol] = '-';
        SetConsoleTextAttribute(hConsole, 10);
        cout << "-";
    }
    else
    {
        a[ghostRow][ghostCol] = ' ';
        SetConsoleTextAttribute(hConsole, 15);
        cout << " ";
    }
    set_cursor(0, row + 1);
}

void isFoodDoorNext(int nextRow, int nextCol, char a[row][column], bool &isFood, bool &isAngerFood, bool &isDoor)
{
    if (a[nextRow][nextCol] == '.')
    {
        isFood = true;
    }
    else if (a[nextRow][nextCol] == '$')
    {
        isAngerFood = true;
        isFood = false;
    }
    else
    {
        isAngerFood = false;
        isFood = false;
    }
    if (a[nextRow][nextCol] == '-')
    {
        isDoor = true;
    }
    else
    {
        isDoor = false;
    }
}

void redGhost_oneStepMove(char a[row][column], char level, bool &angerFood)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    pair<int, int> nextPlace;
    isFoodDoornow(isFoodRed, isAngerFoodRed, isDoorRed, a, red_ghost_row, red_ghost_column);
    if (angerFood)
    {
        scaredGhostAlgorithm(red_ghost_row, red_ghost_column, nextPlace);
        SetConsoleTextAttribute(hConsole, 15);
    }
    else
    {
        findLevelOfAlgorithm(level, red_ghost_row, red_ghost_column, nextPlace);
        SetConsoleTextAttribute(hConsole, 12);
    }
    isFoodDoorNext(nextPlace.first, nextPlace.second, a, isFoodRed, isAngerFoodRed, isDoorRed);
    red_ghost_row = nextPlace.first;
    red_ghost_column = nextPlace.second;
    if (angerFood)
    {
        if (eatingGhosts(a))
        {
            return;
        }
    }
    ghostPosition(a, red_ghost_row, red_ghost_column);
    set_cursor(0, row);
    set_cursor(2 * red_ghost_column, red_ghost_row);
    cout << "G";
    set_cursor(0, row + 1);
}

void pinkGhost_oneStepMove(char a[row][column], char level, bool &angerFood)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    pair<int, int> nextPlace;
    isFoodDoornow(isFoodPink, isAngerFoodPink, isDoorPink, a, pink_ghost_row, pink_ghost_column);
    if (angerFood)
    {
        scaredGhostAlgorithm(pink_ghost_row, pink_ghost_column, nextPlace);
        SetConsoleTextAttribute(hConsole, 15);
    }
    else
    {
        findLevelOfAlgorithm(level, pink_ghost_row, pink_ghost_column, nextPlace);
        SetConsoleTextAttribute(hConsole, 13);
    }
    isFoodDoorNext(nextPlace.first, nextPlace.second, a, isFoodPink, isAngerFoodPink, isDoorPink);
    pink_ghost_row = nextPlace.first;
    pink_ghost_column = nextPlace.second;
    if (angerFood)
    {
        if (eatingGhosts(a))
        {
            return;
        }
    }
    ghostPosition(a, pink_ghost_row, pink_ghost_column);
    set_cursor(0, row);
    set_cursor(2 * pink_ghost_column, pink_ghost_row);
    cout << "G";
    set_cursor(0, row + 1);
}

void blueGhost_oneStepMove(char a[row][column], char level, bool &angerFood)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    pair<int, int> nextPlace;
    isFoodDoornow(isFoodBlue, isAngerFoodBlue, isDoorBlue, a, blue_ghost_row, blue_ghost_column);
    if (angerFood)
    {
        scaredGhostAlgorithm(blue_ghost_row, blue_ghost_column, nextPlace);
        SetConsoleTextAttribute(hConsole, 15);
    }
    else
    {
        findLevelOfAlgorithm(level, blue_ghost_row, blue_ghost_column, nextPlace);
        SetConsoleTextAttribute(hConsole, 11);
    }
    isFoodDoorNext(nextPlace.first, nextPlace.second, a, isFoodBlue, isAngerFoodBlue, isDoorBlue);
    blue_ghost_row = nextPlace.first;
    blue_ghost_column = nextPlace.second;
    if (angerFood)
    {
        if (eatingGhosts(a))
        {
            return;
        }
    }
    ghostPosition(a, blue_ghost_row, blue_ghost_column);
    set_cursor(0, row);
    set_cursor(2 * blue_ghost_column, blue_ghost_row);
    cout << "G";
    set_cursor(0, row + 1);
}

void yellowGhost_oneStepMove(char a[row][column], char level, bool &angerFood)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    pair<int, int> nextPlace;
    isFoodDoornow(isFoodYellow, isAngerFoodYellow, isDoorYellow, a, yellow_ghost_row, yellow_ghost_column);
    if (angerFood)
    {
        scaredGhostAlgorithm(yellow_ghost_row, yellow_ghost_column, nextPlace);
        SetConsoleTextAttribute(hConsole, 15);
    }
    else
    {
        findLevelOfAlgorithm(level, yellow_ghost_row, yellow_ghost_column, nextPlace);
        SetConsoleTextAttribute(hConsole, 14);
    }
    isFoodDoorNext(nextPlace.first, nextPlace.second, a, isFoodYellow, isAngerFoodYellow, isDoorYellow);
    yellow_ghost_row = nextPlace.first;
    yellow_ghost_column = nextPlace.second;
    if (angerFood)
    {
        if (eatingGhosts(a))
        {
            return;
        }
    }
    ghostPosition(a, yellow_ghost_row, yellow_ghost_column);
    set_cursor(0, row);
    set_cursor(2 * yellow_ghost_column, yellow_ghost_row);
    cout << "G";
    set_cursor(0, row + 1);
}

void ghostsMovement(char a[row][column], bool &isLosing, char level, bool &angerFood)
{
    if (!angerFood || !redEaten)
    {
        path(a);
        redGhost_oneStepMove(a, level, angerFood);
        if (losing() && !angerFood)
        {
            isLosing = true;
            return;
        }
    }
    if (ghostMoves >= 20 && (!angerFood || !pinkEaten))
    {
        path(a);
        pinkGhost_oneStepMove(a, level, angerFood);
        if (losing() && !angerFood)
        {
            isLosing = true;
            return;
        }
    }
    if (ghostMoves >= 40 && (!angerFood || !blueEaten))
    {
        path(a);
        blueGhost_oneStepMove(a, level, angerFood);
        if (losing() && !angerFood)
        {
            isLosing = true;
            return;
        }
    }
    if (ghostMoves >= 60 && (!angerFood || !yellowEaten))
    {
        path(a);
        yellowGhost_oneStepMove(a, level, angerFood);
        if (losing() && !angerFood)
        {
            isLosing = true;
            return;
        }
    }
}
