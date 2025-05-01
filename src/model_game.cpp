#include <cstdlib>  // srand() et rand()
#include <ctime> // time()
#include <deque>
#include <list>
#include <vector>
#include <map>
#include <algorithm>

#include "model_game.hpp"
#include "color.hpp"

#define MAP_EXISTS this->game_map != nullptr


// >> Getters <<

Map* GameModel::_map() { return this->game_map; }
int GameModel::_nb_players() { return this->nb_players; }
int GameModel::_current_player() { return this->current_player; }


// >> Getters (undirect) <<

int GameModel::get_tile_color(Coord c)
{ return (MAP_EXISTS) ? this->game_map->get_tile_color(c) : -1; }


int GameModel::get_tile_defense(Coord c)
{
    TILE_T tile = this->game_map->get_tile(c);
    if (tile == nullptr) { return 0; }

    int def_max = tile->get_defense();

    if (tile->_color() == NEUTRAL) { return def_max; } // No neighbours defense

    std::vector<Coord> n = neighbours(c);

    // Checking if there is an higher defense in the neighbours of the destination tile
    for (Coord v : n) {

        TILE_T neib = this->game_map->get_tile(v);
        if (neib == nullptr) { continue; }

        PROVINCE_T neib_prov = this->game_map->get_province(v);
        if (neib->_color() == NEUTRAL) { continue; }

        // Check if the destination tile and its neighbour tile have the same province
        if (neib->_color() == tile->_color()) {
            // If there is an element on this tile that has an higher defense
            if (neib->_element() != nullptr && neib->_element()->_defense() > def_max)
                { def_max = neib->_element()->_defense(); }
        }
    }

    return def_max;
}


ELEMENT_T GameModel::get_tile_element(Coord c)
{ return (MAP_EXISTS) ? this->game_map->get_tile_element(c) : nullptr; }

PROVINCE_T GameModel::get_tile_province(Coord c)
{ return (MAP_EXISTS) ? this->game_map->get_province(c) : nullptr; }

PROVINCE_T GameModel::get_province_at_coord(Coord c)
{ return (MAP_EXISTS) ? this->game_map->get_province(c) : nullptr; }


// >> Setters <<

void GameModel::set_tile_color(Coord coord, int color)
{ if (MAP_EXISTS) this->game_map->set_tile_color(coord, color); }

void GameModel::set_tile_element(Coord c, int elt_level, bool is_unit, int elt_attribute)
{ if (MAP_EXISTS) this->game_map->set_tile_element(c, elt_level, is_unit, elt_attribute); }

void GameModel::set_current_player(int new_player)
{ this->current_player = new_player; }

void GameModel::set_nb_players(int nb_players)
{ this->nb_players = nb_players; }

// >> Resetters <<

void GameModel::reset_tiles_layer()
{ if (MAP_EXISTS) this->game_map->reset_tiles_layer(); }

void GameModel::reset_bandits_layer()
{ if (MAP_EXISTS) this->game_map->reset_bandits_layer(); }

void GameModel::reset_provinces()
{ if (MAP_EXISTS) this->game_map->reset_provinces_layer(); }


// >> Turns <<

void GameModel::at_player_turn_start()
{
    for (std::pair<Coord, ELEMENT_T> it : *(this->game_map->_bandits_layer()))
        { it.second->convert_bandit(); }

    std::vector<PROVINCE_T>* provinces = this->game_map->_provinces_layer();

    for (PROVINCE_T p : *provinces) {

        if (p->_color() != this->current_player) { continue; }
        p->treasury_turn();

        for (std::pair<Coord, TILE_T> it : *(p->_tiles())) {
            UNIT_T unit = DCAST_UNIT_T(it.second->_element());
            if (unit == nullptr) { continue; }
            unit->can_move = true;
            if (p->_treasury() < 0)
                { this->game_map->create_bandit_element(it.first, true); }
        }

        if (p->_treasury() < 0) { p->set_treasury(0); }
    }
}

