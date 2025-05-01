# include <cstdlib> // For rand()
# include <ctime>   // For time()
# include <algorithm> // For remove()
# include <deque>     // For std::deque
# include <iostream>

# include "model_map.hpp"


// ============================== [ Tile ] ====================================

// >> Getters <<
Coord Tile::_coord() const { return this->coord; }
int Tile::_color() const { return this->color; }
ELEMENT_T Tile::_element() const { return this->element; }


// >> Other functions <<
int Tile::get_defense() const { return (this->element != nullptr) ? this->element->_defense() : 0; }

void Tile::convert_color(int new_color) { this->color = new_color; }

void Tile::set_element(ELEMENT_T e)
{
    if (this->element != nullptr) {
        // delete this->element;
    }
    this->element = e;
}

void Tile::reset_element()
{ this->element = nullptr; }


// ============================== [ Province ] ================================

// >> Getters <<

int Province::_color() const { return this->color; }
int Province::_treasury() const { return this->treasury; }
std::map<Coord, TILE_T>* Province::_tiles() { return &(this->tiles_layer); }


// >> Getters (undirect) <<

std::list<BUILDING_T> Province::get_buildings()
{
    std::list<BUILDING_T> buildings;

    for (std::pair<Coord, TILE_T> it : this->tiles_layer) {

        BUILDING_T b = DCAST_BUILDING_T(it.second->_element());
        if (b != nullptr) buildings.push_back(b);
    }

    return buildings;
}


// >> Setters <<

void Province::set_color(int new_color) { this->color = new_color; }
void Province::set_treasury(int new_treasury) { this->treasury = new_treasury; };


// >> Functions: tiles <<

bool Province::has_tile(Coord c) { return (this->tiles_layer.count(c) > 0); }

void Province::add_tile(TILE_T tile)
{
    if (tile == nullptr) { return; }
    tile->convert_color(this->color);
    this->tiles_layer[tile->_coord()] = tile;
}

void Province::remove_tile(TILE_T tile) { tiles_layer.erase(tile->_coord()); }


// >> Functions: treasury <<

int Province::expected_income()
{
    int income = 0;

    for (const auto& t : tiles_layer) {
        income++;

        if (t.second->_element() != nullptr) {
            if (t.second->_element()->_defense() == 0) income--; // bandit
            else income -= t.second->_element()->get_upkeep_cost();
        }
    }

    return income;
}


void Province::treasury_turn() { this->treasury += this->expected_income(); }


void Province::add_treasury(int amount) { this->treasury += amount; }

void Province::remove_treasury(int amount) { this->treasury -= amount; }


// >> Other functions <<

bool Province::is_adjacent_to_coord(Coord c)
{
    if (this->has_tile(c)) { return true; }

    for (std::pair<Coord, TILE_T> it : this->tiles_layer)
        { if (is_adjacent(it.first, c)) { return true; } }

    return false;
}


// ============================= [ Map ] ======================================

// >> Getters <<

int Map::_size() const { return size; }
std::map<Coord, TILE_T>* Map::_tiles_layer() { return &(this->tiles_layer); }
std::map<Coord, ELEMENT_T>* Map::_bandits_layer() { return &(this->bandits_layer); }
std::vector<PROVINCE_T>* Map::_provinces_layer() { return &(this->provinces_layer); }
std::list<PROVINCE_T>* Map::_provinces_to_remove() { return &(this->provinces_to_remove); }


// >> Getters (undirect) <<

TILE_T Map::get_tile(Coord c) { return (this->tiles_layer.count(c) == 0) ? nullptr : this->tiles_layer[c]; }

int Map::get_tile_color(Coord c)
{
    TILE_T tile = this->get_tile(c);
    return (tile != nullptr) ? (int)tile->_color() : -1;
}

ELEMENT_T Map::get_tile_element(Coord c)
{
    TILE_T tile = this->get_tile(c);
    return (tile != nullptr) ? tile->_element() : nullptr;
}

PROVINCE_T Map::get_province(Coord c)
{
    TILE_T tile = this->get_tile(c);
    if (tile == nullptr || tile->_color() == NEUTRAL) { return nullptr; }

    for (PROVINCE_T p : this->provinces_layer)
        { if (p->has_tile(c)) { return p; } }

    return nullptr;
}

