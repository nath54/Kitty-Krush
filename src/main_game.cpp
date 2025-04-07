//
#include "main_game.hpp"
#include "view.hpp"


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
            map_viewer->add_tile_to_tile_layer( coord.x, coord.y, tile_num );

        }

        //
        map_viewer->complete_all_tile_layer_ground_base();

    }

}


//
void MainGame::load_map_from_file(std::string map_path){

    //

}


//
void MainGame::quit(){

    //
    this->game_model->is_running = false;

}
