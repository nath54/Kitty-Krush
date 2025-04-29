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
        WindowEltMapViewer* map_viewer = nullptr;

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
        WindowAttributes* get_win_attr();

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
        WindowAttributes* win_attr;

        // Constructor
        ValuePercentWinWidth(WindowAttributes* win_attr, float percent, int shift = 0)
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
        WindowAttributes* win_attr;

        // Constructor
        ValuePercentWinHeight(WindowAttributes* win_attr, float percent, int shift = 0)
            : win_attr(win_attr), percent(percent), shift(shift) {}

        // Getter
        int get_value();
};


ValueInt* nvi(int value);

ValuePercent* nvp(float percent);

ValuePercentWinWidth* nvpww(WindowAttributes* win_attr, float prc, int shift=0);

ValuePercentWinHeight* nvpwh(WindowAttributes* win_attr, float prc, int shift=0);


class DrawTransform {

    public:

        // Attributes
        Value* translation_x = nullptr;
        Value* translation_y = nullptr;
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
            Value* translation_x = nullptr,
            Value* translation_y = nullptr,
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
        Value* x;
        Value* y;
        Value* w;
        Value* h;
        //
        bool visible = true;
        //
        Style* style;

        // Constructor
        WindowElt( Style* style,
                   Value* x,
                   Value* y,
                   Value* w = new ValueInt(1),
                   Value* h = new ValueInt(1)
                )
            : style(style), x(x), y(y), w(w), h(h) {};

        // Getters
        int get_elt_state(WindowAttributes* win_attr, DrawTransform* transform=nullptr);
        int get_x(DrawTransform* transform=nullptr);
        int get_y(DrawTransform* transform=nullptr);
        int get_w(DrawTransform* transform=nullptr);
        int get_h(DrawTransform* transform=nullptr);

        // Function
        virtual void draw_elt(MainView* main_view, DrawTransform* transform=nullptr);
};


class WindowPage {

    public:

        // Attribute
        std::vector< WindowElt* > elts;

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
        Style* default_style;

        // Constructor
        WindowPagesManager() { this->default_style = new Style(); }

        // Functions
        WindowPage* get_current_page();
        void draw_current_page( MainView* main_view );
        void set_current_page( std::string new_current_page );
};


class WindowEltClickable : public WindowElt {

    public:

        // Attributes
        bool disabled = false;
        std::function<void(WindowEltClickable*, MainGame*, std::vector<std::string>)> on_click = nullptr;
        std::vector<std::string> additional_fn_args;

        // Constructor
        WindowEltClickable(
            Style* style,
            Value* x,
            Value* y,
            Value* w = new ValueInt(-1),
            Value* h = new ValueInt(-1),
            std::function<void(WindowEltClickable*, MainGame*, std::vector<std::string>)> on_click = nullptr,
            std::vector<std::string> additional_fn_args = (std::vector<std::string>){}
         )
        : WindowElt(style, x, y, w, h), on_click(on_click), additional_fn_args(additional_fn_args) {};
};


class WindowEltRect : public WindowElt {

    public:

        // Attributes
        Color cl;
        Value* radius;

        // Constructor
        WindowEltRect( Style* style,
                       Color cl,
                       Value* x,
                       Value* y,
                       Value* w = new ValueInt(-1),
                       Value* h = new ValueInt(-1),
                       Value* radius = new ValueInt(0)
                    )
            : WindowElt(style, x, y, w, h), cl(cl), radius(radius) {};

        // Function
        void draw_elt(MainView* main_view, DrawTransform* transform=nullptr);

};


class WindowEltText : public WindowElt {

    public:

        // Attribute
        std::string txt;

        // Constructor
        WindowEltText( Style* style,
                       std::string txt,
                       Value* x,
                       Value* y,
                       Value* w = new ValueInt(-1),
                       Value* h = new ValueInt(-1)
                    )
            : WindowElt(style, x, y, w, h), txt(txt) {};

        // Function
        void draw_elt(MainView* main_view, DrawTransform* transform=nullptr);
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
        ValuePercent* src_x;
        ValuePercent* src_y;
        ValuePercent* src_w;
        ValuePercent* src_h ;

