//
// Created by jo on 10/1/15.
//

#ifndef CONWAY_GAME_H
#define CONWAY_GAME_H

#include "../console_gfx/screen.h"
#include "../console_gfx/frame.h"
#include "../game_logic/gol.h"

namespace conway {
        using console::screen;
        using console::frame;

        class game {
        private:
                //screen _screen;
                //frame _frame;
                //game_of_life _gol;

        public:
                game();
                void run();
                void to_loop(game_of_life *_gol, frame *_frame);

        };
}

#endif //CONWAY_GAME_H
