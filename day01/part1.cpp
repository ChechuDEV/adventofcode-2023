// Advent of Code 2023 Day 01 Part 1 by Chechu

#include <sstream>
#include <iostream>
#include <fstream>

using std::string, std::ifstream;

int char_to_int(char c);
bool is_letter(char c);
int get_calibration_value(const string &line);
bool test();

int main() {
    std::cout << (test() ? "TEST PASSED" : "TEST NOT PASSED") << std::endl;

    ifstream file("./day01/build/input.txt");

    int total = 0;
    string line;

    file >> line;
    while (!file.eof()) {
        total += get_calibration_value(line);
        file >> line;
    }

    std::cout << "Total result: " << total << std::endl;

    return 0;
}

int get_calibration_value(const string &line) {
    int first = -1;
    int second = -1;
    for (char c: line) {
        if (!is_letter(c)) {
            second = char_to_int(c);
            if (first == -1) first = second * 10;
        }
    }
    return first + second;
}

int char_to_int(char c) {
    return (int) c - '0';
}

bool is_letter(char c) {
    return c >= 'a' && c <= 'z';
}

bool test() {
    string input = "1abc2\n"
                   "pqr3stu8vwx\n"
                   "a1b2c3d4e5f\n"
                   "treb7uchet";

    int expected_output = 142;

    std::istringstream iss(input);

    int total = 0;
    string line;
    iss >> line;
    while (!iss.eof()) {
        total += get_calibration_value(line);
        iss >> line;
    }
    total += get_calibration_value(line);
    // extra line, could group with do while. Because istringstream gets to eof when last string/line is read.

    return total == expected_output;
}