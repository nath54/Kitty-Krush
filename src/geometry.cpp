#include "geometry.hpp"


int pos_mod_2(int x){
    if( x < 0 ){
        return - (x % 2);
    }
    else{
        return (x % 2);
    }
}


bool is_point_in_rect(int px, int py, int rx, int ry, int rw, int rh)
    { return !(px < rx || px > rx + rw || py < ry || py > ry + rh); }


Coord::Coord(int x, int y) : x(x), y(y) {}


Coord get_tile_top_to(Coord c)
    { return (Coord) {c.x, c.y - 1}; }


Coord get_tile_top_right_to(Coord c)
    { return (Coord) {c.x + 1, c.y - 1 + pos_mod_2(c.x)}; }


Coord get_tile_top_left_to(Coord c)
    { return (Coord) {c.x - 1, c.y - 1 + pos_mod_2(c.x)}; }


Coord get_tile_bottom_to(Coord c)
    { return (Coord) {c.x, c.y + 1}; }


Coord get_tile_bottom_right_to(Coord c)
    { return (Coord) {c.x + 1, c.y + pos_mod_2(c.x)}; }


Coord get_tile_bottom_left_to(Coord c)
    { return (Coord) {c.x - 1, c.y + pos_mod_2(c.x)}; }


bool is_adjacent(Coord c1, Coord c2)
{
    if (get_tile_top_to(c1) == c2 ) { return true; }
    if (get_tile_top_left_to(c1) == c2) { return true; }
    if (get_tile_top_right_to(c1) == c2) { return true; }
    if (get_tile_bottom_to(c1) == c2) { return true; }
    if (get_tile_bottom_left_to(c1) == c2) { return true; }
    if (get_tile_bottom_right_to(c1) == c2) { return true; }

    return false;
}

std::vector<Coord> neighbours(Coord c)
{
    std::vector<Coord> n;
    n.push_back(get_tile_top_to(c));
    n.push_back(get_tile_top_left_to(c));
    n.push_back(get_tile_top_right_to(c));
    n.push_back(get_tile_bottom_to(c));
    n.push_back(get_tile_bottom_left_to(c));
    n.push_back(get_tile_bottom_right_to(c));
    return n;
}