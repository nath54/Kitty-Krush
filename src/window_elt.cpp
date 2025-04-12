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


//
void WindowPage::draw_page(MainView* main_view){

    // Draw each element
    for ( WindowElt* elt : this->elts ) {
        //
        elt->draw_elt(main_view, nullptr);
    }

}


//
WindowPage* WindowPagesManager::get_current_page(){

    //
    if( this->pages.find(this->current_page) == this->pages.end() ){
        return nullptr;
    }

    //
    return this->pages[this->current_page];

}


//
void WindowPagesManager::draw_current_page( MainView* main_view ){

    //
    if( this->pages.find(this->current_page) == this->pages.end() ){
        return;
    }

    //
    this->pages[this->current_page]->draw_page(main_view);

}


//
void WindowPagesManager::set_current_page( std::string new_current_page ){
    //
    this->current_page = new_current_page;
}


//
int Value::get_value(){
    //
    return -2;
}

//
int ValueInt::get_value(){
    //
    return this->value;
}

//
float ValuePercent::get_value(){
    //
    return this->percent;
}

//
int ValuePercent::get_value_scaled(int value){
    //
    return (int)(this->percent * ((float)value) ) ;
}


//
int ValuePercentWinWidth::get_value(){
    //
    return (int)(this->percent * this->win_attr->win_width / 100.0 );
}


//
int ValuePercentWinHeight::get_value(){
    //
    return (int)(this->percent * this->win_attr->win_height / 100.0 );
}


//
ValueInt* nvi(int value){
    return new ValueInt(value);
}


//
ValuePercent* nvp(float percent){
    return new ValuePercent(percent);
}

//
ValuePercentWinWidth* nvpww(float prc, WindowAttributes* win_attr){
    return new ValuePercentWinWidth(prc, win_attr);
}

//
ValuePercentWinHeight* nvpwh(float prc, WindowAttributes* win_attr){
    return new ValuePercentWinHeight(prc, win_attr);
}


//
SpriteCropValuePercent* SPRITE_NO_CROP(){
    //
    return new SpriteCropValuePercent( nvp(0), nvp(0), nvp(1), nvp(1) );
}

//
SpriteCropValuePercent* SPRITE_CUSTOM_CROP(float src_x, float src_y, float src_w, float src_h){
    //
    return new SpriteCropValuePercent( nvp(src_x), nvp(src_y), nvp(src_w), nvp(src_h) );
}


//
SpriteRatio* SPRITE_RATIO_ORIGINAL(){
    //
    return new SpriteRatio(true, nullptr, nullptr);
}

//
SpriteRatio* SPRITE_RATIO_CUSTOM(float prc_dest_w, float prc_dest_h){
    //
    return new SpriteRatio(false, nvp(prc_dest_w), nvp(prc_dest_h));
}


//
SpriteResize* SPRITE_RESIZE_KEEP_ORIGINAL(float resize_factor){
    //
    return new SpriteResize(SPRITE_ENUM_RESIZE_KEEP_ORIGINAL, resize_factor);
}

//
SpriteResize* SPRITE_RESIZE_FIT(float resize_factor){
    //
    return new SpriteResize(SPRITE_ENUM_RESIZE_FIT, resize_factor);
}

//
SpriteResize* SPRITE_RESIZE_COVER(float resize_factor){
    //
    return new SpriteResize(SPRITE_ENUM_RESIZE_COVER, resize_factor);
}

//
SpritePosition* SPRITE_POS_ALIGN_START(){
    //
    return new SpritePosition(0, 0);
}

//
SpritePosition* SPRITE_POS_ALIGN_CENTER(){
    //
    return new SpritePosition(0.5, 0);
}

//
SpritePosition* SPRITE_POS_ALIGN_END(){
    //
    return new SpritePosition(1, 0);
}

//
SpritePosition* SPRITE_POS_CUSTOM(float percent, int delta){
    //
    return new SpritePosition(percent, delta);
}


//
int WindowElt::get_elt_state(WindowAttributes* win_attr, DrawTransform* transform){

    //
    int rx = this->get_x(transform);
    int ry = this->get_y(transform);
    int rw = this->get_w(transform);
    int rh = this->get_h(transform);

    //
    if ( is_point_in_rect(win_attr->mouse_x, win_attr->mouse_y, rx, ry, rw, rh) ) {

        //
        if( win_attr->mouse_left_bt_clicked > 0 ){

            //
            return STYLE_ELT_CLICKED;

        }

        //
        return STYLE_ELT_HOVER;

    }

    //
    return STYLE_ELT_BASE;

}