        // Constructor
        SpriteCropValuePercent(
            ValuePercent* src_x,
            ValuePercent* src_y,
            ValuePercent* src_w,
            ValuePercent* src_h
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


SpriteCropValuePercent* SPRITE_NO_CROP();

SpriteCropValuePercent* SPRITE_CUSTOM_CROP(float src_x, float src_y, float src_w, float src_h);


class SpriteRatio {

    public:

        // Attributes
        bool keep_original;
        ValuePercent* prc_dest_w;
        ValuePercent* prc_dest_h;

        // Constructor
        SpriteRatio(
            bool keep_original,
            ValuePercent* prc_dest_w,
            ValuePercent* prc_dest_h
        )
            : keep_original(keep_original), prc_dest_w(prc_dest_w), prc_dest_h(prc_dest_h) {}

};


SpriteRatio* SPRITE_RATIO_ORIGINAL();

SpriteRatio* SPRITE_RATIO_CUSTOM(float prc_dest_w, float prc_dest_h);


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


SpriteResize* SPRITE_RESIZE_KEEP_ORIGINAL(float resize_factor = 1.0);

SpriteResize* SPRITE_RESIZE_FIT(float resize_factor = 1.0);

SpriteResize* SPRITE_RESIZE_COVER(float resize_factor = 1.0);


class SpritePosition {

    public:

        // Attributes
        float percent;
        int delta;

        // Constructor
        SpritePosition(float percent, int delta): percent(percent), delta(delta) {}
};


SpritePosition* SPRITE_POS_ALIGN_START();

SpritePosition* SPRITE_POS_ALIGN_CENTER();

SpritePosition* SPRITE_POS_ALIGN_END();

SpritePosition* SPRITE_POS_CUSTOM(float percent, int delta);


class WindowEltSprite : public WindowElt {

    public:

        // Attributes
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

        // Constructor
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

        // Function
        void draw_elt(MainView* main_view, DrawTransform* transform=nullptr);
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
        WindowEltSprite* sprite;
        //
        SpriteCropInt* sprite_crop;

        // Constructor
        WindowEltAnimatedSprite( Style* style,
                                 std::string img_path,
                                 Value* x,
                                 Value* y,
                                 Value* w,
                                 Value* h,
                                 int first_frame_x,
                                 int first_frame_y,
                                 int frame_w,
                                 int frame_h,
                                 int nb_frames,
                                 uint32_t frame_delay,
                                 Value* angle = new ValueInt(0),
                                 bool flip_h = false,
                                 bool flip_v = false,
                                 SpriteRatio* sprite_ratio = SPRITE_RATIO_ORIGINAL(),
                                 SpriteResize* sprite_resize = SPRITE_RESIZE_KEEP_ORIGINAL(),
                                 SpritePosition* sprite_h_position = SPRITE_POS_ALIGN_START(),
                                 SpritePosition* sprite_v_position = SPRITE_POS_ALIGN_START()
                                );

        // Function
        void draw_elt(MainView* main_view, DrawTransform* transform=nullptr);
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
        WindowEltSprite* bt_sprite = nullptr;

        // Constructor
        WindowEltButton( Style* style,
                         std::string txt,
                         Value* x,
                         Value* y,
                         Value* w,
                         Value* h,
                         std::function<void(WindowEltClickable*, MainGame*, std::vector<std::string>)> on_click = nullptr,
                         std::vector<std::string> additional_fn_args = (std::vector<std::string>){}
                        );

        // Function
        void draw_elt(MainView* main_view, DrawTransform* transform=nullptr);
};


class WindowEltMapTile: public WindowElt {

    public:

        // Attributes
        int tile;
        //
        WindowEltSprite* ground_base_layer = nullptr;
        WindowEltSprite* ground_top_layer = nullptr;
        //
        bool ground_base_to_complete = false;

        // Constructor
        WindowEltMapTile(
            int tile,
            Style* style,
            Value* x,
            Value* y,
            Value* w,
            Value* h
        );

        // Functions
        void draw_elt(MainView* main_view, DrawTransform* transform=nullptr);
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
        std::map< Coord, WindowEltMapTile* > tiles_layers;
        //
        // WindowEltSprite* default_empty_tile;
        WindowEltAnimatedSprite* default_empty_tile;
        WindowEltSprite* color_tile;
        WindowEltAnimatedSprite* under_entity_effect;
        WindowEltAnimatedSprite* can_go_here_effect;


        // ! TODO: sprites for all entities

        //
        WindowEltAnimatedSprite* warrior_lvl_0;     // bandit
        WindowEltAnimatedSprite* warrior_lvl_1;     // villager
        WindowEltAnimatedSprite* warrior_lvl_2;     // spike
        WindowEltAnimatedSprite* warrior_lvl_3;     // knight
        WindowEltAnimatedSprite* warrior_lvl_4;     // heros
        //
        WindowEltAnimatedSprite* building_lvl_1_no_color;    // bandit camp
        WindowEltAnimatedSprite* building_lvl_1;    // town
        WindowEltAnimatedSprite* building_lvl_2;    // tower
        //
        WindowEltSprite* barricade_top;
        WindowEltSprite* barricade_top_right;
        WindowEltSprite* barricade_top_left;
        WindowEltSprite* barricade_bottom_right;
        WindowEltSprite* barricade_bottom_left;
        WindowEltSprite* barricade_bottom;
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
        WindowEltSprite* sprite_map_creator_cursor;
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
        WindowEltRect* rect_current_player = nullptr;
        WindowEltText* txt_current_player = nullptr;
        //
        WindowEltText* elt_province_1 = nullptr;
        WindowEltSprite* elt_province_2 = nullptr;
        WindowEltText* txt_province_treasury = nullptr;
        WindowEltText* txt_province_expected_income = nullptr;
        //
        WindowEltButton* bt_unit_lvl1 = nullptr;
        WindowEltText* txt_unit_lvl1 = nullptr;
        WindowEltButton* bt_unit_lvl2 = nullptr;
        WindowEltText* txt_unit_lvl2 = nullptr;
        WindowEltButton* bt_unit_lvl3 = nullptr;
        WindowEltText* txt_unit_lvl3 = nullptr;
        WindowEltButton* bt_unit_lvl4 = nullptr;
        WindowEltText* txt_unit_lvl4 = nullptr;
        WindowEltButton* bt_building_lvl2 = nullptr;
        WindowEltText* txt_building_lvl2 = nullptr;

        // Constructor
        WindowEltMapViewer( Style* style,
            Value* x,
            Value* y,
            Value* w,
            Value* h,
            std::function<void(WindowEltClickable*, MainGame*, std::vector<std::string>)> on_click = nullptr
        );

        // Functions : darw
        void draw_ground_tile(Coord coord, MainView* main_view, DrawTransform* transform, int color,
                              ValueInt* dep_x, ValueInt* dep_y, int zoomed_W, int zoomed_H, int A, int B);

        void draw_color_tile(Coord coord, MainView* main_view, DrawTransform* transform, int color,
                             ValueInt* dep_x, ValueInt* dep_y, int zoomed_W, int zoomed_H, int A, int B);

        void draw_entity_sprite(EntityData edata, MainView* main_view, DrawTransform* transform, int color);

        void draw_entity(Coord coord, MainView* main_view, DrawTransform* transform, int color,
                         ValueInt* dep_x, ValueInt* dep_y, int zoomed_W, int zoomed_H, int A, int B);

        void draw_barricade(Coord coord, MainView* main_view, DrawTransform* transform, int color,
                            ValueInt* dep_x, ValueInt* dep_y, int zoomed_W, int zoomed_H, int A, int B);

        void draw_elt(MainView* main_view, DrawTransform* transform=nullptr);

        // Other functions
        void clear();

        void add_tile_to_tile_layer( int tile_x, int tile_y, int tile_num );

        void complete_all_tile_layer_ground_base();

        // Getters
        std::vector< Coord > get_adjacents_tiles_coords_to_tile(int x, int y);
        std::vector< std::string > get_adjacents_tiles_base_ground_to_tile(int x, int y);
        WindowEltMapTile* get_layer_tile_at_coord(Coord coord);
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


void on_map_viewer_click(WindowEltClickable* map_viewer_elt, MainGame* main_game, std::vector<std::string> additional_fn_args);

