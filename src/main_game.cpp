#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <filesystem>
#include <map>

#include "main_game.hpp"
#include "view.hpp"
#include "utils.hpp"

#define GAME_DOES_NOT_EXIST (this->game_model == nullptr || this->main_view == nullptr || this->main_view->map_viewer == nullptr)
#define MODEL this->game_model


// Constructor of the MainGame class, initializes all the components
MainGame::MainGame()
{
    this->game_model = new GameModel();
    this->main_view = new MainView(this->game_model);
    this->game_controller = new GameController(this->game_model);
    this->events_manager = new EventsManager();
}


// Destructor of the MainGame class, delete all the components
MainGame::~MainGame()
{
    delete this->game_model;
    delete this->main_view;
    delete this->game_controller;
    delete this->events_manager;
}


// Mainloop
void MainGame::mainloop()
{
    MODEL->is_running = true;

    while (MODEL->is_running) {

        this->main_view->at_frame_start();

        this->game_controller->manage_events(this->main_view->get_win_attr(), this->events_manager);

        this->main_view->update_display(this->menu_state);

        this->mainloop_execute_all_events();

        this->main_view->at_frame_end();
    }
}


void MainGame::change_to_in_game_page_with_map_file(std::string map_path)
{
    this->reset_map();

    this->load_map_from_file(map_path);

    this->at_player_turn_start();

    this->menu_state = 2;
}


void MainGame::change_page(std::string new_page)
{
    if (this->main_view->win_page_manager->current_page == "in_game")
        { this->save_map( "maps/saved_data/saved_map.kkmap" ); }
    //
    else if (this->main_view->win_page_manager->current_page == "map_creator")
        { this->save_map( "maps/map_created.kkmap" ); }

    if (new_page == "main_menu")
        { this->menu_state = 0; }
    //
    else if (new_page == "game_settings") {

        this->update_detected_all_map_files();

        if (this->previous_detected_map_files != this->all_detected_map_files) {

            this->main_view->update_menu_game_settings(this);

            this->previous_detected_map_files = this->all_detected_map_files;
        }

        this->menu_state = 1;
    }
    //
    else if (new_page == "in_game") {

        this->main_view->map_viewer->clear();
        MODEL->reset_bandits_layer();
        MODEL->reset_provinces();
        MODEL->reset_tiles_layer();
        this->main_view->map_viewer->game_end = false;

        if (this->crt_map_file == "") {

            this->update_detected_all_map_files();

            if (this->all_detected_map_files.size() == 0)
                { std::cerr << "\nError: no game map files found !\n"; }

            this->crt_map_file = this->all_detected_map_files[0];
        }

        this->change_to_in_game_page_with_map_file( this->crt_map_file );

        this->save_map( "maps/saved_data/saved_map.kkmap" );

        this->menu_state = 2;
    }
    //
    else if (new_page == "map_creator") {

        for (int i = 8; i < 8 + 70 + 10 + 8; i++) {

            if (this->main_view->win_page_manager->pages["map_creator"]->elts.size() > i)
                { this->main_view->win_page_manager->pages["map_creator"]->elts[i]->visible = false; }
        }

        this->main_view->map_viewer->clear();
        MODEL->reset_bandits_layer();
        MODEL->reset_provinces();
        MODEL->reset_tiles_layer();

        if (check_file_exists("maps/map_created.kkmap"))
            { this->change_to_in_game_page_with_map_file( "maps/map_created.kkmap" ); }

        this->main_view->map_viewer->game_end  = false;
        this->menu_state = 3;
    }
    //
    else {
        std::cout << "Error: Unknown page : `" << new_page << "` !\n";
        this->quit();
    }

    this->main_view->win_page_manager->current_page = new_page;
}


void MainGame::quit(){ MODEL->is_running = false; }


void MainGame::update_detected_all_map_files()
{
    this->all_detected_map_files.clear();

    std::string base_path = "maps/";

    for (const auto & entry : std::filesystem::directory_iterator(base_path)) {

        std::string filepath = entry.path();

        if (!ends_with(filepath, ".kkmap") ){ continue; }

        this->all_detected_map_files.push_back( filepath );
    }
}


// ACTIONS


