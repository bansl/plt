#include "../render.h"
#include <iostream>

using namespace std;
using namespace render;

TileSet::TileSet(TileSetID newId){
	id=newId;

	if (id == Maptile){
		sizeX=197;
		sizeY=280;
		imagePath="res/maptiles.png";	
	}
	
	else if (id==PERSONNAGETILESET){
		sizeX=16; //TBD
		sizeY=16; //TBD
		imagePath="res/char1.png";
	}
}

std::string  TileSet::getImageFile (){
	return imagePath;
}

