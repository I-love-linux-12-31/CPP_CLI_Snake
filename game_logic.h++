#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "posix_only.h++"

#include <string>
#include <vector>
#include "logs.h++"
#include "input_control.h++"


static const std::string APPLE = "*";

bool inited = false;

long int score = 0;

int fruit_time = 5;


int snake[100000000][2]; // Y X
unsigned int snake_len = 0;

int fruits[1000][3]; // Y X Level
unsigned int fruits_len = 1000;
unsigned int fruits_index = 0;

int vector_y = 0;
int vector_x = 1;

int game_sleep_time_ms = 500000; // start = 500000 Hardcore = 60000 bad_render_speed = 55000 MAX_SPEED = 57000


void create_snake () {
    snake[0][0] = (get_terminal_height() / 2);
    snake[0][1] =  (get_terminal_width() / 2) - 1;
    snake_len += 1;

}

void create_fruits () {
    for (unsigned int i = 0; i < 1000; i++) {
        fruits[i][0] = (int) random() % (get_terminal_height()) - 3;
        fruits[i][1] = (int) random() % (get_terminal_width()) - 3;
        if (fruits[i][0] < 3){
            fruits[i][0] += 6;
        }
        if (fruits[i][1] < 3){
            fruits[i][1] += 6;
        }
        fruits[i][2] = (int) random() % 5;
    }

}


void do_movement (bool next_level) {
    if (!next_level) {
        for (unsigned int i = snake_len - 1; i > 0; i--) {
            // logs::log_stream << "Reading address :" << i - 1 << std::endl;
            snake[i][0] = snake[i - 1][0];
            snake[i][1] = snake[i - 1][1];
        }
        snake[0][0] = vector_y + snake[0][0];
        snake[0][1] = vector_x + snake[0][1];

        logs::log_stream << "Do movement (Snake len = " << snake_len << "):" << snake[0][0] << "::" << snake[0][1]
                         << std::endl;
    }
    else {
        for (unsigned int i = snake_len; i > 0; i--) {
            // logs::log_stream << "Reading address :" << i - 1 << std::endl;
            snake[i][0] = snake[i - 1][0];
            snake[i][1] = snake[i - 1][1];
        }
        snake_len += 1;
        snake[0][0] = vector_y + snake[0][0];
        snake[0][1] = vector_x + snake[0][1];
    }

}

bool die_on_next_move () {
    if (vector_x > 0){
        if (snake[0][1] >= get_terminal_width() - 2){
            logs::log_stream << "Die on next move : A" << std::endl;
            return true;
        }
    }
    if (vector_x < 0){
        if (snake[0][1] <= 2){
            logs::log_stream << "Die on next move : B" << std::endl;
            return true;
        }
    }
    if (vector_y < 0){
        if (snake[0][0] <= 4) {
            logs::log_stream << "Die on next move : C" << std::endl;
            return true;
        }
    }
    if (vector_y > 0) {
        if (snake[0][0] >= get_terminal_height() - 2){
            logs::log_stream << "Die on next move : D" << std::endl;
            return true;
        }
    }
    for (unsigned int i = 1; i < snake_len; i++){
        if (snake[0][0] == snake[i][0] and snake[0][1] == snake[i][1]){
            return true;
        }
    }


    return false;
}

#endif //GAME_LOGIC_H
