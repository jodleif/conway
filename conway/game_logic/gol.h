#pragma once

#include <vector>
#include <cstdint>
namespace conway {

        enum class rule_neighbor_state {
                less_than_two,
                two_or_three,
                more_than_three,
                three_reprod,
                invalid
        };

        rule_neighbor_state get_state(int nof);

        class game_of_life {
        private:
                int _width;
                int _height;
                std::vector<char> _game_board; // holding "bool values" 0/1
                std::size_t coord_to_pos(int x, int y);

                rule_neighbor_state get_neighborstate(int x, int y);

                bool cell_change_rule(rule_neighbor_state ruling, bool curr_state);

                void set(int x, int y, bool val);
                char seed_alive(int8_t random_value);
		//Seeding functions

        public:
                game_of_life(int width, int height);
                void update();
                std::vector<char> get_game_board();
                bool alive(int x, int y);
                void print_gameboard();
                int get_width();
                int get_height();
                void reset_board();
                void seed(); // Seed game board with random values (dead or alive)
                void gosper_gun_seed();
        };

}
