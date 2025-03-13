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




// Init Pages
void MainView::init_window_pages(){

    //
    Style default_style = Style();

    //
    std::map<std::string, WindowPage> pages = {

        {
            // Window Page "main_menu"

            "main_menu", {
                // Elts vector
                {
                    WindowEltButton(
                        &default_style, // style
                        "Play !",       // text
                        ValuePercentWinWidth(40, this->get_win_attr()), // x
                        ValuePercentWinHeight(30, this->get_win_attr()), // y
                        ValuePercentWinWidth(20, this->get_win_attr()), // w
                        ValueInt(40)  // h
                    )
                }
            },

        },

        {
            // Window Page game settings

            "game_settings", {
                // Elts vector
                {}
            },

        },

        {
            // Window Page in game

            "in_game", {
                // Elts vector
                {}
            }
        }
    };
    std::string current_page = "main_menu";

    //
    this->win_page_manager = new WindowPagesManager(pages, current_page);

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

