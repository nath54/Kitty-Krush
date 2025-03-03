#include "model.hpp"

// Class Unit

usint Unit::_color() const { return color; }
usint Unit::_defense() const { return defense; }

void Unit::upgrade() { defense++; }
void Unit::convert_bandit() { color = 0; defense = 1; }

// Class Building

usint Building::_color() const { return color; }
usint Building::_defense() const { return defense; }
