//
#include "view.hpp"
#include "main_game.hpp"


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
    int dec_cam = 50 * map_viewer->zoom;

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
        map_viewer->zoom *= 0.99;

        //
        if( map_viewer->zoom < 0.4 ){
            map_viewer->zoom = 0.4;
        }
    }

    //
    else if ( event->key == "Right Shift" ){
        //
        map_viewer->zoom *= 1.01;

        //
        if( map_viewer->zoom > 5 ){
            map_viewer->zoom = 5;
        }
    }

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


