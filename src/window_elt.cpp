//
#include <queue>
#include <map>
#include <vector>
#include <list>
//
#include "geometry.hpp"
#include "map_tiles.hpp"
#include "view.hpp"



//
void WindowPage::draw_page(MainView* main_view){

    // Draw each element
    for ( WindowElt* elt : this->elts ) {
        //
        elt->draw_elt(main_view, nullptr);
    }

}


//
WindowPage* WindowPagesManager::get_current_page(){

    //
    if( this->pages.find(this->current_page) == this->pages.end() ){
        return nullptr;
    }

    //
    return this->pages[this->current_page];

}


//
void WindowPagesManager::draw_current_page( MainView* main_view ){

    //
    if( this->pages.find(this->current_page) == this->pages.end() ){
        return;
    }

    //
    this->pages[this->current_page]->draw_page(main_view);

}


//
void WindowPagesManager::set_current_page( std::string new_current_page ){
    //
    this->current_page = new_current_page;
}


//
int Value::get_value(){
    //
    return -2;
}

//
int ValueInt::get_value(){
    //
    return this->value;
}

//
float ValuePercent::get_value(){
    //
    return this->percent;
}

//
int ValuePercent::get_value_scaled(int value){
    //
    return (int)(this->percent * ((float)value) ) ;
}


//
int ValuePercentWinWidth::get_value(){
    //
    return (int)(this->percent * this->win_attr->win_width / 100.0 );
}


//
int ValuePercentWinHeight::get_value(){
    //
    return (int)(this->percent * this->win_attr->win_height / 100.0 );
}


//
ValueInt* nvi(int value){
    return new ValueInt(value);
}


//
ValuePercent* nvp(float percent){
    return new ValuePercent(percent);
}

//
ValuePercentWinWidth* nvpww(float prc, WindowAttributes* win_attr){
    return new ValuePercentWinWidth(prc, win_attr);
}

//
ValuePercentWinHeight* nvpwh(float prc, WindowAttributes* win_attr){
    return new ValuePercentWinHeight(prc, win_attr);
}


//
SpriteCrop* SPRITE_NO_CROP(){
    //
    return new SpriteCrop( nvp(0), nvp(0), nvp(1), nvp(1) );
}

//
SpriteCrop* SPRITE_CUSTOM_CROP(float src_x, float src_y, float src_w, float src_h){
    //
    return new SpriteCrop( nvp(src_x), nvp(src_y), nvp(src_w), nvp(src_h) );
}


//
SpriteRatio* SPRITE_RATIO_ORIGINAL(){
    //
    return new SpriteRatio(true, nullptr, nullptr);
}

//
SpriteRatio* SPRITE_RATIO_CUSTOM(float prc_dest_w, float prc_dest_h){
    //
    return new SpriteRatio(false, nvp(prc_dest_w), nvp(prc_dest_h));
}


//
SpriteResize* SPRITE_RESIZE_KEEP_ORIGINAL(float resize_factor){
    //
    return new SpriteResize(SPRITE_ENUM_RESIZE_KEEP_ORIGINAL, resize_factor);
}

//
SpriteResize* SPRITE_RESIZE_FIT(float resize_factor){
    //
    return new SpriteResize(SPRITE_ENUM_RESIZE_FIT, resize_factor);
}

//
SpriteResize* SPRITE_RESIZE_COVER(float resize_factor){
    //
    return new SpriteResize(SPRITE_ENUM_RESIZE_COVER, resize_factor);
}

//
SpritePosition* SPRITE_POS_ALIGN_START(){
    //
    return new SpritePosition(0, 0);
}

//
SpritePosition* SPRITE_POS_ALIGN_CENTER(){
    //
    return new SpritePosition(0.5, 0);
}

//
SpritePosition* SPRITE_POS_ALIGN_END(){
    //
    return new SpritePosition(1, 0);
}

//
SpritePosition* SPRITE_POS_CUSTOM(float percent, int delta){
    //
    return new SpritePosition(percent, delta);
}