//
int WindowElt::get_x(DrawTransform* transform){
    //
    int res = this->x->get_value();
    //
    if(transform != nullptr && transform->translation_x != nullptr){
        res += transform->translation_x->get_value();
    }
    //
    return res;
}

//
int WindowElt::get_y(DrawTransform* transform){
    //
    int res = this->y->get_value();
    //
    if(transform != nullptr && transform->translation_y != nullptr){
        res += transform->translation_y->get_value();
    }
    //
    return res;
}

//
int WindowElt::get_w(DrawTransform* transform){
    //
    int res = this->w->get_value();
    //
    if(transform != nullptr){
        res = (int)( ((float)res) * transform->scale_w );
    }
    //
    return res;
}

//
int WindowElt::get_h(DrawTransform* transform){
    //
    int res = this->h->get_value();
    //
    if(transform != nullptr){
        res = (int)( ((float)res) * transform->scale_h );
    }
    //
    return res;
}

//
void WindowElt::draw_elt(MainView* main_view, DrawTransform* transform){

    // Template abstract class

}



//
void WindowEltText::draw_elt(MainView* main_view, DrawTransform* transform){

    //
    int elt_state = this->get_elt_state( main_view->get_win_attr(), transform );

    //
    Color cl = this->style->get_fg_color( elt_state );
    int font_size = this->style->get_font_size( elt_state );

    //
    int x = this->get_x(transform);
    int y = this->get_y(transform);
    int w = this->get_w(transform);
    int h = this->get_h(transform);

    //
    main_view->draw_text( this->txt, cl, font_size, x, y, w, h );

}



//
void WindowEltButton::draw_elt(MainView* main_view, DrawTransform* transform){

    //
    int elt_state = this->get_elt_state( main_view->get_win_attr(), transform );

    //
    Color fg_cl = this->style->get_fg_color( elt_state );
    Color bg_cl = this->style->get_bg_color( elt_state );
    int radius = this->style->get_radius( elt_state );
    int font_size = this->style->get_font_size( elt_state );

    //
    int x = this->get_x(transform);
    int y = this->get_y(transform);
    int w = this->get_w(transform);
    int h = this->get_h(transform);

    //
    int w2 = (int) w / 2;
    int h2 = (int) h / 2;

    //
    if (radius > w2){
        radius = w2;
    }
    //
    if (radius > h2){
        radius = h2;
    }

    //
    main_view->draw_button_1( x, y, w, h, this->txt, fg_cl, bg_cl, font_size, radius );

}



