#pragma once
//
#include <chrono>
#include <cstdint>
#include <iostream>
//
#include "events.hpp"

//
#define MOUSE_BUTTON_LEFT 1
#define MOUSE_BUTTON_RIGHT 3


//
uint64_t timeSinceEpochMillisec();


//
class WindowAttributes{

    public:

        //
        int win_x = 0;
        int win_y = 0;
        int win_width = 1;
        int win_height = 1;

        //
        int mouse_x = 0;
        int mouse_y = 0;

        //
        int mouse_base_drag_x = -1;
        int mouse_base_drag_y = -1;

        //
        uint64_t mouse_left_bt_clicked = false;
        uint64_t mouse_right_bt_clicked = false;

        //
        Event* update_mouse_button_state(int button, bool pressed);

};

