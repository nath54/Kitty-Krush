//
#pragma once
//
#include <iostream>
#include <map>
#include <string>
#include <string_view>

using namespace std;
typedef unsigned short int usint;

//
class Player{

    private:

        const string name;
        const usint color;

    public:

        // Constructor
        Player(const string player_name, const int player_color)
            : name(player_name), color(player_color) {};  // Automatic variable initialisation
};


//
class GameModel{

    private:

        // Players are linked here, indexed by there name
        map<string, Player*> players;

    public:

        // Game state
        bool is_running = false;

        // Constructor
        GameModel() {};

};