//
void WindowEltSprite::draw_elt(MainView* main_view, DrawTransform* transform){

    //
    // int elt_state = this->get_elt_state( main_view->get_win_attr(), transform );

    SDL_Texture* texture = main_view->get_texture(img_path);
    //

    //
    int dest_x = this->get_x(transform);
    int dest_y = this->get_y(transform);
    int dest_w = this->get_w(transform);
    int dest_h = this->get_h(transform);

    //
    int f_dest_x = dest_x;
    int f_dest_y = dest_y;
    int f_dest_w = dest_w;
    int f_dest_h = dest_h;

    //
    int base_src_w, base_src_h;
    SDL_QueryTexture(texture, nullptr, nullptr, &base_src_w, &base_src_h);
    //
    int src_x = 0;
    int src_y = 0;
    int src_w = base_src_w;
    int src_h = base_src_h;

    //
    int angle = this->angle->get_value();

    // CROP

    if( this->sprite_crop != nullptr ){

        //
        SpriteCropInt* sprite_crop_int = dynamic_cast<SpriteCropInt*>(this->sprite_crop);
        SpriteCropValuePercent* sprite_crop_vp = dynamic_cast<SpriteCropValuePercent*>(this->sprite_crop);

        //
        if (sprite_crop_int != nullptr){

            src_x = sprite_crop_int->src_x;
            src_y = sprite_crop_int->src_y;
            src_w = sprite_crop_int->src_w;
            src_h = sprite_crop_int->src_h;

        }

        //
        else if (sprite_crop_vp != nullptr){

            //
            if( sprite_crop_vp->src_x != nullptr ){
                src_x = sprite_crop_vp->src_x->get_value_scaled(base_src_w);
            }

            //
            if( sprite_crop_vp->src_y != nullptr ){
                src_y = sprite_crop_vp->src_y->get_value_scaled(base_src_h);
            }

            //
            if( sprite_crop_vp->src_w != nullptr ){
                src_w = sprite_crop_vp->src_w->get_value_scaled(base_src_w);
            }

            //
            if( sprite_crop_vp->src_h != nullptr ){
                src_h = sprite_crop_vp->src_h->get_value_scaled(base_src_h);
            }

        }

    }

    // CROP CLAMPING

    //
    if(src_x < 0){ src_x = 0; }
    if(src_y < 0){ src_y = 0; }
    if(src_x >= base_src_w){ src_x = base_src_w - 1; }
    if(src_x >= base_src_w){ src_x = base_src_w - 1; }
    //
    if( src_w > base_src_w - src_x ){ src_w = base_src_w - src_x; }
    if( src_h > base_src_h - src_y ){ src_h = base_src_h - src_y; }

    // RATIO

    if( this->sprite_ratio != nullptr){

        // Keep original source ratio for final destination ratio
        if( this->sprite_ratio->keep_original ){

            //
            f_dest_w = src_w;
            f_dest_h = src_h;

        }

        // Multiply final destination ratio from base rect destination ratio
        else{

            //
            if( this->sprite_ratio->prc_dest_w != nullptr ){

                //
                f_dest_w = this->sprite_ratio->prc_dest_w->get_value_scaled( dest_w );

            }

            //
            if( this->sprite_ratio->prc_dest_h != nullptr ){

                //
                f_dest_h = this->sprite_ratio->prc_dest_h->get_value_scaled( dest_h );

            }

        }

    }

    // Check image dimensions
    if( f_dest_h == 0 || f_dest_w == 0 || dest_w == 0 || dest_h == 0 ){
        return;
    }

    // RESIZE

    //
    if( this->sprite_resize != nullptr ){

        // Get the source and destination ratios
        float src_ratio = (float) f_dest_w / (float) f_dest_h;
        float dst_ratio = (float) dest_w / (float) dest_h;

        // Keep original dimensions
        if( this->sprite_resize->mode == SPRITE_ENUM_RESIZE_KEEP_ORIGINAL ){

            // Do nothing, keep original dimensions

        }

        // Fit = all the image must be within the destination rectangle, there can be empty pixels
        else if( this->sprite_resize->mode == SPRITE_ENUM_RESIZE_FIT ){

            //
            if( src_ratio > dst_ratio ){

                //
                f_dest_w = dest_w;
                f_dest_h = (int) ((float) f_dest_w / src_ratio);

            }
            //
            else{

                //
                f_dest_h = dest_h;
                f_dest_w = (int) ((float) f_dest_h * src_ratio);

            }

        }

        // Cover = all the destination rectangle must fit inside the image, there can't be empty pixels
        else if( this->sprite_resize->mode == SPRITE_ENUM_RESIZE_COVER ){

            //
            if( src_ratio < dst_ratio ){

                //
                f_dest_w = dest_w;
                f_dest_h = (int) ((float) f_dest_w / src_ratio);

            }
            //
            else{

                //
                f_dest_h = dest_h;
                f_dest_w = (int) ((float) f_dest_h * src_ratio);

            }

        }

        // Global resize factor (by default to 1.0 )
        f_dest_w = (int) ( (float) f_dest_w * this->sprite_resize->resize_factor );
        f_dest_h = (int) ( (float) f_dest_h * this->sprite_resize->resize_factor );

    }

    // POSITION

    // Horizontal
    if( this->sprite_h_position != nullptr ){

        //
        f_dest_x = dest_x + (int) ( (float) (dest_w - f_dest_w) * this->sprite_h_position->percent) + this->sprite_v_position->delta;

    }

    // Horizontal
    if( this->sprite_v_position != nullptr ){

        //
        f_dest_y = dest_y + (int) ( (float) (dest_h - f_dest_h) * this->sprite_v_position->percent) + this->sprite_v_position->delta;

    }

    // COLOR MOD

    //
    bool do_color_mod = false;
    Color color_mod = (Color){255, 255, 255};
    //
    if (transform != nullptr && transform->do_color_mod){
        do_color_mod = true;
        color_mod = transform->color_mod;
    }

    //
    main_view->draw_image( texture, src_x, src_y, src_w, src_h, f_dest_x, f_dest_y, f_dest_w, f_dest_h, angle, this->flip_h, this->flip_v, do_color_mod, color_mod);

}


