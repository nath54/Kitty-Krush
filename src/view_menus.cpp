#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
//
#include <iostream>
#include <string>
#include <cmath>
#include <unistd.h>
#include <map>
#include <vector>
//
#include "view.hpp"
#include "color.hpp"
#include "model_element.hpp"
#include "utils.hpp"
#include "map_tiles.hpp"


void on_bt_quit_click(WINDOW_ELT_CLICKABLE_T elt, MainGame* main_game, std::vector<std::string> additional_fn_args = (std::vector<std::string>){}) {

    //
    main_game->quit();

}


//
void on_bt_change_page_to_main_menu(WINDOW_ELT_CLICKABLE_T elt, MainGame* main_game, std::vector<std::string> additional_fn_args = (std::vector<std::string>){}) {

    //
    main_game->change_page("main_menu");
}


//
void on_bt_change_page_to_game_settings(WINDOW_ELT_CLICKABLE_T elt, MainGame* main_game, std::vector<std::string> additional_fn_args = (std::vector<std::string>){}) {

    //
    WINDOW_ELT_MAP_VIEWER_T map_viewer = main_game->main_view->map_viewer;

    //
    if(map_viewer == nullptr){ return; }

    //
    map_viewer->map_creator_cursor = "";
    map_viewer->map_creator_elt_category = 0;
    map_viewer->dragging_entity = false;
    map_viewer->can_go_here_tiles.clear();

    //
    main_game->change_page("game_settings");
}


//
void on_bt_change_page_to_in_game(WINDOW_ELT_CLICKABLE_T elt, MainGame* main_game, std::vector<std::string> additional_fn_args = (std::vector<std::string>){}) {

    //
    WINDOW_ELT_MAP_VIEWER_T map_viewer = main_game->main_view->map_viewer;

    //
    if(map_viewer == nullptr){ return; }

    //
    map_viewer->map_creator_cursor = "";
    map_viewer->map_creator_elt_category = 0;
    map_viewer->dragging_entity = false;
    map_viewer->can_go_here_tiles.clear();

    //
    main_game->change_page("in_game");
}


//
void on_bt_change_page_to_map_creator(WINDOW_ELT_CLICKABLE_T elt, MainGame* main_game, std::vector<std::string> additional_fn_args = (std::vector<std::string>){}) {

    //
    WINDOW_ELT_MAP_VIEWER_T map_viewer = main_game->main_view->map_viewer;

    //
    if(map_viewer == nullptr){ return; }

    //
    map_viewer->map_creator_cursor = "";
    map_viewer->map_creator_elt_category = 0;
    map_viewer->dragging_entity = false;
    map_viewer->can_go_here_tiles.clear();

    //
    main_game->change_page("map_creator");
}


//
void set_new_entity_dragged(MainGame* main_game, int level, bool type){

    //
    WINDOW_ELT_MAP_VIEWER_T map_viewer = main_game->main_view->map_viewer;

    //
    if(map_viewer == nullptr){ return; }

    //
    map_viewer->dragging_entity = true;
    map_viewer->dragging_new_entity = true;
    map_viewer->entity_dragged.level = level;
    map_viewer->entity_dragged.type = type;

    //
    // (Coord src, bool new_entity, bool reset, int new_entity_level, int new_entity_type)
    main_game->update_where_entity_can_move((Coord){0, 0}, true, false, level, type);

}


//
void on_bt_new_warrior_lvl1(WINDOW_ELT_CLICKABLE_T elt, MainGame* main_game, std::vector<std::string> additional_fn_args = (std::vector<std::string>){}) {
    //
    set_new_entity_dragged(main_game, 1, true);
}


//
void on_bt_new_warrior_lvl2(WINDOW_ELT_CLICKABLE_T elt, MainGame* main_game, std::vector<std::string> additional_fn_args = (std::vector<std::string>){}) {
    //
    set_new_entity_dragged(main_game, 2, true);
}


//
void on_bt_new_warrior_lvl3(WINDOW_ELT_CLICKABLE_T elt, MainGame* main_game, std::vector<std::string> additional_fn_args = (std::vector<std::string>){}) {
    //
    set_new_entity_dragged(main_game, 3, true);
}


//
void on_bt_new_warrior_lvl4(WINDOW_ELT_CLICKABLE_T elt, MainGame* main_game, std::vector<std::string> additional_fn_args = (std::vector<std::string>){}) {
    //
    set_new_entity_dragged(main_game, 4, true);
}


//
void on_bt_new_tower(WINDOW_ELT_CLICKABLE_T elt, MainGame* main_game, std::vector<std::string> additional_fn_args = (std::vector<std::string>){}) {
    //
    set_new_entity_dragged(main_game, 2, false);
}


//
void on_bt_end_turn(WINDOW_ELT_CLICKABLE_T elt, MainGame* main_game, std::vector<std::string> additional_fn_args = (std::vector<std::string>){}) {

    //
    WINDOW_ELT_MAP_VIEWER_T map_viewer = main_game->main_view->map_viewer;

    //
    if(map_viewer == nullptr){ return; }

    //
    map_viewer->map_creator_cursor = "";
    map_viewer->map_creator_elt_category = 0;
    map_viewer->dragging_entity = false;
    map_viewer->can_go_here_tiles.clear();

    //
    main_game->action_end_turn();
}


//
void on_bt_continue_previous_game(WINDOW_ELT_CLICKABLE_T elt, MainGame* main_game, std::vector<std::string> additional_fn_args = (std::vector<std::string>){}) {

    //
    WINDOW_ELT_MAP_VIEWER_T map_viewer = main_game->main_view->map_viewer;

    //
    if(map_viewer == nullptr){ return; }

    //
    map_viewer->map_creator_cursor = "";
    map_viewer->map_creator_elt_category = 0;
    map_viewer->dragging_entity = false;
    map_viewer->can_go_here_tiles.clear();

    //
    main_game->crt_map_file = "maps/saved_data/saved_map.kkmap";
    //
    main_game->change_page("in_game");
}