void GameModel::bandit_turn()
{
    int nb_coins = 0;
    bool some_bandits = false;
    std::vector<Coord> bandits = {};
    std::vector<Coord> bandit_camps = {};

    for (std::pair<Coord, ELEMENT_T> it : *(this->game_map->_bandits_layer())) {

        it.second->convert_bandit();

        UNIT_T unit = DCAST_UNIT_T(it.second);

        if (unit == nullptr) { // building
            this->set_tile_color(it.first, NEUTRAL);
            bandit_camps.push_back(it.first);
            continue;
        }

        some_bandits = true;
        unit->can_move = true;
        bandits.push_back(it.first);
    }

    // Move existing bandits
    for (Coord c : bandits) {
        TILE_T tile = this->game_map->get_tile(c);

        if (tile->_color() != NEUTRAL) {
            nb_coins++;
            if (this->game_map->get_province(c) == nullptr) {
                tile->convert_color(NEUTRAL);
                continue;
            }
        }

        std::vector<Coord> dest = {};
        std::vector<Coord> colored_dest = {};
        std::vector<Coord> n = neighbours(c);

        for (Coord v : n) {
            TILE_T t = this->game_map->get_tile(v);
            if (t == nullptr) { continue; }
            if (t->_element() == nullptr && this->get_tile_defense(v) == 0) {
                dest.push_back(v);
                if (t->_color() != NEUTRAL)
                    { colored_dest.push_back(v); }
            }
        }

        if (colored_dest.size() > 0) {
            int id = rand() % colored_dest.size();
            this->game_map->move_bandit(c, colored_dest[id]);
        }

        else if (tile->_color() == NEUTRAL && dest.size() > 0) {
            int id = rand() % dest.size();
            this->game_map->move_bandit(c, dest[id]);
        }
    }

    // If there is no bandit camp, create a new one
    if (some_bandits && bandit_camps.size() == 0) {

        std::vector<Coord> n = {};
        for (std::pair<Coord, TILE_T> t : *(this->game_map->_tiles_layer())) {
            if (t.second == nullptr) { continue; }
            if (t.second->_color() == NEUTRAL && t.second->_element() == nullptr)
                { n.push_back(t.second->_coord()); }
        }

        if (n.size() > 0) {
            int id = rand() % n.size();
            this->game_map->create_bandit_element(n[id], false);
            bandit_camps.push_back(n[id]);
        }
    }

    // Manage camps treasury and bandits creation
    for (Coord c : bandit_camps) {

        BUILDING_T b = DCAST_BUILDING_T(this->game_map->get_tile(c)->_element());

        if (nb_coins != 0)
            { b->update_treasury(1 + ((nb_coins - 1) / bandit_camps.size())); }

        if (b->treasury >= 3) {
            std::vector<Coord> n = neighbours(c);
            std::vector<Coord> dest = {};
            std::vector<Coord> colored_dest = {};

            for (Coord v : n) {
                TILE_T t = this->game_map->get_tile(v);
                if (t == nullptr) { continue; }
                if (t->_element() == nullptr && this->get_tile_defense(v) == 0) {
                    dest.push_back(v);
                    if (t->_color() != NEUTRAL)
                        { colored_dest.push_back(v); }
                }
            }

            if (colored_dest.size() > 0) {
                int id = rand() % colored_dest.size();
                this->game_map->create_bandit_element(colored_dest[id], true);
            }
            else if (dest.size() > 0) {
                int id = rand() % dest.size();
                this->game_map->create_bandit_element(dest[id], true);
            }

            b->update_treasury(-3);
        }
    }

    return;
}


// >> Check and Do <<

// [move_element]

bool GameModel::check_action_move_unit(Coord src, Coord dst)
{
    if (this->game_map == nullptr) { return false; }

    TILE_T src_tile = this->game_map->get_tile(src);
    TILE_T dst_tile = this->game_map->get_tile(dst);
    if (src_tile == nullptr || dst_tile == nullptr) { return false; }

    // Check if we move current player entity
    if (src_tile->_color() != this->current_player) { return false; }

    // Get the unit to move
    UNIT_T unit_to_move = DCAST_UNIT_T(src_tile->_element());
    if (unit_to_move == nullptr) { return false; } // building or nullptr
    if (!(unit_to_move->can_move)) { return false; } // already moved this turn
    if (unit_to_move->_defense() == 0) { return false; } // bandit

    PROVINCE_T src_prov = this->game_map->get_province(src);
    PROVINCE_T dst_prov = this->game_map->get_province(dst);

    // To avoid system errors, src_prov should always be different than nullptr
    if (src_prov == nullptr) { return false; }

    // Check if the movement is adjacent to the province
    if (!(this->game_map->adjacent_to_province(dst, src_prov))) { return false; }

    if (dst_prov != nullptr && dst_prov->_color() == src_prov->_color()) {

        if (dst_tile->_element() == nullptr) { return true; }

        // Get the unit at destination tile
        UNIT_T dst_unit = DCAST_UNIT_T(dst_tile->_element());
        if (dst_unit == nullptr) { return false; } // building, can't move
        if (dst_unit->is_bandit()) { return true; } // bandit, can move

        // If the destination unit hasn't the same level than the unit to move (no fusion of units to unit of higher level)
        if (dst_unit->_defense() == MAX_UNIT_LEVEL) { return false; }
        return (unit_to_move->_defense() == dst_unit->_defense());
    }

    // If the source unit is an hero, he can go anywhere
    if (unit_to_move->_defense() == MAX_UNIT_LEVEL) { return true; }

    // If the current unit to move has an higher defense than the destination tile, he can go there
    return (unit_to_move->_defense() > this->get_tile_defense(dst));
}