//
int WindowElt::get_elt_state(WindowAttributes* win_attr, DrawTransform* transform){

    //
    int rx = this->get_x(transform);
    int ry = this->get_y(transform);
    int rw = this->get_w(transform);
    int rh = this->get_h(transform);

    //
    if ( is_point_in_rect(win_attr->mouse_x, win_attr->mouse_y, rx, ry, rw, rh) ) {

        //
        if( win_attr->mouse_left_bt_clicked > 0 ){

            //
            return STYLE_ELT_CLICKED;

        }

        //
        return STYLE_ELT_HOVER;

    }

    //
    return STYLE_ELT_BASE;

}

//
int WindowElt::get_x(DrawTransform* transform){
    //
    int res = this->x->get_value();
    //
    if(transform != nullptr && transform->translation_x != nullptr){
        res += transform->translation_x->get_value();
    }
    //
    return res;
}

//
int WindowElt::get_y(DrawTransform* transform){
    //
    int res = this->y->get_value();
    //
    if(transform != nullptr && transform->translation_y != nullptr){
        res += transform->translation_y->get_value();
    }
    //
    return res;
}

//
int WindowElt::get_w(DrawTransform* transform){
    //
    int res = this->w->get_value();
    //
    if(transform != nullptr){
        res = (int)( ((float)res) * transform->scale_w );
    }
    //
    return res;
}

//
int WindowElt::get_h(DrawTransform* transform){
    //
    int res = this->h->get_value();
    //
    if(transform != nullptr){
        res = (int)( ((float)res) * transform->scale_h );
    }
    //
    return res;
}

//
void WindowElt::draw_elt(MainView* main_view, DrawTransform* transform){

    // Template abstract class

}



//
void WindowEltText::draw_elt(MainView* main_view, DrawTransform* transform){

    //
    int elt_state = this->get_elt_state( main_view->get_win_attr(), transform );

    //
    Color cl = this->style->get_fg_color( elt_state );
    int font_size = this->style->get_font_size( elt_state );

    //
    int x = this->get_x(transform);
    int y = this->get_y(transform);
    int w = this->get_w(transform);
    int h = this->get_h(transform);

    //
    main_view->draw_text( this->txt, cl, font_size, x, y, w, h );

}



//
void WindowEltButton::draw_elt(MainView* main_view, DrawTransform* transform){

    //
    int elt_state = this->get_elt_state( main_view->get_win_attr(), transform );

    //
    Color fg_cl = this->style->get_fg_color( elt_state );
    Color bg_cl = this->style->get_bg_color( elt_state );
    int radius = this->style->get_radius( elt_state );
    int font_size = this->style->get_font_size( elt_state );

    //
    int x = this->get_x(transform);
    int y = this->get_y(transform);
    int w = this->get_w(transform);
    int h = this->get_h(transform);

    //
    int w2 = (int) w / 2;
    int h2 = (int) h / 2;

    //
    if (radius > w2){
        radius = w2;
    }
    //
    if (radius > h2){
        radius = h2;
    }

    //
    main_view->draw_button_1( x, y, w, h, this->txt, fg_cl, bg_cl, font_size, radius );

}



