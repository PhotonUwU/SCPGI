#include <iostream>
#include "globals.h"
#include "primary.hpp"

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
	Wall walls[1024];
	Sector sectors[512];
	Object objects[4096];
	bool Doors[4];
	unsigned short int Tags[4096];
	Item items[512]; //Items ground objects contain pointers to the item
};

void LoadChunk(char* save, int x, int y, Chunk* dest);
void SaveChunk(char* save, int x, int y, Chunk* data);
void LoadAttr(char* save);
void SaveAttr(char* save);
