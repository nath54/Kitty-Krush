//
#pragma once
//
#include <deque>



enum EventType{
    EVT_NULL,
    EVT_QUIT,
    EVT_MOUSE_CLICK,
    EVT_MOUSE_DRAGGING,
    EVT_MOUSE_DRAG_END,
    EVT_KEY_DOWN,
    EVT_KEY_UP
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
class EventMouse : public Event {

    //
    public:

        //
        int x;
        int y;

        //
        EventMouse(int x, int y)
            : x(x), y(y) {}

        //
        int get_event_type(){
            //
            return EVT_NULL;
        }

};


//
class EventMouseClick : public EventMouse {

    //
    public:

        //
        bool valid = true;
        //
        int bt;

        //
        EventMouseClick(int x, int y, int bt)
            : EventMouse(x, y), bt(bt) {}

        //
        int get_event_type(){
            //
            return EVT_MOUSE_CLICK;
        }

};


//
class EventMouseDrag : public EventMouse {

    //
    public:

        //
        int bt;
        int dx;
        int dy;

        //
        EventMouseDrag(int x, int y, int dx, int dy, int bt)
            : EventMouse(x, y), dx(dx), dy(dy), bt(bt) {}

        //
        int get_event_type(){
            //
            return EVT_NULL;
        }

};


//
class EventMouseDragEnd : public EventMouseDrag {

    //
    public:

        //
        EventMouseDragEnd(int x, int y, int dx, int dy, int bt)
            : EventMouseDrag(x, y, dx, dy, bt) {}

        //
        int get_event_type(){
            //
            return EVT_MOUSE_DRAG_END;
        }

};


//
class EventMouseDragging : public EventMouseDrag {

    //
    public:

        //
        EventMouseDragging(int x, int y, int dx, int dy, int bt)
            : EventMouseDrag(x, y, dx, dy, bt) {}

        //
        int get_event_type(){
            //
            return EVT_MOUSE_DRAGGING;
        }

};


//
class EventKey : public Event {

    //
    public:

        //
        std::string key;

        //
        EventKey(std::string key) : key(key) {}

        //
        int get_event_type(){
            //
            return EVT_NULL;
        }

};


//
class EventKeyDown : public EventKey {

    //
    public:

        //
        EventKeyDown(std::string key) : EventKey(key) {}

        //
        int get_event_type(){
            //
            return EVT_KEY_DOWN;
        }

};


//
class EventKeyUp : public EventKey {

    //
    public:

        //
        EventKeyUp(std::string key) : EventKey(key) {}

        //
        int get_event_type(){
            //
            return EVT_KEY_UP;
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
