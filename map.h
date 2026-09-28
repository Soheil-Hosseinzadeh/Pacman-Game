#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <time.h>
#include <unistd.h>
using namespace std;
// It's better to be like : row is odd, column is even
// row could be at least 11 and column could be at least 22
const int row = 21, column = 46;
bool foods[row][column];

void initializing_board_ambient(char a[row][column])
{
    int i;
    for (i = 0; i < column; i++)
    {
        a[0][i] = '#';
        a[row - 1][i] = '#';
    }
    for (i = 0; i < row; i++)
    {
        a[i][0] = '#';
        a[i][column - 1] = '#';
    }
    a[row / 2][0] = ' ';
    a[row / 2][column - 1] = ' ';
}
void ghosts_home(char a[row][column])
{
    int i;
    for (i = (row / 2) - 1; i <= (row / 2) + 1; i++)
    {
        a[i][(column / 2) - 3] = '#';
        a[i][(column / 2) + 2] = '#';
    }
    for (i = (column / 2) - 2; i <= (column / 2) + 1; i++)
    {
        a[(row / 2) - 1][i] = '-';
        a[(row / 2) + 1][i] = '-';
    }
}
void corner1(char a[row][column], int r, int c)
{
    int i, j, k = (r + 3) % 2;
    for (i = r; ((r < row / 2 && i <= row / 2 - 3) || (r > row / 2 && i <= row - 3)); i++)
    {
        for (j = c; j <= c + 8; j++)
        {
            if (c < column / 2)
            {
                if (!(j < column / 2 - 6))
                {
                    break;
                }
            }
            if (c > column / 2)
            {
                while (j <= column / 2 + 5)
                {
                    j++;
                }
            }

            if (i == r)
            {
                if (j != c + 3 && j != c + 7)
                {
                    a[i][j] = '#';
                }
            }
            if (i == r + 1)
            {
                if (j != c + 3 && j != c + 7)
                {
                    a[i][j] = '#';
                }
            }
            if (j == c + 8 && (i % 3 != 0))
            {
                a[i][j] = '#';
            }
            if (i == row / 2 - 3 || i == row - 3)
            {
                a[i][j] = '#';
            }
            if (i >= r + 3 && i % 2 == k && j <= c + 6)
            {
                a[i][j] = '#';
            }
        }
    }
}
void corner2(char a[row][column], int r, int c)
{
    int i, j, k = (r + 3) % 3, h = (r + 3) % 2;
    for (i = r; ((r < row / 2 && i <= row / 2 - 3) || (r > row / 2 && i <= row - 3)); i++)
    {
        for (j = c; j <= c + 8; j++)
        {
            if (c < column / 2)
            {
                if (!(j < column / 2 - 6))
                {
                    break;
                }
            }
            if (c > column / 2)
            {
                while (j <= column / 2 + 5)
                {
                    j++;
                }
            }
            if (i == r || i == r + 1)
            {
                if (j != c + 1 && j != c + 3)
                {
                    a[i][j] = '#';
                }
            }
            if (i >= r + 2 && j == c && (i % 3 != 0))
            {
                a[i][j] = '#';
            }
            if (i == row / 2 - 3 || i == row - 3)
            {
                a[i][j] = '#';
            }
            if (i >= r + 3 && i % 3 == k && j == c + 2)
            {
                a[i][j] = '#';
                a[i - 1][j] = '#';
            }
            if (i >= r + 3 && i % 2 == h && j >= c + 4)
            {
                a[i][j] = '#';
            }
        }
    }
}
void corner3(char a[row][column], int r, int c)
{
    int i, j, k = (r + 3) % 3;
    for (i = r; ((r < row / 2 && i <= row / 2 - 3) || (r > row / 2 && i <= row - 3)); i++)
    {
        for (j = c; j <= c + 8; j++)
        {
            if (c < column / 2)
            {
                if (!(j < column / 2 - 6))
                {
                    break;
                }
            }
            if (c > column / 2)
            {
                while (j <= column / 2 + 5)
                {
                    j++;
                }
            }
            if (i == r || i == row - 3 || i == row / 2 - 3)
            {
                a[i][j] = '#';
            }
            if (j == c && (i % 3 != 0))
            {
                a[i][j] = '#';
            }
            if (i >= r + 3 && i % 3 == k && j != c + 1 && j != c + 4 && j != c + 6)
            {
                a[i - 1][j] = '#';
                a[i][j] = '#';
            }
        }
    }
}
void corner4(char a[row][column], int r, int c)
{
    int i, j, k = (r + 5) % 3;
    for (i = r; ((r < row / 2 && i <= row / 2 - 3) || (r > row / 2 && i <= row - 3)); i++)
    {
        for (j = c; j <= c + 8; j++)
        {
            if (c < column / 2)
            {
                if (!(j < column / 2 - 6))
                {
                    break;
                }
            }
            else if (c > column / 2)
            {
                while (j <= column / 2 + 5)
                {
                    j++;
                }
            }
            if (i == r)
            {
                a[i][j] = '#';
            }
            if (j == c + 8 && (i % 3 != 0))
            {
                a[i][j] = '#';
            }
            if (i == r + 2 && j != c + 3 && j != c + 5 && j < c + 7)
            {
                a[i][j] = '#';
            }
            if (i >= r + 5 && i % 3 == k && j != c + 3 && j != c + 5 && j < c + 7)
            {
                a[i - 1][j] = '#';
                a[i][j] = '#';
            }
            if ((i == row - 3 || i == row / 2 - 3) && j != c + 3 && j != c + 5 && j != c + 7)
            {
                a[i][j] = '#';
            }
        }
    }
}

