//
#include "view.hpp"
#include "color.hpp"
//
#include <SDL.h>
#include <SDL_ttf.h>
//
#include <iostream>
#include <string>
#include <cmath>
#include <unistd.h>


//
const char* FONT_PATH = "res/fonts/blinky_star/BlinkyStar.otf";
const char* TEXT = "UwU";
const int BASE_FONT_SIZE = 50;
const int AMPLITUDE = 20;
const float FREQUENCY = 2.0f;
const float FREQUENCY2 = 0.1;


//
void MainView::sdl_error(const char* error_msg){

    // Display & log error message
    SDL_Log( error_msg );

    // Destroy all the allocated SDL memory for a clean exit
    this->destroy_all_created();

    // Quit TTF
    if(this->ttf_initialized){ TTF_Quit(); }

    // Quit SDL then the program
    if(this->sdl_initialized){ SDL_Quit(); }
    //
    exit(1);
}


//
void MainView::destroy_all_created(){

    // Destroy the sdl window surface
    if(this->sdl_window_surface != nullptr){
        this->sdl_window_surface = nullptr;
    }

    // Destroy the sdl renderer
    if(this->sdl_renderer != nullptr){
        SDL_DestroyRenderer(this->sdl_renderer);
        this->sdl_renderer = nullptr;
    }

    // Destroy the sdl window
    if(this->sdl_window != nullptr){
        SDL_DestroyWindow(this->sdl_window);
        this->sdl_window = nullptr;
    }
}


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
                                        "The Game",
                                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        WIN_SIZE_WIDTH, WIN_SIZE_HEIGHT,
                                        SDL_WINDOW_SHOWN
    );
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
    this->update_display();

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


// Main update display method
void MainView::update_display(){

    // Clean screen
    SDL_SetRenderDrawColor(this->sdl_renderer, 0, 0, 0, 255);
    SDL_RenderClear(this->sdl_renderer);

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

    // 💡 Update the renderer to show the new frame
    SDL_RenderPresent(this->sdl_renderer);
}


// Render text function
void MainView::render_text(std::string text, Color cl, int fontSize, std::string font_path) {

    //
    TTF_Font* dynamicFont = TTF_OpenFont(font_path.c_str(), fontSize);
    if (!dynamicFont) {
        sprintf(SDL_ERROR_BUFFER, "Failed to load font! TTF_OpenFont Error: %s", TTF_GetError());
        this->sdl_error(SDL_ERROR_BUFFER);
    }

    //
    SDL_Color color = {cl.r, cl.g, cl.b, cl.a};
    // SDL_Surface* surface = TTF_RenderText_Solid(dynamicFont, text.c_str(), color);     // No anti-aliasing (blocky text).
    // SDL_Surface* surface = TTF_RenderText_Shaded(dynamicFont, text.c_str(), color);     // Anti-aliasing with background color.
    SDL_Surface* surface = TTF_RenderText_Blended(dynamicFont, text.c_str(), color);     // Best anti-aliasing, recommended for smooth text.
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->sdl_renderer, surface);

    //
    int textWidth = surface->w;
    int textHeight = surface->h;
    SDL_Rect destRect = {(WIN_SIZE_WIDTH - textWidth) / 2, (WIN_SIZE_HEIGHT - textHeight) / 2, textWidth, textHeight};

    //
    SDL_FreeSurface(surface);
    SDL_RenderCopy(this->sdl_renderer, texture, nullptr, &destRect);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(dynamicFont);

}