std::list<BUILDING_T> Map::get_all_buildings(bool with_bandit_buildings)
{
    std::list<BUILDING_T> buildings;

    for (PROVINCE_T p : this->provinces_layer)
        buildings.splice(buildings.end(), p->get_buildings());

    if (!with_bandit_buildings) return buildings;

    for (std::pair<Coord, ELEMENT_T> it : this->bandits_layer) {
        BUILDING_T b = DCAST_BUILDING_T(it.second);
        if (b != nullptr) buildings.push_back(b);
    }

    return buildings;
}


// >> Setters <<

void Map::set_tile(Coord c, TILE_T new_tile)
{
    TILE_T tile = this->get_tile(c);
    if (tile != nullptr) {
        // delete tile;
    }
    this->tiles_layer[c] = new_tile;
}

void Map::set_tile_color(Coord c, int color)
{
    TILE_T tile = this->get_tile(c);

    if (tile == nullptr) {
        tile = CREATE_TILE_T(c);
        this->set_tile(c, tile);
    }

    tile->convert_color(color);
}


void Map::set_tile_element(Coord c, int elt_level, bool is_unit, int elt_attribute)
{
    TILE_T tile = this->get_tile(c);

    if (tile == nullptr) {
        tile = CREATE_TILE_T(c);
        this->set_tile(c, tile);
    }

    if (elt_level < 0)
        { tile->set_element(nullptr); }

    if (is_unit) {
        UNIT_T u = CREATE_UNIT_T(tile->_color(), elt_level);
        u->can_move = !(elt_attribute == 1);
        tile->set_element(u);
    }
    //
    else {
        BUILDING_T b = CREATE_BUILDING_T(tile->_color(), elt_level);
        b->treasury = elt_attribute;
        tile->set_element(b);
    }
}


// >> Resetters <<

void Map::reset_tiles_layer() { this->tiles_layer.clear(); }
void Map::reset_bandits_layer() { this->bandits_layer.clear(); }
void Map::reset_provinces_layer() { this->provinces_layer.clear(); }


// >> Initialization <<

void Map::recursive_fill(Coord c, unsigned int nb_cover, int color_cover, PROVINCE_T p)
{
    if (color_cover == NEUTRAL) {
        if (tiles_layer.size() >= nb_cover) { return; } // inhaf NEUTRAL
        if (tiles_layer.count(c) != 0) { return; } // already exists
        tiles_layer.insert({c, CREATE_TILE_T(c, color_cover)});
    }
    //
    else {
        TILE_T tile = get_tile(c);
        if (tile == nullptr) { return; }
        if (tile->_color() != NEUTRAL) { return; }

        if (p == nullptr) {
            p = CREATE_PROVINCE_T(color_cover);
            p->add_treasury(7);
            add_province(p);
            tile->set_element(CREATE_BUILDING_T(color_cover));
        }

        if (p->_tiles()->size() >= nb_cover) { return; } // inhaf cover
        p->add_tile(tile);
    }

    for (auto n : neighbours(c))
        { if (rand() % 2) { recursive_fill(n, nb_cover, color_cover, p); } }
}