//
void WindowEltSprite::draw_elt(MainView* main_view, DrawTransform* transform){

    //
    // int elt_state = this->get_elt_state( main_view->get_win_attr(), transform );

    SDL_Texture* texture = main_view->get_texture(img_path);
    //

    //
    int dest_x = this->get_x(transform);
    int dest_y = this->get_y(transform);
    int dest_w = this->get_w(transform);
    int dest_h = this->get_h(transform);

    //
    int f_dest_x = dest_x;
    int f_dest_y = dest_y;
    int f_dest_w = dest_w;
    int f_dest_h = dest_h;

    //
    int base_src_w, base_src_h;
    SDL_QueryTexture(texture, nullptr, nullptr, &base_src_w, &base_src_h);
    //
    int src_x = 0;
    int src_y = 0;
    int src_w = base_src_w;
    int src_h = base_src_h;

    //
    int angle = this->angle->get_value();

    // CROP

    if( this->sprite_crop != nullptr ){

        //
        if( this->sprite_crop->src_x != nullptr ){
            src_x = this->sprite_crop->src_x->get_value_scaled(base_src_w);
        }

        //
        if( this->sprite_crop->src_y != nullptr ){
            src_y = this->sprite_crop->src_y->get_value_scaled(base_src_h);
        }

        //
        if( this->sprite_crop->src_w != nullptr ){
            src_w = this->sprite_crop->src_w->get_value_scaled(base_src_w);
        }

        //
        if( this->sprite_crop->src_h != nullptr ){
            src_h = this->sprite_crop->src_h->get_value_scaled(base_src_h);
        }

    }

    // CROP CLAMPING

    //
    if(src_x < 0){ src_x = 0; }
    if(src_y < 0){ src_y = 0; }
    if(src_x >= base_src_w){ src_x = base_src_w - 1; }
    if(src_x >= base_src_w){ src_x = base_src_w - 1; }
    //
    if( src_w > base_src_w - src_x ){ src_w = base_src_w - src_x; }
    if( src_h > base_src_h - src_y ){ src_h = base_src_h - src_y; }

    // RATIO

    if( this->sprite_ratio != nullptr){

        // Keep original source ratio for final destination ratio
        if( this->sprite_ratio->keep_original ){

            //
            f_dest_w = src_w;
            f_dest_h = src_h;

        }

        // Multiply final destination ratio from base rect destination ratio
        else{

            //
            if( this->sprite_ratio->prc_dest_w != nullptr ){

                //
                f_dest_w = this->sprite_ratio->prc_dest_w->get_value_scaled( dest_w );

            }

            //
            if( this->sprite_ratio->prc_dest_h != nullptr ){

                //
                f_dest_h = this->sprite_ratio->prc_dest_h->get_value_scaled( dest_h );

            }

        }

    }

    // Check image dimensions
    if( f_dest_h == 0 || f_dest_w == 0 || dest_w == 0 || dest_h == 0 ){
        return;
    }

    // RESIZE

    //
    if( this->sprite_resize != nullptr ){

        // Get the source and destination ratios
        float src_ratio = (float) f_dest_w / (float) f_dest_h;
        float dst_ratio = (float) dest_w / (float) dest_h;

        // Keep original dimensions
        if( this->sprite_resize->mode == SPRITE_ENUM_RESIZE_KEEP_ORIGINAL ){

            // Do nothing, keep original dimensions

        }

        // Fit = all the image must be within the destination rectangle, there can be empty pixels
        else if( this->sprite_resize->mode == SPRITE_ENUM_RESIZE_FIT ){

            //
            if( src_ratio > dst_ratio ){

                //
                f_dest_w = dest_w;
                f_dest_h = (int) ((float) f_dest_w / src_ratio);

            }
            //
            else{

                //
                f_dest_h = dest_h;
                f_dest_w = (int) ((float) f_dest_h * src_ratio);

            }

        }

        // Cover = all the destination rectangle must fit inside the image, there can't be empty pixels
        else if( this->sprite_resize->mode == SPRITE_ENUM_RESIZE_COVER ){

            //
            if( src_ratio < dst_ratio ){

                //
                f_dest_w = dest_w;
                f_dest_h = (int) ((float) f_dest_w / src_ratio);

            }
            //
            else{

                //
                f_dest_h = dest_h;
                f_dest_w = (int) ((float) f_dest_h * src_ratio);

            }

        }

        // Global resize factor (by default to 1.0 )
        f_dest_w = (int) ( (float) f_dest_w * this->sprite_resize->resize_factor );
        f_dest_h = (int) ( (float) f_dest_h * this->sprite_resize->resize_factor );

    }

    // POSITION

    // Horizontal
    if( this->sprite_h_position != nullptr ){

        //
        f_dest_x = dest_x + (int) ( (float) (dest_w - f_dest_w) * this->sprite_h_position->percent) + this->sprite_v_position->delta;

    }

    // Horizontal
    if( this->sprite_v_position != nullptr ){

        //
        f_dest_y = dest_y + (int) ( (float) (dest_h - f_dest_h) * this->sprite_v_position->percent) + this->sprite_v_position->delta;

    }

    //
    main_view->draw_image( texture, src_x, src_y, src_w, src_h, f_dest_x, f_dest_y, f_dest_w, f_dest_h, angle, this->flip_h, this->flip_v );

}