void random_corners(char a[row][column])
{
    int i, r, c, num, temp1 = 4, temp2 = 4, temp3 = 4, temp4 = 4;
    srand(time(NULL));
    for (i = 1; i <= 4; i++)
    {
        switch (i)
        {
        case 1:
            r = 2;
            c = 2;
            break;
        case 2:
            r = 2;
            c = column - 11;
            break;
        case 3:
            r = row / 2 + 3;
            c = column - 11;
            break;
        case 4:
            r = row / 2 + 3;
            c = 2;
            break;
        default:
            break;
        }
        num = rand() % 4;
        while (num == temp1 || num == temp2 || num == temp3 || num == temp4)
        {
            num = rand() % 4;
        }
        switch (num)
        {
        case 0:
            temp1 = num;
            corner1(a, r, c);
            break;
        case 1:
            temp2 = num;
            corner2(a, r, c);
            break;
        case 2:
            temp3 = num;
            corner3(a, r, c);
            break;
        case 3:
            temp4 = num;
            corner4(a, r, c);
            break;
        default:
            break;
        }
    }
}

void area1(char a[row][column], int r, int c)
{
    int i, j, num;
    srand(time(NULL));
    for (i = r; ((r < row / 2 && i <= row / 2 - 3) || (r > row / 2 && i <= row - 3)); i += 2)
    {
        for (j = c; ((c < column / 2 && j < column / 2 - 6) || (c > column / 2 && j < column - 12)); j += 3)
        {
            if (i == row / 2 - 4 || i == row - 4)
            {
                if (j == column / 2 - 9 || j == column - 15)
                {
                    a[i][j + 2] = '#';
                    a[i + 1][j + 2] = '#';
                }
                a[i][j] = '#';
                a[i + 1][j] = '#';
                if ((c < column / 2 && j + 1 < column / 2 - 6) || (c > column / 2 && j + 1 < column - 12))
                {
                    a[i][j + 1] = '#';
                    a[i + 1][j + 1] = '#';
                }
            }
            else
            {
                if (j == column / 2 - 9 || j == column - 15)
                {
                    a[i][j + 2] = '#';
                }
                a[i][j] = '#';
                if ((c < column / 2 && j + 1 < column / 2 - 6) || (c > column / 2 && j + 1 < column - 12))
                {
                    a[i][j + 1] = '#';
                }
            }
        }
        for (j = c + 2; ((c < column / 2 && j < column / 2 - 7) || (c > column / 2 && j < column - 13)); j += 3)
        {
            if (i == row / 2 - 4 || i == row - 4)
            {
                if (rand() % 3 == 0)
                {
                    a[i][j] = '#';
                    a[i + 1][j] = '#';
                }
            }
            else if (rand() % 3 == 0)
            {
                a[i][j] = '#';
            }
        }
    }
}

void area2(char a[row][column], int r, int c)
{
    int i, j;
    srand(time(NULL));
    for (j = c; ((c < column / 2 && j < column / 2 - 6) || (c > column / 2 && j < column - 12)); j += 2)
    {
        for (i = r; ((r < row / 2 && i <= row / 2 - 3) || (r > row / 2 && i <= row - 3)); i += 2)
        {
            a[i][j] = '#';
            if (j == column - 14 || j == column / 2 - 8)
            {
                a[i][j + 1] = '#';
            }
            if (i == row / 2 - 4 || i == row - 4)
            {
                a[i + 1][j] = '#';
                if (j == column - 14 || j == column / 2 - 8)
                {
                    a[i + 1][j + 1] = '#';
                }
            }
        }
        for (i = r + 1; ((r < row / 2 && i < row / 2 - 3) || (r > row / 2 && i < row - 3)); i += 2)
        {
            if (rand() % 2 == 0)
            {
                a[i][j] = '#';
                if (j == column - 14 || j == column / 2 - 8)
                {
                    a[i][j + 1] = '#';
                }
            }
        }
    }
}

