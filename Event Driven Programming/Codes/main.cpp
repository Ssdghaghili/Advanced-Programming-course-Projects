#include<iostream>
#include<vector>
#include<string>
#include "./src/rsdl.hpp"
#include "Game.h"

int main() {
    ifstream input_file;
    input_file.open("input.txt");
    int num_of_levels;
    int width = 10, length = 10;
    Game game;
    game.run();
} 