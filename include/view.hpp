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
#include <functional>
//
#include <stdint.h>
//
#include "color.hpp"
#include "model.hpp"
#include "window_elt_style.hpp"
#include "window_attributes.hpp"

//
static const int WIN_SIZE_WIDTH_INIT = 834;
static const int WIN_SIZE_HEIGHT_INIT = 836;
// static const int WIN_SIZE_WIDTH_INIT = 900;
// static const int WIN_SIZE_HEIGHT_INIT = 700;
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

        // Create the main menu page
        void init_page_main_menu();

        // Create the game settings page
        void init_page_game_settings();

        // Create the in game page
        void init_page_in_game();

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
class ValuePercent{

    public:

        float percent;

        ValuePercent(float percent): percent(percent) {}

        float get_value();

        int get_value_scaled(int value);
};


//
class ValuePercentWinWidth: public Value{

    public:

        //
        float percent;

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
ValueInt* nvi(int value);


//
ValuePercent* nvp(float percent);

//
ValuePercentWinWidth* nvpww(float prc, WindowAttributes* win_attr);

//
ValuePercentWinHeight* nvpwh(float prc, WindowAttributes* win_attr);



//
class DrawTransform{

    public:

        //
        Value* translation_x = nullptr;
        Value* translation_y = nullptr;
        //
        float scale_w = 1.0;
        float scale_h = 1.0;

        //
        DrawTransform(
            Value* translation_x = nullptr,
            Value* translation_y = nullptr,
            float scale_w = 1.0,
            float scale_h = 1.0
        )
        :   translation_x(translation_x),
            translation_y(translation_y),
            scale_w(scale_w),
            scale_h(scale_h)
        {}

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
        virtual void draw_elt(MainView* main_view, DrawTransform* transform=nullptr);

        //
        int get_elt_state(WindowAttributes* win_attr, DrawTransform* transform=nullptr);

        //
        int get_x(DrawTransform* transform=nullptr);

        //
        int get_y(DrawTransform* transform=nullptr);

        //
        int get_w(DrawTransform* transform=nullptr);

        //
        int get_h(DrawTransform* transform=nullptr);

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
        std::map< std::string, WindowPage* > pages;
        std::string current_page;
        Style* default_style;

        //
        WindowPagesManager() {
            this->default_style = new Style();
        }

        //
        void draw_current_page( MainView* main_view );

        //
        void set_current_page( std::string new_current_page );

};



//
class WindowEltClickable : public WindowElt {

    public:

        //
        std::function<void(MainView*)> on_click = nullptr;

        //
        WindowEltClickable(
            Style* style,
            Value* x,
            Value* y,
            Value* w = new ValueInt(-1),
            Value* h = new ValueInt(-1),
            std::function<void(MainView*)> on_click = nullptr
         )
        : WindowElt(style, x, y, w, h), on_click(on_click) {};

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
        void draw_elt(MainView* main_view, DrawTransform* transform=nullptr);

};


//
class WindowEltButton : public WindowEltClickable {

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
                         Value* h,
                         std::function<void(MainView*)> on_click = nullptr
                        )
        : WindowEltClickable(style, x, y, w, h, on_click), txt(txt) {};

        //
        void draw_elt(MainView* main_view, DrawTransform* transform=nullptr);

};




//
class SpriteCrop{

    public:

        //
        ValuePercent* src_x;
        ValuePercent* src_y;
        ValuePercent* src_w;
        ValuePercent* src_h ;

        // Constructor
        SpriteCrop(
            ValuePercent* src_x,
            ValuePercent* src_y,
            ValuePercent* src_w,
            ValuePercent* src_h
        )
            : src_x(src_x), src_y(src_y), src_w(src_w), src_h(src_h) {}

};


//
SpriteCrop* SPRITE_NO_CROP();

//
SpriteCrop* SPRITE_CUSTOM_CROP(float src_x, float src_y, float src_w, float src_h);


//
class SpriteRatio{

    public:

        //
        bool keep_original;
        ValuePercent* prc_dest_w;
        ValuePercent* prc_dest_h;

