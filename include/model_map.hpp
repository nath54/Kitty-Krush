#pragma once

#include <map>
#include <list>
#include <memory>

#include "model_element.hpp"

#define NEUTRAL 0


// Forward declaration
class Province;

// =============================== [ Pointers ] ===============================


#define TILE_T std::shared_ptr<Tile>
#define PROVINCE_T std::shared_ptr<Province>


#define CREATE_TILE_T(...) std::make_shared<Tile>(__VA_ARGS__)
#define CREATE_PROVINCE_T(...) std::make_shared<Province>(__VA_ARGS__)

// ================================= [ Tile ] =================================

class Tile {

    private:

        Coord coord; // coordinates of the tile
        int color; // owner of the tile
        ELEMENT_T element; // element on the tile (unit or building)

    public:

        // Constructor
        Tile(Coord tile_coord, int tile_color=NEUTRAL, ELEMENT_T tile_element=nullptr)
            : coord(tile_coord), color(tile_color), element(tile_element) {};
        // Destructor
        ~Tile() {}; // Default destructor

        // Getters
        Coord _coord() const;
        int _color() const;
        ELEMENT_T _element() const;

        // Other functions
        int get_defense() const;
        void convert_color(int new_color);
        void set_element(ELEMENT_T element = nullptr);
        void reset_element();
};


// ================================ [ Province ] ==============================

class Province {

    private:

        int color; // owner of the province
        int treasury; // treasury of the province
        std::map<Coord, TILE_T> tiles_layer; // tiles of the province

    public:

    // Constructor
    Province() {}; // Default constructor
    Province(int c, int t=0, std::map<Coord, TILE_T> tiles=(std::map<Coord, TILE_T>){})
            : color(c), treasury(t), tiles_layer(tiles) {};
    // Destructor
    ~Province() {}; // Default destructor
    // delete vectors but NOT their content

    // Getters
    int _color() const;
    int _treasury() const;
    std::map<Coord, TILE_T>* _tiles();

    // Getters (undirects)
    std::list<BUILDING_T> get_buildings();

    // Setters
    void set_color(int new_color);
    void set_treasury(int new_treasury);

    // Functions: tiles
    bool has_tile(Coord c);
    void add_tile(TILE_T tile);
    void remove_tile(TILE_T tile);

    // Functions: treasury
    int expected_income();
    void treasury_turn();
    void add_treasury(int amount);
    void remove_treasury(int amount);

    // Other functions
    bool is_adjacent_to_coord(Coord c);
};


// ================================ [ Map ] ===================================

class Map {

    private:

        int size = 100;
        std::map<Coord, TILE_T> tiles_layer;
        std::map<Coord, ELEMENT_T> bandits_layer;
        std::vector<PROVINCE_T> provinces_layer;
        std::list<PROVINCE_T> provinces_to_remove;

    public:

        // Constructor
        Map() {}; // Default constructor
        Map(int map_size) : size(map_size) {}
        // Destructor
        ~Map() {}; // Default destructor

        // Getters
        int _size() const;
        std::map<Coord, TILE_T>* _tiles_layer();
        std::map<Coord, ELEMENT_T>* _bandits_layer();
        std::vector<PROVINCE_T>* _provinces_layer();
        std::list<PROVINCE_T>* _provinces_to_remove();

        // Getters (undirects)
        TILE_T get_tile(Coord c);
        int get_tile_color(Coord c);
        ELEMENT_T get_tile_element(Coord c);
        PROVINCE_T get_province(Coord c);
        std::list<BUILDING_T> get_all_buildings(bool with_bandit_buildings=false);

        // Setters
        void set_tile(Coord c, TILE_T new_tile);
        void set_tile_color(Coord c, int color);
        void set_tile_element(Coord c, int elt_level, bool is_unit, int elt_attribute = 0);

        // Resetters
        void reset_tiles_layer();
        void reset_bandits_layer();
        void reset_provinces_layer();

        // Initialization
        void recursive_fill(Coord c, unsigned int nb_cover, int color_cover, PROVINCE_T p = nullptr);
        void init_map(int nb_players, int nb_provinces, int size_provinces, bool bandits);

        // Provinces managment
        void add_province(PROVINCE_T p);
        void add_province_from_list_of_tiles(std::list<Coord> tiles_list, int color = -1, bool with_treasury = false, int treasury = 0);
        void remove_province(PROVINCE_T p);
        void fusion_provinces(PROVINCE_T p1, PROVINCE_T p2);
        void split_province(Coord c, PROVINCE_T p);
        void remove_tile_from_all_prov(Coord c);
        bool adjacent_to_province(Coord c, PROVINCE_T p);
        bool has_province_of_color(int color);

        // Bandits managment
        void create_bandit_element(Coord c, bool is_unit);
        void move_bandit(Coord src, Coord dst);
        void delete_bandit_element(Coord c);
};
