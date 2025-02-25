#include "view.hpp"



//
void MainView::sdl_error(char error_msg[]){

    // Display & log error message
    SDL_Log(error_msg);

    // Destroy all the allocated SDL memory for a clean exit
    this->destroy_all_created();

    // Quit SDL then the program
    SDL_Quit();
    exit(1);
}


//
void MainView::destroy_all_created(){

    // Destroy the sdl window surface
    if(this->sdl_window_surface != nullptr){
        SDL_DestroyWindowSurface(this->sdl_window_surface);
        this->sdl_window_surface = nullptr;
    }

    // Destroy the sdl renderer
    if(this->sdl_renderer != nullptr){
        SDL_DestroyRenderer(this->sdl_renderer);
        this->sdl_renderer = nullptr;
    }

    // Destroy the sdl window
    if(this->sdl_window != nullptr){
        SDL_DestroyWindow(this->sdl_window);
        this->sdl_window = nullptr;
    }
}


// Constructor
MainView::MainView(GameModel* game_model)
    : game_model(game_model)  // Automatic initialization of the attribute
{

    // Init SDL & Error Check
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        sprintf(SDL_ERROR_BUFFER, "SDL_Init Error: %s", SDL_GetError());
        this->sdl_error(SDL_ERROR_BUFFER);
    }


    // Window creation
    this->sdl_window = SDL_CreateWindow(
                                        "The Game",
                                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        WIN_SIZE_WIDTH, WIN_SIZE_HEIGHT,
                                        SDL_WINDOW_SHOWN
    );
    // Verify window creation
    if(!this->sdl_window){
        sprintf(SDL_ERROR_BUFFER, "SDL_CreateWindow Error: %s", SDL_GetError());
        this->sdl_error(SDL_ERROR_BUFFER);
    }

    // Create renderer with vsync to limit frame rate
    this->sdl_renderer = SDL_CreateRenderer(this->sdl_window, -1,
                                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Verify renderer
    if (!this->sdl_renderer) {
        sprintf(SDL_ERROR_BUFFER, "SDL_CreateRenderer Error: %s", SDL_GetError());
        this->sdl_error(SDL_ERROR_BUFFER);
    }

    // Get the window surface
    this->sdl_window_surface = SDL_GetWindowSurface(this->sdl_window);

    // Verify the window surface
    if (!this->sdl_window_surface) {
        sprintf(SDL_ERROR_BUFFER, "SDL_GetWindowSurface Error: %s", SDL_GetError());
        this->sdl_error(SDL_ERROR_BUFFER);
    }
}

// Destructor
MainView::~MainView(){
    //
    this->destroy_all_created();
    //
    SDL_Quit();
}


// Main update display method
void MainView::update_display(){
    SDL_UpdateWindowSurface(this->sdl_surface);
}









