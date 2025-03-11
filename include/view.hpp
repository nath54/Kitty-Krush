//
#pragma once
//
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cstdio>
#include <map>
#include <string>
//
#include <stdint.h>
//
#include "color.hpp"
#include "model.hpp"

//
static const int WIN_SIZE_WIDTH_INIT = 900;
static const int WIN_SIZE_HEIGHT_INIT = 700;
//
static char SDL_ERROR_BUFFER[1000];


// Class MainView, manages the SDL environment & SDL Window
class MainView{

    // Private attributes & functions
    private:

        //
        bool sdl_initialized = false;
        bool ttf_initialized = false;

        //
        uint32_t startTime = 0;

        // Window related attributes
        int win_x = 0;
        int win_y = 0;
        int win_width = WIN_SIZE_WIDTH_INIT;
        int win_height = WIN_SIZE_HEIGHT_INIT;

        // SDL related attributes
        SDL_Window* sdl_window = nullptr;
        SDL_Surface* sdl_window_surface = nullptr;
        SDL_Renderer* sdl_renderer = nullptr;

        // Mouse position & mouse buttons states
        int mouse_x = 0;
        int mouse_y = 0;
        bool mouse_bt_left = false;
        bool mouse_bt_right = false;

        // Font path
        const char* font_path = "res/fonts/blinky_star/BlinkyStar.otf";

        // SDL ttf related attributes
        map<int, TTF_Font*> ttf_fonts;

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
        void update_display(int menu_state);

        // Get mouse position & buttons states
        void update_mouse_state();

        // Draw Main Menu
        void display_menu_main();

        // Draw Game Settings Menu
        void display_menu_game_settings();

        // Draw In Game
        void display_menu_in_game();

        // Get font
        TTF_Font* get_font(int fontSize);

        // Render text function
        void draw_text(std::string text, Color cl, int fontSize, int x, int y, int w = -1, int h = -1);

        //
        void draw_rounded_rect(int x, int y, int w, int h, int r, Color color);

        //
        void draw_button_1(int x, int y, int w, int h, std::string text, int fontSize, int r = 20);

};
