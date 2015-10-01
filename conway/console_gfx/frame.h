//
// Created by jo on 10/1/15.
//

#ifndef CONWAY_FRAME_H
#define CONWAY_FRAME_H
#include <cstdint>
#include "ncurses.h"
namespace console {
        class frame {
        private:
                std::size_t _height;
                std::size_t _width;

                // Owning pointer?
                WINDOW *_w;
                // not owning pointer... use boost::optional?
                WINDOW *_super;
        public:
                frame(int nr_rows, int nr_cols, int row_0, int col_0);

                frame(frame &sw, int nr_rows, int nr_cols, int row_0, int col_0);
                ~frame();

                void fill_window_debug();

                void add(character &x);
                void center(character &x);
        };
}

#endif //CONWAY_FRAME_H
