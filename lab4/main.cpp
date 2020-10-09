//  Var 10
#include <fstream>
#include <iostream>
#include <sstream>
#define N 300

std::fstream input_fileA("input_a", std::fstream::in);
std::fstream input_fileB("input_b", std::fstream::in);

// 48 for 1 and 57 for 0
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

int countChar(const char *string, char target) {
    int i = 0;
    while (*string) {
        if (*string == target)
            ++i;

        ++string;
    }
    return i;
}

bool strFromDigits(const char *string) {
    bool is_digit = true;
    while (*string) {
        if (!isDigit(*string))
            is_digit = false;
        string++;
    }
    return is_digit;
}

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

int main() {
    std::stringstream ss;
    char last[N];
    char last_but_one[N];
    char word[N];
    char line[N];
    char subWord[N];
    int n = 0, n_max = 0;

    // Task A
    if (input_fileA.is_open()) {
        while (input_fileA.getline(line, N)) {
            ss.str(line);
            ss >> word;
            ss >> subWord;
            std::cout << _strspn(word, subWord) << std::endl;
            ss.clear();
        }
        input_fileA.close();
    } else {
        std::cout << "AAAAAAAA! CANT FIND DATA!" << std::endl;
    }

    // Task B

    if (input_fileB.is_open()) {
        while (input_fileB.getline(line, N)) {
            ss.str(line);
            while (ss >> word) {
                if (strFromDigits(word)) {
                    n = countChar(word, '0');
                    if (n > n_max) {
                        n_max = n;
                        strCopy(word, last);
                        strCopy(last, last_but_one);
                    }
                    if (n == n_max && n != 0) {
                        strCopy(last, last_but_one);
                        strCopy(word, last);
                    }
                }
            }
            if (n_max == 0) {
                std::cout << "No words containing zeros found." << std::endl;
            } else {
                printString(last_but_one);
            }

            n_max = 0;
            n = 0;
            ss.clear();
        }
        input_fileB.close();
    } else {
        std::cout << "AAAAAAAA! CANT FIND DATA!" << std::endl;
    }
}
