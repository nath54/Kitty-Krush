//
#pragma once


//
static const int MAX_UNIT_LEVEL = 4;
static const int MAX_BUILDING_LEVEL = 4;

//
static const int units_new_costs[] = {
    0,      //
    10,     // level 1 = villager
    20,     // level 2 = pikeman
    40,     // level 3 = knight
    80      // level 4 = hero
};


//
static const int units_upkeep_costs[] = {
    0,      //
    2,      // level 1 = villager
    6,      // level 2 = pikeman
    18,     // level 3 = knight
    54      // level 4 = hero
};


//
static const int buildings_new_costs[] = {
    0,      //
    0,      //
    20,     // level 2 = tower
};


//
static const int buildings_upkeep_costs[] = {
    0,      //
    1,      // level 1 = village
    2       // level 2 = tower
};
