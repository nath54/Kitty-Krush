#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <list>
#include <memory>
#include <functional>

#include <stdint.h>

#include "main_game.hpp"
#include "geometry.hpp"
#include "color.hpp"
#include "model_game.hpp"
#include "window_elt_style.hpp"
#include "window_attributes.hpp"


static const int WIN_SIZE_WIDTH_INIT = 834;
static const int WIN_SIZE_HEIGHT_INIT = 836;
// static const int WIN_SIZE_WIDTH_INIT = 900;
// static const int WIN_SIZE_HEIGHT_INIT = 700;
//
static char SDL_ERROR_BUFFER[1000];

static const int frameDelay = 16;  // 60 FPS = 1000 miliseconds / 60 frame per seconds = 16 miliseconds per frame



// =============================== [ Pointers ] ===============================


#define WINDOW_ELT_T std::shared_ptr<WindowElt>
#define WINDOW_ELT_CLICKABLE_T std::shared_ptr<WindowEltClickable>
#define WINDOW_ELT_RECT_T std::shared_ptr<WindowEltRect>
#define WINDOW_ELT_SPRITE_T std::shared_ptr<WindowEltSprite>
#define WINDOW_ELT_ANIMATED_SPRITE_T std::shared_ptr<WindowEltAnimatedSprite>
#define WINDOW_ELT_BUTTON_T std::shared_ptr<WindowEltButton>
#define WINDOW_ELT_TEXT_T std::shared_ptr<WindowEltText>
#define WINDOW_ELT_MAP_TILE_T std::shared_ptr<WindowEltMapTile>
#define WINDOW_ELT_MAP_VIEWER_T std::shared_ptr<WindowEltMapViewer>

#define VALUE_T std::shared_ptr<Value>
#define VALUE_INT_T std::shared_ptr<ValueInt>
#define VALUE_PERCENT_T std::shared_ptr<ValuePercent>
#define VALUE_PERCENT_WIN_WIDTH_T std::shared_ptr<ValuePercentWinWidth>
#define VALUE_PERCENT_WIN_HEIGHT_T std::shared_ptr<ValuePercentWinHeight>

#define DRAW_TRANSFORM_T std::shared_ptr<DrawTransform>

#define SPRITE_CROP_T std::shared_ptr<SpriteCrop>
#define SPRITE_CROP_INT_T std::shared_ptr<SpriteCropInt>
#define SPRITE_CROP_VALUE_PERCENT_T std::shared_ptr<SpriteCropValuePercent>
#define SPRITE_POSITION_T std::shared_ptr<SpritePosition>
#define SPRITE_RATIO_T std::shared_ptr<SpriteRatio>
#define SPRITE_RESIZE_T std::shared_ptr<SpriteResize>

#define CREATE_WINDOW_ELT_T(...) std::make_shared<WindowElt>(__VA_ARGS__)
#define CREATE_WINDOW_ELT_CLICKABLE_T(...) std::make_shared<WindowEltClickable>(__VA_ARGS__)
#define CREATE_WINDOW_ELT_RECT_T(...) std::make_shared<WindowEltRect>(__VA_ARGS__)
#define CREATE_WINDOW_ELT_SPRITE_T(...) std::make_shared<WindowEltSprite>(__VA_ARGS__)
#define CREATE_WINDOW_ELT_ANIMATED_SPRITE_T(...) std::make_shared<WindowEltAnimatedSprite>(__VA_ARGS__)
#define CREATE_WINDOW_ELT_BUTTON_T(...) std::make_shared<WindowEltButton>(__VA_ARGS__)
#define CREATE_WINDOW_ELT_TEXT_T(...) std::make_shared<WindowEltText>(__VA_ARGS__)
#define CREATE_WINDOW_ELT_MAP_TILE_T(...) std::make_shared<WindowEltMapTile>(__VA_ARGS__)
#define CREATE_WINDOW_ELT_MAP_VIEWER_T(...) std::make_shared<WindowEltMapViewer>(__VA_ARGS__)

