#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <map>
#include <filesystem> // Required for C++17 filesystem features

#include "color.hpp"
#include "main_game.hpp"
#include "view.hpp"
#include "utils.hpp"
#include "model_game.hpp"


//
void MainGame::set_map_from_data(
    std::map< Coord, int >* tiles_layer ,           // Tiles layer
    std::map< Coord, int >* colors_layer,           // Colors layer
    std::map< Coord, int >* entities_layer,         // Entities layer
    std::map< Coord, int >* entities_attributes,    // Entities attributes (treasury or can_move )
    int current_color_to_play,
    bool do_turn_start
){

    //
    WINDOW_ELT_MAP_VIEWER_T map_viewer = this->main_view->map_viewer;
    GameModel* game_model = this->game_model;

    //
    if ( game_model == nullptr ){

        //
        std::cout << "Error : no game model !\n";
        //
        this->quit();
    }

    //
    if ( map_viewer == nullptr ){

        //
        std::cout << "Error : no map viewer !\n";
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
            int entity_attribute = 0;

            //
            if( entities_attributes->count(coord) > 0 ){
                //
                entity_attribute = (*entities_attributes)[coord];
            }

            //
            if (entity_num < 0 ){ continue; }

            if (entity_num >= 10) { // Warriors

                //
                game_model->set_tile_element( coord, entity_num - 10, true, entity_attribute );

            }

            else{ // Buildings

                //
                game_model->set_tile_element( coord, entity_num, false, entity_attribute );

            }

        }

    }

    //
    this->main_view->map_viewer->debug_colors = game_model->calculate_all_provinces_after_map_initialisation();

    //
    game_model->set_nb_players(1);

    //
    std::map<Coord, ELEMENT_T>* bandit_layer = game_model->_map()->_bandits_layer();
    //
    PROVINCE_T p = nullptr;
    //
    for( std::pair<Coord, TILE_T> it : *(game_model->_map()->_tiles_layer()) ){
        //
        TILE_T t = it.second;
        if ( t == nullptr ) { continue; }

        //
        if ( t->_color() > game_model->_nb_players() ) {
            game_model->set_nb_players(t->_color());
        }

        if ( t->_element() == nullptr ) { continue; }

        // Ajout au bandit layer
        if ( t->_color() == 0 ) {
            bandit_layer->insert( std::pair<Coord, ELEMENT_T>(it.first, t->_element()) );
        }

        //
        BUILDING_T b = DCAST_BUILDING_T(t->_element());
        //
        if ( b == nullptr ) { continue; }

        //
        if ( p != nullptr && b->treasury > 0 ) { p->set_treasury( b->treasury ); }

    }

    //
    game_model->set_current_player( current_color_to_play );

    //
    game_model->do_turn_start_map_loading = do_turn_start;

    // Init data

    WINDOW_ELT_T player_rect_elt = this->main_view->win_page_manager->pages["in_game"]->elts[2];
    WINDOW_ELT_T player_text_elt = this->main_view->win_page_manager->pages["in_game"]->elts[3];

    //
    WINDOW_ELT_RECT_T player_rect = DCAST_WINDOW_ELT_RECT_T(player_rect_elt);
    WINDOW_ELT_TEXT_T player_text = DCAST_WINDOW_ELT_TEXT_T(player_text_elt);

    //
    if ( player_rect != nullptr ){
        //
        player_rect->cl = allPlayerColors[game_model->_current_player() - 1];
    }

    //
    if ( player_text != nullptr ){
        //
        player_text->txt = "Player " + std::to_string(game_model->_current_player());
    }

}