//
WindowEltMapTile::WindowEltMapTile(int tile, Style* style, Value* x, Value* y, Value* w, Value* h)
: WindowElt(style, x, y, w, h), tile(tile)
{
    //
    if ( tile < 0 || tile > 69 ){

        //
        return;

    }

    //
    this->ground_base_layer = nullptr;
    this->ground_top_layer = nullptr;

    //
    if ( allTileData[tile].tags[0] != nullptr ){

        //
        std::string img_path = "res/sprites/map_w/" + std::string(allTileData[tile].ground_layer_img);

        //
        this->ground_base_layer = new WindowEltSprite(
                style,
                img_path,
                this->x, this->y, this->w, this->h,
                new ValueInt(0),
                false,
                false,
                SPRITE_NO_CROP(),
                SPRITE_RATIO_CUSTOM(1, 1),
                SPRITE_RESIZE_COVER(),
                SPRITE_POS_ALIGN_START(),
                SPRITE_POS_ALIGN_START()
        );

    }

    //
    if ( allTileData[tile].top_layer_img != nullptr ){

        //
        std::string img_path = "res/sprites/map_w/" + std::string(allTileData[tile].top_layer_img);

        //
        this->ground_top_layer = new WindowEltSprite(
                style,
                img_path,
                this->x, this->y, this->w, this->h,
                new ValueInt(0),
                false,
                false,
                SPRITE_NO_CROP(),
                SPRITE_RATIO_CUSTOM(1, 1),
                SPRITE_RESIZE_COVER(),
                SPRITE_POS_ALIGN_START(),
                SPRITE_POS_ALIGN_START()
        );

    }

}


//
void WindowEltMapTile::draw_elt(MainView* main_view, DrawTransform* transform){

    //
    if (this->ground_base_layer != nullptr){
        //
        this->ground_base_layer->draw_elt(main_view, transform);
    }

    //
    if (this->ground_top_layer != nullptr){
        //
        this->ground_top_layer->draw_elt(main_view, transform);
    }

}


//
void WindowEltMapTile::set_ground_base(std::string ground_base_img){

    //
    if (this->ground_base_layer != nullptr){

        //
        delete this->ground_base_layer;

    }

    //
    std::string img_path = "res/sprites/map_w/" + ground_base_img;

    //
    this->ground_base_layer = new WindowEltSprite(
        this->style,
        img_path,
        this->x, this->y, this->w, this->h,
        new ValueInt(0),
        false,
        false,
        SPRITE_NO_CROP(),
        SPRITE_RATIO_CUSTOM(1, 1),
        SPRITE_RESIZE_COVER(),
        SPRITE_POS_ALIGN_START(),
        SPRITE_POS_ALIGN_START()
    );

}


