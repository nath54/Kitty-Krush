#include <cstdlib>  // srand() et rand()
#include <ctime> // time()
#include <deque>
#include <list>
#include <vector>
#include <map>
#include <algorithm>

#include "model_game.hpp"

#define MAP_EXISTS this->game_map != nullptr


// >> Getters <<

Map* GameModel::_map() { return this->game_map; }
usint GameModel::_nb_players() { return this->nb_players; }
usint GameModel::_current_player() { return this->current_player; }


// >> Getters (undirect) <<

int GameModel::get_tile_color(Coord c)
{ return (MAP_EXISTS) ? this->game_map->get_tile_color(c) : -1; }


usint GameModel::get_tile_defense(Coord c)
{
    Tile* tile = this->game_map->get_tile(c);
    if (tile == nullptr) { return 0; }

    usint def_max = tile->get_defense();

    Province *prov = this->game_map->get_province(c);
    if (prov == nullptr) { return def_max; } // No neighbours defense
    if (prov->_color() == this->current_player) { return 0; } // Can move if same province

    std::vector<Coord> n = neighbours(c);

    // Checking if there is an higher defense in the neighbours of the destination tile
    for (Coord v : n) {

        Tile* neib = this->game_map->get_tile(v);
        if (neib == nullptr) { continue; }

        Province* neib_prov = this->game_map->get_province(v);
        if (neib_prov == nullptr) { continue; }

        // Check if the destination tile and its neighbour tile have the same province
        if (neib_prov == prov)
            // If there is an element on this tile that has an higher defense
            if (neib->_element() != nullptr && neib->_element()->_defense() > def_max)
                { def_max = neib->_element()->_defense(); }

    }

    return def_max;
}


Element* GameModel::get_tile_element(Coord c)
{ return (MAP_EXISTS) ? this->game_map->get_tile_element(c) : nullptr; }

Province* GameModel::get_tile_province(Coord c)
{ return (MAP_EXISTS) ? this->game_map->get_province(c) : nullptr; }

Province* GameModel::get_province_at_coord(Coord c)
{ return (MAP_EXISTS) ? this->game_map->get_province(c) : nullptr; }


// >> Setters <<

void GameModel::set_tile_color(Coord coord, usint color)
{ if (MAP_EXISTS) this->game_map->set_tile_color(coord, color); }

void GameModel::set_tile_element(Coord c, usint elt_level, bool is_unit, int elt_attribute)
{ if (MAP_EXISTS) this->game_map->set_tile_element(c, elt_level, is_unit, elt_attribute); }

void GameModel::set_current_player(int new_player)
{ this->current_player = new_player; }


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
    std::vector<Province*>* provinces = this->game_map->_provinces_layer();

    for (Province* p : *provinces) {

        if (p->_color() != this->current_player) { continue; }
        p->treasury_turn();

        for (std::pair<Coord, Tile*> it : *(p->_tiles())) {
            Unit* unit = dynamic_cast<Unit*>(it.second->_element());
            if (unit != nullptr) unit->can_move = true;
        }
    }
}

void GameModel::bandit_turn()
{
    usint nb_bandits = 0;
    std::vector<Coord> bandit_camps;

    for (std::pair<Coord, Element*> it : *(this->game_map->_bandits_layer())) {

        Tile* tile = this->game_map->get_tile(it.first);
        if (tile == nullptr) { continue; }

        Unit* unit = dynamic_cast<Unit*>(it.second);

        if (unit == nullptr) { bandit_camps.push_back(it.first); } // building

        else { // unit
            nb_bandits++;
            // ! TODO : bouger le bandit
        }
    }

    for (Coord c : bandit_camps) {
        Tile* tile = this->game_map->get_tile(c);
        dynamic_cast<Building*>(tile->_element())->update_treasury(nb_bandits);
    }

    return;
}


// >> Check and Do <<

// [move_element]