void GameModel::do_action_move_unit(Coord src, Coord dst)
{

    TILE_T src_tile = this->game_map->get_tile(src);
    TILE_T dst_tile = this->game_map->get_tile(dst);
    PROVINCE_T src_prov = this->game_map->get_province(src);
    PROVINCE_T dst_prov = this->game_map->get_province(dst);
    UNIT_T unit_to_move = DCAST_UNIT_T(src_tile->_element());

    if (dst_prov == src_prov) { // Same province, just move and may do fusion

        if (dst_tile->_element() != nullptr) {

            UNIT_T unit_at_dst = DCAST_UNIT_T(dst_tile->_element());

            if (unit_at_dst != nullptr) {

                if (unit_at_dst->is_bandit()) { // kill bandit
                    this->game_map->delete_bandit_element(dst);
                    dst_tile->set_element(unit_to_move);
                }
                //
                else // fusion
                    { unit_at_dst->upgrade(); }
            }
            //
            else { dst_tile->set_element(unit_to_move); }
        }
        //
        else { dst_tile->set_element(unit_to_move); }

        src_tile->reset_element();

        return;
    }

    // adverse/bandit town
    if (DCAST_BUILDING_T(dst_tile->_element()) != nullptr) {
        if (dst_tile->_element()->is_bandit())
            { src_prov->add_treasury(DCAST_BUILDING_T(dst_tile->_element())->treasury); }
        else
            { src_prov->add_treasury(dst_prov->_treasury()); }
    }

    // delete bandit element
    if (dst_tile->_element() != nullptr && dst_tile->_element()->is_bandit())
        { this->game_map->delete_bandit_element(dst); }

    dst_tile->set_element(unit_to_move);
    src_tile->reset_element();
    this->game_map->remove_tile_from_all_prov(dst);
    src_prov->add_tile(dst_tile);
    unit_to_move->can_move = false;

    // Look for same color tiles connexion
    std::vector<Coord> n = neighbours(dst);

    for (Coord v : n) {

        TILE_T tile = this->game_map->get_tile(v);
        if (tile == nullptr) { continue; }
        if (tile->_color() != src_prov->_color()) { continue; }
        PROVINCE_T prov = this->game_map->get_province(v);

        if (prov == nullptr) {
            src_prov->add_tile(tile);
            std::vector<Coord> n2 = neighbours(tile->_coord());
            n.insert(n.end(), n2.begin(), n2.end());
        }

        else if (prov != src_prov)
            { this->game_map->fusion_provinces(src_prov, prov); }

        else { continue; }
    }

    return;
}


// [new_element]

