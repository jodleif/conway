//
// Created by jo on 10/1/15.
//

#ifndef CONWAY_GAME_H
#define CONWAY_GAME_H

#include "../console_gfx/frame.h"
#include "../game_logic/gol.h"
#include <atomic>
#include <functional>
#include <thread>

namespace conway {
enum class input_result {
    quit,
    reseed_random,
    reseed_gopher,
    not_reg
};

input_result parse_input(char input);

class game {
private:
    console::frame _frame;
    game_of_life _gol;
    template <typename Lambda>
    bool handle_input(std::thread& draw_loop, const conway::input_result input_command, std::atomic<bool>& run,
        Lambda& game_loop)
    {
        if (input_command == input_result::quit) {
            run.store(false);
            return false;
        } else if (input_command == input_result::reseed_random) {
            run.store(false);
            draw_loop.join();
            _gol.reset_board();
            _gol.seed();
            run.store(true);
            draw_loop = std::thread(game_loop);
        } else if (input_command == input_result::reseed_gopher) {
            run.store(false);
            draw_loop.join();
            _gol.reset_board();
            _gol.gosper_gun_seed();
            run.store(true);
            draw_loop = std::thread(game_loop);
        }
        return true;
    }

public:
    game();
    game(int x, int y);
    void run();
    void to_loop();
};
}

#endif //CONWAY_GAME_H
