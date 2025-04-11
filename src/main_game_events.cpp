//
#include "view.hpp"
#include "main_game.hpp"


//
#ifndef C_CONSTS
#define C_CONSTS


#define BASE_DEC_CAM 100
#define UNZOOM_FACTOR 0.95
#define ZOOM_FACTOR 1.05
#define MIN_ZOOM 0.25
#define MAX_ZOOM 6

#endif



//
void MainGame::mainloop_execute_all_events(){

    //
    int nb_events = 0;

    //
    Event* event = this->events_manager->poll_next_event();

    //
    while( event != nullptr && nb_events < MAINLOOP_MAX_EVENTS_PER_LOOP ){

        //
        this->execute_event(event);

        //
        nb_events += 1;
        //
        event = this->events_manager->poll_next_event();

    }

}



//
void test_all_window_elts_for_clicks(MainGame* main_game, EventMouseClick* event){

    //
    if(event == nullptr || main_game->main_view == nullptr || main_game->main_view->win_page_manager == nullptr){
        return;
    }

    //
    WindowPage* crt_page = main_game->main_view->win_page_manager->get_current_page();

    //
    if(crt_page == nullptr){
        return;
    }

    //
    for(int i = crt_page->elts.size() - 1; i >= 0; i--){

        //
        WindowElt* elt = crt_page->elts[i];
        WindowEltClickable* elt_c = dynamic_cast<WindowEltClickable*>( elt );

        //
        if ( elt_c == nullptr ){ continue; }

        //
        if ( elt_c->on_click == nullptr ){ continue; }

        //
        if ( elt_c->get_elt_state( main_game->main_view->get_win_attr() ) != STYLE_ELT_BASE ){

            //
            elt_c->on_click(main_game);

            //
            event->valid = false;
            return;
        }

    }

}



//
void on_key_up(MainGame* main_game, EventKeyUp* event){

    //
    if(event == nullptr || main_game->menu_state != 2){
        return;
    }

    //
    WindowElt* map_viewer_elt = main_game->main_view->win_page_manager->pages["in_game"]->elts[0];

    //
    WindowEltMapViewer* map_viewer = dynamic_cast<WindowEltMapViewer*>(map_viewer_elt);

    //
    if ( map_viewer == nullptr ){

        //
        cout << "Error : map_viewer can't convert to WindowEltMapViewer* !\n";
        //
        main_game->quit();
    }

    //
    int dec_cam = BASE_DEC_CAM * map_viewer->zoom;

    //
    if ( event->key == "Up" || event->key == "z" ){
        //
        map_viewer->cam_y -= dec_cam;
    }

    //
    else if ( event->key == "Down" || event->key == "s" ){
        //
        map_viewer->cam_y += dec_cam;
    }

    //
    else if ( event->key == "Left" || event->key == "q" ){
        //
        map_viewer->cam_x -= dec_cam;
    }

    //
    else if ( event->key == "Right" || event->key == "d" ){
        //
        map_viewer->cam_x += dec_cam;
    }

    //
    else if ( event->key == "Left Shift" ){

        //
        float last_zoom = map_viewer->zoom;

        //
        map_viewer->zoom *= UNZOOM_FACTOR;

        //
        if( map_viewer->zoom < MIN_ZOOM ){
            map_viewer->zoom = MIN_ZOOM;
        }

        //
        map_viewer->cam_x = map_viewer->cam_x + (int) ( (float) main_game->main_view->win_attr.mouse_x * last_zoom ) - (int) ( ( (float) main_game->main_view->win_attr.win_width  * map_viewer->zoom) / 2.0 );
        map_viewer->cam_y = map_viewer->cam_y + (int) ( (float) main_game->main_view->win_attr.mouse_y * last_zoom ) - (int) ( ( (float) main_game->main_view->win_attr.win_height * map_viewer->zoom) / 2.0 );

    }

    //
    else if ( event->key == "Right Shift" ){

        //
        float last_zoom = map_viewer->zoom;

        //
        map_viewer->zoom *= ZOOM_FACTOR;

        //
        if( map_viewer->zoom > MAX_ZOOM ){
            map_viewer->zoom = MAX_ZOOM;

        }

        //
        map_viewer->cam_x = map_viewer->cam_x + (int) ( (float) main_game->main_view->win_attr.mouse_x * last_zoom ) - (int) ( ( (float) main_game->main_view->win_attr.win_width  * map_viewer->zoom) / 2.0 );
        map_viewer->cam_y = map_viewer->cam_y + (int) ( (float) main_game->main_view->win_attr.mouse_y * last_zoom ) - (int) ( ( (float) main_game->main_view->win_attr.win_height * map_viewer->zoom) / 2.0 );

    }

}

void on_scroll(MainGame* main_game, EventMouseScroll* event) {
    if (event == nullptr || main_game->menu_state != 2) {
        return;
    }

    WindowElt* map_viewer_elt = main_game->main_view->win_page_manager->pages["in_game"]->elts[0];
    WindowEltMapViewer* map_viewer = dynamic_cast<WindowEltMapViewer*>(map_viewer_elt);

    if (map_viewer == nullptr) {
        cout << "Error : map_viewer can't convert to WindowEltMapViewer* !\n";
        main_game->quit();
    }

    float last_zoom = map_viewer->zoom;
    int mouse_x = main_game->main_view->win_attr.mouse_x;
    int mouse_y = main_game->main_view->win_attr.mouse_y;

    if (event->scroll_y > 0) {
        map_viewer->zoom *= ZOOM_FACTOR;
        if (map_viewer->zoom > MAX_ZOOM) {
            map_viewer->zoom = MAX_ZOOM;
        }
    }
    else if (event->scroll_y < 0) {
        map_viewer->zoom *= UNZOOM_FACTOR;
        if (map_viewer->zoom < MIN_ZOOM) {
            map_viewer->zoom = MIN_ZOOM;
        }
    }

    // Corrected camera update with floats
    map_viewer->cam_x = map_viewer->cam_x + (static_cast<float>(mouse_x) / last_zoom) -
                        (static_cast<float>(mouse_x) / map_viewer->zoom);
    map_viewer->cam_y = map_viewer->cam_y + (static_cast<float>(mouse_y) / last_zoom) -
                        (static_cast<float>(mouse_y) / map_viewer->zoom);
}

//
void MainGame::execute_event(Event* event){

    //
    switch( event->get_event_type() ){

        //
        case EVT_MOUSE_CLICK:

            //
            test_all_window_elts_for_clicks( this, dynamic_cast<EventMouseClick*>( event ) );
            //
            break;

        //
        case EVT_KEY_UP:

            //
            on_key_up( this, dynamic_cast<EventKeyUp*>( event ) );
            //
            break;

        //
        case EVT_MOUSE_SCROLL:

            //
            on_scroll( this, dynamic_cast<EventMouseScroll*>( event ) );
            //
            break;

        //
        case EVT_QUIT:

            //
            this->quit();
            //
            break;

        //
        case EVT_NULL:
        //
        default:
            //
            break;

    }

}


