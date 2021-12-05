#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

using std::string, std::vector, std::unordered_set;

int day3_part1() {
    string gamma = "", alpha = "";
    int size;
    string line;
    vector<int> freq(12, 0);

    std::ifstream file("./inputs/input3.txt");

    if (file) {
        while (getline(file, line, '\n')) {
            ++size;
            for (int i = 0; i < (int) line.size(); ++i) {
                if (line[i] == '1') {
                    freq[i] += 1;
                }
            }
        }

        file.close();
    }

    for (int& i : freq) {
        if (i >= size/2) {
            gamma += "1";
            alpha += "0";
        } else {
            gamma += "0";
            alpha += "1";
        }
    }

    return stol(gamma, nullptr, 2) * stol(alpha, nullptr, 2);
}

int day3_part2() {
    string oxygen = "", co2 = "";
    unordered_set<int> oxygen_index, co2_index;
    int size;
    string line;
    vector<string> transposed(12, "");

    std::ifstream file("./inputs/input3.txt");

    if (file) {
        while (getline(file, line, '\n')) {
            ++size;
            for (int i = 0; i < (int) line.size(); ++i) {
                transposed[i] += line[i];
            }
        }
        file.close();
    }

    for (int i = 0; i < (int) transposed[0].size(); ++i) {
        oxygen_index.insert(i);
        co2_index.insert(i);
    }

    for (int i = 0; i < (int) transposed.size(); ++i) {
        int freq_oxygen = 0;
        int freq_co2 = 0;
        
        for (int j = 0; j < (int) transposed[i].size(); ++j) {
            if (oxygen_index.find(j) != oxygen_index.end() && transposed[i][j] == '1') ++freq_oxygen;
            if (co2_index.find(j) != co2_index.end() && transposed[i][j] == '1') ++freq_co2;
        }

        if (oxygen_index.size() > 1) {
            if (freq_oxygen >= (int) oxygen_index.size() - freq_oxygen) oxygen += '1';
            else oxygen += '0';
            for (int j = 0; j < (int) transposed[i].size(); ++j) {
                if (transposed[i][j] != oxygen[i]) oxygen_index.erase(j);
            }
        }   

        if (co2_index.size() > 1) {
            if (freq_co2 >= (int) co2_index.size() - freq_co2) co2 += '0';
            else co2 += '1';
            for (int j = 0; j < (int) transposed[i].size(); ++j) {
            if (transposed[i][j] != co2[i]) co2_index.erase(j);
            }
        }   
    }

    oxygen = "";
    co2 = "";

    for (int i = 0; i < (int) transposed.size(); ++i) {
        oxygen += transposed[i][*oxygen_index.begin()];
        co2 += transposed[i][*co2_index.begin()];
    }

    return stol(oxygen, nullptr, 2) * stol(co2, nullptr, 2);
}

int main(void) {
    std::cout << day3_part1() << "\n" << day3_part2();
}