//
void on_bt_play_map(WINDOW_ELT_CLICKABLE_T elt, MainGame* main_game, std::vector<std::string> additional_fn_args = (std::vector<std::string>){}) {

    //
    WINDOW_ELT_MAP_VIEWER_T map_viewer = main_game->main_view->map_viewer;

    //
    if(map_viewer == nullptr){ return; }

    //
    map_viewer->map_creator_cursor = "";
    map_viewer->map_creator_elt_category = 0;
    map_viewer->dragging_entity = false;
    map_viewer->can_go_here_tiles.clear();

    //
    if( additional_fn_args.size() == 0 ){
        std::cerr << "Error : no map file given in arguments !\n";
        return;
    }
    //
    main_game->crt_map_file = additional_fn_args[0];
    //
    main_game->change_page("in_game");
}


//
void on_bt_map_creator_bt_category(WINDOW_ELT_CLICKABLE_T elt, MainGame* main_game, std::vector<std::string> additional_fn_args = (std::vector<std::string>){}) {

    //
    WINDOW_ELT_MAP_VIEWER_T map_viewer = main_game->main_view->map_viewer;

    //
    if(map_viewer == nullptr){ return; }

    //
    map_viewer->map_creator_cursor = "";
    map_viewer->map_creator_elt_category = 0;

    //
    if( additional_fn_args.size() == 0 ){
        std::cerr << "Error : no map file given in arguments !\n";
        return;
    }

    //
    // TILES
    //
    for(int i = 7; i < 7 + 70; i++){
        //
        if(main_game->main_view->win_page_manager->pages["map_creator"]->elts.size() <= i){ continue; }
        //
        main_game->main_view->win_page_manager->pages["map_creator"]->elts[i]->visible = (additional_fn_args[0] == "tiles");
    }

    //
    // COLORS
    //
    for(int i = 7 + 70; i < 7 + 70 + 10; i++){
        //
        if(main_game->main_view->win_page_manager->pages["map_creator"]->elts.size() <= i){ continue; }
        //
        main_game->main_view->win_page_manager->pages["map_creator"]->elts[i]->visible = (additional_fn_args[0] == "colors");
    }

    //
    // ENTITIES
    //
    for(int i = 7 + 70 + 10; i < 7 + 70 + 10 + 8; i++){
        //
        if(main_game->main_view->win_page_manager->pages["map_creator"]->elts.size() <= i){ continue; }
        //
        main_game->main_view->win_page_manager->pages["map_creator"]->elts[i]->visible = (additional_fn_args[0] == "entities");
    }
}


//
void on_bt_map_creator_clear(WINDOW_ELT_CLICKABLE_T elt, MainGame* main_game, std::vector<std::string> additional_fn_args = (std::vector<std::string>){}) {

    //
    WINDOW_ELT_MAP_VIEWER_T map_viewer = main_game->main_view->map_viewer;

    //
    if(map_viewer == nullptr){ return; }

    //
    map_viewer->map_creator_cursor = "";
    map_viewer->map_creator_elt_category = 0;


    //
    main_game->main_view->map_viewer->clear();
    main_game->game_model->reset_bandits_layer();
    main_game->game_model->reset_provinces();
    main_game->game_model->reset_tiles_layer();

}


//
void on_bt_map_creator_generate(WINDOW_ELT_CLICKABLE_T elt, MainGame* main_game, std::vector<std::string> additional_fn_args = (std::vector<std::string>){}) {

    //
    WINDOW_ELT_MAP_VIEWER_T map_viewer = main_game->main_view->map_viewer;

    //
    if(map_viewer == nullptr){ return; }

    //
    map_viewer->map_creator_cursor = "";
    map_viewer->map_creator_elt_category = 0;

    //
    main_game->main_view->map_viewer->clear();
    main_game->game_model->reset_bandits_layer();
    main_game->game_model->reset_provinces();
    main_game->game_model->reset_tiles_layer();

    //
    main_game->generate_random_map();

}

//
void on_bt_map_creator_tile(WINDOW_ELT_CLICKABLE_T elt, MainGame* main_game, std::vector<std::string> additional_fn_args = (std::vector<std::string>){}) {

    //
    WINDOW_ELT_MAP_VIEWER_T map_viewer = main_game->main_view->map_viewer;

    //
    if(map_viewer == nullptr){ return; }

    //
    if( additional_fn_args.size() == 0 ){ return; }

    //
    int tile_num = std::stoi( additional_fn_args[0] );

    //
    map_viewer->map_creator_elt_category = 1;
    map_viewer->map_creator_elt_id = tile_num;
    map_viewer->map_creator_elt_color_mod = (Color){255, 255, 255};

    //
    map_viewer->map_creator_cursor = "res/sprites/map_w/" + std::string(allTileData[tile_num].img_preview);

}


//
void on_bt_map_creator_color(WINDOW_ELT_CLICKABLE_T elt, MainGame* main_game, std::vector<std::string> additional_fn_args = (std::vector<std::string>){}) {

    //
    WINDOW_ELT_MAP_VIEWER_T map_viewer = main_game->main_view->map_viewer;

    //
    if(map_viewer == nullptr){ return; }

    //
    if( additional_fn_args.size() == 0 ){ return; }

    //
    int color_num = std::stoi( additional_fn_args[0] );

    //
    map_viewer->map_creator_elt_category = 2;
    map_viewer->map_creator_elt_id = color_num;
    map_viewer->map_creator_cursor = "res/ui/tile_for_color.png";

    map_viewer->map_creator_elt_color_mod = allPlayerColors[color_num - 1];

}


