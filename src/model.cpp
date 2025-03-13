#include "model.hpp"

// === Players ===

string Player::_name() const { return name; }
short Player::_color() const { return color; }

// === Elements ===

usint Element::_x() const { return x; }
usint Element::_y() const { return y; }
short Element::_color() const { return color; }
usint Element::_defense() const { return defense; }
usint Element::_cost() const { return cost; }

void Unit::upgrade()
{ defense++; cost *= 3; }

void Unit::convert_bandit()
{ color = -1; defense = 0; cost = 0; }

// === Map ===

usint Tile::_x() const { return x; }
usint Tile::_y() const { return y; }
short Tile::_type() const { return type; }
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

usint Map::_size() const { return size; }

Tile* Map::get_tile(usint x, usint y)
{ return (x < size && y < size) ? tiles_layer[y*size+x] : nullptr; }

bool Map::adjacent_to_player(Tile *t, Player *p)
{
    for (usint x = max(t->_x(), 1) - 1; x <= t->_x()+1; x++) {
        for (usint y = max(t->_y(),1) - 1; y <= t->_y()+1; y++) {

            Tile* adj = get_tile(x, y);

            if (adj != nullptr && t->is_adjacent(adj) && adj->_type() == p->_color())
                return true;
        }
    }

    return false;
}

// === Game ===

//

// === Tools functions ===

usint max(usint a, usint b) { return (a > b) ? a : b; }