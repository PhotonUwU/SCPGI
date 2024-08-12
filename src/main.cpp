#include <SDL2/SDL.h>
#include <iostream>
#include "primary.hpp"

bool SILENT_START = false;
bool DEBUG = false;
bool HELP = false;

void parseArgs(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg == "-s" || arg == "--no-startup") {
            SILENT_START = true;
        } else if (arg == "-d" || arg == "--debug") {
            DEBUG = true;
        } else if (arg == "-h" || arg == "--help"){
        	HELP = true;
        }
    }
}

int main(int argc, char* argv[]) {

	parseArgs(argc, argv);
	if(HELP){
		std::cout << "Usage: scpgi [FLAGS]" << std::endl;
		std::cout << "-s OR --no-startup: Skips the Game Startup, including Game Name, Attributions, Liscence, & Splashscreen" << std::endl;
		std::cout << "-d OR --debug: Enables Debug Info in terminal, & starts the game in a Debug level, as well as allowing spectator mode" << std::endl;
		std::cout << "-h OR --help: Displays this help screen" << std::endl;
		return 0;
	}
    // Initialize game
    GAME_INIT(SILENT_START);
    
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create the window
    SDL_Window* window = SDL_CreateWindow(
        WIN_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIN_WIDTH,
        WIN_HEIGHT,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED
    );

    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create the renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Main game loop
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    WIN_WIDTH = event.window.data1;
                    WIN_HEIGHT = event.window.data2;
            }
        }
        // Call game loop function
        GAME_LOOP(window, renderer, DEBUG);
        SDL_Delay(1000/TICKSPEED);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
