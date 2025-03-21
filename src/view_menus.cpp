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




// Init Pages
void MainView::init_window_pages() {

    //
    WindowAttributes* win_attr = this->get_win_attr();

    //
    Style* default_style = new Style();

    //
    this->win_page_manager = new WindowPagesManager();

    // Create Main Menu
    this->win_page_manager->pages["main_menu"] = new WindowPage();

    //
    this->win_page_manager->pages["main_menu"]->elts.push_back(

        //
        new WindowEltSprite(
            default_style,                      // Style*           style,
            "res/bgs/bg_main_menu.png",         // std::string      img_path,
            nvi(0),                             // Value*           x,
            new ValueInt(0),                    // Value*           y,
            nvpww(100, win_attr),               // Value*           w,
            nvpwh(100, win_attr),               // Value*           h,
            nvi(0),                             // Value*           angle               = new ValueInt(0),
            false,                              // bool             flip_h              = false,
            false,                              // bool             flip_v              = false,
            SPRITE_NO_CROP(),                   // SpriteCrop*      sprite_crop         = SPRITE_NO_CROP(),
            SPRITE_RATIO_ORIGINAL(),            // SpriteRatio*     sprite_ratio        = SPRITE_RATIO_ORIGINAL(),
            SPRITE_RESIZE_KEEP_ORIGINAL(),      // SpriteResize*    sprite_resize       = SPRITE_RESIZE_KEEP_ORIGINAL(),
            SPRITE_POS_ALIGN_CENTER(),          // SpritePosition*  sprite_h_position   = SPRITE_POS_ALIGN_START(),
            SPRITE_POS_ALIGN_START()            // SpritePosition*  sprite_v_position   = SPRITE_POS_ALIGN_START()

        )

    );

    //
    this->win_page_manager->pages["main_menu"]->elts.push_back(

        //
        new WindowEltButton(
            default_style,                      // Style*           style
            "Play !",                           // std::string      text
            nvpww(35, win_attr),                // Value*           x
            nvpwh(50, win_attr),                // Value*           y
            nvpww(30, win_attr),                // Value*           w
            nvi(100)                            // Value*           h
        )

    );

    //
    this->win_page_manager->pages["game_settings"] = new WindowPage();

    //
    this->win_page_manager->pages["in_game"] = new WindowPage();

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