bool GameModel::check_action_new_element(Coord c, int elt_level, bool is_unit)
{
    // Check if the destination tile exists
    TILE_T tile = this->game_map->get_tile(c);
    if (tile == nullptr) { return false; }

    // Verify the entity_level is correct
    if (this->current_player == NEUTRAL && elt_level != 0) { return false; }

    else {
        if (elt_level <= 0) { return false; }
        if (is_unit && elt_level > MAX_UNIT_LEVEL) { return false; }
        else if (!is_unit && elt_level > MAX_BUILDING_LEVEL) { return false; }
    }

    // Get the unit cost
    int unit_cost = (is_unit ? units_new_costs[elt_level] : buildings_new_costs[elt_level]);

    // Check if there is a province of the current player color adjacent to this tile that has the money to pay the unit
    PROVINCE_T dst_prov = nullptr;

    for (PROVINCE_T prov : *(this->game_map->_provinces_layer())) {

        if (prov->is_adjacent_to_coord(c)) {
            if (prov->_color() != this->current_player) { continue; }
            if (prov->_treasury() < unit_cost) { continue; }
            dst_prov = prov;
            break;
        }
    }

    if (dst_prov == nullptr) { return false; }

    // Check if there is an unit in the tile destination
    if (tile->_element() != nullptr) {

        UNIT_T dst_unit = DCAST_UNIT_T(tile->_element());

        if( dst_unit != nullptr ){

            // If it is an unit of the same color
            if (dst_unit->_color() == this->current_player) {

                //
                if (dst_unit->_defense() == MAX_UNIT_LEVEL) { return false; }
                return (dst_unit->_defense() == elt_level);
            }
            else if (dst_unit->_defense() >= elt_level) { return false; }

        }

        BUILDING_T dst_building = DCAST_BUILDING_T(tile->_element());

        if( dst_building != nullptr && dst_building->_color() == this->current_player ){
            return false;
        }

    }

    if (dst_prov->_color() == this->current_player)
        { return true; } // Same province no defense

    // If the source unit is an hero, he can go anywhere
    if (elt_level == MAX_UNIT_LEVEL) { return true; }

    // If the current unit to move has an higher defense than the destination tile, he can go there
    return (elt_level > this->get_tile_defense(c));


}


void GameModel::do_action_new_element(Coord c, int elt_level, bool is_unit)
{
    int unit_cost = (is_unit ? units_new_costs[elt_level] : buildings_new_costs[elt_level]);

    TILE_T tile = this->game_map->get_tile(c);
    PROVINCE_T dst_prov = this->game_map->get_province(c);
    PROVINCE_T src_prov = nullptr;

    if (tile == nullptr) { return; }

    if (dst_prov == nullptr || dst_prov->_color() != this->current_player) {

        for (PROVINCE_T p : *(this->game_map->_provinces_layer())) {

            if (p->_color() != this->current_player) { continue; }
            if (p->_treasury() < unit_cost) { continue; }
            if (!p->is_adjacent_to_coord(c)) { continue; }
            src_prov = p;
            break;
        }
    }
    //
    else { src_prov = dst_prov; }

    if (src_prov == nullptr) { return; }

    if (dst_prov == src_prov) { // Same province

        if (tile->_element() != nullptr) { // bandit or fusion

            if (tile->_element()->is_bandit()) { // kill bandit
                this->game_map->delete_bandit_element(c);
                tile->set_element(CREATE_UNIT_T(this->current_player, elt_level));
            }
            //
            else { DCAST_UNIT_T(tile->_element())->upgrade(); } // fusion units
        }
        //
        else if (is_unit)
            { tile->set_element(CREATE_UNIT_T(this->current_player, elt_level)); }
        //
        else
            { tile->set_element(CREATE_BUILDING_T(this->current_player, elt_level)); }

        src_prov->remove_treasury(unit_cost);

        return;
    }

    // adverse/bandit town
    if (DCAST_BUILDING_T(tile->_element()) != nullptr) {
        if (tile->_element()->is_bandit())
            { src_prov->add_treasury(DCAST_BUILDING_T(tile->_element())->treasury); }
        else
            { src_prov->add_treasury(dst_prov->_treasury()); }
            // ! TODO: ne pas tout voler si plusieurs towns dans la province avderse
    }

    // delete bandit element
    if (tile->_element() != nullptr && tile->_element()->is_bandit())
        { this->game_map->delete_bandit_element(c); }

    if (is_unit) {
        tile->set_element(CREATE_UNIT_T(this->current_player, elt_level));
        DCAST_UNIT_T(tile->_element())->can_move = false;
    }
    //
    else
        { tile->set_element(CREATE_BUILDING_T(this->current_player, elt_level)); }

    this->game_map->remove_tile_from_all_prov(c);
    src_prov->add_tile(tile);
    src_prov->remove_treasury(unit_cost);

    // Look for same color tiles connexion
    std::vector<Coord> n = neighbours(c);

    for (Coord v : n) {

        TILE_T tile = this->game_map->get_tile(v);
        if (tile == nullptr) { continue; }
        if (tile->_color() != src_prov->_color()) { continue; }
        PROVINCE_T prov = this->game_map->get_province(v);

        if (prov == nullptr) {
            src_prov->add_tile(tile);
            std::vector<Coord> n2 = neighbours(tile->_coord());
            n.insert(n.end(), n2.begin(), n2.end());
        }

        else if (prov != src_prov)
            this->game_map->fusion_provinces(src_prov, prov);

        else { continue; }
    }

    return;
}


