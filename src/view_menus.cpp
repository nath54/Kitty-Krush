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



//
const char* FONT_PATH = "res/fonts/blinky_star/BlinkyStar.otf";
//
const char* TEXT = "UwU";
const int BASE_FONT_SIZE = 50;
const int AMPLITUDE = 20;
const float FREQUENCY = 2.0f;
const float FREQUENCY2 = 0.1;



// Draw Main Menu
void MainView::display_menu_main(){



}




// Draw Game Settings Menu
void MainView::display_menu_game_settings(){


}





// Draw In Game
void MainView::display_menu_in_game(){


    //
    float time = (SDL_GetTicks() - this->startTime) / 1000.0f;
    int fontSize = BASE_FONT_SIZE + AMPLITUDE * sin(FREQUENCY * time);
    Color color = Color(
        (int)(255 * sin(FREQUENCY2 * time)),
        128,
        (int)(255 - 128 * sin(FREQUENCY2 * time))
    );
    //
    this->render_text(TEXT, color, fontSize, FONT_PATH);



}

