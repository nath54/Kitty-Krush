//
#include <iostream>
#include <cmath>
//
#include <window_attributes.hpp>

//
#define MIN_DIST_DRAG 1


//
double euclidian_distance(int x1, int y1, int x2, int y2) {

    //
    return sqrt(  pow( (double) (x1 - x2), 2.0 )
                + pow( (double) (y1 - y2), 2.0 ) );

}


//
uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}


//
Event* WindowAttributes::update_mouse_button_state(int button, bool pressed){

    //
    Event* evt = nullptr;

    //
    if(pressed){

        //
        uint64_t time = timeSinceEpochMillisec();

        //
        if( this->mouse_base_drag_x == -1 || this->mouse_base_drag_y == -1){
            this->mouse_base_drag_x = this->mouse_x;
            this->mouse_base_drag_y = this->mouse_y;
        }
        //
        else if( euclidian_distance(
                    this->mouse_base_drag_x,
                    this->mouse_base_drag_y,
                    this->mouse_x,
                    this->mouse_y
                 ) > MIN_DIST_DRAG
        ){
            evt = new EventMouseDragging(
                this->mouse_base_drag_x,
                this->mouse_base_drag_y,
                this->mouse_x - this->mouse_base_drag_x,
                this->mouse_y - this->mouse_base_drag_y,
                button
            );
        }

        //
        if( button == MOUSE_BUTTON_LEFT ){
            mouse_left_bt_clicked = time;
        }
        else if ( button == MOUSE_BUTTON_RIGHT ){
            mouse_right_bt_clicked = time;
        }
    }

    //
    else if( mouse_left_bt_clicked + mouse_right_bt_clicked > 0){

        //
        if( false && this->mouse_base_drag_x != -1 &&
            this->mouse_base_drag_y != -1 &&
            euclidian_distance(
                this->mouse_base_drag_x,
                this->mouse_base_drag_y,
                this->mouse_x,
                this->mouse_y
            ) > MIN_DIST_DRAG
        ){
            evt = new EventMouseDragEnd(
                this->mouse_base_drag_x,
                this->mouse_base_drag_y,
                this->mouse_x - this->mouse_base_drag_x,
                this->mouse_y - this->mouse_base_drag_y,
                button
            );
            //
            this->mouse_base_drag_x = -1;
            this->mouse_base_drag_y = -1;
        }

        //
        else{

            //
            evt = new EventMouseClick(
                this->mouse_x,
                this->mouse_y,
                button
            );

        }

        //
        if( button == MOUSE_BUTTON_LEFT ){
            mouse_left_bt_clicked = 0;
        }
        else if ( button == MOUSE_BUTTON_RIGHT ){
            mouse_right_bt_clicked = 0;
        }

    }

    //
    return evt;

}


Event* WindowAttributes::update_keyboard_state(std::string key, bool pressed){

    //
    Event* evt = nullptr;

    //
    if(pressed){
        //
        if( this->keys_pressed.count(key) == 0 ){
            //
            this->keys_pressed[key] = timeSinceEpochMillisec();

            //
            evt = new EventKeyDown( key );
        }
    }
    //
    else if( this->keys_pressed.count(key) > 0 ){
        //
        this->keys_pressed.erase(key);

        //
        evt = new EventKeyUp( key );
    }

    //
    return evt;

}


