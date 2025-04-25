#pragma once

#include <stdint.h>


class Color{

    public:

        int r = 0;
        int g = 0;
        int b = 0;
        int a = 255;

        Color(int r = 0, int g = 0, int b = 0, int a = 255)
            : r(r), g(g), b(b), a(a) {};

        uint32_t to_hex();

};


#define MAX_COLOR 10

static const Color CL_BLACK = (Color){ 0, 0, 0};
static const Color CL_DARK_GREY = (Color){ 50, 50, 50};
static const Color CL_GREY = (Color){ 100, 100, 100};
static const Color CL_LIGHT_GREY = (Color){ 150, 150, 150};

static const Color allPlayerColors[10] = {

    // Player 1 : Red
    { 250, 50, 50 },

    // Player 2 : Cyan
    { 0, 250, 250 },

    // Player 3 : Gren
    { 150, 250, 00 },

    // Player 4 : Purple
    { 150, 100, 200 },

    // Player 5 : Orange
    { 250, 200, 150 },

    // Player 6 : Mauve
    { 100, 50, 150 },

    // Player 7 : Yellow
    { 250, 250, 100 },

    // Player 8 : White
    { 250, 250, 250 },

    // Player 9 : Between Green and cyan
    { 50, 200, 150 },

    // Player 10 : Between Green and yellow
    { 150, 200, 50 }

};



