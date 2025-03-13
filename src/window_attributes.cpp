//
#include <window_attributes.hpp>


//
uint64_t timeSinceEpochMillisec() {
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}


//
void WindowAttributes::update_mouse_button_state(int button, bool pressed){

    //
    if(pressed){

        //
        uint64_t time = timeSinceEpochMillisec();

        //
        if( button == 0 ){
            mouse_left_bt_clicked = time;
        }
        else if ( button == 1 ){
            mouse_right_bt_clicked = time;
        }
    }

    //
    else{

        //
        if( button == 0 ){
            mouse_left_bt_clicked = 0;
        }
        else if ( button == 1 ){
            mouse_right_bt_clicked = 0;
        }
    }

}



