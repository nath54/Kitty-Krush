#include "model.hpp"

// Elements

usint Element::_color() const { return color; }
usint Element::_defense() const { return defense; }

void Unit::upgrade() { defense++; }
void Unit::convert_bandit() { color = 0; defense = 1; }

// Map

usint Tile::_x() const { return x; }
usint Tile::_y() const { return y; }
Ground Tile::_type() const { return type; }

void Tile::convert_type(Ground new_type) { type = new_type; }

bool Tile::is_adjacent(const Tile* tile) {
    usint diff_x = abs(x - tile->_x());
    usint diff_y = abs(y - tile->_y());
    if ((diff_x <= 1) && (diff_y <= 1) && (diff_x + diff_y > 0)) {
        if (diff_x == 1 && diff_y == 1) {
            if ((tile->_x() < x) && (tile->_y() > y) || (tile->_x() > x) && (tile->_y() < y)) {
                return false;
            }
        return true;
        }
    }
    return false;
}


