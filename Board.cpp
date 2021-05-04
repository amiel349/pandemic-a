#include "Board.hpp"
using namespace std;
using namespace pandemic;



namespace pandemic
{
    // constructor
    Board::Board(){};
    int& Board::operator[](pandemic::City city)
    {
        return num;
    }
    void Board::remove_cures(){};
    ostream& operator<<(ostream& os, pandemic::Board& board) { return os; };
    bool Board::is_clean() { return true; };
}