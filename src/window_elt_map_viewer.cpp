//
#include <queue>
#include <map>
#include <vector>
#include <list>
#include <set>
//
#include "geometry.hpp"
#include "map_tiles.hpp"
#include "view.hpp"
//
#include <random>




// MAP TILE


//
WindowEltMapTile::WindowEltMapTile(int tile, STYLE_T style, VALUE_T x, VALUE_T y, VALUE_T w, VALUE_T h)
: WindowElt(style, x, y, w, h), tile(tile)
{
    //
    if ( tile < 0 || tile > 69 ){

        //
        return;

    }

    //
    std::string img_path;

    //
    this->ground_base_layer = nullptr;
    this->ground_top_layer = nullptr;

    //
    if ( allTileData[tile].tags[0] != nullptr  && allTileData[tile].nb_ground_layer_imgs > 0 ){

        this->set_own_ground_base();

    }

    //
    if ( allTileData[tile].nb_top_layer_imgs > 0 ){

        this->set_own_ground_top();

    }

}


//
void WindowEltMapTile::draw_elt(MainView* main_view, DRAW_TRANSFORM_T transform){

    //
    if (!this->visible){ return; }

    //
    if (this->ground_base_layer != nullptr){
        //
        this->ground_base_layer->draw_elt(main_view, transform);
    }

    //
    if (this->ground_top_layer != nullptr){
        //
        this->ground_top_layer->draw_elt(main_view, transform);
    }

}


//
void WindowEltMapTile::set_ground_base(WINDOW_ELT_T ground_sprite_elt){

    //
    this->ground_base_layer = ground_sprite_elt;

}


//
void WindowEltMapTile::set_own_ground_base(){

    //
    if ( allTileData[this->tile].nb_ground_layer_imgs == 0 ){
        return;
    }

    //
    int img_chosen = 0;

    //
    if ( allTileData[this->tile].nb_ground_layer_imgs > 1 ){
        //
        img_chosen = ( std::rand() % ( allTileData[this->tile].nb_ground_layer_imgs ) );
    }

    std::string img_path = "res/sprites/map_w/" + std::string(allTileData[this->tile].ground_layer_img[img_chosen]);
    int nb_frames = allTileData[this->tile].nb_frames_ground_layer_img[img_chosen];

    //
    if( nb_frames == 1 ){

        //
        this->ground_base_layer = CREATE_WINDOW_ELT_SPRITE_T(
            style,
            img_path,
            this->x, this->y, this->w, this->h,
            CREATE_VALUE_INT_T(0),
            false,
            false,
            SPRITE_NO_CROP(),
            SPRITE_RATIO_CUSTOM(1, 1),
            SPRITE_RESIZE_COVER(),
            SPRITE_POS_ALIGN_START(),
            SPRITE_POS_ALIGN_START()
        );

    }
    else{

        this->ground_base_layer = CREATE_WINDOW_ELT_ANIMATED_SPRITE_T(
            style,
            img_path,
            nvi(0), nvi(0), nvi(TILE_IMG_W), nvi(TILE_IMG_H),
            0, 0, 72, 72, nb_frames, 150,
            nvi(0),
            false,
            false,
            SPRITE_RATIO_CUSTOM(1, 1),
            SPRITE_RESIZE_COVER(),
            SPRITE_POS_ALIGN_START(),
            SPRITE_POS_ALIGN_START()
        );

    }
}


//
void WindowEltMapTile::set_own_ground_top(){

    //
    if ( allTileData[this->tile].nb_top_layer_imgs == 0 ){
        return;
    }

    //
    int img_chosen = 0;

    //
    if ( allTileData[this->tile].nb_top_layer_imgs > 1 ){
        //
        img_chosen = ( std::rand() % ( allTileData[this->tile].nb_top_layer_imgs ) );
    }

    std::string img_path = "res/sprites/map_w/" + std::string(allTileData[this->tile].top_layer_img[img_chosen]);
    int nb_frames = allTileData[this->tile].nb_frames_top_layer_img[img_chosen];

    //
    if( nb_frames == 1 ){

        //
        this->ground_top_layer = CREATE_WINDOW_ELT_SPRITE_T(
            style,
            img_path,
            this->x, this->y, this->w, this->h,
            CREATE_VALUE_INT_T(0),
            false,
            false,
            SPRITE_NO_CROP(),
            SPRITE_RATIO_CUSTOM(1, 1),
            SPRITE_RESIZE_COVER(),
            SPRITE_POS_ALIGN_START(),
            SPRITE_POS_ALIGN_START()
        );

    }
    else{

        this->ground_top_layer = CREATE_WINDOW_ELT_ANIMATED_SPRITE_T(
            style,
            img_path,
            nvi(0), nvi(0), nvi(TILE_IMG_W), nvi(TILE_IMG_H),
            0, 0, 72, 72, nb_frames, 150,
            nvi(0),
            false,
            false,
            SPRITE_RATIO_CUSTOM(1, 1),
            SPRITE_RESIZE_COVER(),
            SPRITE_POS_ALIGN_START(),
            SPRITE_POS_ALIGN_START()
        );

    }
}



// MAP VIEWER


