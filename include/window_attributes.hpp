#pragma once
//
#include <chrono>
#include <cstdint>
#include <iostream>
#include <map>
//
#include "events.hpp"

//
#define MOUSE_BUTTON_LEFT 1
#define MOUSE_BUTTON_RIGHT 3

// ============================ [ Pointers ] ============================

#define WINDOW_ATTRIBUTE_T WindowAttributes*

#define CREATE_WINDOW_ATTRIBUTE_T(...) new WindowAttributes(__VA_ARGS__)


// ============================ [ Classes ] ============================


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
        int mouse_last_drag_x = -1;
        int mouse_last_drag_y = -1;

        //
        uint64_t mouse_left_bt_clicked = false;
        uint64_t mouse_right_bt_clicked = false;

        //
        std::map< std::string, uint64_t > keys_pressed;

        //
        EVENT_T update_mouse_button_state(int button, int pressed);

        //
        EVENT_T update_keyboard_state(std::string key, bool pressed);

        //
        void update_window_size(int new_width, int new_height);

        //
        void update_window_position(int new_x, int new_y);

};

