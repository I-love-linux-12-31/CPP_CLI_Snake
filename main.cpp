#include "input_control.h++"
#include "game_logic.h++"

#include <iostream>
#include <vector>

int main ()
{
    std::cout << get_terminal_height() << "X" << get_terminal_width() << std::endl;

    start_input_processing_thread();


    std::string map[get_terminal_height() - 1][get_terminal_width()];
    for (unsigned int y = 0; y < get_terminal_height() - 1; y++){
        for (unsigned int x = 0; x < get_terminal_width(); x++){
            map[y][x] = " ";
        }
    }
//    for (unsigned int i = 0; i < get_terminal_width(); i++){
//        map[2][i] = APPLE;
//    }

    while (can_run){

        for (unsigned int y = 0; y < get_terminal_height() - 1; y++){
            for (unsigned int x = 0; x < get_terminal_width(); x++){
                std::cout << map[y][x];
            }
            std::cout << std::endl;
        }

        for (unsigned int i = 0; i < snake.size(); i++){
            std::cout << "\033[" << snake[i][1] << ";" << snake[i][0] <<"H";
            if (i == 0){
                std::cout << "$";
            }
            else{
                std::cout << "#";
            }

        }




        std::cout << "\033[0;0H";
        sleep(1);

    }



    return 0;
}