//
WindowEltMapViewer::WindowEltMapViewer(
    STYLE_T style,
    VALUE_T x,
    VALUE_T y,
    VALUE_T w,
    VALUE_T h,
    std::function<void(WINDOW_ELT_CLICKABLE_T, MainGame*, std::vector<std::string>)> on_click
)
: WindowEltClickable(style, x, y, w, h, on_click) {

    //
    this->default_empty_tile = CREATE_WINDOW_ELT_ANIMATED_SPRITE_T(
        this->style,
        "res/sprites/map_w/deep_water/deep_water.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W), nvi(TILE_IMG_H),
        0, 0, 72, 72, 15, 150,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->color_tile = CREATE_WINDOW_ELT_SPRITE_T(
        this->style,
        "res/ui/tile_for_color.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W), nvi(TILE_IMG_H),
        nvi(0),
        false,
        false,
        SPRITE_NO_CROP(),
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->under_entity_effect = CREATE_WINDOW_ELT_ANIMATED_SPRITE_T(
        this->style,
        "res/ui/under_entity.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W), nvi(TILE_IMG_H),
        0, 0, 72, 72, 6, 200,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->can_go_here_effect = CREATE_WINDOW_ELT_ANIMATED_SPRITE_T(
        this->style,
        "res/ui/can_go_here.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W), nvi(TILE_IMG_H),
        0, 0, 72, 72, 6, 200,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->warrior_lvl_0 = CREATE_WINDOW_ELT_ANIMATED_SPRITE_T(
        this->style,
        "res/sprites/entities/bandit.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W - ENTITY_MARGIN), nvi(TILE_IMG_H - ENTITY_MARGIN),
        0, 0, 88, 88, 4, 75,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->warrior_lvl_1 = CREATE_WINDOW_ELT_ANIMATED_SPRITE_T(
        this->style,
        "res/sprites/entities/cat_lvl1.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W - ENTITY_MARGIN), nvi(TILE_IMG_H - ENTITY_MARGIN),
        0, 0, 1024, 1024, 1, 75,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->warrior_lvl_2 = CREATE_WINDOW_ELT_ANIMATED_SPRITE_T(
        this->style,
        "res/sprites/entities/cat_lvl2.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W - ENTITY_MARGIN), nvi(TILE_IMG_H - ENTITY_MARGIN),
        0, 0, 1024, 1024, 1, 75,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->warrior_lvl_3 = CREATE_WINDOW_ELT_ANIMATED_SPRITE_T(
        this->style,
        "res/sprites/entities/cat_lvl3.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W - ENTITY_MARGIN), nvi(TILE_IMG_H - ENTITY_MARGIN),
        0, 0, 1024, 1024, 1, 75,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->warrior_lvl_4 = CREATE_WINDOW_ELT_ANIMATED_SPRITE_T(
        this->style,
        "res/sprites/entities/cat_lvl4.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W - ENTITY_MARGIN), nvi(TILE_IMG_H - ENTITY_MARGIN),
        0, 0, 1024, 1024, 1, 75,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->building_lvl_1_no_color = CREATE_WINDOW_ELT_ANIMATED_SPRITE_T(
        this->style,
        "res/sprites/entities/bandit_camp2.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W - ENTITY_MARGIN), nvi(TILE_IMG_H - ENTITY_MARGIN),
        0, 0, 1536, 1536, 1, 100,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->building_lvl_1 = CREATE_WINDOW_ELT_ANIMATED_SPRITE_T(
        this->style,
        "res/sprites/entities/village2.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W - ENTITY_MARGIN), nvi(TILE_IMG_H - ENTITY_MARGIN),
        0, 0, 1280, 1280, 1, 100,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->building_lvl_2 = CREATE_WINDOW_ELT_ANIMATED_SPRITE_T(
        this->style,
        "res/sprites/entities/tower2.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W - ENTITY_MARGIN), nvi(TILE_IMG_H - ENTITY_MARGIN),
        0, 0, 1024, 1024, 1, 100,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->barricade_top = CREATE_WINDOW_ELT_SPRITE_T(
        this->style,
        "res/sprites/barricade/barricade_top.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W * 2), nvi(TILE_IMG_H * 2),
        nvi(0),
        false,
        false,
        SPRITE_NO_CROP(),
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );
    this->barricade_top_right = CREATE_WINDOW_ELT_SPRITE_T(
        this->style,
        "res/sprites/barricade/barricade_top_right.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W * 2), nvi(TILE_IMG_H * 2),
        nvi(0),
        false,
        false,
        SPRITE_NO_CROP(),
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );
    this->barricade_top_left = CREATE_WINDOW_ELT_SPRITE_T(
        this->style,
        "res/sprites/barricade/barricade_top_left.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W * 2), nvi(TILE_IMG_H * 2),
        nvi(0),
        false,
        false,
        SPRITE_NO_CROP(),
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );
    this->barricade_bottom_right = CREATE_WINDOW_ELT_SPRITE_T(
        this->style,
        "res/sprites/barricade/barricade_bottom_right.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W * 2), nvi(TILE_IMG_H * 2),
        nvi(0),
        false,
        false,
        SPRITE_NO_CROP(),
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );
    this->barricade_bottom_left = CREATE_WINDOW_ELT_SPRITE_T(
        this->style,
        "res/sprites/barricade/barricade_bottom_left.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W * 2), nvi(TILE_IMG_H * 2),
        nvi(0),
        false,
        false,
        SPRITE_NO_CROP(),
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );
    this->barricade_bottom = CREATE_WINDOW_ELT_SPRITE_T(
        this->style,
        "res/sprites/barricade/barricade_bottom.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W * 2), nvi(TILE_IMG_H * 2),
        nvi(0),
        false,
        false,
        SPRITE_NO_CROP(),
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    this->sprite_map_creator_cursor = CREATE_WINDOW_ELT_SPRITE_T(
        this->style,
        "res/ui/tile_for_color.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W / 2), nvi(TILE_IMG_H / 2),
        nvi(0),
        false,
        false,
        SPRITE_NO_CROP(),
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    // this->can_go_here_tiles.insert( (Coord){4, 5} );  // TO TEST THE EFFECT

}


//
void WindowEltMapViewer::draw_ground_tile(Coord coord, MainView* main_view, DRAW_TRANSFORM_T transform, int color, VALUE_INT_T dep_x, VALUE_INT_T dep_y, int zoomed_W, int zoomed_H, int A, int B){

    // GROUND LAYER TILE

    //
    WINDOW_ELT_MAP_TILE_T tile = this->get_layer_tile_at_coord( coord );

    //
    if (tile == nullptr && this->default_empty_tile != nullptr){

        //
        this->default_empty_tile->draw_elt(main_view, transform);

    }
    //
    else{

        //
        tile->draw_elt(main_view, transform);

    }
}


//
void WindowEltMapViewer::draw_color_tile(Coord coord, MainView* main_view, DRAW_TRANSFORM_T transform, int color, VALUE_INT_T dep_x, VALUE_INT_T dep_y, int zoomed_W, int zoomed_H, int A, int B){

    // COLOR LAYER TILE

    if ( color > 0 && color < MAX_COLOR){

        // set the color filter
        transform->do_color_mod = true;
        transform->color_mod = allPlayerColors[color - 1];

        //
        this->color_tile->draw_elt(main_view, transform);
        this->color_tile->draw_elt(main_view, transform);

        //
        if( this->selected_province != nullptr && this->selected_province->has_tile(coord) ){
            //
            this->color_tile->draw_elt(main_view, transform);
        }

        // remove the color filter
        transform->do_color_mod = false;

    }

    //
    if( this->can_go_here_tiles.size() > 0 && this->can_go_here_tiles.count(coord) == 0 ){
        //
        transform->do_color_mod = true;
        transform->color_mod = (Color){0, 0, 0};
        this->color_tile->draw_elt(main_view, transform);
        this->color_tile->draw_elt(main_view, transform);
        transform->do_color_mod = false;
    }

}


//
void WindowEltMapViewer::draw_entity_sprite(EntityData edata, MainView* main_view, DRAW_TRANSFORM_T transform, int color){

    //
    if (edata.type){ // Warrior

        //
        if (edata.level == 0){

            this->warrior_lvl_0->draw_elt(main_view, transform);

        }

        //
        else if (edata.level == 1){

            this->warrior_lvl_1->draw_elt(main_view, transform);

        }

        //
        else if (edata.level == 2){

            this->warrior_lvl_2->draw_elt(main_view, transform);

        }

        //
        else if (edata.level == 3){

            this->warrior_lvl_3->draw_elt(main_view, transform);

        }

        //
        if (edata.level == 4){

            this->warrior_lvl_4->draw_elt(main_view, transform);

        }

    }
    //
    else{       // Building

        //
        if (edata.level == 1 && color <= 0){

            this->building_lvl_1_no_color->draw_elt(main_view, transform);

        }
        //
        else if(edata.level == 1 && color > 0){

            this->building_lvl_1->draw_elt(main_view, transform);

        }
        //
        else if(edata.level == 2){

            this->building_lvl_2->draw_elt(main_view, transform);

        }

    }

}


//
void WindowEltMapViewer::draw_entity(Coord coord, MainView* main_view, DRAW_TRANSFORM_T transform, int color, VALUE_INT_T dep_x, VALUE_INT_T dep_y, int zoomed_W, int zoomed_H, int A, int B){

    // ENTITY LAYER TILE

    //
    if( !(this->dragging_entity && !this->dragging_new_entity && coord == this->tile_entity_dragged) ){

        //
        EntityData edata = this->get_entity_data_at_coord( coord );

        //
        //if( this->can_go_here_tiles.count(coord) == 0){
        if( this->can_go_here_tiles.size() == 0){
            //
            if (edata.type && edata.level >= 0){
                //
                transform->do_color_mod = true;
                if (color == this->game_model->_current_player() && edata.level > 0){
                    //
                    if( edata.can_move ){
                        transform->color_mod = (Color){50, 200, 50};
                    }
                    else{
                        transform->color_mod = (Color){30, 30, 30};
                    }
                }
                else{
                    transform->color_mod = (Color){155, 20, 20};
                }
                //
                this->under_entity_effect->draw_elt(main_view, transform);
                //
                transform->do_color_mod = false;
            }
        }

        //
        dep_x->value += this->zoom * ENTITY_MARGIN / 2;
        dep_y->value += this->zoom * ENTITY_MARGIN / 2;

        //
        this->draw_entity_sprite(edata, main_view, transform, color);

        //
        dep_x->value -= this->zoom * ENTITY_MARGIN / 2;
        dep_y->value -= this->zoom * ENTITY_MARGIN / 2;

    }
}


//
void WindowEltMapViewer::draw_barricade(Coord coord, MainView* main_view, DRAW_TRANSFORM_T transform, int color, VALUE_INT_T dep_x, VALUE_INT_T dep_y, int zoomed_W, int zoomed_H, int A, int B){

    // BARRICADES / WALLS

    //
    dep_x->value -= A;
    dep_y->value -= A;

    //
    if (color >= 0){
        if(this->check_draw_palissade_top(coord)){
            this->barricade_top->draw_elt(main_view, transform);
        }
        if(this->check_draw_palissade_top_right(coord)){
            this->barricade_top_right->draw_elt(main_view, transform);
        }
        if(this->check_draw_palissade_top_left(coord)){
            this->barricade_top_left->draw_elt(main_view, transform);
        }
        if(this->check_draw_palissade_bottom(coord)){
            this->barricade_bottom->draw_elt(main_view, transform);
        }
        if(this->check_draw_palissade_bottom_right(coord)){
            this->barricade_bottom_right->draw_elt(main_view, transform);
        }
        if(this->check_draw_palissade_bottom_left(coord)){
            this->barricade_bottom_left->draw_elt(main_view, transform);
        }
    }

    //
    dep_x->value += A;
    dep_y->value += A;

}


//
void WindowEltMapViewer::draw_elt(MainView* main_view, DRAW_TRANSFORM_T transform){

    //
    if (!this->visible){ return; }

    //
    int zoomed_W = TILE_IMG_W * this->zoom;
    int zoomed_H = TILE_IMG_H * this->zoom;
    int A = 36 * this->zoom;
    int B = 53 * this->zoom;

    //
    const int margin = 2;

    //
    int start_tile_x = (int) (this->cam_x / B) - margin;
    int start_tile_y = (int) (this->cam_y / zoomed_H) - margin;

    int nb_cols_to_display = (int) (this->get_w() / A) + margin;
    int nb_rows_to_display = (int) (this->get_h() / B) + margin;

    //
    DRAW_TRANSFORM_T tile_transform = nullptr;

    //
    int base_dec_x;
    int base_dec_y;
    float base_zoom_w = this->zoom;
    float base_zoom_h = this->zoom;

    //
    VALUE_INT_T dep_x = nvi(0);
    VALUE_INT_T dep_y = nvi(0);

    //
    if ( transform == nullptr ){

        //
        base_dec_x = (int) this->cam_x;
        base_dec_y = (int) this->cam_y;
    }
    //
    else{

        //
        base_dec_x = transform->translation_x->get_value() + (int) this->cam_x;
        base_dec_y = transform->translation_y->get_value() + (int) this->cam_y;
        base_zoom_w *= transform->scale_w;
        base_zoom_h *= transform->scale_h;

    }

    //
    tile_transform = CREATE_DRAW_TRANSFORM_T( dep_x, dep_y, base_zoom_w, base_zoom_h);

    //
    for( int tile_x = start_tile_x ; tile_x <= start_tile_x + nb_cols_to_display; tile_x ++ ){

        //
        for( int tile_y = start_tile_y ; tile_y <= start_tile_y + nb_rows_to_display; tile_y ++ ){

            //
            Coord coord = {tile_x, tile_y};

            //
            int color = this->get_color_at_coord( coord );

            //
            dep_x->value = - base_dec_x + tile_x * B;
            //
            if ( pos_mod_2(tile_x) != 0){
                //
                dep_y->value = - base_dec_y + A + tile_y * zoomed_H;
            }
            else{
                //
                dep_y->value = - base_dec_y + tile_y * zoomed_H;
            }

            //
            this->draw_ground_tile(coord, main_view, tile_transform, color, dep_x, dep_y, zoomed_W, zoomed_H, A, B);

            //
            this->draw_color_tile(coord, main_view, tile_transform, color, dep_x, dep_y, zoomed_W, zoomed_H, A, B);

            //
            this->draw_entity(coord, main_view, tile_transform, color, dep_x, dep_y, zoomed_W, zoomed_H, A, B);

        }

    }

    //
    for( int tile_x = start_tile_x ; tile_x <= start_tile_x + nb_cols_to_display; tile_x ++ ){

        //
        for( int tile_y = start_tile_y ; tile_y <= start_tile_y + nb_rows_to_display; tile_y ++ ){

            //
            Coord coord = {tile_x, tile_y};

            //
            int color = this->get_color_at_coord( coord );

            //
            dep_x->value = - base_dec_x + tile_x * B;
            //
            if ( pos_mod_2(tile_x) != 0){
                //
                dep_y->value = - base_dec_y + A + tile_y * zoomed_H;
            }
            else{
                //
                dep_y->value = - base_dec_y + tile_y * zoomed_H;
            }

            //
            this->draw_barricade(coord, main_view, tile_transform, color, dep_x, dep_y, zoomed_W, zoomed_H, A, B);


            //
            if( false && this->debug_colors.count( coord ) > 0 ){

                // set the color filter
                tile_transform->do_color_mod = true;
                tile_transform->color_mod = this->debug_colors[coord];

                //
                this->color_tile->draw_elt(main_view, tile_transform);

                // remove the color filter
                tile_transform->do_color_mod = false;

            }

            //
            if(coord == this->mouse_hover_tile){

                // set the color filter
                tile_transform->do_color_mod = true;
                tile_transform->color_mod = CL_DARK_GREY;

                //
                this->color_tile->draw_elt(main_view, tile_transform);

                // remove the color filter
                tile_transform->do_color_mod = false;

            }

        }
    }

    //
    if( this->dragging_entity ){

        //
        dep_x->value = main_view->win_attr.mouse_x;
        dep_y->value = main_view->win_attr.mouse_y;

        //
        this->draw_entity_sprite(this->entity_dragged, main_view, tile_transform, this->game_model->_current_player());

    }
    //
    else if( this->map_creator_cursor != "" ){

        //
        dep_x->value = main_view->win_attr.mouse_x;
        dep_y->value = main_view->win_attr.mouse_y;

        //
        this->sprite_map_creator_cursor->img_path = this->map_creator_cursor;

        // set the color filter
        tile_transform->do_color_mod = true;
        tile_transform->color_mod = this->map_creator_elt_color_mod;

        //
        this->sprite_map_creator_cursor->draw_elt(main_view, tile_transform);

        // remove the color filter
        tile_transform->do_color_mod = false;

    }

}


//
void WindowEltMapViewer::clear(){

    //
    this->cam_x = 0;
    this->cam_y = 0;
    this->zoom = 1.2;

    //
    for ( std::pair<const Coord, WINDOW_ELT_MAP_TILE_T> const it : this->tiles_layers ){

        //
        if ( it.second == nullptr ){
            continue;
        }

    }

    //
    this->tiles_layers.erase( this->tiles_layers.begin(), this->tiles_layers.end() );

}


//
void WindowEltMapViewer::add_tile_to_tile_layer( int tile_x, int tile_y, int tile_num ){

    //
    Coord v = (Coord){tile_x, tile_y};

    //
    std::map< Coord, WINDOW_ELT_MAP_TILE_T>::iterator res_iter = this->tiles_layers.find( v );

    //
    this->tiles_layers[v] = CREATE_WINDOW_ELT_MAP_TILE_T(
        tile_num,
        this->style,
        nvi(0),
        nvi(0),
        nvi(TILE_IMG_W),
        nvi(TILE_IMG_W)
    );

}

//
void WindowEltMapViewer::complete_all_tile_layer_ground_base(){

    //
    Coord case_with_max(0, 0);
    int max_non_null_adj = -1;
    std::vector< WINDOW_ELT_MAP_TILE_T > max_adj_ground_base;

    //
    std::list< Coord > cases_with_null;

    // FIRST SEARCH

    //
    for ( std::pair<Coord, WINDOW_ELT_MAP_TILE_T> it_pair : this->tiles_layers ){

        //
        Coord pos = it_pair.first;
        WINDOW_ELT_MAP_TILE_T tile = it_pair.second;

        //
        if ( tile == nullptr ){ continue; }

        //
        if ( tile->ground_base_layer != nullptr ){ continue; }

        //
        cases_with_null.push_back( pos );

        //
        std::vector< WINDOW_ELT_MAP_TILE_T > adj_ground_base = this->get_adjacents_tiles_base_ground_to_tile( pos.x, pos.y );

        //
        if( max_non_null_adj == -1 || max_non_null_adj < adj_ground_base.size() ){

            //
            case_with_max = pos;
            max_non_null_adj = adj_ground_base.size();
            max_adj_ground_base = adj_ground_base;

        }

    }

    // WHILE LOOP

    //
    while ( max_non_null_adj != -1 ) {

        // Delete the coordinate that will be processed
        cases_with_null.remove(case_with_max);

        //
        WINDOW_ELT_MAP_TILE_T w_tile = get_layer_tile_at_coord( case_with_max );

        //
        if ( w_tile != nullptr ){

            //
            std::map< int, int > counts;
            std::map< int, WINDOW_ELT_MAP_TILE_T > represents;

            //
            for( WINDOW_ELT_MAP_TILE_T mt : max_adj_ground_base ){

                //
                if( counts.count(mt->tile) == 0 ){
                    counts[mt->tile] = 1;
                    represents[mt->tile] = mt;
                }
                else{
                    counts[mt->tile] += 1;
                }
            }

            //
            int maxi_ground_base;
            int maxi_count = -1;

            //
            for ( std::pair<int, int> it_pair : counts ){

                //
                if ( maxi_count == -1 || it_pair.second > maxi_count ){

                    maxi_ground_base = it_pair.first;
                    maxi_count = it_pair.second;

                }

            }

            //
            if ( maxi_count == -1 ){

                w_tile->set_own_ground_base();

            }
            //
            else {

                //
                w_tile->ground_base_layer = represents[maxi_ground_base]->ground_base_layer;

            }

        }

        // GET THE NEW TILE TO PROCESS
        max_non_null_adj = -1;

        //
        for ( Coord coord : cases_with_null ){

            //
            std::vector< WINDOW_ELT_MAP_TILE_T > adj_ground_base = this->get_adjacents_tiles_base_ground_to_tile( coord.x, coord.y );

            //
            if( max_non_null_adj == -1 || max_non_null_adj < adj_ground_base.size() ){

                //
                case_with_max = coord;
                max_non_null_adj = adj_ground_base.size();
                max_adj_ground_base = adj_ground_base;

            }

        }

    }

}


//
std::vector< Coord > WindowEltMapViewer::get_adjacents_tiles_coords_to_tile(int x, int y){

    //
    std::vector< Coord > adjacent_tiles;

    //
    Coord coord1 = get_tile_top_to( (Coord){x, y} );
    Coord coord2 = get_tile_top_right_to( (Coord){x, y} );
    Coord coord3 = get_tile_top_left_to( (Coord){x, y} );
    Coord coord4 = get_tile_bottom_to( (Coord){x, y} );
    Coord coord5 = get_tile_bottom_right_to( (Coord){x, y} );
    Coord coord6 = get_tile_bottom_left_to( (Coord){x, y} );

    //
    if ( this->tiles_layers.count( coord1 ) ) { adjacent_tiles.push_back( coord1 ); }
    if ( this->tiles_layers.count( coord2 ) ) { adjacent_tiles.push_back( coord2 ); }
    if ( this->tiles_layers.count( coord3 ) ) { adjacent_tiles.push_back( coord3 ); }
    if ( this->tiles_layers.count( coord4 ) ) { adjacent_tiles.push_back( coord4 ); }
    if ( this->tiles_layers.count( coord5 ) ) { adjacent_tiles.push_back( coord5 ); }
    if ( this->tiles_layers.count( coord6 ) ) { adjacent_tiles.push_back( coord6 ); }

    //
    return adjacent_tiles;

}


//
std::vector< WINDOW_ELT_MAP_TILE_T > WindowEltMapViewer::get_adjacents_tiles_base_ground_to_tile(int x, int y){

    //
    std::vector< Coord > adj_coords = this->get_adjacents_tiles_coords_to_tile(x, y);

    //
    std::vector< WINDOW_ELT_MAP_TILE_T > res;

    //
    for( Coord coord : adj_coords ){

        //
        WINDOW_ELT_MAP_TILE_T mt = this->get_layer_tile_at_coord(coord);

        //
        if( mt == nullptr ){

            //
            continue;

        }
        //
        if( mt->ground_base_layer == nullptr ){

            //
            continue;
        }

        //
        res.push_back( mt );

    }

    //
    return res;

}


//
WINDOW_ELT_MAP_TILE_T WindowEltMapViewer::get_layer_tile_at_coord(Coord coord){

    //
    if ( this->tiles_layers.count( coord ) <= 0 ){

        //
        return nullptr;

    }

    //
    return this->tiles_layers[coord];

}



//
EntityData WindowEltMapViewer::get_entity_data_at_coord(Coord coord){

    //
    EntityData entity = (EntityData){-1, false};

    //
    if( this->game_model == nullptr){ return entity; }
    //
    ELEMENT_T elt = this->game_model->get_tile_element( coord );
    //
    if( elt == nullptr){ return entity; }

    //
    entity.level = elt->_defense();
    //
    BUILDING_T building = DCAST_BUILDING_T( elt );
    UNIT_T unit = DCAST_UNIT_T( elt );
    //
    entity.type = (building == nullptr);

    //
    if( unit != nullptr ){
        entity.can_move = unit->can_move;
    }

    //
    return entity;

}


//
int WindowEltMapViewer::get_color_at_coord(Coord coord){

    //
    if( this->game_model == nullptr){ return -1; }
    //
    return this->game_model->get_tile_color( coord );

}


//
void WindowEltMapViewer::update_mouse_hover_tile(Coord mouse_pos){

    //
    double zoomed_W = (double) TILE_IMG_W * this->zoom;
    double zoomed_H = (double) TILE_IMG_H * this->zoom;
    double half_W = zoomed_W / 2.0;
    double half_H = zoomed_H / 2.0;
    double A = 36.0 * this->zoom;
    double B = 53.0 * this->zoom;


    //
    double mx = (double) mouse_pos.x + this->cam_x;
    double my = (double) mouse_pos.y + this->cam_y;

    //
    int lx = (int) ( mx / B );
    //
    if ( lx > 0){
        lx += 1;
    }

    //
    int ly = (int) ( my / zoomed_H );
    //
    if ( ly <= 0){
        ly -= 1;
    }

    //
    if ( pos_mod_2(lx) == 1){
        ly += 1;
    }

    //
    std::vector< Coord > coords;
    std::vector< double > center_x;
    std::vector< double > center_y;

    //
    int minidx = 0;
    double midist = -1;

    //
    Coord c1 = (Coord){lx, ly};
    coords.push_back( c1 );
    center_x.push_back( c1.x * B + half_W );
    center_y.push_back( c1.y * zoomed_H + half_H + pos_mod_2(c1.x) * A );
    //
    Coord c2 = (Coord){lx - 1, ly};
    coords.push_back( c2 );
    center_x.push_back( c2.x * B + half_W );
    center_y.push_back( c2.y * zoomed_H + half_H + pos_mod_2(c2.x) * A );
    //
    Coord c3 = (Coord){lx - 1, ly - 1};
    coords.push_back( c3 );
    center_x.push_back( c3.x * B + half_W );
    center_y.push_back( c3.y * zoomed_H + half_H + pos_mod_2(c3.x) * A );
    //
    Coord c4 = (Coord){lx, ly - 1};
    coords.push_back( c4 );
    center_x.push_back( c4.x * B + half_W );
    center_y.push_back( c4.y * zoomed_H + half_H + pos_mod_2(c4.x) * A );

    //
    for (int i = 0; i < 3; i++){

        //
        double cx = center_x[i];
        double cy = center_y[i];

        //
        double dx = cx - mx;
        double dy = cy - my;
        //
        double d = dx * dx + dy * dy;

        //
        if(midist == -1 || d < midist){
            midist = d;
            minidx = i;
        }

    }

    //
    this->mouse_hover_tile = coords[minidx];

}


//
void WindowEltMapViewer::drag_entity(Coord tile_to_drag){
    //
    this->tile_entity_dragged = tile_to_drag;
    this->dragging_entity = false;
}


//
void WindowEltMapViewer::stop_dragging_entity(){
    //
    this->dragging_entity = false;
}


//
void WindowEltMapViewer::zoom_at_point(double mouse_x, double mouse_y, float zoom_factor) {

    //
    if (this->game_end){ return; }

    // Current world point under mouse
    double world_x = (mouse_x + cam_x) / zoom;  // Simplified, adjust based on your system
    double world_y = (mouse_y + cam_y) / zoom;

    // Apply zoom
    this->zoom *= zoom_factor;

    if (this->zoom < 0.25){
        this->zoom = 0.25;
    }

    else if (this->zoom > 6){
        this->zoom = 6;
    }

    // Update camera to keep world point under mouse
    this->cam_x = world_x * this->zoom - mouse_x;
    this->cam_y = world_y * this->zoom - mouse_y;

}


//
bool has_building_of_color_in_neighbours_or_itself(GameModel* game_model, Coord c, int color){

    //
    BUILDING_T b = DCAST_BUILDING_T( game_model->get_tile_element(c) );

    //
    if( b != nullptr && b->_color() == color ) { return true; }

    //
    for(Coord v : neighbours(c)){

        //
        b = DCAST_BUILDING_T( game_model->get_tile_element(v) );

        //
        if( b == nullptr ){ continue; }

        //
        if( b->_color() == color ) { return true; }

    }

    //
    return false;

}



//
bool WindowEltMapViewer::check_draw_palissade_between_to_tiles(Coord v1, Coord v2){

    //
    int color = this->get_color_at_coord(v1);
    int color2 = this->get_color_at_coord(v2);

    //
    EntityData e1 = this->get_entity_data_at_coord(v1);
    EntityData e2 = this->get_entity_data_at_coord(v2);

    // FOR BANDITS CAMPS

    if( color == 0 ){

        //
        if( e1.level == -1 || e1.type ){
            return false;
        }
        //
        if(color2 != color){
            return true;
        }
        //
        if( e2.level != -1 && !e2.type && color2 == 0 ){
            return false;
        }

        //
        return true;

    }

    // FOR PLAYERS

    //
    if( ! has_building_of_color_in_neighbours_or_itself(this->game_model, v1, color) ){
        return false;
    }

    //
    if( color != color2 ){
        return true;
    }

    //
    if( has_building_of_color_in_neighbours_or_itself(this->game_model, v2, color) ){
        return false;
    }

    //
    return true;
}


//
bool WindowEltMapViewer::check_draw_palissade_top(Coord v){
    //
    return this->check_draw_palissade_between_to_tiles(v, get_tile_top_to(v));
}
//
bool WindowEltMapViewer::check_draw_palissade_top_right(Coord v){
    //
    return this->check_draw_palissade_between_to_tiles(v, get_tile_top_right_to(v));
}
//
bool WindowEltMapViewer::check_draw_palissade_top_left(Coord v){
    //
    return this->check_draw_palissade_between_to_tiles(v, get_tile_top_left_to(v));
}
//
bool WindowEltMapViewer::check_draw_palissade_bottom(Coord v){
    //
    return this->check_draw_palissade_between_to_tiles(v, get_tile_bottom_to(v));
}
//
bool WindowEltMapViewer::check_draw_palissade_bottom_right(Coord v){
    //
    return this->check_draw_palissade_between_to_tiles(v, get_tile_bottom_right_to(v));
}
//
bool WindowEltMapViewer::check_draw_palissade_bottom_left(Coord v){
    //
    return this->check_draw_palissade_between_to_tiles(v, get_tile_bottom_left_to(v));
}


//
void on_map_viewer_click_map_creator(WINDOW_ELT_MAP_VIEWER_T map_viewer, MainGame* main_game, std::vector<std::string> additional_fn_args){

    //
    if(map_viewer == nullptr){ return; }
    if(main_game == nullptr){ return; }

    //
    if ( map_viewer->map_creator_elt_category == 0 ){
        return;
    }

    // TILES
    else if ( map_viewer->map_creator_elt_category == 1 ){

        //
        map_viewer->add_tile_to_tile_layer( map_viewer->mouse_hover_tile.x, map_viewer->mouse_hover_tile.y, map_viewer->map_creator_elt_id );

        //
        map_viewer->complete_all_tile_layer_ground_base();

        // check for colors & update if needed

        //
        if ( allTileData[map_viewer->map_creator_elt_id].global_type == 0 ){

            // Compatible avec couleur dessus, couleur par défaut à 0

            if( main_game->game_model->get_tile_color(map_viewer->mouse_hover_tile) < 0 ){
                main_game->game_model->set_tile_color(map_viewer->mouse_hover_tile, 0);
            }

        }

        //
        else{

            // Pas de couleurs dessus, couleur à -1

            if( main_game->game_model->get_tile_color(map_viewer->mouse_hover_tile) >= 0 ){
                main_game->game_model->set_tile_color(map_viewer->mouse_hover_tile, -1);
            }

            // Pas d'entités dessus aussi

            if( main_game->game_model->get_tile_element(map_viewer->mouse_hover_tile) != nullptr ){
                main_game->game_model->set_tile_element(map_viewer->mouse_hover_tile, -1, false);
            }

        }


    }

    // COLORS
    else if ( map_viewer->map_creator_elt_category == 2 ){

        // Check if it is possible to set color (if the tile num global type == 0)

        if ( map_viewer->tiles_layers.count( map_viewer->mouse_hover_tile ) == 0 ) { return; }

        if ( allTileData[map_viewer->tiles_layers[map_viewer->mouse_hover_tile]->tile].global_type != 0 ) { return; }

        //

        main_game->game_model->set_tile_color(map_viewer->mouse_hover_tile, map_viewer->map_creator_elt_id);

    }

    // ENTITIES
    else if ( map_viewer->map_creator_elt_category == 3 ){

        // Check if it is possible to set entity (if the tile num global type == 0)

        if ( map_viewer->tiles_layers.count( map_viewer->mouse_hover_tile ) == 0 ) { return; }

        if ( allTileData[map_viewer->tiles_layers[map_viewer->mouse_hover_tile]->tile].global_type != 0 ) { return; }

        //

        bool elt_type = map_viewer->map_creator_elt_id > 10;
        int elt_defense = map_viewer->map_creator_elt_id - 10 * (int) elt_type;

        if( map_viewer->map_creator_elt_id == 00 ){
            elt_type = false;
            elt_defense = 1;
        }

        //

        main_game->game_model->set_tile_element(map_viewer->mouse_hover_tile, elt_defense, elt_type);

    }

}


//
void on_map_viewer_click_in_game(WINDOW_ELT_MAP_VIEWER_T map_viewer, MainGame* main_game, std::vector<std::string> additional_fn_args){

    //
    if(map_viewer == nullptr){ return; }
    if(main_game == nullptr){ return; }


    //
    main_game->update_selected_province( map_viewer->mouse_hover_tile );

    //
    if (map_viewer->dragging_entity) {

        //
        map_viewer->dragging_entity = false;

        //
        if (map_viewer->dragging_new_entity){

            // TODO: new entity -> call the model & update the visuals
            main_game->action_new_entity( map_viewer->mouse_hover_tile, map_viewer->entity_dragged.level, map_viewer->entity_dragged.type );
        }
        //
        else{

            // TODO: move entity -> call the model & update the visuals
            main_game->action_move_entity( map_viewer->tile_entity_dragged, map_viewer->mouse_hover_tile );

        }

        //
        // (Coord src, bool new_entity, bool reset, int new_entity_level, int new_entity_type)
        main_game->update_where_entity_can_move(map_viewer->mouse_hover_tile, false, true, map_viewer->entity_dragged.level, map_viewer->entity_dragged.type);

        //
        return;
    }

    //
    EntityData edata = map_viewer->get_entity_data_at_coord( map_viewer->mouse_hover_tile );

    //
    if( !edata.type || edata.level <= 0 ){ return; }

    //
    int color = map_viewer->get_color_at_coord( map_viewer->mouse_hover_tile );

    //
    if ( color != main_game->game_model->_current_player() ){ return; }

    //
    map_viewer->dragging_entity = true;
    map_viewer->dragging_new_entity = false;
    map_viewer->tile_entity_dragged = map_viewer->mouse_hover_tile;
    map_viewer->entity_dragged = edata;

    //
    // main_game->update_where_entity_can_move( map_viewer->tile_entity_dragged );

    // (Coord src, bool new_entity, bool reset, int new_entity_level, int new_entity_type)
    main_game->update_where_entity_can_move(map_viewer->tile_entity_dragged, true, false, map_viewer->entity_dragged.level, map_viewer->entity_dragged.type);


}



//
void on_map_viewer_click(WINDOW_ELT_CLICKABLE_T map_viewer_elt, MainGame* main_game, std::vector<std::string> additional_fn_args){

    //
    WINDOW_ELT_MAP_VIEWER_T map_viewer = DCAST_WINDOW_ELT_MAP_VIEWER_T(map_viewer_elt);
    //
    if (map_viewer->game_end){ return; }

    // IF MAP CREATOR
    if ( main_game->menu_state == 3 ) {
        on_map_viewer_click_map_creator(map_viewer, main_game, additional_fn_args);
    }
    // ELSE
    else if ( main_game->menu_state == 2 ) {
        on_map_viewer_click_in_game(map_viewer, main_game, additional_fn_args);
    }
}
