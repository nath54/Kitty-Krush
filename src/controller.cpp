//
#include <SDL2/SDL.h>
//
#include <string>
//
#include "controller.hpp"
#include "window_attributes.hpp"
#include "events.hpp"


//
std::string getKeyNameFromEvent(SDL_Event& event) {

    //
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {

        //
        SDL_Keysym keysym = event.key.keysym;

        // First, try to get the printable character

        //
        if (keysym.sym >= SDLK_a && keysym.sym <= SDLK_z) {
            //
            return std::string(1, static_cast<char>(keysym.sym));
        }

        //
        else if (keysym.sym >= SDLK_0 && keysym.sym <= SDLK_9) {
            //
            return std::string(1, static_cast<char>(keysym.sym));
        }

        //
        else if (keysym.sym >= SDLK_KP_0 && keysym.sym <= SDLK_KP_9) {
            //
            return std::string(1, static_cast<char>('0' + (keysym.sym - SDLK_KP_0)));
        }

        //
        else {
            // If it's not a simple printable character, try to get the SDL key name

            const char* keyName = SDL_GetKeyName(keysym.sym);

            if (keyName != nullptr && keyName[0] != '\0') {
                return std::string(keyName);
            }
        }

        // Handle special keys that might not have a direct SDL_GetKeyName
        switch (keysym.sym) {
            case SDLK_UP:    return "up";
            case SDLK_DOWN:  return "down";
            case SDLK_LEFT:  return "left";
            case SDLK_RIGHT: return "right";
            case SDLK_SPACE: return "space";
            case SDLK_RETURN: return "return";
            case SDLK_ESCAPE: return "escape";
            case SDLK_TAB:    return "tab";
            case SDLK_LCTRL:  return "lctrl";
            case SDLK_RCTRL:  return "rctrl";
            case SDLK_LSHIFT: return "lshift";
            case SDLK_RSHIFT: return "rshift";
            case SDLK_LALT:   return "lalt";
            case SDLK_RALT:   return "ralt";
            case SDLK_CAPSLOCK: return "capslock";
            case SDLK_NUMLOCKCLEAR: return "numlock";
            case SDLK_SCROLLLOCK: return "scrolllock";
            case SDLK_PAGEUP: return "pageup";
            case SDLK_PAGEDOWN: return "pagedown";
            case SDLK_HOME:   return "home";
            case SDLK_END:    return "end";
            case SDLK_INSERT: return "insert";
            case SDLK_DELETE: return "delete";
            case SDLK_PRINTSCREEN: return "printscreen";
            case SDLK_PAUSE: return "pause";
            // Add more special keys as needed
            default:
                return "unknown";
        }
    }
    return ""; // Not a key down or up event
}



//
void GameController::manage_events(WindowAttributes* win_attr, EventsManager* events_manager){

    //
    this->polled_events = 0;

    // Poll all the awaiting events
    SDL_Event event;
    while (this->game_model->is_running && SDL_PollEvent(&event) && this->polled_events < this->max_events_to_poll_at_each_frame)
    {
        //
        this->polled_events++;

        //
        Event* evt = nullptr;

        //
        switch (event.type)
        {
            // Quit event
            case SDL_QUIT:
                //
                this->game_model->is_running = false;
                break;

            //
            case SDL_MOUSEBUTTONDOWN:
                //
                events_manager->new_event(
                     win_attr->update_mouse_button_state(event.button.button, 1)
                );

                break;

            //
            case SDL_MOUSEBUTTONUP:
                //
                events_manager->new_event(
                    win_attr->update_mouse_button_state(event.button.button, 0)
                );
                //
                break;

            //
            case SDL_MOUSEMOTION:
                //
                events_manager->new_event(
                    win_attr->update_mouse_button_state(-1, -1)
                );
                //
                events_manager->new_event(
                    new EventMouseMotion(
                        event.motion.x, event.motion.y
                    )
                );
                //
                break;

            //
            case SDL_MOUSEWHEEL:
                //
                events_manager->new_event(
                    new EventMouseScroll( event.wheel.mouseX, event.wheel.mouseY, event.wheel.x, event.wheel.y )
                );
                //
                break;

            //
            case SDL_KEYDOWN:
                //
                events_manager->new_event(
                    win_attr->update_keyboard_state( getKeyNameFromEvent(event) , true)
                );
                //
                break;

            //
            case SDL_KEYUP:
                //
                events_manager->new_event(
                    win_attr->update_keyboard_state( getKeyNameFromEvent(event) , false)
                );
                //
                break;

            //
            default: break;
        }
    }

}