void Map::init_map(int nb_players, int nb_prov, int size_prov, bool bandits)
{

    // Initialize the random seed
    srand(static_cast<unsigned int>(time(0)));
    int seed_x = rand() % this->size;
    int seed_y = rand() % this->size;
    Coord seed(seed_x, seed_y);

    // Create the map NEUTRAL
    unsigned int nb_neutral = 0;
    recursive_fill(seed, (this->size*this->size/3), NEUTRAL, nullptr);

    // Add players' provinces
    for (int p=1; p<=nb_players; p++) {
        for (int n=0; n<=nb_prov; n++) {
            // Get a random tile
            seed.x = rand() % this->size;
            seed.y = rand() % this->size;

            while (tiles_layer.count(seed) == 0
                    || tiles_layer[seed]->_color() != NEUTRAL)
                { seed.x = rand() % this->size; seed.y = rand() % this->size; }

            recursive_fill(seed, size_prov, p, nullptr);
        }
    }

    if (bandits) {
        seed.x = rand() % this->size;
        seed.y = rand() % this->size;

        while (tiles_layer.count(seed) == 0
                || tiles_layer[seed]->_color() != NEUTRAL)
            { seed.x = rand() % this->size; seed.y = rand() % this->size; }

        tiles_layer[seed]->set_element(CREATE_BUILDING_T(NEUTRAL));
        DCAST_BUILDING_T(tiles_layer[seed]->_element())->update_treasury(3);
        bandits_layer[seed] = tiles_layer[seed]->_element();

        while (tiles_layer.count(seed) == 0
                || tiles_layer[seed]->get_defense() != 0)
            { seed.x = rand() % this->size; seed.y = rand() % this->size; }

        tiles_layer[seed]->set_element(CREATE_UNIT_T(NEUTRAL, 0));
        bandits_layer[seed] = tiles_layer[seed]->_element();
    }
}


// >> Provinces managment <<

void Map::add_province(PROVINCE_T p) { this->provinces_layer.push_back(p); }


void Map::add_province_from_list_of_tiles(std::list<Coord> tiles_list, int color, bool with_treasury, int treasury)
{
    PROVINCE_T p = CREATE_PROVINCE_T();

    if (color == -1)
        color = this->get_tile_color(tiles_list.front());

    p->set_color(color);
    p->set_treasury(with_treasury ? treasury : tiles_list.size());

    for (Coord c : tiles_list) {
        TILE_T tile = this->get_tile(c);
        if (tile != nullptr) { p->add_tile(tile); }
    }

    this->add_province(p);
}


void Map::remove_province(PROVINCE_T p)
{
    this->provinces_layer.erase(
        std::remove(this->provinces_layer.begin(), this->provinces_layer.end(), p),
        this->provinces_layer.end()
    );

    this->_provinces_to_remove()->push_back(p);
}


void Map::fusion_provinces(PROVINCE_T p1, PROVINCE_T p2)
{
    if (p1 == nullptr || p2 == nullptr) { return; }
    if (p1 == p2) { return; }
    if (p1->_color() != p2->_color()) { return; }

    for (auto& t : *(p2->_tiles())) { p1->add_tile(t.second); }
    p1->add_treasury(p2->_treasury());
    remove_province(p2);
    // delete p2;
}


