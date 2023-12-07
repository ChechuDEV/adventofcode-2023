#include <sstream>
#include <iostream>
#include <fstream>
#include <chrono>

using std::string, std::ifstream, std::istream;

bool test();
int process_input(istream &in);

int main() {
    std::cout << (test() ? "TEST PASSED" : "TEST NOT PASSED") << std::endl;


    ifstream file("./day02/build/input.txt");
    if (!file.is_open()) file.open("../day02/input.txt");
    if (!file.is_open()) return -1;

    int output = process_input(file);

    std::cout << output << std::endl;
    return 0;
}

bool test() {
    string input = "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green\n"
                   "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue\n"
                   "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red\n"
                   "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red\n"
                   "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green";
    int expected_output = 8;

    std::istringstream iss(input);
    int output = process_input(iss);

    return output == expected_output;
}

int process_input(istream &in) {
    int output = 0;
    char next; // void-like

    int id = 0;
    bool possible = true;

    string word;
    int num = 0;

    in >> word;
    while (!in.fail()) {
        if (word == "Game") {
            in >> id >> next >> num >> word;
            // ':' goes to void :)
        } else {
            char &color = word[0];
            int max = 12;
            if (color == 'g') max++;
            else if (color == 'b') max += 2;
            if (num > max) possible = false;

            char &l = word[word.length() - 1];
            if (l != ',' && l != ';') {
                if (possible) output += id;
                possible = true;
                in >> word; // next game
            } else {
                in >> num >> word; // next color
            }
        }
    }
   return output;
}