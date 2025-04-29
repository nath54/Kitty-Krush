#pragma once

#include "model_game.hpp"
#include "events.hpp"
#include "window_attributes.hpp"




class GameController {

    public:

        // Reference to game_model
        GameModel* game_model = nullptr;

        const int max_events_to_poll_at_each_frame = 100;

        int polled_events = 0;

        // Constructor
        GameController(GameModel* game_model): game_model(game_model) {};

        // Manage events (called in mainloop)
        void manage_events(WindowAttributes* win_attr, EventsManager* events_manager);
};

