#include "beautiful_output_cpp.h++"
#include "input_control.h++"
#include "game_logic.h++"
#include "logs.h++"

#include <iostream>
#include <vector>

#include <fstream>

int main ()
{
    logs::init();

    std::cout << get_terminal_height() << "X" << get_terminal_width() << std::endl;

    start_input_processing_thread();


    std::string map[get_terminal_height() - 1][get_terminal_width()];
    for (unsigned int y = 0; y < get_terminal_height() - 1; y++){
        for (unsigned int x = 0; x < get_terminal_width(); x++){
            if (x == 2){
                map[y][x] = std::to_string(y);
                continue;
            }
            if (y == 0) {
                map[y][x] = "*";
            }
            else {
                if (y == get_terminal_height() - 2) {
                    map[y][x] = "=";
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

    while (can_run){

        for (unsigned int y = 0; y < get_terminal_height() - 1; y++){
            for (unsigned int x = 0; x < get_terminal_width() - 1; x++){
                std::cout << map[y][x];
            }
            std::cout << std::endl;
        }

        for (unsigned int i = 0; i < snake_len; i++){

            //std::cout << "\033[" << snake[i][0] << ";" << snake[i][1] <<"H";
            gotoxy(snake[i][1], snake[i][0]);
            //std::cout << "#" << snake[i][1] << "|" << snake[i][0] << "#";
//            std::cout << "#" << snake[i][0] << "|" << snake[i][1] << "#";
//            std::cout << "#" << vector_x << "|" << vector_y << "#";
            if (snake[i][0] < 0 or snake[i][1] < 0){
                logs::log_stream << "WTF :" << snake[i][0] << snake[i][1] << std::endl;
            }
            if (i == 0){
                std::cout << "$";
            }
            else{
                std::cout << "#";
            }

        }


        //std::cout << "E";
        std::cout << "\n\n";
        sleep(1);
        logs::log_stream << "Snake pos : y = " << snake[0][0] << " x = " << snake[0][1] << std::endl;
        if (!die_on_next_move()){
            do_movement();
        } else {
            logs::log_stream << "Cant move : y = " << snake[0][0] << " x = " << snake[0][1] << std::endl;
        }
        //std::cout << "\033[0;0H";
        // std::cout << "\033[" << -get_terminal_width() << ";" << -get_terminal_height() <<"H";
        gotoxy(0, 0);


    }



    return 0;
}