//
WindowEltAnimatedSprite::WindowEltAnimatedSprite(
    Style* style,
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
    Value* angle,
    bool flip_h,
    bool flip_v,
    SpriteRatio* sprite_ratio,
    SpriteResize* sprite_resize,
    SpritePosition* sprite_h_position,
    SpritePosition* sprite_v_position
)
    : WindowElt(style, x, y, w, h),
      first_frame_x(first_frame_x),
      first_frame_y(first_frame_y),
      frame_w(frame_w),
      frame_h(frame_h),
      nb_frames(nb_frames),
      frame_delay(frame_delay)
{

    //
    this->sprite_crop = new SpriteCropInt(0, 0, frame_w, frame_h);

    //
    this->sprite = new WindowEltSprite(
        style,
        img_path,
        x, y, w, h,
        angle,
        flip_h, flip_v,
        this->sprite_crop,
        sprite_ratio,
        sprite_resize,
        sprite_h_position,
        sprite_v_position
    );

    //
    this->start_time = SDL_GetTicks();

};


//
void WindowEltAnimatedSprite::draw_elt(MainView* main_view, DrawTransform* transform){

    //
    uint32_t time_shift = 0;
    //
    if (transform != nullptr){
        time_shift = transform->time_shift;
    }

    //
    int current_frame = (int) ( ( time_shift + SDL_GetTicks() - this->start_time ) / this->frame_delay ) % this->nb_frames;

    //
    this->sprite_crop->src_x = this->first_frame_x + this->frame_w * current_frame;
    this->sprite_crop->src_y = this->first_frame_y;

    //
    this->sprite->draw_elt(main_view, transform);

}


//
WindowEltMapTile::WindowEltMapTile(int tile, Style* style, Value* x, Value* y, Value* w, Value* h)
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

        //
        if ( allTileData[tile].nb_ground_layer_imgs == 1 ){

            //
            img_path = "res/sprites/map_w/" + std::string(allTileData[tile].ground_layer_img[0]);

        }

        //
        else{

            //
            int selected_img = ( std::rand() % ( allTileData[tile].nb_ground_layer_imgs ) );

            //
            img_path = "res/sprites/map_w/" + std::string(allTileData[tile].ground_layer_img[selected_img]);

        }

        //
        this->ground_base_layer = new WindowEltSprite(
                style,
                img_path,
                this->x, this->y, this->w, this->h,
                new ValueInt(0),
                false,
                false,
                SPRITE_NO_CROP(),
                SPRITE_RATIO_CUSTOM(1, 1),
                SPRITE_RESIZE_COVER(),
                SPRITE_POS_ALIGN_START(),
                SPRITE_POS_ALIGN_START()
        );

    }

    //
    if ( allTileData[tile].nb_top_layer_imgs > 0 ){

        //
        if ( allTileData[tile].nb_top_layer_imgs == 1 ){

            //
            img_path = "res/sprites/map_w/" + std::string(allTileData[tile].ground_layer_img[0]);

        }

        //
        else{

            //
            int selected_img = ( std::rand() % ( allTileData[tile].nb_top_layer_imgs ) );

            //
            img_path = "res/sprites/map_w/" + std::string(allTileData[tile].top_layer_img[selected_img]);

        }

        //
        this->ground_top_layer = new WindowEltSprite(
                style,
                img_path,
                this->x, this->y, this->w, this->h,
                new ValueInt(0),
                false,
                false,
                SPRITE_NO_CROP(),
                SPRITE_RATIO_CUSTOM(1, 1),
                SPRITE_RESIZE_COVER(),
                SPRITE_POS_ALIGN_START(),
                SPRITE_POS_ALIGN_START()
        );

    }

}


