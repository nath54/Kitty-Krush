//
#include "window_elt.hpp"


//
void WindowElt::draw_elt(){

    // Template abstract class

}



//
void WindowPage::draw_page(){

    // Draw each element
    for ( WindowElt elt : this->elts ) {

        elt.draw_elt();

    }

}



