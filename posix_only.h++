#ifndef POSIX_ONLY_H
#define POSIX_ONLY_H

#include <sys/ioctl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>


static const char NOT_PUSHED = '\0';
static const char KEY_W = 'w';
static const char KEY_A = 'a';
static const char KEY_S = 's';
static const char KEY_D = 'd';

//static const char KEY_UP = 'u';
//static const char KEY_LEFT = 'l';
//static const char KEY_DOWN = 'd';
//static const char KEY_RIGHT = 'r';


int get_terminal_height (){
    struct winsize w{};
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_row;
}

int get_terminal_width (){
    struct winsize w{};
    ioctl(0, TIOCGWINSZ, &w);
    return w.ws_col;
}


char get_pushed_button () {
    struct termios tio{};
    int i,bkup;

    if(!tcgetattr(0,&tio))
    {
        bkup=tio.c_lflag;
        tio.c_lflag=0;
        if(!tcsetattr(0,TCSANOW,&tio))
        {
            // printf("\nTell me [Y]es or [N]o: ");
            while(true)
            {
                i=getc(stdin);
                switch (i) {
                    case 'w':
                        tio.c_lflag=bkup;
                        tcsetattr(0,TCSANOW,&tio);
                        return KEY_W;
                    case 'a':
                        tio.c_lflag=bkup;
                        tcsetattr(0,TCSANOW,&tio);
                        return KEY_A;
                    case 's':
                        tio.c_lflag=bkup;
                        tcsetattr(0,TCSANOW,&tio);
                        return KEY_S;
                    case 'd':
                        tio.c_lflag=bkup;
                        tcsetattr(0,TCSANOW,&tio);
                        return KEY_D;
                    default:
                        tio.c_lflag=bkup;
                        tcsetattr(0,TCSANOW,&tio);
                        return NOT_PUSHED;

                }
            }
        }
        else
        {
            printf("\nerror setting console attr...\n");
            return NOT_PUSHED;

        }
    }
    else
    {
        printf("\nerror getting console attr...\n");
        return NOT_PUSHED;
    }
}


#endif //POSIX_ONLY_H