void MainGame::at_player_turn_start()
{
    if (GAME_DOES_NOT_EXIST) { return; }

    //
    this->test_end_game();

    //
    this->update_current_player_display();

    // TODO: maybe update here with the first province of the current player
    this->set_selected_province( nullptr );

    if (!MODEL->do_turn_start_map_loading)
        { MODEL->do_turn_start_map_loading = true; }
    else
        { MODEL->at_player_turn_start(); }
}


void MainGame::at_player_turn_end() {  }


void MainGame::update_current_player_display()
{
    if (GAME_DOES_NOT_EXIST) { return; }

    this->main_view->map_viewer->rect_current_player->cl = allPlayerColors[MODEL->_current_player() - 1];

    this->main_view->map_viewer->txt_current_player->txt = "Player " + std::to_string(MODEL->_current_player());
}


void MainGame::set_selected_province(PROVINCE_T p)
{
    if (GAME_DOES_NOT_EXIST) { return; }

    this->main_view->map_viewer->selected_province = p;

    if( p == nullptr ) {

        this->main_view->map_viewer->elt_province_1->visible = false;
        this->main_view->map_viewer->elt_province_2->visible = false;
        //
        this->main_view->map_viewer->txt_province_treasury->visible = false;
        this->main_view->map_viewer->txt_province_expected_income->visible = false;
        //
        this->main_view->map_viewer->bt_unit_lvl1->disabled = true;
        this->main_view->map_viewer->bt_unit_lvl2->disabled = true;
        this->main_view->map_viewer->bt_unit_lvl3->disabled = true;
        this->main_view->map_viewer->bt_unit_lvl4->disabled = true;
        //
        this->main_view->map_viewer->bt_building_lvl2->disabled = true;

        return;
    }

    this->main_view->map_viewer->elt_province_1->visible = true;
    this->main_view->map_viewer->elt_province_2->visible = true;
    this->main_view->map_viewer->txt_province_treasury->visible = true;
    this->main_view->map_viewer->txt_province_expected_income->visible = true;

    int treasury = p->_treasury();

    this->main_view->map_viewer->bt_unit_lvl1->disabled = treasury < units_new_costs[1];
    this->main_view->map_viewer->bt_unit_lvl2->disabled = treasury < units_new_costs[2];
    this->main_view->map_viewer->bt_unit_lvl3->disabled = treasury < units_new_costs[3];
    this->main_view->map_viewer->bt_unit_lvl4->disabled = treasury < units_new_costs[4];
    this->main_view->map_viewer->bt_building_lvl2->disabled = treasury < buildings_new_costs[2];

    this->main_view->map_viewer->txt_province_treasury->txt = std::to_string(treasury);

    int expected_income = p->expected_income();

    if (expected_income >= 0)
        { this->main_view->map_viewer->txt_province_expected_income->txt = "(+" + std::to_string(expected_income) + ")"; }
    else
        { this->main_view->map_viewer->txt_province_expected_income->txt = "(" + std::to_string(expected_income) + ")"; }
}


void MainGame::update_selected_province(Coord src)
{
    if(GAME_DOES_NOT_EXIST) { return; }

    PROVINCE_T new_province = MODEL->get_province_at_coord( this->main_view->map_viewer->mouse_hover_tile );

    if( new_province == nullptr ){ return; }

    this->set_selected_province( new_province );
}


