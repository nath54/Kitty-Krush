//
#include "window_elt.hpp"


//
void WindowElt::draw_elt(WindowAttributes* win_attr){

    // Template abstract class

}


//
void WindowPage::draw_page(WindowAttributes* win_attr){

    // Draw each element
    for ( WindowElt elt : this->elts ) {

        //
        elt.draw_elt(win_attr);

    }

}


//
void WindowPagesManager::draw_current_page( WindowAttributes* win_attr ){

    //
    if( this->pages.find(this->current_page) == this->pages.end() ){
        return;
    }

    //
    this->pages[this->current_page].draw_page(win_attr);

}


//
void WindowPagesManager::set_current_page( std::string new_current_page ){
    //
    this->current_page = new_current_page;
}

