#include <SDL2/SDL.h>
#include "map.hpp"
#include "renderer.hpp"
#include <iostream>

Chunk map[5];
Player player;
unsigned short int State = 0;

void GAME_INIT(bool silent, bool debug, bool mapeditor)
{
	if(!silent){
		std::cout << "\x1b[32;1m";
		std::cout << ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;" << std::endl;
		std::cout << ";;        SCP: Green Insignia       ;;" << std::endl;
		std::cout << ";;            By Photon Law         ;;" << std::endl;
		std::cout << ";;  A game set in the SCP Universe  ;;" << std::endl;
		std::cout << ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;" << std::endl;
		SDL_Delay(3000);
		std::cout << "\x1b[0m";
		std::cout << "\x1b[31;3m";
		std::cout << "The following are on the SCP Wiki, under CC-BY-SA liscence:" << std::endl;
		SDL_Delay(2500);
		std::cout << "\x1b[23m";
		std::cout << std::endl;
		std::cout << "Chaos Insurgency written by Kain Pathos Crow" << std::endl;
		SDL_Delay(500);
		std::cout << "SCP 939 written by Adam Smascher and EchoFourDelta" << std::endl;
		SDL_Delay(500);
		std::cout << "SCP 096 written by Dr Dan" << std::endl;
		SDL_Delay(500);
		std::cout << "SCP 173 written by Moto42" << std::endl;
		SDL_Delay(500);
		std::cout << "SCP 049 written by djkaktus & Gabriel Jade" << std::endl;
		SDL_Delay(500);
		std::cout << "SCP 106 written by Dr Gears" << std::endl;
		std::cout << "=====================================================" << std::endl;
		SDL_Delay(5000);
		std::cout << "\x1b[34m";
		std::cout << "Programming by Photon Law" << std::endl;
		SDL_Delay(200);
		std::cout << "Textures by Photon Law" << std::endl;
		SDL_Delay(200);
		std::cout << "Models by Photon Law" << std::endl;
		SDL_Delay(200);
		std::cout << "FMV Intro by Photon Law" << std::endl;
		SDL_Delay(200);
		std::cout << "Story by Photon Law" << std::endl;
		SDL_Delay(750);
		std::cout << std::endl;
		std::cout << "\"Photon Law\" is an alias, and not a legal name" << std::endl;
		std::cout << "=====================================================" << std::endl;
		SDL_Delay(3000);
		std::cout << "Business & Legal contact: photonlaw6+SCPGI@gmail.com" << std::endl;
		std::cout << "=====================================================" << std::endl;
		SDL_Delay(1000);
		std::cout << "\x1b[37;2m";
		std::cout << "SCP: " << WIN_TITLE << " is distributed under the CC-BY-SA liscence" << std::endl;
		std::cout << "https://creativecommons.org/licenses/by-sa/3.0/deed.en" << std::endl;
		SDL_Delay(3000);
		std::cout << "=====================================================" << std::endl;
		std::cout << "\x1b[0m" << std::endl;
	}
	else
	{
		State = 1;
	}
	if(debug){
		std::cout << "DEBUG MODE ENABLED" << std::endl;
		LoadChunk("DEBUG", 0, 0, &map[0]);
		State = 2;
	}
	if(mapeditor){
		std::cout << "MAP EDIT MODE ENABLED" << std::endl;
		State = 5000;
	}
	return;
}

void GAME_LOOP(SDL_Window* window, SDL_Renderer* renderer, bool debug)
{
	SDL_SetRenderDrawColor(renderer, 0,0,0,255);
	SDL_RenderClear(renderer);
	if(State==2 || State == 5000){
		Render(window, renderer, player.Pos[0],player.Pos[1],player.Pos[2],player.Rot[0],player.Rot[1], true, &map[0]);
	}
	SDL_RenderPresent(renderer);
	return;
}
