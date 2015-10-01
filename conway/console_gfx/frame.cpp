//
// Created by jo on 10/1/15.
//

#include "frame.h"

console::frame::frame(int nr_rows, int nr_cols, int row_0, int col_0)
{
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

void console::frame::fill_window_debug()
{

}

void console::frame::add(::console::frame::character &x)
{
        mvwaddch(_window, x.row(), x.col(), x.symbol());
}

void console::frame::center(::console::frame::character &x)
{
        mvaddch(_window, x.row(),x.col(), ' ');
}

WINDOW *console::frame::get_window()
{
        return _window;
}
