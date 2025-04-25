#include <map>
#include <list>

#include "model_element.hpp"

#define NEUTRAL 0

// Forward declaration
class Province;


// ================================= [ Tile ] =================================

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


// ================================ [ Province ] ==============================

class Province {

    private:

        usint color; // owner of the province
        int treasury; // treasury of the province
        std::map<Coord, Tile*> tiles_layer; // tiles of the province

    public:

    // Constructor
    Province() {}; // Default constructor
    Province(usint c, int t=0, std::map<Coord, Tile*> tiles=(std::map<Coord, Tile*>){})
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


// ================================ [ Map ] ===================================

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
