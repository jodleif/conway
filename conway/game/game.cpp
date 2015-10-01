//
// Created by jo on 10/1/15.
//

#include "game.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <memory>


conway::game::game()
{

}

void conway::game::run()
{
        //screen _screen;
       // frame _frame(_screen.height(),_screen.width(),0,0);
        auto _gol = std::make_unique<game_of_life>(80, 24);
       // _frame.fill_window_debug();
        int counter {0};
        while(counter < 10){
                //std::this_thread::sleep_for(1s);
                to_loop(_gol.get());
                std::this_thread::sleep_for(std::chrono::seconds(1));
                ++counter;
                std::cerr << counter << std::endl;
        }
}

void conway::game::to_loop(game_of_life* _gol)
{
        //_frame.fill_window(_gol.get_game_board());
        //_frame.clr();
        //_frame.fill_window(_gol.get_game_board());
        //_frame.refresh();
        _gol->print_gameboard();
        _gol->update();
}
