#include "../render.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <SFML/Graphics/Image.hpp>



using namespace std;
using namespace render;
using namespace state;

void Window::renderWindow (render::WindowType windowType){
    if (windowType=infobanner)
    {
        /* code */
    }
    else if (windowType=actionselect)
    {
        /* code */
    }
    else
    {
        /* code */
    }
    
}

void Window::renderCursor (){

}
void Window::moveCursorUp (){
    if (selectpos>=0) selectpos--;
}
void Window::moveCursorDown (){
    if (selectpos<4) selectpos--;
}