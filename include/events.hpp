//
#pragma once
//
#include <deque>



enum EventType{
    EVT_NULL,
    EVT_QUIT
};





//
class Event{

    //
    public:

        //
        Event() {}

        //
        virtual int get_event_type(){
            //
            return EVT_NULL;
        }

};


//
class EventQuit : public Event {

    //
    public:

        //
        EventQuit() {}

        //
        int get_event_type(){
            //
            return EVT_QUIT;
        }

};


//
class EventsManager{

    public:

        //
        std::deque<Event*> list_of_events;
        int nb_events_waiting = 0;

        //
        EventsManager() {}

        //
        void new_event(Event* event);

        //
        Event* poll_next_event();

};
