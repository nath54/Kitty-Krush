#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <string_view>

#include "geometry.hpp"

using namespace std;
typedef unsigned short int usint;

#define NEUTRAL 0


// ========================= [ Forward declarations ] =========================

class Province;


// ============================== [ Elements ] ================================

class Element {

    protected:

        Coord coord;    // coordinates of the element
        usint color;    // owner of the element
        usint defense;  // level (= defense) of the element

    public:

        // Constructor
        Element () {}; // Default constructor
        Element(Coord element_coord, usint element_color, usint element_defense = 0)
            : coord(element_coord), color(element_color), defense(element_defense) {};
        // Destructor
        virtual ~Element() {}; // Virtual destructor

        // Getters
        Coord _coord() const;
        usint _color() const;
        usint _defense() const;

        // Other functions
        virtual int get_upkeep_cost() = 0; // Return the upkeep cost of the element
        virtual void convert_bandit() = 0; // Change the element into a bandit element
};


class Unit : public Element {

    public:

        // Additional Attribute
        bool can_move = true;

        // Constructor
        Unit(Coord unit_coord, usint unit_color, usint unit_defense = 1)
            : Element(unit_coord, unit_color, unit_defense) {};
        // Destructor
        ~Unit() {}; // Default destructor

        // Other Functions
        void upgrade(); // Increase unit level
        int get_upkeep_cost() override;
        void convert_bandit() override;
};


class Building : public Element {

    public:

        // Additional Attribute
        int treasury = 0;

        // Constructor
        Building(Coord building_coord, usint building_color, usint building_defense = 1)
                : Element(building_coord, building_color, building_defense) {}
        // Destructor
        ~Building() {}; // Default destructor

        // Other Functions
        bool is_town() const; // Return true if town, false if tower
        void update_treasury(int change);
        int get_upkeep_cost() override;
        void convert_bandit() override;
};


// ================================= [ Map ] ==================================

class Tile {

    private:

        Coord coord; // coordinates of the tile
        usint color; // owner of the tile
        Element* element; // element on the tile (unit or building)

    public:

        // Constructor
        Tile(Coord tile_coord, usint tile_color=NEUTRAL, Element* tile_element=nullptr)
            : coord(tile_coord), color(tile_color), element(tile_element) {};
        // Destructor
        ~Tile() {}; // Default destructor

        // Getters
        Coord _coord() const;
        usint _color() const;
        Element* _element() const;

        // Other functions
        usint get_defense() const;
        void convert_color(usint new_color);
        void set_element(Element* element);
        void delete_element();
};


//
class Province {

    private:

        usint color; // owner of the province
        int treasury; // treasury of the province
        std::map<Coord, Tile*> tiles_layer; // tiles of the province

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
    std::map<Coord, Tile*>* _tiles();

    // Getters (undirects)
    std::list<Building*> get_buildings();

    // Setters
    void set_color(usint new_color);
    void set_treasury(int new_treasury);

    // Functions: tiles
    bool has_tile(Coord c);
    void add_tile(Tile* tile);
    void remove_tile(Tile* tile);
    void remove_tile_at_coord(Coord c);

    // Functions: treasury
    int expected_income();
    void treasury_turn();
    void add_treasury(int amount);
    void remove_treasury(int amount);

    // Other functions
    bool is_adjacent_to_coord(Coord c);
};


class Map {

    private:

        usint size = 100;
        std::map<Coord, Tile*> tiles_layer;
        std::map<Coord, Element*> bandits_layer;
        std::vector<Province*> provinces_layer;
        std::list<Province*> provinces_to_remove;

    public:

        // Constructor
        Map() {}; // Default constructor
        Map(usint map_size) : size(map_size) {}
        // Destructor
        ~Map() {}; // Default destructor

        // Getters
        usint _size() const;
        std::map<Coord, Tile*>* _tiles_layer();
        std::map<Coord, Element*>* _bandits_layer();
        std::vector<Province*>* _provinces_layer();
        std::list<Province*>* _provinces_to_remove();

        // Getters (undirects)
        Tile* get_tile(Coord c);
        int get_tile_color(Coord c);
        Element* get_tile_element(Coord c);
        Province* get_province(Coord c);
        std::list<Building*> get_all_buildings(bool with_bandit_buildings=false);

        // Setters
        void set_tile(Coord c, Tile* new_tile);
        void set_tile_color(Coord c, int color);
        void set_tile_element(Coord c, usint elt_level, bool is_unit, int elt_attribute = 0);

        // Resetters
        void reset_tiles_layer();
        void reset_bandits_layer();
        void reset_provinces_layer();

        // Initialization
        void recursive_fill(Coord c, unsigned int nb_cover, usint color_cover, Province* p = nullptr);
        void init_map(usint nb_players, int nb_provinces, int size_provinces, bool bandits);

        // Provinces managment
        void add_province(Province* p);
        void add_province_from_list_of_tiles(std::list<Coord> tiles_list, int color = -1, bool with_treasury = false, int treasury = 0);
        void remove_province(Province* p);
        void fusion_provinces(Province* p1, Province* p2);
        void split_province(Coord c, Province* p);
        void remove_tile_of_all_provinces(Coord c);
        bool adjacent_to_province(Coord c, Province* p);
};


// ============================ [ Game Model ] ================================


class GameModel {

    private:

        Map* game_map = nullptr; // Map of the game
        usint nb_players = 2; // Number of players
        usint current_player = 1; // Current player color

    //
    public:

        // Game state (additional attribute)
        bool is_running = false;

        // Constructor
        GameModel() { this->game_map = new Map(); };

        // Getters
        Map* _map();
        usint _nb_players();
        usint _current_player();

        // Getters (undirect)
        int get_tile_color(Coord c);
        usint get_tile_defense(Coord c);
        Element* get_tile_element(Coord c);
        Province* get_tile_province(Coord c);
        Province* get_province_at_coord(Coord c);

        // Setters
        void set_tile_color(Coord coord, usint color);
        void set_tile_element(Coord c, usint elt_level, bool is_unit, int element_attribute=0);
        void set_current_player(int new_player);

        // Resetters
        void reset_provinces();
        void reset_tiles_layer();
        void reset_bandits_layer();

        // Turns
        void at_player_turn_start();
        void bandit_turn();

        // Check and Do
        bool check_action_move_unit(Coord src, Coord dst);
        void do_action_move_unit(Coord src, Coord dst);
        //
        bool check_action_new_element(Coord c, int elt_level, bool is_unit);
        void do_action_new_element(Coord c, int elt_level, bool is_unit);
        //
        bool check_action_end_turn();
        void do_action_end_turn();

        // Other functions
        void calculate_all_provinces_after_map_initialisation();
};


// ========================== [ Utility functions ] ===========================

usint max(usint a, usint b);

bool is_adjacent(Coord c1, Coord c2);

vector<Coord> neighbours(Coord c);