//
void WindowEltMapViewer::draw_elt(MainView* main_view, DrawTransform* transform){

    //
    int zoomed_W = TILE_IMG_W * this->zoom;
    int zoomed_H = TILE_IMG_H * this->zoom;
    int A = 36 * this->zoom;
    int B = 53 * this->zoom;

    //
    int start_tile_x = (int) (this->cam_x / zoomed_W) - 3;
    int start_tile_y = (int) (this->cam_y / zoomed_H) - 3;

    int nb_cols_to_display = (int) (this->get_w() / zoomed_W) + 3;
    int nb_rows_to_display = (int) (this->get_h() / zoomed_H) + 3;

    //
    DrawTransform* tile_transform = nullptr;

    //
    int base_dec_x;
    int base_dec_y;
    float base_zoom_w = this->zoom;
    float base_zoom_h = this->zoom;

    //
    ValueInt* dep_x = nvi(0);
    ValueInt* dep_y = nvi(0);

    //
    if ( transform == nullptr ){

        //
        base_dec_x = this->cam_x;
        base_dec_y = this->cam_y;
    }
    //
    else{

        //
        base_dec_x = transform->translation_x->get_value() + this->cam_x;
        base_dec_y = transform->translation_y->get_value() + this->cam_y;
        base_zoom_w *= transform->scale_w;
        base_zoom_h *= transform->scale_h;

    }

    //
    tile_transform = new DrawTransform( dep_x, dep_y, base_zoom_w, base_zoom_h);

    //
    for( int tile_x = start_tile_x ; tile_x < start_tile_x + nb_cols_to_display; tile_x ++ ){

        //
        for( int tile_y = start_tile_y ; tile_y < start_tile_y + nb_rows_to_display; tile_y ++ ){

            //
            Vector2 coord = {tile_x, tile_y};

            //
            WindowEltMapTile* tile = this->get_layer_tile_at_coord( coord );

            //
            if (tile == nullptr){

                //
                continue;
            }

            //
            dep_x->value = base_dec_x + tile_x * B;
            //
            if (tile_x % 2 == 0){
                dep_y->value = base_dec_y + A + tile_y * zoomed_H;
            }
            else{
                dep_y->value = base_dec_y + tile_y * zoomed_H;
            }

            //
            tile->draw_elt(main_view, tile_transform);

        }

    }

}


//
void WindowEltMapViewer::clear(){

    //
    for ( std::pair<const Vector2, WindowEltMapTile*> const it : this->tiles_layers ){

        //
        if ( it.second == nullptr ){
            continue;
        }

        //
        delete it.second;

    }

    //
    this->tiles_layers.erase( this->tiles_layers.begin(), this->tiles_layers.end() );

}


//
void WindowEltMapViewer::add_tile_to_tile_layer( int tile_x, int tile_y, int tile_num ){

    //
    Vector2 v = (Vector2){tile_x, tile_y};

    //
    std::map< Vector2, WindowEltMapTile*>::iterator res_iter = this->tiles_layers.find( v );
    if( res_iter != this->tiles_layers.end() ){

        // res_iter->first is the key, res_iter->second is the value
        delete res_iter->second;
    }

    //
    int cx = 53 * tile_x;;
    int cy = 0;

    //
    if ( tile_x % 2 == 0 ) {

        //
        cy = 36 + 72 * ( tile_y );

    }

    //
    else {

        //
        cy = 72 * ( tile_y );

    }

    //
    // cout << "DEBUG | " << cx << ", " << cy << "\n";

    cx = 0;
    cy = 0;

    //
    this->tiles_layers[v] = new WindowEltMapTile(
        tile_num,
        this->style,
        nvi(cx),
        nvi(cy),
        nvi(TILE_IMG_W),
        nvi(TILE_IMG_W)
    );

}

