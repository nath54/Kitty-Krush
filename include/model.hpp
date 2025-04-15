//
#pragma once
//
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <string_view>
//
#include "geometry.hpp"

//
using namespace std;
typedef unsigned short int usint;

//
#define NEUTRAL 0


// ========== [ Forward declarations ] ==========

//
class Province;


// ========== [ Game Elements ] ==========


//
class Element {

    protected:

        Coord coord;    // coordinates of the element
        usint color;    // owner of the element
        usint defense;  // level (= defense) of the element
        usint cost;     // Cost of the element

    public:

        // Constructor
        Element () {}; // Default constructor
        Element(Coord element_coord,
                usint element_color,
                usint element_defense = 0,
                usint element_cost = 0)
            : coord(element_coord), color(element_color), defense(element_defense), cost(element_cost) {};
        // Destructor
        virtual ~Element() {}; // Virtual destructor

        // Getters
        Coord _coord() const;
        usint _color() const;
        usint _defense() const;
        usint _cost() const;
};


//
class Unit : public Element {

    private:

        Coord coord;
        usint color;
        usint defense;
        usint cost;

    public:

        // Constructor
        Unit(Coord unit_coord,
            usint unit_color,
            usint unit_defense = 1,
            usint unit_cost = 2)
            : Element(unit_coord, unit_color, unit_defense, unit_cost) {};
        // Destructor
        ~Unit() {}; // Default destructor

        // Functions
        void upgrade(); // Increase unit defense
        void convert_bandit(); // Change the unit into a bandits
};


//
class Building : public Element {

    private:

        Coord coord;
        usint color;
        usint defense;
        usint cost;
        int treasury;

    public:

        // Constructor
        Building(Coord building_coord,
                 usint building_color,
                 usint building_defense = 1,
                 usint building_cost = 0,
                 int building_treasury = 0)
            : Element(building_coord, building_color, building_defense, building_cost) {};
        // Destructor
        ~Building() {}; // Default destructor

        // Functions
        bool is_town() const; // Return true if town, false if tower
};


// ========== [ Map ] ==========


//
class Tile {

    private:

        Coord coord;
        usint color;
        usint defense;
        Element* element;

    public:

        // Constructor
        Tile(Coord tile_coord,
            usint tile_color=NEUTRAL,
            usint tile_defense=0,
            Element* tile_element=nullptr)
            : coord(tile_coord), color(tile_color), defense(tile_defense), element(tile_element) {};
        // Destructor
        ~Tile() {}; // Default destructor

        // Getters
        Coord _coord() const;
        usint _color() const;
        usint _defense() const;
        Element* _element() const;

        // Functions
        void convert_color(usint new_color);
        bool adjacent_to_province(Province* p);
        void add_element(Element* element);
        void remove_element();
        void delete_element();
};


//
class Province {

    private:

        usint color;
        int treasury;
        map<Coord, Tile*> tiles_layer;

    public:

    // Constructor
    Province() {}; // Default constructor
    Province(usint c, int t=0, map<Coord, Tile*> tiles=map<Coord, Tile*>())
        : color(c), treasury(t), tiles_layer(tiles) {};
    // Destructor
    ~Province() {}; // Default destructor
    // delete vectors but NOT their content

    // Getters
    usint _color() const;
    int _treasury() const;
    map<Coord, Tile*> _tiles() const;

    // Functions
    void add_tile(Tile* tile);
    void remove_tile(Tile* tile);

    void treasury_turn();
    void add_treasury(int amount);
    void remove_treasury(int amount);
};


//
class Map {

    private:

        usint size;
        map<Coord, Tile*> tiles_layer;
        map<Coord, Element*> elements_layer;
        vector<Province*> provinces_layer;

    public:

        // Constructor
        Map() {}; // Default constructor
        Map(usint map_size) : size(map_size) {}
        // Destructor
        ~Map() {}; // Default destructor

        // Functions
        usint _size() const;
        Tile* get_tile(Coord c);

        void recursive_fill(Coord c, unsigned int nb_cover, usint cover, Province* province);
        void init_map(usint nb_players, int nb_provinces, int size_provinces, bool bandits);

        Province* get_province(Coord c);
        void add_province(Province* province);
        void remove_province(Province* province);
        void fusion_provinces(Province* p1, Province* p2);
        void split_province(Coord c);
};


// ========== [ Game Model ] ==========


class GameModel {

    private:

        //
        Map* game_map;

        //
        int nb_players_colors = 2;
        int current_player_color = 1;

    public:

        // Game state
        bool is_running = false;

        // Constructor
        GameModel() {};


        //
        bool player_action_move_entity(Coord src, Coord dst);

        //
        bool player_action_new_entity(Coord dst, int entity_level, bool entity_type);

        //
        bool player_action_end_turn();

        //
        int get_current_player_color();

        //
        Province* get_tile_province(Coord coord);

        //
        Element* get_tile_entity(Coord coord);

        //
        int get_tile_color(Coord coord);

        //
        void set_tile_entity(Coord coord, int entity_level, bool entity_type);

        //
        void set_tile_color(Coord coord, int color);

        //
        void reset_entity_layer();

        //
        void reset_color_layer();

};


// ========== [ Tools functions ] ==========

//
usint max(usint a, usint b);

//
bool is_adjacent(Coord c1, Coord c2);

//
vector<Coord> neighbours(Coord c);

