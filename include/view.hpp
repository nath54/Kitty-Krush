//
#pragma once
//
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
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
        std::unique_ptr<Value> x;
        std::unique_ptr<Value> y;
        std::unique_ptr<Value> w;
        std::unique_ptr<Value> h;

        //
        Style* style;

        //
        WindowElt( Style* style,
                   std::unique_ptr<Value> x,
                   std::unique_ptr<Value> y,
                   std::unique_ptr<Value> w = std::make_unique<ValueInt>(1),
                   std::unique_ptr<Value> h = std::make_unique<ValueInt>(1)
                )
            : style(style), x(std::move(x)), y(std::move(y)), w(std::move(w)), h(std::move(h)) {};

        //
        void draw_elt(MainView* main_view);

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
                       std::unique_ptr<Value> x,
                       std::unique_ptr<Value> y,
                       std::unique_ptr<Value> w = std::make_unique<ValueInt>(-1),
                       std::unique_ptr<Value> h = std::make_unique<ValueInt>(-1)
                    )
            : WindowElt(style, std::move(x), std::move(y), std::move(w), std::move(h)), txt(txt) {};

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
                         std::unique_ptr<Value> x,
                         std::unique_ptr<Value> y,
                         std::unique_ptr<Value> w,
                         std::unique_ptr<Value> h
                        )
        : WindowElt(style, std::move(x), std::move(y), std::move(w), std::move(h)), txt(txt) {};

        //
        void draw_elt(MainView* main_view);

};


//
class WindowPage{

    public:

        //
        std::unique_ptr< std::vector< std::unique_ptr<WindowElt> > > elts;

        // Constructeur par défaut
        WindowPage() {

            //
            this->elts = std::make_unique< std::vector< std::unique_ptr<WindowElt> > >();

        };

        //
        void draw_page(MainView* main_view);

};




//
class WindowPagesManager{

    public:

        //
        std::unique_ptr< std::map<std::string, std::unique_ptr<WindowPage> > > pages;
        std::string current_page;

        //
        WindowPagesManager() {

            //
            this->pages = std::make_unique<std::map<std::string, std::unique_ptr<WindowPage>>>();

        }

        //
        void draw_current_page( MainView* main_view );

        //
        void set_current_page( std::string new_current_page );

};





