#pragma once
#include "Player.hpp"

namespace pandemic{

    class OperationsExpert: public Player {

        public:
            OperationsExpert(Board& board, City city): Player(board,city){};
            Player& build() override;
    };

}