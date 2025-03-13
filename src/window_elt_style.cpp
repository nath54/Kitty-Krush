#pragma once
//
#include "color.hpp"
#include "window_elt_style.hpp"


//
int Style::get_font_size(int win_state){
    //
    switch ( win_state ){

        //
        case STYLE_ELT_CLICKED:
            return this->clicked_font_size;

        //
        case STYLE_ELT_HOVER:
            return this->hover_font_size;

        //
        default:
            return this->base_font_size;

    }
}


//
Color Style::get_fg_color(int win_state){
    //
    switch ( win_state ){

        //
        case STYLE_ELT_CLICKED:
            return this->clicked_fg_color;

        //
        case STYLE_ELT_HOVER:
            return this->hover_fg_color;

        //
        default:
            return this->base_fg_color;

    }
}


//
Color Style::get_bg_color(int win_state){
    //
    switch ( win_state ){

        //
        case STYLE_ELT_CLICKED:
            return this->clicked_bg_color;

        //
        case STYLE_ELT_HOVER:
            return this->hover_bg_color;

        //
        default:
            return this->base_bg_color;

    }
}


//
int Style::get_radius(int win_state){
    //
    switch ( win_state ){

        //
        case STYLE_ELT_CLICKED:
            return this->clicked_radius;

        //
        case STYLE_ELT_HOVER:
            return this->hover_radius;

        //
        default:
            return this->base_radius;

    }
}
