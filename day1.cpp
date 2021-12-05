#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using std::string, std::queue;

int day1_part1() {
    string line;
    int n1, n2, count = 0;

    std::ifstream file("./inputs/input1.txt");
    if (file.is_open()) {
        getline(file, line);
        n1 = stoi(line);

        while (getline(file, line)) {
            n2 = stoi(line);

            if (n2 - n1 > 0) ++count;
            
            n1 = n2;
        }

        file.close();
    }

    return count;
}

int day1_part2() {
    int count = 0, window_size = 0, new_window_size;
    string line;
    queue<int> window;

    std::ifstream file("./inputs/input1.txt");

    if (file.is_open()) {
        int curr;
        for (int i = 0; i < 3; ++i) {
            getline(file, line);
            curr = stoi(line);

            window_size += curr;
            window.push(curr);
        }

        while (getline(file, line)) {
            curr = stoi(line);
            new_window_size = window_size + curr - window.front();
            
            if (new_window_size - window_size > 0) ++count;

            window.pop();
            window.push(curr);    
            
            window_size = new_window_size;
        }

        file.close();
    }

    return count;
}

int main(void) {
    std::cout << day1_part1() << "\n" << day1_part2();
}