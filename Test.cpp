#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "Researcher.hpp"
#include "Scientist.hpp"
#include "FieldDoctor.hpp"
#include "GeneSplicer.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"
#include "doctest.h"
using namespace pandemic;

#include <iostream>
#include <stdexcept>
using namespace std;
using namespace doctest;

TEST_CASE("init")
{

        Board board; // Initialize an empty board (with 0 disease cubes in any city).

        CHECK(board.is_clean());
        board[City::Kinshasa] = 3;      // put 3 yellow disease cubes in Kinshasa.
        board[City::Kinshasa] = 2;      // change number of disease cubes in Kinshasa to 2.
        board[City::MexicoCity] = 3;    // put 3 yellow disease cubes in MexicoCity
        board[City::HoChiMinhCity] = 1; // put 1 red disease cube in HoChiMinhCity
        board[City::Chicago] = 1;
        CHECK_FALSE(board.is_clean());
}

TEST_CASE("Dispatcher")
{
        Board board;

        Dispatcher disp{board, City::BuenosAires};
        disp.take_card(City::Miami)
            .take_card(City::Montreal);

        CHECK_THROWS(disp.build());                 // disp cant build beacuase he dont have the card of bueno aires
        CHECK_THROWS(disp.fly_direct(City::Cairo)); // cant flight direct to cairo beacause he dont have the card

        disp.take_card(City::BuenosAires);
        CHECK_NOTHROW(disp.build());                 // now he can build because he got the card
        CHECK_NOTHROW(disp.fly_direct(City::Cairo)); // after building he can filght direct to anywhere
        CHECK(disp.role() == string("Dispatcher"));
}

TEST_CASE("FieldDoctor")
{
        Board board;

        board[City::Montreal] = 4;
        board[City::Washington] = 3;
        FieldDoctor f_doc{board, City::NewYork};

        f_doc.take_card(City::Tokyo)
            .take_card(City::Osaka);

        f_doc.treat(City::Montreal);
        CHECK(board[City::Montreal] == 3); // field doctor can treat neighbors without card
        f_doc.treat(City::Washington);
        CHECK(board[City::Washington] == 2);          // field doctor can treat neighbors without card
        CHECK_THROWS(f_doc.treat(City::Lagos));       // not legal because lagos is not connected to new york
        CHECK_THROWS(f_doc.treat(City::BuenosAires)); // not legal because lagos is not connected to new york
        CHECK(f_doc.role() == "FieldDoctor");
}

TEST_CASE("GeneSplicer")
{
        Board board;

        board[City::Istanbul] = 5;
        board[City::Lagos] = 3;
        board[City::HoChiMinhCity] = 3;
        board[City::StPetersburg] = 3;
        board[City::Shanghai] = 3;
        board[City::SaoPaulo] = 3;
        board[City::Washington] = 3;

        GeneSplicer g_splicer{board, City::Santiago};
        g_splicer.take_card(City::Istanbul)
            .take_card(City::Lagos)
            .take_card(City::Shanghai)
            .take_card(City::HoChiMinhCity)
            .take_card(City::Delhi)
            .take_card(City::Santiago);
        g_splicer.build();
        g_splicer.discover_cure(pandemic::Color::Yellow);
        g_splicer.treat(City::Santiago);
        CHECK(board[City::Santiago] == 0); // after discover_cure treat should done to 0

        OperationsExpert player_yellow{board, City::SaoPaulo};
        OperationsExpert player_blue{board, City::Washington};
        player_yellow.treat(City::SaoPaulo);
        CHECK(board[City::SaoPaulo] == 0); //the is a cure for yellow so it go down to 0

        player_blue.treat(City::Washington);
        CHECK(board[City::Washington] == 2); //there is no cure for blue it goes doown by 1
        CHECK(g_splicer.role() == "GeneSplicer");
}

