//
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <filesystem>
#include <map>
//
#include "main_game.hpp"
#include "view.hpp"
#include "utils.hpp"


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
void MainGame::change_to_in_game_page_with_map_file(std::string map_path){

    //
    this->reset_map();

    //
    this->load_map_from_file(map_path);

    //
    this->at_player_turn_start();

    //
    this->menu_state = 2;
}



//
void MainGame::change_page(std::string new_page){

    //
    if( this->main_view->win_page_manager->current_page == "in_game" ){

        this->save_map( "maps/saved_data/saved_map.kkmap" );

    }
    //
    else if( this->main_view->win_page_manager->current_page == "map_creator" ){

        this->save_map( "maps/map_created.kkmap" );

    }

    //
    if( new_page == "main_menu" ){

        //
        this->menu_state = 0;
    }
    //
    else if( new_page == "game_settings" ){

        //
        this->update_detected_all_map_files();

        //
        if( this->previous_detected_map_files != this->all_detected_map_files){

            //
            this->main_view->update_menu_game_settings(this);

            //
            this->previous_detected_map_files = this->all_detected_map_files;

        }

        //
        this->menu_state = 1;
    }
    //
    else if( new_page == "in_game" ){

        //
        this->main_view->map_viewer->clear();
        this->game_model->reset_bandits_layer();
        this->game_model->reset_provinces();
        this->game_model->reset_tiles_layer();

        //
        if( this->crt_map_file == "" ){
            //
            this->update_detected_all_map_files();
            //
            if( this->all_detected_map_files.size() == 0 ){
                //
                std::cerr << "\nError: no game map files found !\n";
            }
            //
            this->crt_map_file = this->all_detected_map_files[0];
        }

        this->change_to_in_game_page_with_map_file( this->crt_map_file );

        this->save_map( "maps/saved_data/saved_map.kkmap" );

        //
        this->menu_state = 2;

    }
    //
    else if( new_page == "map_creator" ){

        //
        for(int i = 6; i < 6 + 69 + 10 + 8; i++){
            //
            if(this->main_view->win_page_manager->pages["map_creator"]->elts.size() <= i){ continue; }
            //
            this->main_view->win_page_manager->pages["map_creator"]->elts[i]->visible = false;
        }

        //
        this->main_view->map_viewer->clear();
        this->game_model->reset_bandits_layer();
        this->game_model->reset_provinces();
        this->game_model->reset_tiles_layer();

        //
        if( check_file_exists("maps/map_created.kkmap") ){
            this->change_to_in_game_page_with_map_file( "maps/map_created.kkmap" );
        }

        //
        this->menu_state = 3;

    }
    //
    else {

        //
        std::cout << "Error: Unknown page : `" << new_page << "` !\n";

        //
        this->quit();
    }

    //
    this->main_view->win_page_manager->current_page = new_page;

}



//
void MainGame::quit(){

    //
    this->game_model->is_running = false;

}


