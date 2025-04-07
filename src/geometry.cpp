//
#include "geometry.hpp"


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
int hash_v2(int x, int y){

    //
    return x * 1 << 8 + y;

}


//
Vector2::Vector2(int x, int y)
: x(x), y(y)
{
    this->hash = hash_v2(x, y);
}

