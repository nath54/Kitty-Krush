#include <cstdlib>  // srand() et rand()
#include <ctime> // time()
#include <deque>
#include <list>
#include <vector>
#include <map>
#include <algorithm>

#include "entity_data.hpp"
#include "model.hpp"


// ============================== [ Elements ] ================================

// >> Getters <<
Coord Element::_coord() const { return this->coord; }
usint Element::_color() const { return this->color; }
usint Element::_defense() const { return this->defense; }

// >> Unit <<
void Unit::upgrade() { if (this->defense < MAX_UNIT_LEVEL) this->defense++; }
void Unit::convert_bandit() { this->color = 0; this->defense = 0; }
int Unit::get_upkeep_cost() { return units_upkeep_costs[this->defense]; }

// >> Building <<
bool Building::is_town() const { return (this->defense == 1); }
void Building::update_treasury(int change) { this->treasury += change; }
void Building::convert_bandit() { this->color = 0; this->defense = 1; }
int Building::get_upkeep_cost() { return buildings_upkeep_costs[this->defense]; }


// ================================= [ Map ] ==================================

// ----------------------------------- Tile -----------------------------------

// >> Getters <<
Coord Tile::_coord() const { return this->coord; }
usint Tile::_color() const { return this->color; }
Element* Tile::_element() const { return this->element; }

// >> Other functions <<
usint Tile::get_defense() const { return (this->element == nullptr) ? 0 : this->element->_defense(); }

void Tile::convert_color(usint new_color) { this->color = new_color; }

void Tile::set_element(Element* e)
{
    this->delete_element();
    this->element = e;
}

void Tile::delete_element()
{
    if (this->element != nullptr) {

        // TODO: manage the memory correctly ! Because some pointers can be lost lost !
        // delete this->element;
    }
    this->element = nullptr;
}


// --------------------------------- Province ---------------------------------

// Getters
usint Province::_color() const { return this->color; }
int Province::_treasury() const { return this->treasury; }
std::map<Coord, Tile*>* Province::_tiles() { return &(this->tiles_layer); }

// Getters (undirect)
std::list<Building*> Province::get_buildings()
{
    std::list<Building*> buildings;

    for (std::pair<Coord, Tile*> it : this->tiles_layer) {

        Building* b = dynamic_cast<Building*>(it.second->_element());
        if (b != nullptr) buildings.push_back(b);
    }

    return buildings;
}

// Setters
void Province::set_color(usint new_color) { this->color = new_color; }
void Province::set_treasury(int new_treasury) { this->treasury = new_treasury; };

// Functions: tiles
bool Province::has_tile(Coord c) { return (this->tiles_layer.count(c) > 0); }

void Province::add_tile(Tile* tile)
{
    if (tile == nullptr) return;
    tile->convert_color(this->color);
    tiles_layer[tile->_coord()] = tile;
}

void Province::remove_tile(Tile* tile) { tiles_layer.erase(tile->_coord()); }

void Province::remove_tile_at_coord(Coord c) { tiles_layer.erase(c); }

