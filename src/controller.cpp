//
#include "controller.hpp"
//
#include <SDL.h>


//
void GameController::manage_events(){

    //
    this->polled_events = 0;

    // Poll all the awaiting events
    SDL_Event event;
    while (this->game_model->is_running && SDL_PollEvent(&event) && this->polled_events < this->max_events_to_poll_at_each_frame)
    {
        //
        this->polled_events++;

        //
        switch (event.type)
        {
            // Quit event
            case SDL_QUIT:
                //
                this->game_model->is_running = false;
                break;

            //
            default: break;
        }
    }

}