#define CREATE_VALUE_T(...) std::make_shared<Value>(__VA_ARGS__)
#define CREATE_VALUE_INT_T(...) std::make_shared<ValueInt>(__VA_ARGS__)
#define CREATE_VALUE_PERCENT_T(...) std::make_shared<ValuePercent>(__VA_ARGS__)
#define CREATE_VALUE_PERCENT_WIN_WIDTH_T(...) std::make_shared<ValuePercentWinWidth>(__VA_ARGS__)
#define CREATE_VALUE_PERCENT_WIN_HEIGHT_T(...) std::make_shared<ValuePercentWinHeight>(__VA_ARGS__)

#define CREATE_DRAW_TRANSFORM_T(...) std::make_shared<DrawTransform>(__VA_ARGS__)

#define CREATE_SPRITE_CROP_T(...) std::make_shared<SpriteCrop>(__VA_ARGS__)
#define CREATE_SPRITE_CROP_INT_T(...) std::make_shared<SpriteCropInt>(__VA_ARGS__)
#define CREATE_SPRITE_CROP_VALUE_PERCENT_T(...) std::make_shared<SpriteCropValuePercent>(__VA_ARGS__)
#define CREATE_SPRITE_POSITION_T(...) std::make_shared<SpritePosition>(__VA_ARGS__)
#define CREATE_SPRITE_RATIO_T(...) std::make_shared<SpriteRatio>(__VA_ARGS__)
#define CREATE_SPRITE_RESIZE_T(...) std::make_shared<SpriteResize>(__VA_ARGS__)

#define DCAST_WINDOW_ELT_CLICKABLE_T(...) std::dynamic_pointer_cast<WindowEltClickable>(__VA_ARGS__)
#define DCAST_WINDOW_ELT_RECT_T(...) std::dynamic_pointer_cast<WindowEltRect>(__VA_ARGS__)
#define DCAST_WINDOW_ELT_SPRITE_T(...) std::dynamic_pointer_cast<WindowEltSprite>(__VA_ARGS__)
#define DCAST_WINDOW_ELT_ANIMATED_SPRITE_T(...) std::dynamic_pointer_cast<WindowEltAnimatedSprite>(__VA_ARGS__)
#define DCAST_WINDOW_ELT_BUTTON_T(...) std::dynamic_pointer_cast<WindowEltButton>(__VA_ARGS__)
#define DCAST_WINDOW_ELT_TEXT_T(...) std::dynamic_pointer_cast<WindowEltText>(__VA_ARGS__)
#define DCAST_WINDOW_ELT_MAP_TILE_T(...) std::dynamic_pointer_cast<WindowEltMapTile>(__VA_ARGS__)
#define DCAST_WINDOW_ELT_MAP_VIEWER_T(...) std::dynamic_pointer_cast<WindowEltMapViewer>(__VA_ARGS__)

#define DCAST_VALUE_INT_T(...) std::dynamic_pointer_cast<ValueInt>(__VA_ARGS__)
#define DCAST_VALUE_PERCENT_T(...) std::dynamic_pointer_cast<ValuePercent>(__VA_ARGS__)
#define DCAST_VALUE_PERCENT_WIN_WIDTH_T(...) std::dynamic_pointer_cast<ValuePercentWinWidth>(__VA_ARGS__)
#define DCAST_VALUE_PERCENT_WIN_HEIGHT_T(...) std::dynamic_pointer_cast<ValuePercentWinHeight>(__VA_ARGS__)

#define DCAST_SPRITE_CROP_T(...) std::dynamic_pointer_cast<SpriteCrop>(__VA_ARGS__)
#define DCAST_SPRITE_CROP_INT_T(...) std::dynamic_pointer_cast<SpriteCropInt>(__VA_ARGS__)
#define DCAST_SPRITE_CROP_VALUE_PERCENT_T(...) std::dynamic_pointer_cast<SpriteCropValuePercent>(__VA_ARGS__)
#define DCAST_SPRITE_POSITION_T(...) std::dynamic_pointer_cast<SpritePosition>(__VA_ARGS__)
#define DCAST_SPRITE_RATIO_T(...) std::dynamic_pointer_cast<SpriteRatio>(__VA_ARGS__)
#define DCAST_SPRITE_RESIZE_T(...) std::dynamic_pointer_cast<SpriteResize>(__VA_ARGS__)

