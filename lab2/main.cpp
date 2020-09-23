#include <iostream>
#include <random> 

using std::cout;
using std::cin;
using std::endl;

int main() {
    int choice, arraySize, isRandom;
    while (1) {
        cout << "Enter size of an array ";
        cin >> arraySize;

        int* array = new int[arraySize];
        cout << "Pass 0 if you want to fill array yourself." << endl;
        cout << "Pass 1 if you want randomly filled array ";
        cin >> isRandom;
        switch (isRandom) {
        case (0): {
            for (int i = 0; i < arraySize; i++) {
                cout << "Enter " << i+1 << "th element ";
                cin >> array[i];
            }
            break;
        }
        case (1): {
            std::random_device rd;
            std::mt19937 mt(rd());
            int minRand, maxRand;
            cout << "Enter min element for random range ";
            cin >> minRand;
            cout << "Enter max element for random range ";
            cin >> maxRand;

            if (minRand > maxRand){
                std::swap(minRand, maxRand);
            }

            std::uniform_int_distribution<int> dist(minRand, maxRand);

            for (int i = 0; i < arraySize; i++) {
                array[i] = dist(mt);
                std::cout << array[i] << endl;
            }
            break;
        }
        default: {
            cout << "Something is wrong with your input." << endl;
            return 0;
        }
        }

        cout << "Enter number of task you want to check (pass 0 to exit) ";
        cin >> choice;
        switch (choice) {
        case (1): {
            break;
        }
        case (2): {
            break;
        }
        case (3): {
            break;
        }
        case (0): {
            return 0;
        }
                defaut: {
                cout << "No such task is present" << endl;
                break;
        }
        }
        delete[] array;
    }
    return 0;
}