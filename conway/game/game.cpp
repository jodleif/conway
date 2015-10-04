//
// Created by jo on 10/1/15.
//

#include "game.h"
#include <thread>
#include <chrono>


conway::game::game() : _frame(4,4,0,0), _gol(4,4)
{

//        _frame = console::frame(_screen.height(), _screen.width(), 0, 0);
 //       _gol = game_of_life(_screen.width(), _screen.height());
}

conway::game::game(int x, int y) : _frame(y,x,0,0), _gol(x,y)
{

}
void conway::game::run()
{

        int counter{0};
        while (counter < 600) {
                to_loop();
                std::this_thread::sleep_for(std::chrono::milliseconds(166));
                ++counter;
        }
}

void conway::game::to_loop()
{
        _frame.fill_window(_gol.get_game_board());
        _frame.refresh();
        _gol.update();
}