//
void on_bt_map_creator_entity(WINDOW_ELT_CLICKABLE_T elt, MainGame* main_game, std::vector<std::string> additional_fn_args = (std::vector<std::string>){}) {

    //
    WINDOW_ELT_MAP_VIEWER_T map_viewer = main_game->main_view->map_viewer;

    //
    if(map_viewer == nullptr){ return; }

    //
    if( additional_fn_args.size() == 0 ){ return; }

    //
    int entity_num = std::stoi( additional_fn_args[0] );

    //
    map_viewer->map_creator_elt_category = 3;
    map_viewer->map_creator_elt_id = entity_num;
    map_viewer->map_creator_elt_color_mod = (Color){255, 255, 255};

    //
    if (entity_num == 00){ // Bandit camp
        map_viewer->map_creator_cursor = "res/sprites/entities/bandit_camp2_p.png";
    }
    else if (entity_num == 01){ // Town
        map_viewer->map_creator_cursor = "res/sprites/entities/village2_p.png";

    } else if (entity_num == 02){ // tower
        map_viewer->map_creator_cursor = "res/sprites/entities/tower2_p.png";

    } else if (entity_num == 10){ // bandit
        map_viewer->map_creator_cursor = "res/sprites/entities/bandit2_p.png";

    } else if (entity_num == 11){ // cat lvl1
        map_viewer->map_creator_cursor = "res/sprites/entities/cat_lvl1_p.png";

    } else if (entity_num == 12){ // cat lvl2
        map_viewer->map_creator_cursor = "res/sprites/entities/cat_lvl2_p.png";

    } else if (entity_num == 13){ // cat lvl3
        map_viewer->map_creator_cursor = "res/sprites/entities/cat_lvl3_p.png";

    } else if (entity_num == 14){ // cat lvl4
        map_viewer->map_creator_cursor = "res/sprites/entities/cat_lvl4_p.png";
    }
}


//
void MainView::init_page_main_menu() {

    //
    WINDOW_ATTRIBUTE_T win_attr = this->get_win_attr();

    // Create Main Menu
    this->win_page_manager->pages["main_menu"] = new WindowPage();

    //
    this->win_page_manager->pages["main_menu"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_SPRITE_T(
            this->win_page_manager->default_style,  // STYLE_T           style,
            "res/bgs/bg_main_menu_2.png",           // std::string      img_path,
            nvi(0),                                 // VALUE_T           x,
            nvi(0),                        // VALUE_T           y,
            nvpww(win_attr, 100),                   // VALUE_T           w,
            nvpwh(win_attr, 100),                   // VALUE_T           h,
            nvi(0),                                 // VALUE_T           angle               = nvi(0),
            false,                                  // bool             flip_h              = false,
            false,                                  // bool             flip_v              = false,
            SPRITE_NO_CROP(),                       // SPRITE_CROP_T      sprite_crop         = SPRITE_NO_CROP(),
            // SPRITE_RATIO_CUSTOM(1, 1),           // SPRITE_RATIO_T     sprite_ratio        = SPRITE_RATIO_ORIGINAL(),
            SPRITE_RATIO_ORIGINAL(),                // SPRITE_RATIO_T     sprite_ratio        = SPRITE_RATIO_ORIGINAL(),
            SPRITE_RESIZE_FIT(1.9),                 // SPRITE_RESIZE_T    sprite_resize       = SPRITE_RESIZE_KEEP_ORIGINAL(),
            SPRITE_POS_ALIGN_CENTER(),              // SPRITE_POSITION_T  sprite_h_position   = SPRITE_POS_ALIGN_START(),
            SPRITE_POS_ALIGN_CENTER()               // SPRITE_POSITION_T  sprite_v_position   = SPRITE_POS_ALIGN_START()
        )

    );


    //
    this->win_page_manager->pages["main_menu"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "Play !",                               // std::string                      text
            nvpww(win_attr, 35),                    // VALUE_T                           x
            nvpwh(win_attr, 45),                    // VALUE_T                           y
            nvpww(win_attr, 30),                    // VALUE_T                           w
            nvi(100),                               // VALUE_T                           h
            on_bt_change_page_to_game_settings      // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
        )

    );

    //
    this->win_page_manager->pages["main_menu"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "Quit...",                              // std::string                      text
            nvpww(win_attr, 40),                    // VALUE_T                           x
            nvpwh(win_attr, 65),                    // VALUE_T                           y
            nvpww(win_attr, 20),                    // VALUE_T                           w
            nvi(40),                                // VALUE_T                           h
            on_bt_quit_click                        // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
        )

    );

}