void area3_helper(int i, int j, int c, char a[row][column])
{
    int k;
    if (j == column - 16 || j == column / 2 - 10)
    {
        for (k = j; k <= j + 3 && ((c < column / 2 && k < column / 2 - 6) || (c > column / 2 && k < column - 12)); k++)
        {
            a[i][k] = '#';
        }
    }
    else
    {
        for (k = j; k <= j + 2 && ((c < column / 2 && k < column / 2 - 6) || (c > column / 2 && k < column - 12)); k++)
        {
            a[i][k] = '#';
        }
    }
}

void area3(char a[row][column], int r, int c)
{
    int i, j, k;
    int space_between_rand = (r + 1) % 2;
    srand(time(NULL));
    for (j = c; ((c < column / 2 && j < column / 2 - 6) || (c > column / 2 && j < column - 12)); j += 4)
    {
        for (i = r; ((r < row / 2 && i <= row / 2 - 3) || (r > row / 2 && i <= row - 3)); i++)
        {
            if (i == r || i == row / 2 - 3 || i == row - 3)
            {
                area3_helper(i, j, c, a);
            }
            else if (i % 2 != space_between_rand)
            {
                area3_helper(i, j, c, a);
            }
            else if (rand() % 3 == 0)
            {
                area3_helper(i, j, c, a);
            }
        }
    }
}

void area4_helper(int i, int j, int r, char a[row][column])
{
    int k;
    if (i == row - 6 || i == row / 2 - 6)
    {
        for (k = i; k <= i + 3 && ((r < row / 2 && k <= row / 2 - 3) || (r > row / 2 && k <= row - 3)); k++)
        {
            a[k][j] = '#';
        }
    }
    else
    {
        for (k = i; k <= i + 2 && ((r < row / 2 && k <= row / 2 - 3) || (r > row / 2 && k <= row - 3)); k++)
        {
            a[k][j] = '#';
        }
    }
}

void area4(char a[row][column], int r, int c)
{
    int i, j, k;
    int space_between_rand = c % 2;
    srand(time(NULL));
    for (i = r; ((r < row / 2 && i <= row / 2 - 3) || (r > row / 2 && i <= row - 3)); i += 4)
    {
        for (j = c; ((c < column / 2 && j < column / 2 - 6) || (c > column / 2 && j < column - 12)); j++)
        {
            if (j == c || j == column / 2 - 7 || j == column - 13)
            {
                area4_helper(i, j, r, a);
            }
            else if (j % 2 == space_between_rand)
            {
                area4_helper(i, j, r, a);
            }
            else if (rand() % 3 == 0)
            {
                area4_helper(i, j, r, a);
            }
        }
    }
}

void random_areas(char a[row][column])
{
    int i, r, c, num, temp1 = 4, temp2 = 4, temp3 = 4, temp4 = 4;
    srand(time(NULL));
    for (i = 1; i <= 4; i++)
    {
        switch (i)
        {
        case 1:
            r = 2;
            c = 12;
            break;
        case 2:
            r = 2;
            c = column / 2 + 6;
            break;
        case 3:
            r = row / 2 + 3;
            c = column / 2 + 6;
            break;
        case 4:
            r = row / 2 + 3;
            c = 12;
            break;
        default:
            break;
        }
        num = rand() % 4;
        while (num == temp1 || num == temp2 || num == temp3 || num == temp4)
        {
            num = rand() % 4;
        }
        switch (num)
        {
        case 0:
            temp1 = num;
            area1(a, r, c);
            break;
        case 1:
            temp2 = num;
            area2(a, r, c);
            break;
        case 2:
            temp3 = num;
            area3(a, r, c);
            break;
        case 3:
            temp4 = num;
            area4(a, r, c);
            break;
        default:
            break;
        }
    }
}

void middle_shape1(char a[row][column], int r, int c)
{
    int i, j;
    for (i = c; i <= c + 6 && ((c < column / 2 && i < column / 2 - 6) || (c > column / 2 && i < column - 6)); i++)
    {
        if (i != c + 5)
        {
            a[r][i] = '#';
        }
        if (i != c + 1)
        {
            a[r + 2][i] = '#';
        }
        if (i == c)
        {
            a[r + 1][c] = '#';
        }
        if (i == c + 6)
        {
            a[r + 1][c + 6] = '#';
        }
    }
}

