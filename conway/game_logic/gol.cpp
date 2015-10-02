#include "gol.h"
#include <cassert>
#include <iostream>
#include <random>
#include <chrono>

conway::rule_neighbor_state conway::get_state(int nof)
{
        switch (nof) {
                case 0:
                case 1:
                        return rule_neighbor_state::less_than_two;
                case 2:
                        return rule_neighbor_state::two_or_three;
                case 3:
                        return rule_neighbor_state::three_reprod;
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                        return rule_neighbor_state::more_than_three;
                default:
                        return rule_neighbor_state::invalid;
        }
}

conway::rule_neighbor_state conway::game_of_life::get_neighborstate(int x, int y)
{
        int nof_alive{0};
        for (int i = y - 1; i <= (y + 1); ++i) {
                for (int j = x - 1; j <= (x + 1); ++j) {
                        if (alive(j, i)) {
                                ++nof_alive;
                                if(i==y&&x==j){
                                        --nof_alive; // dont count self.
                                }
                        }
                }
        }
        return conway::get_state(nof_alive);
}

std::size_t conway::game_of_life::coord_to_pos(int x, int y)
{
        assert(x >= 0 && x < _width);
        assert(y >= 0 && y < _height);
        return static_cast<std::size_t>(y*_width + x);
}

bool conway::game_of_life::cell_change_rule(rule_neighbor_state ruling, bool curr_state)
{
        switch (ruling) {
                case rule_neighbor_state::less_than_two:
                        return false; // DEAD - lonely :(
                case rule_neighbor_state::two_or_three:
                        return (curr_state); // No change
                case rule_neighbor_state::three_reprod:
                        return true; // DEAD->alive. Alive->alive
                case rule_neighbor_state::more_than_three:
                        return false; // DEAD - overpopulation!
                default:
                        std::cerr << "[game_of_life::cell_change_rule] ERROR: Got invalid game_rule\n";
                        return false;
        }
}

conway::game_of_life::game_of_life(int width, int height)
{
        _game_board = std::vector<char>(static_cast<std::size_t>(width * height), static_cast<char>(0));
        _width = width;
        _height = height;
        //seed(); // "initialize" game board
        gosper_gun_seed();
}

/*
 - En levende celle med færre enn to levende naboer dør av ensomhet.
 - En levende celle med to eller tre levende naboer lever videre.
 - En levende celle med flere enn tre levende naboer dør av overbefolkning.
 - En død celle med nøyaktig tre levende naboer blir til en levende celle, som ved reproduksjon.
*/
// Update board according to rules above.
void conway::game_of_life::update()
{
        std::vector<char> next_gen(_game_board);
        for (int y{0}; y < _height; ++y) {
                for (int x{0}; x < _width; ++x) {
                        auto next_state_ji = get_neighborstate(x, y);
                        next_gen[coord_to_pos(x, y)] = cell_change_rule(next_state_ji, alive(x, y));
                }
        }
        _game_board = next_gen;
}

// IS ANIMAL IN CELL (x,y) alive?
// Outside our "area" everything is dead.
// TODO: implement changeable boundary conditions?
bool conway::game_of_life::alive(int x, int y)
{
        if (x < 0 || y < 0) {
                // std::cerr << "OUTSIDE BOUNDS" << x << "," << y << "MAX:" << _width << "," << _height << std::endl;
                return false;
        }
        if (x >= _width || y >= _height) {
                // std::cerr << "OUTSIDE BOUNDS" << x << "," << y << "MAX:" << _width << "," << _height << std::endl;
                return false;
        }
        auto temp_check = _game_board[coord_to_pos(x, y)];
        return (temp_check != 0);
}

std::vector<char> conway::game_of_life::get_game_board()
{
        return _game_board;
}

void conway::game_of_life::seed()
{
        auto sclock_seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 rng_engine(sclock_seed);
        std::uniform_int_distribution<int> dist(0, 1);
        for (std::size_t i{0}; i < _game_board.size(); ++i) {
                _game_board[i] = (seed_alive(dist(rng_engine)));
        }
}

char conway::game_of_life::seed_alive(int8_t random_value)
{
        switch (random_value) {
                case 0:
                        return 1;
                default:
                        return 0;
        }
}

void conway::game_of_life::print_gameboard()
{
        for (const auto &elem : _game_board) {
                std::cout << static_cast<char>('0' + elem);
        }
        std::cout << std::endl;
}

void conway::game_of_life::gosper_gun_seed()
{
        if(_height<11)
                return;
        if(_width<38)
                return;

        // GUN 2
        set(25,1,true);
        set(25,2,true);
        set(23,2,true);
        set(21,3,true);
        set(22,3,true);
        set(21,4,true);
        set(22,4,true);
        set(21,5,true);
        set(22,5,true);
        set(25,6,true);
        set(25,7,true);
        set(23,6,true);
        //GUN 1
        set(13,3,true);
        set(14,3,true);
        set(12,4,true);
        set(16,4,true);
        set(11,5,true);
        set(17,5,true);
        set(11,6,true);
        set(18,6,true);
        set(17,6,true);
        set(15,6,true);
        set(11,7,true);
        set(17,7,true);
        set(12,8,true);
        set(16,8,true);
        set(13,9,true);
        set(14,9,true);
        //SQUARE 1
        set(1,5,true);
        set(2,5,true);
        set(1,6,true);
        set(2,6,true);

        //SQUARE 2
        set(35,3,true);
        set(36,3,true);
        set(35,4,true);
        set(36,4,true);

}

void conway::game_of_life::set(int x, int y, bool val)
{
        _game_board[coord_to_pos(x,y)] = static_cast<char>(val);
}
