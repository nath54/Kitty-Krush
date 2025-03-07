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




// Render text function
void MainView::render_text(std::string text, Color cl, int fontSize, std::string font_path) {

    //
    TTF_Font* dynamicFont = TTF_OpenFont(font_path.c_str(), fontSize);
    if (!dynamicFont) {
        sprintf(SDL_ERROR_BUFFER, "Failed to load font! TTF_OpenFont Error: %s", TTF_GetError());
        this->sdl_error(SDL_ERROR_BUFFER);
    }

    //
    SDL_Color color = {(Uint8)cl.r, (Uint8)cl.g, (Uint8)cl.b, (Uint8)cl.a};
    // SDL_Surface* surface = TTF_RenderText_Solid(dynamicFont, text.c_str(), color);     // No anti-aliasing (blocky text).
    // SDL_Surface* surface = TTF_RenderText_Shaded(dynamicFont, text.c_str(), color);     // Anti-aliasing with background color.
    SDL_Surface* surface = TTF_RenderText_Blended(dynamicFont, text.c_str(), color);     // Best anti-aliasing, recommended for smooth text.
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->sdl_renderer, surface);

    //
    int textWidth = surface->w;
    int textHeight = surface->h;
    SDL_Rect destRect = {(this->win_width - textWidth) / 2, (this->win_height - textHeight) / 2, textWidth, textHeight};

    //
    SDL_FreeSurface(surface);
    SDL_RenderCopy(this->sdl_renderer, texture, nullptr, &destRect);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(dynamicFont);

}











