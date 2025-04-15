//
#include <queue>
#include <map>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <fstream>
#include <random>
//
#include "geometry.hpp"
#include "map_tiles.hpp"
#include "view.hpp"
//



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
void WindowEltRect::draw_elt(MainView* main_view, DrawTransform* transform){

    //
    int x = this->get_x(transform);
    int y = this->get_y(transform);
    int w = this->get_w(transform);
    int h = this->get_h(transform);
    int r = 0;
    if(this->radius != nullptr) { r = this->radius->get_value(); }

    //
    main_view->draw_rounded_rect(x, y, w, h, r, this->cl);

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
inline bool check_file_exists(const std::string& name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}


//
inline bool ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}


//
WindowEltButton::WindowEltButton( Style* style,
    std::string txt,
    Value* x,
    Value* y,
    Value* w,
    Value* h,
    std::function<void(WindowEltClickable*, MainGame*)> on_click
   )
: WindowEltClickable(style, x, y, w, h, on_click), txt(txt) {

    //
    if ( ( ends_with(txt, ".png") || ends_with(txt, ".jpg") || ends_with(txt, ".jpeg") ) && check_file_exists(txt) ){

        //
        this->bt_sprite = new WindowEltSprite(
            this->style,
            txt,
            this->x, this->y, this->w, this->h,
            nvi(0),
            false,
            false,
            SPRITE_NO_CROP(),
            SPRITE_RATIO_ORIGINAL(),
            SPRITE_RESIZE_FIT(),
            SPRITE_POS_ALIGN_CENTER(),
            SPRITE_POS_ALIGN_CENTER()
        );

    }

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
    std::string txt = "";

    //
    if (this->bt_sprite == nullptr ){
        txt = this->txt;
    }

    //
    main_view->draw_button_1( x, y, w, h, txt, fg_cl, bg_cl, font_size, radius );

    //
    if (this->bt_sprite != nullptr){
        this->bt_sprite->draw_elt(main_view, transform);
    }

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
