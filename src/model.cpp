#include "model.hpp"
#include <cstdlib>  // srand() et rand()
#include <ctime> // time()


// ===== Players =====

string Player::_name() const { return name; }
short Player::_color() const { return color; }


// ===== Elements =====

usint Element::_x() const { return x; }
usint Element::_y() const { return y; }
short Element::_color() const { return color; }
usint Element::_defense() const { return defense; }
usint Element::_cost() const { return cost; }

void Unit::upgrade()
{ defense++; cost *= 3; }

void Unit::convert_bandit()
{ color = -1; defense = 0; cost = 0; }

bool Building::is_town() const { return (defense == 1); }


// ===== [ Map ] =====

// --- Tile ---

int Tile::_x() const { return x; }
int Tile::_y() const { return y; }
usint Tile::_type() const { return type; }
usint Tile::_defense() const { return defense; }
Element* Tile::_element() const { return element; }

void Tile::convert_type(usint new_type)
{ type = new_type; }

bool Tile::adjacent_to_province(Province* p)
{
    for (const auto& t : p->_tiles()) {
        if (is_adjacent(x, y, t.first.x, t.first.y))
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

short Province::_color() const { return color; }
int Province::_treasury() const { return treasury; }
map<Coord, Tile*> Province::_tiles() const { return tiles_layer; }


void Province::add_tile(Tile* tile)
{ 
    tile->convert_type(color);
    tiles_layer.insert({{tile->_x(), tile->_y()}, tile});
}

void Province::remove_tile(Tile* tile)
{
    for (auto t = tiles_layer.begin(); t != tiles_layer.end(); t++) {
        if (t->first.x == tile->_x() && t->first.y == tile->_y()) {
            tiles_layer.erase(t);
            break;
        }
    }
}

void Province::treasury_turn()
{
    // Income
    treasury += tiles_layer.size();
    // ! Ne pas gagner les tuiles avec des bandits dessus
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

// --- Map ---

usint Map::_size() const { return size; }

void Map::recursive_fill(Coord c, unsigned int nb_cover, usint cover, Province* province=nullptr)
{
    if (cover == NEUTRAL) {
        if (tiles_layer.size() >= nb_cover) return; // inhaf NEUTRAL
        if (tiles_layer.find(c) != tiles_layer.end()) return; // already exists
        tiles_layer.insert({c, new Tile(c.x, c.y, cover)});
    }

    else {
        Tile* tile = get_tile(c.x, c.y);
        if (tile == nullptr) return;
        if (tile->_type() != NEUTRAL) return;

        if (province == nullptr) {
            province = new Province(cover);
            province->add_treasury(7);
            add_province(province);
            tile->add_element(new Building(c.x, c.y, cover));
        }
        province->add_tile(tile);
    }

    for (auto c : neighbours(c.x, c.y))
        if (rand() % 2) recursive_fill(c, nb_cover, cover, province);
}

// ! Gérer le bool bandit
void Map::init_map(short nb_players, int nb_provinces, int size_provinces, bool bandits)
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
                    || tiles_layer[Coord(seed_x, seed_y)]->_type() != NEUTRAL)
                { seed_x = rand() % size; seed_y = rand() % size; }

            recursive_fill(Coord(seed_x, seed_y), size_provinces, p, nullptr);
        }
    }

    if (bandits) {
        // ! to complete
    }
}

Tile* Map::get_tile(int x, int y)
{ return (tiles_layer.find(Coord(x, y)) != tiles_layer.end()) ? tiles_layer[Coord(x, y)] : nullptr; }

Province* Map::get_province(usint x, usint y)
{
    for (Province* p : provinces_layer) {
        for (auto& t : p->_tiles()) {
            if (t.first.x == x && t.first.y == y)
                return p;
        }
    }
    return nullptr;
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


// ===== Game =====

//


// ===== Tools functions =====

usint max(usint a, usint b) { return (a > b) ? a : b; }

bool is_adjacent(int x1, int y1, int x2, int y2)
{
    int diff_x = x1 - x2;
    int diff_y = y1 - y2;

    // False cases
    if (diff_x == 0 && diff_y == 0) return false; // same tile
    if (abs(diff_x) > 1 || abs(diff_y) > 1) return false; // too far
    if (x1%2 == 0 && diff_x == 1 && abs(diff_y) == 1) return false; // diagonal movement not allowed
    else if (x1%2 == 1 && diff_x == -1 && abs(diff_y) == 1) return false; // diagonal movement not allowed
    return true;
}

vector<Coord> neighbours(int x, int y)
{
    vector<Coord> n;
    n.push_back(Coord(x-1, y));
    n.push_back(Coord(x+1, y));
    n.push_back(Coord(x, y-1));
    n.push_back(Coord(x, y+1));
    n.push_back(Coord(x+1, y+1-((x%2)*2)));
    n.push_back(Coord(x-1, y+1-((x%2)*2)));
    return n;
}