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


    // 🔥 APPLY CROPPING STRATEGY

    //
    int crop_x = 0;
    int crop_y = 0;
    int crop_w = src_w;
    int crop_h = src_h;

    //
    switch (this->crop_mode) {
        case CropMode::NO_CROP:
            // Use the full image
            break;

        case CropMode::CENTER_CROP:
            {
                float aspect_src = (float)src_w / src_h;
                float aspect_dest = (float)dest_w / dest_h;

                if (aspect_src > aspect_dest) {
                    // Crop width (wider source image)
                    crop_w = (int)(src_h * aspect_dest);
                    crop_h = src_h;
                    crop_x = (src_w - crop_w) / 2;
                    crop_y = 0;
                } else {
                    // Crop height (taller source image)
                    crop_w = src_w;
                    crop_h = (int)(src_w / aspect_dest);
                    crop_x = 0;
                    crop_y = (src_h - crop_h) / 2;
                }
            }
            break;

        case CropMode::TOP_LEFT_CROP:
            // Just set the crop region (default values)
            crop_x = 0;
            crop_y = 0;
            crop_w = dest_w;
            crop_h = dest_h;
            break;

        case CropMode::CUSTOM_CROP:
            // Use user-specified crop coordinates
            crop_x = this->custom_crop_x;
            crop_y = this->custom_crop_y;
            crop_w = this->custom_crop_w;
            crop_h = this->custom_crop_h;
            break;
    }

    //
    // 🔥 APPLY LAYOUT (RESIZING STRATEGY)
    switch (this->layout_mode) {
        case LayoutMode::STRETCH:
            // Force the image to stretch exactly
            break;

        case LayoutMode::FIT:
            {
                float scale = std::min((float)dest_w / crop_w, (float)dest_h / crop_h);
                int new_w = (int)(crop_w * scale);
                int new_h = (int)(crop_h * scale);
                dest_x += (dest_w - new_w) / 2;
                dest_y += (dest_h - new_h) / 2;
                dest_w = new_w;
                dest_h = new_h;
            }
            break;

        case LayoutMode::COVER:
            {
                float scale = std::max((float)dest_w / crop_w, (float)dest_h / crop_h);
                int new_w = (int)(crop_w * scale);
                int new_h = (int)(crop_h * scale);
                dest_x += (dest_w - new_w) / 2;
                dest_y += (dest_h - new_h) / 2;
                dest_w = new_w;
                dest_h = new_h;
            }
            break;

        case LayoutMode::CUSTOM_SCALE:
            // Scale manually
            dest_w = (int)(crop_w * this->custom_scale);
            dest_h = (int)(crop_h * this->custom_scale);
            break;
    }

    //
    cout << " src_x = " << src_x << " | src_y = " << src_y << " | src_w = " << src_w << " | src_h = " << src_h << " | dst_x = " << dest_x << " | dst_y = " << dest_y << " | dst_w = " << dest_w << " | dst_h = " << dest_h << "\n";

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

