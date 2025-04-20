//
#include <cstdlib>  // srand() et rand()
#include <ctime> // time()
#include <deque>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
//
#include "entity_data.hpp"
#include "model.hpp"


// ===== Elements =====


Coord Element::_coord() const { return this->coord; }
usint Element::_color() const { return this->color; }
usint Element::_defense() const { return this->defense; }


int Element::get_upkeep_cost() { return 0; }


void Unit::upgrade() { this->defense++; }


void Unit::convert_bandit() { this->color = -1; this->defense = 0; }


int Unit::get_upkeep_cost() { return units_upkeep_costs[this->defense]; }


bool Building::is_town() const { return (this->defense == 1); }


int Building::get_upkeep_cost() { return buildings_upkeep_costs[this->defense]; }


// ===== [ Map ] =====


// --- Tile ---


Coord Tile::_coord() const { return this->coord; }
usint Tile::_color() const { return this->color; }
usint Tile::_defense() const { return this->defense; }
Element* Tile::_element() const { return this->element; }


void Tile::convert_color(usint new_color) { this->color = new_color; }

void Tile::set_element(Element* e)
{
    this->delete_element();
    this->element = e;
}


void Tile::delete_element()
{
    //
    if (this->element != nullptr) {

        //
        // TODO: manage the memory correctly ! Because some pointers can be lost lost !

        //
        // delete this->element;
    }
    //
    this->element = nullptr;
}


// --- Province ---


// Getters
usint Province::_color() const { return this->color; }
int Province::_treasury() const { return this->treasury; }
map<Coord, Tile*> Province::_tiles() const { return this->tiles_layer; }


// Setters
void Province::set_color(usint new_color){ this->color = new_color; }
void Province::set_treasury(int new_treasury){ this->treasury = new_treasury; };


//
bool Province::has_tile(Coord c){
    //
    return (this->tiles_layer.count(c) > 0);
}


void Province::add_tile(Tile* tile)
{
    //
    if (tile == nullptr) { return; }

    //
    Coord c = tile->_coord();

    //
    if (tiles_layer.count(c) > 0) { return; }  // already exists

    // insert
    tile->convert_color(this->color);
    tiles_layer[c] = tile;
}


void Province::remove_tile(Tile* tile) { tiles_layer.erase(tile->_coord()); }



int Province::expected_income()
{
    //
    int income = 0;

    //
    for (const auto& t : tiles_layer) {
        if (t.second->_element() != nullptr &&
            t.second->_element()->_defense() == 0) // bandit
            continue;
        else income++;
    }
    // Expenses
    for (const auto& t : tiles_layer) {
        if (t.second->_element() == nullptr) continue;
        //
        income -= t.second->_element()->get_upkeep_cost();
    }

    //
    return income;
}


void Province::treasury_turn()
{
    // Income
    this->treasury += this->expected_income();

    // Units management
    if (this->treasury >= 0) return; // units are paid

    this->treasury = 0;
    Unit* u = nullptr;
    for (auto& t : tiles_layer) {
        u = dynamic_cast<Unit*>(t.second->_element());
        if (u != nullptr) u->convert_bandit();
    }
}


void Province::add_treasury(int amount) { this->treasury += amount; }


void Province::remove_treasury(int amount) { this->treasury -= amount; }


// ----- Map -----


usint Map::_size() const { return size; }


Tile* Map::get_tile(Coord c)
{
    //
    if( this->tiles_layer.count(c) == 0){
        return nullptr;
    }
    //
    return this->tiles_layer[c];
}


Element* Map::get_tile_entity(Coord c)
{
    //
    Tile* tile = this->get_tile(c);

    //
    if( tile == nullptr ) { return nullptr; }

    //
    return tile->_element();

}


int Map::get_tile_color(Coord c)
{
    //
    Tile* tile = this->get_tile(c);

    //
    if( tile == nullptr ) { return -1; }

    //
    return tile->_color();

}

Province* Map::get_province(Coord c)
{
    //
    Tile * tile = this->get_tile(c);
    //
    if (tile == nullptr) return nullptr;
    //
    if (tile->_color() == NEUTRAL) return nullptr;

    //
    for (Province* p : this->provinces_layer) {

        //
        if( p->has_tile(c) ){

            return p;
        }

    }

    //
    return nullptr;
}


