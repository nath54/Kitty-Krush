//
#pragma once
//
#include <iostream>
#include <map>
#include <string>
#include <string_view>


//
class Player{

    public:

        // Player name, it is in the name   ദ്ദി(˵ •̀ ᴗ - ˵ ) ✧
        const std::string player_name;

        // Constructor
        Player(const std::string player_name)
            : player_name(player_name) {};  // Automatic variable initialisation
};


//
class GameModel{

    private:

        // Players are linked here, indexed by there player_name
        std::map<std::string, Player*> players;

    public:

        // Game state
        bool is_running = false;

        // Constructor
        GameModel() {};

};
