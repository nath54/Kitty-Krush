//
#pragma once
//
#include "model.hpp"
#include "view.hpp"
#include "controller.hpp"


//
class MainGame{

    private:

        // MVC Modelisation:
        // Model
        GameModel* game_model;
        // View
        MainView* main_view;
        // Controller
        GameController* game_controller;

        // Menu State
        //   - 0 = Main Menu
        //   - 1 = Game Settings
        //   - 2 = In Game
        int menu_state = 0;

    public:

        // Constructor
        MainGame();

        // Destructor
        ~MainGame();

        // Mainloop
        void mainloop();

};
