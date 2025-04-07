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
        this->game_controller->manage_events(this->main_view->get_win_attr(), this->events_manager);

        //
        this->main_view->update_display(this->menu_state);

        //
        this->mainloop_execute_all_events();

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
        this->load_map_from_file("res/map_tests/map_1.kkmap");

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
void MainGame::set_map_from_data(
    std::map< Vector2, int >* tiles_layer ,      // Tiles layer
    std::map< Vector2, int >* colors_layer,      // Colors layer
    std::map< Vector2, int >* entities_layer     // Entities layer
){

    //
    WindowElt* map_viewer_elt = this->main_view->win_page_manager->pages["in_game"]->elts[0];

    //
    WindowEltMapViewer* map_viewer = dynamic_cast<WindowEltMapViewer*>(map_viewer_elt);

    //
    if ( map_viewer == nullptr ){

        //
        cout << "Error : map_viewer can't convert to WindowEltMapViewer* !\n";
        //
        this->quit();
    }

    //
    if( tiles_layer != nullptr ){

        //
        for ( std::pair<Vector2, int> it : *tiles_layer ){

            //
            Vector2 coord = it.first;
            int tile_num = it.second;

            //
            // cout << "DEBUG tile add | x = " << coord.x << " | y = " << coord.y << " | tile = " << tile_num << "\n";

            //
            map_viewer->add_tile_to_tile_layer( coord.x, coord.y, tile_num );

        }

        //
        map_viewer->complete_all_tile_layer_ground_base();

    }


    //
    if( tiles_layer != nullptr ){

        //
        for ( std::pair<Vector2, int> it : *tiles_layer ){

            //
            Vector2 coord = it.first;
            int tile_color = it.second;

            //
            this->game_model->game_map->add_tile_to_color_layer( coord.x, coord.y, tile_color );

        }

        //
        map_viewer->complete_all_tile_layer_ground_base();

    }

}


//
void MainGame::load_map_from_file(std::string map_path) {

    // Open the file
    std::ifstream file(map_path);
    if (!file.is_open()) {
        std::cerr << "Error opening map file: " << map_path << std::endl;
        this->quit();
    }

    // Initial data
    std::map< Vector2, int >* tiles_layer = nullptr;
    std::map< Vector2, int >* colors_layer = nullptr;
    std::map< Vector2, int >* entities_layer = nullptr;

    std::string line;
    std::string current_type = "";
    std::string current_layer = "";

    int y = 0;

    while (std::getline(file, line)) {

        // Trim whitespace
        if (line.empty()) continue;

        // New section starts
        if (line[0] == '#') {

            // Reset y for new grid section
            y = 0;

            std::stringstream ss(line);
            std::string token;

            // Format: # type, layer_name
            std::getline(ss, token, ','); // skip '# type'
            current_type = token.substr(1); // remove '#'

            std::getline(ss, token); // layer name
            current_layer = token;

            // Trim possible leading/trailing whitespaces
            current_type = trim(current_type);
            current_layer = trim(current_layer);

            //
            if (current_layer == "tiles_layer") {
                //
                if(tiles_layer == nullptr){
                    //
                    tiles_layer = new std::map< Vector2, int >();
                }
                else{
                    //
                    std::cerr << "Error, multiple tiles_layer parts in map file : " << map_path << std::endl;
                    this->quit();
                }
            }
            else if (current_layer == "colors_layer") {
                //
                if(colors_layer == nullptr){
                    //
                    colors_layer = new std::map< Vector2, int >();
                }
                else{
                    //
                    std::cerr << "Error, multiple colors_layer parts in map file : " << map_path << std::endl;
                    this->quit();
                }
            }
            else if (current_layer == "entities_layer") {
                //
                if(entities_layer == nullptr){
                    //
                    entities_layer = new std::map< Vector2, int >();
                }
                else{
                    //
                    std::cerr << "Error, multiple entities_layer parts in map file : " << map_path << std::endl;
                    this->quit();
                }
            }

            //
            continue;
        }

        // Process grid line (semicolon-separated integers)
        std::stringstream ss(line);
        std::string cell;
        int x = 0;

        while (std::getline(ss, cell, ';')) {

            //
            // cout << "DEBUG CELL | cell = `" << cell << "` | x = " << x << " - y = " << y << " \n";

            // Clean whitespace
            cell = trim(cell);

            //
            // cout << "DEBUG TRIMED CELL | cell = `" << cell << " | empty = " << !cell.empty() << " \n";

            //
            if (!cell.empty()) {
                int value = std::stoi(cell);
                Vector2 coord = Vector2(x, y);

                if (current_type == "grid") {

                    if (current_layer == "tiles_layer") {
                        (*tiles_layer)[coord] = value;
                    }
                    else if (current_layer == "colors_layer") {
                        (*colors_layer)[coord] = value;
                    }
                    else if (current_layer == "entities_layer") {
                        (*entities_layer)[coord] = value;
                    }
                }

                x++;
            }
        }

        y++;
    }

    file.close();

    //
    // cout << "DEBUG | Lecture finished and file closed ! \n";

    // Now send the layers to the viewer
    this->set_map_from_data(tiles_layer, colors_layer, entities_layer);

    // Now, free the memory
    if( tiles_layer != nullptr ){ delete tiles_layer; }
    if( colors_layer != nullptr ){ delete colors_layer; }
    if( entities_layer != nullptr ){ delete entities_layer; }

}


//
void MainGame::quit(){

    //
    this->game_model->is_running = false;

}