void MainGame::update_where_entity_can_move(Coord src, bool new_entity, bool reset, int new_entity_level, int new_entity_type)
{
    if(GAME_DOES_NOT_EXIST) { return; }

    this->main_view->map_viewer->can_go_here_tiles.clear();

    if (reset) { return; }

    if (new_entity) {

        for (PROVINCE_T p : *( MODEL->_map()->_provinces_layer())) {

            if (p->_color() != MODEL->_current_player()) { continue; }

            for (std::pair<const Coord, TILE_T> it : *(p->_tiles())) {

                Coord c = it.first;

                this->main_view->map_viewer->can_go_here_tiles.insert(c);

                for (Coord v : neighbours(c))
                    { this->main_view->map_viewer->can_go_here_tiles.insert(v); }
            }
        }

        for (std::set<Coord>::iterator it = this->main_view->map_viewer->can_go_here_tiles.begin();
             it != this->main_view->map_viewer->can_go_here_tiles.end();) {

            Coord current_dst = *it; // Dereference the iterator to get the current element

            if (!(MODEL->check_action_new_element(current_dst, new_entity_level, new_entity_type)))
                // Erase the current element and get a valid iterator to the next element
                { it = this->main_view->map_viewer->can_go_here_tiles.erase(it); }

            else // Move to the next element
                { ++it; }
        }
    }
    //
    else {

        PROVINCE_T p = MODEL->get_province_at_coord( src );

        if (p == nullptr) { return; }

        for (std::pair<const Coord, TILE_T> it : *(p->_tiles())) {

            Coord c = it.first;

            this->main_view->map_viewer->can_go_here_tiles.insert(c);

            for (Coord v : neighbours(c))
                { this->main_view->map_viewer->can_go_here_tiles.insert( v ); }
        }

        for (std::set<Coord>::iterator it = this->main_view->map_viewer->can_go_here_tiles.begin();
             it != this->main_view->map_viewer->can_go_here_tiles.end();) {

            Coord current_dst = *it; // Dereference the iterator to get the current element

            if (!(MODEL->check_action_move_unit(src, current_dst)))
                // Erase the current element and get a valid iterator to the next element
                { it = this->main_view->map_viewer->can_go_here_tiles.erase(it); }
            //
            else // Move to the next element
                { ++it; }
        }
    }
}


void MainGame::action_move_entity(Coord src, Coord dst)
{
    if (src == dst) { return; }

    if (GAME_DOES_NOT_EXIST) { return; }

    if (!MODEL->check_action_move_unit(src, dst)) { return; }

    PROVINCE_T old_prov_dst = MODEL->get_province_at_coord(dst);

    MODEL->do_action_move_unit(src, dst);

    PROVINCE_T new_prov_dst = MODEL->get_province_at_coord(dst);

    MODEL->_map()->remove_tile_from_all_prov(dst);

    new_prov_dst->add_tile(MODEL->_map()->get_tile(dst));

    if( old_prov_dst != nullptr && old_prov_dst != new_prov_dst)
        { MODEL->_map()->split_province(dst, old_prov_dst); }

    // Check for provinces to remove

    std::list<PROVINCE_T>* provinces_to_remove = MODEL->_map()->_provinces_to_remove();
    //
    while (provinces_to_remove->size() > 0) {

        PROVINCE_T province = provinces_to_remove->front();
        provinces_to_remove->pop_front();

        if (this->main_view->map_viewer->selected_province == province)
            { this->main_view->map_viewer->selected_province = nullptr; }

        // ! TODO: manage the memory correctly ! Because some pointers are lost !
        // delete province;
    }

    this->update_selected_province(dst);
}


void MainGame::action_new_entity(Coord dst, int level, bool type)
{
    if (GAME_DOES_NOT_EXIST) { return; }

    if (!MODEL->check_action_new_element(dst, level, type)) { return; }

    PROVINCE_T prev_prov_dst = MODEL->get_province_at_coord(dst);

    MODEL->do_action_new_element(dst, level, type);

    PROVINCE_T new_prov_dst = MODEL->get_province_at_coord(dst);

    if( prev_prov_dst != nullptr && prev_prov_dst != new_prov_dst)
        { MODEL->_map()->split_province( dst, prev_prov_dst ); }

    std::list<PROVINCE_T>* provinces_to_remove = MODEL->_map()->_provinces_to_remove();

    while (provinces_to_remove->size() > 0) {

        PROVINCE_T province = provinces_to_remove->front();
        provinces_to_remove->pop_front();

        if (this->main_view->map_viewer->selected_province == province)
            { this->main_view->map_viewer->selected_province = nullptr; }

        // ! TODO: manage the memory correctly ! Because some pointers are lost !
        // delete province;
    }

    this->update_selected_province(dst);
}


void MainGame::action_end_turn()
{
    if (GAME_DOES_NOT_EXIST) { return; }

    if (!MODEL->check_action_end_turn()) { return; }

    int crt_color = MODEL->_current_player();

    this->at_player_turn_end();

    MODEL->do_action_end_turn();

    if (MODEL->_current_player() <= crt_color) { this->bandit_turn(); }

    this->at_player_turn_start();

    //
    this->test_end_game();
}


