#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "posix_only.h++"

#include <string>
#include <vector>
#include "logs.h++"

static const std::string APPLE = "*";

bool inited = false;

long int score = 0;


int snake[100000000][2];
unsigned int snake_len = 0;
int vector_y = 0;
int vector_x = 1;


void create_snake () {
    snake[0][0] = get_terminal_height() / 2;
    snake[0][1] =  get_terminal_width() / 2 - 1;
    snake_len += 1;
    snake[1][0] = get_terminal_height() / 2;
    snake[1][1] =  get_terminal_width() / 2 - 1;
    snake_len += 1;
}


void do_movement () {
    /*
    //gotoxy(1, 1);
    //std::cout << snake[0][0] << "|" << snake[0][1];
    std::vector<int> new_pos; // {snake[0][0] + vector_x, snake[0][1] + vector_y}
    new_pos.push_back(snake[0][0] + vector_x);
    new_pos.push_back(snake[0][1] + vector_y);
    snake.push_back(new_pos);

    logs::log_stream << "Snake now ("<< snake.size() << "#" << vector_x << "|" << vector_y << " ) :\n";
    for (unsigned int i = 0; i < snake.size(); i++){
        logs::log_stream << i << ") " << snake[i][0] << " " << snake[i][1] << std::endl;
    }
    snake.erase(snake.begin());
    logs::log_stream << "Snake after ("<< snake.size() <<" ) :\n";
    for (unsigned int i = 0; i < snake.size(); i++){
        logs::log_stream << i << ") " << snake[i][0] << " " << snake[i][1] << std::endl;
    }*/
    //logs::log_stream << "Do movement (Snake len = " << snake_len << "):" << std::endl;
    for (unsigned int i = snake_len - 1; i > 0; i--) {
        // logs::log_stream << "Reading address :" << i - 1 << std::endl;
        snake[i][0] = snake[i - 1][0];
        snake[i][1] = snake[i - 1][1];
    }
    snake[0][0] = vector_x + snake[0][0];
    snake[0][1] = vector_y + snake[0][1];


}

bool die_on_next_move () {
    if (vector_x > 0){
        if (snake[0][1] >= get_terminal_width() - 1){
            logs::log_stream << "Die on next move : A" << std::endl;
            return true;
        }
    }
    if (vector_x < 0){
        if (snake[0][1] <= 1){
            logs::log_stream << "Die on next move : B" << std::endl;
            return true;
        }
    }
    if (vector_y < 0){
        if (snake[0][0] <= 1) {
            logs::log_stream << "Die on next move : C" << std::endl;
            return true;
        }
    }
    if (vector_y > 0) {
        if (snake[0][0] >= get_terminal_height() - 1){
            logs::log_stream << "Die on next move : D" << std::endl;
            return true;
        }
    }


    return false;
}

#endif //GAME_LOGIC_H
