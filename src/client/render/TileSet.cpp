#include "../render.h"
#include <iostream>

using namespace std;
using namespace render;

TileSet::TileSet(TileSetType id){
	type=id;

	if (type == Maptile){
		sizeX=129;
		sizeY=129;
		margin=0;
		imagePath="res/maptile2x129.png";	
	}
	
	else if (type==CharaSpritesheet){
		sizeX=129; //TBD
		sizeY=155; //TBD
		margin=12; //TBD
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