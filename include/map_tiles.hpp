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

    const char* img_preview;

    const int nb_ground_layer_imgs;
    const char* ground_layer_img[5];  // Maximum 5 sprites per tile, unused slots are set to nullptr

    const int nb_frames_ground_layer_img[5];

    const int nb_top_layer_imgs;
    const char* top_layer_img[5];     // Maximum 5 sprites per tile, unused slots are set to nullptr

    const int nb_frames_top_layer_img[5];

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

        "deep_water/deep_water_01.png",

        // ground_layer_img
        1,
        {"deep_water/deep_water.png", nullptr, nullptr, nullptr, nullptr},
        {15, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 01. Shallow Water
    {
        1,                                              // terrain id
        -1,                                             // global terrain type
        "Shallow Water",                                // terrain name

        "shallow_water.png",

        // ground_layer_img
        1,
        {"shallow_water.png", nullptr, nullptr, nullptr,nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 02. River Water
    {
        2,                                              // terrain id
        -1,                                             // global terrain type
        "River Water",                                  // terrain name

        "river_water.png",

        // ground_layer_img
        1,
        {"river_water.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 03. Swamp Water
    {
        3,                                              // terrain id
        -1,                                             // global terrain type
        "Swamp Water",                                  // terrain name

        "swamp_water.png",

        // ground_layer_img
        5,
        {"swamp/reed1.png","swamp/reed2.png", "swamp/reed3.png", "swamp/reed4.png", "swamp/reed5.png"},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 04. Reef
    {
        4,                                              // terrain id
        -1,                                             // global terrain type
        "Reef",                                         // terrain name

        "reef.png",

        // ground_layer_img
        1,
        {"reef.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 05. Oasis
    {
        5,                                              // terrain id
        -1,                                             // global terrain type
        "Oasis",                                        // terrain name

        "oasis.png",

        // ground_layer_img
        1,
        {"oasis.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 06. Frozen Water
    {
        6,                                              // terrain id
        -1,                                             // global terrain type
        "Frozen Water",                                 // terrain name

        "frozen_water.png",

        // ground_layer_img
        1,
        {"frozen_water.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "water", "snow", nullptr, nullptr},    // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 07. Water Lilies
    {
        7,                                              // terrain id
        -1,                                             // global terrain type
        "Water Lilies",                                 // terrain name

        "water_lilies.png",

        // ground_layer_img
        1,
        {"shallow_water.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"water_lilies.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"water", nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 08. Flowering Water Lilies
    {
        8,                                              // terrain id
        -1,                                             // global terrain type
        "Flowering Lilies",                             // terrain name

        "flowering_water_lilies.png",

        // ground_layer_img
        1,
        {"shallow_water.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"flowering_water_lilies.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"water", nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 09. Muddy
    {
        9,                                              // terrain id
        0,                                              // global terrain type
        "Muddy",                                        // terrain name

        "muddy.png",

        // ground_layer_img
        3,
        {"swamp/mud1.png", "swamp/mud2.png", "swamp/mud3.png", nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 10. Green Grass
    {
        10,                                             // terrain id
        0,                                              // global terrain type
        "Green Grass",                                  // terrain name

        "green_grass/green_grass_01.png",

        // ground_layer_img
        5,
        {"green_grass/green_grass_01.png", "green_grass/green_grass_02.png", "green_grass/green_grass_03.png", "green_grass/green_grass_04.png", "green_grass/green_grass_05.png"},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "grass", nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 11. Semi-dry Grass
    {
        11,                                             // terrain id
        0,                                              // global terrain type
        "Semi-dry Grass",                               // terrain name

        "semi_dry_grass.png",

        // ground_layer_img
        1,
        {"semi_dry_grass.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "grass", "dry", nullptr},    // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 12. Dry Grass
    {
        12,                                             // terrain id
        0,                                              // global terrain type
        "Dry Grass",                                    // terrain name

        "dry_grass.png",

        // ground_layer_img
        1,
        {"dry_grass.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "grass", "dry", nullptr},    // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 13. Dirt
    {
        13,                                             // terrain id
        0,                                              // global terrain type
        "Dirt",                                         // terrain name

        "dirt.png",

        // ground_layer_img
        1,
        {"dirt.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 14. Dry Dirt
    {
        14,                                             // terrain id
        0,                                              // global terrain type
        "Dry Dirt",                                     // terrain name

        "dry_dirt.png",

        // ground_layer_img
        1,
        {"dry_dirt.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "dry", nullptr, nullptr},    // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 15. Cobbles
    {
        15,                                             // terrain id
        0,                                              // global terrain type
        "Cobbles",                                      // terrain name

        "cobbles.png",

        // ground_layer_img
        1,
        {"cobbles.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 16. Snow
    {
        16,                                             // terrain id
        0,                                              // global terrain type
        "Snow",                                         // terrain name

        "snow.png",

        // ground_layer_img
        1,
        {"snow.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "snow", nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 17. Snow Grass
    {
        17,                                             // terrain id
        0,                                              // global terrain type
        "Snow Grass",                                   // terrain name

        "snow_grass.png",

        // ground_layer_img
        1,
        {"snow_grass.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "grass", "snow", nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 18. Desert Sand
    {
        18,                                             // terrain id
        0,                                              // global terrain type
        "Desert Sand",                                  // terrain name

        "desert_sand.png",

        // ground_layer_img
        5,
        {"sand/desert1.png", "sand/desert2.png", "sand/desert3.png", "sand/desert4.png", "sand/desert5.png"},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "sand", nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 19. Beach Sand
    {
        19,                                             // terrain id
        0,                                              // global terrain type
        "Beach Sand",                                   // terrain name

        "beach_sand.png",

        // ground_layer_img
        5,
        {"sand/beach1.png", "sand/beach2.png", "sand/beach3.png", "sand/beach4.png", "sand/beach5.png"},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "sand", nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 20. Farmland
    {
        20,                                             // terrain id
        0,                                              // global terrain type
        "Farmland",                                     // terrain name

        "farmlands.png",

        // ground_layer_img
        1,
        {"farmlands.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 21. Dirt Path
    {
        21,                                             // terrain id
        0,                                              // global terrain type
        "Dirt Path",                                    // terrain name

        "dirt_path.png",

        // ground_layer_img
        1,
        {"dirt_path.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "path", nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 22. Rubble
    {
        22,                                             // terrain id
        -1,                                             // global terrain type
        "Rubble",                                       // terrain name

        "rubble.png",

        // ground_layer_img
        1,
        {"dirt.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"rubble.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 23. Mixed flowers
    {
        23,                                             // terrain id
        0,                                              // global terrain type
        "Mixed flowers",                                // terrain name

        "mixed_flowers.png",

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"mixed_flowers.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"grass", nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 24. Mixed Frozen flowers
    {
        24,                                             // terrain id
        0,                                              // global terrain type
        "Mixed Frozen flowers",                         // terrain name

        "mixed_frozen_flowers.png",

        // ground_layer_img
        1,
        {"snow_grass.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"mixed_frozen_flowers.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"grass", "snow", nullptr, nullptr, nullptr},   // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 25. Cherry Flowers
    {
        25,                                             // terrain id
        0,                                              // global terrain type
        "Cherry Flowers",                               // terrain name

        "cherry_flowers.png",

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"cherry_flowers.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 26. Small Stones
    {
        26,                                             // terrain id
        0,                                              // global terrain type
        "Small Stones",                                 // terrain name

        "small_stones.png",

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"small_stones.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 27. Small Snowy Stones
    {
        27,                                             // terrain id
        0,                                              // global terrain type
        "Small Snowy Stones",                           // terrain name

        "small_snowy_stones.png",

        // ground_layer_img
        1,
        {"snow.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"small_snowy_stones.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", "snow", nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 28. Small Mushrooms
    {
        28,                                             // terrain id
        0,                                              // global terrain type
        "Small Mushrooms",                              // terrain name

        "small_mushrooms.png",

        // ground_layer_img
        1,
        {"dirt.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"small_mushrooms.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 29. Brazier
    {
        29,                                             // terrain id
        -1,                                             // global terrain type
        "Brazier",                                      // terrain name

        "brazier.png",

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"brazier.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 30. Lit Brazier
    {
        30,                                             // terrain id
        -1,                                             // global terrain type
        "Lit Brazier",                                  // terrain name

        "lit_brazier.png",

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"brazier/brazier.png", nullptr, nullptr, nullptr, nullptr},
        {8, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 31. Great Tree
    {
        31,                                             // terrain id
        -1,                                             // global terrain type
        "Great Tree",                                   // terrain name

        "great_tree/great_tree_01.png",

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        3,
        {"great_tree/great_tree_01.png", "great_tree/great_tree_02.png", "great_tree/great_tree_03.png", nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", "grass", nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 32. Dead Great Tree
    {
        32,                                             // terrain id
        -1,                                             // global terrain type
        "Dead Great Tree",                              // terrain name

        "great_tree/dead_great_tree_1.png",

        // ground_layer_img
        1,
        {"dirt.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        5,
        {"great_tree/dead_great_tree_1.png", "great_tree/dead_great_tree_2.png", "great_tree/dead_great_tree_3.png", "great_tree/dead_great_tree_4.png", "great_tree/dead_great_tree_5.png"},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", "grass", nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 33. Snow Great Tree
    {
        33,                                             // terrain id
        -1,                                             // global terrain type
        "Snow Great Tree",                              // terrain name

        "snow_great_tree.png",

        // ground_layer_img
        1,
        {"snow_grass.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"snow_great_tree.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", "grass", "snow", nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 34. Tropical Forest
    {
        34,                                             // terrain id
        -1,                                             // global terrain type
        "Tropical Forest",                              // terrain name

        "tropical_forest.png",

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"tropical_forest.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 35. Rainforest
    {
        35,                                             // terrain id
        -1,                                             // global terrain type
        "Rainforest",                                   // terrain name

        "rainforest.png",

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"rainforest.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 36. Palm Forest
    {
        36,                                             // terrain id
        -1,                                             // global terrain type
        "Palm Forest",                                  // terrain name

        "palm_forest.png",

        // ground_layer_img
        1,
        {"beach_sand.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"palm_forest.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", "sand", nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 37. Savanna
    {
        37,                                             // terrain id
        -1,                                             // global terrain type
        "Savanna",                                      // terrain name

        "savanna.png",

        // ground_layer_img
        1,
        {"semi_dry_dirt.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"savanna.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", "dry", nullptr, nullptr, nullptr},   // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 38. Pine Forest
    {
        38,                                             // terrain id
        -1,                                             // global terrain type
        "Pine Forest",                                  // terrain name

        "pine_forest.png",

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"pine_forest.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 39. Snowy Pine Forest
    {
        39,                                             // terrain id
        -1,                                             // global terrain type
        "Snowy Pine Forest",                            // terrain name

        "snowy_pine_forest.png",

        // ground_layer_img
        1,
        {"snow_grass.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"snowy_pine_forest.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", "snow", nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 40. Summer Deciduous Forest
    {
        40,                                             // terrain id
        -1,                                             // global terrain type
        "Summer Deciduous Forest",                      // terrain name

        "summer_forest/summer_forest_01.png",

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        5,
        {"summer_forest/summer_forest_01.png", "summer_forest/summer_forest_02.png", "summer_forest/summer_forest_03.png", "summer_forest/summer_forest_06.png", "summer_forest/summer_forest_08.png"},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 41. Fall Deciduous Forest
    {
        41,                                             // terrain id
        -1,                                             // global terrain type
        "Fall Deciduous Forest",                        // terrain name

        "fall_forest.png",

        // ground_layer_img
        1,
        {"semi_dry_grass.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"fall_forest.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 42. Cherry Forest
    {
        42,                                             // terrain id
        -1,                                             // global terrain type
        "Cherry Forest",                                // terrain name

        "cherry_forest.png",

        // ground_layer_img
        1,
        {"green_grass.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"cherry_forest.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"ground", nullptr, nullptr, nullptr, nullptr}, // positive tags (for tiles that don't have a ground_layer_img)
        {"snow", nullptr, nullptr, nullptr, nullptr}    // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 43. Regular Hills
    {
        43,                                             // terrain id
        0,                                              // global terrain type
        "Regular Hills",                                // terrain name

        "regular_hills.png",

        // ground_layer_img
        3,
        {"hills/regular1.png", "hills/regular2.png", "hills/regular3.png", nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "hill", nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 44. Dry Hills
    {
        44,                                             // terrain id
        0,                                              // global terrain type
        "Dry Hills",                                    // terrain name

        "dry_hills.png",

        // ground_layer_img
        3,
        {"hills/dry1.png", "hills/dry2.png", "hills/dry3.png", nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "hill", "dry", nullptr},     // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 45. Dunes
    {
        45,                                             // terrain id
        0,                                              // global terrain type
        "Dunes",                                        // terrain name

        "dunes.png",

        // ground_layer_img
        3,
        {"hills/desert1.png", "hills/desert2.png", "hills/desert3.png", nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "hill", "sand", nullptr},    // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 46. Snowy Hills
    {
        46,                                             // terrain id
        0,                                              // global terrain type
        "Snowy Hills",                                  // terrain name

        "snowy_hills.png",

        // ground_layer_img
        3,
        {"hills/snow1.png", "hills/snow2.png", "hills/snow3.png", nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "hill", "snow", nullptr},    // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 47. Regular Mountains
    {
        47,                                                 // terrain id
        -1,                                                 // global terrain type
        "Regular Mountains",                                // terrain name

        "regular_mountains.png",

        // ground_layer_img
        1,
        {"regular_mountains.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "mountain", nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},      // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}       // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 48. Dry Mountains
    {
        48,                                             // terrain id
        -1,                                             // global terrain type
        "Dry Mountains",                                // terrain name

        "dry_mountains.png",

        // ground_layer_img
        1,
        {"dry_mountains.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "mountain", "dry", nullptr}, // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 49. Snow Mountains
    {
        49,                                             // terrain id
        -1,                                             // global terrain type
        "Snow Mountains",                               // terrain name

        "snow_mountains.png",

        // ground_layer_img
        1,
        {"snow_mountains.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "mountain", "snow", nullptr},// tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 50. Desert Mountains
    {
        50,                                             // terrain id
        -1,                                             // global terrain type
        "Desert Mountains",                             // terrain name

        "desert_mountains.png",

        // ground_layer_img
        1,
        {"desert_mountains.png", "mountain/desert2.png", "mountain/desert3.png", "mountain/desert4.png", "mountain/desert5.png"},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "mountain", "sand", nullptr},// tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 51. Volcano
    {
        51,                                             // terrain id
        -1,                                             // global terrain type
        "Volcano",                                      // terrain name

        "volcano.png",

        // ground_layer_img
        1,
        {"volcano.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "mountain", "lava", nullptr},// tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 52. Basic Stone floor
    {
        52,                                             // terrain id
        0,                                              // global terrain type
        "Basic Stone floor",                            // terrain name

        "basic_stone_floor.png",

        // ground_layer_img
        1,
        {"basic_stone_floor.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "floor", nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 53. Ancient Stone floor
    {
        53,                                             // terrain id
        0,                                              // global terrain type
        "Ancient Stone floor",                          // terrain name

        "ancient_stone_floor.png",

        // ground_layer_img
        1,
        {"ancient_stone_floor.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "floor", nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 54. Basic Wooden floor
    {
        54,                                             // terrain id
        0,                                              // global terrain type
        "Basic Wooden floor",                           // terrain name

        "basic_wooden_floor.png",

        // ground_layer_img
        1,
        {"basic_wooden_floor.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "floor", nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 55. Old Wooden floor
    {
        55,                                             // terrain id
        0,                                              // global terrain type
        "Old Wooden floor",                             // terrain name

        "old_wooden_floor.png",

        // ground_layer_img
        1,
        {"old_wooden_floor.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "floor", nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 56. Beam of light
    {
        56,                                             // terrain id
        0,                                              // global terrain type
        "Beam of light",                                // terrain name

        "beam_of_light.png",

        // ground_layer_img
        1,
        {"cave_floor.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"beam_of_light.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 57. Cave floor
    {
        57,                                             // terrain id
        0,                                              // global terrain type
        "Cave Floor",                                   // terrain name

        "cave_floor.png",

        // ground_layer_img
        1,
        {"cave_floor.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "floor", "cave", nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 58. Earthy Cave Floor
    {
        58,                                             // terrain id
        0,                                              // global terrain type
        "Earthy Cave Floor",                            // terrain name

        "earthy_cave_floor.png",

        // ground_layer_img
        1,
        {"earthy_cave_floor.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "floor", "cave", nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 59. Cave Path
    {
        59,                                             // terrain id
        0,                                              // global terrain type
        "Cave Path",                                    // terrain name

        "cave_path.png",

        // ground_layer_img
        1,
        {"cave_path.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "floor", "cave", "path"},    // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 60. Mushroom Grove
    {
        60,                                             // terrain id
        0,                                              // global terrain type
        "Mushroom Grove",                               // terrain name

        "mushroom_grove.png",

        // ground_layer_img
        1,
        {"cave_floor.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        1,
        {"mushroom_grove.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {nullptr, nullptr, nullptr, nullptr, nullptr},  // tags (for tiles that have a ground_layer_img)
        {"cave", nullptr, nullptr, nullptr, nullptr},   // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 61. Rockbound Cave
    {
        61,                                             // terrain id
        -1,                                             // global terrain type
        "Rockbound Cave",                               // terrain name

        "rockbound_cave.png",

        // ground_layer_img
        1,
        {"rockbound_cave.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "cave", nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 62. Earthy Rockbound Cave
    {
        62,                                             // terrain id
        -1,                                             // global terrain type
        "Earthy Rockbound Cave",                        // terrain name

        "earthy_rockbound_cave.png",

        // ground_layer_img
        1,
        {"earthy_rockbound_cave.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "ground", "cave", nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 63. Regular Cave Wall
    {
        63,                                             // terrain id
        -1,                                             // global terrain type
        "Regular Cave Wall",                            // terrain name

        "regular_cave_wall.png",

        // ground_layer_img
        1,
        {"regular_cave_wall.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "cave", "wall", nullptr, nullptr},     // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 64. Earthy Cave Wall
    {
        64,                                             // terrain id
        -1,                                             // global terrain type
        "Earthy Cave Wall",                             // terrain name

        "earthy_cave_wall.png",

        // ground_layer_img
        1,
        {"earthy_cave_wall.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "cave", "wall", nullptr, nullptr},     // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 65. Regular Chasm
    {
        65,                                             // terrain id
        -1,                                             // global terrain type
        "Regular Chasm",                                // terrain name

        "regular_chasm.png",

        // ground_layer_img
        1,
        {"chasm/depths.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "chasm", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 66. Earthy Chasm
    {
        66,                                             // terrain id
        -1,                                             // global terrain type
        "Earthy Chasm",                                 // terrain name

        "earthy_chasm.png",

        // ground_layer_img
        1,
        {"chasm/depths.png", nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "chasm", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 67. Ethereal Chasm
    {
        67,                                             // terrain id
        -1,                                             // global terrain type
        "Ethereal Chasm",                               // terrain name

        "ethereal_chasm.png",

        // ground_layer_img
        5,
        {"chasm/abyss1.png", "chasm/abyss2.png", "chasm/abyss3.png", "chasm/abyss4.png", "chasm/abyss5.png"},
        {1, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "chasm", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 68. Lava Chasm
    {
        68,                                             // terrain id
        -1,                                             // global terrain type
        "Lava Chasm",                                   // terrain name

        "lava_chasm.png",

        // ground_layer_img
        1,
        {"lava/lava.png", nullptr, nullptr, nullptr, nullptr},
        {4, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "chasm", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    },

    // 69. Lava
    {
        69,                                             // terrain id
        -1,                                             // global terrain type
        "Lava",                                         // terrain name

        "lava.png",

        // ground_layer_img
        1,
        {"lava/lava.png", nullptr, nullptr, nullptr, nullptr},
        {4, 1, 1, 1, 1},

        // top_layer_img
        0,
        {nullptr, nullptr, nullptr, nullptr, nullptr},
        {1, 1, 1, 1, 1},

        {"base", "water", nullptr, nullptr, nullptr},   // tags (for tiles that have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr},  // positive tags (for tiles that don't have a ground_layer_img)
        {nullptr, nullptr, nullptr, nullptr, nullptr}   // negative tags (for tiles that don't have a ground_layer_img)
    }
};
