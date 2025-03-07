//
#pragma once
//
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <string_view>

using namespace std;
typedef unsigned short int usint;

// type of tiles
typedef enum Ground {
    LOCK, // can't be possessed
    NEUTRAL, // can be possessed
    // possessed by player 1-4:
    P1, 
    P2,
    P3,
    P4
} Ground;


// ========== [ Players ] ==========


class Player {

    private:

        const string name; // name of the player
        const usint color; // color of the player

    public:

        // Constructor
        Player(const string player_name, const usint player_color)
            : name(player_name), color(player_color) {};  // Automatic variable initialisation
};


// ========== [ Game Elements ] ==========


class Element {
    
    protected:

        usint color;  // owner of the element 
        usint defense; // level (= defense) of the element

    public:

        // Constructor
        Element () {}; // Default constructor
        // Destructor
        virtual ~Element() {}; // Virtual destructor

        // Getters
        virtual usint _color() const;
        virtual usint _defense() const;
};


class Unit : public Element {

    private:

        usint color;
        usint defense;

    public:

        // Constructor
        Unit(usint unit_color, usint unit_defense)
            : color(unit_color), defense(unit_defense) {};
        // Destructor
        ~Unit() {}; // Default destructor

        // Functions
        void upgrade(); // Increase unit defense
        void convert_bandit(); // Change the unit into a bandits
};


class Building : public Element {

    private:

        usint color;
        usint defense;

    public:

        // Constructor
        Building(usint building_color, usint building_defense)
            : color(building_color), defense(building_defense) {};
        // Destructor
        ~Building() {}; // Default destructor

        // Functions
        
};


// ========== [ Map ] ==========


class Tile {

    private:

        usint x;
        usint y;
        Ground type;

    public:

        // Constructor
        Tile(usint tile_x, usint tile_y, Ground tile_type=NEUTRAL)
            : x(tile_x), y(tile_y), type(tile_type) {};
        // Destructor
        ~Tile() {}; // Default destructor

        // Getters
        usint _x() const;
        usint _y() const;
        Ground _type() const;

        // Functions
        void convert_type(Ground new_type);
        bool is_adjacent(const Tile* tile);
};


class Map {

    private:

        vector<Tile*> tiles_layer;
        vector<Element*> elements_layer;

    public:
};



class GameModel {

    private:

        // Players are linked here, indexed by there name
        map<string, Player*> players;
        Map game_map;

    public:

        // Game state
        bool is_running = false;

        // Constructor
        GameModel() {};
};