bool GameModel::check_action_move_unit(Coord src, Coord dst)
{
    if (this->game_map == nullptr) { return false; }

    Tile* src_tile = this->game_map->get_tile(src);
    Tile* dst_tile = this->game_map->get_tile(dst);
    if (src_tile == nullptr || dst_tile == nullptr) { return false; }

    // Check if we move current player entity
    if (src_tile->_color() != this->current_player) { return false; }

    // Get the unit to move
    Unit* unit_to_move = dynamic_cast<Unit*>(src_tile->_element());
    if (unit_to_move == nullptr) { return false; } // building or nullptr
    if (!(unit_to_move->can_move)) { return false; } // already moved this turn
    if (unit_to_move->_defense() == 0) { return false; } // bandit

    Province* src_prov = this->game_map->get_province(src);
    Province* dst_prov = this->game_map->get_province(dst);

    // To avoid system errors, src_prov should always be different than nullptr
    if (src_prov == nullptr) { return false; }

    // Check if the movement is adjacent to the province
    if (!(this->game_map->adjacent_to_province(dst, src_prov))) { return false; }

    if (dst_prov != nullptr && dst_prov->_color() == src_prov->_color()) {

        if (dst_tile->_element() == nullptr) { return true; }

        // Get the unit at destination tile
        Unit* dst_unit = dynamic_cast<Unit*>(dst_tile->_element());
        if (dst_unit == nullptr) { return false; } // building, can't move
        if (dst_unit->_color() != dst_prov->_color()) { return true; } // bandit, can move

        // If the destination unit hasn't the same level than the unit to move (no fusion of units to unit of higher level)
        if (dst_unit->_defense() == MAX_UNIT_LEVEL) { return false; }
        if (unit_to_move->_defense() != dst_unit->_defense()) { return false; }
    }

    // If the source unit is an hero, he can go anywhere
    if (unit_to_move->_defense() == MAX_UNIT_LEVEL) { return true; }

    // If the current unit to move has an higher defense than the destination tile, he can go there
    return (unit_to_move->_defense() > this->get_tile_defense(dst));
}