// =============================== [ Classes ] ===============================




// Forward declaration
class WindowPagesManager;
class WindowEltMapViewer;


// Class MainView, manages the SDL environment & SDL Window
class MainView{

    // Private attributes & functions
    public:

        //
        bool sdl_initialized = false;
        bool ttf_initialized = false;
        //
        uint32_t startTime = 0;
        //
        uint32_t frameStart = 0;
        uint32_t frameTime = 0;

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
        std::map<int, TTF_Font*> ttf_fonts;

        // SDL image related attributes
        std::map<std::string, SDL_Texture*> loaded_textures;

        // Reference to game_model
        GameModel* game_model = nullptr;

        // Reference to map viewer
        WINDOW_ELT_MAP_VIEWER_T map_viewer = nullptr;

        // Constructor
        MainView(GameModel* game_model);

        // Destructor
        ~MainView();

        // Clean quit program while displaying the sdl error
        void sdl_error(const char* error_msg);

        // Destroy all the SDL variable created here inside
        void destroy_all_created();

        // Create the pages for each menu
        void init_window_pages();

        // Create the main menu page
        void init_page_main_menu();

        // Create the game settings page
        void init_page_game_settings();

        // Create the in game page
        void init_page_in_game();

        // Create the map creator page
        void init_page_map_creator();

        // At frame
        void at_frame_start();
        void at_frame_end();

        // Main update display method
        void update_display(int menu_state);

        // Get mouse position & buttons states
        void update_mouse_state();

        //
        WINDOW_ATTRIBUTE_T get_win_attr();

        // Draw Main Menu
        void display_menu_main();

        // Draw Game Settings Menu
        void display_menu_game_settings();

        // Draw In Game
        void display_menu_in_game();

        // Draw Map Creator
        void display_menu_map_creator();

        //
        void update_menu_game_settings(MainGame* main_game, bool update_all_maps = true);

        // Get font
        TTF_Font* get_font(int fontSize);

        // Get a texture
        SDL_Texture* get_texture(std::string img_path);

        // Render img function
        void draw_image(SDL_Texture* texture, int src_x, int src_y, int src_w, int src_h, int dest_x, int dest_y, int dest_w, int dest_h,
                        int angle = 0, bool flip_horizontal = false, bool flip_vertical = false, bool do_color_mod = false, Color color_mod = (Color){255, 255, 255});

        // Render text function
        void draw_text(std::string text, Color cl, int fontSize, int x, int y, int w = -1, int h = -1);

        // Draw
        void draw_rounded_rect(int x, int y, int w, int h, int r, Color color);
        void draw_button_1(int x, int y, int w, int h, std::string text, Color fg_cl, Color bg_cl, int fontSize, int r);

};


class Value {

    public:

        //
        virtual int get_value() = 0;


};


class ValueInt: public Value {

    public:

        // Attribute
        int value;

        // Constructor
        ValueInt(int value): value(value) {}

        // Getter
        int get_value();
};


class ValuePercent {

    public:

        // Attribute
        float percent;

        // Constructor
        ValuePercent(float percent): percent(percent) {}

        // Getters
        float get_value();
        int get_value_scaled(int value);
};


class ValuePercentWinWidth: public Value {

    public:

        // Attributes
        float percent;
        //
        int shift = 0;
        //
        WINDOW_ATTRIBUTE_T win_attr;

        // Constructor
        ValuePercentWinWidth(WINDOW_ATTRIBUTE_T win_attr, float percent, int shift = 0)
            : win_attr(win_attr), percent(percent), shift(shift) {}

        // Getter
        int get_value();
};


class ValuePercentWinHeight: public Value {

    public:

        // Attributes
        float percent;
        //
        int shift = 0;
        //
        WINDOW_ATTRIBUTE_T win_attr;

