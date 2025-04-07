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

#define LOCK -1
#define NEUTRAL 0


// ========== [ Forward Definition ] ==========

class Province;


// ========== [ Players ] ==========


class Player {

    private:

        const string name; // name of the player
        const short color; // color of the player

    public:

        // Constructor
        Player(const string player_name, const short player_color)
            : name(player_name), color(player_color) {};  // Automatic variable initialisation

        // Getters
        string _name() const;
        short _color() const;
};


// ========== [ Game Elements ] ==========


class Element {

    protected:

        usint x;        // x position of the element
        usint y;        // y position of the element
        short color;    // owner of the element
        usint defense;  // level (= defense) of the element
        usint cost;     // Cost of the element

    public:

        // Constructor
        Element () {}; // Default constructor
        Element(usint element_x,
                usint element_y,
                short element_color,
                usint element_defense = 0,
                usint element_cost = 0)
            : x(element_x), y(element_y), color(element_color), defense(element_defense), cost(element_cost) {};
        // Destructor
        virtual ~Element() {}; // Virtual destructor

        // Getters
        usint _x() const;
        usint _y() const;
        short _color() const;
        usint _defense() const;
        usint _cost() const;
};


class Unit : public Element {

    private:

        usint x;
        usint y;
        short color;
        usint defense;
        usint cost;

    public:

        // Constructor
        Unit(usint unit_x,
            usint unit_y,
            short unit_color,
            usint unit_defense = 1,
            usint unit_cost = 2)
            : Element(unit_x, unit_y, unit_color, unit_defense, unit_cost) {};
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
        short color;
        usint defense;
        usint cost;

    public:

        // Constructor
        Building(usint building_x,
                 usint building_y,
                 short building_color,
                 usint building_defense = 1,
                 usint building_cost = 0)
            : Element(building_x, building_y, building_color, building_defense, building_cost) {};
        // Destructor
        ~Building() {}; // Default destructor

        // Functions
        bool is_town() const; // Return true if town, false if tower
};


// ========== [ Map ] ==========


class Tile {

    private:

        usint x;
        usint y;
        short type;
        usint defense;
        Element* element;

    public:

        // Constructor
        Tile(usint tile_x,
            usint tile_y,
            short tile_type=LOCK,
            usint tile_defense=0,
            Element* tile_element=nullptr)
            : x(tile_x), y(tile_y), type(tile_type), defense(tile_defense), element(tile_element) {};
        // Destructor
        ~Tile() {}; // Default destructor

        // Getters
        usint _x() const;
        usint _y() const;
        short _type() const;
        usint _defense() const;
        Element* _element() const;

        // Functions
        void convert_type(short new_type);
        bool is_adjacent(const Tile* tile);
        bool adjacent_to_province(Province* p);
        void add_element(Element* element);
        void remove_element();
        void delete_element();
};


class Map {

    private:

        usint size;
        usint _size() const;
        void recursive_fill(Tile* tile, unsigned int* current_cover, int nb_cover, int cover, int ground, Province* province);
        void init_map(short nb_players, int nb_provinces, int size_provinces, bool bandits);

    protected:

        vector<Tile*> tiles_layer;
        vector<Element*> elements_layer;
        vector<Province*> provinces_layer;

    public:

    // Constructor
    Map() {}; // Default constructor
    Map(usint map_size) : size(map_size) {
        // Create the map
        for (usint y = 0; y < size; y++) {
            for (usint x = 0; x < size; x++) {
                tiles_layer.push_back(new Tile(y, x));
            }
        }
    };
    // Destructor
    virtual ~Map() {}; // Default destructor

    // Functions
    Tile* get_tile(usint x, usint y);
    Province* get_province(usint x, usint y);
    void add_province(Province* province);
    void remove_province(Province* province);
    vector<Tile*> adjacent_tiles(Tile* tile);
};

class Province : public Map {

    private:

        short color;
        int treasury;
        vector<Tile*> tiles_layer;

    public:

    // Constructor
    Province(short c, int t=0, vector<Tile*> tiles=vector<Tile*>())
        : color(c), treasury(t), tiles_layer(tiles) {};
    // Destructor
    ~Province() override {}; // Default destructor
    // delete vectors but NOT their content

    // Getters
    short _color() const;
    int _treasury() const;
    vector<Tile*> _tiles() const;

    // Functions
    void add_tile(Tile* tile);
    void remove_tile(Tile* tile);
    void treasury_turn();
    void add_treasury(int amount);
    void remove_treasury(int amount);
};


// ========== [ Game Model ] ==========


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


// ========== [ Tools functions ] ==========

usint max(usint a, usint b);

