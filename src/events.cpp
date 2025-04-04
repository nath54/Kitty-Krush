//
#include <iostream>
//
#include "events.hpp"


//
void EventsManager::new_event(Event* event) {

    //
    if( event == nullptr ){
        return;
    }

    //
    this->list_of_events.push_back( event );

    //
    this->nb_events_waiting += 1;

    //
    std::cout << "New event (in list : " << this->nb_events_waiting << ") = " << event->get_event_type() << "\n";

}


//
Event* EventsManager::poll_next_event() {

    //
    if( this->nb_events_waiting == 0 ){
        return nullptr;
    }

    //
    Event* evt = this->list_of_events.front();
    //
    this->list_of_events.pop_front();
    //
    this->nb_events_waiting -= 1;

    //
    return evt;
}