TEST_CASE("Medic")
{
        Board board;

        board[City::Atlanta] = 2;
        board[City::Baghdad] = 4;
        board[City::MexicoCity] = 3;
        board[City::Chennai] = 1;
        board[City::Madrid] = 4;
        board[City::Paris] = 4;

        Medic medic{board, City::Madrid};
        medic.treat(City::Madrid);
        CHECK(board[City::Madrid] == 0); // when paramedic make treat it directly go down to 0
        OperationsExpert player{board, City::NewYork};
        player.take_card(City::Paris)
            .take_card(City::Essen)
            .take_card(City::NewYork)
            .take_card(City::London)
            .take_card(City::StPetersburg)
            .take_card(City::Milan);

        player.build();
        player.discover_cure(pandemic::Color::Blue);
        medic.drive(City::Paris);
        CHECK(board[City::Paris] == 0); // after there is a cure when paramedic arrive the city it goes down to 0
        CHECK(player.role() == string("Medic"));
}

TEST_CASE("OperationsExpert")
{
        Board board;

        board[City::Kinshasa] = 5;
        board[City::Johannesburg] = 2;

        OperationsExpert Op_e{board, City::Khartoum};
        Op_e.take_card(City::Beijing);
        CHECK_NOTHROW(Op_e.build());                      // operations expert can build without a card
        CHECK_THROWS(Op_e.fly_shuttle(City::Beijing));    // not legal in beijing the is no reaserch
        CHECK_THROWS(Op_e.fly_direct(City::BuenosAires)); //cant flight without a card
        Op_e.fly_direct(City::Beijing);                   // legal- he have a card
        CHECK_NOTHROW(Op_e.build());                      // operations expert can build without a card
        CHECK_NOTHROW(Op_e.fly_shuttle(City::Khartoum));  // now its legal because there is reasarch in both cities

        CHECK(Op_e.role() == "OperationsExpert");
}

TEST_CASE("Researcher")
{
        Board board;

        board[City::Tehran] = 3;
        board[City::Riyadh] = 3;
        board[City::MexicoCity] = 3;
        board[City::London] = 3;

        Researcher researcher{board, City::London};
        researcher.take_card(City::Paris)
            .take_card(City::London)
            .take_card(City::StPetersburg)
            .take_card(City::Essen)
            .take_card(City::Madrid);
        CHECK_NOTHROW(researcher.discover_cure(pandemic::Color::Blue)); // reseacher can discover without build
        OperationsExpert player{board, City::Lima};
        player.take_card(City::Lima)
            .take_card(City::SaoPaulo)
            .take_card(City::BuenosAires)
            .take_card(City::Santiago)
            .take_card(City::Bogota);
        CHECK_THROWS(player.discover_cure(pandemic::Color::Yellow)); // operations expert need a research to discover cure
        CHECK(researcher.role() == "Researcher");
}
TEST_CASE("Scientist")
{
        Board board;
        board[City::Beijing] = 5;
        board[City::Shanghai] = 5;
        board[City::Seoul] = 4;
        board[City::Taipei] = 4;
        board[City::Bangkok] = 4;

        Scientist scientist{board, City::Bangkok, 3};
        scientist.take_card(City::Beijing)
            .take_card(City::Shanghai)
            .take_card(City::Taipei)
            .take_card(City::Bangkok);
        scientist.build();
        scientist.take_card(City::Bangkok);
        CHECK_NOTHROW( scientist.discover_cure(pandemic::Color::Black)); //scientist can discover cure with N cards
        scientist.treat(City::Bangkok);
        CHECK(board[City::Bangkok] == 0);
        CHECK(scientist.role() =="Scientist");
}


TEST_CASE("Virologist")
{
        Board board;

        

      board[City::Beijing] = 5;
        board[City::Shanghai] = 2;
        board[City::Seoul] = 4;
        board[City::Taipei] = 4;
        board[City::Bangkok] = 0;

        Virologist viro{board, City::Istanbul};
        viro.take_card(City::Beijing)
            .take_card(City::Shanghai)
            .take_card(City::Taipei)
            .take_card(City::Bangkok);

        viro.treat(City::Beijing); // virologist can treat witout being in this city
        viro.treat(City::Shanghai);
        viro.treat(City::Taipei);
        CHECK(board[City::Beijing]==4);
        CHECK(board[City::Shanghai]==1);
        CHECK(board[City::Taipei]==3);
        CHECK_THROWS(viro.treat(City::Bangkok)); // not legal  the infection already is 0 
        CHECK_THROWS(viro.treat(City::Lima)); // virologist dont have this card
        CHECK_THROWS(viro.treat(City::BuenosAires)); // virologist dont have this card
        
        CHECK(viro.role() == "Virologist");
}

