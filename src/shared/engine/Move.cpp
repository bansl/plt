#include "../engine.h"
#include <state.h>

#include <iostream>
#include <unistd.h>

using namespace engine;
using namespace state;
using namespace std;

bool Move::moveAction(state::Turn& turn){
    if (character.getStatus()==Available){
        Entity tilecheck{};
        cout << "is dest Tile free: " << std::boolalpha << tilecheck.isFree(turn,newPosition) << endl ;
        cout << "is dest Tile crossable: " << std::boolalpha << tilecheck.isCrossable(turn.getMap()[newPosition.getX()][newPosition.getY()]) << endl ;
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
        vector<Position> pathToDest={currentPosition};
        bool firstpos=true;
        while(pathToDest.size()<10){
            currentPosition.setPos(pathToDest.back().getX()+1,pathToDest.back().getY()  ), neighbors.push_back(currentPosition);
            currentPosition.setPos(pathToDest.back().getX()-1,pathToDest.back().getY()  ), neighbors.push_back(currentPosition);
            currentPosition.setPos(pathToDest.back().getX()  ,pathToDest.back().getY()+1), neighbors.push_back(currentPosition);
            currentPosition.setPos(pathToDest.back().getX()  ,pathToDest.back().getY()-1), neighbors.push_back(currentPosition);
            firstpos=true;
            while(neighbors.empty()==false){
                currentPosition.setPos(neighbors.back().getX(),neighbors.back().getY());
                cout << "------" << endl ;
                cout << "is dest Tile free: " << std::boolalpha << tilecheck.isFree(turn,currentPosition) << endl ;
                cout << "is dest Tile crossable: " << std::boolalpha << tilecheck.isCrossable(turn.getMap()[currentPosition.getX()][currentPosition.getY()]) << endl ;
                cout << "posX:" << currentPosition.getX() << endl ;
                cout << "posY:" << currentPosition.getY() << endl ;
                if(tilecheck.isCrossable(turn.getMap()[currentPosition.getX()][currentPosition.getY()]) && tilecheck.isFree(turn,currentPosition)){
                    if(firstpos){
                        pathToDest.push_back(currentPosition);
                        cout << "path: " << pathToDest.back().getX() << " | " << pathToDest.back().getY() << endl ;
                        firstpos=false;
                    }
                    else if (currentPosition.distanceBetween(currentPosition,newPosition)<currentPosition.distanceBetween(pathToDest[0],newPosition)){
                        pathToDest.pop_back();
                        pathToDest.push_back(currentPosition);
                        cout << "path: " << pathToDest.back().getX() << " | " << pathToDest.back().getY() << endl ;
                    }
                    else{
                        cout << "kept last path " << endl;
                    }
                }
                cout << "remove last" << endl;
                neighbors.pop_back();

                if(currentPosition.distanceBetween(pathToDest.back(),newPosition)==0){
                    cout << "final path: ";
                    for (size_t i = 0; i < pathToDest.size(); i++)
                    {
                        
                        cout << pathToDest[i].getX() << "|" << pathToDest[i].getY() << " -- ";
                    }
                    cout << "path found!" << endl;
                    return true;
                }
            } 
        }  
        cout << "couldn't find path within 10 moves..." << endl;  
        return false;
    }
    return false; 
}

Move::Move (state::Character& targetCharacter, state::Position& destination):character(targetCharacter),newPosition(destination){
    commandType= Movecmd;
}