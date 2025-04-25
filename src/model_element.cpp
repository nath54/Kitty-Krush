# include "model_element.hpp"

// >> Getters <<
Coord Element::_coord() const { return this->coord; }
usint Element::_color() const { return this->color; }
usint Element::_defense() const { return this->defense; }

// >> Unit <<
void Unit::upgrade() { if (this->defense < MAX_UNIT_LEVEL) this->defense++; }
void Unit::convert_bandit() { this->color = 0; this->defense = 0; }
int Unit::get_upkeep_cost() { return units_upkeep_costs[this->defense]; }

// >> Building <<
bool Building::is_town() const { return (this->defense == 1); }
void Building::update_treasury(int change) { this->treasury += change; }
void Building::convert_bandit() { this->color = 0; this->defense = 1; }
int Building::get_upkeep_cost() { return buildings_upkeep_costs[this->defense]; }