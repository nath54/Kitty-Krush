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
        map_viewer->zoom_at_point(main_game->main_view->win_attr.mouse_x, main_game->main_view->win_attr.mouse_y, UNZOOM_FACTOR);

    }

    //
    else if ( event->key == "Right Shift" ){

        //
        map_viewer->zoom_at_point(main_game->main_view->win_attr.mouse_x, main_game->main_view->win_attr.mouse_y, ZOOM_FACTOR);

    }

}


//
void on_scroll(MainGame* main_game, EventMouseScroll* event) {

    //
    if (event == nullptr || main_game->menu_state != 2) {
        return;
    }

    //
    WindowElt* map_viewer_elt = main_game->main_view->win_page_manager->pages["in_game"]->elts[0];
    WindowEltMapViewer* map_viewer = dynamic_cast<WindowEltMapViewer*>(map_viewer_elt);

    //
    if (map_viewer == nullptr) {
        cout << "Error : map_viewer can't convert to WindowEltMapViewer* !\n";
        main_game->quit();
    }

    //
    if(event->scroll_y == 0){
        return;
    }

    //
    if (event->scroll_y > 0) {
        //
        map_viewer->zoom_at_point(event->x, event->y, ZOOM_FACTOR);
    }

    //
    else {
        //
        map_viewer->zoom_at_point(event->x, event->y, UNZOOM_FACTOR);
    }

}





//
void on_dragging(MainGame* main_game, EventMouseDragging* event) {

    //
    if (event == nullptr || main_game->menu_state != 2) {
        return;
    }

    //
    WindowElt* map_viewer_elt = main_game->main_view->win_page_manager->pages["in_game"]->elts[0];
    WindowEltMapViewer* map_viewer = dynamic_cast<WindowEltMapViewer*>(map_viewer_elt);

    //
    if (map_viewer == nullptr) {
        cout << "Error : map_viewer can't convert to WindowEltMapViewer* !\n";
        main_game->quit();
    }

    //
    // int dec_cam = BASE_DEC_CAM * map_viewer->zoom;

    //
    map_viewer->cam_x -= event->dx * 2; // / map_viewer->zoom;
    map_viewer->cam_y -= event->dy * 2; // / map_viewer->zoom;

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
        case EVT_MOUSE_DRAGGING:

            //
            on_dragging( this, dynamic_cast<EventMouseDragging*>( event ) );
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