//
std::map<Coord, Tile*>* Map::get_tiles_layer() { return &(this->tiles_layer); }


//
std::map<Coord, Element*>* Map::get_bandits_layer() { return &(this->bandits_layer); }


//
std::vector<Province*>* Map::get_provinces_layer() { return &(this->provinces_layer); }


//
std::list<Province*>* Map::get_provinces_to_remove() { return &(this->provinces_to_remove); }


//
void Map::reset_tiles_layer(){

    //
    this->tiles_layer.clear();

}


//
void Map::reset_provinces_layer(){

    //
    this->provinces_layer.clear();
}


//
void Map::reset_bandits_layer(){

    //
    this->bandits_layer.clear();
}


//
void Map::set_tile(Coord coord, Tile* new_tile){

    //
    Tile* tile = this->get_tile(coord);

    //
    if( tile != nullptr ){
        delete tile;
    }

    //
    this->tiles_layer[coord] = new_tile;

}


//
void Map::set_tile_entity(Coord coord, int entity_level, bool entity_type){

    //
    Tile* tile = this->get_tile(coord);

    //
    if( tile == nullptr ){

        //
        tile = new Tile(coord);
        this->set_tile( coord, tile );

    }

    //
    if(entity_type){

        //
        tile->set_element( new Unit(coord, tile->_color(), entity_level) );

    }
    else{

        //
        tile->set_element( new Building(coord, tile->_color(), entity_level) );

    }

}


//
void Map::set_tile_color(Coord coord, int tile_color){

    //
    Tile* tile = this->get_tile(coord);

    //
    if (tile == nullptr) {
        tile = new Tile(coord);
        this->set_tile(coord, tile);
    }

    //
    tile->convert_color(tile_color);

}


//
void Map::add_province_from_list_of_tiles(std::list<Coord> tiles_list, int color, bool with_treasury, int treasury){

    //
    Province* p = new Province();

    //
    if( color == -1 ){
        //
        color = this->get_tile_color( tiles_list.front() );
    }

    //
    p->set_color( color );

    //
    if( with_treasury ){
        p->set_treasury( treasury );
    }
    else{
        p->set_treasury( tiles_list.size() );
    }

    //
    for( Coord c : tiles_list ){

        //
        Tile* tile = this->get_tile(c);

        //
        if( tile == nullptr ) { continue; }

        //
        p->add_tile( tile );

    }

    //
    this->add_province( p );

}


//
void Map::recursive_fill(Coord c, unsigned int nb_cover, usint cover, Province* province=nullptr)
{
    if (cover == NEUTRAL) {
        if (tiles_layer.size() >= nb_cover) return; // inhaf NEUTRAL
        if (tiles_layer.find(c) != tiles_layer.end()) return; // already exists
        tiles_layer.insert({c, new Tile(c, cover)});
    }

    else {
        Tile* tile = get_tile(c);
        if (tile == nullptr) return;
        if (tile->_color() != NEUTRAL) return;

        if (province == nullptr) {
            province = new Province(cover);
            province->add_treasury(7);
            add_province(province);
            tile->set_element(new Building(c, cover));
        }
        if (province->_tiles().size() >= nb_cover) return; // inhaf cover
        province->add_tile(tile);
    }

    for (auto c : neighbours(c))
        if (rand() % 2) recursive_fill(c, nb_cover, cover, province);
}


// ! Gérer le bool bandits
void Map::init_map(usint nb_players, int nb_provinces, int size_provinces, bool bandits)
{

    // Initialize the random seed
    srand(static_cast<unsigned int>(time(0)));
    usint seed_x = rand() % size;
    usint seed_y = rand() % size;

    // Create the map NEUTRAL
    unsigned int nb_neutral = 0;
    recursive_fill(Coord(seed_x, seed_y), (size*size/3), NEUTRAL, nullptr);

    // Add players' provinces
    for (usint p=1; p<=nb_players; p++) {
        for (usint n=0; n<=nb_provinces; n++) {
            // Get a random tile
            seed_x = rand() % size;
            seed_y = rand() % size;

            while (tiles_layer.find(Coord(seed_x, seed_y)) == tiles_layer.end()
                    || tiles_layer[Coord(seed_x, seed_y)]->_color() != NEUTRAL)
                { seed_x = rand() % size; seed_y = rand() % size; }

            recursive_fill(Coord(seed_x, seed_y), size_provinces, p, nullptr);
        }
    }

    if (bandits) {
        // ! to complete
    }
}