        // Constructor
        ValuePercentWinHeight(WINDOW_ATTRIBUTE_T win_attr, float percent, int shift = 0)
            : win_attr(win_attr), percent(percent), shift(shift) {}

        // Getter
        int get_value();
};


VALUE_INT_T nvi(int value);

VALUE_PERCENT_T nvp(float percent);

VALUE_PERCENT_WIN_WIDTH_T nvpww(WINDOW_ATTRIBUTE_T win_attr, float prc, int shift=0);

VALUE_PERCENT_WIN_HEIGHT_T nvpwh(WINDOW_ATTRIBUTE_T win_attr, float prc, int shift=0);


class DrawTransform {

    public:

        // Attributes
        VALUE_T translation_x = nullptr;
        VALUE_T translation_y = nullptr;
        //
        float scale_w = 1.0;
        float scale_h = 1.0;
        //
        uint32_t time_shift = 0;
        //
        bool do_color_mod = false;
        Color color_mod = (Color){255, 255, 255};

        // Constructor
        DrawTransform(
            VALUE_T translation_x = nullptr,
            VALUE_T translation_y = nullptr,
            float scale_w = 1.0,
            float scale_h = 1.0,
            uint32_t time_shift = 0,
            bool do_color_mod = 0,
            Color color_mod = (Color){255, 255, 255}
        )
        :   translation_x(translation_x),
            translation_y(translation_y),
            scale_w(scale_w),
            scale_h(scale_h),
            time_shift(time_shift),
            do_color_mod(do_color_mod),
            color_mod(color_mod)
        {}
};


class WindowElt {

    public:

        // Attributes
        VALUE_T x;
        VALUE_T y;
        VALUE_T w;
        VALUE_T h;
        //
        bool visible = true;
        //
        STYLE_T style;

        // Constructor
        WindowElt( STYLE_T style,
                   VALUE_T x,
                   VALUE_T y,
                   VALUE_T w = CREATE_VALUE_INT_T(1),
                   VALUE_T h = CREATE_VALUE_INT_T(1)
                )
            : style(style), x(x), y(y), w(w), h(h) {};

        // Getters
        int get_elt_state(WINDOW_ATTRIBUTE_T win_attr, DRAW_TRANSFORM_T transform=nullptr);
        int get_x(DRAW_TRANSFORM_T transform=nullptr);
        int get_y(DRAW_TRANSFORM_T transform=nullptr);
        int get_w(DRAW_TRANSFORM_T transform=nullptr);
        int get_h(DRAW_TRANSFORM_T transform=nullptr);

        // Function
        virtual void draw_elt(MainView* main_view, DRAW_TRANSFORM_T transform=nullptr);
};


class WindowPage {

    public:

        // Attribute
        std::vector< WINDOW_ELT_T > elts;

        // Constructeur par défaut
        WindowPage() {}

        // Function
        void draw_page(MainView* main_view);
};


class WindowPagesManager {

    public:

        // Attributes
        std::map< std::string, WindowPage* > pages;
        std::string current_page;
        STYLE_T default_style;

        // Constructor
        WindowPagesManager() { this->default_style = CREATE_STYLE_T(); }

        // Functions
        WindowPage* get_current_page();
        void draw_current_page( MainView* main_view );
        void set_current_page( std::string new_current_page );
};


class WindowEltClickable : public WindowElt {

    public:

        // Attributes
        bool disabled = false;
        std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)> on_click = nullptr;
        std::vector<std::string> additional_fn_args;

        // Constructor
        WindowEltClickable(
            STYLE_T style,
            VALUE_T x,
            VALUE_T y,
            VALUE_T w = CREATE_VALUE_INT_T(-1),
            VALUE_T h = CREATE_VALUE_INT_T(-1),
            std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)> on_click = nullptr,
            std::vector<std::string> additional_fn_args = (std::vector<std::string>){}
         )
        : WindowElt(style, x, y, w, h), on_click(on_click), additional_fn_args(additional_fn_args) {};
};


class WindowEltRect : public WindowElt {

    public:

        // Attributes
        Color cl;
        VALUE_T radius;

