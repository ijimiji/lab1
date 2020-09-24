/*
    Jahor
    Variant 10
    No rights preserved
*/

#include <iostream>
#include <random> 

using std::cout;
using std::cin;
using std::endl;

// I don't like to think, so I use templates
template <typename A>
void printArray(int N, A array) {
    cout << "[";
    for (int i = 0; i < N; i++) {
        cout << array[i];
        if (i != N - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    // [a, b, c, d, e,...]
}

int main() {
    // Reusable variables
    int choice, arraySize, isRandom;
    while (1) {
        cout << "Enter size of an array." << endl;
        cin >> arraySize;

        if (arraySize < 1){
            cout << "I can't create such array :0" << endl;
            continue;
        }

        int* array = new int[arraySize];

        cout << "Pass 0 if you want to fill array yourself." << endl;
        cout << "Pass 1 if you want randomly filled array." << endl;
        cin >> isRandom;

        switch (isRandom) {
            // Fill array manually
        case (0): {
            for (int i = 0; i < arraySize; i++) {
                cout << "Enter " << i + 1 << "th element: ";
                cin >> array[i];
            }
            break;
        }
                // Fill array with random elements
        case (1): {
            std::random_device rd;
            std::mt19937 mt(rd());
            int minRand, maxRand;
            cout << "Enter min element for random range." << endl;
            cin >> minRand;
            cout << "Enter max element for random range." << endl;
            cin >> maxRand;

            if (minRand > maxRand) {
                std::swap(minRand, maxRand);
            }

            std::uniform_int_distribution<int> dist(minRand, maxRand);

            cout << "Here is array of random elements:" << endl;
            for (int i = 0; i < arraySize; i++) {
                array[i] = dist(mt);
            }

            printArray(arraySize, array);

            break;
        }
        default: {
            cout << "Something is wrong with your input." << endl;
            return 0;
        }
        }

            // Swap first min and max
            if (arraySize > 1) {
                int min = 0;
                int max = 0;
                for (int i = 1; i < arraySize; i++) {
                    if (array[min] > array[i]) {
                        min = i;
                    }
                    if (array[max] < array[i]) {
                        max = i;
                    }
                }
                int t = array[min];
                array[min] = array[max];
                array[max] = t;
                cout << "Here is modified array after swapping:" << endl;
                printArray(arraySize, array);
            }
            else {
                cout << "No reason to swap min and max in one element array." << endl;
            }
        
                // Calculate sum of elements after last last minimal element
            // Find last minimal element
            int min = 0;
            // Dont search for minimal element is one element array
            if (arraySize > 1) {
                for (int i = 1; i < arraySize; i++) {
                    if (array[min] >= array[i]) {
                        min = i;
                    }
                }
            }
            int sum = 0;
            // Calculate sum of elements after min
            if (min != arraySize - 1) {
                for (int i = min + 1; i < arraySize; i++) {
                    sum += array[i];
                }
                cout << "Sum of elements after min is " << sum << "." << endl;
            }
            else {
                cout << "Can't calculate sum of elements after min because min is the last element." << endl;
            }
        

                // Replace negative elements with their squares
                // and print sorted array

            // Replace negative elements with their squares
            for (int i = 0; i < arraySize; i++) {
                if (array[i] < 0) {
                    array[i] = array[i] * array[i];
                }
            }
            // Sort with bubble sort
            for (int i = 0; i < arraySize; i++) {

                for (int j = i + 1; j < arraySize; j++)
                {
                    if (array[j] < array[i]) {
                        std::swap(array[i], array[j]);
                    }
                }
            }
            cout << "Here is sorted array:" << endl;
            printArray(arraySize, array);
            break;
        
        // Free memory
        delete[] array;
    }
}
