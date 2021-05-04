#pragma once
#include "Player.hpp"
//#include "City.hpp"
//#include "Color.hpp"
//#include "Board.hpp"

namespace pandemic{

    class Virologist: public Player {

        public:
            Virologist(Board& board, City city): Player(board, city) {};
            Player& treat(City city) override;
    };

}