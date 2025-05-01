#include "view.hpp"
#include "main_game.hpp"

#ifndef C_CONSTS
#define C_CONSTS

#define BASE_DEC_CAM 100
#define UNZOOM_FACTOR 0.95
#define ZOOM_FACTOR 1.05
#define MIN_ZOOM 0.25
#define MAX_ZOOM 6

#endif


void MainGame::mainloop_execute_all_events()
{
    int nb_events = 0;

    EVENT_T event = this->events_manager->poll_next_event();

    while (event != nullptr && nb_events < MAINLOOP_MAX_EVENTS_PER_LOOP) {

        this->execute_event(event);
        nb_events++;
        event = this->events_manager->poll_next_event();
    }
}

//
void test_all_window_elts_for_clicks(MainGame* main_game, EVENT_MOUSE_CLICK_T event)
{
    if (event == nullptr || main_game->main_view == nullptr
        || main_game->main_view->win_page_manager == nullptr)
        { return; }

    WindowPage* crt_page = main_game->main_view->win_page_manager->get_current_page();

    if (crt_page == nullptr) { return; }

    for (int i = crt_page->elts.size() - 1; i >= 0; i--) {

        WINDOW_ELT_T elt = crt_page->elts[i];
        WINDOW_ELT_CLICKABLE_T elt_c = DCAST_WINDOW_ELT_CLICKABLE_T(elt);

        if (elt_c == nullptr) { continue; }
        if (!(elt_c->visible) ) { continue; }
        if (elt_c->disabled) { continue; }
        if (elt_c->on_click == nullptr) { continue; }

        if (elt_c->get_elt_state(main_game->main_view->get_win_attr()) != STYLE_ELT_BASE) {

            elt_c->on_click(elt_c, main_game, elt_c->additional_fn_args);
            event->valid = false;
            return;
        }
    }
}

//
void on_key_up(MainGame* main_game, EVENT_KEY_UP_T event)
{
    if (event == nullptr || main_game->menu_state < 2 || main_game->menu_state > 3) { return; }

    WINDOW_ELT_MAP_VIEWER_T map_viewer = main_game->main_view->map_viewer;

    if (map_viewer == nullptr) {
        std::cout << "Error : no map viewer !\n";
        main_game->quit();
    }

    if (map_viewer->game_end){ return; }

    int dec_cam = BASE_DEC_CAM * map_viewer->zoom;

    if (event->key == "Up" || event->key == "z")
        { map_viewer->cam_y -= dec_cam; }

    else if (event->key == "Down" || event->key == "s")
        { map_viewer->cam_y += dec_cam; }

    else if (event->key == "Left" || event->key == "q")
        { map_viewer->cam_x -= dec_cam; }

    else if (event->key == "Right" || event->key == "d")
        { map_viewer->cam_x += dec_cam; }

    else if (event->key == "Left Shift")
        { map_viewer->zoom_at_point(main_game->main_view->win_attr.mouse_x,
                                    main_game->main_view->win_attr.mouse_y,
                                    UNZOOM_FACTOR); }

    else if (event->key == "Right Shift")
        { map_viewer->zoom_at_point(main_game->main_view->win_attr.mouse_x,
                                    main_game->main_view->win_attr.mouse_y,
                                    ZOOM_FACTOR); }

    Coord mouse_pos = (Coord){main_game->main_view->win_attr.mouse_x, main_game->main_view->win_attr.mouse_y};

    map_viewer->update_mouse_hover_tile(mouse_pos);
}

//
void on_scroll(MainGame* main_game, EVENT_MOUSE_SCROLL_T event)
{
    if (event == nullptr || main_game->menu_state < 2 || main_game->menu_state > 3) { return; }

    WINDOW_ELT_MAP_VIEWER_T map_viewer = main_game->main_view->map_viewer;

    if (map_viewer == nullptr) {
        std::cout << "Error : no map viewer !\n";
        main_game->quit();
    }

    if (map_viewer->game_end){ return; }

    if (event->scroll_y == 0) { return; }

    if (event->scroll_y > 0)
        { map_viewer->zoom_at_point(event->x, event->y, ZOOM_FACTOR); }
    else
        { map_viewer->zoom_at_point(event->x, event->y, UNZOOM_FACTOR); }

    Coord mouse_pos = (Coord) {main_game->main_view->win_attr.mouse_x,
                               main_game->main_view->win_attr.mouse_y};

    map_viewer->update_mouse_hover_tile( mouse_pos );
}

//
void on_dragging(MainGame* main_game, EVENT_MOUSE_DRAGGING_T event)
{
    if (event == nullptr || main_game->menu_state < 2 || main_game->menu_state > 3)
        { return; }

    WINDOW_ELT_MAP_VIEWER_T map_viewer = main_game->main_view->map_viewer;

    if (map_viewer == nullptr) {
        std::cout << "Error : no map_viewer !\n";
        main_game->quit();
    }

    if (map_viewer->game_end){ return; }

    // int dec_cam = BASE_DEC_CAM * map_viewer->zoom;

    map_viewer->cam_x -= event->dx; // * 2; // / map_viewer->zoom;
    map_viewer->cam_y -= event->dy; // * 2; // / map_viewer->zoom;

    Coord mouse_pos = (Coord) {main_game->main_view->win_attr.mouse_x,
                               main_game->main_view->win_attr.mouse_y};

    map_viewer->update_mouse_hover_tile(mouse_pos);
}

//
void on_mouse_motion(MainGame* main_game, EVENT_MOUSE_MOTION_T event)
{
    if (event == nullptr || main_game->menu_state < 2 || main_game->menu_state > 3) { return; }

    WINDOW_ELT_MAP_VIEWER_T map_viewer = main_game->main_view->map_viewer;

    if (map_viewer == nullptr) {
        std::cout << "Error : no map viewer !\n";
        main_game->quit();
    }

    if (map_viewer->game_end){ return; }

    Coord mouse_pos = (Coord){event->x, event->y};

    map_viewer->update_mouse_hover_tile(mouse_pos);
}

//
void MainGame::execute_event(EVENT_T event)
{
    switch (event->get_event_type()) {

        case EVT_MOUSE_CLICK:

            test_all_window_elts_for_clicks(this, DCAST_EVENT_MOUSE_CLICK_T(event));
            break;

        case EVT_KEY_UP:

            on_key_up(this, DCAST_EVENT_KEY_UP_T(event));
            break;

        case EVT_MOUSE_MOTION:

            on_mouse_motion(this, DCAST_EVENT_MOUSE_MOTION_T(event));
            break;

        case EVT_MOUSE_SCROLL:

            on_scroll(this, DCAST_EVENT_MOUSE_SCROLL_T(event));
            break;

        case EVT_MOUSE_DRAGGING:

            on_dragging(this, DCAST_EVENT_MOUSE_DRAGGING_T(event));
            break;

        case EVT_QUIT:

            this->quit();
            break;

        case EVT_NULL:

        default:

            break;
    }
}

