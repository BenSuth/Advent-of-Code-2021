#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

using std::string;
using std::vector; 
using std::cout;


vector<int> parse_input() {
    std::ifstream file("./inputs/input7.txt");
    vector<int> res;
    if (file) {
        int num;
        while (file >> num) {
            file.ignore(1);
            res.push_back(num);
        }
    }

    file.close();

    return res;
}

int day7_part1() {
    vector<int> crabs = parse_input();

    std::sort(crabs.begin(), crabs.end());

    int m = crabs[crabs.size()/2];

    return std::accumulate(crabs.begin(), crabs.end(), 0, [&m](int a, int b) {
        return a + std::abs(b - m);
    });
}

int day7_part2() {
    vector<int> crabs = parse_input();
    int m = std::accumulate(crabs.begin(), crabs.end(), 0) / crabs.size();

    return std::accumulate(crabs.begin(), crabs.end(), (long) 0, [&m](int a, int b) {
        int x = std::abs(b - m);
        return a + (x*(x+1))/2;
    });

    return 0;
}




int main(void) {
    std::cout << day7_part1() << " " << day7_part2();
    return 0;
}