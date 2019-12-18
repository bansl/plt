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
		imagePath.push_back("res/maptile2x129.png");
	}

	else if (type==CharaSpritesheet){
		sizeX=129; //TBD
		sizeY=155; //TBD
		margin=12; //TBD
		imagePath.push_back("res/char1.png");
		imagePath.push_back("res/char2.png");

	}
	else if (type==CursorSprite){
		sizeX=129;
		sizeY=129;
		margin=0;
		imagePath.push_back("res/cursor.png");
	}
	else if (type==WindowSprite){
		sizeX=96;
		sizeY=96;
		margin=0;
		imagePath.push_back("res/windowsprites.png");
	}
}

const vector<std::string> TileSet::getImagePath (){
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

void TileSet::setImagePath(std::vector<std::string> imagePath){
	this->imagePath=imagePath;
}