void Map::split_province(Coord c, PROVINCE_T p)
{
    int color = p->_color();

    std::map<Coord, int> visited;
    std::map<int, int> to_convert_num;

    std::deque<Coord> to_visit_coord;
    std::deque<int> to_visit_num;

    int nb_tot_nums = 0;

    // INIT

    std::vector<Coord> nbs = neighbours(c);

    for (Coord i : nbs) {

        TILE_T tile_nb = this->get_tile(i);
        if (tile_nb == nullptr) { continue; }
        if (tile_nb->_color() != color) { continue; }

        to_visit_coord.push_back(i);
        to_visit_num.push_back(nb_tot_nums);

        nb_tot_nums += 1;
    }

    // WHILE THERE ARE TILES TO VISIT

    while (to_visit_coord.size() > 0) {

        Coord v = to_visit_coord.front();
        int num = to_visit_num.front();

        if (to_convert_num.count(num) > 0)
            { num = to_convert_num[num]; }

        to_visit_coord.pop_front();
        to_visit_num.pop_front();

        if (visited.count(v) > 0) { continue; }

        visited[v] = num;

        for (Coord vv : neighbours(v)) {

            int color2 = this->get_tile_color(vv);

            if (color2 == -1 || color != color2) { continue; }

            if (visited.count(vv) > 0) {

                if (visited[vv] == num) { continue; }

                // else...
                to_convert_num[visited[vv]] = num;

                // Change all the different number to the same number for connex zones
                for (std::pair<Coord, int> it : visited) {
                    if (it.second == visited[vv])
                        { visited[it.first] = num; }
                }

                continue;
            }

            to_visit_coord.push_back(vv);
            to_visit_num.push_back(num);
        }
    }

    // Extract all the different new zones

    int nb_differents = nb_tot_nums - to_convert_num.size();

    if (nb_differents < 1) { return; } // No split to do

    int crt_idx = 0;
    std::map<int, int> num_idx;
    std::vector< std::list<Coord> > areas;

    for (std::pair<Coord, int> it : visited) {

        int num = it.second;

        if( to_convert_num.count(num) > 0)
            { num = to_convert_num[num]; }

        if (num_idx.count(num) == 0) {
            num_idx[num] = crt_idx;
            crt_idx++;
            areas.push_back((std::list<Coord>){});
        }

        areas[num_idx[num]].push_back(it.first);
    }

    std::list<PROVINCE_T> new_provinces;
    int nb_tiles_of_split_prov = 0;

    for (int i = 0; i < areas.size(); i++) {

        // Check if there is a town in the splited zone
        bool town = false;

        for (Coord cc : areas[i]) {

            TILE_T t = this->get_tile(cc);

            if (t == nullptr || t->_element() == nullptr) { continue; }

            BUILDING_T b = DCAST_BUILDING_T(t->_element());

            if (b == nullptr || b->_color() == NEUTRAL) { continue; }

            if (b->_defense() == 1) { town = true; break; }
        }

        if (!town) {
            // Remove the tiles which no longer belong to the province
            for (Coord cc : areas[i]) {

                TILE_T t = this->get_tile(cc);
                if (t == nullptr) { continue; }

                ELEMENT_T elt = t->_element();
                if (elt != nullptr)
                    { this->bandits_layer[cc] = elt; }

                // this->set_tile_color(cc, NEUTRAL); // let colored tiles

                this->remove_tile_from_all_prov(cc);
            }
        }

        else {
            // Create a CREATE_PROVINCE_T and add it all the tiles
            PROVINCE_T pp = CREATE_PROVINCE_T(p->_color());

            for (Coord cc : areas[i]) {
                pp->add_tile(this->get_tile(cc));
                nb_tiles_of_split_prov++;
            }

            new_provinces.push_back(pp);
        }
    }

    for (PROVINCE_T pp : new_provinces) {
        pp->set_treasury((int) ((float)(p->_treasury()) * ((float)(pp->_tiles()->size()) / (float)(nb_tiles_of_split_prov))));
        this->add_province(pp);

        // ? DEBUG: std::cout << "Province " << pp->_color() << " created with " << pp->_tiles()->size() << " tiles and a treasury of " << pp->_treasury() << std::endl;
    }

    this->remove_province(p);
}


void Map::remove_tile_from_all_prov(Coord c)
{
    for (PROVINCE_T p : this->provinces_layer) {
        if (p->has_tile(c)) { p->_tiles()->erase(c) ; }
    }
}


bool Map::adjacent_to_province(Coord c, PROVINCE_T p)
{
    if (this->get_province(c) == p) { return true; }

    std::vector<Coord> n = neighbours(c);
    for (auto& t : n)
        { if (this->get_province(t) == p) { return true; } }

    return false;
}


bool Map::has_province_of_color(int color)
{
    for( PROVINCE_T p : this->provinces_layer )
        { if (p->_color() == color) { return true; } }

    return false;
}


// >> Bandits managment <<
// Checks are done in bandit_turn function

void Map::create_bandit_element(Coord c, bool is_unit)
{
    if (is_unit) {
        UNIT_T u = CREATE_UNIT_T(NEUTRAL, 0);
        this->get_tile(c)->set_element(u);
        this->bandits_layer[c] = u;
    }
    //
    else {
        BUILDING_T b = CREATE_BUILDING_T(NEUTRAL);
        this->get_tile(c)->set_element(b);
        this->bandits_layer[c] = b;
    }
}


void Map::move_bandit(Coord src, Coord dst)
{
    ELEMENT_T bandit = this->bandits_layer[src];
    this->bandits_layer.erase(src);
    this->bandits_layer[dst] = bandit;
    this->get_tile(src)->reset_element();
    this->get_tile(dst)->set_element(bandit);
}


void Map::delete_bandit_element(Coord c)
{
    this->bandits_layer.erase(c);
    this->get_tile(c)->set_element();
}


