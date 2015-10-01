//
// Created by jo on 10/1/15.
//

#include <exception>
#include <iostream>
#include "frame.h"

console::frame::frame(int nr_rows, int nr_cols, int row_0, int col_0)
{
        _has_super = false;
        _width = nr_cols;
        _height = nr_rows;
        _col_pos = col_0;
        _row_pos = row_0;
        _window = newwin(_height, _width, _row_pos, _col_pos);
}

console::frame::frame(console::frame &sw, int nr_rows, int nr_cols, int row_0, int col_0)
{
        _has_super = true;
        _super = sw.get_window();
        _width = nr_cols;
        _height = nr_rows;
        _col_pos = col_0;
        _row_pos = row_0;
        _window = derwin(_super, _height, _width, _row_pos, _col_pos);
}

console::frame::~frame()
{
        delwin(_window);
}

/*
 * should print:
 * 0|1
 * ---
 * 2|3
 */
void console::frame::fill_window_debug()
{
        for (int y{0}; y < _height; ++y) {
                for (int x{0}; x < _width; ++x) {
                        auto ch = console::debug_stuff::get_char_based_on_pos(x, y, _width, _height);
                        mvwaddch(_window, y, x, (ch));
                }
        }
}

void console::frame::add(console::character &x)
{
        mvwaddch(_window, x.row(), x.col(), x.symbol());
}

void console::frame::center(console::character &x)
{
        // TODO: add if needed...
}

WINDOW *console::frame::get_window()
{
        return _window;
}

void console::frame::erase(console::character &x)
{
        mvwaddch(_window, x.row(), x.col(), ' ');
}

void console::frame::refresh()
{
        if (_has_super) {
                touchwin(_super);
        }
        wrefresh(_window);
}

void console::frame::move(int col, int row)
{
        if (_has_super) {
                mvderwin(_window, row, col);
                _row_pos = row;
                _col_pos = col;
                refresh();
        }
}

WINDOW *console::frame::get_super()
{
        if (!_has_super) {
                std::cerr << "[frame::get_super()]Tried to get nullptr!\nExiting.\n";
                std::terminate();
        }
        return _super;
}

int console::frame::get_width()
{
        return _width;
}

int console::frame::get_height()
{
        return _height;
}

int console::frame::get_row_pos()
{
        return _row_pos;
}

int console::frame::get_col_pos()
{
        return _col_pos;
}

char ::console::debug_stuff::get_char_based_on_pos(int x, int y, int max_x, int max_y)
{

        if (x < max_x / 2) {
                if (y < max_y / 2) {
                        return '0';
                }
                return '2';
        } else {
                if (y < max_y / 2) {
                        return '1';
                }
                return '3';
        }
}

void console::frame::fill_window(const std::vector<char> &bitvector)
{
        if (bitvector.size() != static_cast<std::size_t>(_height * _width)) {
                std::cerr << "[frame::fill_window] ERROR: Invalid length of vector to draw got:" << bitvector.size() <<
                " wanted " << (_height * _width) << "\n";
                return;
        }

        move(0,0);
        for (int y{0}; y < _height; ++y) {
                for (int x{0}; x < _width; ++x) {
                        auto ch = to_draw(bitvector[x * y + x]); // <-- to draw.
                        move(y,x-1);
                        wattron(_window,COLOR_PAIR(ch.first));
                        mvwprintw(_window,y,x, "%c",ch.second);//    A
                        wattroff(_window,COLOR_PAIR(ch.first));
                        //                    mvwaddch(_window, y, x, ch.second);
                }
        }

}

std::pair<short, char> console::frame::to_draw(char ch)
{
        switch(ch){
                case 0:
                        return {1,'X'};
                case 1:
                        return {2,'O'}; //COLOR green (see screen.cpp)
                default:
                        return {0,'E'};
        }
}

