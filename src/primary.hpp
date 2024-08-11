#include <SDL2/SDL.h>
#include "globals.h"

void GAME_INIT(SDL_Window* window, SDL_Renderer* renderer);
void GAME_LOOP(SDL_Window* window, SDL_Renderer* renderer);

class Item{
	public:
		char* Name[32];

		void Use(){}
		
};

class Player{
	public:
		short int Health = 100; // HP, obvious
		short int Armor = 0; // Ditto for Armor
		double Armortype = 0.0; // The % of damage your armor absorbs, /100, 
		// When hit, armor takes DMG*Armortype damage, and health takes DMG*(1-Armortype) damage
		double Speed = 1 / TICKSPEED; // 1u / sec
};