void Map::add_province(Province* province) { provinces_layer.push_back(province); }


void Map::remove_province(Province* province)
{
    //
    this->provinces_layer.erase(
        std::remove(this->provinces_layer.begin(), this->provinces_layer.end(), province),
        this->provinces_layer.end()
    );

    //
    this->get_provinces_to_remove()->push_back( province );

}


bool Map::adjacent_to_province(Province* p, Coord c)
{
    if (get_province(c) == p) return true;
    vector<Coord> n = neighbours(c);
    for (auto& t : n) {
        if (get_province(t) == p)
            return true;
    }
    return false;
}


void Map::fusion_provinces(Province* p1, Province* p2)
{
    if (p1 == nullptr || p2 == nullptr) return;
    if (p1 == p2) return;
    if (p1->_color() != p2->_color()) return;

    for (auto& t : p2->_tiles()) p1->add_tile(t.second);
    p1->add_treasury(p2->_treasury());
    remove_province(p2);
    delete p2;
}


void Map::split_province(Coord c)
{
    //
    Province* p = get_province(c);
    if (p == nullptr) return;
    if (p->_tiles().size() <= 1) return;

    //
    int color = p->_color();

    //
    std::map<Coord, int> visited;
    std::map<int, int> to_convert_num;

    //
    std::deque<Coord> to_visit_coord;
    std::deque<int> to_visit_num;

    //
    int nb_tot_nums = 0;

    // INIT

    std::vector<Coord> nbs = neighbours(c);

    //
    for(int i = 1; i < nbs.size(); i++){
        //
        Tile* tile_nb = this->get_tile( nbs[i] );
        if( tile_nb == nullptr ){ continue; }
        if( tile_nb->_color() != color ){ continue; }

        //
        to_visit_coord.push_back( nbs[i] );
        to_visit_num.push_back( nb_tot_nums );
        //
        nb_tot_nums++;
    }

    // WHILE THERE ARE TILES TO VISIT

    while( to_visit_coord.size() > 0 ){

        //
        Coord v = to_visit_coord.front();
        int num = to_visit_num.front();

        //
        if(to_convert_num.count(num) > 0){ num = to_convert_num[num]; }

        //
        to_visit_coord.pop_front();
        to_visit_num.pop_front();

        //
        if( visited.count(v) > 0 ){ continue; }

        //
        visited[v] = num;

        //
        for( Coord vv : neighbours(v) ){

            //
            int color2 = this->get_tile_color( vv );

            //
            if( color2 == -1 || color != color2 ){ continue; }

            //
            if( visited.count(vv) > 0){
                //
                if( visited[vv] == num ){ continue; }

                // else...
                to_convert_num[visited[vv]] = num;

                // Change all the different number to the same number for connex zones
                for( std::pair<Coord, int> it : visited){
                    if( it.second == visited[vv]){
                        visited[it.first] = num;
                    }
                }

            }

            //
            to_visit_coord.push_back( vv );
            to_visit_num.push_back( num );

        }

    }

    // Extract all the different new zones

    int nb_differents = nb_tot_nums - to_convert_num.size();

    if (nb_differents <= 1){

        return; // No split to do

    }

    //
    int crt_idx = 0;
    std::map<int, int> num_idx;

    //
    std::vector< std::list<Coord> > splited_zones;

    //
    for( std::pair<Coord, int> it : visited){
        //
        int num = it.second;
        //
        if(num_idx.count(num) == 0){
            num_idx[num] = crt_idx;
            crt_idx++;
            //
            splited_zones.push_back( (std::list<Coord>){} );
        }
        //
        splited_zones[ num_idx[num] ].push_back( it.first );
    }

    // TODO: there is the list of regions in splited_zones (you can rename this variable if you have a better name)


}


// ===== Game =====


//
GameModel::GameModel(){

    //
    this->game_map = new Map();

}


//
Map* GameModel::get_map(){
    //
    return this->game_map;
}


