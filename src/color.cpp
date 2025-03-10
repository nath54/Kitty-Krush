//
#include <stdint.h>
//
#include "color.hpp"


//
uint32_t Color::to_hex(){

    //
    return ((this->a & 0xff) << 24) + ((this->b & 0xff) << 16) + ((this->g & 0xff) << 8) + (this->r & 0xff);

}


