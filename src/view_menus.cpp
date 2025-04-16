//
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
#include "entity_data.hpp"




//
void on_bt_quit_click(WindowEltClickable* elt, MainGame* main_game) {

    //
    main_game->quit();

}


//
void on_bt_change_page_to_main_menu(WindowEltClickable* elt, MainGame* main_game) {

    //
    main_game->change_page("main_menu");
}


//
void on_bt_change_page_to_game_settings(WindowEltClickable* elt, MainGame* main_game) {

    //
    main_game->change_page("game_settings");
}


//
void on_bt_change_page_to_in_game(WindowEltClickable* elt, MainGame* main_game) {

    //
    main_game->change_page("in_game");
}


//
void set_new_entity_dragged(MainGame* main_game, int level, bool type){

    //
    WindowEltMapViewer* map_viewer = main_game->main_view->map_viewer;

    //
    if(map_viewer == nullptr){ return; }

    //
    map_viewer->dragging_entity = true;
    map_viewer->dragging_new_entity = true;
    map_viewer->entity_dragged.level = level;
    map_viewer->entity_dragged.type = type;

    //
    main_game->update_where_entity_can_move((Coord){0, 0}, true);

}


//
void on_bt_new_warrior_lvl1(WindowEltClickable* elt, MainGame* main_game) {
    //
    set_new_entity_dragged(main_game, 1, true);
}


//
void on_bt_new_warrior_lvl2(WindowEltClickable* elt, MainGame* main_game) {
    //
    set_new_entity_dragged(main_game, 2, true);
}


//
void on_bt_new_warrior_lvl3(WindowEltClickable* elt, MainGame* main_game) {
    //
    set_new_entity_dragged(main_game, 3, true);
}


//
void on_bt_new_warrior_lvl4(WindowEltClickable* elt, MainGame* main_game) {
    //
    set_new_entity_dragged(main_game, 4, true);
}


//
void on_bt_new_tower(WindowEltClickable* elt, MainGame* main_game) {
    //
    set_new_entity_dragged(main_game, 2, false);
}


//
void on_bt_end_turn(WindowEltClickable* elt, MainGame* main_game) {
    //
    main_game->action_end_turn();
}



//
void MainView::init_page_main_menu() {

    //
    WindowAttributes* win_attr = this->get_win_attr();

    // Create Main Menu
    this->win_page_manager->pages["main_menu"] = new WindowPage();

    //
    this->win_page_manager->pages["main_menu"]->elts.push_back(

        //
        new WindowEltSprite(
            this->win_page_manager->default_style,  // Style*           style,
            "res/bgs/bg_main_menu_2.png",           // std::string      img_path,
            nvi(0),                                 // Value*           x,
            new ValueInt(0),                        // Value*           y,
            nvpww(win_attr, 100),                   // Value*           w,
            nvpwh(win_attr, 100),                   // Value*           h,
            nvi(0),                                 // Value*           angle               = new ValueInt(0),
            false,                                  // bool             flip_h              = false,
            false,                                  // bool             flip_v              = false,
            SPRITE_NO_CROP(),                       // SpriteCrop*      sprite_crop         = SPRITE_NO_CROP(),
            // SPRITE_RATIO_CUSTOM(1, 1),           // SpriteRatio*     sprite_ratio        = SPRITE_RATIO_ORIGINAL(),
            SPRITE_RATIO_ORIGINAL(),                // SpriteRatio*     sprite_ratio        = SPRITE_RATIO_ORIGINAL(),
            SPRITE_RESIZE_FIT(1.9),                 // SpriteResize*    sprite_resize       = SPRITE_RESIZE_KEEP_ORIGINAL(),
            SPRITE_POS_ALIGN_CENTER(),              // SpritePosition*  sprite_h_position   = SPRITE_POS_ALIGN_START(),
            SPRITE_POS_ALIGN_CENTER()               // SpritePosition*  sprite_v_position   = SPRITE_POS_ALIGN_START()
        )

    );


    //
    this->win_page_manager->pages["main_menu"]->elts.push_back(

        //
        new WindowEltButton(
            this->win_page_manager->default_style,  // Style*                           style
            "Play !",                               // std::string                      text
            nvpww(win_attr, 35),                    // Value*                           x
            nvpwh(win_attr, 45),                    // Value*                           y
            nvpww(win_attr, 30),                    // Value*                           w
            nvi(100),                               // Value*                           h
            on_bt_change_page_to_in_game            // std::function<void(WindowEltClickable*, MainGame*)>    on_click
        )

    );

    //
    this->win_page_manager->pages["main_menu"]->elts.push_back(

        //
        new WindowEltButton(
            this->win_page_manager->default_style,  // Style*                           style
            "Quit...",                              // std::string                      text
            nvpww(win_attr, 40),                    // Value*                           x
            nvpwh(win_attr, 65),                    // Value*                           y
            nvpww(win_attr, 20),                    // Value*                           w
            nvi(40),                                // Value*                           h
            on_bt_quit_click                        // std::function<void(WindowEltClickable*, MainGame*)>    on_click
        )

    );

}



