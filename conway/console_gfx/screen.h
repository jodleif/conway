//
// Created by jo on 10/1/15.
//

#ifndef CONWAY_SCREEN_H
#define CONWAY_SCREEN_H

#include <cstdint>
#include <string>
/*
 * This class initializes ncurses and gives info about the terminal
 */
namespace console {
        class screen {
        private:
                int _width;
                int _height;
        public:
                screen();

                ~screen();

                void add(const std::string& message);

                int height();

                int width();

                void clr();


        };
}

#endif //CONWAY_SCREEN_H
