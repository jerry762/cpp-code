#include <iostream>
#include <queue>
#include <array>
#include <chrono>
#include <random>
#include <utility>
#include <Windows.h>
#include <cstdlib>

#define ROW 20
#define COLUMN 20
#define SPEED 1000 //* 1000 = 1s

HANDLE stdHandle;
COORD coord;


struct value
{
    int data = 0;
    bool isVisited = false;
};

void printMatrix(std::array<std::array<value, COLUMN>, ROW> &arr);

//* right -> down -> left -> up
void DFSMatrix(std::array<std::array<value, COLUMN>, ROW> &arr, std::pair<int, int> point);

int main()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);

    std::uniform_int_distribution<int> distRow(0, ROW - 1);
    std::uniform_int_distribution<int> distColumn(0, COLUMN - 1);

    std::array<std::array<value, COLUMN>, ROW> arr;


    CONSOLE_CURSOR_INFO ci;

    stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleCursorInfo(stdHandle, &ci);
    ci.bVisible = false;
    SetConsoleCursorInfo(stdHandle, &ci);

    coord.X = 0;
    coord.Y = 0;


    // DFSMatrix(arr, std::make_pair(distRow(gen), distColumn(gen))); //* random
    DFSMatrix(arr, std::make_pair(0, 0)); //* start at top-left corner

    system("pause");
    return 0;
}

void DFSMatrix(std::array<std::array<value, COLUMN>, ROW> &arr, std::pair<int, int> point)
{
    arr.at(point.first).at(point.second).isVisited = true;

    printMatrix(arr);

    if (point.second + 1 < COLUMN && !arr.at(point.first).at(point.second + 1).isVisited)
        DFSMatrix(arr, std::make_pair(point.first, point.second + 1));

    if (point.first + 1 < ROW && !arr.at(point.first + 1).at(point.second).isVisited)
        DFSMatrix(arr, std::make_pair(point.first + 1, point.second));

    if (point.second - 1 >= 0 && !arr.at(point.first).at(point.second - 1).isVisited)
        DFSMatrix(arr, std::make_pair(point.first, point.second - 1));

    if (point.first - 1 >= 0 && !arr.at(point.first - 1).at(point.second).isVisited)
        DFSMatrix(arr, std::make_pair(point.first - 1, point.second));
}

void printMatrix(std::array<std::array<value, COLUMN>, ROW> &arr)
{
    SetConsoleCursorPosition(stdHandle, coord);

    for (const auto &i : arr)
    {
        for (const value &j : i)
        {
            if (j.isVisited)
                std::cout << j.data << " ";
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }

    Sleep(SPEED / 100);
}