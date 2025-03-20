//
#pragma once
//
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cstdio>
#include <map>
#include <string>
#include <vector>
#include <memory>
//
#include <stdint.h>
//
#include "color.hpp"
#include "model.hpp"
#include "window_elt_style.hpp"
#include "window_attributes.hpp"

//
static const int WIN_SIZE_WIDTH_INIT = 900;
static const int WIN_SIZE_HEIGHT_INIT = 700;
//
static char SDL_ERROR_BUFFER[1000];


// Forward declaration

class WindowPagesManager;




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
        WindowAttributes win_attr;

        // Window pages
        WindowPagesManager* win_page_manager = nullptr;

        // SDL related attributes
        SDL_Window* sdl_window = nullptr;
        SDL_Surface* sdl_window_surface = nullptr;
        SDL_Renderer* sdl_renderer = nullptr;

        // Font path
        const char* font_path = "res/fonts/blinky_star/BlinkyStar.otf";

        // SDL ttf related attributes
        map<int, TTF_Font*> ttf_fonts;

        // SDL image related attributes
        map<std::string, SDL_Texture*> loaded_textures;

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

        // Create the pages for each menu
        void init_window_pages();

        // Main update display method
        void update_display(int menu_state);

        // Get mouse position & buttons states
        void update_mouse_state();

        //
        WindowAttributes* get_win_attr();

        // Draw Main Menu
        void display_menu_main();

        // Draw Game Settings Menu
        void display_menu_game_settings();

        // Draw In Game
        void display_menu_in_game();

        // Get font
        TTF_Font* get_font(int fontSize);

        // Get a texture
        SDL_Texture* get_texture(std::string img_path);

        // Render img function
        void draw_image(SDL_Texture* texture, int src_x, int src_y, int src_w, int src_h, int dest_x, int dest_y, int dest_w, int dest_h, int angle = 0, bool flip_horizontal = false, bool flip_vertical = false);


        // Render text function
        void draw_text(std::string text, Color cl, int fontSize, int x, int y, int w = -1, int h = -1);

        //
        void draw_rounded_rect(int x, int y, int w, int h, int r, Color color);

        //
        void draw_button_1(int x, int y, int w, int h, std::string text, Color fg_cl, Color bg_cl, int fontSize, int r);

};



//
class Value{

    public:

        //
        virtual int get_value() = 0;

};



//
class ValueInt: public Value{

    public:

        int value;

        ValueInt(int value): value(value) {}

        int get_value();
};


//
class ValuePercentWinWidth: public Value{

    public:

        //
        float percent;
        float min_value = 0.0;
        float max_value = 0.0;

        //
        WindowAttributes* win_attr;

        //
        ValuePercentWinWidth(float percent, WindowAttributes* win_attr): percent(percent), win_attr(win_attr) {}

        //
        int get_value();

};



//
class ValuePercentWinHeight: public Value{

    public:

        //
        float percent;

        //
        WindowAttributes* win_attr;

        //
        ValuePercentWinHeight(float percent, WindowAttributes* win_attr): percent(percent), win_attr(win_attr) {}

        //
        int get_value();

};


//
class WindowElt{

    public:

        //
        Value* x;
        Value* y;
        Value* w;
        Value* h;

        //
        Style* style;

        //
        WindowElt( Style* style,
                   Value* x,
                   Value* y,
                   Value* w = new ValueInt(1),
                   Value* h = new ValueInt(1)
                )
            : style(style), x(x), y(y), w(w), h(h) {};

        //
        virtual void draw_elt(MainView* main_view);

        //
        int get_elt_state(WindowAttributes* win_attr);

        //
        int get_x();

        //
        int get_y();

        //
        int get_w();

        //
        int get_h();

};


//
class WindowEltText : public WindowElt {

    public:

        //
        std::string txt;

        //
        WindowEltText( Style* style,
                       std::string txt,
                       Value* x,
                       Value* y,
                       Value* w = new ValueInt(-1),
                       Value* h = new ValueInt(-1)
                    )
            : WindowElt(style, x, y, w, h), txt(txt) {};

        //
        void draw_elt(MainView* main_view);

};


//
class WindowEltButton : public WindowElt {

    public:

        //
        std::string txt;
        //
        Color color;
        //
        int fontSize;

        //
        WindowEltButton( Style* style,
                         std::string txt,
                         Value* x,
                         Value* y,
                         Value* w,
                         Value* h
                        )
        : WindowElt(style, x, y, w, h), txt(txt) {};

        //
        void draw_elt(MainView* main_view);

};


//
class WindowEltSprite : public WindowElt {

    public:

        //
        std::string img_path;
        //
        Value* angle = 0;
        bool flip_h = false;
        bool flip_v = false;

        //
        enum class LayoutMode {
            STRETCH,   // Stretch to fit (can distort)
            FIT,       // Scale to fit inside (letterbox)
            COVER,     // Scale to fill (crop excess)
            CUSTOM_SCALE // Manual scaling
        };

        //
        enum class CropMode {
            NO_CROP,       // Use full image
            CENTER_CROP,   // Crop from center
            TOP_LEFT_CROP, // Crop from top-left
            CUSTOM_CROP    // Use custom coordinates
        };

        //
        LayoutMode layout_mode = LayoutMode::FIT;
        CropMode crop_mode = CropMode::NO_CROP;

        //
        float custom_scale = 1.0f;

        //
        int custom_crop_x = 0;
        int custom_crop_y = 0;
        int custom_crop_w = 0;
        int custom_crop_h = 0;

        //
        WindowEltSprite( Style* style,
                         std::string img_path,
                         Value* x,
                         Value* y,
                         Value* w,
                         Value* h,
                         Value* angle = new ValueInt(0),
                         bool flip_h = false,
                         bool flip_v = false,
                         LayoutMode layout_mode = LayoutMode::FIT,
                         CropMode crop_mode = CropMode::NO_CROP,
                         float custom_scale = 1.0f,
                         int custom_crop_x = 0,
                         int custom_crop_y = 0,
                         int custom_crop_w = 0,
                         int custom_crop_h = 0
                        )
        :
            WindowElt(style, x, y, w, h),
            img_path(img_path),
            angle(angle),
            flip_h(flip_h),
            flip_v(flip_v),
            layout_mode(layout_mode),
            crop_mode(crop_mode),
            custom_scale(custom_scale),
            custom_crop_x(custom_crop_x),
            custom_crop_y(custom_crop_y),
            custom_crop_w(custom_crop_w),
            custom_crop_h(custom_crop_h)
        {};

        //
        void draw_elt(MainView* main_view);

};


//
class WindowPage{

    public:

        //
        std::vector< WindowElt* > elts;

        // Constructeur par défaut
        WindowPage() {}

        //
        void draw_page(MainView* main_view);

};


//
class WindowPagesManager{

    public:

        //
        std::map<std::string, WindowPage* > pages;
        std::string current_page;

        //
        WindowPagesManager() {}

        //
        void draw_current_page( MainView* main_view );

        //
        void set_current_page( std::string new_current_page );

};