//
void GameModel::at_player_turn_start(){

    //
    std::vector<Province*>* provinces = this->game_map->get_provinces_layer();
    for( Province* p : *provinces ){

        //
        if( p->_color() != this->current_player_color ){

            //
            continue;

        }

        //
        p->treasury_turn();

    }

}


//
bool GameModel::check_player_action_move_entity(Coord src, Coord dst){

    // Check game map existence
    if( this->game_map == nullptr ) { return false; }

    // Get the tile
    Tile* src_tile = this->game_map->get_tile(src);
    Tile* dst_tile = this->game_map->get_tile(dst);

    // Check if tiles exists
    if (src_tile == nullptr || dst_tile == nullptr){ return false; }

    // Check if we move current player entity
    if (src_tile->_color() != this->current_player_color){ return false; }

    // Check if there is an entity at the source of the mouvement
    if (src_tile->_element() == nullptr){ return false; }

    // Get the unit to move
    Unit* unit_to_move = dynamic_cast<Unit*>(src_tile->_element());

    // Check if the element is a unit and not a building
    if (unit_to_move == nullptr){ return false; }

    // Check if the unit to move is not a bandit
    if (unit_to_move->_defense() == 0){ return false; }

    // Get the provinces of the movements
    Province* src_prov = this->game_map->get_province(src);
    Province* dst_prov = this->game_map->get_province(dst);

    // To avoid system errors, src_prov should always be different than nullptr
    if ( src_prov == nullptr ){ return false; }

    // Check if the movement is adjacent to the province
    if ( !(this->game_map->adjacent_to_province(src_prov, dst)) ){ return false; }

    // If there is destination province
    if(dst_prov != nullptr){

        // If the movement is inside a province of the same color
        if (dst_prov->_color() == src_prov->_color()){

            // Check if there an element in the destination tile
            if( dst_tile->_element() != nullptr ){

                // Get the unit at destination tile
                Unit* dst_unit = dynamic_cast<Unit*>(dst_tile->_element());

                // If it's building at destination tile
                if( dst_unit == nullptr){ return false; }

                // If it's a bandit
                if( dst_unit->_color() != dst_prov->_color() ){ return true; }

                // If the destination unit hasn't the same level than the unit to move (no fusion of units to unit of higher level)
                if( unit_to_move->_defense() != dst_unit->_defense() ){ return false; }

            }

            //
            return true;
        }

    }

    // If the source unit is an hero, he can go anywhere
    if (src_tile->_element()->_defense() == 4){ return true; }

    // Get the neighbours of the destination tile
    std::vector<Coord> n = neighbours(dst);

    // Initializing the maximum defense with the defense of destination tile
    usint def_max = dst_tile->_defense();

    // Checking if there is an higher defense in the neighbours of the destination tile
    for (Coord v : n) {

        // Get the tile at coordinate v
        Tile* tile = this->game_map->get_tile(v);

        // If no tiles here, abort for coordinate v
        if( tile == nullptr ){ continue; }

        // Get the province at coordinate v
        Province* prov = this->game_map->get_province(v);

        // If no province here, abort for coordinate v
        if( prov == nullptr ){ continue; }

        // An unit can move anywhere on its color
        if( prov->_color() == unit_to_move->_color() ){
            continue;
        }

        // Check if the destination tile and its neighbour tile have the same province
        if (prov == dst_prov) {

            // If there is an element on this tile that has an higher defense
            if (tile->_element() != nullptr && tile->_element()->_defense() > def_max){

                // Update the maximum defense of the destination tile
                def_max = tile->_element()->_defense();
            }
        }
    }

    // If the current unit to move has an higher defense than the destination tile, he can go there
    return (unit_to_move->_defense() > def_max);
}


