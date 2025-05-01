#pragma once

#include <memory>

#include "geometry.hpp"


// =============================== [ Pointers ] ===============================


#define ELEMENT_T std::shared_ptr<Element>
#define UNIT_T std::shared_ptr<Unit>
#define BUILDING_T std::shared_ptr<Building>

#define CREATE_ELEMENT_T(...) std::make_shared<Element>(__VA_ARGS__)
#define CREATE_UNIT_T(...) std::make_shared<Unit>(__VA_ARGS__)
#define CREATE_BUILDING_T(...) std::make_shared<Building>(__VA_ARGS__)

#define DCAST_UNIT_T(...) std::dynamic_pointer_cast<Unit>(__VA_ARGS__)
#define DCAST_BUILDING_T(...) std::dynamic_pointer_cast<Building>(__VA_ARGS__)


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
        int defense;  // level (= defense) of the element

    public:

        // Constructor
        Element () {}; // Default constructor
        Element(int element_color, int element_defense = 0)
            : color(element_color), defense(element_defense) {};
        // Destructor
        virtual ~Element() {}; // Virtual destructor

        // Getters
        int _color() const;
        int _defense() const;

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
        Unit(int unit_color, int unit_defense = 1)
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
        Building(int building_color, int building_defense = 1)
                : Element(building_color, building_defense) {}
        // Destructor
        ~Building() {}; // Default destructor

        // Other Functions
        bool is_town() const; // Return true if town, false if tower
        void update_treasury(int change);
        int get_upkeep_cost() override;
        void convert_bandit() override;
};
