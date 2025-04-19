//
#pragma once
//
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <deque>
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

    public:

        // Constructor
        Element () {}; // Default constructor
        Element(Coord element_coord,
                usint element_color,
                usint element_defense = 0)
            : coord(element_coord), color(element_color), defense(element_defense) {};
        // Destructor
        virtual ~Element() {}; // Virtual destructor

        // Getters
        Coord _coord() const;
        usint _color() const;
        usint _defense() const;

        //
        virtual int get_upkeep_cost();
};


//
class Unit : public Element {

    public:

        // Constructor
        Unit(Coord unit_coord,
            usint unit_color,
            usint unit_defense = 1)
            : Element(unit_coord, unit_color, unit_defense) {};
        // Destructor
        ~Unit() {}; // Default destructor

        // Functions
        void upgrade(); // Increase unit defense
        void convert_bandit(); // Change the unit into a bandits

        //
        int get_upkeep_cost();
};


//
class Building : public Element {

    public:

        // Constructor
        Building(Coord building_coord,
                 usint building_color,
                 usint building_defense = 1)
            : Element(building_coord, building_color, building_defense) {};
        // Destructor
        ~Building() {}; // Default destructor

        // Functions
        bool is_town() const; // Return true if town, false if tower

        //
        int get_upkeep_cost();
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
        void set_element(Element* element);
        void delete_element();
};


//
class Province {

    private:

        usint color;
        int treasury;
        std::map<Coord, Tile*> tiles_layer;

    public:

    // Constructor
    Province() {}; // Default constructor
    Province(usint c, int t=0, map<Coord, Tile*> tiles=(std::map<Coord, Tile*>){})
        : color(c), treasury(t), tiles_layer(tiles) {};
    // Destructor
    ~Province() {}; // Default destructor
    // delete vectors but NOT their content

    // Getters
    usint _color() const;
    int _treasury() const;
    map<Coord, Tile*> _tiles() const;
    bool has_tile(Coord c);

    // Setters
    void set_color(usint new_color);
    void set_treasury(int new_treasury);

    // Functions
    void add_tile(Tile* tile);
    void remove_tile(Tile* tile);

    int expected_income();
    void treasury_turn();
    void add_treasury(int amount);
    void remove_treasury(int amount);
};


//
class Map {

    private:

        usint size = 100;
        std::map<Coord, Tile*> tiles_layer;
        std::map<Coord, Element*> bandits_layer;
        std::vector<Province*> provinces_layer;

    public:

        // Constructor
        Map() {}; // Default constructor
        Map(usint map_size) : size(map_size) {}
        // Destructor
        ~Map() {}; // Default destructor

        // Functions
        usint _size() const;
        //
        Tile* get_tile(Coord c);
        Element* get_tile_entity(Coord c);
        int get_tile_color(Coord c);
        Province* get_province(Coord c);
        //
        std::map<Coord, Tile*>* get_tiles_layer();
        std::map<Coord, Element*>* get_bandits_layer();
        std::vector<Province*>* get_provinces_layer();
        //
        void reset_tiles_layer();
        void reset_provinces_layer();
        void reset_bandits_layer();
        //
        void set_tile(Coord coord, Tile* tile);
        void set_tile_entity(Coord coord, int entity_level, bool entity_type);
        void set_tile_color(Coord coord, int tile_color);
        //
        void add_province_from_list_of_tiles(std::list<Coord> tiles_list, int color = -1, bool with_treasury = false, int treasury = 0);

        void recursive_fill(Coord c, unsigned int nb_cover, usint cover, Province* province);
        void init_map(usint nb_players, int nb_provinces, int size_provinces, bool bandits);

        void add_province(Province* province);
        bool adjacent_to_province(Province* p, Coord c);
        void remove_province(Province* province);
        void fusion_provinces(Province* p1, Province* p2);
        void split_province(Coord c);
};


// ========== [ Game Model ] ==========


class GameModel {

    private:

        //
        Map* game_map = nullptr;

        //
        int nb_players_colors = 2;
        int current_player_color = 1;

    //
    public:

        // Game state
        bool is_running = false;

        // Constructor
        GameModel();

        //
        Province* get_province_at_coord(Coord c);

        //
        int get_nb_players_colors();

        //
        void at_player_turn_start();

        //
        bool check_player_action_move_entity(Coord src, Coord dst);

        //
        void do_player_action_move_entity(Coord src, Coord dst);

        //
        bool check_player_action_new_entity(Coord dst, int entity_level, bool entity_type);

        //
        void do_player_action_new_entity(Coord dst, int entity_level, bool entity_type);

        //
        bool check_player_action_end_turn();

        //
        void do_player_action_end_turn();

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
        void calculate_all_provinces_after_map_initialisation();

        //
        void reset_bandits_layer();

        //
        void reset_tiles_layer();

        //
        void reset_provinces();

};


// ========== [ Tools functions ] ==========

//
usint max(usint a, usint b);

//
bool is_adjacent(Coord c1, Coord c2);

//
vector<Coord> neighbours(Coord c);

