#ifndef INPUT_CONTROL_H
#define INPUT_CONTROL_H

#include <iostream>

#include <pthread.h>
#include <stdio.h>
#include "posix_only.h++"
#include "game_logic.h++"

void *input_processing(void *param);

bool can_run = true;
char pushed_button = NOT_PUSHED;
bool game_over = false;

void start_input_processing_thread ( ) {
    pthread_t tid; /* идентификатор потока */
    pthread_attr_t attr; /* отрибуты потока */

    /* получаем дефолтные значения атрибутов */
    pthread_attr_init(&attr);
    char* void_arg[0];
    pthread_create(&tid,&attr,input_processing, void_arg);

}

void *input_processing(void *param)
{
    while (can_run){
        while (true){
            pushed_button = get_pushed_button();
            if (pushed_button == KEY_Q or (int)pushed_button == 27){
                can_run = false;
                break;
            }
            else {
                switch (pushed_button) {
                    case KEY_W:
                        vector_y = -1;
                        vector_x = 0;
                        std::cout << "W\n";
                        break;
                    case KEY_A:
                        vector_x = -1;
                        vector_y = 0;
                        std::cout << "A\n";
                        break;
                    case KEY_S:
                        vector_x = 0;
                        vector_y = 1;
                        std::cout << "S\n";
                        break;
                    case KEY_D:
                        vector_y = 0;
                        vector_x = 1;
                        std::cout << "D\n";
                        break;
                    case KEY_E:
                        std::cout << "E\n";
                        can_run = false;
                        pthread_exit(0);
                    default:
                        std::cout << pushed_button ;
                        break;

                }
                //std::cout << "QQ\n";
            }

        }
    }
    pthread_exit(0);
}

#endif //INPUT_CONTROL_H