//
void MainView::init_page_game_settings() {

    //
    WINDOW_ATTRIBUTE_T win_attr = this->get_win_attr();

    //
    this->win_page_manager->pages["game_settings"] = new WindowPage();

    //
    this->win_page_manager->pages["game_settings"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_SPRITE_T(
            this->win_page_manager->default_style,  // STYLE_T           style,
            "res/bgs/bg_game_settings_menu.png",    // std::string      img_path,
            nvi(0),                                 // VALUE_T           x,
            nvi(0),                        // VALUE_T           y,
            nvpww(win_attr, 100),                   // VALUE_T           w,
            nvpwh(win_attr, 100),                   // VALUE_T           h,
            nvi(0),                                 // VALUE_T           angle               = nvi(0),
            false,                                  // bool             flip_h              = false,
            false,                                  // bool             flip_v              = false,
            SPRITE_NO_CROP(),                       // SPRITE_CROP_T      sprite_crop         = SPRITE_NO_CROP(),
            // SPRITE_RATIO_CUSTOM(1, 1),           // SPRITE_RATIO_T     sprite_ratio        = SPRITE_RATIO_ORIGINAL(),
            SPRITE_RATIO_ORIGINAL(),                // SPRITE_RATIO_T     sprite_ratio        = SPRITE_RATIO_ORIGINAL(),
            SPRITE_RESIZE_FIT(1.9),                 // SPRITE_RESIZE_T    sprite_resize       = SPRITE_RESIZE_KEEP_ORIGINAL(),
            SPRITE_POS_ALIGN_CENTER(),              // SPRITE_POSITION_T  sprite_h_position   = SPRITE_POS_ALIGN_START(),
            SPRITE_POS_ALIGN_CENTER()               // SPRITE_POSITION_T  sprite_v_position   = SPRITE_POS_ALIGN_START()
        )

    );

    //
    this->win_page_manager->pages["game_settings"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "Back",                                 // std::string                      text
            nvi(15),                                // VALUE_T                           x
            nvi(15),                                // VALUE_T                           y
            nvi(200),                               // VALUE_T                           w
            nvi(40),                                // VALUE_T                           h
            on_bt_change_page_to_main_menu          // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
        )

    );

    //
    this->win_page_manager->pages["game_settings"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_RECT_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            (Color){255, 255, 255},                 // Color                            cl
            nvpww(win_attr, 15),                    // VALUE_T                           x
            nvi(80),                               // VALUE_T                           y
            nvpww(win_attr, 100 - 2 * 15),          // VALUE_T                           w
            nvi(2),                                 // VALUE_T                           h
            nvi(2)                         // VALUE_T                           radius
        )

    );

    //
    this->win_page_manager->pages["game_settings"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "Continue game",                        // std::string                      text
            nvpww(win_attr, 20),                    // VALUE_T                           x
            nvi(100),                               // VALUE_T                           y
            nvpww(win_attr, 100 - 2 * 20),          // VALUE_T                           w
            nvi(60),                                // VALUE_T                           h
            on_bt_continue_previous_game            // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
        )

    );

    //
    this->win_page_manager->pages["game_settings"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_RECT_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            (Color){255, 255, 255},                 // Color                            cl
            nvpww(win_attr, 15),                    // VALUE_T                           x
            nvi(180),                               // VALUE_T                           y
            nvpww(win_attr, 100 - 2 * 15),          // VALUE_T                           w
            nvi(2),                                 // VALUE_T                           h
            nvi(2)                         // VALUE_T                           radius
        )

    );

    //
    this->win_page_manager->pages["game_settings"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "Create a new map",                     // std::string                      text
            nvpww(win_attr, 20),                    // VALUE_T                           x
            nvi(200),                               // VALUE_T                           y
            nvpww(win_attr, 100 - 2 * 20),          // VALUE_T                           w
            nvi(60),                                // VALUE_T                           h
            on_bt_change_page_to_map_creator        // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
        )

    );

    //
    this->win_page_manager->pages["game_settings"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_RECT_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            (Color){255, 255, 255},                 // Color                            cl
            nvpww(win_attr, 15),                    // VALUE_T                           x
            nvi(280),                               // VALUE_T                           y
            nvpww(win_attr, 100 - 2 * 15),          // VALUE_T                           w
            nvi(2),                                 // VALUE_T                           h
            nvi(2)                         // VALUE_T                           radius
        )

    );


    //
    this->win_page_manager->pages["game_settings"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_TEXT_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "Play another game :",                  // std::string                      txt
            nvpww(win_attr, 15),                    // VALUE_T                           x
            nvi(300),                               // VALUE_T                           y
            nvpww(win_attr, 100 - 2 * 15),          // VALUE_T                           w
            nvi(50)                                 // VALUE_T                           h
        )

    );


}



