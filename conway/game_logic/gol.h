#pragma once
#include <vector>
namespace conway {

	enum class rule_neighbor_state
	{
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
		std::vector<char> _game_board;
		std::size_t coord_to_pos(int x, int y);
		rule_neighbor_state get_neighborstate(int x, int y);
		bool cell_change_rule(rule_neighbor_state ruling, bool curr_state);
	public:
		game_of_life(std::size_t width, std::size_t height);
		void update();

		bool alive(int x, int y);

		auto get_width()
		{
			return _height;
		}

		auto get_height()
		{
			return _width;
		}
	};

}
