#pragma once
#include "Board.hpp"
using namespace std;

namespace pandemic
{
    class Player
    {

    protected:
        pandemic::Board m_board;
        pandemic::City m_city;

    public:
        Player(pandemic::Board &board, pandemic::City city): m_board(board), m_city(city){}
        Player &drive(pandemic::City city);
        virtual Player &fly_direct(pandemic::City city);
        Player &fly_charter(pandemic::City city);
        Player &fly_shuttle(pandemic::City city);
        virtual Player &build();
        virtual Player &discover_cure(pandemic::Color color);
        virtual Player &treat(pandemic::City color);
        Player &take_card(pandemic::City color);
        string role();
    };

}