//
void MainView::init_page_in_game() {

    //
    WINDOW_ATTRIBUTE_T win_attr = this->get_win_attr();

    //
    this->win_page_manager->pages["in_game"] = new WindowPage();

    //
    this->map_viewer = CREATE_WINDOW_ELT_MAP_VIEWER_T(
        this->win_page_manager->default_style,  // STYLE_T                           style
        nvi(0),                                 // VALUE_T                           x
        nvi(0),                                 // VALUE_T                           y
        nvpww(win_attr, 100),                   // VALUE_T                           w
        nvpwh(win_attr, 100),                   // VALUE_T                           h
        on_map_viewer_click                     // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>  on_click
    );
    this->map_viewer->game_model = this->game_model;

    //
    this->map_viewer->rect_current_player = CREATE_WINDOW_ELT_RECT_T(
        this->win_page_manager->default_style,  // STYLE_T                           style
        (Color){150, 150, 150},                 // Color                            cl
        nvpww(win_attr, 40),                    // VALUE_T                           x
        nvi(15),                                // VALUE_T                           y
        nvpww(win_attr, 20),                    // VALUE_T                           w
        nvi(40),                                // VALUE_T                           h
        nvi(15)                                 // VALUE_T                           radius
    );

    //
    this->map_viewer->txt_current_player = CREATE_WINDOW_ELT_TEXT_T(
        this->win_page_manager->default_style,  // STYLE_T                           style
        "player 1",                             // std::string                      txt
        nvpww(win_attr, 40),                    // VALUE_T                           x
        nvi(15),                                // VALUE_T                           y
        nvpww(win_attr, 20),                    // VALUE_T                           w
        nvi(40)                                 // VALUE_T                           h
    );

    //
    this->map_viewer->elt_province_1 = CREATE_WINDOW_ELT_TEXT_T(
        this->win_page_manager->default_style,  // STYLE_T                           style
        "Selected province : ",                 // std::string                      txt
        nvpww(win_attr, 38, 0),                 // VALUE_T                           x
        nvi(70),                                // VALUE_T                           y
        nvi(160),                               // VALUE_T                           w
        nvi(40)                                 // VALUE_T                           h
    );

    //
    this->map_viewer->txt_province_treasury = CREATE_WINDOW_ELT_TEXT_T(
        this->win_page_manager->default_style,  // STYLE_T                           style
        "10",                                   // std::string                      txt
        nvpww(win_attr, 38, 160),               // VALUE_T                           x
        nvi(70),                                // VALUE_T                           y
        nvi(40),                                // VALUE_T                           w
        nvi(40)                                 // VALUE_T                           h
    );

    //
    this->map_viewer->elt_province_2 = CREATE_WINDOW_ELT_SPRITE_T(
        this->win_page_manager->default_style,  // STYLE_T                           style
        "res/ui/gold.png",                      // std::string                      txt
        nvpww(win_attr, 38, 200),               // VALUE_T                           x
        nvi(80),                                // VALUE_T                           y
        nvi(40),                                // VALUE_T                           w
        nvi(40)                                 // VALUE_T                           h
    );

    //
    this->map_viewer->txt_province_expected_income = CREATE_WINDOW_ELT_TEXT_T(
        this->win_page_manager->default_style,  // STYLE_T                           style
        "(+10)",                                // std::string                      txt
        nvpww(win_attr, 38, 230),               // VALUE_T                           x
        nvi(70),                                // VALUE_T                           y
        nvi(40),                                // VALUE_T                           w
        nvi(40)                                 // VALUE_T                           h
    );

    //
    this->map_viewer->bt_unit_lvl1 = CREATE_WINDOW_ELT_BUTTON_T(
        this->win_page_manager->default_style,  // STYLE_T                           style
        "res/sprites/entities/cat_lvl1_p.png",  // std::string                      text
        nvi(15),                                // VALUE_T                           x
        nvi(100),                               // VALUE_T                           y
        nvi(60),                                // VALUE_T                           w
        nvi(60),                                // VALUE_T                           h
        on_bt_new_warrior_lvl1                  // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
    );

    //
    this->map_viewer->txt_unit_lvl1 = CREATE_WINDOW_ELT_TEXT_T(
        this->win_page_manager->default_style,  // STYLE_T                           style
        std::to_string(units_new_costs[1]),     // std::string                      txt
        nvi(15),                                // VALUE_T                           x
        nvi(165),                               // VALUE_T                           y
        nvi(60),                                // VALUE_T                           w
        nvi(20)                                 // VALUE_T                           h
    );

    //
    this->map_viewer->bt_unit_lvl2 = CREATE_WINDOW_ELT_BUTTON_T(
        this->win_page_manager->default_style,  // STYLE_T                           style
        "res/sprites/entities/cat_lvl2_p.png",  // std::string                      text
        nvi(15),                                // VALUE_T                           x
        nvi(200),                               // VALUE_T                           y
        nvi(60),                                // VALUE_T                           w
        nvi(60),                                // VALUE_T                           h
        on_bt_new_warrior_lvl2                  // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
    );

    //
    this->map_viewer->txt_unit_lvl2 = CREATE_WINDOW_ELT_TEXT_T(
        this->win_page_manager->default_style,  // STYLE_T                           style
        std::to_string(units_new_costs[2]),     // std::string                      txt
        nvi(15),                                // VALUE_T                           x
        nvi(265),                               // VALUE_T                           y
        nvi(60),                                // VALUE_T                           w
        nvi(20)                                 // VALUE_T                           h
    );

    //
    this->map_viewer->bt_unit_lvl3 = CREATE_WINDOW_ELT_BUTTON_T(
        this->win_page_manager->default_style,  // STYLE_T                           style
        "res/sprites/entities/cat_lvl3_p.png",  // std::string                      text
        nvi(15),                                // VALUE_T                           x
        nvi(300),                               // VALUE_T                           y
        nvi(60),                                // VALUE_T                           w
        nvi(60),                                // VALUE_T                           h
        on_bt_new_warrior_lvl3                  // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
    );

    //
    this->map_viewer->txt_unit_lvl3 = CREATE_WINDOW_ELT_TEXT_T(
        this->win_page_manager->default_style,  // STYLE_T                           style
        std::to_string(units_new_costs[3]),     // std::string                      txt
        nvi(15),                                // VALUE_T                           x
        nvi(365),                               // VALUE_T                           y
        nvi(60),                                // VALUE_T                           w
        nvi(20)                                 // VALUE_T                           h
    );

    //
    this->map_viewer->bt_unit_lvl4 = CREATE_WINDOW_ELT_BUTTON_T(
        this->win_page_manager->default_style,  // STYLE_T                           style
        "res/sprites/entities/cat_lvl4_p.png",  // std::string                      text
        nvi(15),                                // VALUE_T                           x
        nvi(400),                               // VALUE_T                           y
        nvi(60),                                // VALUE_T                           w
        nvi(60),                                // VALUE_T                           h
        on_bt_new_warrior_lvl4                  // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
    );

    //
    this->map_viewer->txt_unit_lvl4 = CREATE_WINDOW_ELT_TEXT_T(
        this->win_page_manager->default_style,  // STYLE_T                           style
        std::to_string(units_new_costs[4]),     // std::string                      txt
        nvi(15),                                // VALUE_T                           x
        nvi(465),                               // VALUE_T                           y
        nvi(60),                                // VALUE_T                           w
        nvi(20)                                 // VALUE_T                           h
    );

    //
    this->map_viewer->bt_building_lvl2 = CREATE_WINDOW_ELT_BUTTON_T(
        this->win_page_manager->default_style,  // STYLE_T                           style
        "res/sprites/entities/tower2_p.png",    // std::string                      text
        nvi(15),                                // VALUE_T                           x
        nvi(500),                               // VALUE_T                           y
        nvi(60),                                // VALUE_T                           w
        nvi(60),                                // VALUE_T                           h
        on_bt_new_tower                         // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
    );

    //
    this->map_viewer->txt_building_lvl2 = CREATE_WINDOW_ELT_TEXT_T(
        this->win_page_manager->default_style,  // STYLE_T                           style
        std::to_string(buildings_new_costs[2]), // std::string                      txt
        nvi(15),                                // VALUE_T                           x
        nvi(565),                               // VALUE_T                           y
        nvi(60),                                // VALUE_T                           w
        nvi(20)                                 // VALUE_T                           h
    );


    //
    this->map_viewer->elts_end_game.push_back(

        //
        CREATE_WINDOW_ELT_RECT_T(
            this->win_page_manager->default_style,                  // STYLE_T                           style
            this->win_page_manager->default_style->base_fg_color,   // Color                             cl
            nvpww(win_attr, 20),                                    // VALUE_T                           x
            nvpwh(win_attr, 20),                                    // VALUE_T                           y
            nvpww(win_attr, 60),                                    // VALUE_T                           w
            nvpwh(win_attr, 60),                                    // VALUE_T                           h
            nvi(15)                                                 // VALUE_T                           radius
        )

    );

    //
    this->map_viewer->elts_end_game.push_back(

        //
        CREATE_WINDOW_ELT_RECT_T(
            this->win_page_manager->default_style,                  // STYLE_T                           style
            this->win_page_manager->default_style->base_bg_color,   // Color                             cl
            nvpww(win_attr, 20, 2),                                 // VALUE_T                           x
            nvpwh(win_attr, 20, 2),                                 // VALUE_T                           y
            nvpww(win_attr, 60, -4),                               // VALUE_T                           w
            nvpwh(win_attr, 60, -4),                               // VALUE_T                           h
            nvi(15)                                                 // VALUE_T                           radius
        )

    );

    //
    this->map_viewer->elts_end_game.push_back(

        //
        CREATE_WINDOW_ELT_TEXT_T(
            this->win_page_manager->default_style,  // STYLE_T                          style
            "Player 1 win !",                       // std::string                      txt
            nvpww(win_attr, 33),                    // VALUE_T                          x
            nvpwh(win_attr, 80, -120),              // VALUE_T                          y
            nvpww(win_attr, 33),                    // VALUE_T                          w
            nvi(50)                                 // VALUE_T                          h
        )

    );

    //
    this->map_viewer->elts_end_game.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                          style
            "Go Back to menu",                      // std::string                      text
            nvpww(win_attr, 33),                    // VALUE_T                          x
            nvpwh(win_attr, 80, -60),               // VALUE_T                          y
            nvpww(win_attr, 33),                    // VALUE_T                          w
            nvi(50),                                // VALUE_T                          h
            on_bt_change_page_to_game_settings      // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
        )

    );

    //
    this->map_viewer->elts_end_game.push_back(

        //
        CREATE_WINDOW_ELT_SPRITE_T(
            this->win_page_manager->default_style,  // STYLE_T           style,
            "res/bgs/victory2.png",                 // std::string      img_path,
            nvpww(win_attr, 25),                    // VALUE_T                          x
            nvpwh(win_attr, 20, +15),               // VALUE_T                          y
            nvpww(win_attr, 50),                    // VALUE_T                          w
            nvpwh(win_attr, 45, -30),               // VALUE_T                          h
            nvi(0),                                 // VALUE_T           angle               = nvi(0),
            false,                                  // bool             flip_h              = false,
            false,                                  // bool             flip_v              = false,
            SPRITE_NO_CROP(),                       // SPRITE_CROP_T      sprite_crop         = SPRITE_NO_CROP(),
            SPRITE_RATIO_ORIGINAL(),                // SPRITE_RATIO_T     sprite_ratio        = SPRITE_RATIO_ORIGINAL(),
            SPRITE_RESIZE_FIT(),                    // SPRITE_RESIZE_T    sprite_resize       = SPRITE_RESIZE_KEEP_ORIGINAL(),
            SPRITE_POS_ALIGN_CENTER(),              // SPRITE_POSITION_T  sprite_h_position   = SPRITE_POS_ALIGN_START(),
            SPRITE_POS_ALIGN_CENTER()               // SPRITE_POSITION_T  sprite_v_position   = SPRITE_POS_ALIGN_START()
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back( this->map_viewer );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                          style
            "Back",                                 // std::string                      text
            nvi(15),                                // VALUE_T                          x
            nvi(15),                                // VALUE_T                          y
            nvi(100),                               // VALUE_T                          w
            nvi(40),                                // VALUE_T                          h
            on_bt_change_page_to_game_settings      // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back( this->map_viewer->rect_current_player );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back( this->map_viewer->txt_current_player );


    //
    this->win_page_manager->pages["in_game"]->elts.push_back( this->map_viewer->elt_province_1 );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back( this->map_viewer->txt_province_treasury );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back( this->map_viewer->elt_province_2 );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back( this->map_viewer->txt_province_expected_income );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back( this->map_viewer->bt_unit_lvl1 );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back( this->map_viewer->txt_unit_lvl1 );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_SPRITE_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "res/ui/gold.png",                      // std::string                      txt
            nvi(57),                                // VALUE_T                           x
            nvi(168),                               // VALUE_T                           y
            nvi(40),                                // VALUE_T                           w
            nvi(40)                                 // VALUE_T                           h
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back( this->map_viewer->bt_unit_lvl2 );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back( this->map_viewer->txt_unit_lvl2 );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_SPRITE_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "res/ui/gold.png",                      // std::string                      txt
            nvi(57),                                // VALUE_T                           x
            nvi(268),                               // VALUE_T                           y
            nvi(40),                                // VALUE_T                           w
            nvi(40)                                 // VALUE_T                           h
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back( this->map_viewer->bt_unit_lvl3 );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back( this->map_viewer->txt_unit_lvl3 );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_SPRITE_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "res/ui/gold.png",                      // std::string                      txt
            nvi(57),                                // VALUE_T                           x
            nvi(368),                               // VALUE_T                           y
            nvi(40),                                // VALUE_T                           w
            nvi(40)                                 // VALUE_T                           h
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back( this->map_viewer->bt_unit_lvl4 );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back( this->map_viewer->txt_unit_lvl4 );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_SPRITE_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "res/ui/gold.png",                      // std::string                      txt
            nvi(57),                                // VALUE_T                           x
            nvi(468),                               // VALUE_T                           y
            nvi(40),                                // VALUE_T                           w
            nvi(40)                                 // VALUE_T                           h
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back( this->map_viewer->bt_building_lvl2 );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back( this->map_viewer->txt_building_lvl2 );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_SPRITE_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "res/ui/gold.png",                      // std::string                      txt
            nvi(57),                                // VALUE_T                           x
            nvi(568),                               // VALUE_T                           y
            nvi(40),                                // VALUE_T                           w
            nvi(40)                                 // VALUE_T                           h
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "end turn",                             // std::string                      text
            nvi(15),                                // VALUE_T                           x
            nvpwh(win_attr, 100, -60),              // VALUE_T                           y
            nvi(200),                               // VALUE_T                           w
            nvi(40),                                // VALUE_T                           h
            on_bt_end_turn                          // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
        )

    );


    //
    for( WINDOW_ELT_T welt : this->map_viewer->elts_end_game ){

        //
        this->win_page_manager->pages["in_game"]->elts.push_back( welt );

    }

}