//
void WindowEltMapTile::draw_elt(MainView* main_view, DrawTransform* transform){

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
void WindowEltMapTile::set_ground_base(std::string ground_base_img){

    //
    if (this->ground_base_layer != nullptr){

        //
        delete this->ground_base_layer;

    }

    //
    std::string img_path;

    //
    if (ground_base_img.rfind("res/sprites/map_w/", 0) == 0) {
        img_path = ground_base_img;
    }
    else{
        img_path = "res/sprites/map_w/" + ground_base_img;
    }

    //
    this->ground_base_layer = new WindowEltSprite(
        this->style,
        img_path,
        this->x, this->y, this->w, this->h,
        new ValueInt(0),
        false,
        false,
        SPRITE_NO_CROP(),
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

}

//
WindowEltMapViewer::WindowEltMapViewer( Style* style,
    Value* x,
    Value* y,
    Value* w,
    Value* h)
: WindowElt(style, x, y, w, h) {

    //
    // this->default_empty_tile = new WindowEltSprite(
    //     this->style,
    //     "res/sprites/map_w/deep_water.png",
    //     nvi(0), nvi(0), nvi(TILE_IMG_W), nvi(TILE_IMG_H),
    //     nvi(0),
    //     false,
    //     false,
    //     SPRITE_NO_CROP(),
    //     SPRITE_RATIO_CUSTOM(1, 1),
    //     SPRITE_RESIZE_COVER(),
    //     SPRITE_POS_ALIGN_START(),
    //     SPRITE_POS_ALIGN_START()
    // );

    this->default_empty_tile = new WindowEltAnimatedSprite(
        this->style,
        "res/sprites/map_w/deep_water/deep_water.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W), nvi(TILE_IMG_H),
        0, 0, 72, 72, 15, 200,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->color_tile = new WindowEltSprite(
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
    this->warrior_lvl_0 = new WindowEltAnimatedSprite(
        this->style,
        "res/sprites/entities/bandit.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W), nvi(TILE_IMG_H),
        0, 0, 220, 220, 9, 100,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->warrior_lvl_1 = new WindowEltAnimatedSprite(
        this->style,
        "res/sprites/entities/cat_lvl1.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W), nvi(TILE_IMG_H),
        0, 0, 256, 256, 1, 100,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->warrior_lvl_2 = new WindowEltAnimatedSprite(
        this->style,
        "res/sprites/entities/cat_lvl2.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W), nvi(TILE_IMG_H),
        0, 0, 256, 256, 1, 100,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->warrior_lvl_3 = new WindowEltAnimatedSprite(
        this->style,
        "res/sprites/entities/cat_lvl3.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W), nvi(TILE_IMG_H),
        0, 0, 256, 256, 1, 100,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->warrior_lvl_4 = new WindowEltAnimatedSprite(
        this->style,
        "res/sprites/entities/cat_lvl4.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W), nvi(TILE_IMG_H),
        0, 0, 256, 256, 6, 75,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->building_lvl_1_no_color = new WindowEltAnimatedSprite(
        this->style,
        "res/sprites/entities/bandit_camp.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W), nvi(TILE_IMG_H),
        0, 0, 72, 72, 1, 100,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->building_lvl_1 = new WindowEltAnimatedSprite(
        this->style,
        "res/sprites/entities/village.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W), nvi(TILE_IMG_H),
        0, 0, 96, 96, 1, 100,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->building_lvl_2 = new WindowEltAnimatedSprite(
        this->style,
        "res/sprites/entities/tower.png",
        nvi(0), nvi(0), nvi(TILE_IMG_W), nvi(TILE_IMG_H),
        0, 0, 54, 54, 1, 100,
        nvi(0),
        false,
        false,
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

    //
    this->barricade_top = new WindowEltSprite(
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
    this->barricade_top_right = new WindowEltSprite(
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
    this->barricade_top_left = new WindowEltSprite(
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
    this->barricade_bottom_right = new WindowEltSprite(
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
    this->barricade_bottom_left = new WindowEltSprite(
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
    this->barricade_bottom = new WindowEltSprite(
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

}


//
void WindowEltMapViewer::draw_elt(MainView* main_view, DrawTransform* transform){

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
    DrawTransform* tile_transform = nullptr;

    //
    int base_dec_x;
    int base_dec_y;
    float base_zoom_w = this->zoom;
    float base_zoom_h = this->zoom;

    //
    ValueInt* dep_x = nvi(0);
    ValueInt* dep_y = nvi(0);

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
    tile_transform = new DrawTransform( dep_x, dep_y, base_zoom_w, base_zoom_h);

    //
    for( int tile_x = start_tile_x ; tile_x <= start_tile_x + nb_cols_to_display; tile_x ++ ){

        //
        for( int tile_y = start_tile_y ; tile_y <= start_tile_y + nb_rows_to_display; tile_y ++ ){

            //
            Coord coord = {tile_x, tile_y};

            //
            dep_x->value = - base_dec_x + tile_x * B;
            //
            if (tile_x % 2 != 0){
                //
                dep_y->value = - base_dec_y + A + tile_y * zoomed_H;
            }
            else{
                //
                dep_y->value = - base_dec_y + tile_y * zoomed_H;
            }


            // GROUND LAYER TILE

            //
            WindowEltMapTile* tile = this->get_layer_tile_at_coord( coord );

            //
            if (tile == nullptr && this->default_empty_tile != nullptr){

                //
                this->default_empty_tile->draw_elt(main_view, tile_transform);

            }
            //
            else{

                //
                tile->draw_elt(main_view, tile_transform);

            }


            // COLOR LAYER TILE

            int color = this->get_color_at_coord( coord );

            if ( color > 0 && color < MAX_COLOR){

                // set the color filter
                tile_transform->do_color_mod = true;
                tile_transform->color_mod = allPlayerColors[color - 1];

                //
                this->color_tile->draw_elt(main_view, tile_transform);

                // remove the color filter
                tile_transform->do_color_mod = false;

            }

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
            if (tile_x % 2 != 0){
                //
                dep_y->value = - base_dec_y + A + tile_y * zoomed_H;
            }
            else{
                //
                dep_y->value = - base_dec_y + tile_y * zoomed_H;
            }


            //
            dep_x->value -= A;
            dep_y->value -= A;

            // TODO: BARRICADES / WALLS
            if (color > 0){
                if(this->check_draw_palissade_top(coord)){
                    this->barricade_top->draw_elt(main_view, tile_transform);
                }
                if(this->check_draw_palissade_top_right(coord)){
                    this->barricade_top_right->draw_elt(main_view, tile_transform);
                }
                if(this->check_draw_palissade_top_left(coord)){
                    this->barricade_top_left->draw_elt(main_view, tile_transform);
                }
                if(this->check_draw_palissade_bottom(coord)){
                    this->barricade_bottom->draw_elt(main_view, tile_transform);
                }
                if(this->check_draw_palissade_bottom_right(coord)){
                    this->barricade_bottom_right->draw_elt(main_view, tile_transform);
                }
                if(this->check_draw_palissade_bottom_left(coord)){
                    this->barricade_bottom_left->draw_elt(main_view, tile_transform);
                }
            }


            //
            dep_x->value += A;
            dep_y->value += A;


            // ENTITY LAYER TILE

            //
            EntityData edata = this->get_entity_data_at_coord( coord );

            //
            if (edata.type){ // Warrior

                //
                if (edata.level == 0){

                    this->warrior_lvl_0->draw_elt(main_view, tile_transform);

                }

                //
                else if (edata.level == 1){

                    this->warrior_lvl_1->draw_elt(main_view, tile_transform);

                }

                //
                else if (edata.level == 2){

                    this->warrior_lvl_2->draw_elt(main_view, tile_transform);

                }

                //
                else if (edata.level == 3){

                    this->warrior_lvl_3->draw_elt(main_view, tile_transform);

                }

                //
                if (edata.level == 4){

                    this->warrior_lvl_4->draw_elt(main_view, tile_transform);

                }

            }
            //
            else{       // Building

                //
                if (edata.level == 1 && color <= 0){

                    this->building_lvl_1_no_color->draw_elt(main_view, tile_transform);

                }
                //
                else if(edata.level == 1 && color > 0){

                    this->building_lvl_1->draw_elt(main_view, tile_transform);

                }
                //
                else if(edata.level == 2){

                    this->building_lvl_2->draw_elt(main_view, tile_transform);

                }

            }

        }

    }

}


//
void WindowEltMapViewer::clear(){

    //
    for ( std::pair<const Coord, WindowEltMapTile*> const it : this->tiles_layers ){

        //
        if ( it.second == nullptr ){
            continue;
        }

        //
        delete it.second;

    }

    //
    this->tiles_layers.erase( this->tiles_layers.begin(), this->tiles_layers.end() );

}


//
void WindowEltMapViewer::add_tile_to_tile_layer( int tile_x, int tile_y, int tile_num ){

    //
    Coord v = (Coord){tile_x, tile_y};

    //
    std::map< Coord, WindowEltMapTile*>::iterator res_iter = this->tiles_layers.find( v );
    if( res_iter != this->tiles_layers.end() ){

        // res_iter->first is the key, res_iter->second is the value
        delete res_iter->second;
    }

    //
    this->tiles_layers[v] = new WindowEltMapTile(
        tile_num,
        this->style,
        nvi(0),
        nvi(0),
        nvi(TILE_IMG_W),
        nvi(TILE_IMG_W)
    );

}


//
void WindowEltMapViewer::set_color_to_color_layer ( int tile_x, int tile_y, int color_num ){

    //
    Coord v = (Coord){tile_x, tile_y};

    //
    bool tile_present = (this->colors_layers.count( v ) > 0);

    //
    if ( color_num == -1 ){
        //
        if ( tile_present ){
            //
            this->colors_layers.erase( v );
        }
    }
    else{
        //
        this->colors_layers[v] = color_num;
    }

}


//
void WindowEltMapViewer::set_entity_to_entity_layer ( int tile_x, int tile_y, int entity_level, bool entity_type ){

    //
    Coord v = (Coord){tile_x, tile_y};

    //
    bool tile_present = (this->entity_layers.count( v ) > 0);

    //
    if ( entity_level == -1 ){
        //
        if ( tile_present ){
            //
            this->entity_layers.erase( v );
        }
    }
    else{
        //
        if ( tile_present ){
            this->entity_layers[v].level = entity_level;
            this->entity_layers[v].type = entity_type;
        }
        else{
            this->entity_layers[v] = (EntityData){entity_level, entity_type};
        }
    }

}


//
void WindowEltMapViewer::complete_all_tile_layer_ground_base(){

    //
    Coord case_with_max(0, 0);
    int max_non_null_adj = -1;
    std::vector< std::string > max_adj_ground_base;

    //
    std::list< Coord > cases_with_null;

    // FIRST SEARCH

    //
    for ( std::pair<Coord, WindowEltMapTile*> it_pair : this->tiles_layers ){

        //
        Coord pos = it_pair.first;
        WindowEltMapTile* tile = it_pair.second;

        //
        if ( tile == nullptr ){ continue; }

        //
        if ( tile->ground_base_layer != nullptr ){ continue; }

        //
        cases_with_null.push_back( pos );

        //
        std::vector< std::string > adj_ground_base = this->get_adjacents_tiles_base_ground_to_tile( pos.x, pos.y );

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
        std::map< std::string, int > counts;

        //
        for( std::string ground_base : max_adj_ground_base ){

            //
            if( counts.count(ground_base) == 0 ){
                counts[ground_base] = 1;
            }
            else{
                counts[ground_base] += 1;
            }
        }

        //
        std::string maxi_ground_base;
        int maxi_count = -1;

        //
        for ( std::pair<std::string, int> it_pair : counts ){

            //
            if ( maxi_count == -1 || it_pair.second > maxi_count ){

                maxi_ground_base = it_pair.first;
                maxi_count = it_pair.second;

            }

        }

        //
        WindowEltMapTile* w_tile = get_layer_tile_at_coord( case_with_max );

        //
        if ( w_tile != nullptr ){

            //
            if ( maxi_count == -1 ){

                //
                w_tile->set_ground_base( allTileData[w_tile->tile].ground_layer_img[0] );

            }
            //
            else {

                //
                w_tile->set_ground_base( maxi_ground_base );

            }

        }

        // GET THE NEW TILE TO PROCESS
        max_non_null_adj = -1;

        //
        for ( Coord coord : cases_with_null ){

            //
            std::vector< std::string > adj_ground_base = this->get_adjacents_tiles_base_ground_to_tile( coord.x, coord.y );

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
void WindowEltMapViewer::update_closest_building_of_color(){

    //
    this->closest_building_of_color.clear();

    //
    std::list< Coord > starting_points;

    //
    for( std::pair< Coord, EntityData > it : this->entity_layers ){

        //
        if( it.second.type ){ continue; }

        //
        if( this->colors_layers.count(it.first) == 0){ continue; }

        //
        starting_points.push_back( it.first );

    }

    //
    while (starting_points.size() > 0){

        //
        Coord starting_point = starting_points.front();
        starting_points.pop_front();

        //
        std::list< Coord > to_explore;
        std::list< int > crt_distance;

        //
        to_explore.push_back( starting_point );
        crt_distance.push_back( 0 );

        //
        while ( to_explore.size() > 0 ){

            //
            Coord v = to_explore.front();
            to_explore.pop_front();

            //
            int dist = crt_distance.front();
            crt_distance.pop_front();

            //
            if ( this->closest_building_of_color.count(v) == 0 || this->closest_building_of_color[v] > dist ){
                this->closest_building_of_color[v] = dist;
            }

            //
            for ( Coord vv : this->get_adjacents_colors( v ) ){

                //
                if ( this->closest_building_of_color.count(vv) > 0 && this->closest_building_of_color[vv] < dist + 1 ){
                    continue;
                }

                //
                if ( this->colors_layers[vv] == this->colors_layers[v] ){
                    to_explore.push_back(vv);
                    crt_distance.push_back(dist+1);
                }

            }

        }

    }

}



//
std::list< Coord > WindowEltMapViewer::get_adjacents_colors( Coord v ){

    //
    std::list< Coord > adjacent_tiles;

    //
    Coord coord1 = get_tile_top_to( v );
    Coord coord2 = get_tile_top_right_to( v );
    Coord coord3 = get_tile_top_left_to( v );
    Coord coord4 = get_tile_bottom_to( v );
    Coord coord5 = get_tile_bottom_right_to( v );
    Coord coord6 = get_tile_bottom_left_to( v );

    //
    if ( this->colors_layers.count( coord1 ) ) { adjacent_tiles.push_back( coord1 ); }
    if ( this->colors_layers.count( coord2 ) ) { adjacent_tiles.push_back( coord2 ); }
    if ( this->colors_layers.count( coord3 ) ) { adjacent_tiles.push_back( coord3 ); }
    if ( this->colors_layers.count( coord4 ) ) { adjacent_tiles.push_back( coord4 ); }
    if ( this->colors_layers.count( coord5 ) ) { adjacent_tiles.push_back( coord5 ); }
    if ( this->colors_layers.count( coord6 ) ) { adjacent_tiles.push_back( coord6 ); }

    //
    return adjacent_tiles;

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
std::vector< std::string > WindowEltMapViewer::get_adjacents_tiles_base_ground_to_tile(int x, int y){

    //
    std::vector< Coord > adj_coords = this->get_adjacents_tiles_coords_to_tile(x, y);

    //
    std::vector< std::string > res;

    //
    for( Coord coord : adj_coords ){

        //
        WindowEltMapTile* mt = this->get_layer_tile_at_coord(coord);

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
        res.push_back( mt->ground_base_layer->img_path );

    }

    //
    return res;

}


//
WindowEltMapTile* WindowEltMapViewer::get_layer_tile_at_coord(Coord coord){

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
    if ( this->entity_layers.count( coord ) <= 0 ){

        //
        return (EntityData){-1, false};

    }

    //
    return this->entity_layers[coord];

}


//
int WindowEltMapViewer::get_color_at_coord(Coord coord){

    //
    if ( this->colors_layers.count( coord ) <= 0 ){

        //
        return -1;

    }

    //
    return this->colors_layers[coord];

}


//
void WindowEltMapViewer::zoom_at_point(double mouse_x, double mouse_y, float zoom_factor) {
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
    cam_x = world_x * this->zoom - mouse_x;
    cam_y = world_y * this->zoom - mouse_y;

    // Round to nearest integer to match draw_elt's integer truncation
    cam_x = round(cam_x);
    cam_y = round(cam_y);
}


//
bool WindowEltMapViewer::check_draw_palissade_between_to_tiles(Coord v1, Coord v2){
    //
    if (this->closest_building_of_color.count(v1) == 0 || this->closest_building_of_color[v1] > 1){
        return false;
    }
    //
    if(this->colors_layers.count(v2) == 0 || this->colors_layers[v2] != this->colors_layers[v1]){
        return true;
    }
    //
    if (this->closest_building_of_color.count(v2) == 1 && this->closest_building_of_color[v2] <= 1){
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
