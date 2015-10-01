//
// Created by jo on 10/1/15.
//

#ifndef CONWAY_CHARACTER_H
#define CONWAY_CHARACTER_H

namespace console {
        // Inane data structure for a character in x,y space
        class character {
        private:
                int _row;
                int _col;
                char _symbol;
        public:
                character(char symbol, int row, int col);
                void pos(int row, int col);
                int row();
                int col();
                char symbol();

        };
}

#endif //CONWAY_CHARACTER_H
