//
#include "view.hpp"
#include "color.hpp"
//
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
//
#include <iostream>
#include <string>
#include <cmath>
#include <unistd.h>


// Constructor
MainView::MainView(GameModel* game_model)
    : game_model(game_model)  // Automatic initialization of the attribute
{

    // Init SDL & Error Check
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        sprintf(SDL_ERROR_BUFFER, "SDL_Init Error: %s", SDL_GetError());
        this->sdl_error(SDL_ERROR_BUFFER);
    }
    this->sdl_initialized = true;

    //
    if (TTF_Init() == -1) {
        sprintf(SDL_ERROR_BUFFER, "TTF_Init Error: %s", TTF_GetError());
        this->sdl_error(SDL_ERROR_BUFFER);
    }
    this->ttf_initialized = true;

    // Window creation
    this->sdl_window = SDL_CreateWindow(
                                        "Kitty Krush !",
                                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        WIN_SIZE_WIDTH_INIT, WIN_SIZE_HEIGHT_INIT,
                                        SDL_WINDOW_SHOWN
    );

    // Set window size
    this->win_attr.win_width = WIN_SIZE_WIDTH_INIT;
    this->win_attr.win_height = WIN_SIZE_HEIGHT_INIT;


    // Verify window creation
    if(!this->sdl_window){
        sprintf(SDL_ERROR_BUFFER, "SDL_CreateWindow Error: %s", SDL_GetError());
        this->sdl_error(SDL_ERROR_BUFFER);
    }

    // Create renderer with vsync to limit frame rate
    this->sdl_renderer = SDL_CreateRenderer(this->sdl_window, -1,
                                            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Verify renderer
    if (!this->sdl_renderer) {
        sprintf(SDL_ERROR_BUFFER, "SDL_CreateRenderer Error: %s", SDL_GetError());
        this->sdl_error(SDL_ERROR_BUFFER);
    }

    // Get the window surface
    this->sdl_window_surface = SDL_GetWindowSurface(this->sdl_window);

    // Verify the window surface
    if (!this->sdl_window_surface) {
        sprintf(SDL_ERROR_BUFFER, "SDL_GetWindowSurface Error: %s", SDL_GetError());
        this->sdl_error(SDL_ERROR_BUFFER);
    }

    //
    this->startTime = SDL_GetTicks();

    //
    this->update_display(0);

    //
    std::cout << "SDL Initialized & Window created !\n/ᐠ > ˕ <マ ₊˚⊹♡\n";

}

// Destructor
MainView::~MainView(){
    //
    this->destroy_all_created();
    //
    TTF_Quit();
    //
    SDL_Quit();
}

//
void MainView::update_mouse_state(){

    // Get mouse position
    uint32_t mouse_state = SDL_GetGlobalMouseState( &(this->win_attr.mouse_x), &(this->win_attr.mouse_y) );

    // Update from window position
    this->win_attr.mouse_x -= this->win_attr.win_x;
    this->win_attr.mouse_y -= this->win_attr.win_y;

}


// Main update display method
void MainView::update_display(int menu_state){

    // Get window position
    SDL_GetWindowPosition(this->sdl_window, &(this->win_attr.win_x), &(this->win_attr.win_y));

    // Get window size
    SDL_GetWindowSize(this->sdl_window, &(this->win_attr.win_width), &(this->win_attr.win_height));

    // Get mouse position
    this->update_mouse_state();

    // Clean screen
    SDL_SetRenderDrawColor(this->sdl_renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->sdl_renderer);

    //
    switch (menu_state){

        //
        case 0:     // Main Menu

            //
            this->display_menu_main();
            break;

        //
        case 1:     // Game Settings

            //
            this->display_menu_game_settings();
            break;

        //
        case 2:     // In Game

            //
            this->display_menu_in_game();
            break;

        //
        default:

            //
            std::cerr << "Error : Unkown Menu State - " << menu_state << "\n";

    }

    //
    if(this->win_page_manager != nullptr){
        this->win_page_manager->draw_current_page( this );
    }

    // 💡 Update the renderer to show the new frame
    SDL_RenderPresent(this->sdl_renderer);
}



WindowAttributes* MainView::get_win_attr(){
    return &(this->win_attr);
}