//
void MainGame::update_detected_all_map_files(){

    //
    this->all_detected_map_files.clear();

    //
    std::string base_path = "maps/";
    //
    for (const auto & entry : std::filesystem::directory_iterator(base_path)){
        //
        std::string filepath = entry.path();
        //
        if( ! ends_with(filepath, ".kkmap") ){
            continue;
        }
        //
        this->all_detected_map_files.push_back( filepath );
    }

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

    //
    if( ! this->game_model->do_turn_start_map_loading ){
        this->game_model->do_turn_start_map_loading = true;
    }
    else{
        this->game_model->at_player_turn_start();
    }

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
    this->main_view->map_viewer->rect_current_player->cl = allPlayerColors[this->game_model->_current_player() - 1];

    //
    this->main_view->map_viewer->txt_current_player->txt = "Player " + std::to_string( this->game_model->_current_player() );

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
void MainGame::update_where_entity_can_move(Coord src, bool new_entity, bool reset, int new_entity_level, int new_entity_type){

    //
    if( this->game_model == nullptr || this->main_view == nullptr || this->main_view->map_viewer == nullptr ){ return; }

    //
    this->main_view->map_viewer->can_go_here_tiles.clear();

    //
    if( reset ){ return; }

    //
    if( new_entity ){

        //
        for( Province* p : *( this->game_model->_map()->_provinces_layer() ) ){

            //
            if (p->_color() != this->game_model->_current_player()) continue;

            //
            for ( std::pair<const Coord, Tile*> it : *(p->_tiles())) {

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

        }

        //
        for (std::set<Coord>::iterator it = this->main_view->map_viewer->can_go_here_tiles.begin(); it != this->main_view->map_viewer->can_go_here_tiles.end(); ) {

            Coord current_dst = *it; // Dereference the iterator to get the current element

            //
            if (!(this->game_model->check_action_new_element(current_dst, new_entity_level, new_entity_type))) {

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

    //
    else{

        //
        Province* p = this->game_model->get_province_at_coord( src );

        if( p == nullptr ){ return; }

        //
        for (std::pair<const Coord, Tile*> it : *(p->_tiles())) {

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
            if (!(this->game_model->check_action_move_unit(src, current_dst))) {

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
void MainGame::action_move_entity(Coord src, Coord dst)
{
    if (src == dst) { return; }

    if (this->game_model == nullptr
        || this->main_view == nullptr
        || this->main_view->map_viewer == nullptr)
        { return; }

    if (!this->game_model->check_action_move_unit(src, dst)) { return; }

    Province* old_prov_dst = this->game_model->get_province_at_coord(dst);

    this->game_model->do_action_move_unit(src, dst);

    Province* new_prov_dst = this->game_model->get_province_at_coord(dst);

    this->game_model->_map()->remove_tile_from_all_prov(dst);

    new_prov_dst->add_tile(this->game_model->_map()->get_tile(dst));

    if( old_prov_dst != nullptr && old_prov_dst != new_prov_dst)
        { this->game_model->_map()->split_province(dst, old_prov_dst); }

    // Check for provinces to remove

    std::list<Province*>* provinces_to_remove = this->game_model->_map()->_provinces_to_remove();
    //
    while (provinces_to_remove->size() > 0) {

        Province* province = provinces_to_remove->front();
        provinces_to_remove->pop_front();

        if (this->main_view->map_viewer->selected_province == province)
            { this->main_view->map_viewer->selected_province = nullptr; }

        // ! TODO: manage the memory correctly ! Because some pointers are lost !
        // delete province;
    }

    this->update_selected_province(dst);
}


//
void MainGame::action_new_entity(Coord dst, int level, bool type){

    //
    if( this->game_model == nullptr || this->main_view == nullptr || this->main_view->map_viewer == nullptr ){ return; }

    //
    if( !this->game_model->check_action_new_element(dst, level, type) ){
        return;
    }

    //
    Province* prev_prov_dst = this->game_model->get_province_at_coord(dst);

    //
    this->game_model->do_action_new_element(dst, level, type);

    //
    Province* new_prov_dst = this->game_model->get_province_at_coord(dst);

    //
    if( prev_prov_dst != nullptr && prev_prov_dst != new_prov_dst){
        //
        this->game_model->_map()->split_province( dst, prev_prov_dst );
    }

    //
    std::list<Province*>* provinces_to_remove = this->game_model->_map()->_provinces_to_remove();
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

    //
    this->update_selected_province(dst);

}


//
void MainGame::action_end_turn(){

    //
    if( this->game_model == nullptr || this->main_view == nullptr || this->main_view->map_viewer == nullptr ){ return; }

    //
    if( !this->game_model->check_action_end_turn() ){
        return;
    }

    //
    int crt_color = this->game_model->_current_player();

    //
    this->at_player_turn_end();

    //
    this->game_model->do_action_end_turn();

    //
    if( this->game_model->_current_player() < crt_color ){

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
    this->game_model->bandit_turn();
    //

}


//
void MainGame::reset_map(){

    //
    if( this->game_model == nullptr || this->main_view == nullptr || this->main_view->map_viewer == nullptr ){ return; }

    //
    this->game_model->_map()->reset_tiles_layer();
    this->game_model->_map()->reset_provinces_layer();
    this->game_model->_map()->reset_bandits_layer();
}