// Functions: treasury
int Province::expected_income()
{
    int income = 0;

    for (const auto& t : tiles_layer) {
        income++;

        if (t.second->_element() != nullptr) {
            if (t.second->_element()->_defense() == 0) income--; // bandit
            else income -= t.second->_element()->get_upkeep_cost();
        }
    }

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

// Other functions
bool Province::is_adjacent_to_coord(Coord c)
{
    if (this->has_tile(c)) { return true; }

    for (std::pair<Coord, Tile*> it : this->tiles_layer)
        if (is_adjacent(it.first, c)) return true;

    return false;
}


// ----------------------------------- Map ------------------------------------

// >> Getters <<
usint Map::_size() const { return size; }
std::map<Coord, Tile*>* Map::_tiles_layer() { return &(this->tiles_layer); }
std::map<Coord, Element*>* Map::_bandits_layer() { return &(this->bandits_layer); }
std::vector<Province*>* Map::_provinces_layer() { return &(this->provinces_layer); }
std::list<Province*>* Map::_provinces_to_remove() { return &(this->provinces_to_remove); }

// >> Getters (undirect) <<
Tile* Map::get_tile(Coord c) { return (this->tiles_layer.count(c) == 0) ? nullptr : this->tiles_layer[c]; }

int Map::get_tile_color(Coord c)
{
    Tile* tile = this->get_tile(c);
    return (tile == nullptr) ? -1 : (int)tile->_color();
}

Element* Map::get_tile_element(Coord c)
{
    Tile* tile = this->get_tile(c);
    return (tile == nullptr) ? nullptr : tile->_element();
}

Province* Map::get_province(Coord c)
{
    Tile * tile = this->get_tile(c);
    if (tile == nullptr || tile->_color() == NEUTRAL) return nullptr;

    for (Province* p : this->provinces_layer)
        if (p->has_tile(c)) return p;

    return nullptr;
}

std::list<Building*> Map::get_all_buildings(bool with_bandit_buildings)
{
    std::list<Building*> buildings;

    for (Province* p : this->provinces_layer)
        buildings.splice(buildings.end(), p->get_buildings());

    if (!with_bandit_buildings) return buildings;

    for (std::pair<Coord, Element*> it : this->bandits_layer) {
        Building* b = dynamic_cast<Building*>(it.second);
        if (b != nullptr) buildings.push_back(b);
    }

    return buildings;
}

// >> Setters <<
void Map::set_tile(Coord coord, Tile* new_tile)
{
    Tile* tile = this->get_tile(coord);
    if (tile != nullptr) delete tile;
    this->tiles_layer[coord] = new_tile;
}

void Map::set_tile_color(Coord coord, int tile_color)
{
    Tile* tile = this->get_tile(coord);

    if (tile == nullptr) {
        tile = new Tile(coord);
        this->set_tile(coord, tile);
    }

    tile->convert_color(tile_color);
}

void Map::set_tile_element(Coord coord, usint element_level, bool is_unit)
{
    Tile* tile = this->get_tile(coord);

    if (tile == nullptr) {
        tile = new Tile(coord);
        this->set_tile( coord, tile );
    }

    if (is_unit)
        tile->set_element( new Unit(coord, tile->_color(), element_level) );
    else
        tile->set_element( new Building(coord, tile->_color(), element_level) );

}

// >> Resetters <<
void Map::reset_tiles_layer() { this->tiles_layer.clear(); }
void Map::reset_bandits_layer() { this->bandits_layer.clear(); }
void Map::reset_provinces_layer() { this->provinces_layer.clear(); }

// >> Initialization <<
void Map::recursive_fill(Coord coord, unsigned int nb_cover, usint cover, Province* province=nullptr)
{
    if (cover == NEUTRAL) {
        if (tiles_layer.size() >= nb_cover) return; // inhaf NEUTRAL
        if (tiles_layer.count(coord) != 0) return; // already exists
        tiles_layer.insert({coord, new Tile(coord, cover)});
    }

    else {
        Tile* tile = get_tile(coord);
        if (tile == nullptr) return;
        if (tile->_color() != NEUTRAL) return;

        if (province == nullptr) {
            province = new Province(cover);
            province->add_treasury(7);
            add_province(province);
            tile->set_element(new Building(coord, cover));
        }

        if (province->_tiles()->size() >= nb_cover) return; // inhaf cover
        province->add_tile(tile);
    }

    for (auto c : neighbours(coord))
        if (rand() % 2) recursive_fill(c, nb_cover, cover, province);
}

// ! TODO: Gérer le bool bandits
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

// >> Provinces managment <<
void Map::add_province(Province* p) { provinces_layer.push_back(p); }

void Map::add_province_from_list_of_tiles(std::list<Coord> tiles_list, int color, bool with_treasury, int treasury)
{
    Province* p = new Province();

    if (color == -1)
        color = this->get_tile_color(tiles_list.front());

    p->set_color(color);
    p->set_treasury(with_treasury ? treasury : tiles_list.size());

    for (Coord c : tiles_list) {
        Tile* tile = this->get_tile(c);
        if (tile != nullptr) p->add_tile(tile);
    }

    this->add_province(p);
}

void Map::remove_province(Province* p)
{
    this->provinces_layer.erase(
        std::remove(this->provinces_layer.begin(), this->provinces_layer.end(), p),
        this->provinces_layer.end()
    );

    this->_provinces_to_remove()->push_back(p);
}

void Map::fusion_provinces(Province* p1, Province* p2)
{
    if (p1 == nullptr || p2 == nullptr) return;
    if (p1 == p2) return;
    if (p1->_color() != p2->_color()) return;

    for (auto& t : *(p2->_tiles())) p1->add_tile(t.second);
    p1->add_treasury(p2->_treasury());
    remove_province(p2);
    delete p2;
}


void Map::split_province(Coord c, Province* p)
{
    // //
    // Province* p = get_province(c);
    // if (p == nullptr) return;
    // if (p->_tiles().size() <= 1) return;

    cout << "DEBUG 0 | province to split has size=" << p->_tiles()->size() << " | color=" << p->_color() << " | and has treasury=" << p->_treasury() << "\n";

    int color = p->_color();

    std::map<Coord, int> visited;
    std::map<int, int> to_convert_num;

    std::deque<Coord> to_visit_coord;
    std::deque<int> to_visit_num;

    int nb_tot_nums = 0;

    // INIT

    std::vector<Coord> nbs = neighbours(c);

    for (int i = 0; i < nbs.size(); i++) {

        Tile* tile_nb = this->get_tile(nbs[i]);
        if (tile_nb == nullptr) continue;
        if (tile_nb->_color() != color) continue;

        to_visit_coord.push_back(nbs[i]);
        to_visit_num.push_back(nb_tot_nums);

        nb_tot_nums += 1;
    }

    cout << "DEBUG 1 | to_visit_coord.size()=" << to_visit_coord.size() << "\n";

    // WHILE THERE ARE TILES TO VISIT

    while (to_visit_coord.size() > 0) {

        Coord v = to_visit_coord.front();
        int num = to_visit_num.front();

        if (to_convert_num.count(num) > 0)
            num = to_convert_num[num];

        to_visit_coord.pop_front();
        to_visit_num.pop_front();

        if (visited.count(v) > 0) continue;

        visited[v] = num;

        for (Coord vv : neighbours(v)) {

            int color2 = this->get_tile_color(vv);

            if (color2 == -1 || color != color2) continue;

            if (visited.count(vv) > 0) {

                if (visited[vv] == num) continue;

                // else...
                to_convert_num[visited[vv]] = num;

                // Change all the different number to the same number for connex zones
                for (std::pair<Coord, int> it : visited) {
                    if (it.second == visited[vv])
                        visited[it.first] = num;
                }
            }

            to_visit_coord.push_back( vv );
            to_visit_num.push_back( num );
        }
    }

    // Extract all the different new zones

    int nb_differents = nb_tot_nums - to_convert_num.size();

    cout << "DEBUG 2 | to_convert_num.size()=" << to_convert_num.size() << " | visited.size() = " << visited.size() << " | nb_differents=" << nb_differents << "\n";

    if (nb_differents < 1) return; // No split to do

    int crt_idx = 0;
    std::map<int, int> num_idx;
    std::vector< std::list<Coord> > splited_zones;

    for (std::pair<Coord, int> it : visited){

        int num = it.second;

        if(num_idx.count(num) == 0){
            num_idx[num] = crt_idx;
            crt_idx++;
    
            splited_zones.push_back( (std::list<Coord>){} );
        }

        splited_zones[ num_idx[num] ].push_back( it.first );
    }

    cout << "DEBUG 3 | splited_zones.size()=" << splited_zones.size() << "\n";

    // TODO: there is the list of regions in splited_zones (you can rename this variable if you have a better name)

    std::list<Province*> new_provinces;
    int nb_tiles_to_split_prov = 0;

    for (int i = 0; i < splited_zones.size(); i++) {

        // Check if there is a village in the splited zone
        bool village = false;

        for (Coord cc : splited_zones[i]) {

            Tile* t = this->get_tile(cc);

            if(t == nullptr || t->_element() == nullptr) continue;

            Building* b = dynamic_cast<Building*>(t->_element());

            if( b == nullptr || b->_color() == NEUTRAL) continue;

            if (b->_defense() == 1) {village = true; break;}
        }

        if (!village) {
            // Remove all the tiles of the color

            for (Coord cc : splited_zones[i]) {

                Tile* t = this->get_tile(cc);
                if (t == nullptr) continue;

                Element* elt = t->_element();
                if( elt != nullptr ) elt->convert_bandit();

                this->set_tile_color(cc, NEUTRAL);
                this->remove_tile_of_all_provinces(cc);
            }
        }

        else {
            // Create a new province and add it all the tiles
 
            Province* pp = new Province(p->_color());

            for (Coord cc : splited_zones[i]) {
                pp->add_tile(this->get_tile(cc));
                nb_tiles_to_split_prov++;
            }

            new_provinces.push_back(pp);
        }
    }

    cout << "DEBUG 4 | new_provinces.size()=" << new_provinces.size() << " | nb_tiles_to_split_prov=" << nb_tiles_to_split_prov << "\n";

    for (Province* pp : new_provinces) {
        pp->set_treasury((int) (p->_treasury() * (pp->_tiles()->size() / nb_tiles_to_split_prov)));
        this->add_province(pp);
    }

    this->remove_province(p);
}


void Map::remove_tile_of_all_provinces(Coord c)
{
    for (Province* p : this->provinces_layer)
        if (p->has_tile(c)) p->remove_tile_at_coord(c);
}

bool Map::adjacent_to_province(Coord c, Province* p)
{
    if (get_province(c) == p) return true;

    vector<Coord> n = neighbours(c);
    for (auto& t : n)
        if (get_province(t) == p) return true;

    return false;
}


// ============================ [ Game Model ] ================================


// >> Getters <<
Map* GameModel::_map() { return this->game_map; }
usint GameModel::_nb_players() { return this->nb_players; }
usint GameModel::_current_player() { return this->current_player; }

// >> Getters (undirect) <<
int GameModel::get_tile_color(Coord c)
{ return (this->game_map != nullptr) ? this->game_map->get_tile_color(c) : -1; }

usint GameModel::get_tile_defense(Coord c)
{
    Tile* tile = this->game_map->get_tile(c);
    if (tile == nullptr) return 0;

    usint def_max = tile->get_defense();

    Province *prov = this->game_map->get_province(c);
    if (prov == nullptr) return def_max; // No neighbours defense
    if (prov->_color() == this->current_player) return 0; // Can move if same province

    std::vector<Coord> n = neighbours(c);

    // Checking if there is an higher defense in the neighbours of the destination tile
    for (Coord v : n) {

        Tile* neib = this->game_map->get_tile(v);
        if (neib == nullptr) continue;

        Province* neib_prov = this->game_map->get_province(v);
        if (neib_prov == nullptr) continue;

        // Check if the destination tile and its neighbour tile have the same province
        if (neib_prov == prov) 
            // If there is an element on this tile that has an higher defense
            if (neib->_element() != nullptr && neib->_element()->_defense() > def_max)
                def_max = neib->_element()->_defense(); // update destination defense
    }

    return def_max;
}

Element* GameModel::get_tile_element(Coord c)
{ return (this->game_map != nullptr) ? this->game_map->get_tile_element(c) : nullptr; }

Province* GameModel::get_tile_province(Coord c)
{ return (this->game_map != nullptr) ? this->game_map->get_province(c) : nullptr; }

Province* GameModel::get_province_at_coord(Coord c)
{ return (this->game_map != nullptr) ? this->game_map->get_province(c) : nullptr; }

// >> Setters <<
void GameModel::set_tile_color(Coord coord, usint color)
{ if (this->game_map != nullptr) this->game_map->set_tile_color(coord, color); }

void GameModel::set_tile_element(Coord c, usint elt_level, bool is_unit)
{ if (this->game_map != nullptr) this->game_map->set_tile_element(c, elt_level, is_unit); }

// >> Resetters <<
void GameModel::reset_tiles_layer()
{ if (this->game_map != nullptr) this->game_map->reset_tiles_layer(); }

void GameModel::reset_bandits_layer()
{ if (this->game_map != nullptr) this->game_map->reset_bandits_layer(); }

void GameModel::reset_provinces()
{ if (this->game_map != nullptr) this->game_map->reset_provinces_layer(); }

// >> Turns <<
void GameModel::at_player_turn_start()
{
    std::vector<Province*>* provinces = this->game_map->_provinces_layer();

    for (Province* p : *provinces) {
        
        if (p->_color() != this->current_player) continue;
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
    vector<Coord> bandit_camps;

    for (std::pair<Coord, Element*> it : *(this->game_map->_bandits_layer())) {

        Tile* tile = this->game_map->get_tile(it.first);
        if (tile == nullptr) continue;

        Unit* unit = dynamic_cast<Unit*>(it.second);

        if (unit == nullptr) bandit_camps.push_back(it.first); // building

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
    if (this->game_map == nullptr) return false;

    Tile* src_tile = this->game_map->get_tile(src);
    Tile* dst_tile = this->game_map->get_tile(dst);
    if (src_tile == nullptr || dst_tile == nullptr) return false;

    // Check if we move current player entity
    if (src_tile->_color() != this->current_player) return false;

    // Get the unit to move
    Unit* unit_to_move = dynamic_cast<Unit*>(src_tile->_element());
    if (unit_to_move == nullptr) return false; // building or nullptr
    if (!(unit_to_move->can_move)) return false; // already moved this turn
    if (unit_to_move->_defense() == 0) return false; // bandit

    Province* src_prov = this->game_map->get_province(src);
    Province* dst_prov = this->game_map->get_province(dst);

    // To avoid system errors, src_prov should always be different than nullptr
    if (src_prov == nullptr) return false;

    // Check if the movement is adjacent to the province
    if (!(this->game_map->adjacent_to_province(dst, src_prov))) return false;

    if (dst_prov != nullptr && dst_prov->_color() == src_prov->_color()) {

        if (dst_tile->_element() == nullptr) return true;

        // Get the unit at destination tile
        Unit* dst_unit = dynamic_cast<Unit*>(dst_tile->_element());
        if (dst_unit == nullptr) return false; // building, can't move
        if (dst_unit->_color() != dst_prov->_color()) return true; // bandit, can move

        // If the destination unit hasn't the same level than the unit to move (no fusion of units to unit of higher level)
        if (dst_unit->_defense() == MAX_UNIT_LEVEL) return false;
        if (unit_to_move->_defense() != dst_unit->_defense()) return false;
    }

    // If the source unit is an hero, he can go anywhere
    if (unit_to_move->_defense() == MAX_UNIT_LEVEL) return true;

    // If the current unit to move has an higher defense than the destination tile, he can go there
    return (unit_to_move->_defense() > this->get_tile_defense(dst));
}

void GameModel::do_action_move_unit(Coord src, Coord dst)
{

    Tile* src_tile = this->game_map->get_tile(src);
    Tile* dst_tile = this->game_map->get_tile(dst);
    Province* src_prov = this->game_map->get_province(src);
    Province* dst_prov = this->game_map->get_province(dst);
    Unit* unit_to_move = dynamic_cast<Unit*>( src_tile->_element() );

    if (unit_to_move == nullptr) return;

    if (dst_prov == src_prov) { // Same province, just move and may fusion

        Unit* fusion_with = nullptr;

        if (dst_tile->_element() != nullptr) {

            Unit* unit = dynamic_cast<Unit*>(dst_tile->_element());

            if (unit != nullptr && unit->_color() == unit_to_move->_color()) {

                if (unit->_defense() != unit_to_move->_defense()) return;
                fusion_with = unit;
            }
        }

        if (fusion_with != nullptr) {
            fusion_with->upgrade();
            src_tile->delete_element();
        } else {
            dst_tile->set_element(unit_to_move);
            src_tile->set_element(nullptr);
        }

        return;
    }

    // adverse province
    if (dst_prov != nullptr) {

        // this->game_map->split_province(dst_tile->_coord());
        if (dynamic_cast<Building*>(dst_tile->_element()) != nullptr)
            src_prov->add_treasury(dst_prov->_treasury());
    }

    dst_tile->delete_element();
    dst_tile->set_element(unit_to_move);
    src_tile->delete_element();
    this->game_map->remove_tile_of_all_provinces( dst_tile->_coord() );
    src_prov->add_tile(dst_tile);
    unit_to_move->can_move = false;

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

// [new_element]

bool GameModel::check_action_new_element(Coord c, int elt_level, bool is_unit)
{
    // Check if the destination tile exists
    Tile* tile = this->game_map->get_tile(c);
    if (tile == nullptr) return false;

    // Verify the entity_level is correct
    if (this->current_player == NEUTRAL && elt_level != 0) return false;

    else {
        if (elt_level <= 0) return false;
        if (is_unit && elt_level > MAX_UNIT_LEVEL) return false;
        else if (!is_unit && elt_level > MAX_BUILDING_LEVEL) return false;
    }

    // Get the unit cost
    int unit_cost = (is_unit ? units_new_costs[elt_level] : buildings_new_costs[elt_level]);

    // Check if there is a province of the current player color adjacent to this tile that has the money to pay the unit
    Province* dst_prov = nullptr;

    for (Province* prov : *(this->game_map->_provinces_layer())) {

        if (prov->is_adjacent_to_coord(c)) {
            if (prov->_color() != this->current_player) continue;
            if (prov->_treasury() < unit_cost) continue;
            dst_prov = prov;
            break;
        }
    }

    if (dst_prov == nullptr) return false;

    // Check if there is an unit in the tile destination
    if (tile->_element() != nullptr) {

        Unit* dst_unit = dynamic_cast<Unit*>(tile->_element());
        if (dst_unit == nullptr) return false; // building

        // If it is an unit of the same color
        if (dst_unit->_color() == this->current_player) {
            if (dst_unit->_defense() == MAX_UNIT_LEVEL) return false;
            return (dst_unit->_defense() == elt_level) ? true : false;
        }
        else if (dst_unit->_defense() >= elt_level) return false;
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

    if (tile == nullptr) return;

    if (dst_prov == nullptr || dst_prov->_color() != this->current_player) {

        for (Province* prov : *(this->game_map->_provinces_layer())) {

            if (prov->is_adjacent_to_coord(c)) {
                if (prov->_color() != this->current_player) continue;
                if (prov->_treasury() < unit_cost) continue;
                src_prov = prov;
                break;
            }
        }

    }
    else src_prov = dst_prov;

    if (src_prov == nullptr) return;

    Element* new_unit;

    if (is_unit)
        new_unit = new Unit(c, this->current_player, elt_level);
    else
        new_unit = new Building(c, this->current_player, elt_level);

    if (new_unit == nullptr) return;

    if (dst_prov != nullptr && dst_prov->_color() == this->current_player) { // Same province, just move and may fusion

        Unit* fusion_with = nullptr;

        if (tile->_element() != nullptr) {

            Unit* unit = dynamic_cast<Unit*>(tile->_element());

            if (unit != nullptr && unit->_color() == new_unit->_color()) {
                if( !is_unit || unit->_defense() != new_unit->_defense()) return;
                fusion_with = unit;
            }
        }

        if (fusion_with != nullptr) fusion_with->upgrade();
        else tile->set_element(new_unit);

        src_prov->remove_treasury(unit_cost);

        return;
    }

    // adverse province
    if (dst_prov != nullptr) {
        // this->game_map->split_province(dst_tile->_coord());
        if (dynamic_cast<Building*>(tile->_element()) != nullptr)
            src_prov->add_treasury(dst_prov->_treasury());
    }

    tile->delete_element();
    tile->set_element(new_unit);
    this->game_map->remove_tile_of_all_provinces(tile->_coord());
    src_prov->add_tile(tile);
    //
    Unit* unit_to_move_unit = dynamic_cast<Unit*>(new_unit);
    if (unit_to_move_unit != nullptr) unit_to_move_unit->can_move = false;

    src_prov->remove_treasury(unit_cost);

    // Look for same color tiles connexion
    vector<Coord> n = neighbours(c);

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

    if (this->game_map == nullptr) return;

    std::map< int, int > to_convert_num;
    std::map< Coord, int > visited;

    std::deque< Coord > to_visit_coord;
    std::deque< int > to_visit_num;

    int nb_tot_nums = 0;

    for (std::pair<Coord, Tile*> it : *(this->game_map->_tiles_layer())) {

        Building* building = dynamic_cast<Building*>(this->game_map->get_tile_element(it.first));
        if (building == nullptr || building->_color() == NEUTRAL) continue;

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

        if (visited.count(v) > 0) continue;

        visited[v] = num;

        for (Coord vv : neighbours(v)) {

            int color2 = this->get_tile_color(vv);
    
            if (color2 == -1 || color2 != color) continue;

            if (visited.count(vv) > 0) {

                if (visited[vv] == num) continue;
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

    if (nb_differents <= 1) return; // no split to do

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
        this->game_map->add_province_from_list_of_tiles(list_of_tiles);
}


// ========================== [ Utility functions ] ===========================

usint max(usint a, usint b) { return (a > b) ? a : b; }

bool is_adjacent(Coord c1, Coord c2)
{
    if( get_tile_top_to(c1) == c2 ){ return true; }
    if( get_tile_top_left_to(c1) == c2 ){ return true; }
    if( get_tile_top_right_to(c1) == c2 ){ return true; }
    if( get_tile_bottom_to(c1) == c2 ){ return true; }
    if( get_tile_bottom_left_to(c1) == c2 ){ return true; }
    if( get_tile_bottom_right_to(c1) == c2 ){ return true; }

    return false;
}

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
