//
#pragma once


//
int hash_v2(int x, int y);



//
class Vector2{

    public:

        //
        int x;
        int y;
        int hash;

        //
        Vector2(int x, int y);

        //
        bool operator<(const Vector2& v){
            //return this->hash < v.hash;
            if(this->x < v.x){
                return true;
            }
            else if(this->x == v.x){
                return this->y < v.y;
            }
            else{
                return false;
            }
        }

        friend bool operator<(const Vector2& l, const Vector2& r){
            //return l.hash < r.hash;
            if(l.x < r.x){
                return true;
            }
            else if(l.x == r.x){
                return l.y < r.y;
            }
            else{
                return false;
            }
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