// [end_turn]

bool GameModel::check_action_end_turn() { return true; }

void GameModel::do_action_end_turn()
{
    int player_limit = this->current_player;

    this->current_player++;

    while (this->current_player != player_limit && !(this->check_map_has_provinces_of_color(this->current_player))) {
        this->current_player++;

        if (this->current_player > this->nb_players)
            { this->current_player = 1; }
    }
}


// >> Other functions <<

std::map<Coord, Color> GameModel::calculate_all_provinces_after_map_initialisation()
{

    if (this->game_map == nullptr) { return {}; }

    std::map< int, int > to_convert_num;
    std::map< Coord, int > visited;

    std::deque< Coord > to_visit_coord;
    std::deque< int > to_visit_num;

    int nb_tot_nums = 0;

    for (std::pair<Coord, TILE_T> it : *(this->game_map->_tiles_layer())) {

        TILE_T t = it.second;

        BUILDING_T building = DCAST_BUILDING_T( t->_element() );
        if (building == nullptr || building->_color() <= 0 || t->_color() <= 0) { continue; }

        to_visit_coord.push_back(it.first);
        to_visit_num.push_back(nb_tot_nums);
        nb_tot_nums++;
    }

    // WHILE THERE ARE TILES TO VISIT

    while (to_visit_coord.size() > 0) {

        Coord v = to_visit_coord.front();
        int num = to_visit_num.front();
        int color = this->get_tile_color(v);

        if (to_convert_num.count(num) > 0){ num = to_convert_num[num]; }

        to_visit_coord.pop_front();
        to_visit_num.pop_front();

        if (visited.count(v) > 0) { continue; }

        visited[v] = num;

        for (Coord vv : neighbours(v)) {

            int color2 = this->get_tile_color(vv);

            if (color2 == -1 || color2 != color) { continue; }

            if (visited.count(vv) > 0) {

                if (visited[vv] == num) { continue; }
                // else...
                to_convert_num[visited[vv]] = num;

                // Change all the different number to the same number for connex zones
                for (std::pair<Coord, int> it : visited) {
                    if (it.second == visited[vv]){
                        visited[it.first] = num;
                    }
                }

                continue;
            }

            to_visit_coord.push_back(vv);
            to_visit_num.push_back(num);
        }
    }

    // Extract all the different zones

    int crt_idx = 0;
    std::map<int, int> num_idx;
    std::map<int, Color> debug_colors;
    std::map<Coord, Color> map_colors_debug;
    std::vector< std::list<Coord> > all_province_zones;

    for (std::pair<Coord, int> it : visited) {

        int num = it.second;
        if(to_convert_num.count(num) > 0)
            { num = to_convert_num[num]; }

        if (num_idx.count(num) == 0) {
            num_idx[num] = crt_idx;
            debug_colors[num] = random_color();
            crt_idx++;
            all_province_zones.push_back((std::list<Coord>){});

        }

        all_province_zones[num_idx[num]].push_back(it.first);

        map_colors_debug[it.first] = debug_colors[num];

    }

    this->reset_provinces();

    for (std::list<Coord> list_of_tiles : all_province_zones)
        { this->game_map->add_province_from_list_of_tiles(list_of_tiles); }

    return map_colors_debug;
}


bool GameModel::check_map_has_provinces_of_color(int color)
    { return this->game_map->has_province_of_color(color); }


int GameModel::check_game_finished()
{
    /*
        returns :
            * -1 : Game not finished
            * 0 : Game finished, but no winning player
            * n > 0 : Game finished, and player n is victorious

    */

    std::vector<int> colors_left;

    for (int color = 1; color < this->nb_players; color++) {
        if (this->check_map_has_provinces_of_color(color))
            { colors_left.push_back(color); }
    }

    if (colors_left.size() == 0) { return 0; }

    if (colors_left.size() > 1 ) { return -1; }

    return colors_left[0];
}

