#include <sstream>
#include <iostream>
#include <fstream>

using std::string, std::ifstream, std::istream;

bool test();
int process_input(istream &in);

int main() {
    std::cout << (test() ? "TEST PASSED" : "TEST NOT PASSED") << std::endl;

    ifstream file("./day02/build/input.txt"); // Running build from src
    if (!file.is_open()) file.open("../day02/input.txt"); // CMake debug run
    if (!file.is_open()) return 1;

    int result = process_input(file);
    std::cout << result;
    return result;
}

bool test() {
    string input = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green\n"
                   "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue\n"
                   "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red\n"
                   "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red\n"
                   "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green";

    int expected_output = 2286;

    std::istringstream iss(input);
    int output = process_input(iss);

    return output == expected_output;
}

int process_input(istream &in) {
    int output = 0;

    int blue = 0;
    int green = 0;
    int red = 0;

    string word;
    int num = 0;

    in >> word;
    while (!in.fail()) {
        if (word == "Game") {
            in >> word >> num >> word; // '1:' goes to void :)
        } else {
            char &color = word[0];
            if (color == 'r' && num > red) red = num;
            else if (color == 'g' && num > green) green = num;
            else if (color == 'b' && num > blue) blue = num;

            char &lastChar = word[word.length() - 1];
            if (lastChar != ',' && lastChar != ';') {
                output += red * green * blue;
                red = 0;
                green = 0;
                blue = 0;
                in >> word; // next game
            } else {
                in >> num >> word; // next color
            }
        }
    }
    return output;
}