#pragma once

#include <vector>

class Coord {

    public:

        // Attributes
        int x;
        int y;

        // Constructors
        Coord() {};
        Coord(int x, int y);

            // Overloads
        bool operator<(const Coord& v) {
            if (this->x < v.x) { return true; }
            else if (this->x == v.x) { return (this->y < v.y); }
            else { return false; }
        }

        friend bool operator<(const Coord& l, const Coord& r) {
            if (l.x < r.x) { return true; }
            else if (l.x == r.x) { return (l.y < r.y); }
            else { return false; }
        }

        bool operator==(const Coord& v)
            { return (this->x == v.x) && (this->y == v.y); }

        friend bool operator==(const Coord& l, const Coord& r)
            { return (l.x == r.x) && (l.y == r.y); }

        bool operator!=(const Coord& v)
            { return (this->x != v.x) || (this->y != v.y); }

        friend bool operator!=(const Coord& l, const Coord& r)
            { return (l.x != r.x) || (l.y != r.y); }

};

// === Utility functions ===

bool is_point_in_rect(int px, int py, int rx, int ry, int rw, int rh);

Coord get_tile_top_to(Coord v);
Coord get_tile_top_right_to(Coord v);
Coord get_tile_top_left_to(Coord v);
Coord get_tile_bottom_to(Coord v);
Coord get_tile_bottom_right_to(Coord v);
Coord get_tile_bottom_left_to(Coord v);

bool is_adjacent(Coord c1, Coord c2);

std::vector<Coord> neighbours(Coord c);
