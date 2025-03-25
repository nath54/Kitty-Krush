#pragma once


/*


TILES TERRAIN TYPES:

 -1     : Tile where no player can go
  0     : neutral but player can go
 [1-n]  : tile of the i'th player


TILES GRAPHICAL :

    (0; -1)         : Deep Water Ocean          [base, water]
    (1; -1)         : Shallow Water             [base, water]
    (2; -1)         : River Water               [base, water]
    (3; -1)         : Swamp Water               [base, water]
    (4; -1)         : Reef                      [base, water]
    (5; -1)         : Oasis                     [base, water]
    (6; -1)         : Frozen Water              [base, water, snow]

    (7; -1)         : Water Lilies              [+water, -snow]
    (8; -1)         : Flowering Water Lilies    [+water, -snow]

    (9; 0)          : Muddy                     [base, ground]
    (10; 0)         : Green Grass               [base, ground, grass]
    (11; 0)         : Semi-dry Grass            [base, ground, grass, dry]
    (12; 0)         : Dry Grass                 [base, ground, grass, dry]
    (13; 0)         : Dirt                      [base, ground]
    (14; 0)         : Dry Dirt                  [base, ground, dry]
    (15; 0)         : Cobbles                   [base, ground]
    (16; 0)         : Snow                      [base, ground, snow]
    (17; 0)         : Snow Grass                [base, ground, grass, snow]
    (18; 0)         : Desert Sand               [base, ground, sand]
    (19; 0)         : Beach Sand                [base, ground, sand]
    (20; 0)         : Farmland                  [base, ground]
    (21; 0)         : Dirt Path                 [base, ground, path]

    (22; -1)        : Rubble                    [+ground]
    (23; 0)         : Mixed flowers             [+grass, -snow]
    (24; 0)         : Mixed Frozen flowers      [+grass, +snow]
    (25; 0)         : Cherry Flowers            [+ground]
    (26; 0)         : Small Stones              [+ground, -snow]
    (27; 0)         : Small Snowy Stones        [+ground, +snow]
    (28; 0)         : Small Mushrooms           [+ground, -snow]

    (29; -1)        : Brazier                   [+ground]
    (30; -1)        : Lit Brazier               [+ground]

    (31; -1)        : Great Tree                [+ground, +grass, -snow]
    (32; -1)        : Dead Great Tree           [+ground, +grass, -snow]
    (33; -1)        : Snow Great Tree           [+ground, +grass, +snow]

    (34; -1)        : Tropical Forest           [+ground, -snow]
    (35; -1)        : Rainforest                [+ground, -snow]
    (36; -1)        : Palm Forest               [+ground, +sand]
    (37; -1)        : Savanna                   [+ground, +dry]
    (38; -1)        : Pine Forest               [+ground, -snow]
    (39; -1)        : Snowy Pine Forest         [+ground, +snow]
    (40; -1)        : Summer Deciduous Forest   [+ground, -snow]
    (41; -1)        : Fall Deciduous Forest     [+ground, -snow]
    (42; -1)        : Cherry Forest             [+ground, -snow]

    (43; 0)         : Regular Hills             [base, ground, hill]
    (44; 0)         : Dry Hills                 [base, ground, hill, dry]
    (45; 0)         : Dunes                     [base, ground, hill, sand]
    (46; 0)         : Snowy Hills               [base, ground, hill, snow]

    (47; -1)        : Regular Mountains         [base, ground, mountain]
    (48; -1)        : Dry Mountains             [base, ground, mountain, dry]
    (49; -1)        : Snow Mountains            [base, ground, mountain, snow]
    (50; -1)        : Desert Mountains          [base, ground, mountain, sand]

    (51; 0)         : Basic Stone floor         [base, ground, floor]
    (52; 0)         : Ancient Stone floor       [base, ground, floor]
    (53; 0)         : Basic Wooden floor        [base, ground, floor]
    (54; 0)         : Old Wooden floor          [base, ground, floor]

    (55; 0)         : Beam of light             []

    (56; 0)         : Cave Floor                [base, ground, floor, cave]
    (57; 0)         : Earthy Cave Floor         [base, ground, floor, cave]
    (58; 0)         : Cave Path                 [base, ground, floor, cave, path]
    (59; 0)         : Mushroom Grove            [+cave]
    (60; -1)        : Rockbound Cave            [base, ground, cave]
    (61; -1)        : Earthy Rockbound Cave     [base, ground, cave]

    (62; -1)        : Regular Cave Wall         [base, cave, wall]
    (63; -1)        : Earthy Cave Wall          [base, cave, wall]

    (64; -1)        : Regular Chasm             [base, chasm]
    (65; -1)        : Earthy Chasm              [base, chasm]
    (66; -1)        : Ethereal Chasm            [base, chasm]
    (67; -1)        : Lava Chasm                [base, chasm]
    (68; -1)        : Lava                      [base, water]

*/








