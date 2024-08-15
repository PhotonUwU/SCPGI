#include <iostream>
#include <SDL2/SDL.h>
#include "map.hpp"

void MapRender(SDL_Window* window, SDL_Renderer* renderer, double x, double y, double z, double rx, double ry, Chunk* Map)
{
	for(unsigned short int i = 0; i < 1024; i++){
		if(Map->walls[i].Points[0] == 0 && Map->walls[i].Points[1] == 0 && Map->walls[i].Points[2] == 0 && Map->walls[i].Points[3] == 0)
		{
			break;
		}
		SDL_SetRenderDrawColor(renderer, 0,0,255,255);
		SDL_RenderDrawLine(renderer, Map->walls[i].Points[0]+(WIN_WIDTH/2), Map->walls[i].Points[1]+(WIN_HEIGHT/2), Map->walls[i].Points[2]+(WIN_WIDTH/2), Map->walls[i].Points[3]+(WIN_HEIGHT/2));
	}
	return;
}

void ViewRender(SDL_Window* window, SDL_Renderer* renderer, double x, double y, double z, double rx, double ry, Chunk* Map)
{
	for(unsigned short int i = 0; i < 1024; i++){
		if(Map->walls[i].Points[0] == Map->walls[i].Points[2] && Map->walls[i].Points[1] == Map->walls[i].Points[3])
		{
			break;
		}
		SDL_SetRenderDrawColor(renderer, 0,0,255,255);
		SDL_RenderDrawLine(renderer, Map->walls[i].Points[0], Map->walls[i].Points[1], Map->walls[i].Points[2], Map->walls[i].Points[3]);
		
	}
	return;
}

void Render(SDL_Window* window, SDL_Renderer* renderer, double x, double y, double z, double rx, double ry, bool MapView, Chunk* Map){
	if(MapView)
	{
		MapRender(window, renderer, x, y, z, rx, ry, Map);
	}
	else
	{
		ViewRender(window, renderer, x, y, z, rx, ry, Map);
	}
	return;
}
