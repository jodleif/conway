//
// Created by jo on 10/1/15.
//

#ifndef CONWAY_GAME_H
#define CONWAY_GAME_H

#include "../console_gfx/frame.h"
#include "../game_logic/gol.h"

namespace conway {

        class game {
        private:
		console::frame _frame;
                game_of_life _gol;

        public:
                game();
		game(int x, int y);
                void run();
                void to_loop();
        };
}

#endif //CONWAY_GAME_H
