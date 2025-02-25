//
#include "main_game.hpp"


// Constructor of the MainGame class, initializes all the components
MainGame::MainGame(){

    //
    this->game_model = new GameModel();

    //
    this->main_view = new MainView( this->game_model );

    //
    this->game_controller = new GameController( this->game_model );

}


// Destructor of the MainGame class, delete all the components
MainGame::~MainGame(){

    //
    delete this->game_model;
    delete this->main_view;
    delete this->game_controller;

}


// Mainloop
void MainGame::mainloop(){

    //
    this->game_model->is_running = true;

    //
    while(this->game_model->is_running){

        //
        this->game_controller->manage_events();

        //
        this->main_view->update_display();

    }

}