//
void GameModel::do_player_action_move_entity(Coord src, Coord dst){

    // TODO : changer province case si nécessaire
    // Détruire camp/tour/pion adverse si nécessaire (camp -> prendre les sous)
    // Fusion provinces si nécessaire
    // Fusion bonhomme si nécessaire

    Tile* src_tile = this->game_map->get_tile(src);
    Tile* dst_tile = this->game_map->get_tile(dst);
    Province* src_prov = this->game_map->get_province(src);
    Province* dst_prov = this->game_map->get_province(dst);

    //
    Unit* unit_to_move = dynamic_cast<Unit*>( src_tile->_element() );

    //
    if( unit_to_move == nullptr ){ return; }

    //
    if (dst_prov == src_prov) { // Same province, just move and may fusion

        //
        Unit* fusion_with = nullptr;

        if (dst_tile->_element() != nullptr) {

            //
            Unit* unit = dynamic_cast<Unit*>(dst_tile->_element());

            if( unit != nullptr && unit->_color() == unit_to_move->_color() ){

                //
                if( unit->_defense() != unit_to_move->_defense() ){ return; }

                //
                fusion_with = unit;

            }

        }

        //
        if( fusion_with != nullptr ){
            //
            fusion_with->upgrade();
            src_tile->delete_element();
        }
        //
        else {
            //
            dst_tile->set_element(src_tile->_element());
            src_tile->set_element(nullptr);
        }

        return;
    }

    // adverse province
    if (dst_prov != nullptr) {

        this->game_map->split_province(dst_tile->_coord());

        if (dynamic_cast<Building*>(dst_tile->_element()) != nullptr)
            src_prov->add_treasury(dst_prov->_treasury());
    }

    dst_tile->delete_element();
    dst_tile->set_element(src_tile->_element());
    src_tile->set_element(nullptr);
    src_prov->add_tile(dst_tile);

    // Look for same color tiles connexion
    vector<Coord> n = neighbours(dst);

    for (Coord v : n) {

        Tile* tile = this->game_map->get_tile(v);
        if (tile == nullptr) continue;
        if (tile->_color() != src_prov->_color()) continue;
        Province* prov = this->game_map->get_province(v);

        if (prov == nullptr) {
            src_prov->add_tile(tile);
            vector<Coord> n2 = neighbours(tile->_coord());
            n.insert(n.end(), n2.begin(), n2.end());
        }

        else if (prov != src_prov)
            this->game_map->fusion_provinces(src_prov, prov);

        else continue;
    }

    return;
}


//
bool GameModel::check_player_action_new_entity(Coord dst, int entity_level, bool entity_type){

    // TODO

    return false;
}


//
void GameModel::do_player_action_new_entity(Coord dst, int entity_level, bool entity_type){

    // TODO

    return;
}


//
bool GameModel::check_player_action_end_turn(){

    // TODO

    return true;
}


//
void GameModel::do_player_action_end_turn(){

    //
    this->current_player_color++;

    //
    if ( this->current_player_color > this->nb_players_colors ){

        this->current_player_color = 1;

    }

    //
    return;
}


//
int GameModel::get_current_player_color(){

    return this->current_player_color;
}


//
Province* GameModel::get_tile_province(Coord coord){

    //
    if( this->game_map == nullptr ){ return nullptr; }

    //
    return this->game_map->get_province(coord);

}


//
Element* GameModel::get_tile_entity(Coord coord){

    //
    if( this->game_map == nullptr ){ return nullptr; }

    //
    return this->game_map->get_tile_entity(coord);

}


//
int GameModel::get_tile_color(Coord coord){

    //
    if( this->game_map == nullptr ){ return -1; }

    //
    return this->game_map->get_tile_color(coord);
}


//
void GameModel::set_tile_entity(Coord coord, int entity_level, bool entity_type){

    //
    if( this->game_map == nullptr ){ return; }

    //
    this->game_map->set_tile_entity(coord, entity_level, entity_type);

}


//
void GameModel::set_tile_color(Coord coord, int color){

    //
    if( this->game_map == nullptr ){ return; }

    //
    this->game_map->set_tile_color(coord, color);

}


//
void GameModel::reset_tiles_layer(){

    //
    if( this->game_map == nullptr ){ return; }

    //
    this->game_map->reset_tiles_layer();

}


//
void GameModel::reset_bandits_layer(){

    //
    if( this->game_map == nullptr ){ return; }

    //
    this->game_map->reset_bandits_layer();
}


//
Province* GameModel::get_province_at_coord(Coord c){

    //
    if( this->game_map == nullptr ){ return nullptr; }

    //
    return this->game_map->get_province(c);

}


//
int GameModel::get_nb_players_colors(){

    //
    return this->nb_players_colors;

}


