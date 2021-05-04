#include "Player.hpp"
using namespace pandemic;

Player& Player::drive(City city) { return *this; };
Player& Player::fly_direct(City city) { return *this; };
Player& Player::fly_charter(City city) { return *this; };
Player& Player::fly_shuttle(City city) { return *this; };
Player& Player::build() { return *this; };
Player& Player::discover_cure(Color color) { return *this; };
Player& Player::treat(City city) { return *this; };
Player& Player::take_card(City city) { return *this; };
string Player::role() { return "testing"; };