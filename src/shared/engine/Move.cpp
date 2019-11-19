#include "../engine.h"
#include <state.h>

#include <iostream>
#include <unistd.h>

using namespace engine;
using namespace state;
using namespace std;

bool Move::validate (state::Turn& turn){
    if (character.getStatus()==Available){
        Entity tilecheck{};
        // cout << "is dest Tile free: " << std::boolalpha << tilecheck.isFree(turn,newPosition) << endl ;
        // cout << "is dest Tile crossable: " << std::boolalpha << tilecheck.isCrossable(turn.getMap()[newPosition.getX()][newPosition.getY()]) << endl ;
        if(tilecheck.isFree(turn,newPosition)==false){
            return false;
        }

        if(tilecheck.isCrossable(turn.getMap()[newPosition.getX()][newPosition.getY()])==false){
            return false;
        }

        if(newPosition.distanceBetween(newPosition,character.getPosition())>10){
            return false;
            // character.getPosition().setPos(newPosition.getX(),newPosition.getY());
        }

        //Find Path
        Position currentPosition(character.getPosition());
        vector<Position> neighbors;
        pathToDest={currentPosition};
        bool firstpos=true;
        while(pathToDest.size()<10){
            // cout << "CURRENT POS:" << pathToDest.back().getX() << " | " << pathToDest.back().getY() << endl ;
            currentPosition.setPos(pathToDest.back().getX()+1,pathToDest.back().getY()  ), neighbors.push_back(currentPosition);
            currentPosition.setPos(pathToDest.back().getX()-1,pathToDest.back().getY()  ), neighbors.push_back(currentPosition);
            currentPosition.setPos(pathToDest.back().getX()  ,pathToDest.back().getY()+1), neighbors.push_back(currentPosition);
            currentPosition.setPos(pathToDest.back().getX()  ,pathToDest.back().getY()-1), neighbors.push_back(currentPosition);
            firstpos=true;
            while(!neighbors.empty()){
                currentPosition.setPos(neighbors.back().getX(),neighbors.back().getY());
                // cout << "------" << endl ;
                // cout << "is dest Tile free: " << std::boolalpha << tilecheck.isFree(turn,currentPosition) <<  " | " << "is dest Tile crossable: " << std::boolalpha << tilecheck.isCrossable(turn.getMap()[currentPosition.getX()][currentPosition.getY()]) << endl ;
                // cout << "posX:" << currentPosition.getX() <<  " | " << "posY:" << currentPosition.getY() << endl ;
                bool newpos=true;
                for (size_t q = 0; q < pathToDest.size(); q++)
                  {
                      if((pathToDest[q].getX()==currentPosition.getX()) && (pathToDest[q].getY()==currentPosition.getY())) newpos=false;
                  }
                if(tilecheck.isCrossable(turn.getMap()[currentPosition.getX()][currentPosition.getY()]) && tilecheck.isFree(turn,currentPosition) && newpos){

                    if(firstpos){
                        pathToDest.push_back(currentPosition);
                        // cout << "--first path: " << pathToDest.back().getX() << " | " << pathToDest.back().getY() << endl ;
                        firstpos=false;
                    }
                    else if (currentPosition.distanceBetween(currentPosition,newPosition)<currentPosition.distanceBetween(pathToDest.back(),newPosition)){
                        pathToDest.pop_back();
                        pathToDest.push_back(currentPosition);
                        // cout << "--better path: " << pathToDest.back().getX() << " | " << pathToDest.back().getY() << endl ;
                    }
                    else{
                        // cout << "--kept last path " << endl;
                    }
                }
                // cout << "trying next neighbor" << endl;
                neighbors.pop_back();

                if(currentPosition.distanceBetween(pathToDest.back(),newPosition)==0){
                    // cout << "final path: ";
                    // for (size_t i = 0; i < pathToDest.size(); i++)
                    // {

                    //     cout << pathToDest[i].getX() << "|" << pathToDest[i].getY() << " -- ";
                    // }
                    // cout << "path found!" << endl;
                    character.setStatus(Moving);
                    return true;
                }
            }
            // cout << "MOVING TO NEXT TILE" << endl;
        }
        // for (size_t i = 0; i < pathToDest.size(); i++)
        //             {

        //                 cout << pathToDest[i].getX() << "|" << pathToDest[i].getY() << " -- ";
        //             }
        // cout << "couldn't find path within 10 moves..." << endl;
        return false;
    }
    return false;

}

bool Move::action(state::Turn& turn){
    // for (size_t i = 0; i < pathToDest.size(); i++)
    // {
    //     character.getPosition().setPos(pathToDest[i].getX(),pathToDest[i].getY());
    // }

    character.getPosition().setPos(newPosition.getX(),newPosition.getY());
    return true;
}

bool Move::finish(state::Turn& turn){
    character.setStatus(Used);
    return true;
}

Move::Move (state::Character& targetCharacter, state::Position& destination):character(targetCharacter),newPosition(destination){
    commandType= Movecmd;
}

state::Character& Move::getCharacter(){
  Character & addrCharacter = character;
  return addrCharacter;
}

std::vector<state::Position>& Move::getPathToDest(){
  std::vector<state::Position>& addrPath = pathToDest;
  return addrPath;
}
