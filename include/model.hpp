//
#pragma once
//
#include <iostream>
#include <map>
#include <string>
#include <string_view>

using namespace std;
typedef unsigned short int usint;


class Player {

    private:

        const string name; // name of the player
        const usint color; // color of the player

    public:

        // Constructor
        Player(const string player_name, const usint player_color)
            : name(player_name), color(player_color) {};  // Automatic variable initialisation
};



class GameModel {

    private:

        // Players are linked here, indexed by there name
        map<string, Player*> players;

    public:

        // Game state
        bool is_running = false;

        // Constructor
        GameModel() {};

};


class Unit {
    
    private:

        usint color;  // owner of the units
        usint defense; // level of the unit

    public:

        // Constructor
        Unit(usint unit_color, usint unit_defense)
            : color(unit_color), defense(unit_defense) {};  // Automatic variable initialisation
        
        // Getters
        usint _color() const;
        usint _defense() const;

        // Functions
        void upgrade(); // Increase unit defense
        void convert_bandit(); // Change the unit into a bandits
};

class Building {

    private:

        usint color;  // owner of the building    
        usint defense; // level of the building

    public:

        // Constructor
        Building(usint building_color, usint building_defense)
            : color(building_color), defense(building_defense) {};  // Automatic variable initialisation
        
        // Getters
        usint _color() const;
        usint _defense() const;

        // Functions
        
};

