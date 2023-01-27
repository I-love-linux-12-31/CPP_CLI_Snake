#include "beautiful_output_cpp.h++"
#include "input_control.h++"
#include "game_logic.h++"
#include "logs.h++"

#include <iostream>
#include <vector>
#include <cstdlib>

#include <fstream>

int main ()
{
    logs::init();

    std::cout << get_terminal_height() << "X" << get_terminal_width() << std::endl;

    start_input_processing_thread();


    std::string map[get_terminal_height() - 1][get_terminal_width()];
    for (unsigned int y = 0; y < get_terminal_height() - 1; y++){
        for (unsigned int x = 0; x < get_terminal_width(); x++){
            if (x == 0 and y == 2){
                map[y][x] = "\033[35m╔\033[0m";
                continue;
            }
            if (x == get_terminal_width() - 2 and y == 2){
                map[y][x] = "\033[35m╗\033[0m";
                continue;
            }
            if (x == 0 and y == get_terminal_height() - 2){
                map[y][x] = "\033[35m╚\033[0m";
                continue;
            }
            if (x == get_terminal_width() - 2 and y == get_terminal_height() - 2){
                map[y][x] = "\033[35m╝\033[0m";
                continue;
            }

            if ((x == 0 or x == get_terminal_width() - 2) and y > 2 and y < get_terminal_height() - 2){
                map[y][x] = "\033[35m║\033[0m";
                continue;
            }

            if (y == 2) {
                map[y][x] = "\033[35m═\033[0m";
            }
            else {
                if (y == get_terminal_height() - 2) {
                    map[y][x] = "\033[35m═\033[0m";
                }
                else {
                    map[y][x] = " ";
                }
            }
        }
    }

//    for (unsigned int i = 0; i < get_terminal_width(); i++){
//        map[2][i] = APPLE;
//    }

    create_snake();
    create_fruits();

    while (can_run){

        for (unsigned int y = 0; y < get_terminal_height() - 1; y++){
            for (unsigned int x = 0; x < get_terminal_width() - 1; x++){
                std::cout << map[y][x];
            }
            std::cout << std::endl;
        }

        gotoxy(8, 2);
        std::cout << "\033[31m Score: \033[1m" << std::to_string(score) << "\033[0m";
        //gotoxy(32, 2);
        //std::cout << "\033[31m Speed: \033[1m" << std::to_string(game_sleep_time_ms) << "\033[0m";

        gotoxy(fruits[fruits_index][1], fruits[fruits_index][0]);
        switch (fruits[fruits_index][2]) {
            case 0:
                std::cout << "\033[31m*\033[0m";
                break;
            case 1:
                std::cout << "\033[91m*\033[0m";
                break;
            case 2:
                std::cout << "\033[33m*\033[0m";
                break;
            case 3:
                std::cout << "\033[34mo\033[0m";
                break;
            case 4:
                std::cout << "\033[36m\033[1m@\033[0m";
                break;
            case 5:
                std::cout << "\033[96m\033[1m@\033[0m";
                break;


        }


        for (unsigned int i = 0; i < snake_len; i++){

            gotoxy(snake[i][1], snake[i][0]);

            if (snake[i][0] < 0 or snake[i][1] < 0){
                logs::log_stream << "WTF :" << snake[i][0] << snake[i][1] << std::endl;
            }
            if (i == 0){
                if (snake[0][0] == fruits[fruits_index][0] and snake[0][1] == fruits[fruits_index][1]){
                    std::cout << "\033[32m\033[1mO\033[0m";
                }
                else {
                    std::cout << "\033[32m$\033[0m";
                }
            }
            else{
                std::cout << "\033[1m\033[32m#\033[0m";
            }

        }

        logs::log_stream << "====================" << std::endl;


        //std::cout << "E";
        std::cout << "\n\n";
        usleep(game_sleep_time_ms);
        logs::log_stream << "Snake pos : y = " << snake[0][0] << " x = " << snake[0][1] << std::endl;
        if (!die_on_next_move()){
            if (snake[0][0] == fruits[fruits_index][0] and snake[0][1] == fruits[fruits_index][1]){
                score += fruits[fruits_index][2];
                fruits_index += 1;
                do_movement(true);
                switch (fruits[fruits_index][2]) {
                    case 0:
                        if (game_sleep_time_ms > 57000){
                            game_sleep_time_ms -= 7000;
                        }
                        break;
                    case 1:
                        if (game_sleep_time_ms > 57000){
                            game_sleep_time_ms -= 5000;
                        }
                        break;
                    case 2:
                        if (game_sleep_time_ms > 57000){
                            game_sleep_time_ms -= 3000;
                        }
                        break;
                    case 3:
                        game_sleep_time_ms += 1000;
                        break;
                    case 4:
                        game_sleep_time_ms += 3000;
                        break;
                    case 5:
                        game_sleep_time_ms += 5000;
                        break;


                }

            }
            else {
                do_movement(false);

            }
        } else {

            std::cout << std::endl;
            std::cout << "Game Over !" << std::endl;
            std::cout << std::endl;
            return 0;
            //logs::log_stream << "Cant move : y = " << snake[0][0] << " x = " << snake[0][1] << std::endl;
        }
        //std::cout << "\033[0;0H";
        // std::cout << "\033[" << -get_terminal_width() << ";" << -get_terminal_height() <<"H";
        gotoxy(0, 0);


    }



    return 0;
}