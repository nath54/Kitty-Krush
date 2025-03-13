//
#include <iostream>
#include <string>
#include <cmath>
#include <unistd.h>
//
#include "view.hpp"
#include "color.hpp"
//
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>



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

    // Iterate & Destroy all the fonts
    for (const auto& [key, value] : this->ttf_fonts) {
        // std::cout << "Key: " << key << ", Value: " << value << std::endl;
    }

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


//
TTF_Font* MainView::get_font(int fontSize){

    //
    std::map<int, TTF_Font*>::iterator res_iter = this->ttf_fonts.find(fontSize);
    if( res_iter != this->ttf_fonts.end() ){

        // res_iter->first is the key, res_iter->second is the value
        return res_iter->second;

    }

    // If not exists
    TTF_Font* dynamicFont = TTF_OpenFont(this->font_path, fontSize);
    if (!dynamicFont) {
        sprintf(SDL_ERROR_BUFFER, "Failed to load font! TTF_OpenFont Error: %s", TTF_GetError());
        this->sdl_error(SDL_ERROR_BUFFER);
    }

    //
    this->ttf_fonts[fontSize] = dynamicFont;

    //
    return dynamicFont;

}



// Render text function
void MainView::draw_text(std::string text, Color cl, int fontSize, int x, int y, int w, int h) {

    //
    TTF_Font* dynamicFont = this->get_font(fontSize);

    //
    SDL_Color color = {(Uint8)cl.r, (Uint8)cl.g, (Uint8)cl.b, (Uint8)cl.a};
    // SDL_Surface* surface = TTF_RenderText_Solid(dynamicFont, text.c_str(), color);     // No anti-aliasing (blocky text).
    // SDL_Surface* surface = TTF_RenderText_Shaded(dynamicFont, text.c_str(), color);     // Anti-aliasing with background color.
    SDL_Surface* surface = TTF_RenderText_Blended(dynamicFont, text.c_str(), color);     // Best anti-aliasing, recommended for smooth text.
    SDL_Texture* texture = SDL_CreateTextureFromSurface(this->sdl_renderer, surface);

    //
    int textWidth = surface->w;
    int textHeight = surface->h;

    //
    if (w != -1 && h != -1){

        //
        x = x + (w - textWidth) / 2;
        y = y + (h - textHeight) / 2;

    }

    //
    SDL_Rect destRect = {x, y, textWidth, textHeight};

    //
    SDL_FreeSurface(surface);
    SDL_RenderCopy(this->sdl_renderer, texture, nullptr, &destRect);
    SDL_DestroyTexture(texture);

}



//
void MainView::draw_rounded_rect(int x, int y, int w, int h, int r, Color color){

    //
    uint32_t hex_cl = color.to_hex();

    // Rounded corners
    filledCircleColor(this->sdl_renderer, x + r, y + r, r, hex_cl);
    filledCircleColor(this->sdl_renderer, x + w - r, y + r, r, hex_cl);
    filledCircleColor(this->sdl_renderer, x + r, y + h - r, r, hex_cl);
    filledCircleColor(this->sdl_renderer, x + w - r, y + h - r, r, hex_cl);

    // the boxes
    boxColor(this->sdl_renderer, x + r, y, x + w - r, y + h, hex_cl);
    boxColor(this->sdl_renderer, x, y + r, x + w, y + h - r, hex_cl);

}



//
void MainView::draw_button_1(int x, int y, int w, int h, std::string text, Color fg_cl, Color bg_cl, int fontSize, int r){

    //
    this->draw_rounded_rect(x, y, w, h, r, bg_cl);

    //
    this->draw_text(text, fg_cl, fontSize, x, y, w, h);

}

