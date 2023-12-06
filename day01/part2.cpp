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
    if (!file.is_open()) file.open("input.txt");
    if (!file.is_open()) return 1;

    int total = 0;
    string line;
    file >> line;
    while (!file.eof()) {
        total += get_calibration_value(line);
        file >> line;
    }

    std::cout << "Total result: " << total << std::endl;
    file.close();
    return 0;
}

int min(int a, int b) {
    int min = a;
    if (b < a) min = b;
    return min;
}

int get_number(string &possible) {
    if (possible == "eight") return 8;
    if (possible == "seven") return 7;
    if (possible == "three") return 3;
    possible = possible.substr(0, 4);
    if (possible == "nine") return 9;
    if (possible == "five") return 5;
    if (possible == "four") return 4;
    possible = possible.substr(0, 3);
    if (possible == "six") return 6;
    if (possible == "two") return 2;
    if (possible == "one") return 1;
    return 0;
}

int get_calibration_value(const string &line) {
    int first = -1;
    int second = -1;
    int len = (int) line.length();
    for (int i = 0; i < len; i++) {
        char c = line[i];
        int num;
        if (is_letter(c)) {
            int cut = min(len - i + 5, 5);
            string possible = line.substr(i, cut);
            num = get_number(possible);
        } else {
            num = char_to_int(c);
        }
        if (num != 0) {
            second = num;
            if (first == -1) first = num * 10;
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
    string input = "two1nine\n"
                   "eightwothree\n"
                   "abcone2threexyz\n"
                   "xtwone3four\n"
                   "4nineeightseven2\n"
                   "zoneight234\n"
                   "7pqrstsixteen";

    int expected_output = 281;

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