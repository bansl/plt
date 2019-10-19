#include "../render.h"
#include <iostream>

using namespace std;
using namespace render;

TileSet::TileSet(TileSetType id){
	type=id;

	if (type == Maptile){
		sizeX=50;
		sizeY=70;
		margin=17;
		imagePath="res/maptiles25.png";	
	}
	
	else if (type==CharaSpritesheet){
		sizeX=16; //TBD
		sizeY=16; //TBD
		margin=0; //TBD
		imagePath="res/char1.png";
	}
}

const std::string TileSet::getImagePath (){
	return imagePath;
}

int TileSet::getXsize(){
        return sizeX;
}

int TileSet::getYsize(){
        return sizeY;
}

int TileSet::getMargin(){
        return margin;
}