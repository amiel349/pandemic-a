#pragma once
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace pandemic {

    class Scientist: public Player {
        int num;

        public:
            Scientist(Board& board, City city, int x): Player(board, city), num(x){}
            Player& discover_cure(Color color) override;
    };
}