#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>


class Debug {
    public:
        static void log(const std::string& message) {
            std::cout << message << std::endl;
        }
};

#endif // DEBUG_H