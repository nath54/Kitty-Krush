# include "model_element.hpp"

// >> Getters <<
int Element::_color() const { return this->color; }
int Element::_defense() const { return this->defense; }
bool Element::is_bandit() const { return (this->color == 0); }

// >> Unit <<
void Unit::upgrade() { if (this->defense < MAX_UNIT_LEVEL) this->defense++; }
void Unit::convert_bandit() { this->color = 0; this->defense = 0; }
int Unit::get_upkeep_cost() { return units_upkeep_costs[this->defense]; }

// >> Building <<
bool Building::is_town() const { return (this->defense == 1); }
void Building::update_treasury(int change) { this->treasury += change; }
void Building::convert_bandit() { this->color = 0; this->defense = 1; }
int Building::get_upkeep_cost() { return buildings_upkeep_costs[this->defense]; }