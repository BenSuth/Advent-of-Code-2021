#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

using std::string;
using std::vector; 
using std::cout;


vector<int> parse_input(std::ifstream& file) {
    vector<int> res;
    long num;

    while (file >> num) {
      file.ignore(1);
      res.push_back(num);
    }

    return res;
}

long day6_part1() {
    std::ifstream file("./inputs/input6.txt");
    vector<int> fish = parse_input(file);

    file.close();

    for (int i = 1; i <= 80; ++i) {
        vector<int> update_fish(fish);
        for (int j = 0; j < (int) fish.size(); ++j) {
            if (fish[j] == 0) {
                update_fish.push_back(8);
                update_fish[j] = 6;
            } else {
                update_fish[j] = fish[j] - 1;
            }
        }
        fish.swap(update_fish);
        vector<int>().swap(update_fish);
    }

    return fish.size();
}

unsigned long long day6_part2() {
    std::ifstream file("./inputs/input6.txt");
    vector<int> fish = parse_input(file);

    file.close();

    vector<unsigned long long> ages(9, 0);
    
    for (int& f : fish) {
        ages[f] += 1;
    }

    for (int i = 1; i <= 256; ++i) {
        std::rotate(ages.begin(), ages.begin() + 1, ages.end());
        ages[6] += ages[8];
    }

    return std::accumulate(ages.begin(), ages.end(), (unsigned long long) 0);
}


int main(void) {
    std::cout << day6_part1() << " " << day6_part2();
    return 0;
}