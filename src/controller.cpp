//
#include "controller.hpp"
#include "window_attributes.hpp"
#include "events.hpp"
//
#include <SDL2/SDL.h>


//
void GameController::manage_events(WindowAttributes* win_attr, EventsManager* events_manager){

    //
    this->polled_events = 0;

    // Poll all the awaiting events
    SDL_Event event;
    while (this->game_model->is_running && SDL_PollEvent(&event) && this->polled_events < this->max_events_to_poll_at_each_frame)
    {
        //
        this->polled_events++;

        //
        Event* evt = nullptr;

        //
        switch (event.type)
        {
            // Quit event
            case SDL_QUIT:
                //
                this->game_model->is_running = false;
                break;

            //
            case SDL_MOUSEBUTTONDOWN:
                //
                events_manager->new_event(
                     win_attr->update_mouse_button_state(event.button.button, true)
                );

                break;

            //
            case SDL_MOUSEBUTTONUP:
                //
                events_manager->new_event(
                    win_attr->update_mouse_button_state(event.button.button, false)
                );
                //
                break;

            //
            case SDL_MOUSEMOTION:
                //
                events_manager->new_event(
                    win_attr->update_mouse_button_state(-1, false)
                );
                //
                break;

            //
            //case SDL

            //
            default: break;
        }
    }

}
