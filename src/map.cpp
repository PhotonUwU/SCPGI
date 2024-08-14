#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "globals.h"

class Item{
	public:
		std::string Name;
		int Texture;
		int HoldTexture;
		int Data[8];
		void Use(){}
		
};

class Player{
	public:
		short int Health = 100; // HP, obvious
		short int Armor = 0; // Ditto for Armor
		double Armortype = 0.0; // The % of damage your armor absorbs, /100, 
		// When hit, armor takes DMG*Armortype damage, and health takes DMG*(1-Armortype) damage
		double Speed = 5 / TICKSPEED; // u / sec

		Item inventory[16];
};

struct GameVars{
		unsigned short int State = 0;
};

struct Wall{
	double Points[4];
	short int Texture;
	unsigned short int Sectors[2];
	bool Portal;
	unsigned short int Function;
	unsigned short int Target;
};

struct Sector{
	Wall* walls[16];
	short int FloorTexture;
	short int CeilTexture;	
	double FloorHeight;
	double CeilHeight;
	short int Tag;
	bool IsValid;
};

class Object{
	public:
		double Position[2];
		unsigned short int Rotation;
		unsigned short int Type;
		bool Flags[7];
		bool IsValid;
		short int ai[8];
		Object* target;
};

struct Chunk{
	int Position[2];
	Wall walls[1024];
	Sector sectors[512];
	Object objects[4096];
	bool Doors[4];
	unsigned short int Tags[4096];
	Item items[512]; //Items ground objects contain pointers to the item
};

void LoadChunk(std::string save, int x, int y, Chunk* dest)
{
    
}
void SaveChunk(std::string save, int x, int y, Chunk* data)
{
    
}
void LoadAttr(char* save, Player* player, GameVars* gamevars);
void SaveAttr(char* save, Player* player, GameVars* gamevars);
