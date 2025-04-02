//
#include "view.hpp"
#include "color.hpp"
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
void on_bt_quit_click(MainView* main_view) {

    //
    // pass

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
            "res/bgs/bg_main_menu.png",             // std::string      img_path,
            nvi(0),                                 // Value*           x,
            new ValueInt(0),                        // Value*           y,
            nvpww(100, win_attr),                   // Value*           w,
            nvpwh(100, win_attr),                   // Value*           h,
            nvi(0),                                 // Value*           angle               = new ValueInt(0),
            false,                                  // bool             flip_h              = false,
            false,                                  // bool             flip_v              = false,
            SPRITE_NO_CROP(),                       // SpriteCrop*      sprite_crop         = SPRITE_NO_CROP(),
            // SPRITE_RATIO_CUSTOM(1, 1),              // SpriteRatio*     sprite_ratio        = SPRITE_RATIO_ORIGINAL(),
            SPRITE_RATIO_ORIGINAL(),                // SpriteRatio*     sprite_ratio        = SPRITE_RATIO_ORIGINAL(),
            SPRITE_RESIZE_FIT(),                    // SpriteResize*    sprite_resize       = SPRITE_RESIZE_KEEP_ORIGINAL(),
            SPRITE_POS_ALIGN_CENTER(),              // SpritePosition*  sprite_h_position   = SPRITE_POS_ALIGN_START(),
            SPRITE_POS_ALIGN_START()                // SpritePosition*  sprite_v_position   = SPRITE_POS_ALIGN_START()
        )

    );

    //
    this->win_page_manager->pages["main_menu"]->elts.push_back(

        //
        new WindowEltButton(
            this->win_page_manager->default_style,  // Style*                           style
            "Play !",                               // std::string                      text
            nvpww(35, win_attr),                    // Value*                           x
            nvpwh(50, win_attr),                    // Value*                           y
            nvpww(30, win_attr),                    // Value*                           w
            nvi(100),                               // Value*                           h
            nullptr                                 // std::function<void(MainView*)    on_click
        )

    );

    //
    this->win_page_manager->pages["main_menu"]->elts.push_back(

        //
        new WindowEltButton(
            this->win_page_manager->default_style,  // Style*                           style
            "Quit...",                              // std::string                      text
            nvpww(40, win_attr),                    // Value*                           x
            nvpwh(75, win_attr),                    // Value*                           y
            nvpww(20, win_attr),                    // Value*                           w
            nvi(40),                                // Value*                           h
            nullptr                                 // std::function<void(MainView*)    on_click
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
            nvpww(35, win_attr),                    // Value*                           x
            nvpwh(50, win_attr),                    // Value*                           y
            nvi(200),                               // Value*                           w
            nvi(40),                                // Value*                           h
            nullptr                                 // std::function<void(MainView*)    on_click
        )

    );
}



//
void MainView::init_page_in_game() {

    //
    WindowAttributes* win_attr = this->get_win_attr();

    //
    this->win_page_manager->pages["in_game"] = new WindowPage();

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

