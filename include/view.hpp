#include <SDL.h>
#include <iostream>
#include <cstdio>

#include <model.hpp>

static const int WIN_SIZE_WIDTH = 900;
static const int WIN_SIZE_HEIGHT = 700;

static const char SDL_ERROR_BUFFER[1000];


class MainView{

    private:

        // SDL related attributes
        SDL_Window* sdl_window = nullptr;
        SDL_Surface* sdl_window_surface = nullptr;
        SDL_Renderer* sdl_renderer = nullptr;

        // Reference to game_model
        GameModel* game_model = nullptr;

        void sdl_error(char error_msg[]){

            // Display & log error message
            SDL_Log(error_msg);

            //
            if(this->sdl_window != nullptr){
                SDL_DestroySurface(this->sdl_window_surface);
            }
            //
            if(this->sdl_renderer != nullptr){
                SDL_DestroyRenderer(this->sdl_renderer);
            }
            //
            if(this->sdl_window != nullptr){
                SDL_DestroyWindow(this->sdl_window);
            }
            //
            SDL_Quit();
            exit(1);
        }


    public:

        // Constructor
        MainView(GameModel* game_model)
            : game_model(game_model)  // Automatic initialization of the attribute
        {

            if (SDL_Init(SDL_INIT_VIDEO) != 0 )
            {
                sprintf(SDL_ERROR_BUFFER, "SDL_Init Error: %s", SDL_GetError());
                this->sdl_error(SDL_ERROR_BUFFER);            }


            // Window creation
            this->sdl_window = SDL_CreateWindow(
                                                "The Game",
                                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                                WIN_SIZE_WIDTH, WIN_SIZE_HEIGHT,
                                                SDL_WINDOW_SHOWN
            );
            //
            if(!this->sdl_window){
                sprintf(SDL_ERROR_BUFFER, "SDL_CreateWindow Error: %s", SDL_GetError());
                this->sdl_error(SDL_ERROR_BUFFER);
            }

            // Create renderer with vsync to limit frame rate
            this->sdl_renderer = SDL_CreateRenderer(this->sdl_window, -1,
                                                        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

            //
            if (!this->sdl_renderer) {
                sprintf(SDL_ERROR_BUFFER, "SDL_CreateRenderer Error: %s", SDL_GetError());
                this->sdl_error(SDL_ERROR_BUFFER);
            }

            // Get the window surface
	        this->sdl_window_surface = SDL_GetWindowSurface(this->sdl_window);
        }

        // Destructor
        ~MainView(){
            SDL_Quit();
        }


        // Main update display method
        void update_display(){
		    SDL_UpdateWindowSurface(this->sdl_surface);
        }

};