//
void MainView::init_page_game_settings() {

    //
    WindowAttributes* win_attr = this->get_win_attr();

    //
    this->win_page_manager->pages["game_settings"] = new WindowPage();

    //
    this->win_page_manager->pages["game_settings"]->elts.push_back(

        //
        new WindowEltButton(
            this->win_page_manager->default_style,  // Style*                           style
            "Back",                                 // std::string                      text
            nvi(15),                                // Value*                           x
            nvi(15),                                // Value*                           y
            nvi(200),                               // Value*                           w
            nvi(40),                                // Value*                           h
            on_bt_change_page_to_main_menu          // std::function<void(WindowEltClickable*, MainGame*)>    on_click
        )

    );
}



//
void MainView::init_page_in_game() {

    //
    WindowAttributes* win_attr = this->get_win_attr();

    //
    this->win_page_manager->pages["in_game"] = new WindowPage();

    //
    this->map_viewer = new WindowEltMapViewer(
        this->win_page_manager->default_style,  // Style*                           style
        nvi(0),                                 // Value*                           x
        nvi(0),                                 // Value*                           y
        nvpww(win_attr, 100),                   // Value*                           w
        nvpwh(win_attr, 100),                   // Value*                           h
        on_map_viewer_click                     // std::function<void(WindowEltClickable*, MainGame*)>  on_click
    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back( this->map_viewer );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        new WindowEltButton(
            this->win_page_manager->default_style,  // Style*                           style
            "Back",                                 // std::string                      text
            nvi(15),                                // Value*                           x
            nvi(15),                                // Value*                           y
            nvi(100),                               // Value*                           w
            nvi(40),                                // Value*                           h
            on_bt_change_page_to_main_menu          // std::function<void(WindowEltClickable*, MainGame*)>    on_click
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        new WindowEltRect(
            this->win_page_manager->default_style,  // Style*                           style
            (Color){150, 150, 150},                 // Color                            cl
            nvpww(win_attr, 40),                    // Value*                           x
            nvi(15),                                // Value*                           y
            nvpww(win_attr, 20),                    // Value*                           w
            nvi(40),                                // Value*                           h
            nvi(15)                                 // Value*                           radius
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        new WindowEltText(
            this->win_page_manager->default_style,  // Style*                           style
            "player 1",                             // std::string                      txt
            nvpww(win_attr, 40),                    // Value*                           x
            nvi(15),                                // Value*                           y
            nvpww(win_attr, 20),                    // Value*                           w
            nvi(40)                                 // Value*                           h
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        new WindowEltButton(
            this->win_page_manager->default_style,  // Style*                           style
            "res/sprites/entities/cat_lvl1_p.png",  // std::string                      text
            nvi(15),                                // Value*                           x
            nvi(100),                               // Value*                           y
            nvi(60),                                // Value*                           w
            nvi(60),                                // Value*                           h
            on_bt_new_warrior_lvl1                  // std::function<void(WindowEltClickable*, MainGame*)>    on_click
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        new WindowEltText(
            this->win_page_manager->default_style,  // Style*                           style
            std::to_string(units_new_costs[1]),     // std::string                      txt
            nvi(15),                                // Value*                           x
            nvi(165),                               // Value*                           y
            nvi(60),                                // Value*                           w
            nvi(20)                                 // Value*                           h
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        new WindowEltButton(
            this->win_page_manager->default_style,  // Style*                           style
            "res/sprites/entities/cat_lvl2_p.png",  // std::string                      text
            nvi(15),                                // Value*                           x
            nvi(200),                               // Value*                           y
            nvi(60),                                // Value*                           w
            nvi(60),                                // Value*                           h
            on_bt_new_warrior_lvl2                  // std::function<void(WindowEltClickable*, MainGame*)>    on_click
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        new WindowEltText(
            this->win_page_manager->default_style,  // Style*                           style
            std::to_string(units_new_costs[2]),     // std::string                      txt
            nvi(15),                                // Value*                           x
            nvi(265),                               // Value*                           y
            nvi(60),                                // Value*                           w
            nvi(20)                                 // Value*                           h
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        new WindowEltButton(
            this->win_page_manager->default_style,  // Style*                           style
            "res/sprites/entities/cat_lvl3_p.png",  // std::string                      text
            nvi(15),                                // Value*                           x
            nvi(300),                               // Value*                           y
            nvi(60),                                // Value*                           w
            nvi(60),                                // Value*                           h
            on_bt_new_warrior_lvl3                  // std::function<void(WindowEltClickable*, MainGame*)>    on_click
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        new WindowEltText(
            this->win_page_manager->default_style,  // Style*                           style
            std::to_string(units_new_costs[3]),     // std::string                      txt
            nvi(15),                                // Value*                           x
            nvi(365),                               // Value*                           y
            nvi(60),                                // Value*                           w
            nvi(20)                                 // Value*                           h
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        new WindowEltButton(
            this->win_page_manager->default_style,  // Style*                           style
            "res/sprites/entities/cat_lvl4_p.png",  // std::string                      text
            nvi(15),                                // Value*                           x
            nvi(400),                               // Value*                           y
            nvi(60),                                // Value*                           w
            nvi(60),                                // Value*                           h
            on_bt_new_warrior_lvl4                  // std::function<void(WindowEltClickable*, MainGame*)>    on_click
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        new WindowEltText(
            this->win_page_manager->default_style,  // Style*                           style
            std::to_string(units_new_costs[4]),     // std::string                      txt
            nvi(15),                                // Value*                           x
            nvi(465),                               // Value*                           y
            nvi(60),                                // Value*                           w
            nvi(20)                                 // Value*                           h
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        new WindowEltButton(
            this->win_page_manager->default_style,  // Style*                           style
            "res/sprites/entities/tower_p.png",     // std::string                      text
            nvi(15),                                // Value*                           x
            nvi(500),                               // Value*                           y
            nvi(60),                                // Value*                           w
            nvi(60),                                // Value*                           h
            on_bt_new_tower                         // std::function<void(WindowEltClickable*, MainGame*)>    on_click
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        new WindowEltText(
            this->win_page_manager->default_style,  // Style*                           style
            std::to_string(buildings_new_costs[2]), // std::string                      txt
            nvi(15),                                // Value*                           x
            nvi(565),                               // Value*                           y
            nvi(60),                                // Value*                           w
            nvi(20)                                 // Value*                           h
        )

    );

    //
    this->win_page_manager->pages["in_game"]->elts.push_back(

        //
        new WindowEltButton(
            this->win_page_manager->default_style,  // Style*                           style
            "end turn",                             // std::string                      text
            nvi(15),                                // Value*                           x
            nvpwh(win_attr, 100, -60),              // Value*                           y
            nvi(200),                               // Value*                           w
            nvi(40),                                // Value*                           h
            on_bt_end_turn                          // std::function<void(WindowEltClickable*, MainGame*)>    on_click
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
    this->win_page_manager->current_page = "main_menu";

}




// Draw Main Menu
void MainView::display_menu_main(){

}


// Draw Game Settings Menu
void MainView::display_menu_game_settings(){


}


// Draw In Game
void MainView::display_menu_in_game(){

}

