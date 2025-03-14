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
    Style default_style = Style();

    //
    this->win_page_manager = new WindowPagesManager();

    // Create Main Menu
    this->win_page_manager->pages["main_menu"] = new WindowPage();

    this->win_page_manager->pages["main_menu"]->elts.push_back(

        //
        new WindowEltButton(
            &default_style,
            "Play !",
            new ValuePercentWinWidth(40, this->get_win_attr()),
            new ValuePercentWinHeight(30, this->get_win_attr()),
            new ValuePercentWinWidth(20, this->get_win_attr()),
            new ValueInt(40)
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

