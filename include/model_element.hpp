#pragma once

#include "geometry.hpp"

typedef unsigned short int usint;

// ============================== [ Constants ] ===============================

static const int MAX_UNIT_LEVEL = 4;
static const int MAX_BUILDING_LEVEL = 2;

static const int units_new_costs[] = {
    0,      //
    10,     // level 1 = villager
    20,     // level 2 = pikeman
    40,     // level 3 = knight
    80      // level 4 = hero
};

static const int units_upkeep_costs[] = {
    0,      //
    2,      // level 1 = villager
    6,      // level 2 = pikeman
    18,     // level 3 = knight
    54      // level 4 = hero
};

static const int buildings_new_costs[] = {
    0,      //
    0,      //
    20,     // level 2 = tower
};

static const int buildings_upkeep_costs[] = {
    0,      //
    0,      // level 1 = village
    2       // level 2 = tower
};

// =============================== [ Classes ] ================================

class Element {

    protected:

        int color;    // owner of the element
        usint defense;  // level (= defense) of the element

    public:

        // Constructor
        Element () {}; // Default constructor
        Element(usint element_color, usint element_defense = 0)
            : color(element_color), defense(element_defense) {};
        // Destructor
        virtual ~Element() {}; // Virtual destructor

        // Getters
        usint _color() const;
        usint _defense() const;

        // Other functions
        bool is_bandit() const; // Return true if bandit, false otherwise
        virtual int get_upkeep_cost() = 0; // Return the upkeep cost of the element
        virtual void convert_bandit() = 0; // Change the element into a bandit element
};


class Unit : public Element {

    public:

        // Additional Attribute
        bool can_move = true;

        // Constructor
        Unit(usint unit_color, usint unit_defense = 1)
            : Element(unit_color, unit_defense) {};
        // Destructor
        ~Unit() {}; // Default destructor

        // Other Functions
        void upgrade(); // Increase unit level
        int get_upkeep_cost() override;
        void convert_bandit() override;
};


class Building : public Element {

    public:

        // Additional Attribute
        int treasury = 0;

        // Constructor
        Building(usint building_color, usint building_defense = 1)
                : Element(building_color, building_defense) {}
        // Destructor
        ~Building() {}; // Default destructor

        // Other Functions
        bool is_town() const; // Return true if town, false if tower
        void update_treasury(int change);
        int get_upkeep_cost() override;
        void convert_bandit() override;
};
