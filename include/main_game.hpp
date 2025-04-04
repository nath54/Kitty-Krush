//
#pragma once
//
#include "model.hpp"
// #include "view.hpp"
#include "controller.hpp"
#include "events.hpp"
//
#define MAINLOOP_MAX_EVENTS_PER_LOOP 1000

//
class MainView;


//
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

        //
        void mainloop_execute_all_events();

        //
        void execute_event(Event* event);

        //
        void change_page(std::string new_page);

        //
        void quit();

};



