#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "posix_only.h++"

#include <string>
#include <vector>

static const std::string APPLE = "*";

bool inited = false;

long int score = 0;

std::vector<std::vector<int>> snake;
int_fast8_t vector_y = 0;
int_fast8_t vector_x = 1;


void create_snake () {
    std::vector<int> pos = {get_terminal_height() / 2, get_terminal_width() / 2};
    snake.push_back(pos);
    pos = {get_terminal_height() / 2, get_terminal_width() / 2 - 1};
    snake.push_back(pos);
}


#endif //GAME_LOGIC_H
