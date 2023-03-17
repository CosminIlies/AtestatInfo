#include <GL/glew.h>
#include <iostream>
#include "Game.h"

int main(int argc, char** argv) {


    Game game = Game(1280, 720, "Grafica C++");
    game.Start();

}