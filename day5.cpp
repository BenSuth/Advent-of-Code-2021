#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

using std::string;
using std::vector; 
using std::unordered_set;

vector<vector<int>> parse_input(std::ifstream& file) {
    vector<vector<int>> res;
    int num;

    while (file >> num) {
        vector<int> interval;
        interval.push_back(num);

        file.ignore(1);
        file >> num;
        interval.push_back(num);

        file.ignore(4);
        file >> num;
        interval.push_back(num);
        
        file.ignore(1);
        file >> num;
        interval.push_back(num);

        res.push_back(interval);
    }

    return res;
}

void insert_interval_part1(vector<vector<int>>& intervals, vector<int>& interval, unordered_set<string>& overlap) {
    if (interval[1] == interval[3]) {
        int x1 = std::min(interval[0], interval[2]);
        int x2 = std::max(interval[0], interval[2]);

        for (int i = x1; i <= x2; ++i) {
            intervals[i][interval[1]] += 1;

            if (intervals[i][interval[1]] > 1) overlap.insert(std::to_string(i) + ":" + std::to_string(interval[1]));
            
        }
    } else if (interval[0] == interval[2]) {
        int y1 = std::min(interval[1], interval[3]);
        int y2 = std::max(interval[1], interval[3]);

        for (int i = y1; i <= y2; ++i) {
            intervals[interval[0]][i] += 1;

            if (intervals[interval[0]][i] > 1) overlap.insert(std::to_string(interval[0]) + ":" + std::to_string(i));
            

        }
    }

    return;
}

void insert_interval_part2(vector<vector<int>>& intervals, vector<int>& interval, unordered_set<string>& overlap) {
    int x1 = interval[0];
    int x2 = interval[2];
    int y1 = interval[1];
    int y2 = interval[3];

    int m = (x2 - x1) / (y2 - y1);
    int b = y1 - x1*m;

    x1 = std::min(interval[0], interval[2]);
    x2 = std::max(interval[0], interval[2]);

    for (int i = x1; i <= x2; ++i) {
        intervals[i][i*m + b] += 1;
        if (intervals[i][i*m + b] > 1) overlap.insert(std::to_string(i) + ":" + std::to_string(i*m + b));
    }
    return;
}

int day5_part1() {
    std::ifstream file("./inputs/input5.txt");

    unordered_set<string> overlap;

    vector<vector<int>> line_count(1000, vector<int> (1000, 0));
    vector<vector<int>> intervals = parse_input(file);

    file.close();

    for (vector<int>& interval : intervals) {
        insert_interval_part1(line_count, interval, overlap);
    }

    return overlap.size();
}

int day5_part2() {
    std::ifstream file("./inputs/input5.txt");

    unordered_set<string> overlap;

    vector<vector<int>> line_count(1000, vector<int> (1000, 0));
    vector<vector<int>> intervals = parse_input(file);

    file.close();

    for (vector<int>& interval : intervals) {
        if (interval[0] == interval[2] || interval[1] == interval[3]) insert_interval_part1(line_count, interval, overlap);
        else insert_interval_part2(line_count, interval, overlap);
    }

    return overlap.size();
}


int main(void) {
    std::cout << day5_part1() << " " << day5_part2();
    return 0;
}