        // Constructor
        WindowEltRect( STYLE_T style,
                       Color cl,
                       VALUE_T x,
                       VALUE_T y,
                       VALUE_T w = CREATE_VALUE_INT_T(-1),
                       VALUE_T h = CREATE_VALUE_INT_T(-1),
                       VALUE_T radius = CREATE_VALUE_INT_T(0)
                    )
            : WindowElt(style, x, y, w, h), cl(cl), radius(radius) {};

        // Function
        void draw_elt(MainView* main_view, DRAW_TRANSFORM_T transform=nullptr);

};


class WindowEltText : public WindowElt {

    public:

        // Attribute
        std::string txt;

        // Constructor
        WindowEltText( STYLE_T style,
                       std::string txt,
                       VALUE_T x,
                       VALUE_T y,
                       VALUE_T w = CREATE_VALUE_INT_T(-1),
                       VALUE_T h = CREATE_VALUE_INT_T(-1)
                    )
            : WindowElt(style, x, y, w, h), txt(txt) {};

        // Function
        void draw_elt(MainView* main_view, DRAW_TRANSFORM_T transform=nullptr);
};


class SpriteCrop{

    public:

        // Constructor
        SpriteCrop() {}

        // Destructor
        virtual ~SpriteCrop() = default; // Use default implementation
};


//
class SpriteCropValuePercent : public SpriteCrop {

    public:

        // Attributes
        VALUE_PERCENT_T src_x;
        VALUE_PERCENT_T src_y;
        VALUE_PERCENT_T src_w;
        VALUE_PERCENT_T src_h ;

        // Constructor
        SpriteCropValuePercent(
            VALUE_PERCENT_T src_x,
            VALUE_PERCENT_T src_y,
            VALUE_PERCENT_T src_w,
            VALUE_PERCENT_T src_h
        )
            : SpriteCrop(), src_x(src_x), src_y(src_y), src_w(src_w), src_h(src_h) {}
};


class SpriteCropInt : public SpriteCrop {

    public:

        // Attributes
        int src_x;
        int src_y;
        int src_w;
        int src_h;

        // Constructor
        SpriteCropInt(
            int src_x,
            int src_y,
            int src_w,
            int src_h
        )
            : SpriteCrop(), src_x(src_x), src_y(src_y), src_w(src_w), src_h(src_h) {}
};


SPRITE_CROP_VALUE_PERCENT_T SPRITE_NO_CROP();

SPRITE_CROP_VALUE_PERCENT_T SPRITE_CUSTOM_CROP(float src_x, float src_y, float src_w, float src_h);


class SpriteRatio {

    public:

        // Attributes
        bool keep_original;
        VALUE_PERCENT_T prc_dest_w;
        VALUE_PERCENT_T prc_dest_h;

        // Constructor
        SpriteRatio(
            bool keep_original,
            VALUE_PERCENT_T prc_dest_w,
            VALUE_PERCENT_T prc_dest_h
        )
            : keep_original(keep_original), prc_dest_w(prc_dest_w), prc_dest_h(prc_dest_h) {}

};


SPRITE_RATIO_T SPRITE_RATIO_ORIGINAL();

SPRITE_RATIO_T SPRITE_RATIO_CUSTOM(float prc_dest_w, float prc_dest_h);


#define SPRITE_ENUM_RESIZE_KEEP_ORIGINAL 0
#define SPRITE_ENUM_RESIZE_FIT 1
#define SPRITE_ENUM_RESIZE_COVER 2


class SpriteResize {

    public:

        // Attributes
        int mode;
        float resize_factor = 1.0;

        // Constructor
        SpriteResize(int mode, float resize_factor)
            : mode(mode), resize_factor(resize_factor) {}
};


SPRITE_RESIZE_T SPRITE_RESIZE_KEEP_ORIGINAL(float resize_factor = 1.0);

SPRITE_RESIZE_T SPRITE_RESIZE_FIT(float resize_factor = 1.0);

SPRITE_RESIZE_T SPRITE_RESIZE_COVER(float resize_factor = 1.0);