void MainGame::bandit_turn()
{
    if(GAME_DOES_NOT_EXIST) { return; }
    MODEL->bandit_turn();
}


void MainGame::reset_map()
{
    if(GAME_DOES_NOT_EXIST) { return; }

    MODEL->_map()->reset_tiles_layer();
    MODEL->_map()->reset_provinces_layer();
    MODEL->_map()->reset_bandits_layer();
}


void MainGame::generate_random_map(int fn_to_gen){

    if(GAME_DOES_NOT_EXIST) { return; }

    this->main_view->map_viewer->clear();
    MODEL->_map()->reset_tiles_layer();
    MODEL->_map()->reset_provinces_layer();
    MODEL->_map()->reset_bandits_layer();

    /*
        THEMES:
            - 0:  green_grass && summer forest
            - 1:  sand && deep_water
            - 2:  snow && mountains
    */
    //
    static const std::vector<std::vector<int>> neutral_tile = (std::vector<std::vector<int>>){
        (std::vector<int>){ 10, 23, 26 },
        (std::vector<int>){ 19, 28 },
        (std::vector<int>){ 17, 24, 27 }
    };
    static const std::vector<std::vector<int>> negativ_tile = (std::vector<std::vector<int>>){
        (std::vector<int>){ 40, 31 },
        (std::vector<int>){ 0 },
        (std::vector<int>){ 49 }
    };
    //
    int theme = rand() % neutral_tile.size();

    //
    int nb_players = 2 + (rand() % 2);
    //
    int nb_provinces = nb_players * (1 + (rand() % 2));
    //
    int size_provinces = 2 + (rand() % 7);
    //
    bool bandits = (rand() % 2) == 0;

    //
    if(fn_to_gen == 1){
        MODEL->_map()->init_map(nb_players, nb_provinces, size_provinces, bandits);
    }
    else{
        MODEL->_map()->generate_random_map(nb_players, nb_provinces, size_provinces, bandits);
    }

    //
    for( std::pair<Coord, TILE_T> it : *(MODEL->_map()->_tiles_layer()) ){

        //
        int tile_num = 10;

        //
        if( it.second->_color() >= 0 ){

            if( rand() % 4 == 0 ){
                tile_num = neutral_tile[theme][ (rand() % neutral_tile[theme].size() ) ];
            }
            else{
                tile_num = neutral_tile[theme][0];
            }


        }
        else{

            if( rand() % 4 == 0 ){
                tile_num = negativ_tile[theme][ (rand() % negativ_tile[theme].size() ) ];
            }
            else{
                tile_num = negativ_tile[theme][0];
            }

        }

        this->main_view->map_viewer->add_tile_to_tile_layer( it.first.x, it.first.y, tile_num );

    }

    //
    this->main_view->map_viewer->complete_all_tile_layer_ground_base();

}


//
void MainGame::test_end_game(){

    //
    int game_end = this->game_model->check_game_finished();

    //
    if( game_end == -1 ){

        // Game not finished
        this->main_view->map_viewer->game_end = false;

        //
        for( WINDOW_ELT_T welt : this->main_view->map_viewer->elts_end_game ){

            //
            welt->visible = false;

        }

    }
    else{

        // Game finished
        this->main_view->map_viewer->game_end = true;

        //
        for( WINDOW_ELT_T welt : this->main_view->map_viewer->elts_end_game ){

            //
            welt->visible = true;

        }

        // update

        WINDOW_ELT_SPRITE_T sprite = DCAST_WINDOW_ELT_SPRITE_T( this->main_view->map_viewer->elts_end_game[4] );
        WINDOW_ELT_TEXT_T text = DCAST_WINDOW_ELT_TEXT_T( this->main_view->map_viewer->elts_end_game[2] );

        //
        if( game_end == 0){
            sprite->img_path = "res/bgs/loss.png";
            text->txt = "Game End : defeat for everyone !";
        }
        else{
            sprite->img_path = "res/bgs/victory.png";
            text->txt = "Game End : player " + std::to_string(game_end) + " win !";
        }

    }

}

