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


// ACTIONS


//
void MainGame::at_player_turn_start(){

    //

}


//
void MainGame::at_player_turn_end(){

    //

}


//
void MainGame::update_selected_province(Coord src){

    //
    if( this->game_model == nullptr ){ return; }
    if( this->main_view == nullptr ) { return; }
    if( this->main_view->map_viewer == nullptr ) { return; }

    //
    this->main_view->map_viewer->selected_province = this->game_model->get_province_at_coord( this->main_view->map_viewer->mouse_hover_tile );

}


//
void MainGame::update_where_entity_can_move(Coord src, bool new_entity){

    //
    if( new_entity ){

        // TODO

    }

    //
    else{

        // TODO

    }

}


//
void MainGame::action_move_entity(Coord src, Coord dst){

    //

}


//
void MainGame::action_new_entity(Coord dst, int level, bool type){

    //

}


//
void MainGame::action_end_turn(){

    //


}


//
void MainGame::bandit_turn(){

    //

}
