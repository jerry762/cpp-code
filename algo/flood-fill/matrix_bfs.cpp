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
void BFSMatrix(std::array<std::array<value, COLUMN>, ROW> &arr, std::pair<int, int> start_point);

int main()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);

    std::uniform_int_distribution<int> distRow(0, ROW - 1);
    std::uniform_int_distribution<int> distColumn(0, COLUMN - 1);

    std::array<std::array<value, COLUMN>, ROW> arr;

    // BFSMatrix(arr, std::make_pair(distRow(gen), distColumn(gen))); //* random
    BFSMatrix(arr, std::make_pair(ROW / 2, COLUMN / 2)); //* center

    system("pause");
    return 0;
}

void BFSMatrix(std::array<std::array<value, COLUMN>, ROW> &arr, std::pair<int, int> start_point)
{
    CONSOLE_CURSOR_INFO ci;
    int count = 0;

    stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleCursorInfo(stdHandle, &ci);
    ci.bVisible = false;
    SetConsoleCursorInfo(stdHandle, &ci);

    coord.X = 0;
    coord.Y = 0;

    std::queue<std::pair<int, int>> queue;

    queue.push(start_point);

    arr.at(start_point.first).at(start_point.second).isVisited = true;

    printMatrix(arr);

    while (!queue.empty())
    {
        std::pair<int, int> temp = queue.front();

        queue.pop();

        if (temp.first - 1 >= 0 && !arr.at(temp.first - 1).at(temp.second).isVisited)
        {
            queue.push(std::make_pair(temp.first - 1, temp.second));
            arr.at(temp.first - 1).at(temp.second).isVisited = true;
            printMatrix(arr);
        }

        if (temp.first + 1 < ROW && !arr.at(temp.first + 1).at(temp.second).isVisited)
        {
            queue.push(std::make_pair(temp.first + 1, temp.second));
            arr.at(temp.first + 1).at(temp.second).isVisited = true;
            printMatrix(arr);
        }

        if (temp.second - 1 >= 0 && !arr.at(temp.first).at(temp.second - 1).isVisited)
        {
            queue.push(std::make_pair(temp.first, temp.second - 1));
            arr.at(temp.first).at(temp.second - 1).isVisited = true;
            printMatrix(arr);
        }

        if (temp.second + 1 < COLUMN && !arr.at(temp.first).at(temp.second + 1).isVisited)
        {
            queue.push(std::make_pair(temp.first, temp.second + 1));
            arr.at(temp.first).at(temp.second + 1).isVisited = true;
            printMatrix(arr);
        }

        if (temp.first - 1 >= 0 && temp.second - 1 >= 0 && !arr.at(temp.first - 1).at(temp.second - 1).isVisited)
        {
            queue.push(std::make_pair(temp.first - 1, temp.second - 1));
            arr.at(temp.first - 1).at(temp.second - 1).isVisited = true;
            printMatrix(arr);
        }

        if (temp.first - 1 >= 0 && temp.second + 1 < COLUMN && !arr.at(temp.first - 1).at(temp.second + 1).isVisited)
        {
            queue.push(std::make_pair(temp.first - 1, temp.second + 1));
            arr.at(temp.first - 1).at(temp.second + 1).isVisited = true;
            printMatrix(arr);
        }

        if (temp.first + 1 < ROW && temp.second - 1 >= 0 && !arr.at(temp.first + 1).at(temp.second - 1).isVisited)
        {
            queue.push(std::make_pair(temp.first + 1, temp.second - 1));
            arr.at(temp.first + 1).at(temp.second - 1).isVisited = true;
            printMatrix(arr);
        }

        if (temp.first + 1 < ROW && temp.second + 1 < COLUMN && !arr.at(temp.first + 1).at(temp.second + 1).isVisited)
        {
            queue.push(std::make_pair(temp.first + 1, temp.second + 1));
            arr.at(temp.first + 1).at(temp.second + 1).isVisited = true;
            printMatrix(arr);
        }

        ++count;
    }
    std::cout << count << " rounds." << std::endl;
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