#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using std::string;

int day2_part1() {
    int pos = 0, depth = 0;
    string line;

    std::ifstream file("./inputs/input2.txt");

    if (file) {
        while (getline(file, line, '\n')) {
            std::stringstream ss;
            string direction = "";
            int distance = 0;

            ss << line;
            ss >> direction;
            ss >> distance;

            if (direction == "forward") pos += distance;
            else if (direction == "down") depth += distance;
            else if (direction == "up") depth -= distance;
        }
    }
    return pos*depth;
}

int day2_part2() {
    int pos = 0, depth = 0, aim = 0;
    string line;

    std::ifstream file("./inputs/input2.txt");

    if (file) {
        while (getline(file, line, '\n')) {
            std::stringstream ss;
            string direction = "";
            int distance = 0;

            ss << line;
            ss >> direction;
            ss >> distance;

            if (direction == "forward") {
                pos += distance;
                depth += distance * aim;
            }
            else if (direction == "down") aim += distance;
            else if (direction == "up") aim -= distance;
        }
    }
    return pos*depth;
}

int main(void) {
    std::cout << day2_part1() << "\n" << day2_part2();
}