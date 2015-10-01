//
// Created by jo on 10/1/15.
//

#include "screen.h"
namespace console {
        screen::screen()
        {
                initscr();
                clear();
                noecho();
                cbreak();
                keypad(stdscr, 1);
                curs_set(0);
                getmaxyx(stdscr, _height, _width);
        }

        // Clear ncurses
        screen::~screen()
        {
                endwin();
        }

        void screen::add(const std::string& message)
        {
                printw(message.c_str());
        }

        int screen::height()
        {
                return _height;
        }

        int screen::width()
        {
                return _width;
        }
}