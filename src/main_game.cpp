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
#include "entity_data.hpp"


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
        this->at_player_turn_start();

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
    if( this->game_model == nullptr || this->main_view == nullptr || this->main_view->map_viewer == nullptr ){ return; }

    //
    this->update_current_player_display();

    // TODO: maybe update here with the first province of the current player
    this->set_selected_province( nullptr );

    // TODO: all the income of each province
    this->game_model->at_player_turn_start();

}


//
void MainGame::at_player_turn_end(){

    //
    if( this->game_model == nullptr || this->main_view == nullptr || this->main_view->map_viewer == nullptr ){ return; }


}


//
void MainGame::update_current_player_display(){

    //
    if( this->game_model == nullptr || this->main_view == nullptr || this->main_view->map_viewer == nullptr ){ return; }

    //
    this->main_view->map_viewer->rect_current_player->cl = allPlayerColors[this->game_model->get_current_player_color() - 1];

    //
    this->main_view->map_viewer->txt_current_player->txt = "Player " + std::to_string( this->game_model->get_current_player_color() );

}


//
void MainGame::set_selected_province(Province* p){

    //
    if( this->game_model == nullptr || this->main_view == nullptr || this->main_view->map_viewer == nullptr ){ return; }

    //
    this->main_view->map_viewer->selected_province = p;

    //
    if( p == nullptr ){

        //
        this->main_view->map_viewer->elt_province_1->visible = false;
        this->main_view->map_viewer->elt_province_2->visible = false;
        this->main_view->map_viewer->txt_province_treasury->visible = false;
        this->main_view->map_viewer->txt_province_expected_income->visible = false;

        //
        this->main_view->map_viewer->bt_unit_lvl1->disabled = true;
        this->main_view->map_viewer->bt_unit_lvl2->disabled = true;
        this->main_view->map_viewer->bt_unit_lvl3->disabled = true;
        this->main_view->map_viewer->bt_unit_lvl4->disabled = true;
        this->main_view->map_viewer->bt_building_lvl2->disabled = true;

        //
        return;
    }

    //
    this->main_view->map_viewer->elt_province_1->visible = true;
    this->main_view->map_viewer->elt_province_2->visible = true;
    this->main_view->map_viewer->txt_province_treasury->visible = true;
    this->main_view->map_viewer->txt_province_expected_income->visible = true;

    //
    int treasury = p->_treasury();

    //
    this->main_view->map_viewer->bt_unit_lvl1->disabled = treasury < units_new_costs[1];
    this->main_view->map_viewer->bt_unit_lvl2->disabled = treasury < units_new_costs[2];
    this->main_view->map_viewer->bt_unit_lvl3->disabled = treasury < units_new_costs[3];
    this->main_view->map_viewer->bt_unit_lvl4->disabled = treasury < units_new_costs[4];
    this->main_view->map_viewer->bt_building_lvl2->disabled = treasury < buildings_new_costs[2];

    //
    this->main_view->map_viewer->txt_province_treasury->txt = std::to_string(treasury);

    //
    int expected_income = p->expected_income();
    if( expected_income >= 0 ){
        this->main_view->map_viewer->txt_province_expected_income->txt = "(+" + std::to_string(expected_income) + ")";
    }
    else{
        this->main_view->map_viewer->txt_province_expected_income->txt = "(" + std::to_string(expected_income) + ")";
    }

}


//
void MainGame::update_selected_province(Coord src){

    //
    if( this->game_model == nullptr || this->main_view == nullptr || this->main_view->map_viewer == nullptr ){ return; }

    //
    Province* new_province = this->game_model->get_province_at_coord( this->main_view->map_viewer->mouse_hover_tile );

    //
    if( new_province == nullptr ){ return; }

    //
    this->set_selected_province( new_province );

}


//
void MainGame::update_where_entity_can_move(Coord src, bool new_entity, bool reset){

    //
    if( this->game_model == nullptr || this->main_view == nullptr || this->main_view->map_viewer == nullptr ){ return; }

    //
    this->main_view->map_viewer->can_go_here_tiles.clear();

    //
    if( reset ){ return; }

    //
    if( new_entity ){

        // TODO

    }

    //
    else{

        //
        Province* p = this->game_model->get_province_at_coord( src );

        if( p == nullptr ){ return; }

        //
        for ( std::pair<const Coord, Tile*> it : p->_tiles() ){

            //
            Coord c = it.first;

            //
            this->main_view->map_viewer->can_go_here_tiles.insert( c );

            //
            for ( Coord v : neighbours(c) ){

                //
                this->main_view->map_viewer->can_go_here_tiles.insert( v );

            }

        }

        //
        for (std::set<Coord>::iterator it = this->main_view->map_viewer->can_go_here_tiles.begin(); it != this->main_view->map_viewer->can_go_here_tiles.end(); ) {

            Coord current_dst = *it; // Dereference the iterator to get the current element

            //
            if (!(this->game_model->check_player_action_move_entity(src, current_dst))) {

                // Erase the current element and get a valid iterator to the next element
                it = this->main_view->map_viewer->can_go_here_tiles.erase(it);

            }

            //
            else {

                // Move to the next element
                ++it;
            }

        }

    }

}


//
void MainGame::action_move_entity(Coord src, Coord dst){

    //
    if( src == dst ){
        return;
    }

    //
    if( this->game_model == nullptr || this->main_view == nullptr || this->main_view->map_viewer == nullptr ){ return; }

    //
    if( !this->game_model->check_player_action_move_entity(src, dst) ){
        return;
    }

    //
    this->game_model->do_player_action_move_entity(src, dst);

    // Check for provinces to remove

    //
    std::list<Province*>* provinces_to_remove = this->game_model->get_map()->get_provinces_to_remove();
    //
    while ( provinces_to_remove->size() > 0 ){

        //
        Province* province = provinces_to_remove->front();
        //
        provinces_to_remove->pop_front();

        //
        if( this->main_view->map_viewer->selected_province == province ){
            this->main_view->map_viewer->selected_province = nullptr;
        }

        // TODO: manage the memory correctly ! Because some pointers are lost !
        // delete province;

    }


}


//
void MainGame::action_new_entity(Coord dst, int level, bool type){

    //
    if( this->game_model == nullptr || this->main_view == nullptr || this->main_view->map_viewer == nullptr ){ return; }

    //
    if( !this->game_model->check_player_action_new_entity(dst, level, type) ){
        return;
    }

    //
    this->game_model->do_player_action_new_entity(dst, level, type);

}


//
void MainGame::action_end_turn(){

    //
    if( this->game_model == nullptr || this->main_view == nullptr || this->main_view->map_viewer == nullptr ){ return; }

    //
    if( !this->game_model->check_player_action_end_turn() ){
        return;
    }

    //
    int crt_color = this->game_model->get_current_player_color();

    //
    this->at_player_turn_end();

    //
    this->game_model->do_player_action_end_turn();

    //
    if( this->game_model->get_current_player_color() < crt_color ){

        //
        this->bandit_turn();

    }

    //
    this->at_player_turn_start();

}


//
void MainGame::bandit_turn(){

    //
    if( this->game_model == nullptr || this->main_view == nullptr || this->main_view->map_viewer == nullptr ){ return; }

    //

}
