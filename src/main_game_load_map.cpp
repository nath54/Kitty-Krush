//
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <map>
//
#include "color.hpp"
#include "main_game.hpp"
#include "view.hpp"
#include "strings_utils.hpp"


//
void MainGame::set_map_from_data(
    std::map< Coord, int >* tiles_layer ,      // Tiles layer
    std::map< Coord, int >* colors_layer,      // Colors layer
    std::map< Coord, int >* entities_layer     // Entities layer
){

    //
    WindowEltMapViewer* map_viewer = this->main_view->map_viewer;
    GameModel* game_model = this->game_model;

    //
    if ( game_model == nullptr ){

        //
        cout << "Error : no game model !\n";
        //
        this->quit();
    }

    //
    if ( map_viewer == nullptr ){

        //
        cout << "Error : no map viewer !\n";
        //
        this->quit();
    }

    //
    if( tiles_layer != nullptr ){

        //
        for ( std::pair<Coord, int> it : *tiles_layer ){

            //
            Coord coord = it.first;
            int tile_num = it.second;

            //
            if (tile_num <= 0) { continue; }

            //
            map_viewer->add_tile_to_tile_layer( coord.x, coord.y, tile_num );

        }

        //
        map_viewer->complete_all_tile_layer_ground_base();

    }

    //
    if( colors_layer != nullptr ){

        //
        for ( std::pair<Coord, int> it : *colors_layer ){

            //
            Coord coord = it.first;
            int color_num = it.second;

            //
            if (color_num < 0){ continue; }

            //
            map_viewer->set_color_to_color_layer( coord.x, coord.y, color_num );
            //
            game_model->set_tile_color( coord, color_num );

        }

    }

    //
    if( entities_layer != nullptr ){

        //
        for ( std::pair<Coord, int> it : *entities_layer ){

            //
            Coord coord = it.first;
            int entity_num = it.second;

            //
            if (entity_num < 0 ){ continue; }

            if (entity_num >= 10) { // Warriors

                //
                map_viewer->set_entity_to_entity_layer( coord.x, coord.y, entity_num - 10, true );
                //
                game_model->set_tile_entity( coord, entity_num - 10, true );

            }

            else{ // Buildings

                //
                map_viewer->set_entity_to_entity_layer( coord.x, coord.y, entity_num, false );
                //
                game_model->set_tile_entity( coord, entity_num, false );

            }

        }

        //
        map_viewer->update_closest_building_of_color();

    }

    //
    game_model->calculate_all_provinces_after_map_initialisation();

    // Init data

    WindowElt* player_rect_elt = this->main_view->win_page_manager->pages["in_game"]->elts[2];
    WindowElt* player_text_elt = this->main_view->win_page_manager->pages["in_game"]->elts[3];

    //
    WindowEltRect* player_rect = dynamic_cast<WindowEltRect*>(player_rect_elt);
    WindowEltText* player_text = dynamic_cast<WindowEltText*>(player_text_elt);

    //
    if ( player_rect != nullptr ){
        //
        player_rect->cl = allPlayerColors[map_viewer->current_color_to_play - 1];
    }

    //
    if ( player_text != nullptr ){
        //
        player_text->txt = "Player " + std::to_string(map_viewer->current_color_to_play);
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
    std::map< Coord, int >* tiles_layer = nullptr;
    std::map< Coord, int >* colors_layer = nullptr;
    std::map< Coord, int >* entities_layer = nullptr;

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
                    tiles_layer = new std::map< Coord, int >();
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
                    colors_layer = new std::map< Coord, int >();
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
                    entities_layer = new std::map< Coord, int >();
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

            // Clean whitespace
            cell = trim(cell);

            //
            if (!cell.empty()) {
                int value = std::stoi(cell);
                Coord coord = Coord(x, y);

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

    // Now send the layers to the viewer
    this->set_map_from_data(tiles_layer, colors_layer, entities_layer);

    // Now, free the memory
    if( tiles_layer != nullptr ){ delete tiles_layer; }
    if( colors_layer != nullptr ){ delete colors_layer; }
    if( entities_layer != nullptr ){ delete entities_layer; }

}
