//
// Created by jo on 10/1/15.
//

#include "game.h"
#include <chrono>
#include <iostream>


conway::game::game()
    : _frame(4, 4, 0, 0)
    , _gol(4, 4)
{

    //        _frame = console::frame(_screen.height(), _screen.width(), 0, 0);
    //       _gol = game_of_life(_screen.width(), _screen.height());
}

conway::game::game(int x, int y)
    : _frame(y, x, 0, 0)
    , _gol(x, y)
{
}
void conway::game::run()
{
    std::atomic<bool> run{ true };
    auto game_loop = [this,&run]() {
        while (run) {
            to_loop();
            std::this_thread::sleep_for(std::chrono::milliseconds(166));
        }
    };

    std::thread draw_loop(game_loop);
    while (true) {
        char letter;
        std::cin >> letter;
        auto command = conway::parse_input(letter);
        if(handle_input(draw_loop,command,run,game_loop)!=true) break;
    }
    draw_loop.join();
}

void conway::game::to_loop()
{
    _frame.fill_window(_gol.get_game_board());
    _frame.refresh();
    _gol.update();
}

conway::input_result conway::parse_input(char input)
{
    switch (input) {
    case 'g':
    case 'G':
        return input_result::reseed_gopher;
    case 'q':
    case 'Q':
        return input_result::quit;
    case 'r':
    case 'R':
        return input_result::reseed_random;
    default:
        return input_result::not_reg;
    }
}
