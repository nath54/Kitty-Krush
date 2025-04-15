//
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <map>
//
#include "main_game.hpp"
#include "view.hpp"
#include "strings_utils.hpp"


// Constructor of the MainGame class, initializes all the components
MainGame::MainGame(){

    //
    this->game_model = new GameModel();

    //
    this->main_view = new MainView( this->game_model );

    //
    this->game_controller = new GameController( this->game_model );

    //
    this->events_manager = new EventsManager();

}


// Destructor of the MainGame class, delete all the components
MainGame::~MainGame(){

    //
    delete this->game_model;
    delete this->main_view;
    delete this->game_controller;
    delete this->events_manager;

}


// Mainloop
void MainGame::mainloop(){

    //
    this->game_model->is_running = true;

    //
    while(this->game_model->is_running){

        //
        this->main_view->at_frame_start();

        //
        this->game_controller->manage_events(this->main_view->get_win_attr(), this->events_manager);

        //
        this->main_view->update_display(this->menu_state);

        //
        this->mainloop_execute_all_events();

        //
        this->main_view->at_frame_end();
    }

}



//
void MainGame::change_page(std::string new_page){

    //
    this->main_view->win_page_manager->current_page = new_page;

    //
    if( new_page == "main_menu" ){

        //
        this->menu_state = 0;
    }
    //
    else if( new_page == "game_settings" ){

        //
        this->menu_state = 1;
    }
    //
    else if( new_page == "in_game" ){

        //
        this->load_map_from_file("res/map_tests/map_2.kkmap");

        //
        this->menu_state = 2;
    }
    //
    else {

        //
        cout << "Error: Unknown page : `" << new_page << "` !\n";

        //
        this->quit();
    }
}



//
void MainGame::quit(){

    //
    this->game_model->is_running = false;

}
