#pragma once
#include "Player.hpp"

namespace pandemic{

    class FieldDoctor: public Player {

        public:
            FieldDoctor(Board& board, City city): Player(board, city) {};
            Player& treat(City city) override;
    };

}