#include "gol.h"
#include <cassert>
#include <iostream>
#include <random>

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
        int alive{0};
        for (int i = y - 1; i <= (y + 1); ++i) {
                for (int j = x - 1; j <= (x + 1); ++j) {
                        if (this->alive(i, j) && (i != y && j != x)) {
                                ++alive;
                        }
                }
        }
        return conway::get_state(alive);
}

std::size_t conway::game_of_life::coord_to_pos(int x, int y)
{
        assert(x >= 0 && x < _width);
        assert(y >= 0 && y < _height);
        return static_cast<std::size_t>(x * y + x);
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
        _game_board = std::vector<char>(static_cast<std::size_t>(width*height),static_cast<char>(0));
        _width = width;
        _height = height;
        seed(); // "initialize" game board
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
                        auto next_state_ji = get_neighborstate(y, x);
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
                return false;
        }
        if (x >= _width || y >= _height) {
                return false;
        }
        auto temp_check = _game_board[coord_to_pos(x, y)];
        return (temp_check == 0) ? false : true;
}

std::vector<char> conway::game_of_life::get_game_board()
{
        return _game_board;
}

void conway::game_of_life::seed()
{
        std::mt19937 rng_engine;
        std::uniform_int_distribution<int> dist(0,9);
        for(std::size_t i {0};i<_game_board.size();++i){
                _game_board[i]=(seed_alive(dist(rng_engine)));
        }
}

char conway::game_of_life::seed_alive(int8_t random_value)
{
        switch (random_value){
                case 0:
                        return 1;
                default:
                        return 0;
        }
}

void conway::game_of_life::print_gameboard()
{
        for(const auto& elem : _game_board){
                std::cout << static_cast<char>('0'+elem);
        }
        std::cout << std::endl;
}
