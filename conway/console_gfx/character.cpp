//
// Created by jo on 10/1/15.
//

#include "character.h"

console::character::character(char symbol, int row, int col)
{
        _row = row;
        _col = col;
        _symbol = symbol;
}

void console::character::pos(int row, int col)
{
        _row = row;
        _col = col;
}

int console::character::row()
{
        return _row;
}

int console::character::col()
{
        return _col;
}

char console::character::symbol()
{
        return _symbol;
}
