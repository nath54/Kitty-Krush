#pragma once

#include "model_game.hpp"
#include "controller.hpp"
#include "events.hpp"
// #include "view.hpp"

#define MAINLOOP_MAX_EVENTS_PER_LOOP 1000


class MainView;


class MainGame{

    public:

        // MVC Modelisation:
        // Model
        GameModel* game_model;
        // View
        MainView* main_view;
        // Controller
        GameController* game_controller;

        // Event manager
        EventsManager* events_manager;

        // Menu State
        //   - -1 = quit the game
        //   -  0 = Main Menu
        //   -  1 = Game Settings
        //   -  2 = In Game
        int menu_state = 0;

        // Constructor
        MainGame();

        // Destructor
        ~MainGame();

        // Mainloop
        void mainloop();
        void mainloop_execute_all_events();

        void execute_event(Event* event);

        void change_page(std::string new_page);


        void set_map_from_data(
            std::map< Coord, int >* tiles_layer,            // Tiles layers
            std::map< Coord, int >* colors_layer,           // Colors layers
            std::map< Coord, int >* entity_layer,           // Entity layers
            std::map< Coord, int >* entities_attributes,    // Entities attributes (treasury or can_move)
            int current_color_to_play
        );


        void load_map_from_file(std::string map_path);
        void save_map(std::string file_path);

        void quit();


        // ACTIONS
        void at_player_turn_start();
        void at_player_turn_end();

        void update_current_player_display();

        void set_selected_province(Province* p);

        void update_selected_province(Coord src);

        void update_where_entity_can_move(Coord src, bool new_entity=false, bool reset=false, int new_entity_level = 1, int new_entity_type = true);

        void action_move_entity(Coord src, Coord dst);
        void action_new_entity(Coord dst, int level, bool type);
        void action_end_turn();

        void bandit_turn();

        void reset_map();
};
