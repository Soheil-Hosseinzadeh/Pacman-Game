#include <iostream>
#include <math.h>
#include <float.h> // double max
#include "map.h"
#include <utility> // for using pair
#include <windows.h>
#include <vector>
using namespace std;

struct cell
{
    int parent_i, parent_j;
    double f, g, h;
};

struct openListItem
{
    int f, i, j;
};

double hCalculator(int row, int column, int trow, int tcol)
{
    return (double)(abs(trow - row) + abs(tcol - column));
}

void cellDetails_initializer(cell a[row][column])
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            a[i][j].parent_i = -1;
            a[i][j].parent_j = -1;
            a[i][j].f = -1;
            a[i][j].g = 0;
            a[i][j].h = 0;
        }
    }
}

void openList_initializer(vector<openListItem> &openList)
{
    openList.clear();
}

void closedList_Initializer(bool a[row][column])
{
    int i, j;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < column; j++)
        {
            a[i][j] = 0; // not visited
        }
    }
}

void insert_into_OpenList(vector<openListItem> &openList, cell cellDetails[row][column], int a, int b)
{
    openListItem item;
    item.f = cellDetails[a][b].f;
    item.i = a;
    item.j = b;
    openList.push_back(item);
}

openListItem extract_from_openList(vector<openListItem> &openList)
{
    openListItem min = *openList.begin();
    vector<openListItem>::iterator minPos;
    minPos = openList.begin();
    for (vector<openListItem>::iterator i = openList.begin() + 1; i < openList.end(); i++)
    {
        if ((*i).f < min.f)
        {
            min = *i;
            minPos = i;
        }
    }
    openList.erase(minPos);
    return min;
}

int nextCell_row = -1, nextCell_column = -1;
void backRoute_finder(cell cellDetails[row][column], int row, int col, int SourceRow, int SourceCol)
{
    int tempRow, tempCol;
    while (!(cellDetails[row][col].parent_i == SourceRow && cellDetails[row][col].parent_j == SourceCol))
    {
        tempRow = cellDetails[row][col].parent_i;
        tempCol = cellDetails[row][col].parent_j;
        row = tempRow;
        col = tempCol;
    }
    nextCell_row = row;
    nextCell_column = col;
}

