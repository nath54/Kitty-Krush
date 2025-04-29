#pragma once

#include <deque>
#include <memory>



// ============================ [ Pointers ] ============================

#define EVENT_T std::shared_ptr<Event>
#define EVENT_QUIT_T std::shared_ptr<EventQuit>
#define EVENT_MOUSE_T std::shared_ptr<EventMouse>
#define EVENT_MOUSE_SCROLL_T std::shared_ptr<EventMouseScroll>
#define EVENT_MOUSE_MOTION_T std::shared_ptr<EventMouseMotion>
#define EVENT_MOUSE_CLICK_T std::shared_ptr<EventMouseClick>
#define EVENT_MOUSE_DRAG_T std::shared_ptr<EventMouseDrag>
#define EVENT_MOUSE_DRAGGING_T std::shared_ptr<EventMouseDragging>
#define EVENT_MOUSE_DRAG_END_T std::shared_ptr<EventMouseDragEnd>
#define EVENT_KEY_T std::shared_ptr<EventKey>
#define EVENT_KEY_UP_T std::shared_ptr<EventKeyUp>
#define EVENT_KEY_DOWN_T std::shared_ptr<EventKeyDown>

#define CREATE_EVENT_T(...) std::make_shared<Event>(__VA_ARGS__)
#define CREATE_EVENT_QUIT_T(...) std::make_shared<EventQuit>(__VA_ARGS__)
#define CREATE_EVENT_MOUSE_T(...) std::make_shared<EventMouse>(__VA_ARGS__)
#define CREATE_EVENT_MOUSE_SCROLL_T(...) std::make_shared<EventMouseScroll>(__VA_ARGS__)
#define CREATE_EVENT_MOUSE_MOTION_T(...) std::make_shared<EventMouseMotion>(__VA_ARGS__)
#define CREATE_EVENT_MOUSE_CLICK_T(...) std::make_shared<EventMouseClick>(__VA_ARGS__)
#define CREATE_EVENT_MOUSE_DRAG_T(...) std::make_shared<EventMouseDrag>(__VA_ARGS__)
#define CREATE_EVENT_MOUSE_DRAGGING_T(...) std::make_shared<EventMouseDragging>(__VA_ARGS__)
#define CREATE_EVENT_MOUSE_DRAG_END_T(...) std::make_shared<EventMouseDragEnd>(__VA_ARGS__)
#define CREATE_EVENT_KEY_T(...) std::make_shared<EventKey>(__VA_ARGS__)
#define CREATE_EVENT_KEY_UP_T(...) std::make_shared<EventKeyUp>(__VA_ARGS__)
#define CREATE_EVENT_KEY_DOWN_T(...) std::make_shared<EventKeyDown>(__VA_ARGS__)

#define DCAST_EVENT_QUIT_T(...) std::dynamic_pointer_cast<Event>(__VA_ARGS__)
#define DCAST_EVENT_MOUSE_T(...) std::dynamic_pointer_cast<EventMouse>(__VA_ARGS__)
#define DCAST_EVENT_MOUSE_SCROLL_T(...) std::dynamic_pointer_cast<EventMouseScroll>(__VA_ARGS__)
#define DCAST_EVENT_MOUSE_MOTION_T(...) std::dynamic_pointer_cast<EventMouseMotion>(__VA_ARGS__)
#define DCAST_EVENT_MOUSE_CLICK_T(...) std::dynamic_pointer_cast<EventMouseClick>(__VA_ARGS__)
#define DCAST_EVENT_MOUSE_DRAG_T(...) std::dynamic_pointer_cast<EventMouseDrag>(__VA_ARGS__)
#define DCAST_EVENT_MOUSE_DRAGGING_T(...) std::dynamic_pointer_cast<EventMouseDragging>(__VA_ARGS__)
#define DCAST_EVENT_MOUSE_DRAG_END_T(...) std::dynamic_pointer_cast<EventMouseDragEnd>(__VA_ARGS__)
#define DCAST_EVENT_KEY_T(...) std::dynamic_pointer_cast<EventKey>(__VA_ARGS__)
#define DCAST_EVENT_KEY_UP_T(...) std::dynamic_pointer_cast<EventKeyUp>(__VA_ARGS__)
#define DCAST_EVENT_KEY_DOWN_T(...) std::dynamic_pointer_cast<EventKeyDown>(__VA_ARGS__)


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
