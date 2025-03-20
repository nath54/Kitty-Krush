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


// ===== [ Map ] =====

// --- Tile ---

usint Tile::_x() const { return x; }
usint Tile::_y() const { return y; }
short Tile::_type() const { return type; }
usint Tile::_defense() const { return defense; }
Element* Tile::_element() const { return element; }

void Tile::convert_type(short new_type)
{ type = new_type; }

bool Tile::is_adjacent(const Tile* tile)
{
    short diff_x = x - tile->_x();
    short diff_y = y - tile->_y();

    if (diff_x == -diff_y) return false; // wrong diagonal
    if (abs(diff_x) > 1 || abs(diff_y) > 1) return false; // too far
    return true;
}

bool Tile::adjacent_to_province(Province* p)
{
    for (const Tile* t : p->_tiles()) {
        if (is_adjacent(t))
            return true;
    }
    return false;
}

// --- Province ---

short Province::_color() const { return color; }
int Province::_treasury() const { return treasury; }
vector<Tile*> Province::_tiles() const { return tiles_layer; }


void Province::add_tile(Tile* tile)
{ tiles_layer.push_back(tile); }

void Province::remove_tile(Tile* tile)
{
    for (auto t = tiles_layer.begin(); t != tiles_layer.end(); t++) {
        if (*t == tile) {
            tiles_layer.erase(t);
            break;
        }
    }
}


void Province::treasury_positive()
{ for (Tile* t : tiles_layer) treasury++; }

void Province::treasury_negative()
{
    for (Tile* t : tiles_layer) {
        if (t->_element() == nullptr) continue;
        treasury -= t->_element()->_cost();
    }
    if (treasury >= 0) return; // unities are paid
    treasury = 0;
    Unit* u = nullptr;
    for (Tile* t : tiles_layer) {
        u = dynamic_cast<Unit*>(t->_element());
        if (u != nullptr) u->convert_bandit();
    }
}

void Province::add_treasury(int amount)
{ treasury += amount; }

void Province::remove_treasury(int amount)
{ treasury -= amount; }

// --- Map ---

usint Map::_size() const { return size; }

void Map::init_map(int nb_players, int nb_provinces, bool bandits)
{
    srand(static_cast<unsigned int>(time(0)));

    usint seed = rand() % size*size;

    for (int p=1; p<=nb_players; p++) {

        while (tiles_layer[seed]->_type() != NEUTRAL)
            seed = rand() % size*size;

        tiles_layer[seed]->convert_type(p);
        // Province* province = new Province(p);
        // province->add_tile(tiles_layer[seed]);
        // add_province(province);
        // ! TODO : continuer
    }
}

Tile* Map::get_tile(usint x, usint y)
{ return (x < size && y < size) ? tiles_layer[y*size+x] : nullptr; }

Province* Map::get_province(usint x, usint y)
{
    for (Province* p : provinces_layer) {
        for (Tile* t : p->_tiles()) {
            if (t->_x() == x && t->_y() == y)
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
        if (*p == province) {
            // ! appeler une Province::méthode qui vide la province pour qu'elle soit prete a la suppression
            provinces_layer.erase(p);
            break;
        }
    }
}


// ===== Game =====

//


// ===== Tools functions =====

usint max(usint a, usint b) { return (a > b) ? a : b; }