class SpritePosition {

    public:

        // Attributes
        float percent;
        int delta;

        // Constructor
        SpritePosition(float percent, int delta): percent(percent), delta(delta) {}
};


SPRITE_POSITION_T SPRITE_POS_ALIGN_START();

SPRITE_POSITION_T SPRITE_POS_ALIGN_CENTER();

SPRITE_POSITION_T SPRITE_POS_ALIGN_END();

SPRITE_POSITION_T SPRITE_POS_CUSTOM(float percent, int delta);


class WindowEltSprite : public WindowElt {

    public:

        // Attributes
        std::string img_path;
        //
        VALUE_T angle = 0;
        bool flip_h = false;
        bool flip_v = false;
        //
        SPRITE_CROP_T sprite_crop;
        SPRITE_RATIO_T sprite_ratio;
        SPRITE_RESIZE_T sprite_resize;
        SPRITE_POSITION_T sprite_h_position;
        SPRITE_POSITION_T sprite_v_position;

        // Constructor
        WindowEltSprite( STYLE_T style,
                         std::string img_path,
                         VALUE_T x,
                         VALUE_T y,
                         VALUE_T w,
                         VALUE_T h,
                         VALUE_T angle = CREATE_VALUE_INT_T(0),
                         bool flip_h = false,
                         bool flip_v = false,
                         SPRITE_CROP_T sprite_crop = SPRITE_NO_CROP(),
                         SPRITE_RATIO_T sprite_ratio = SPRITE_RATIO_ORIGINAL(),
                         SPRITE_RESIZE_T sprite_resize = SPRITE_RESIZE_KEEP_ORIGINAL(),
                         SPRITE_POSITION_T sprite_h_position = SPRITE_POS_ALIGN_START(),
                         SPRITE_POSITION_T sprite_v_position = SPRITE_POS_ALIGN_START()
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

        // Function
        void draw_elt(MainView* main_view, DRAW_TRANSFORM_T transform=nullptr);
};


class WindowEltAnimatedSprite : public WindowElt {

    public:

        // Attributes
        int first_frame_x;
        int first_frame_y;
        int frame_w;
        int frame_h;
        int nb_frames;
        uint32_t frame_delay;
        //
        uint32_t start_time;
        //
        WINDOW_ELT_SPRITE_T sprite;
        //
        SPRITE_CROP_INT_T sprite_crop;

        // Constructor
        WindowEltAnimatedSprite( STYLE_T style,
                                 std::string img_path,
                                 VALUE_T x,
                                 VALUE_T y,
                                 VALUE_T w,
                                 VALUE_T h,
                                 int first_frame_x,
                                 int first_frame_y,
                                 int frame_w,
                                 int frame_h,
                                 int nb_frames,
                                 uint32_t frame_delay,
                                 VALUE_T angle = CREATE_VALUE_INT_T(0),
                                 bool flip_h = false,
                                 bool flip_v = false,
                                 SPRITE_RATIO_T sprite_ratio = SPRITE_RATIO_ORIGINAL(),
                                 SPRITE_RESIZE_T sprite_resize = SPRITE_RESIZE_KEEP_ORIGINAL(),
                                 SPRITE_POSITION_T sprite_h_position = SPRITE_POS_ALIGN_START(),
                                 SPRITE_POSITION_T sprite_v_position = SPRITE_POS_ALIGN_START()
                                );

        // Function
        void draw_elt(MainView* main_view, DRAW_TRANSFORM_T transform=nullptr);
};


class WindowEltButton : public WindowEltClickable {

    public:

        // Attributes
        std::string txt;
        //
        Color color;
        //
        int fontSize;
        //
        WINDOW_ELT_SPRITE_T bt_sprite = nullptr;

        // Constructor
        WindowEltButton( STYLE_T style,
                         std::string txt,
                         VALUE_T x,
                         VALUE_T y,
                         VALUE_T w,
                         VALUE_T h,
                         std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)> on_click = nullptr,
                         std::vector<std::string> additional_fn_args = (std::vector<std::string>){}
                        );

