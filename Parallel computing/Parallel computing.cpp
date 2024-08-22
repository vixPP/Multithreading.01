#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

static void sumVectors(double sumOfVectors, const vector<int> newVector1, const vector<int> newVector2)
{
    for (int i = 0; i < newVector1.size(); ++i)
    {
        sumOfVectors += newVector1.at(i) + newVector2.at(i);
    }
}

int main() 
{
    
    std::cout << "Количество аппаратных ядер: " << thread::hardware_concurrency() << "\n\n";
    std::cout <<"\t\t 1000" << "\t    10000" << "\t100000" << "\t     1000000" << "\n";

    vector<int> vector1;
    vector<int> vector2;
    vector<int> numOfThreads{ 1, 2, 4, 8, 16 };
    vector<int> sizeOfVector{ 1000, 10000, 100000, 1000000 };

    for (auto& countThread : numOfThreads)
    {
        if (countThread == 1)
        {
            std::cout << endl << countThread << " поток    | ";
        }
        else if (countThread == 2 || countThread == 4)
        {
            std::cout << endl << countThread << " потока   |";
        }
        else if (countThread == 8)
        {
            std::cout << endl << countThread << " потоков  |";
        }
        else 
        {
            std::cout << endl << countThread << " потоков |";
        }

        for (auto& countVector : sizeOfVector)
        {
            vector1.resize(countVector, 1);
            vector2.resize(countVector, 2);
            vector<thread> threads;
            double sumOfVectors = 0;

            int partOfTheSize = static_cast<int>(countVector / countThread);

            auto start = chrono::high_resolution_clock::now();
            for (int i = 0; i < countThread; i++)
            {
                vector<int> newVector1;
                vector<int> newVector2;
                int rightBorder = 0;

                if (i != countThread - 1)
                {
                    rightBorder = partOfTheSize * (i + 1);
                }
                else
                {
                    rightBorder = countVector;
                }

                for (int j = partOfTheSize * i; j < rightBorder; ++j)
                {
                    newVector1.push_back(vector1.at(j));
                    newVector2.push_back(vector2.at(j));
                }
                threads.push_back(thread(sumVectors, ref(sumOfVectors), newVector1, newVector2));
            }
            for (auto& it : threads)
            {
                it.join();
            }

            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double, milli> totalTime = end - start;
            std::cout << "  |" << totalTime.count() << "ms|";
        }
        std::cout << "\n\n";
    }
    return 0;
}