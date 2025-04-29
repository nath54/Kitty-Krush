//
#include "color.hpp"
#include "window_elt_style.hpp"


//
int clamp(int v, int mini, int maxi){
    if(v < mini){
        return mini;
    }
    if(v > maxi){
        return maxi;
    }
    return v;
}


//
int Style::get_font_size(int win_state, bool disabled){

    //
    int res;

    //
    if(disabled){
        //
        res = this->base_font_size;
    }

    //
    else{

        //
        switch ( win_state ){

            //
            case STYLE_ELT_CLICKED:
                res = this->clicked_font_size;
                break;

            //
            case STYLE_ELT_HOVER:
                res = this->hover_font_size;
                break;

            //
            default:
                res = this->base_font_size;
                break;

        }

    }

    //
    return clamp(res, 6, 100);
}


//
Color Style::get_fg_color(int win_state, bool disabled){

    //
    if(disabled){
        //
        return this->disabled_fg_color;
    }

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
Color Style::get_bg_color(int win_state, bool disabled){

    //
    if(disabled){
        //
        return this->disabled_bg_color;
    }

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
int Style::get_radius(int win_state, bool disabled){

    //
    int res;

    //
    if(disabled){
        //
        res = this->base_radius;
    }

    //
    else{

        //
        switch ( win_state ){

            //
            case STYLE_ELT_CLICKED:
                res = this->clicked_radius;
                break;

            //
            case STYLE_ELT_HOVER:
                res = this->hover_radius;
                break;

            //
            default:
                res = this->base_radius;
                break;
        }

    }

    //
    return clamp(res, 0, 2000);
}



//
AllYourStyles::AllYourStyles(){

    //
    this->styles["default"] = CREATE_STYLE_T();

}



//
STYLE_T AllYourStyles::get_style(std::string style_name){

    //
    if(this->styles.find(style_name) == this->styles.end()){
        //
        return this->styles["default"];
    }

    //
    return this->styles[style_name];

}
