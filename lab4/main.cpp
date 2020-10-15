//  Var 10
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
#define N 300

int strLen(char *string) {
    int n = 0;
    while (*string) {
        ++n;
        ++string;
    }
    return n;
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

void wordFromIndex(char *source, char *dest, std::pair<int, int> start_end) {
    int start = std::get<0>(start_end);
    int end = std::get<1>(start_end);

    int i, j;
    for (i = start, j = 0; i <= end; ++i, ++j) {
        dest[j] = source[i];
    }
    dest[j] = '\0';
}

std::vector<std::pair<int, int>> cutLine(char *line) {
    bool last_is_space = true;
    int start = 0;
    int end = 0;
    int n = strLen(line);
    std::vector<std::pair<int, int>> wordInds;

    for (int i = 0; i < n; ++i) {
        if (line[i] != ' ' && last_is_space) {
            start = i;
            last_is_space = false;
        }
        if (line[i] == ' ' && !last_is_space) {
            end = i - 1;
            wordInds.push_back(std::make_pair(start, end));
            last_is_space = true;
        }
        if (i == n - 1 && start > end) {
            end = i;
            wordInds.push_back(std::make_pair(start, end));
        }
    }

    return wordInds;
}

int main() {
    char word[N];
    char subWord[N];
    char line[N];
    char last[N];
    char last_but_one[N];
    int n = 0, n_max = 0;
    std::vector<std::pair<int, int>> wordInds;

    std::fstream input_fileA("input_a", std::fstream::in);
    std::fstream input_fileB("input_b", std::fstream::in);

    // Task A

    while (input_fileA.getline(line, N)) {
        wordInds = cutLine(line);
        wordFromIndex(line, word, wordInds[0]);
        wordFromIndex(line, subWord, wordInds[1]);
        std::cout << _strspn(word, subWord) << std::endl;
    }

    input_fileA.close();

    // Task B
    while (input_fileB.getline(line, N)) {
        wordInds = cutLine(line);
        for (std::pair<int, int> wordInd : wordInds) {
            wordFromIndex(line, word, wordInd);
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
