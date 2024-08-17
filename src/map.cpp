#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <string>
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

void LoadChunk(std::string save, int x, int y, Chunk* dest) {
    std::string path;
    if (save == "DEBUG") {
        path = "Assets/DEBUG.sav";
    } else {
        path = "Data/" + save + ".sav";
    }

    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << path << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string section;
        iss >> section;

        if (section == "[Globals]") {
            // Load globals (e.g., doors and tags)
            for (int i = 0; i < 4; i++) {
                iss >> dest->Doors[i];
            }
            for (int i = 0; i < 512; i++) {
                iss >> dest->Tags[i];
            }
        } else if (section == "[Walls]") {
            int id;
            while (iss >> id && id < 1024) {
                Wall& wall = dest->walls[id];
                for (int i = 0; i < 4; i++) {
                    iss >> wall.Points[i];
                }
                iss >> wall.Texture >> wall.Sectors[0] >> wall.Sectors[1] >> wall.Portal >> wall.Function >> wall.Target;
            }
        } else if (section == "[Sectors]") {
            int id;
            while (iss >> id && id < 512) {
                Sector& sector = dest->sectors[id];
                sector.IsValid = true;  // Mark sector as valid since data is being loaded

                // Load wall IDs and assign pointers
                for (int i = 0; i < 16; i++) {
                    int wallID;
                    iss >> wallID;
                    if (wallID >= 0 && wallID < 1024) {
                        sector.walls[i] = &dest->walls[wallID];
                    } else {
                        sector.walls[i] = nullptr;
                    }
                }

                iss >> sector.FloorTexture >> sector.CeilTexture >> sector.FloorHeight >> sector.CeilHeight >> sector.Tag;
            }
        } else if (section == "[Objects]") {
            int id;
            while (iss >> id && id < 4096) {
                Object& obj = dest->objects[id];
                obj.IsValid = true;  // Mark object as valid since data is being loaded

                iss >> obj.Position[0] >> obj.Position[1] >> obj.Rotation >> obj.Type;
                for (int i = 0; i < 7; i++) {
                    iss >> obj.Flags[i];
                }
                for (int i = 0; i < 8; i++) {
                    iss >> obj.ai[i];
                }

                int targetID;
                iss >> targetID;
                if (targetID >= 0 && targetID < 4096) {
                    obj.target = &dest->objects[targetID];
                } else {
                    obj.target = nullptr;
                }
            }
        } else if (section == "[Items]") {
            int id;
            while (iss >> id && id < 512) {
                Item& item = dest->items[id];
                item.Name = "";
                iss >> item.Name >> item.Texture >> item.HoldTexture;
                for (int i = 0; i < 8; i++) {
                    iss >> item.Data[i];
                }
            }
        }
    }

    file.close();
}

void SaveChunk(std::string save, int x, int y, Chunk* data) {
    std::string path;
    if (save == "DEBUG") {
        path = "Assets/DEBUG.sav";
    } else {
        path = "Data/" + save + ".sav";
    }

    std::ofstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << path << std::endl;
        return;
    }

    // Save Globals
    file << "[Globals]\n";
    for (int i = 0; i < 4; i++) {
        file << data->Doors[i] << " ";
    }
    file << "\n";
    for (int i = 0; i < 512; i++) {
        file << data->Tags[i] << " ";
    }
    file << "\n";

    // Save Walls
    file << "[Walls]\n";
    for (int id = 0; id < 1024; id++) {
        Wall& wall = data->walls[id];
        file << id << " ";
        for (int i = 0; i < 4; i++) {
            file << wall.Points[i] << " ";
        }
        file << wall.Texture << " "
             << wall.Sectors[0] << " "
             << wall.Sectors[1] << " "
             << wall.Portal << " "
             << wall.Function << " "
             << wall.Target << "\n";
    }

    // Save Sectors
    file << "[Sectors]\n";
    for (int id = 0; id < 512; id++) {
        Sector& sector = data->sectors[id];
        if (sector.IsValid) {
            file << id << " ";
            for (int i = 0; i < 16; i++) {
                if (sector.walls[i] != nullptr) {
                    file << (sector.walls[i] - data->walls) << " ";  // Get wall ID by pointer difference
                } else {
                    file << "-1 ";  // No wall
                }
            }
            file << sector.FloorTexture << " "
                 << sector.CeilTexture << " "
                 << sector.FloorHeight << " "
                 << sector.CeilHeight << " "
                 << sector.Tag << "\n";
        }
    }

    // Save Objects
    file << "[Objects]\n";
    for (int id = 0; id < 4096; id++) {
        Object& obj = data->objects[id];
        if (obj.IsValid) {
            file << id << " "
                 << obj.Position[0] << " "
                 << obj.Position[1] << " "
                 << obj.Rotation << " "
                 << obj.Type << " ";
            for (int i = 0; i < 7; i++) {
                file << obj.Flags[i] << " ";
            }
            for (int i = 0; i < 8; i++) {
                file << obj.ai[i] << " ";
            }
            if (obj.target != nullptr) {
                file << (obj.target - data->objects) << "\n";  // Get target ID by pointer difference
            } else {
                file << "-1\n";  // No target
            }
        }
    }

    // Save Items
    file << "[Items]\n";
    for (int id = 0; id < 512; id++) {
        Item& item = data->items[id];
        if (!item.Name.empty()) {
            file << id << " " << item.Name << " "
                 << item.Texture << " "
                 << item.HoldTexture << " ";
            for (int i = 0; i < 8; i++) {
                file << item.Data[i] << " ";
            }
            file << "\n";
        }
    }

    file.close();
}
void LoadAttr(char* save, Player* player, GameVars* gamevars);
void SaveAttr(char* save, Player* player, GameVars* gamevars);
