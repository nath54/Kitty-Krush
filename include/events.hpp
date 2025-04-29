#pragma once

#include <deque>




// ============================ [ Pointers ] ============================

#define EVENT_T Event*
#define EVENT_QUIT_T EventQuit*
#define EVENT_MOUSE_T EventMouse*
#define EVENT_MOUSE_SCROLL_T EventMouseScroll*
#define EVENT_MOUSE_MOTION_T EventMouseMotion*
#define EVENT_MOUSE_CLICK_T EventMouseClick*
#define EVENT_MOUSE_DRAG_T EventMouseDrag*
#define EVENT_MOUSE_DRAGGING_T EventMouseDragging*
#define EVENT_MOUSE_DRAG_END_T EventMouseDragEnd*
#define EVENT_KEY_T EventKey*
#define EVENT_KEY_UP_T EventKeyUp*
#define EVENT_KEY_DOWN_T EventKeyDown*

#define CREATE_EVENT_T(...) new Event(__VA_ARGS__)
#define CREATE_EVENT_QUIT_T(...) new EventQuit(__VA_ARGS__)
#define CREATE_EVENT_MOUSE_T(...) new EventMouse(__VA_ARGS__)
#define CREATE_EVENT_MOUSE_SCROLL_T(...) new EventMouseScroll(__VA_ARGS__)
#define CREATE_EVENT_MOUSE_MOTION_T(...) new EventMouseMotion(__VA_ARGS__)
#define CREATE_EVENT_MOUSE_CLICK_T(...) new EventMouseClick(__VA_ARGS__)
#define CREATE_EVENT_MOUSE_DRAG_T(...) new EventMouseDrag(__VA_ARGS__)
#define CREATE_EVENT_MOUSE_DRAGGING_T(...) new EventMouseDragging(__VA_ARGS__)
#define CREATE_EVENT_MOUSE_DRAG_END_T(...) new EventMouseDragEnd(__VA_ARGS__)
#define CREATE_EVENT_KEY_T(...) new EventKey(__VA_ARGS__)
#define CREATE_EVENT_KEY_UP_T(...) new EventKeyUp(__VA_ARGS__)
#define CREATE_EVENT_KEY_DOWN_T(...) new EventKeyDown(__VA_ARGS__)

#define DCAST_EVENT_QUIT_T(...) dynamic_cast<EVENT_QUIT_T>(__VA_ARGS__)
#define DCAST_EVENT_MOUSE_T(...) dynamic_cast<EVENT_MOUSE_T>(__VA_ARGS__)
#define DCAST_EVENT_MOUSE_SCROLL_T(...) dynamic_cast<EVENT_MOUSE_SCROLL_T>(__VA_ARGS__)
#define DCAST_EVENT_MOUSE_MOTION_T(...) dynamic_cast<EVENT_MOUSE_MOTION_T>(__VA_ARGS__)
#define DCAST_EVENT_MOUSE_CLICK_T(...) dynamic_cast<EVENT_MOUSE_CLICK_T>(__VA_ARGS__)
#define DCAST_EVENT_MOUSE_DRAG_T(...) dynamic_cast<EVENT_MOUSE_DRAG_T>(__VA_ARGS__)
#define DCAST_EVENT_MOUSE_DRAGGING_T(...) dynamic_cast<EVENT_MOUSE_DRAGGING_T>(__VA_ARGS__)
#define DCAST_EVENT_MOUSE_DRAG_END_T(...) dynamic_cast<EVENT_MOUSE_DRAG_END_T>(__VA_ARGS__)
#define DCAST_EVENT_KEY_T(...) dynamic_cast<EVENT_KEY_T>(__VA_ARGS__)
#define DCAST_EVENT_KEY_UP_T(...) dynamic_cast<EVENT_KEY_UP_T>(__VA_ARGS__)
#define DCAST_EVENT_KEY_DOWN_T(...) dynamic_cast<EVENT_KEY_DOWN_T>(__VA_ARGS__)


