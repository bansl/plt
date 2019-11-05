#include "../state.h"

using namespace state;
using namespace std;

int Level::getLevel (){
    return level;
}
void Level::levelUp (int experience){
    this->experience+=experience;
    while (experience >= (this->level)*(this->level))
    {
        this->level+=1;
    }
}
