//
#pragma once
//
#include <string>
//
#include "model.hpp"
#include "events.hpp"
#include "window_attributes.hpp"


//
class PlayerController{

        // Player name, it is in the name   ദ്ദി(˵ •̀ ᴗ - ˵ ) ✧
        const std::string player_name;

        // Constructor
        PlayerController(const std::string player_name)
            : player_name(player_name) {};  // Automatic variable initialisation

};


//
class GameController{

    private:

        // Reference to game_model
        GameModel* game_model = nullptr;

        // list of players controllers
        PlayerController** player_controllers = nullptr;

        //
        const int max_events_to_poll_at_each_frame = 100;
        //
        int polled_events = 0;

    public:

        // Constructor
        GameController(GameModel* game_model): game_model(game_model) {};

        // Manage events (called in mainloop)
        void manage_events(WindowAttributes* win_attr, EventsManager* events_manager);

};

