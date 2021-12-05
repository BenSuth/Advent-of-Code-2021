#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

using std::string, std::vector, std::unordered_set;

vector<vector<int>> parse_boards(std::ifstream& file) {
    vector<vector<int>> res;

    if (file) {
        int i = 0;
        int temp;
        vector<int> board;
        while (file >> temp) {
            ++i;
            board.push_back(temp);

            if (i == 25) {
                res.push_back(board);
                i = 0;
                board.clear();
            }
        }
    }

    return res;
}

vector<int> get_numbers(std::ifstream& file) {
    vector<int> res;
    std::stringstream ss;
    string input_string;
    
    if (file) {
        getline(file, input_string);
        int temp;
        ss << input_string;

        while (ss >> temp) {
            ss.get();
            res.push_back(temp);
        }
    }

    return res;
}

bool check_board(vector<int> board) {
    bool winner = false;
    for (int i = 0; i < 25; i += 5) {
        winner = true;
        for (int j = i; j < i + 5; ++j) {
            if (board[j] != -1) {
                winner = false;
                break;
            }
        }
        if (winner) return winner;
        
    }

    for (int i = 0; i < 5; i++) {
        winner = true;
        for (int j = i; j < i + 21; j += 5) {
            if (board[j] != -1) {
                winner = false;
                break;
            }
        }

        if (winner) return winner;
    }

    return false;
}

int sum_board(vector<int> board) {
    int sum = 0;

    for (int& b : board) {
        if (b != -1) sum += b;
    }

    return sum;
}

int day4_part1() {
    std::ifstream file("./inputs/input4.txt");
    
    vector<int> numbers = get_numbers(file);
    vector<vector<int>> boards = parse_boards(file);

    file.close();

    for (int& n : numbers) {
        for (vector<int>& board : boards) {
            for (int& b : board) {
                if (b == n) {
                    b = -1;
                    if (check_board(board)) {
                        return sum_board(board) * n;
                    }
                }
            }
        }
    }

    return 0;
}

int day4_part2() {
    int res = 0;
    std::ifstream file("./inputs/input4.txt");
    
    vector<int> numbers = get_numbers(file);
    vector<vector<int>> boards = parse_boards(file);

    unordered_set<int> unsolved;

    for (int i = 0; i < (int) boards.size(); ++i) {
        unsolved.insert(i);
    }

    file.close();

    for (int& n : numbers) {
        for (int i = 0; i < (int) boards.size(); ++i) {
            for (int& b : boards[i]) {
                if (b == n) {
                    b = -1;
                    if (unsolved.find(i) != unsolved.end() && check_board(boards[i])) {
                        res = sum_board(boards[i]) * n;
                        unsolved.erase(i);
                    }

                    if (unsolved.size() == 0) return res;
                }
            }
        }
    }

    return res;
}

int main(void) {
    std::cout << day4_part1() << " " << day4_part2();
    return 0;
}