//
#include "Window_elt.hpp"




//
void WindowPage::draw_page(){

    // Draw each element
    for ( Window_elt elt : this->elts ) {

        elt.draw_elt();

    }

}