// ============================ [ EventType ] ============================



enum EventType {
    EVT_NULL,
    EVT_QUIT,
    EVT_MOUSE_MOTION,
    EVT_MOUSE_CLICK,
    EVT_MOUSE_SCROLL,
    EVT_MOUSE_DRAGGING,
    EVT_MOUSE_DRAG_END,
    EVT_KEY_DOWN,
    EVT_KEY_UP
};


// ============================ [ General Events ] ============================


class Event {

    public:

        // Constructor
        Event() {}

        // Getter
        virtual int get_event_type() { return EVT_NULL; }
};


class EventQuit : public Event {

    public:

        // Constructor
        EventQuit() {}

        // Getter
        int get_event_type() { return EVT_QUIT; }

};


class EventMouse : public Event {

    public:

        // Attributes
        int x;
        int y;

        // Constructor
        EventMouse(int x, int y)
            : x(x), y(y) {}

        // Getter
        int get_event_type() { return EVT_NULL; }
};


// ============================ [ Mouse Events ] ============================


class EventMouseMotion : public EventMouse {

    public:

        // Constructor
        EventMouseMotion(int x, int y)
            : EventMouse(x, y){}

        // Getter
        int get_event_type() { return EVT_MOUSE_MOTION; }
};


class EventMouseClick : public EventMouse {

    public:

        // Attributes
        bool valid = true;
        int bt;

        // Constructor
        EventMouseClick(int x, int y, int bt)
            : EventMouse(x, y), bt(bt) {}

        // Getter
        int get_event_type() { return EVT_MOUSE_CLICK; }
};


class EventMouseScroll : public EventMouse {

    public:

        // Attributes
        int scroll_x;
        int scroll_y;

        // Constructor
        EventMouseScroll(int x, int y, int scroll_x, int scroll_y)
            : EventMouse(x, y), scroll_x(scroll_x), scroll_y(scroll_y) {}

        // Getter
        int get_event_type() { return EVT_MOUSE_SCROLL; }
};


class EventMouseDrag : public EventMouse {

    public:

        // Attributes
        int bt;
        int dx;
        int dy;

        // Constructor
        EventMouseDrag(int x, int y, int dx, int dy, int bt)
            : EventMouse(x, y), dx(dx), dy(dy), bt(bt) {}

        // Getter
        int get_event_type() { return EVT_NULL; }
};


class EventMouseDragEnd : public EventMouseDrag {

    public:

        // Constructor
        EventMouseDragEnd(int x, int y, int dx, int dy, int bt)
            : EventMouseDrag(x, y, dx, dy, bt) {}

        // Getter
        int get_event_type() { return EVT_MOUSE_DRAG_END; }
};


class EventMouseDragging : public EventMouseDrag {

    public:

        // Constructor
        EventMouseDragging(int x, int y, int dx, int dy, int bt)
            : EventMouseDrag(x, y, dx, dy, bt) {}

        // Getter
        int get_event_type() { return EVT_MOUSE_DRAGGING; }
};


class EventKey : public Event {

    public:

        // Attribute
        std::string key;

        // Constructor
        EventKey(std::string key) : key(key) {}

        // Getter
        int get_event_type() { return EVT_NULL; }
};


class EventKeyDown : public EventKey {

    public:

        // Constructor
        EventKeyDown(std::string key) : EventKey(key) {}

        // Getter
        int get_event_type() { return EVT_KEY_DOWN; }
};


class EventKeyUp : public EventKey {

    public:

        // Constructor
        EventKeyUp(std::string key) : EventKey(key) {}

        // Getter
        int get_event_type() { return EVT_KEY_UP; }
};


// ============================ [ Events Manager ] ============================


class EventsManager {

    public:

        // Attributes
        std::deque<EVENT_T> list_of_events;
        int nb_events_waiting = 0;

        // Constructor
        EventsManager() {}

        // Functions
        void new_event(EVENT_T event);
        EVENT_T poll_next_event();
};
