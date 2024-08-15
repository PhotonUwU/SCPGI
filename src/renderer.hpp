#ifndef RENDERER_HPP
#define RENDERER_HPP
void Render(SDL_Window* window, SDL_Renderer* renderer, double x, double y, double z, double rx, double ry, bool MapView, Chunk* Map);
void MapRender(SDL_Window* window, SDL_Renderer* renderer, double x, double y, double z, double rx, double ry, Chunk* Map);
void ViewRender(SDL_Window* window, SDL_Renderer* renderer, double x, double y, double z, double rx, double ry, Chunk* Map);
#endif
