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
Coord::Coord(int x, int y)
: x(x), y(y)
{ }



//
Coord get_tile_top_to(Coord v){
    return (Coord) {v.x, v.y - 1};
}
//
Coord get_tile_top_right_to(Coord v){
    if(v.x % 2 == 0){
        return (Coord){v.x + 1, v.y - 1};
    }
    return (Coord){v.x + 1, v.y};
}
//
Coord get_tile_top_left_to(Coord v){
    if(v.x % 2 == 0){
        return (Coord){v.x - 1, v.y - 1};
    }
    return (Coord){v.x - 1, v.y};
}
//
Coord get_tile_bottom_to(Coord v){
    return (Coord) {v.x, v.y + 1};
}
//
Coord get_tile_bottom_right_to(Coord v){
    if(v.x % 2 == 0){
        return (Coord){v.x + 1, v.y};
    }
    return (Coord){v.x + 1, v.y + 1};
}
//
Coord get_tile_bottom_left_to(Coord v){
    if(v.x % 2 == 0){
        return (Coord){v.x - 1, v.y};
    }
    return (Coord){v.x - 1, v.y + 1};
}
