//
// Created by jo on 10/1/15.
//

#ifndef CONWAY_FRAME_H
#define CONWAY_FRAME_H
#include <cstdint>
#include <vector>
#include <functional>
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
                //std::function<unsigned(char c)> render_stuff;
                WINDOW *_window; // "Owning" pointer - Gets handled in destructor
                WINDOW *_super = nullptr; // not owning pointer.

                bool _has_super = false;
                char char_to_draw(char ch);
        public:
                frame(int nr_rows, int nr_cols, int row_0, int col_0);
                frame(frame &sw, int nr_rows, int nr_cols, int row_0, int col_0);
                ~frame();

                void fill_window_debug();
                void fill_window(const std::vector<char>& to_draw);
                void add(character &x);
                void erase(character &x);
                void center(character &x);
                void refresh();
                void move(int col, int row);
                void clr();

                WINDOW* get_window();
                WINDOW* get_super();
                int get_width();
                int get_height();
                int get_row_pos();
                int get_col_pos();

        };
        namespace debug_stuff {
                char get_char_based_on_pos(int x, int y, int max_x, int max_y);
        }
}

#endif //CONWAY_FRAME_H
