//
#include "view.hpp"

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
ValuePercentWinWidth* nvpww(float prct, WindowAttributes* win_attr){
    return new ValuePercentWinWidth(prct, win_attr);
}

//
ValuePercentWinHeight* nvpwh(float prct, WindowAttributes* win_attr){
    return new ValuePercentWinHeight(prct, win_attr);
}


//
SpriteCrop* SPRITE_NO_CROP(){
    //
    return new SpriteCrop( nvp(0), nvp(0), nvp(1), nvp(1) );
}

//
SpriteCrop* SPRITE_CUSTOM_CROP(float src_x, float src_y, float src_w, float src_h){
    //
    return new SpriteCrop( nvp(src_x), nvp(src_y), nvp(src_w), nvp(src_h) );
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
bool is_point_in_rect(int px, int py, int rx, int ry, int rw, int rh){

    //
    if( px < rx || px > rx + rw || py < ry || py > ry + rh){
        return false;
    }

    //
    return true;
}


//
int WindowElt::get_elt_state(WindowAttributes* win_attr){

    //
    int rx = this->get_x();
    int ry = this->get_y();
    int rw = this->get_w();
    int rh = this->get_h();

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
int WindowElt::get_x(){
    //
    return this->x->get_value();
}

//
int WindowElt::get_y(){
    //
    return this->y->get_value();
}

//
int WindowElt::get_w(){
    //
    return this->w->get_value();
}

//
int WindowElt::get_h(){
    //
    return this->h->get_value();
}

//
void WindowElt::draw_elt(MainView* main_view){

    // Template abstract class

}



//
void WindowEltText::draw_elt(MainView* main_view){

    //
    int elt_state = this->get_elt_state( main_view->get_win_attr() );

    //
    Color cl = this->style->get_fg_color( elt_state );
    int font_size = this->style->get_font_size( elt_state );

    //
    int x = this->get_x();
    int y = this->get_y();
    int w = this->get_w();
    int h = this->get_h();

    //
    main_view->draw_text( this->txt, cl, font_size, x, y, w, h );

}



//
void WindowEltButton::draw_elt(MainView* main_view){

    //
    int elt_state = this->get_elt_state( main_view->get_win_attr() );

    //
    Color fg_cl = this->style->get_fg_color( elt_state );
    Color bg_cl = this->style->get_bg_color( elt_state );
    int radius = this->style->get_radius( elt_state );
    int font_size = this->style->get_font_size( elt_state );

    //
    int x = this->get_x();
    int y = this->get_y();
    int w = this->get_w();
    int h = this->get_h();

    //
    main_view->draw_button_1( x, y, w, h, this->txt, fg_cl, bg_cl, font_size, radius );

}



//
void WindowEltSprite::draw_elt(MainView* main_view){

    //
    // int elt_state = this->get_elt_state( main_view->get_win_attr() );

    SDL_Texture* texture = main_view->get_texture(img_path);
    //

    //
    int dest_x = this->get_x();
    int dest_y = this->get_y();
    int dest_w = this->get_w();
    int dest_h = this->get_h();
    //
    int src_x = 0;
    int src_y = 0;
    int src_w;
    int src_h;
    SDL_QueryTexture(texture, nullptr, nullptr, &src_w, &src_h);

    //
    int angle = this->angle->get_value();

    // CROP

    // ...

    // RATIO

    // ...

    // RESIZE

    // ...

    // POSITION

    // ...

    //
    main_view->draw_image( texture, src_x, src_y, src_w, src_h, dest_x, dest_y, dest_w, dest_h, angle, this->flip_h, this->flip_v );

}

//
void WindowPage::draw_page(MainView* main_view){

    // Draw each element
    for ( WindowElt* elt : this->elts ) {
        //
        elt->draw_elt(main_view);
    }

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

