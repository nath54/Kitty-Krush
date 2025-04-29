#pragma once

#include <iostream>
#include <string>
#include <string_view>

#include "model_map.hpp"
#include "color.hpp"


//
class GameModel {

    private:

        Map* game_map = nullptr; // Map of the game
        usint nb_players = 2; // Number of players
        usint current_player = 1; // Current player color

    public:

        // Game state (additional attribute)
        bool is_running = false;

        //
        bool do_turn_start_map_loading = true;

        // Constructor
        GameModel() { this->game_map = new Map(); };

        // Getters
        Map* _map();
        usint _nb_players();
        usint _current_player();

        // Getters (undirect)
        int get_tile_color(Coord c);
        usint get_tile_defense(Coord c);
        ELEMENT_T get_tile_element(Coord c);
        PROVINCE_T get_tile_province(Coord c);
        PROVINCE_T get_province_at_coord(Coord c);

        // Setters
        void set_tile_color(Coord coord, int color);
        void set_tile_element(Coord c, usint elt_level, bool is_unit, int element_attribute=0);
        void set_current_player(int new_player);
        void set_nb_players(int nb_players);

        // Resetters
        void reset_provinces();
        void reset_tiles_layer();
        void reset_bandits_layer();

        // Turns
        void at_player_turn_start();
        void bandit_turn();

        // Check and Do
        bool check_action_move_unit(Coord src, Coord dst);
        void do_action_move_unit(Coord src, Coord dst);
        //
        bool check_action_new_element(Coord c, int elt_level, bool is_unit);
        void do_action_new_element(Coord c, int elt_level, bool is_unit);
        //
        bool check_action_end_turn();
        void do_action_end_turn();

        // Other functions
        std::map<Coord, Color> calculate_all_provinces_after_map_initialisation();
};