        // Function
        void draw_elt(MainView* main_view, DRAW_TRANSFORM_T transform=nullptr);
};


class WindowEltMapTile: public WindowElt {

    public:

        // Attributes
        int tile;
        //
        WINDOW_ELT_SPRITE_T ground_base_layer = nullptr;
        WINDOW_ELT_SPRITE_T ground_top_layer = nullptr;
        //
        bool ground_base_to_complete = false;

        // Constructor
        WindowEltMapTile(
            int tile,
            STYLE_T style,
            VALUE_T x,
            VALUE_T y,
            VALUE_T w,
            VALUE_T h
        );

        // Functions
        void draw_elt(MainView* main_view, DRAW_TRANSFORM_T transform=nullptr);
        void set_ground_base(std::string ground_base_img);
};


class EntityData{

    public:

        // Attributes
        int level;
        bool type;
        bool can_move;

        // Constructor
        EntityData(int level = -1, bool type = false, bool can_move = true) : level(level), type(type), can_move(can_move) {}
};


class WindowEltMapViewer: public WindowEltClickable {

    public:

        // Attributes
        std::map< Coord, WINDOW_ELT_MAP_TILE_T > tiles_layers;
        //
        // WINDOW_ELT_SPRITE_T default_empty_tile;
        WINDOW_ELT_ANIMATED_SPRITE_T default_empty_tile;
        WINDOW_ELT_SPRITE_T color_tile;
        WINDOW_ELT_ANIMATED_SPRITE_T under_entity_effect;
        WINDOW_ELT_ANIMATED_SPRITE_T can_go_here_effect;


        // ! TODO: sprites for all entities

        //
        WINDOW_ELT_ANIMATED_SPRITE_T warrior_lvl_0;     // bandit
        WINDOW_ELT_ANIMATED_SPRITE_T warrior_lvl_1;     // villager
        WINDOW_ELT_ANIMATED_SPRITE_T warrior_lvl_2;     // spike
        WINDOW_ELT_ANIMATED_SPRITE_T warrior_lvl_3;     // knight
        WINDOW_ELT_ANIMATED_SPRITE_T warrior_lvl_4;     // heros
        //
        WINDOW_ELT_ANIMATED_SPRITE_T building_lvl_1_no_color;    // bandit camp
        WINDOW_ELT_ANIMATED_SPRITE_T building_lvl_1;    // town
        WINDOW_ELT_ANIMATED_SPRITE_T building_lvl_2;    // tower
        //
        WINDOW_ELT_SPRITE_T barricade_top;
        WINDOW_ELT_SPRITE_T barricade_top_right;
        WINDOW_ELT_SPRITE_T barricade_top_left;
        WINDOW_ELT_SPRITE_T barricade_bottom_right;
        WINDOW_ELT_SPRITE_T barricade_bottom_left;
        WINDOW_ELT_SPRITE_T barricade_bottom;
        //
        double cam_x = 0;
        double cam_y = 0;
        double zoom = 1.1;
        //
        Coord mouse_hover_tile = (Coord){1, 1};
        //
        int current_color_to_play = 1;
        //
        bool dragging_entity = false;
        bool dragging_new_entity = true;
        EntityData entity_dragged = (EntityData){4, true};
        Coord tile_entity_dragged = (Coord){0, 0};
        //
        WINDOW_ELT_SPRITE_T sprite_map_creator_cursor;
        std::string map_creator_cursor = "";
        int map_creator_elt_category = 0;   // 0 = non, 1 = tiles, 2 = colors, 3 = entities
        int map_creator_elt_id = -1;
        Color map_creator_elt_color_mod = (Color){255, 255, 255};
        //
        PROVINCE_T selected_province = nullptr;
        //
        std::set<Coord> can_go_here_tiles;
        //
        std::map<Coord, Color> debug_colors;
        //
        GameModel* game_model = nullptr;
        //
        WINDOW_ELT_RECT_T rect_current_player = nullptr;
        WINDOW_ELT_TEXT_T txt_current_player = nullptr;
        //
        WINDOW_ELT_TEXT_T elt_province_1 = nullptr;
        WINDOW_ELT_SPRITE_T elt_province_2 = nullptr;
        WINDOW_ELT_TEXT_T txt_province_treasury = nullptr;
        WINDOW_ELT_TEXT_T txt_province_expected_income = nullptr;
        //
        WINDOW_ELT_BUTTON_T bt_unit_lvl1 = nullptr;
        WINDOW_ELT_TEXT_T txt_unit_lvl1 = nullptr;
        WINDOW_ELT_BUTTON_T bt_unit_lvl2 = nullptr;
        WINDOW_ELT_TEXT_T txt_unit_lvl2 = nullptr;
        WINDOW_ELT_BUTTON_T bt_unit_lvl3 = nullptr;
        WINDOW_ELT_TEXT_T txt_unit_lvl3 = nullptr;
        WINDOW_ELT_BUTTON_T bt_unit_lvl4 = nullptr;
        WINDOW_ELT_TEXT_T txt_unit_lvl4 = nullptr;
        WINDOW_ELT_BUTTON_T bt_building_lvl2 = nullptr;
        WINDOW_ELT_TEXT_T txt_building_lvl2 = nullptr;