//
std::vector<std::string> splitStringStream(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(s); // Create a stringstream from the input string

    // Use std::getline, specifying the stream, token, and delimiter
    while (std::getline(ss, token, delimiter)) {
        // Optionally, ignore empty tokens if needed
        if (!token.empty()) {
             tokens.push_back(token);
        }
    }
    return tokens;
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

    //
    std::map< Coord, int >* entities_attributes = nullptr;

    //
    int current_color_to_play = 1;

    //
    bool do_turn_start = true;

    //
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
                //
                if( entities_attributes == nullptr ){
                    //
                    entities_attributes = new std::map< Coord, int >();
                }
                //
                else{
                    //
                    std::cerr << "Error, multiple entities_layer parts in map file : " << map_path << std::endl;
                    this->quit();
                }
            }

            //
            continue;
        }

        //
        else if( current_type == "grid" ){

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

        //
        else if( current_type == "coordinate_value" ){

            //
            std::vector<std::string> split_text = splitStringStream(line, ';');

            //
            if( split_text.size() <=  2 ){ continue; }

            //
            Coord coord = Coord(
                std::stoi( split_text[0] ), // x
                std::stoi( split_text[1] )  // y
            );

            //
            int value = std::stoi( split_text[2] );

            //
            int value2 = 0;
            if( split_text.size() >= 4 ){ value2 = std::stoi( split_text[3] ); }

            //
            if (current_layer == "tiles_layer") {
                (*tiles_layer)[coord] = value;
            }
            else if (current_layer == "colors_layer") {
                (*colors_layer)[coord] = value;
            }
            else if (current_layer == "entities_layer") {
                //
                (*entities_layer)[coord] = value;
                //
                if( value2 != 0 ){
                    (*entities_attributes)[coord] = value2;
                }
            }

        }

        //
        else if( current_type == "value" ){

            //
            int value = std::stoi( line );

            //
            if( current_layer == "current_color_to_play" ){
                current_color_to_play = value;
            }
            //
            else if( current_layer == "do_turn_start" ){
                do_turn_start = (bool)value;
            }

        }

    }

    file.close();

    // Now send the layers to the viewer
    this->set_map_from_data(tiles_layer, colors_layer, entities_layer, entities_attributes, current_color_to_play, do_turn_start);

    // Now, free the memory
    if( tiles_layer != nullptr ){ delete tiles_layer; }
    if( colors_layer != nullptr ){ delete colors_layer; }
    if( entities_layer != nullptr ){ delete entities_layer; }
    if( entities_attributes != nullptr ){ delete entities_attributes; }

}


//
void MainGame::save_map(std::string file_path) {

    // Ensure directory exists
    std::filesystem::path path_obj(file_path);
    std::filesystem::path dir = path_obj.parent_path();

    if (!dir.empty() && !std::filesystem::exists(dir)) {
        std::error_code ec;
        if (!std::filesystem::create_directories(dir, ec)) {
            std::cerr << "Error creating directories for: " << dir << "\nReason: " << ec.message() << std::endl;
            return;
        }
    }

    // Open the file
    std::ofstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error opening file for saving: " << file_path << std::endl;
        return;
    }

    //
    std::vector<Coord> coords;

    // -- Save the tile layer --

    file << "# coordinate_value, tiles_layer\n";

    for (auto it : this->main_view->map_viewer->tiles_layers) {

        Coord coord = it.first;
        WINDOW_ELT_MAP_TILE_T tile = it.second;

        coords.push_back(coord);

        file << coord.x << ";" << coord.y << ";" << tile->tile << "\n";
    }

    // -- Save the color layer --

    file << "# coordinate_value, colors_layer\n";

    for (Coord c : coords) {

        int cl = this->game_model->get_tile_color(c);

        if (cl < 0) continue;

        file << c.x << ";" << c.y << ";" << cl << "\n";
    }

    // -- Save the entity layer --

    file << "# coordinate_value, entities_layer\n";

    for (Coord c : coords) {

        ELEMENT_T e = this->game_model->get_tile_element(c);

        if (!e) continue;

        BUILDING_T b = DCAST_BUILDING_T(e);
        UNIT_T u = DCAST_UNIT_T(e);

        PROVINCE_T p = this->game_model->get_province_at_coord(c);

        if (b != nullptr) {

            //
            if( p != nullptr ){
                file << c.x << ";" << c.y << ";" << b->_defense() << ";" << p->_treasury() << "\n";
            } else if (b->treasury == 0) {
                file << c.x << ";" << c.y << ";" << b->_defense() << "\n";
            } else {
                file << c.x << ";" << c.y << ";" << b->_defense() << ";" << b->treasury << "\n";
            }

        } else if (u != nullptr) {

            if (u->can_move) {
                file << c.x << ";" << c.y << ";" << u->_defense() + 10 << "\n";
            } else {
                file << c.x << ";" << c.y << ";" << u->_defense() + 10 << ";1\n";
            }
        }
    }

    // -- Save the current player to play --

    file << "# value, current_color_to_play\n";
    file << this->game_model->_current_player() << "\n";

    // -- Save saying do not do turn start at loading --

    file << "# value, do_turn_start\n";
    file << "0" << "\n";


    file.close();
}