void Astar(int source_row, int source_column, int target_row, int target_column, bool isValid[row][column])
{
    bool foundTarget = false;
    cell cellDetails[row][column];
    cellDetails_initializer(cellDetails);

    bool closedList[row][column];
    closedList_Initializer(closedList);

    vector<openListItem> openList;
    openList_initializer(openList);

    if (source_row == target_row && source_column == target_column) // source is target
    {
        nextCell_row = source_row;
        nextCell_column = source_column;
        foundTarget = true;
        return;
    }
    
    cellDetails[source_row][source_column].f = 0;
    cellDetails[source_row][source_column].g = 0;
    cellDetails[source_row][source_column].h = 0;
    cellDetails[source_row][source_column].parent_i = source_row;
    cellDetails[source_row][source_column].parent_j = source_column;
    insert_into_OpenList(openList, cellDetails, source_row, source_column);

    while (!openList.empty())
    {
        int i, j;
        openListItem minf;
        minf = extract_from_openList(openList);
        i = minf.i;
        j = minf.j;
        closedList[i][j] = true;

        double gNew, hNew, fNew;
        // North cell
        if (isValid[i - 1][j] && closedList[i - 1][j] == false)
        {
            if (target_row == i - 1 && target_column == j) // isTarget
            {
                foundTarget = true;
                cellDetails[i - 1][j].parent_i = i;
                cellDetails[i - 1][j].parent_j = j;
                backRoute_finder(cellDetails, i - 1, j, source_row, source_column);
                return;
            }
            else
            {
                gNew = cellDetails[i][j].g + 1;
                hNew = hCalculator(i - 1, j, target_row, target_column);
                fNew = gNew + hNew;
                // If the dot is not in the openList then add it, if yes check if it has a greater f than fNew, then add it to the openList.
                if (cellDetails[i - 1][j].f == -1 || cellDetails[i - 1][j].f > fNew)
                {
                    cellDetails[i - 1][j].f = fNew;
                    cellDetails[i - 1][j].g = gNew;
                    cellDetails[i - 1][j].h = hNew;
                    cellDetails[i - 1][j].parent_i = i;
                    cellDetails[i - 1][j].parent_j = j;
                    insert_into_OpenList(openList, cellDetails, i - 1, j);
                }
            }
        }

        // East cell
        if (isValid[i][j + 1] && closedList[i][j + 1] == false)
        {
            if (target_row == i && target_column == j + 1) // isTarget
            {
                foundTarget = true;
                cellDetails[i][j + 1].parent_i = i;
                cellDetails[i][j + 1].parent_j = j;
                backRoute_finder(cellDetails, i, j + 1, source_row, source_column);
                return;
            }
            else
            {
                gNew = cellDetails[i][j].g + 1;
                hNew = hCalculator(i, j + 1, target_row, target_column);
                fNew = gNew + hNew;
                // If the dot is not in the openList then add it, if yes check if it has a greater f than fNew, then add it to the openList.
                if (cellDetails[i][j + 1].f == -1 || cellDetails[i][j + 1].f > fNew)
                {
                    cellDetails[i][j + 1].f = fNew;
                    cellDetails[i][j + 1].g = gNew;
                    cellDetails[i][j + 1].h = hNew;
                    cellDetails[i][j + 1].parent_i = i;
                    cellDetails[i][j + 1].parent_j = j;
                    insert_into_OpenList(openList, cellDetails, i, j + 1);
                }
            }
        }

        // South cell
        if (isValid[i + 1][j] && closedList[i + 1][j] == false)
        {
            if (target_row == i + 1 && target_column == j) // isTarget
            {
                foundTarget = true;
                cellDetails[i + 1][j].parent_i = i;
                cellDetails[i + 1][j].parent_j = j;
                backRoute_finder(cellDetails, i + 1, j, source_row, source_column);
                return;
            }
            else
            {
                gNew = cellDetails[i][j].g + 1;
                hNew = hCalculator(i + 1, j, target_row, target_column);
                fNew = gNew + hNew;
                // If the dot is not in the openList then add it, if yes check if it has a greater f than fNew, then add it to the openList.
                if (cellDetails[i + 1][j].f == -1 || cellDetails[i + 1][j].f > fNew)
                {
                    cellDetails[i + 1][j].f = fNew;
                    cellDetails[i + 1][j].g = gNew;
                    cellDetails[i + 1][j].h = hNew;
                    cellDetails[i + 1][j].parent_i = i;
                    cellDetails[i + 1][j].parent_j = j;
                    insert_into_OpenList(openList, cellDetails, i + 1, j);
                }
            }
        }

        // West cell
        if (isValid[i][j - 1] && closedList[i][j - 1] == false)
        {
            if (target_row == i && target_column == j - 1) // isTarget
            {
                foundTarget = true;
                cellDetails[i][j - 1].parent_i = i;
                cellDetails[i][j - 1].parent_j = j;
                backRoute_finder(cellDetails, i, j - 1, source_row, source_column);
                return;
            }
            else
            {
                gNew = cellDetails[i][j].g + 1;
                hNew = hCalculator(i, j - 1, target_row, target_column);
                fNew = gNew + hNew;
                // If the dot is not in the openList then add it, if yes check if it has a greater f than fNew, then add it to the openList.
                if (cellDetails[i][j - 1].f == -1 || cellDetails[i][j - 1].f > fNew)
                {
                    cellDetails[i][j - 1].f = fNew;
                    cellDetails[i][j - 1].g = gNew;
                    cellDetails[i][j - 1].h = hNew;
                    cellDetails[i][j - 1].parent_i = i;
                    cellDetails[i][j - 1].parent_j = j;
                    insert_into_OpenList(openList, cellDetails, i, j - 1);
                }
            }
        }
    }
    if (foundTarget == false)
    {
        nextCell_row = source_row;
        nextCell_column = source_column;
    }
}

pair<int, int> nextCellAstar(bool isValid[row][column], int source_row, int source_column, int target_row, int target_column)
{
    Astar(source_row, source_column, target_row, target_column, isValid);
    return make_pair(nextCell_row, nextCell_column);
}
