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
    if(main_game->main_view == nullptr || main_game->main_view->win_page_manager == nullptr){
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


