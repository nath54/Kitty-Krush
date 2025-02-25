//
#pragma once
//
#include <SDL.h>
#include <iostream>
#include <cstdio>
//
#include <model.hpp>

//
static const int WIN_SIZE_WIDTH = 900;
static const int WIN_SIZE_HEIGHT = 700;
//
static char SDL_ERROR_BUFFER[1000];


// Class MainView, manages the SDL environment & SDL Window
class MainView{

    // Private attributes & functions
    private:

        // SDL related attributes
        SDL_Window* sdl_window = nullptr;
        SDL_Surface* sdl_window_surface = nullptr;
        SDL_Renderer* sdl_renderer = nullptr;

        // Reference to game_model
        GameModel* game_model = nullptr;

        // Clean quit program while displaying the sdl error
        void sdl_error(const char* error_msg);

        // Destroy all the SDL variable created here inside
        void destroy_all_created();


    // Public attributes & functions
    public:

        // Constructor
        MainView(GameModel* game_model);

        // Destructor
        ~MainView();

        // Main update display method
        void update_display();

};


