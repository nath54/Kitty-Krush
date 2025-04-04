#pragma once


/*


TILES TERRAIN TYPES:

 -1     : Tile where no player can go
  0     : neutral but player can go
 [1-n]  : tile of the i'th player (like neutral)


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
    (51; -1)        : Volcano                   [base, ground, mountain, lava]

    (52; 0)         : Basic Stone floor         [base, ground, floor]
    (53; 0)         : Ancient Stone floor       [base, ground, floor]
    (54; 0)         : Basic Wooden floor        [base, ground, floor]
    (55; 0)         : Old Wooden floor          [base, ground, floor]

    (56; 0)         : Beam of light             []

    (57; 0)         : Cave Floor                [base, ground, floor, cave]
    (58; 0)         : Earthy Cave Floor         [base, ground, floor, cave]
    (59; 0)         : Cave Path                 [base, ground, floor, cave, path]
    (50; 0)         : Mushroom Grove            [+cave]
    (61; -1)        : Rockbound Cave            [base, ground, cave]
    (62; -1)        : Earthy Rockbound Cave     [base, ground, cave]

    (63; -1)        : Regular Cave Wall         [base, cave, wall]
    (64; -1)        : Earthy Cave Wall          [base, cave, wall]

    (65; -1)        : Regular Chasm             [base, chasm]
    (66; -1)        : Earthy Chasm              [base, chasm]
    (67; -1)        : Ethereal Chasm            [base, chasm]
    (68; -1)        : Lava Chasm                [base, chasm]
    (69; -1)        : Lava                      [base, water]

*/


