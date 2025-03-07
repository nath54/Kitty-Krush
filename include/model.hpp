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

        usint x;       // x position of the element
        usint y;       // y position of the element
        usint color;  // owner of the element 
        usint defense; // level (= defense) of the element

    public:

        // Constructor
        Element () {}; // Default constructor
        // Destructor
        virtual ~Element() {}; // Virtual destructor

        // Getters
        virtual usint _x() const;
        virtual usint _y() const;
        virtual usint _color() const;
        virtual usint _defense() const;
};


class Unit : public Element {

    private:

        usint x;
        usint y;
        usint color;
        usint defense;

    public:

        // Constructor
        Unit(usint unit_x, usint unit_y, usint unit_color, usint unit_defense)
            : x(unit_x), y(unit_y), color(unit_color), defense(unit_defense) {};
        // Destructor
        ~Unit() {}; // Default destructor

        // Functions
        void upgrade(); // Increase unit defense
        void convert_bandit(); // Change the unit into a bandits
};


class Building : public Element {

    private:

        usint x;
        usint y;
        usint color;
        usint defense;

    public:

        // Constructor
        Building(usint building_x, usint building_y, usint building_color, usint building_defense)
            : x(building_x), y(building_y), color(building_color), defense(building_defense) {};
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

        usint size;
        vector<Tile*> tiles_layer;
        vector<Element*> elements_layer;

    public:

    // Constructor
    Map(usint map_size) : size(map_size) {
        // Create the map
        for (usint i = 0; i < size; i++) {
            for (usint j = 0; j < size; j++) {
                tiles_layer.push_back(new Tile(i, j));
            }
        }
    };
    // Destructor
    ~Map() {}; // Default destructor

    // Getters
    usint _size() const;
};



class GameModel {

    private:

        // Players are linked here, indexed by there name
        map<string, Player*> players;
        Map* game_map;

    public:

        // Game state
        bool is_running = false;

        // Constructor
        GameModel() {};
};



