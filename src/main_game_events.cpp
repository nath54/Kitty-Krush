//
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
void MainGame::execute_event(Event* event){

    //
    switch( event->get_event_type() ){

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