        // Constructor
        WindowEltMapViewer( STYLE_T style,
            VALUE_T x,
            VALUE_T y,
            VALUE_T w,
            VALUE_T h,
            std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)> on_click = nullptr
        );

        // Functions : darw
        void draw_ground_tile(Coord coord, MainView* main_view, DRAW_TRANSFORM_T transform, int color,
                              VALUE_INT_T dep_x, VALUE_INT_T dep_y, int zoomed_W, int zoomed_H, int A, int B);

        void draw_color_tile(Coord coord, MainView* main_view, DRAW_TRANSFORM_T transform, int color,
                             VALUE_INT_T dep_x, VALUE_INT_T dep_y, int zoomed_W, int zoomed_H, int A, int B);

        void draw_entity_sprite(EntityData edata, MainView* main_view, DRAW_TRANSFORM_T transform, int color);

        void draw_entity(Coord coord, MainView* main_view, DRAW_TRANSFORM_T transform, int color,
                         VALUE_INT_T dep_x, VALUE_INT_T dep_y, int zoomed_W, int zoomed_H, int A, int B);

        void draw_barricade(Coord coord, MainView* main_view, DRAW_TRANSFORM_T transform, int color,
                            VALUE_INT_T dep_x, VALUE_INT_T dep_y, int zoomed_W, int zoomed_H, int A, int B);

        void draw_elt(MainView* main_view, DRAW_TRANSFORM_T transform=nullptr);

        // Other functions
        void clear();

        void add_tile_to_tile_layer( int tile_x, int tile_y, int tile_num );

        void complete_all_tile_layer_ground_base();

        // Getters
        std::vector< Coord > get_adjacents_tiles_coords_to_tile(int x, int y);
        std::vector< std::string > get_adjacents_tiles_base_ground_to_tile(int x, int y);
        WINDOW_ELT_MAP_TILE_T get_layer_tile_at_coord(Coord coord);
        EntityData get_entity_data_at_coord(Coord coord);
        int get_color_at_coord(Coord coord);

        // Other functions
        void zoom_at_point(double mouse_x, double mouse_y, float zoom_factor);

        void update_mouse_hover_tile(Coord mouse_pos);

        void drag_entity(Coord tile_to_drag);

        void stop_dragging_entity();

        // Functions : check_draw
        bool check_draw_palissade_between_to_tiles(Coord v1, Coord v2);
        bool check_draw_palissade_top(Coord v);
        bool check_draw_palissade_top_right(Coord v);
        bool check_draw_palissade_top_left(Coord v);
        bool check_draw_palissade_bottom(Coord v);
        bool check_draw_palissade_bottom_left(Coord v);
        bool check_draw_palissade_bottom_right(Coord v);
};


void on_map_viewer_click(WINDOW_ELT_CLICKABLE_T map_viewer_elt, MainGame* main_game, std::vector<std::string> additional_fn_args);