void GameModel::do_action_move_unit(Coord src, Coord dst)
{

    Tile* src_tile = this->game_map->get_tile(src);
    Tile* dst_tile = this->game_map->get_tile(dst);
    Province* src_prov = this->game_map->get_province(src);
    Province* dst_prov = this->game_map->get_province(dst);
    Unit* unit_to_move = dynamic_cast<Unit*>(src_tile->_element());

    if (dst_prov == src_prov && dst_tile->_element() != nullptr) {
        // Same province, just move and may fusion if possible

        Unit* unit_to_fusion = dynamic_cast<Unit*>(dst_tile->_element());

        if (unit_to_fusion != nullptr && unit_to_fusion->_color() == unit_to_move->_color()) {
            unit_to_fusion->upgrade();
            src_tile->delete_element();
        }

        else {
            dst_tile->set_element(unit_to_move);
            src_tile->set_element(nullptr);
        }

        return;
    }

    // adverse province
    if (dst_prov != nullptr) {

        // this->game_map->split_province(dst_tile->_coord());
        if (dynamic_cast<Building*>(dst_tile->_element()) != nullptr)
            { src_prov->add_treasury(dst_prov->_treasury()); }
    }

    dst_tile->delete_element();
    dst_tile->set_element(unit_to_move);
    src_tile->delete_element();
    this->game_map->remove_tile_of_all_provinces( dst_tile->_coord() );
    src_prov->add_tile(dst_tile);
    unit_to_move->can_move = false;

    // Look for same color tiles connexion
    std::vector<Coord> n = neighbours(dst);

    for (Coord v : n) {

        Tile* tile = this->game_map->get_tile(v);
        if (tile == nullptr) { continue; }
        if (tile->_color() != src_prov->_color()) { continue; }
        Province* prov = this->game_map->get_province(v);

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
    Tile* tile = this->game_map->get_tile(c);
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
    Province* dst_prov = nullptr;

    for (Province* prov : *(this->game_map->_provinces_layer())) {

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

        Unit* dst_unit = dynamic_cast<Unit*>(tile->_element());
        if (dst_unit == nullptr) { return false; } // building

        // If it is an unit of the same color
        if (dst_unit->_color() == this->current_player) {
            if (dst_unit->_defense() == MAX_UNIT_LEVEL) { return false; }
            return (dst_unit->_defense() == elt_level);
        }
        else if (dst_unit->_defense() >= elt_level) { return false; }
    }

    // If the source unit is an hero, he can go anywhere
    if (elt_level == MAX_UNIT_LEVEL) return true;

    // Get the tile defense
    int tile_def = this->get_tile_defense(c);

    // If the current unit to move has an higher defense than the destination tile, he can go there
    return (elt_level > tile_def);
}


void GameModel::do_action_new_element(Coord c, int elt_level, bool is_unit)
{
    int unit_cost = (is_unit ? units_new_costs[elt_level] : buildings_new_costs[elt_level]);

    Tile* tile = this->game_map->get_tile(c);
    Province* dst_prov = this->game_map->get_province(c);
    Province* src_prov = nullptr;

    if (tile == nullptr) { return; }

    if (dst_prov == nullptr || dst_prov->_color() != this->current_player) {

        for (Province* prov : *(this->game_map->_provinces_layer())) {

            if (prov->is_adjacent_to_coord(c)) {
                if (prov->_color() != this->current_player) { continue; }
                if (prov->_treasury() < unit_cost) { continue; }
                src_prov = prov;
                break;
            }
        }

    }
    else src_prov = dst_prov;

    if (src_prov == nullptr) { return; }

    Element* new_elt;

    if (is_unit)
        { new_elt = new Unit(c, this->current_player, elt_level); }
    else
        { new_elt = new Building(c, this->current_player, elt_level); }

    if (new_elt == nullptr) { return; }

    if (dst_prov != nullptr && dst_prov->_color() == this->current_player) { // Same province, just move and may fusion

        Unit* fusion_with = nullptr;

        if (tile->_element() != nullptr) {

            Unit* unit = dynamic_cast<Unit*>(tile->_element());

            if (unit != nullptr && unit->_color() == new_elt->_color()) {
                if( !is_unit || unit->_defense() != new_elt->_defense()) { return; }
                fusion_with = unit;
            }
        }

        if (fusion_with != nullptr) { fusion_with->upgrade(); }
        else { tile->set_element(new_elt); }

        src_prov->remove_treasury(unit_cost);

        return;
    }

    // adverse province
    if (dst_prov != nullptr) {
        // this->game_map->split_province(dst_tile->_coord());
        if (dynamic_cast<Building*>(tile->_element()) != nullptr)
            { src_prov->add_treasury(dst_prov->_treasury()); }
    }

    tile->delete_element();
    tile->set_element(new_elt);
    this->game_map->remove_tile_of_all_provinces(tile->_coord());
    src_prov->add_tile(tile);
    //
    Unit* unit_to_move_unit = dynamic_cast<Unit*>(new_elt);
    if (unit_to_move_unit != nullptr) { unit_to_move_unit->can_move = false; }

    src_prov->remove_treasury(unit_cost);

    // Look for same color tiles connexion
    std::vector<Coord> n = neighbours(c);

    for (Coord v : n) {

        Tile* tile = this->game_map->get_tile(v);
        if (tile == nullptr) { continue; }
        if (tile->_color() != src_prov->_color()) { continue; }
        Province* prov = this->game_map->get_province(v);

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
    this->current_player++;
    if (this->current_player > this->nb_players)
        this->current_player = 1;
}


// >> Other functions <<

void GameModel::calculate_all_provinces_after_map_initialisation()
{

    if (this->game_map == nullptr) { return; }

    std::map< int, int > to_convert_num;
    std::map< Coord, int > visited;

    std::deque< Coord > to_visit_coord;
    std::deque< int > to_visit_num;

    int nb_tot_nums = 0;

    for (std::pair<Coord, Tile*> it : *(this->game_map->_tiles_layer())) {

        Building* building = dynamic_cast<Building*>(this->game_map->get_tile_element(it.first));
        if (building == nullptr || building->_color() == NEUTRAL) { continue; }

        to_visit_coord.push_back(building->_coord());
        to_visit_num.push_back(nb_tot_nums);
        nb_tot_nums++;
    }

    // WHILE THERE ARE TILES TO VISIT

    while (to_visit_coord.size() > 0) {

        Coord v = to_visit_coord.front();
        int num = to_visit_num.front();
        int color = this->get_tile_color(v);

        if (to_convert_num.count(num) > 0)
            num = to_convert_num[num];

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
                    if (it.second == visited[vv])
                        visited[it.first] = num;
                }
            }

            to_visit_coord.push_back(vv);
            to_visit_num.push_back(num);
        }
    }

    // Extract all the different new zones

    int nb_differents = nb_tot_nums - to_convert_num.size();

    if (nb_differents <= 1) { return; } // no split to do

    int crt_idx = 0;
    std::map<int, int> num_idx;
    std::vector< std::list<Coord> > all_province_zones;

    for (std::pair<Coord, int> it : visited) {

        int num = it.second;

        if (num_idx.count(num) == 0) {
            num_idx[num] = crt_idx;
            crt_idx++;
            all_province_zones.push_back((std::list<Coord>){});
        }

        all_province_zones[num_idx[num]].push_back(it.first);
    }

    this->reset_provinces();

    for (std::list<Coord> list_of_tiles : all_province_zones)
        { this->game_map->add_province_from_list_of_tiles(list_of_tiles); }
}
