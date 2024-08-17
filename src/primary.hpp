#ifndef PRIMARY_HPP
#define PRIMARY_HPP
#include <SDL2/SDL.h>
#include "map.hpp"

void GAME_INIT(bool silent, bool debug, bool mapeditor);
void GAME_LOOP(SDL_Window* window, SDL_Renderer* renderer, bool debug);
#endif
