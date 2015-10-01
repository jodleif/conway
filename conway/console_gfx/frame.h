//
// Created by jo on 10/1/15.
//

#ifndef CONWAY_FRAME_H
#define CONWAY_FRAME_H
#include <cstdint>
#include "ncurses.h"
#include "character.h"
namespace console {
        class frame {
        private:
                int _height;
                int _width;

                // Position of frame
                int _row_pos;
                int _col_pos;
                // Owning pointer?
                WINDOW *_window;
                // not owning pointer... use boost::optional?
                WINDOW *_super = nullptr;
                bool _has_super = false;
        public:
                frame(int nr_rows, int nr_cols, int row_0, int col_0);

                frame(frame &sw, int nr_rows, int nr_cols, int row_0, int col_0);
                ~frame();

                void fill_window_debug();

                void add(character &x);
                void center(character &x);
                WINDOW* get_window();
        };
}

#endif //CONWAY_FRAME_H
