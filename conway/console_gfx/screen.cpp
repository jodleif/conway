//
// Created by jo on 10/1/15.
//

#include "screen.h"

#include <curses.h>
namespace console {

        screen::screen()
        {
                initscr();
                clear();
                start_color();
                noecho();
                cbreak();
                keypad(stdscr, 1);
                curs_set(0);
                getmaxyx(stdscr, _height, _width);
                // Colors
                init_pair(1,COLOR_RED,COLOR_WHITE);
                init_pair(2,COLOR_GREEN,COLOR_WHITE);
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

        void screen::clr()
        {
                clear();
        }
}