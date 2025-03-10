//
#pragma once
//
#include <stdint.h>


// Hey hey, color class UwU
class Color{

    public:

        int r = 0;
        int g = 0;
        int b = 0;
        int a = 255;

        //
        Color(int r = 0, int g = 0, int b = 0, int a = 255)
            : r(r), g(g), b(b), a(a) {};

        //
        uint32_t to_hex();

};
