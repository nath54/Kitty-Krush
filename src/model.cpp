#include "model.hpp"
#include <cstdlib>  // srand() et rand()
#include <ctime> // time()
#include <deque>
#include <list>


// ===== Elements =====

Coord Element::_coord() const { return coord; }
usint Element::_color() const { return color; }
usint Element::_defense() const { return defense; }
usint Element::_cost() const { return cost; }

void Unit::upgrade()
{ defense++; cost *= 3; }

void Unit::convert_bandit()
{ color = -1; defense = 0; cost = 0; }

bool Building::is_town() const { return (defense == 1); }


// ===== [ Map ] =====

// --- Tile ---

Coord Tile::_coord() const { return coord; }
usint Tile::_color() const { return color; }
usint Tile::_defense() const { return defense; }
Element* Tile::_element() const { return element; }

void Tile::convert_color(usint new_color)
{ color = new_color; }

void Tile::add_element(Element* e)
{ element = e; }

void Tile::remove_element()
{ element = nullptr; }

void Tile::delete_element()
{
    if (element) delete element;
    element = nullptr;
}

// --- Province ---

usint Province::_color() const { return color; }
int Province::_treasury() const { return treasury; }
map<Coord, Tile*> Province::_tiles() const { return tiles_layer; }

bool Province::has_tile(Coord c){
    //
    return (this->tiles_layer.count(c) > 0);
}

void Province::add_tile(Tile* tile)
{
    if (tiles_layer.find(tile->_coord()) != tiles_layer.end())
        return; // already exists
    tile->convert_color(color);
    tiles_layer.insert({tile->_coord(), tile});
}

void Province::remove_tile(Tile* tile)
{ tiles_layer.erase(tile->_coord()); }

void Province::treasury_turn()
{
    // Income
    for (const auto& t : tiles_layer) {
        if (t.second->_element() != nullptr &&
            t.second->_element()->_cost() == 0) // bandit
            continue;
        else treasury++;
    }
    // Expenses
    for (const auto& t : tiles_layer) {
        if (t.second->_element() == nullptr) continue;
        treasury -= t.second->_element()->_cost();
    }
    // Units management
    if (treasury >= 0) return; // units are paid
    treasury = 0;
    Unit* u = nullptr;
    for (auto& t : tiles_layer) {
        u = dynamic_cast<Unit*>(t.second->_element());
        if (u != nullptr) u->convert_bandit();
    }
}

void Province::add_treasury(int amount)
{ treasury += amount; }

void Province::remove_treasury(int amount)
{ treasury -= amount; }

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

Province* Map::get_province(Coord c)
{
    Tile * tile = this->get_tile(c);
    if (tile == nullptr) return nullptr;
    if (tile->_color() == NEUTRAL) return nullptr;
    for (Province* p : provinces_layer) {
        for (auto& t : p->_tiles()) {
            if (t.first.x == c.x && t.first.y == c.y){ return p; }
        }
    }
    return nullptr;
}

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
            tile->add_element(new Building(c, cover));
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

void Map::add_province(Province* province)
{ provinces_layer.push_back(province); }

void Map::remove_province(Province* province)
{
    for (auto p = provinces_layer.begin(); p != provinces_layer.end(); p++) {
        if (*p != province) continue;
        (*p)->_tiles().clear();
        delete *p;
        break;
    }
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

    // INITIALISATION

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

    // BOUCLE TANT QUE FILE NON VIDE

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
        visited[v] = num;

        //
        for( Coord vv : neighbours(v) ){

            //
            if( visited.count(vv) > 0){
                //
                if( visited[vv] == num ){ continue; }

                // else...
                to_visit_num[visited[vv]] = num;

                // Change all the different number to the same number for connex zones
                for( std::pair<Coord, int> it : visited){
                    if( it.second == visited[vv]){
                        visited[it.first] = num;
                    }
                }

            }

            //
            Tile* tile_vv = this->get_tile( vv );
            if( tile_vv == nullptr ){ continue; }
            if( tile_vv->_color() != color ){ continue; }

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
bool GameModel::player_action_move_entity(Coord src, Coord dst){

    Tile* src_tile = game_map->get_tile(src);
    Tile* dst_tile = game_map->get_tile(dst);

    if (src_tile == nullptr || dst_tile == nullptr) return false;
    if (src_tile->_color() != this->current_player_color) return false;
    if (src_tile->_element() == nullptr) return false;
    if (dynamic_cast<Unit*>(src_tile->_element()) == nullptr) return false;
    if (src_tile->_element()->_defense() == 0) return false; // bandit

    Province* src_prov = game_map->get_province(src);
    Province* dst_prov = game_map->get_province(dst);

    if (!(game_map->adjacent_to_province(src_prov, dst))) return false;

    if (dst_prov == src_prov)
        return (dst_tile->_element() != nullptr);

    if (src_tile->_element()->_defense() == 4) return true; // hero

    vector<Coord> n = neighbours(dst);
    usint def_max = dst_tile->_defense();

    for (auto& t : n) {
        if (game_map->get_province(t) == dst_prov) {
            if (game_map->get_tile(t)->_element() != nullptr)
                def_max = max(def_max, game_map->get_tile(t)->_element()->_defense());
        }
    }

    return (src_tile->_element()->_defense() > def_max);
}

//
bool GameModel::player_action_new_entity(Coord dst, int entity_level, bool entity_type){

    // TODO

    return false;
}

//
bool GameModel::player_action_end_turn(){

    // TODO

    return false;
}

//
int GameModel::get_current_player_color(){

    return this->current_player_color;
}

//
Province* GameModel::get_tile_province(Coord coord){

    // TODO

    return nullptr;
}

//
Element* GameModel::get_tile_entity(Coord coord){

    // TODO

    return nullptr;
}

//
int GameModel::get_tile_color(Coord coord){

    // TODO

    return -1;
}

//
void GameModel::set_tile_entity(Coord coord, int entity_level, bool entity_type){

    // TODO

}

//
void GameModel::set_tile_color(Coord coord, int color){

    // TODO

}

//
void GameModel::reset_entity_layer(){

    // TODO

}

//
void GameModel::reset_color_layer(){

    // TODO

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
    n.push_back(Coord(x-1, y));
    n.push_back(Coord(x+1, y));
    n.push_back(Coord(x, y-1));
    n.push_back(Coord(x, y+1));
    n.push_back(Coord(x+1, y+1-((x%2)*2)));
    n.push_back(Coord(x-1, y+1-((x%2)*2)));
    return n;
}
