#include "model.hpp"
#include <cstdlib>  // srand() et rand()
#include <ctime> // time()


// ===== Elements =====

Coord Element::_coord() const { return coord; }
usint Element::_color() const { return color; }
usint Element::_defense() const { return defense; }
usint Element::_cost() const { return cost; }

void Unit::upgrade()
{ defense++; cost *= 3; }

void Unit::convert_bandit()
{ color = -1; defense = 0; cost = 0; }

bool Building::is_town() const { return (defense == 1); }


// ===== [ Map ] =====

// --- Tile ---

Coord Tile::_coord() const { return coord; }
usint Tile::_color() const { return color; }
usint Tile::_defense() const { return defense; }
Element* Tile::_element() const { return element; }

void Tile::convert_color(usint new_color)
{ color = new_color; }

bool Tile::adjacent_to_province(Province* p)
{
    for (const auto& t : p->_tiles()) {
        if (is_adjacent(coord, t.first))
            return true;
    }
    return false;
}

void Tile::add_element(Element* e)
{ element = e; }

void Tile::remove_element()
{ element = nullptr; }

void Tile::delete_element()
{
    if (element) delete element;
    element = nullptr;
}

// --- Province ---

usint Province::_color() const { return color; }
int Province::_treasury() const { return treasury; }
map<Coord, Tile*> Province::_tiles() const { return tiles_layer; }


void Province::add_tile(Tile* tile)
{
    if (tiles_layer.find(tile->_coord()) != tiles_layer.end())
        return; // already exists
    tile->convert_color(color);
    tiles_layer.insert({tile->_coord(), tile});
}

void Province::remove_tile(Tile* tile)
{ tiles_layer.erase(tile->_coord()); }

void Province::treasury_turn()
{
    // Income
    for (const auto& t : tiles_layer) {
        if (t.second->_element() != nullptr &&
            t.second->_element()->_cost() == 0) // bandit
            continue;
        else treasury++;
    }
    // Expenses
    for (const auto& t : tiles_layer) {
        if (t.second->_element() == nullptr) continue;
        treasury -= t.second->_element()->_cost();
    }
    // Units management
    if (treasury >= 0) return; // units are paid
    treasury = 0;
    Unit* u = nullptr;
    for (auto& t : tiles_layer) {
        u = dynamic_cast<Unit*>(t.second->_element());
        if (u != nullptr) u->convert_bandit();
    }
}

void Province::add_treasury(int amount)
{ treasury += amount; }

void Province::remove_treasury(int amount)
{ treasury -= amount; }

// ----- Map -----

usint Map::_size() const { return size; }

Tile* Map::get_tile(Coord c)
{ return (tiles_layer.find(c) != tiles_layer.end()) ? tiles_layer[c] : nullptr; }

Province* Map::get_province(Coord c)
{
    Tile * tile = get_tile(c);
    if (tile == nullptr) return nullptr;
    if (tile->_color() == NEUTRAL) return nullptr;
    for (Province* p : provinces_layer) {
        for (auto& t : p->_tiles()) {
            if (t.first.x == c.x && t.first.y == c.y)
                return p;
        }
    }
    return nullptr;
}

void Map::recursive_fill(Coord c, unsigned int nb_cover, usint cover, Province* province=nullptr)
{
    if (cover == NEUTRAL) {
        if (tiles_layer.size() >= nb_cover) return; // inhaf NEUTRAL
        if (tiles_layer.find(c) != tiles_layer.end()) return; // already exists
        tiles_layer.insert({c, new Tile(c, cover)});
    }

    else {
        Tile* tile = get_tile(c);
        if (tile == nullptr) return;
        if (tile->_color() != NEUTRAL) return;

        if (province == nullptr) {
            province = new Province(cover);
            province->add_treasury(7);
            add_province(province);
            tile->add_element(new Building(c, cover));
        }
        if (province->_tiles().size() >= nb_cover) return; // inhaf cover
        province->add_tile(tile);
    }

    for (auto c : neighbours(c))
        if (rand() % 2) recursive_fill(c, nb_cover, cover, province);
}