//
void GameModel::calculate_all_provinces_after_map_initialisation(){

    //
    if( this->game_map == nullptr ) {return; }

    //
    std::map< int, int > to_convert_num;
    std::map< Coord, int > visited;

    //
    std::deque< Coord > to_visit_coord;
    std::deque< int > to_visit_num;

    //
    int nb_tot_nums = 0;

    //
    std::map<Coord, Tile*>* tiles_layer = this->game_map->get_tiles_layer();
    //
    for (std::pair<Coord, Tile*> it : (*tiles_layer) ){

        //
        Element* entity = this->game_map->get_tile_entity(it.first);
        //
        if( entity == nullptr ){ continue; }

        //
        Building* building = dynamic_cast<Building*>(entity);
        //
        if( building == nullptr ){ continue; }

        //
        if( building->_color() <= 0 ){ continue; }

        //
        to_visit_coord.push_back( building->_coord() );

        //
        to_visit_num.push_back( nb_tot_nums );
        nb_tot_nums++;

    }

    // WHILE THERE ARE TILES TO VISIT

    while( to_visit_coord.size() > 0 ){

        //
        Coord v = to_visit_coord.front();
        int num = to_visit_num.front();

        //
        int color = this->get_tile_color( v );

        //
        if(to_convert_num.count(num) > 0){ num = to_convert_num[num]; }

        //
        to_visit_coord.pop_front();
        to_visit_num.pop_front();

        //
        if( visited.count(v) > 0 ){ continue; }

        //
        visited[v] = num;

        //
        for( Coord vv : neighbours(v) ){

            //
            int color2 = this->get_tile_color(vv);
            //
            if( color2 == -1 || color2 != color ){
                continue;
            }

            //
            if( visited.count(vv) > 0){
                //
                if( visited[vv] == num ){ continue; }

                // else...
                to_convert_num[visited[vv]] = num;

                // Change all the different number to the same number for connex zones
                for( std::pair<Coord, int> it : visited){
                    if( it.second == visited[vv]){
                        visited[it.first] = num;
                    }
                }

            }

            //
            to_visit_coord.push_back( vv );
            to_visit_num.push_back( num );

        }

    }

    // Extract all the different new zones

    int nb_differents = nb_tot_nums - to_convert_num.size();

    if (nb_differents <= 1){

        return; // No split to do

    }

    //
    int crt_idx = 0;
    std::map<int, int> num_idx;

    //
    std::vector< std::list<Coord> > all_province_zones;

    //
    for( std::pair<Coord, int> it : visited){
        //
        int num = it.second;
        //
        if(num_idx.count(num) == 0){
            num_idx[num] = crt_idx;
            crt_idx++;
            //
            all_province_zones.push_back( (std::list<Coord>){} );
        }
        //
        all_province_zones[ num_idx[num] ].push_back( it.first );
    }

    //
    this->reset_provinces();

    //
    for ( std::list<Coord> list_of_tiles : all_province_zones ){

        //
        this->game_map->add_province_from_list_of_tiles( list_of_tiles );

    }

}



//
void GameModel::reset_provinces(){

    //
    if( this->game_map == nullptr ) {return; }

    //
    this->game_map->reset_provinces_layer();

}



// ===== Tools functions =====

//
usint max(usint a, usint b) { return (a > b) ? a : b; }


//
bool is_adjacent(Coord c1, Coord c2)
{
    int diff_x = c1.x - c2.x;
    int diff_y = c1.y - c2.y;

    // False cases
    if (diff_x == 0 && diff_y == 0) return false; // same tile
    if (abs(diff_x) > 1 || abs(diff_y) > 1) return false; // too far
    if (c1.x%2 == 0 && diff_x == 1 && abs(diff_y) == 1) return false; // diagonal movement not allowed
    else if (c1.x%2 == 1 && diff_x == -1 && abs(diff_y) == 1) return false; // diagonal movement not allowed

    return true;
}


//
vector<Coord> neighbours(Coord c)
{
    int x = c.x;
    int y = c.y;
    vector<Coord> n;
    n.push_back(get_tile_top_to(c));
    n.push_back(get_tile_top_left_to(c));
    n.push_back(get_tile_top_right_to(c));
    n.push_back(get_tile_bottom_to(c));
    n.push_back(get_tile_bottom_left_to(c));
    n.push_back(get_tile_bottom_right_to(c));
    return n;
}
