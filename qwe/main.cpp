#include <GL/glew.h>
#include <iostream>
#include "Game.h"

int main(int argc, char** argv) {


    Game game = Game(800, 600, "Grafica C++");
    game.Start();

}