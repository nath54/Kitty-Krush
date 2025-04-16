#pragma once
//
#include <string>
#include <map>
//
#include "color.hpp"

//
#define STYLE_ELT_BASE 0
#define STYLE_ELT_HOVER 1
#define STYLE_ELT_CLICKED 2


//
class Style{

    public:

        // Font size
        int base_font_size = 20;
        int hover_font_size = 21;
        int clicked_font_size = 19;

        // Foreground Color
        Color base_fg_color = Color(255, 255, 255);
        Color hover_fg_color = Color(255, 255, 255);
        Color clicked_fg_color = Color(255, 255, 255);
        Color disabled_fg_color = Color(200, 200, 200);

        // Background Color
        Color base_bg_color = Color(200, 100, 150);
        Color hover_bg_color = Color(180, 100, 170);
        Color clicked_bg_color = Color(220, 100, 130);
        Color disabled_bg_color = Color(80, 60, 70);

        // Radius
        int base_radius = 22;
        int hover_radius = 15;
        int clicked_radius = 19;


        //
        int get_font_size(int win_state, bool disabled=false);

        //
        Color get_fg_color(int win_state, bool disabled=false);

        //
        Color get_bg_color(int win_state, bool disabled=false);

        //
        int get_radius(int win_state, bool disabled=false);

};


//
class AllYourStyles{

    public:

        //
        std::map<std::string, Style*> styles;

        //
        AllYourStyles();


        //
        Style* get_style(std::string style_name);

};

