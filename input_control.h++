#ifndef INPUT_CONTROL_H
#define INPUT_CONTROL_H

#include <iostream>

#include <pthread.h>
#include <stdio.h>
#include "posix_only.h++"

void *input_processing(void *param);
bool can_run = true;
char pushed_button = NOT_PUSHED;

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
            if (pushed_button == KEY_W){
                can_run = false;
                break;
            }
            else {
                std::cout << "QQ\n";
            }

        }
    }
    pthread_exit(0);
}

#endif //INPUT_CONTROL_H
