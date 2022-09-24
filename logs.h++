//
// Created by yaroslav_admin on 21.09.22.
//

#ifndef LOGS_H
#define LOGS_H

#include <fstream>
#include <iostream>

namespace logs {
    std::ofstream log_stream;

    void init() {
        log_stream.open(".log");
        if (!log_stream) {
            std::cout << "File creation error !" << std::endl;
            exit(1);
        }

    }

}
#endif //LOGS_H
