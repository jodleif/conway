#include <iostream>
#include "console_gfx/screen.h"
#include "console_gfx/frame.h"

int main()
{
        console::screen init_screen; // initialize screen.. with an object?:P
        console::frame frame_(init_screen.height(),init_screen.width(),0,0);
        frame_.fill_window_debug();
//        frame_.refresh();
        std::cin.get();
        return 0;
}