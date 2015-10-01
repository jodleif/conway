//
// Created by jo on 10/1/15.
//

#ifndef CONWAY_GAME_H
#define CONWAY_GAME_H

#include "../console_gfx/screen.h"
#include "../console_gfx/frame.h"

namespace conway {
        using console::screen;
        using console::frame;

        class game {
        private:
                screen _screen;
                frame _frame;
        public:
                game();

        };
}

#endif //CONWAY_GAME_H