void middle_shape2(char a[row][column], int r, int c)
{
    int i, j;
    for (i = c; i <= c + 6 && ((c < column / 2 && i < column / 2 - 6) || (c > column / 2 && i < column - 6)); i++)
    {
        a[r][i] = '#';
        a[r + 2][i] = '#';
    }
}

void middle_shape3(char a[row][column], int r, int c)
{
    int i, j;
    for (i = c; i <= c + 6 && ((c < column / 2 && i < column / 2 - 6) || (c > column / 2 && i < column - 6)); i += 2)
    {
        for (j = r; j <= r + 2; j++)
        {
            a[j][i] = '#';
        }
    }
}

void middle_shape4(char a[row][column], int r, int c)
{
    int i, j;
    for (i = c; i <= c + 6 && ((c < column / 2 && i < column / 2 - 6) || (c > column / 2 && i < column - 6)); i++)
    {
        a[r][i] = '#';
        if (i != c + 5)
        {
            a[r + 2][i] = '#';
        }
        if (i == c + 6)
        {
            for (j = r; j <= r + 2; j++)
            {
                a[j][i] = '#';
            }
        }
    }
}

void random_middle_shapes(char a[row][column])
{
    int i;
    srand(time(NULL));
    for (i = 6; i < column / 2 - 6; i += 8)
    {
        switch (rand() % 4)
        {
        case 0:
            middle_shape1(a, row / 2 - 1, i);
            break;
        case 1:
            middle_shape2(a, row / 2 - 1, i);
            break;
        case 2:
            middle_shape3(a, row / 2 - 1, i);
            break;
        case 3:
            middle_shape4(a, row / 2 - 1, i);
            break;
        default:
            break;
        }
    }
    for (i = column / 2 + 6; i < column - 6; i += 8)
    {
        switch (rand() % 4)
        {
        case 0:
            middle_shape1(a, row / 2 - 1, i);
            break;
        case 1:
            middle_shape2(a, row / 2 - 1, i);
            break;
        case 2:
            middle_shape3(a, row / 2 - 1, i);
            break;
        case 3:
            middle_shape4(a, row / 2 - 1, i);
            break;
        default:
            break;
        }
    }
}

void middle_updown_shape(char a[row][column], int r, int c)
{
    int i, j, k = r % 2, h;
    for (i = r; (r < row / 2 && i <= row / 2 - 3) || (r > row / 2 && i <= row - 5); i++)
    {
        if (i % 2 == k)
        {
            for (j = column / 2 - 5; j <= column / 2 + 4; j++)
            {
                if (j == column / 2)
                {
                    continue;
                }
                a[i][j] = '#';
            }
        }
        else if (rand() % 3 == 0)
        {
            for (j = column / 2 - 5; j <= column / 2 + 4; j++)
            {
                if (j == column / 2)
                {
                    continue;
                }
                a[i][j] = '#';
            }
        }
        if (i == row / 2 - 3 || i == row - 5)
        {
            for (j = column / 2 - 5; j <= column / 2 + 4; j++)
            {
                if (j == column / 2)
                {
                    continue;
                }
                a[i][j] = '#';
            }
        }
    }
}

void constants(char a[row][column])
{
    int i, j;
    for (i = column / 2 - 5; i <= column / 2 + 4; i++)
    {
        a[1][i] = '#';
        a[2][i] = '#';
        a[row - 2][i] = '#';
        a[row - 3][i] = '#';
    }
    for (i = 1; i <= 4 && i < column / 2 - 6; i++)
    {
        a[row / 2 - 1][i] = '#';
        a[row / 2 + 1][i] = '#';
    }
    for (i = column - 2; i >= column - 5 && i > column / 2 + 5; i--)
    {
        a[row / 2 - 1][i] = '#';
        a[row / 2 + 1][i] = '#';
    }
    for (i = row / 2 - 1; i <= row / 2 + 1; i++)
    {
        a[i][column / 2 - 5] = '#';
        a[i][column / 2 + 4] = '#';
    }
}

void superFood(char a[row][column])
{
    int i, j;
    i = rand() % row;
    j = rand() % column;
    if (a[i][j] == '.')
    {
        a[i][j] = '$';
        return;
    }
    superFood(a);
}

void initializingFoods()
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            foods[i][j] = 0;
        }
    }
}

void pacman_foods(char a[row][column])
{
    srand(time(NULL));
    int i, j;
    initializingFoods();
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            if (a[i][j] == ' ' && (i != row / 2 || j >= column / 2 + 2 || j <= column / 2 - 3))
            {
                a[i][j] = '.';
                foods[i][j] = 1;
            }
        }
    }
    for (i = 0; i < 5; i++)
    {
        superFood(a);
    }
}
