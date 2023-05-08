#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
using namespace std::chrono;

struct Transform
{
    float matrix[16] =
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
};

class GameObject3D
{
public:
    Transform transform;
    int ID;
};

class GameObject3DAlt
{
public:
    Transform* transform;
    int ID;
};

std::vector<float> measures;
std::vector<float> allFirstOperations;
bool alt{};


void LoopClass()
{
    const int arraySize = 10'000'000;
    GameObject3D* largeArray = nullptr;
    GameObject3DAlt* largeArrayAlt = nullptr;

    if(alt)
    {
        largeArrayAlt = new GameObject3DAlt[arraySize]{};
    }
    else
    {
        largeArray = new GameObject3D[arraySize]{};
    }

    for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
    {
        auto start = high_resolution_clock::now();

        if(alt)
        {
            for (int i = 0; i < arraySize; i += stepSize)
            {
                largeArrayAlt[i].ID += 2;
            }
        }
        else
        {
            for (int i = 0; i < arraySize; i += stepSize)
            {
                largeArray[i].ID += 2;
            }
        }

        auto end = high_resolution_clock::now();
        auto elapsedTime = duration_cast<microseconds>(end - start).count();
        std::cout << "Operation took " << elapsedTime << "ms\n";
        measures.push_back(static_cast<float>(elapsedTime));
    }

    std::cout << std::endl;
    delete[] largeArray;
    delete[] largeArrayAlt;
}

void LoopInt()
{
    const int arraySize = 67'108'864;
    int* largeArray = new int[arraySize] {};

    for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
    {
        auto start = high_resolution_clock::now();

        for (int i = 0; i < arraySize; i += stepSize)
        {
            largeArray[i] += 2;
        }

        auto end = high_resolution_clock::now();
        auto elapsedTime = duration_cast<microseconds>(end - start).count();
        std::cout << "Operation took " << elapsedTime << "ms\n";
        measures.push_back(static_cast<float>(elapsedTime));
    }
    std::cout << std::endl;
    delete[] largeArray;
}

float CalcAverage(int nr)
{
    for (int i{ nr }; i < static_cast<int>(measures.size()); i += 11)
    {
        allFirstOperations.push_back(measures[i]);
    }

    allFirstOperations.erase(std::min_element(allFirstOperations.begin(), allFirstOperations.end()));
    allFirstOperations.erase(std::max_element(allFirstOperations.begin(), allFirstOperations.end()));
    //---------------------------------------------------------------------------------------------------

    return std::accumulate(allFirstOperations.begin(), allFirstOperations.end(), 0.f) / allFirstOperations.size();
}
