//
// Created by jo on 10/1/15.
//

#include "game.h"
#include <thread>
#include <chrono>


conway::game::game()
{

}

void conway::game::run()
{
        screen _screen;
        auto _frame = frame(_screen.height(), _screen.width(), 0, 0);
        auto _gol = game_of_life(_screen.width(), _screen.height());

        int counter{0};
        while (counter < 3000) {
                to_loop(&_gol, &_frame);
                std::this_thread::sleep_for(std::chrono::milliseconds(33));
                ++counter;
        }
}

void conway::game::to_loop(game_of_life *_gol, frame *_frame)
{
        (*_frame).fill_window((*_gol).get_game_board());
        (*_frame).refresh();
        _gol->update();
}
