#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <sys/cdefs.h>
#include <vector>

bool IsNonIncreasingOrder(std::string str) {
    int n = str.length();
    int k;
    bool isOrd = true;

    char last = str[n - 1];
    for (int i = n - 1; i >= 0; i = i - 2) {
        if (last < str[i]) {
            isOrd = false;
        }
        last = str[i];
    }

    return isOrd;
}

std::string ConsoleReader(std::string msg) {
    std::cout << msg << std::endl;
    std::string str;
    std::cin >> str;
    return str;
}
std::vector<std::string> FileReader(std::string input_file) {
    std::ifstream input(input_file);
    std::vector<std::string> fileContent;
    std::string line;
    while (std::getline(input, line)) {
        fileContent.push_back(line);
    }
    return fileContent;
}

std::vector<std::string> WordParser(std::vector<std::string> lines) {
    std::stringstream ss;
    std::string word;
    std::vector<std::string> words;
    for (std::string line : lines) {
        ss << line;
        while (ss >> word) {
            words.push_back(word);
        }
        ss.clear();
    }

    return words;
}

std::vector<std::string> FindItems(std::vector<std::string> words) {
    std::vector<std::string> matchingWords;
    for (auto word : words) {
        if (IsNonIncreasingOrder(word)) {
            matchingWords.push_back(word);
        }
    }
    return matchingWords;
}

int WordWeight(std::string str) {
    int weight = 0;
    for (auto ch : str) {
        if ((ch & 0b100) && (ch & 0b10000)) {
            weight += (int)ch;
        }
    }
    return weight;
}
template <typename T>
std::map<std::string, T> WordWeight(std::vector<std::string> words) {
    std::map<std::string, T> dict;
    for (auto word : words) {
        dict[word] = WordWeight(word);
    }
    return dict;
}

template <typename T>
void FileWriter(std::map<std::string, T> records, std::string file_name) {
    std::ofstream output(file_name);
    for (auto const &record : records) {
        output.width(50);
        output << std::left << record.first;
        output << std::right << record.second << '\n';
    }
}

void SortCollection(std::vector<std::string> &arr) {

  std::sort(arr.begin(), arr.end(), [](auto x, auto y) {
        return (WordWeight(x) > WordWeight(y));
    });

}

void Encryption(std::string file_path, std::string key) {
    std::stringstream ss(file_path);
    std::string name;
    getline(ss, name, '.');
    std::string new_file_name = name + "_encr.txt";

    char EncryptedChar;

    std::ifstream input(file_path);
    std::ofstream output(new_file_name);
    std::string line;
    int key_length = key.length();
    int i = 0;

    while (std::getline(input, line)) {
        for (char ch : line) {
            EncryptedChar = ch ^ key[i % key_length];
            output << EncryptedChar;
            ++i;
        }
        output << '\n';
        i = 0;
    }
}


int main() {
    auto fileName = ConsoleReader("Enter file name");
    auto fileContent = FileReader(fileName);
    auto words = WordParser(fileContent);
    
    auto matchingWords = FindItems(words);
    
    SortCollection(matchingWords);
    
    auto word_weight_map = WordWeight<int>(matchingWords);
    auto word_weight_map_ch = WordWeight<char>(matchingWords);
    FileWriter<int>(word_weight_map, "output.txt");
    FileWriter<char>(word_weight_map_ch, "output_ch.txt");
    Encryption("output.txt", "jahor");
    Encryption("output_encr.txt", "jahor");
    return 0;
}
