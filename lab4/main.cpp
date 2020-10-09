//  Var 10
#include <fstream>
#include <iostream>
#include <vector>
#define N 300

int _strspn(const char *string, const char *strCharSet) {
    int n;
    const char *copy;
    for (n = 0; *string; string++, n++) {
        for (copy = strCharSet; *copy && *copy != *string; ++copy)
            ;
        if (!*copy)
            break;
    }
    return n;
}

void printString(const char *string) {
    while (*string) {
        std::cout << *string;
        ++string;
    }
    std::cout << std::endl;
}

// 48 for '1' and 57 for '0' in ASCII
bool isDigit(char ch) {
    return ((int)ch >= 48 && (int)ch <= 57) ? true : false;
}

void strCopy(char *source, char *dest) {
    int i = 0;
    while (*source) {
        dest[i] = *source;
        ++i, ++source;
    }
    dest[i] = '\0';
}

bool strIsMadeOfDigits(const char *string) {
    bool is_digit = true;
    while (*string) {
        if (!isDigit(*string))
            is_digit = false;
        string++;
    }
    return is_digit;
}

int countChar(const char *string, char target) {
    int i = 0;
    while (*string) {
        if (*string == target)
            ++i;

        ++string;
    }
    return i;
}

int countWordsInLine(char *string) {
    int n = 0;
    bool last_is_space = true;
    while (*string) {
        if (*string != ' ') {
            if (last_is_space)
                ++n;
            last_is_space = false;
        } else {
            last_is_space = true;
        }
        ++string;
    }
    return n;
}

std::vector<int> countWordsInFile(const char *file) {
    std::vector<int> arr;
    char line[N];
    std::fstream fin(file);
    if (fin.is_open()) {
        while (fin.getline(line, N)) {
            arr.push_back(countWordsInLine(line));
        }
    }
    fin.close();
    return arr;
}

void findWordWithMaxZeros(char *word, int &n, int &n_max, char *last,
                          char *last_but_one) {
    if (strIsMadeOfDigits(word)) {
        n = countChar(word, '0');
        if (n > n_max) {
            n_max = n;
            strCopy(last, last_but_one);
            strCopy(word, last);
        }
        if (n == n_max && n != 0) {
            strCopy(last, last_but_one);
            strCopy(word, last);
        }
    }
}

int main() {
    char word[N];
    char subWord[N];
    char line[N];
    char last[N];
    char last_but_one[N];
    int n = 0, n_max = 0;

    std::vector<int> amountOfWordsInFile;

    std::fstream input_fileA("input_a", std::fstream::in);
    std::fstream input_fileB("input_b", std::fstream::in);

    // Task A
    amountOfWordsInFile = countWordsInFile("input_a");
    for (auto amountOfWordsInLine : amountOfWordsInFile) {
        input_fileA >> word;
        input_fileA >> subWord;
        std::cout << _strspn(word, subWord) << std::endl;
    }
    input_fileA.close();

    // Task B
    amountOfWordsInFile = countWordsInFile("input_b");
    for (auto wN : amountOfWordsInFile) {
        for (int i = 0; i < wN; ++i) {
            input_fileB >> word;
            findWordWithMaxZeros(word, n, n_max, last, last_but_one);
        }
        if (n_max == 0) {
            std::cout << "No words with zeros are found" << std::endl;
        } else
            printString(last_but_one);

        n = 0;
        n_max = 0;
    }
    input_fileB.close();
}
