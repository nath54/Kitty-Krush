//
#pragma once


//
class Vector2{

    public:

        //
        int x;
        int y;

        //
        Vector2(int x, int y): x(x), y(y) {}

        //
        bool operator<(const Vector2& v){
            return this->x < v.x && this->y < v.y;
        }

        friend bool operator<(const Vector2& l, const Vector2& r){
            return l.x < r.x && l.y < r.y;
        }

        //
        bool operator==(const Vector2& v){
            return this->x == v.x && this->y == v.y;
        }

        //
        friend bool operator==(const Vector2& l, const Vector2& r){
            return l.x == r.x && l.y == r.y;
        }

        //
        bool operator!=(const Vector2& v){
            return this->x == v.x || this->y == v.y;
        }

        //
        friend bool operator!=(const Vector2& l, const Vector2& r){
            return l.x != r.x || l.y != r.y;
        }

};


//
Vector2 v2(int x, int y);


//
bool is_point_in_rect(int px, int py, int rx, int ry, int rw, int rh);