// A static constant array of TileData.
// Each entry corresponds exactly to the tile definitions in the comment.
// For the tiles where the tag list is given inside square brackets,
// we separate plain tags (e.g. "base", "ground") and the ones with a sign:
//   - For example, "[+water, -snow]" is stored with "water" in ground_positive_tags
//     and "snow" in ground_negative_tags.
static const TileData allTileData[] = {

    // 00. Deep Water Ocean
    {
        0,                                              // terrain id
        -1,                                             // global terrain type
        "Deep Water Ocean",                             // terrain name
        "TODO",                                         // ground_layer_img  ("" == no image)
        "TODO",                                         // top_layer_img  ("" == no image)
        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 01. Shallow Water
    {
        1,                                              // terrain id
        -1,                                             // global terrain type
        "Shallow Water",                                // terrain name
        "TODO",                                         // ground_layer_img  ("" == no image)
        "TODO",                                         // top_layer_img  ("" == no image)
        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 02. River Water
    {
        2,                                              // terrain id
        -1,                                             // global terrain type
        "River Water",                                  // terrain name
        "TODO",                                         // ground_layer_img  ("" == no image)
        "TODO",                                         // top_layer_img  ("" == no image)
        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 03. Swamp Water
    {
        3,                                              // terrain id
        -1,                                             // global terrain type
        "Swamp Water",                                  // terrain name
        "TODO",                                         // ground_layer_img  ("" == no image)
        "TODO",                                         // top_layer_img  ("" == no image)
        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 04. Reef
    {
        4,                                              // terrain id
        -1,                                             // global terrain type
        "Reef",                                         // terrain name
        "TODO",                                         // ground_layer_img  ("" == no image)
        "TODO",                                         // top_layer_img  ("" == no image)
        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 05. Oasis
    {
        5,                                              // terrain id
        -1,                                             // global terrain type
        "Oasis",                                        // terrain name
        "TODO",                                         // ground_layer_img  ("" == no image)
        "TODO",                                         // top_layer_img  ("" == no image)
        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 06. Frozen Water
    {
        6,                                              // terrain id
        -1,                                             // global terrain type
        "Frozen Water",                                 // terrain name
        "TODO",                                         // ground_layer_img  ("" == no image)
        "TODO",                                         // top_layer_img  ("" == no image)
        {"base", "water", "snow", nullptr, nullptr},    // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 07. Water Lilies
    {
        7,                                              // terrain id
        -1,                                             // global terrain type
        "Water Lilies",                                 // terrain name
        "TODO",                                         // ground_layer_img  ("" == no image)
        "TODO",                                         // top_layer_img  ("" == no image)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"water", nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 08. Flowering Water Lilies
    {
        8,                                              // terrain id
        -1,                                             // global terrain type
        "Flowering Lilies",                             // terrain name
        "TODO",                                         // ground_layer_img  ("" == no image)
        "TODO",                                         // top_layer_img  ("" == no image)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"water", nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 09. Muddy
    {
        9,                                              // terrain id
        0,                                              // global terrain type
        "Muddy",                                        // terrain name
        "TODO",                                         // ground_layer_img  ("" == no image)
        "TODO",                                         // top_layer_img  ("" == no image)
        {"base", "ground", nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 10. Green Grass
    {
        10,                                             // terrain id
        0,                                              // global terrain type
        "Green Grass",                                  // terrain name
        "TODO",                                         // ground_layer_img  ("" == no image)
        "TODO",                                         // top_layer_img  ("" == no image)
        {"base", "ground", "grass", nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 11. Semi-dry Grass
    {
        11,                                             // terrain id
        0,                                              // global terrain type
        "Semi-dry Grass",                               // terrain name
        "TODO",                                         // ground_layer_img  ("" == no image)
        "TODO",                                         // top_layer_img  ("" == no image)
        {"base", "ground", "grass", "dry", nullptr},    // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 12. Dry Grass
    {
        12,
        0,
        "Dry Grass",
        "TODO",
        "TODO",
        {"base", "ground", "grass", "dry", nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 13. Dirt
    {
        13,
        0,
        "Dirt",
        "TODO",
        "TODO",
        {"base", "ground", nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 14. Dry Dirt
    {
        14,
        0,
        "Dry Dirt",
        "TODO",
        "TODO",
        {"base", "ground", "dry", nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 15. Cobbles
    {
        15,
        0,
        "Cobbles",
        "TODO",
        "TODO",
        {"base", "ground", nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 16. Snow
    {
        16,
        0,
        "Snow",
        "TODO",
        "TODO",
        {"base", "ground", "snow", nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 17. Snow Grass
    {
        17,
        0,
        "Snow Grass",
        "TODO",
        "TODO",
        {"base", "ground", "grass", "snow", nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 18. Desert Sand
    {
        18,
        0,
        "Desert Sand",
        "TODO",
        "TODO",
        {"base", "ground", "sand", nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 19. Beach Sand
    {
        19,
        0,
        "Beach Sand",
        "TODO",
        "TODO",
        {"base", "ground", "sand", nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 20. Farmland
    {
        20,
        0,
        "Farmland",
        "TODO",
        "TODO",
        {"base", "ground", nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 21. Dirt Path
    {
        21,
        0,
        "Dirt Path",
        "TODO",
        "TODO",
        {"base", "ground", "path", nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 22. Rubble
    {
        22,
        -1,
        "Rubble",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"ground", nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 23. Mixed flowers
    {
        23,
        0,
        "Mixed flowers",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"grass", nullptr, nullptr, nullptr, nullptr},
        {"snow", nullptr, nullptr, nullptr, nullptr}
    },

    // 24. Mixed Frozen flowers
    {
        24,
        0,
        "Mixed Frozen flowers",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"grass", "snow", nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 25. Cherry Flowers
    {
        25,
        0,
        "Cherry Flowers",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"ground", nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 26. Small Stones
    {
        26,
        0,
        "Small Stones",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"ground", nullptr, nullptr, nullptr, nullptr},
        {"snow", nullptr, nullptr, nullptr, nullptr}
    },

    // 27. Small Snowy Stones
    {
        27,
        0,
        "Small Snowy Stones",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"ground", "snow", nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 28. Small Mushrooms
    {
        28,
        0,
        "Small Mushrooms",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"ground", nullptr, nullptr, nullptr, nullptr},
        {"snow", nullptr, nullptr, nullptr, nullptr}
    },

    // 29. Brazier
    {
        29,
        -1,
        "Brazier",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"ground", nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 30. Lit Brazier
    {
        30,
        -1,
        "Lit Brazier",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"ground", nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 31. Great Tree
    {
        31,
        -1,
        "Great Tree",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"ground", "grass", nullptr, nullptr, nullptr},
        {"snow", nullptr, nullptr, nullptr, nullptr}
    },

    // 32. Dead Great Tree
    {
        32,
        -1,
        "Dead Great Tree",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"ground", "grass", nullptr, nullptr, nullptr},
        {"snow", nullptr, nullptr, nullptr, nullptr}
    },

    // 33. Snow Great Tree
    {
        33,
        -1,
        "Snow Great Tree",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"ground", "grass", "snow", nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 34. Tropical Forest
    {
        34,
        -1,
        "Tropical Forest",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"ground", nullptr, nullptr, nullptr, nullptr},
        {"snow", nullptr, nullptr, nullptr, nullptr}
    },

    // 35. Rainforest
    {
        35,
        -1,
        "Rainforest",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"ground", nullptr, nullptr, nullptr, nullptr},
        {"snow", nullptr, nullptr, nullptr, nullptr}
    },

    // 36. Palm Forest
    {
        36,
        -1,
        "Palm Forest",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"ground", "sand", nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 37. Savanna
    {
        37,
        -1,
        "Savanna",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"ground", "dry", nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 38. Pine Forest
    {
        38,
        -1,
        "Pine Forest",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"ground", nullptr, nullptr, nullptr, nullptr},
        {"snow", nullptr, nullptr, nullptr, nullptr}
    },

    // 39. Snowy Pine Forest
    {
        39,
        -1,
        "Snowy Pine Forest",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"ground", "snow", nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 40. Summer Deciduous Forest
    {
        40,
        -1,
        "Summer Deciduous Forest",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"ground", nullptr, nullptr, nullptr, nullptr},
        {"snow", nullptr, nullptr, nullptr, nullptr}
    },

    // 41. Fall Deciduous Forest
    {
        41,
        -1,
        "Fall Deciduous Forest",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"ground", nullptr, nullptr, nullptr, nullptr},
        {"snow", nullptr, nullptr, nullptr, nullptr}
    },

    // 42. Cherry Forest
    {
        42,
        -1,
        "Cherry Forest",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"ground", nullptr, nullptr, nullptr, nullptr},
        {"snow", nullptr, nullptr, nullptr, nullptr}
    },

    // 43. Regular Hills
    {
        43,
        0,
        "Regular Hills",
        "TODO",
        "TODO",
        {"base", "ground", "hill", nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 44. Dry Hills
    {
        44,
        0,
        "Dry Hills",
        "TODO",
        "TODO",
        {"base", "ground", "hill", "dry", nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 45. Dunes
    {
        45,
        0,
        "Dunes",
        "TODO",
        "TODO",
        {"base", "ground", "hill", "sand", nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 46. Snowy Hills
    {
        46,
        0,
        "Snowy Hills",
        "TODO",
        "TODO",
        {"base", "ground", "hill", "snow", nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 47. Regular Mountains
    {
        47,
        -1,
        "Regular Mountains",
        "TODO",
        "TODO",
        {"base", "ground", "mountain", nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 48. Dry Mountains
    {
        48,
        -1,
        "Dry Mountains",
        "TODO",
        "TODO",
        {"base", "ground", "mountain", "dry", nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 49. Snow Mountains
    {
        49,
        -1,
        "Snow Mountains",
        "TODO",
        "TODO",
        {"base", "ground", "mountain", "snow", nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 50. Desert Mountains
    {
        50,
        -1,
        "Desert Mountains",
        "TODO",
        "TODO",
        {"base", "ground", "mountain", "sand", nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 51. Volcano
    {
        51,
        -1,
        "Volcano",
        "TODO",
        "TODO",
        {"base", "ground", "mountain", "lava", nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 52. Basic Stone floor
    {
        52,
        0,
        "Basic Stone floor",
        "TODO",
        "TODO",
        {"base", "ground", "floor", nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 53. Ancient Stone floor
    {
        53,
        0,
        "Ancient Stone floor",
        "TODO",
        "TODO",
        {"base", "ground", "floor", nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 54. Basic Wooden floor
    {
        54,
        0,
        "Basic Wooden floor",
        "TODO",
        "TODO",
        {"base", "ground", "floor", nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 55. Old Wooden floor
    {
        55,
        0,
        "Old Wooden floor",
        "TODO",
        "TODO",
        {"base", "ground", "floor", nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 56. Beam of light
    {
        56,
        0,
        "Beam of light",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 57. Cave floor
    {
        57,
        0,
        "Cave Floor",
        "TODO",
        "TODO",
        {"base", "ground", "floor", "cave", nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 58. Earthy Cave Floor
    {
        58,
        0,
        "Earthy Cave Floor",
        "TODO",
        "TODO",
        {"base", "ground", "floor", "cave", nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 59. Cave Path
    {
        59,
        0,
        "Cave Path",
        "TODO",
        "TODO",
        {"base", "ground", "floor", "cave", "path"},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 60. Mushroom Grove
    {
        60,
        0,
        "Mushroom Grove",
        "TODO",
        "TODO",
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {"cave", nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 61. Rockbound Cave
    {
        61,
        -1,
        "Rockbound Cave",
        "TODO",
        "TODO",
        {"base", "ground", "cave", nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 62. Earthy Rockbound Cave
    {
        62,
        -1,
        "Earthy Rockbound Cave",
        "TODO",
        "TODO",
        {"base", "ground", "cave", nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 63. Regular Cave Wall
    {
        63,
        -1,
        "Regular Cave Wall",
        "TODO",
        "TODO",
        {"base", "cave", "wall", nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 64. Earthy Cave Wall
    {
        64,
        -1,
        "Earthy Cave Wall",
        "TODO",
        "TODO",
        {"base", "cave", "wall", nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 65. Regular Chasm
    {
        65,
        -1,
        "Regular Chasm",
        "TODO",
        "TODO",
        {"base", "chasm", nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 66. Earthy Chasm
    {
        66,
        -1,
        "Earthy Chasm",
        "TODO",
        "TODO",
        {"base", "chasm", nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 67. Ethereal Chasm
    {
        67,
        -1,
        "Ethereal Chasm",
        "TODO",
        "TODO",
        {"base", "chasm", nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 68. Lava Chasm
    {
        68,
        -1,
        "Lava Chasm",
        "TODO",
        "TODO",
        {"base", "chasm", nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    },

    // 69. Lava
    {
        69,
        -1,
        "Lava",
        "TODO",
        "TODO",
        {"base", "water", nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr}
    }
};
