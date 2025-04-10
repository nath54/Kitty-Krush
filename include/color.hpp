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


#define MAX_COLOR 10


static const Color allPlayerColors[10] = {

    // Player 1 : Red
    { 200, 100, 100 },

    // Player 2 : Blue
    { 100, 200, 100 },

    // Player 3 : Gren
    { 100, 100, 200 },

    // Player 4 : Purple
    { 200, 200, 100 },

    // Player 5 : Cyan
    { 100, 200, 200 },

    // Player 6 : Yellow
    { 200, 100, 200 },

    // Player 7 : Red
    { 200, 100, 100 },

    // Player 8 : Red
    { 200, 100, 100 },

    // Player 9 : Red
    { 200, 100, 100 },

    // Player 10 : Red
    { 200, 100, 100 }

};