//
void WindowEltMapViewer::complete_all_tile_layer_ground_base(){

    //
    Vector2 case_with_max(0, 0);
    int max_non_null_adj = -1;
    std::vector< std::string > max_adj_ground_base;

    //
    std::list< Vector2 > cases_with_null;

    // FIRST SEARCH

    //
    for ( std::pair<Vector2, WindowEltMapTile*> it_pair : this->tiles_layers ){

        //
        Vector2 pos = it_pair.first;
        WindowEltMapTile* tile = it_pair.second;

        //
        if ( tile == nullptr ){ continue; }

        //
        if ( tile->ground_base_layer != nullptr ){ continue; }

        //
        cases_with_null.push_back( pos );

        //
        std::vector< std::string > adj_ground_base = this->get_adjacents_tiles_base_ground_to_tile( pos.x, pos.y );

        //
        if( max_non_null_adj == -1 || max_non_null_adj < adj_ground_base.size() ){

            //
            case_with_max = pos;
            max_non_null_adj = adj_ground_base.size();
            max_adj_ground_base = adj_ground_base;

        }

    }

    // WHILE LOOP

    //
    while ( max_non_null_adj != -1 ) {

        // Delete the coordinate that will be processed
        cases_with_null.remove(case_with_max);

        //
        std::map< std::string, int > counts;

        //
        for( std::string ground_base : max_adj_ground_base ){

            //
            if( counts.count(ground_base) == 0 ){
                counts[ground_base] = 1;
            }
            else{
                counts[ground_base] += 1;
            }
        }

        //
        std::string maxi_ground_base;
        int maxi_count = -1;

        //
        for ( std::pair<std::string, int> it_pair : counts ){

            //
            if ( maxi_count == -1 || it_pair.second > maxi_count ){

                maxi_ground_base = it_pair.first;
                maxi_count = it_pair.second;

            }

        }

        //
        WindowEltMapTile* w_tile = get_layer_tile_at_coord( case_with_max );

        //
        if ( w_tile == nullptr ){

            //
            if ( maxi_count == -1 ){

                //
                w_tile->set_ground_base( allTileData[w_tile->tile].ground_layer_img );

            }
            //
            else {

                //
                w_tile->set_ground_base( maxi_ground_base );

            }

        }

        // GET THE NEW TILE TO PROCESS
        max_non_null_adj = -1;

        //
        for ( Vector2 coord : cases_with_null ){

            //
            std::vector< std::string > adj_ground_base = this->get_adjacents_tiles_base_ground_to_tile( coord.x, coord.y );

            //
            if( max_non_null_adj == -1 || max_non_null_adj < adj_ground_base.size() ){

                //
                case_with_max = coord;
                max_non_null_adj = adj_ground_base.size();
                max_adj_ground_base = adj_ground_base;

            }

        }

    }

}


//
std::vector< Vector2 > WindowEltMapViewer::get_adjacents_tiles_coords_to_tile(int x, int y){

    //
    std::vector< Vector2 > adjacent_tiles;

    //
    Vector2 coord1(x, y-1);
    Vector2 coord2(x, y+1);
    Vector2 coord3(x-1, y);
    Vector2 coord4(x+1, y);
    Vector2 coord5(x-1, y+1);
    Vector2 coord6(x+1, y+1);

    //
    if( x % 2 == 1 ){

        //
        coord5.y = y - 1;
        coord6.y = y - 1;

    }

    //
    if ( this->tiles_layers.count( coord1 ) ) { adjacent_tiles.push_back( coord1 ); }
    if ( this->tiles_layers.count( coord2 ) ) { adjacent_tiles.push_back( coord2 ); }
    if ( this->tiles_layers.count( coord3 ) ) { adjacent_tiles.push_back( coord3 ); }
    if ( this->tiles_layers.count( coord4 ) ) { adjacent_tiles.push_back( coord4 ); }
    if ( this->tiles_layers.count( coord5 ) ) { adjacent_tiles.push_back( coord5 ); }
    if ( this->tiles_layers.count( coord6 ) ) { adjacent_tiles.push_back( coord6 ); }

    //
    return adjacent_tiles;

}


//
std::vector< std::string > WindowEltMapViewer::get_adjacents_tiles_base_ground_to_tile(int x, int y){

    //
    std::vector< Vector2 > adj_coords = this->get_adjacents_tiles_coords_to_tile(x, y);

    //
    std::vector< std::string > res;

    //
    for( Vector2 coord : adj_coords ){

        //
        WindowEltMapTile* mt = this->get_layer_tile_at_coord(coord);

        //
        if( mt == nullptr ){

            //
            continue;

        }
        //
        if( mt->ground_base_layer == nullptr ){

            //
            continue;
        }

        //
        res.push_back( mt->ground_base_layer->img_path );

    }

    //
    return res;

}


//
WindowEltMapTile* WindowEltMapViewer::get_layer_tile_at_coord(Vector2 coord){

    //
    if ( this->tiles_layers.count( coord ) <= 0 ){

        //
        return nullptr;

    }

    //
    return this->tiles_layers[coord];

}
