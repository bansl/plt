#include "../state.h"

using namespace state; 
using namespace std;

void Cursor::cursorMove (state::Position dest){
    position.setX(dest.getX());
    position.setY(dest.getY());

}