        //
        SpriteRatio(
            bool keep_original,
            ValuePercent* prc_dest_w,
            ValuePercent* prc_dest_h
        )
            : keep_original(keep_original), prc_dest_w(prc_dest_w), prc_dest_h(prc_dest_h) {}

};


//
SpriteRatio* SPRITE_RATIO_ORIGINAL();

//
SpriteRatio* SPRITE_RATIO_CUSTOM(float prc_dest_w, float prc_dest_h);


//
#define SPRITE_ENUM_RESIZE_KEEP_ORIGINAL 0
#define SPRITE_ENUM_RESIZE_FIT 1
#define SPRITE_ENUM_RESIZE_COVER 2


//
class SpriteResize{

    public:

        //
        int mode;
        float resize_factor = 1.0;

        //
        SpriteResize(int mode, float resize_factor): mode(mode), resize_factor(resize_factor) {}

};


//
SpriteResize* SPRITE_RESIZE_KEEP_ORIGINAL(float resize_factor = 1.0);

//
SpriteResize* SPRITE_RESIZE_FIT(float resize_factor = 1.0);

//
SpriteResize* SPRITE_RESIZE_COVER(float resize_factor = 1.0);


//
class SpritePosition{

    public:

        //
        float percent;

        //
        int delta;

        //
        SpritePosition(float percent, int delta): percent(percent), delta(delta) {}

};


//
SpritePosition* SPRITE_POS_ALIGN_START();

//
SpritePosition* SPRITE_POS_ALIGN_CENTER();

//
SpritePosition* SPRITE_POS_ALIGN_END();

//
SpritePosition* SPRITE_POS_CUSTOM(float percent, int delta);



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
        SpriteCrop* sprite_crop;
        SpriteRatio* sprite_ratio;
        SpriteResize* sprite_resize;
        SpritePosition* sprite_h_position;
        SpritePosition* sprite_v_position;

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
                         SpriteCrop* sprite_crop = SPRITE_NO_CROP(),
                         SpriteRatio* sprite_ratio = SPRITE_RATIO_ORIGINAL(),
                         SpriteResize* sprite_resize = SPRITE_RESIZE_KEEP_ORIGINAL(),
                         SpritePosition* sprite_h_position = SPRITE_POS_ALIGN_START(),
                         SpritePosition* sprite_v_position = SPRITE_POS_ALIGN_START()
                        )
        :
            WindowElt(style, x, y, w, h),
            img_path(img_path),
            angle(angle),
            flip_h(flip_h),
            flip_v(flip_v),
            sprite_crop(sprite_crop),
            sprite_ratio(sprite_ratio),
            sprite_resize(sprite_resize),
            sprite_h_position(sprite_h_position),
            sprite_v_position(sprite_v_position)
        {};

        //
        void draw_elt(MainView* main_view, DrawTransform* transform=nullptr);

};



//
class Vector2{

    public:

        //
        int x;
        int y;

        //
        Vector2(int x, int y): x(x), y(y) {}

        //
        bool operator<(const Vector2& v){
            return this->x < v.x && this->y < v.y;
        }

        friend bool operator<(const Vector2& l, const Vector2& r){
            return l.x < r.x && l.y < r.y;
        }

};


//
Vector2 v2(int x, int y);




//
class WindowEltMapTile: public WindowElt {

    //
    WindowEltMapTile( Style* style,
        std::string img_path,
        Value* x,
        Value* y,
        Value* w,
        Value* h)
    : WindowElt(style, x, y, w, h) {}

    //
    void draw_elt(MainView* main_view, DrawTransform* transform=nullptr);

};




//
class WindowEltMapViewer: public WindowElt {

    //
    std::map< Vector2, WindowEltMapTile* > tiles_layers;

    //
    WindowEltMapViewer( Style* style,
        std::string img_path,
        Value* x,
        Value* y,
        Value* w,
        Value* h)
    : WindowElt(style, x, y, w, h) {}

    //
    void draw_elt(MainView* main_view, DrawTransform* transform=nullptr);

};