//
void MainView::init_page_map_creator() {

    //
    WINDOW_ATTRIBUTE_T win_attr = this->get_win_attr();

    //
    this->win_page_manager->pages["map_creator"] = new WindowPage();

    //
    this->win_page_manager->pages["map_creator"]->elts.push_back( this->map_viewer );

    //
    this->win_page_manager->pages["map_creator"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "Back",                                 // std::string                      text
            nvi(15),                                // VALUE_T                           x
            nvi(15),                                // VALUE_T                           y
            nvi(100),                               // VALUE_T                           w
            nvi(40),                                // VALUE_T                           h
            on_bt_change_page_to_game_settings      // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
        )

    );


    //
    this->win_page_manager->pages["map_creator"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "tiles",                                // std::string                      text
            nvi(15),                                // VALUE_T                           x
            nvi(70),                                // VALUE_T                           y
            nvi(70),                                // VALUE_T                           w
            nvi(25),                                // VALUE_T                           h
            on_bt_map_creator_bt_category,          // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
            std::vector<std::string>{"tiles"}
        )

    );


    //
    this->win_page_manager->pages["map_creator"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "colors",                               // std::string                      text
            nvi(90),                                // VALUE_T                           x
            nvi(70),                                // VALUE_T                           y
            nvi(70),                                // VALUE_T                           w
            nvi(25),                                // VALUE_T                           h
            on_bt_map_creator_bt_category,          // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
            std::vector<std::string>{"colors"}        )

    );


    //
    this->win_page_manager->pages["map_creator"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "entities",                             // std::string                      text
            nvi(165),                               // VALUE_T                           x
            nvi(70),                                // VALUE_T                           y
            nvi(70),                                // VALUE_T                           w
            nvi(25),                                // VALUE_T                           h
            on_bt_map_creator_bt_category,          // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
            std::vector<std::string>{"entities"}        )

    );


    //
    this->win_page_manager->pages["map_creator"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "clear",                                // std::string                      text
            nvi(245),                               // VALUE_T                           x
            nvi(70),                                // VALUE_T                           y
            nvi(70),                                // VALUE_T                           w
            nvi(25),                                // VALUE_T                           h
            on_bt_map_creator_clear                 // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
        )

    );


    //
    this->win_page_manager->pages["map_creator"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "generate",                             // std::string                      text
            nvi(320),                               // VALUE_T                           x
            nvi(70),                                // VALUE_T                           y
            nvi(140),                                // VALUE_T                           w
            nvi(25),                                // VALUE_T                           h
            on_bt_map_creator_generate              // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
        )

    );

    //
    int t = 40;

    //
    // TILES
    //
    for(int i = 0; i < 70; i++){

        //
        std::string tile_img = "res/sprites/map_w/" + std::string(allTileData[i].img_preview);

        //
        if( tile_img == ""){ continue; }

        //
        this->win_page_manager->pages["map_creator"]->elts.push_back(

            //
            CREATE_WINDOW_ELT_BUTTON_T(
                this->win_page_manager->default_style,  // STYLE_T                           style
                tile_img,                               // std::string                      text
                nvi(15 + (int)(i / 10) * (t + 5)),      // VALUE_T                           x
                nvi(100 + (i % 10) * (t+5)),            // VALUE_T                           y
                nvi(t),                                 // VALUE_T                           w
                nvi(t),                                 // VALUE_T                           h
                on_bt_map_creator_tile,                 // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
                (std::vector<std::string>){ std::to_string(i) }
            )

        );
    }

    //
    // colors
    //
    for(int i = 0; i < 10; i++){

        //
        this->win_page_manager->pages["map_creator"]->elts.push_back(

            //
            CREATE_WINDOW_ELT_BUTTON_T(
                this->win_page_manager->default_style,  // STYLE_T                           style
                std::to_string(i+1),                    // std::string                      text
                nvi(15),                                // VALUE_T                           x
                nvi(100 + i * (t+5)),                   // VALUE_T                           y
                nvi(t),                                 // VALUE_T                           w
                nvi(t),                                 // VALUE_T                           h
                on_bt_map_creator_color,                // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
                (std::vector<std::string>){ std::to_string(i+1) }                                 // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
            )

        );
    }

    //
    // Entities
    //

    this->win_page_manager->pages["map_creator"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "res/sprites/entities/bandit2_p.png",   // std::string                      text
            nvi(15),                                // VALUE_T                           x
            nvi(100 + 0 * (t+5)),                   // VALUE_T                           y
            nvi(t),                                 // VALUE_T                           w
            nvi(t),                                 // VALUE_T                           h
            on_bt_map_creator_entity,               // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
            (std::vector<std::string>){ "10" }
        )

    );

    this->win_page_manager->pages["map_creator"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "res/sprites/entities/cat_lvl1_p.png",  // std::string                      text
            nvi(15),                                // VALUE_T                           x
            nvi(100 + 1 * (t+5)),                   // VALUE_T                           y
            nvi(t),                                 // VALUE_T                           w
            nvi(t),                                 // VALUE_T                           h
            on_bt_map_creator_entity,               // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
            (std::vector<std::string>){ "11" }
        )

    );

    this->win_page_manager->pages["map_creator"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "res/sprites/entities/cat_lvl2_p.png",  // std::string                      text
            nvi(15),                                // VALUE_T                           x
            nvi(100 + 2 * (t+5)),                   // VALUE_T                           y
            nvi(t),                                 // VALUE_T                           w
            nvi(t),                                 // VALUE_T                           h
            on_bt_map_creator_entity,               // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
            (std::vector<std::string>){ "12" }
        )

    );

    this->win_page_manager->pages["map_creator"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "res/sprites/entities/cat_lvl3_p.png",  // std::string                      text
            nvi(15),                                // VALUE_T                           x
            nvi(100 + 3 * (t+5)),                   // VALUE_T                           y
            nvi(t),                                 // VALUE_T                           w
            nvi(t),                                 // VALUE_T                           h
            on_bt_map_creator_entity,               // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
            (std::vector<std::string>){ "13" }
        )

    );

    this->win_page_manager->pages["map_creator"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "res/sprites/entities/cat_lvl4_p.png",  // std::string                      text
            nvi(15),                                // VALUE_T                           x
            nvi(100 + 4 * (t+5)),                   // VALUE_T                           y
            nvi(t),                                 // VALUE_T                           w
            nvi(t),                                 // VALUE_T                           h
            on_bt_map_creator_entity,               // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
            (std::vector<std::string>){ "14" }
        )

    );

    this->win_page_manager->pages["map_creator"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "res/sprites/entities/bandit_camp2_p.png",  // std::string                      text
            nvi(15 + 1 * (t+5)),                    // VALUE_T                           x
            nvi(100 + 0 * (t+5)),                   // VALUE_T                           y
            nvi(t),                                 // VALUE_T                           w
            nvi(t),                                 // VALUE_T                           h
            on_bt_map_creator_entity,               // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
            (std::vector<std::string>){ "00" }
        )

    );

    this->win_page_manager->pages["map_creator"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "res/sprites/entities/village2_p.png",  // std::string                      text
            nvi(15 + 1 * (t+5)),                    // VALUE_T                           x
            nvi(100 + 1 * (t+5)),                   // VALUE_T                           y
            nvi(t),                                 // VALUE_T                           w
            nvi(t),                                 // VALUE_T                           h
            on_bt_map_creator_entity,               // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
            (std::vector<std::string>){ "01" }
        )

    );

    this->win_page_manager->pages["map_creator"]->elts.push_back(

        //
        CREATE_WINDOW_ELT_BUTTON_T(
            this->win_page_manager->default_style,  // STYLE_T                           style
            "res/sprites/entities/tower2_p.png",  // std::string                      text
            nvi(15 + 1 * (t+5)),                    // VALUE_T                           x
            nvi(100 + 2 * (t+5)),                   // VALUE_T                           y
            nvi(t),                                 // VALUE_T                           w
            nvi(t),                                 // VALUE_T                           h
            on_bt_map_creator_entity,               // std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)>    on_click
            (std::vector<std::string>){ "02" }
        )

    );

}