// ! Gérer le bool bandits
void Map::init_map(usint nb_players, int nb_provinces, int size_provinces, bool bandits)
{

    // Initialize the random seed
    srand(static_cast<unsigned int>(time(0)));
    usint seed_x = rand() % size;
    usint seed_y = rand() % size;

    // Create the map NEUTRAL
    unsigned int nb_neutral = 0;
    recursive_fill(Coord(seed_x, seed_y), (size*size/3), NEUTRAL, nullptr);

    // Add players' provinces
    for (usint p=1; p<=nb_players; p++) {
        for (usint n=0; n<=nb_provinces; n++) {
            // Get a random tile
            seed_x = rand() % size;
            seed_y = rand() % size;

            while (tiles_layer.find(Coord(seed_x, seed_y)) == tiles_layer.end()
                    || tiles_layer[Coord(seed_x, seed_y)]->_color() != NEUTRAL)
                { seed_x = rand() % size; seed_y = rand() % size; }

            recursive_fill(Coord(seed_x, seed_y), size_provinces, p, nullptr);
        }
    }

    if (bandits) {
        // ! to complete
    }
}

void Map::add_province(Province* province)
{ provinces_layer.push_back(province); }

void Map::remove_province(Province* province)
{
    for (auto p = provinces_layer.begin(); p != provinces_layer.end(); p++) {
        if (*p != province) continue;
        (*p)->_tiles().clear();
        delete *p;
        break;
    }
}

void Map::fusion_provinces(Province* p1, Province* p2)
{
    if (p1 == nullptr || p2 == nullptr) return;
    if (p1 == p2) return;
    if (p1->_color() != p2->_color()) return;

    for (auto& t : p2->_tiles()) p1->add_tile(t.second);
    remove_province(p2);
    delete p2;
}

void Map::split_province(Coord c)
{
    Province* p = get_province(c);
    if (p == nullptr) return;
    if (p->_tiles().size() <= 1) return;
    
}


// ===== Game =====

//
bool GameModel::player_action_move_entity(Coord src, Coord dst){

    // ! TODO

    return false;
}

//
bool GameModel::player_action_new_entity(Coord dst, int entity_level, bool entity_type){

    // TODO

    return false;
}

//
bool GameModel::player_action_end_turn(){

    // TODO

    return false;
}

//
int GameModel::get_current_player_color(){

    // TODO

    return 1;
}

//
Province* GameModel::get_tile_province(Coord coord){

    // TODO

    return nullptr;
}

//
Element* GameModel::get_tile_entity(Coord coord){

    // TODO

    return nullptr;
}

//
int GameModel::get_tile_color(Coord coord){

    // TODO

    return -1;
}

//
void GameModel::set_tile_entity(Coord coord, int entity_level, bool entity_type){

    // TODO

}

//
void GameModel::set_tile_color(Coord coord, int color){

    // TODO

}

//
void GameModel::reset_entity_layer(){

    // TODO

}

//
void GameModel::reset_color_layer(){

    // TODO

}


// ===== Tools functions =====

//
usint max(usint a, usint b) { return (a > b) ? a : b; }


//
bool is_adjacent(Coord c1, Coord c2)
{
    int diff_x = c1.x - c2.x;
    int diff_y = c1.y - c2.y;

    // False cases
    if (diff_x == 0 && diff_y == 0) return false; // same tile
    if (abs(diff_x) > 1 || abs(diff_y) > 1) return false; // too far
    if (c1.x%2 == 0 && diff_x == 1 && abs(diff_y) == 1) return false; // diagonal movement not allowed
    else if (c1.x%2 == 1 && diff_x == -1 && abs(diff_y) == 1) return false; // diagonal movement not allowed

    return true;
}


//
vector<Coord> neighbours(Coord c)
{
    int x = c.x;
    int y = c.y;
    vector<Coord> n;
    n.push_back(Coord(x-1, y));
    n.push_back(Coord(x+1, y));
    n.push_back(Coord(x, y-1));
    n.push_back(Coord(x, y+1));
    n.push_back(Coord(x+1, y+1-((x%2)*2)));
    n.push_back(Coord(x-1, y+1-((x%2)*2)));
    return n;
}
