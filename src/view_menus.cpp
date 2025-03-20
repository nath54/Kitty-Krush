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
    Style* default_style = new Style();

    //
    this->win_page_manager = new WindowPagesManager();

    // Create Main Menu
    this->win_page_manager->pages["main_menu"] = new WindowPage();

    //
    this->win_page_manager->pages["main_menu"]->elts.push_back(

        //
        new WindowEltSprite(
            default_style,                                          // Style*       style,
            "res/bgs/bg_main_menu.png",                             // std::string  img_path,
            new ValueInt(0),                                        // Value*       x,
            new ValueInt(0),                                        // Value*       y,
            new ValuePercentWinWidth(100, this->get_win_attr()),    // Value*       w,
            new ValuePercentWinHeight(100, this->get_win_attr()),   // Value*       h,
            new ValueInt(0),                                        // Value*       angle           = new ValueInt(0),
            false,                                                  // bool         flip_h          = false,
            false,                                                  // bool         flip_v          = false,
            LayoutMode::FIT,                                      // LayoutMode   layout_mode     = LayoutMode::FIT,
            CropMode::NO_CROP,                                      // CropMode     crop_mode       = CropMode::NO_CROP,
            1.0f,                                                   // float        custom_scale    = 1.0f,
            0,                                                      // int          custom_crop_x   = 0,
            0,                                                      // int          custom_crop_y   = 0,
            0,                                                      // int          custom_crop_w   = 0,
            0                                                       // int          custom_crop_h   = 0
        )

    );

    //
    this->win_page_manager->pages["main_menu"]->elts.push_back(

        //
        new WindowEltButton(
            default_style,
            "Play !",
            new ValuePercentWinWidth(40, this->get_win_attr()),
            new ValuePercentWinHeight(30, this->get_win_attr()),
            new ValuePercentWinWidth(20, this->get_win_attr()),
            new ValueInt(60)
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