// Init Pages
void MainView::init_window_pages() {

    //
    this->win_page_manager = new WindowPagesManager();

    //
    this->init_page_main_menu();

    //
    this->init_page_game_settings();

    //
    this->init_page_in_game();

    //
    this->init_page_map_creator();

    //
    this->win_page_manager->current_page = "main_menu";

}




// Draw Main Menu
void MainView::display_menu_main(){}


// Draw Game Settings Menu
void MainView::display_menu_game_settings(){}


// Draw In Game
void MainView::display_menu_in_game(){}


// Draw In Game
void MainView::display_menu_map_creator(){}


// Update Game Settings Menu Before Displaying it
void MainView::update_menu_game_settings(MainGame* main_game, bool update_all_maps){

    //
    WINDOW_ELT_BUTTON_T bt = DCAST_WINDOW_ELT_BUTTON_T( this->win_page_manager->pages["game_settings"]->elts[3] );

    //
    if( bt == nullptr ){ return; }

    //
    bt->disabled = !check_file_exists("maps/saved_data/saved_map.kkmap");

    //
    std::vector<WINDOW_ELT_T>* v = &(this->win_page_manager->pages["game_settings"]->elts);

    //
    if( !update_all_maps ){ return; }

    //
    v->erase(v->begin() + 8, v->end());

    //
    int i = -1;
    //
    for( std::string map_file : main_game->all_detected_map_files ){

        //
        i++;

        //
        v->push_back(

            CREATE_WINDOW_ELT_BUTTON_T(
                bt->style,
                map_file.substr(5, map_file.size() - 11),
                bt->x,
                nvi(380 + 75 * i),
                bt->w,
                bt->h,
                on_bt_play_map,
                (std::vector<std::string>){map_file}
            )

        );

    }

}

