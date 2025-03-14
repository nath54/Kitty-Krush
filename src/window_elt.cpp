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

