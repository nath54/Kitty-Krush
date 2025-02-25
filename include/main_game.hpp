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

    public:

        // Constructor
        MainGame();

        // Destructor
        ~MainGame();

        // Mainloop
        void mainloop();

};
