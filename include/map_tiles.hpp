#pragma once

#define TILE_IMG_W 72
#define TILE_IMG_H 72

#define TILE_DEC_Y 36
#define TILE_DEC_X 53

#define ENTITY_MARGIN 5


// A structure holding all static information for a tile.
// We use const char* (instead of std::string) to avoid any dynamic allocations.
typedef struct TileData {
    int id;                           // valid values: 0 to 69
    int global_type;                  // -1: impassable; 0: neutral; [1-n]: owned by a player
    const char* tile_name;            // human-readable name
    const int nb_ground_layer_imgs;
    const char* ground_layer_img[5];  // Maximum 5 sprites per tile, unused slots are set to nullptr
    const int nb_top_layer_imgs;
    const char* top_layer_img[5];     // Maximum 5 sprites per tile, unused slots are set to nullptr

    // Maximum 5 tags per tile; unused slots are set to nullptr.
    const char* tags[5];

    // These arrays hold tags with a preceding '+' or '-' as described.
    const char* ground_positive_tags[5];
    const char* ground_negative_tags[5];
} TileData;


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

        // ground_layer_img
        5,
        {"deep_water/deep_water_01.png", "deep_water/deep_water_03.png", "deep_water/deep_water_05.png", "deep_water/deep_water_07.png", "deep_water/deep_water_10.png"},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 01. Shallow Water
    {
        1,                                              // terrain id
        -1,                                             // global terrain type
        "Shallow Water",                                // terrain name

        // ground_layer_img
        1,
        {"shallow_water.png", nullptr, nullptr, nullptr,nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 02. River Water
    {
        2,                                              // terrain id
        -1,                                             // global terrain type
        "River Water",                                  // terrain name

        // ground_layer_img
        1,
        {"river_water.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 03. Swamp Water
    {
        3,                                              // terrain id
        -1,                                             // global terrain type
        "Swamp Water",                                  // terrain name

        // ground_layer_img
        1,
        {"swamp_water.png",nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 04. Reef
    {
        4,                                              // terrain id
        -1,                                             // global terrain type
        "Reef",                                         // terrain name

        // ground_layer_img
        1,
        {"reef.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 05. Oasis
    {
        5,                                              // terrain id
        -1,                                             // global terrain type
        "Oasis",                                        // terrain name

        // ground_layer_img
        1,
        {"oasis.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 06. Frozen Water
    {
        6,                                              // terrain id
        -1,                                             // global terrain type
        "Frozen Water",                                 // terrain name
        1,
        {
            "frozen_water.png",
            nullptr, nullptr, nullptr, nullptr},        // ground_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // top_layer_img
        {"base", "water", "snow", nullptr, nullptr},    // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 07. Water Lilies
    {
        7,                                              // terrain id
        -1,                                             // global terrain type
        "Water Lilies",                                 // terrain name

        // ground_layer_img
        1,
        {"shallow_water.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"water_lilies.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"water", nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 08. Flowering Water Lilies
    {
        8,                                              // terrain id
        -1,                                             // global terrain type
        "Flowering Lilies",                             // terrain name

        // ground_layer_img
        1,
        {"shallow_water.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"flowering_water_lilies.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"water", nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 09. Muddy
    {
        9,                                              // terrain id
        0,                                              // global terrain type
        "Muddy",                                        // terrain name

        // ground_layer_img
        1,
        {"muddy.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 10. Green Grass
    {
        10,                                             // terrain id
        0,                                              // global terrain type
        "Green Grass",                                  // terrain name

        // ground_layer_img
        5,
        {"green_grass/green_grass_01.png", "green_grass/green_grass_02.png", "green_grass/green_grass_03.png", "green_grass/green_grass_04.png", "green_grass/green_grass_05.png"},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "grass", nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 11. Semi-dry Grass
    {
        11,                                             // terrain id
        0,                                              // global terrain type
        "Semi-dry Grass",                               // terrain name

        // ground_layer_img
        1,
        {"semi_dry_grass.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "grass", "dry", nullptr},    // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 12. Dry Grass
    {
        12,                                             // terrain id
        0,                                              // global terrain type
        "Dry Grass",                                    // terrain name

        // ground_layer_img
        1,
        {"dry_grass.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "grass", "dry", nullptr},    // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 13. Dirt
    {
        13,                                             // terrain id
        0,                                              // global terrain type
        "Dirt",                                         // terrain name

        // ground_layer_img
        1,
        {"dirt.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 14. Dry Dirt
    {
        14,                                             // terrain id
        0,                                              // global terrain type
        "Dry Dirt",                                     // terrain name

        // ground_layer_img
        1,
        {"dry_dirt.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "dry", nullptr, nullptr},    // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 15. Cobbles
    {
        15,                                             // terrain id
        0,                                              // global terrain type
        "Cobbles",                                      // terrain name

        // ground_layer_img
        1,
        {"cobbles.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 16. Snow
    {
        16,                                             // terrain id
        0,                                              // global terrain type
        "Snow",                                         // terrain name

        // ground_layer_img
        1,
        {"snow.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "snow", nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 17. Snow Grass
    {
        17,                                             // terrain id
        0,                                              // global terrain type
        "Snow Grass",                                   // terrain name

        // ground_layer_img
        1,
        {"snow_grass.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "grass", "snow", nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 18. Desert Sand
    {
        18,                                             // terrain id
        0,                                              // global terrain type
        "Desert Sand",                                  // terrain name

        // ground_layer_img
        1,
        {"desert_sand.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "sand", nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 19. Beach Sand
    {
        19,                                             // terrain id
        0,                                              // global terrain type
        "Beach Sand",                                   // terrain name

        // ground_layer_img
        1,
        {"beach_sand.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "sand", nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 20. Farmland
    {
        20,                                             // terrain id
        0,                                              // global terrain type
        "Farmland",                                     // terrain name

        // ground_layer_img
        1,
        {"farmlands.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 21. Dirt Path
    {
        21,                                             // terrain id
        0,                                              // global terrain type
        "Dirt Path",                                    // terrain name

        // ground_layer_img
        1,
        {"dirt_path.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "path", nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 22. Rubble
    {
        22,                                             // terrain id
        -1,                                             // global terrain type
        "Rubble",                                       // terrain name

        // ground_layer_img
        1,
        {"dirt.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"rubble.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 23. Mixed flowers
    {
        23,                                             // terrain id
        0,                                              // global terrain type
        "Mixed flowers",                                // terrain name

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"mixed_flowers.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"grass", nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 24. Mixed Frozen flowers
    {
        24,                                             // terrain id
        0,                                              // global terrain type
        "Mixed Frozen flowers",                         // terrain name

        // ground_layer_img
        1,
        {"snow_grass.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"mixed_frozen_flowers.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"grass", "snow", nullptr, nullptr, nullptr},   // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 25. Cherry Flowers
    {
        25,                                             // terrain id
        0,                                              // global terrain type
        "Cherry Flowers",                               // terrain name

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"cherry_flowers.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 26. Small Stones
    {
        26,                                             // terrain id
        0,                                              // global terrain type
        "Small Stones",                                 // terrain name

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"small_stones.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 27. Small Snowy Stones
    {
        27,                                             // terrain id
        0,                                              // global terrain type
        "Small Snowy Stones",                           // terrain name

        // ground_layer_img
        1,
        {"snow.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"small_snowy_stones.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", "snow", nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 28. Small Mushrooms
    {
        28,                                             // terrain id
        0,                                              // global terrain type
        "Small Mushrooms",                              // terrain name

        // ground_layer_img
        1,
        {"dirt.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"small_mushrooms.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 29. Brazier
    {
        29,                                             // terrain id
        -1,                                             // global terrain type
        "Brazier",                                      // terrain name

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"brazier.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 30. Lit Brazier
    {
        30,                                             // terrain id
        -1,                                             // global terrain type
        "Lit Brazier",                                  // terrain name

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"lit_brazier.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 31. Great Tree
    {
        31,                                             // terrain id
        -1,                                             // global terrain type
        "Great Tree",                                   // terrain name

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        3,
        {"great_tree/great_tree_01.png", "great_tree/great_tree_02.png", "great_tree/great_tree_03.png", nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", "grass", nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 32. Dead Great Tree
    {
        32,                                             // terrain id
        -1,                                             // global terrain type
        "Dead Great Tree",                              // terrain name

        // ground_layer_img
        1,
        {"dirt.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"dead_great_tree.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", "grass", nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 33. Snow Great Tree
    {
        33,                                             // terrain id
        -1,                                             // global terrain type
        "Snow Great Tree",                              // terrain name

        // ground_layer_img
        1,
        {"snow_grass.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"snow_great_tree.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", "grass", "snow", nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 34. Tropical Forest
    {
        34,                                             // terrain id
        -1,                                             // global terrain type
        "Tropical Forest",                              // terrain name

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"tropical_forest.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 35. Rainforest
    {
        35,                                             // terrain id
        -1,                                             // global terrain type
        "Rainforest",                                   // terrain name

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"rainforest.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 36. Palm Forest
    {
        36,                                             // terrain id
        -1,                                             // global terrain type
        "Palm Forest",                                  // terrain name

        // ground_layer_img
        1,
        {"beach_sand.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"palm_forest.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", "sand", nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 37. Savanna
    {
        37,                                             // terrain id
        -1,                                             // global terrain type
        "Savanna",                                      // terrain name

        // ground_layer_img
        1,
        {"semi_dry_dirt.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"savanna.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", "dry", nullptr, nullptr, nullptr},   // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 38. Pine Forest
    {
        38,                                             // terrain id
        -1,                                             // global terrain type
        "Pine Forest",                                  // terrain name

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"pine_forest.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 39. Snowy Pine Forest
    {
        39,                                             // terrain id
        -1,                                             // global terrain type
        "Snowy Pine Forest",                            // terrain name

        // ground_layer_img
        1,
        {"snow_grass.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"snowy_pine_forest.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", "snow", nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 40. Summer Deciduous Forest
    {
        40,                                             // terrain id
        -1,                                             // global terrain type
        "Summer Deciduous Forest",                      // terrain name

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        5,
        {"summer_forest/summer_forest_01.png", "summer_forest/summer_forest_02.png", "summer_forest/summer_forest_03.png", "summer_forest/summer_forest_06.png", "summer_forest/summer_forest_08.png"},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 41. Fall Deciduous Forest
    {
        41,                                             // terrain id
        -1,                                             // global terrain type
        "Fall Deciduous Forest",                        // terrain name

        // ground_layer_img
        1,
        {"semi_dry_grass.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"fall_forest.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 42. Cherry Forest
    {
        42,                                             // terrain id
        -1,                                             // global terrain type
        "Cherry Forest",                                // terrain name

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"cherry_forest.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 43. Regular Hills
    {
        43,                                             // terrain id
        0,                                              // global terrain type
        "Regular Hills",                                // terrain name

        // ground_layer_img
        1,
        {"regular_hills.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "hill", nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 44. Dry Hills
    {
        44,                                             // terrain id
        0,                                              // global terrain type
        "Dry Hills",                                    // terrain name

        // ground_layer_img
        1,
        {"dry_hills.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "hill", "dry", nullptr},     // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 45. Dunes
    {
        45,                                             // terrain id
        0,                                              // global terrain type
        "Dunes",                                        // terrain name

        // ground_layer_img
        1,
        {"dunes.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "hill", "sand", nullptr},    // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 46. Snowy Hills
    {
        46,                                             // terrain id
        0,                                              // global terrain type
        "Snowy Hills",                                  // terrain name

        // ground_layer_img
        1,
        {"snowy_hills.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "hill", "snow", nullptr},    // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 47. Regular Mountains
    {
        47,                                                 // terrain id
        -1,                                                 // global terrain type
        "Regular Mountains",                                // terrain name

        // ground_layer_img
        1,
        {"regular_mountains.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "mountain", nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},      // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}       // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 48. Dry Mountains
    {
        48,                                             // terrain id
        -1,                                             // global terrain type
        "Dry Mountains",                                // terrain name

        // ground_layer_img
        1,
        {"dry_mountains.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "mountain", "dry", nullptr}, // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 49. Snow Mountains
    {
        49,                                             // terrain id
        -1,                                             // global terrain type
        "Snow Mountains",                               // terrain name

        // ground_layer_img
        1,
        {"snow_mountains.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "mountain", "snow", nullptr},// tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 50. Desert Mountains
    {
        50,                                             // terrain id
        -1,                                             // global terrain type
        "Desert Mountains",                             // terrain name

        // ground_layer_img
        1,
        {"desert_mountains.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "mountain", "sand", nullptr},// tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 51. Volcano
    {
        51,                                             // terrain id
        -1,                                             // global terrain type
        "Volcano",                                      // terrain name

        // ground_layer_img
        1,
        {"volcano.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "mountain", "lava", nullptr},// tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 52. Basic Stone floor
    {
        52,                                             // terrain id
        0,                                              // global terrain type
        "Basic Stone floor",                            // terrain name

        // ground_layer_img
        1,
        {"basic_stone_floor.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "floor", nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 53. Ancient Stone floor
    {
        53,                                             // terrain id
        0,                                              // global terrain type
        "Ancient Stone floor",                          // terrain name

        // ground_layer_img
        1,
        {"ancient_stone_floor.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "floor", nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 54. Basic Wooden floor
    {
        54,                                             // terrain id
        0,                                              // global terrain type
        "Basic Wooden floor",                           // terrain name

        // ground_layer_img
        1,
        {"basic_wooden_floor.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "floor", nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 55. Old Wooden floor
    {
        55,                                             // terrain id
        0,                                              // global terrain type
        "Old Wooden floor",                             // terrain name

        // ground_layer_img
        1,
        {"old_wooden_floor.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "floor", nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 56. Beam of light
    {
        56,                                             // terrain id
        0,                                              // global terrain type
        "Beam of light",                                // terrain name

        // ground_layer_img
        1,
        {"cave_floor.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"beam_of_light.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 57. Cave floor
    {
        57,                                             // terrain id
        0,                                              // global terrain type
        "Cave Floor",                                   // terrain name

        // ground_layer_img
        1,
        {"cave_floor.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "floor", "cave", nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 58. Earthy Cave Floor
    {
        58,                                             // terrain id
        0,                                              // global terrain type
        "Earthy Cave Floor",                            // terrain name

        // ground_layer_img
        1,
        {"earthy_cave_floor.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "floor", "cave", nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 59. Cave Path
    {
        59,                                             // terrain id
        0,                                              // global terrain type
        "Cave Path",                                    // terrain name

        // ground_layer_img
        1,
        {"cave_path.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "floor", "cave", "path"},    // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 60. Mushroom Grove
    {
        60,                                             // terrain id
        0,                                              // global terrain type
        "Mushroom Grove",                               // terrain name

        // ground_layer_img
        1,
        {"cave_floor.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        1,
        {"mushroom_grove.png", nullptr, nullptr, nullptr, nullptr},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"cave", nullptr, nullptr, nullptr, nullptr},   // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 61. Rockbound Cave
    {
        61,                                             // terrain id
        -1,                                             // global terrain type
        "Rockbound Cave",                               // terrain name

        // ground_layer_img
        1,
        {"rockbound_cave.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "cave", nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 62. Earthy Rockbound Cave
    {
        62,                                             // terrain id
        -1,                                             // global terrain type
        "Earthy Rockbound Cave",                        // terrain name

        // ground_layer_img
        1,
        {"earthy_rockbound_cave.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "ground", "cave", nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 63. Regular Cave Wall
    {
        63,                                             // terrain id
        -1,                                             // global terrain type
        "Regular Cave Wall",                            // terrain name

        // ground_layer_img
        1,
        {"regular_cave_wall.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "cave", "wall", nullptr, nullptr},     // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 64. Earthy Cave Wall
    {
        64,                                             // terrain id
        -1,                                             // global terrain type
        "Earthy Cave Wall",                             // terrain name

        // ground_layer_img
        1,
        {"earthy_cave_wall.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "cave", "wall", nullptr, nullptr},     // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 65. Regular Chasm
    {
        65,                                             // terrain id
        -1,                                             // global terrain type
        "Regular Chasm",                                // terrain name

        // ground_layer_img
        1,
        {"regular_chasm.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "chasm", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 66. Earthy Chasm
    {
        66,                                             // terrain id
        -1,                                             // global terrain type
        "Earthy Chasm",                                 // terrain name

        // ground_layer_img
        1,
        {"earthy_chasm.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "chasm", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 67. Ethereal Chasm
    {
        67,                                             // terrain id
        -1,                                             // global terrain type
        "Ethereal Chasm",                               // terrain name

        // ground_layer_img
        1,
        {"ethereal_chasm.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "chasm", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 68. Lava Chasm
    {
        68,                                             // terrain id
        -1,                                             // global terrain type
        "Lava Chasm",                                   // terrain name

        // ground_layer_img
        1,
        {"lava_chasm.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "chasm", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 69. Lava
    {
        69,                                             // terrain id
        -1,                                             // global terrain type
        "Lava",                                         // terrain name

        // ground_layer_img
        1,
        {"lava.png", nullptr, nullptr, nullptr, nullptr},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},

        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    }
};
