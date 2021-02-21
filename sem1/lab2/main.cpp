/*
    Jahor
    Variant 10
    No rights preserved
*/

#define N_MAX 20
#include <cmath>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

double fRand(double fMin, double fMax) {
  double f = (double)rand() / RAND_MAX;
  return fMin + f * (fMax - fMin);
}

// I know that array's type in this lab is double *
// But I like things to be polymorphic
template <typename A> void printArray(int N, A array) {
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
  cout << "Enter size of an array." << endl;
  cout << "Size must be less than " << N_MAX + 1 << ", bigger than 0." << endl;
  cin >> arraySize;

  if (arraySize > N_MAX || arraySize < 1) {
    cout << "I can't create such array :0" << endl;
    cout << "I will use the default (" << N_MAX << ")" << endl;
  }

  double *array = new double[arraySize];

  cout << "Pass 0 if you want to fill array yourself." << endl;
  cout << "Pass 1 if you want randomly filled array." << endl;
  cin >> isRandom;

  if (isRandom) {
    // Fill randomly
    double minRand, maxRand;

    cout << "Enter min element for random range." << endl;
    cin >> minRand;
    cout << "Enter max element for random range." << endl;
    cin >> maxRand;

    if (minRand > maxRand) {
      std::swap(minRand, maxRand);
    }

    for (int i = 0; i < arraySize; i++) {
      array[i] = fRand(minRand, maxRand);
    }

    cout << "Here is array of random elements:" << endl;
    printArray(arraySize, array);

  } else {
    // Fill array manually
    for (int i = 0; i < arraySize; i++) {
      cout << "Enter elements (a b c d ...): ";
      cin >> array[i];
    }
    cout << "Here is array of your elements:" << endl;
    printArray(arraySize, array);
  }

  // Swap first min and max
  int min = 0;
  if (arraySize != 1) {
    int max = 0;
    for (int i = 1; i < arraySize; i++) {
      if (std::abs(array[min]) > std::abs(array[i])) {
        min = i;
      }
      if (std::abs(array[max]) < std::abs(array[i])) {
        max = i;
      }
    }
    int t = array[min];
    array[min] = array[max];
    array[max] = t;
    cout << "Here is modified array after swapping:" << endl;
    printArray(arraySize, array);
  } else {
    cout << "No reason to swap min and max in 1 element array" << endl;
  }

  // Calculate sum of elements after last last minimal element
  // Find last minimal element
  min = 0;
  if (arraySize > 1) {
    for (int i = 1; i < arraySize; i++) {
      if (std::abs(array[min]) >= std::abs(array[i])) {
        min = i;
      }
    }
  }

  // Calculate sum of elements after min
  double sum = 0;
  if (min != arraySize - 1) {
    for (int i = min + 1; i < arraySize; i++) {
      sum += array[i];
    }
    cout << "Sum of elements after min is " << sum << "." << endl;
  } else {
    cout << "Can't calculate sum of elements after min because min is the "
            "last element."
         << endl;
  }

  // Replace negative elements with their squares
  // and print sorted array

  for (int i = 0; i < arraySize; i++) {
    if (array[i] < 0) {
      array[i] = array[i] * array[i];
    }
  }
  // Sort with bubble sort
  for (int i = 0; i < arraySize; i++) {

    for (int j = i + 1; j < arraySize; j++) {
      if (array[j] < array[i]) {
        std::swap(array[i], array[j]);
      }
    }
  }
  cout << "Here is sorted array:" << endl;
  printArray(arraySize, array);

  // Free memory
  delete[] array;
}

