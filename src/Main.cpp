#include <iostream>

#include "./Constants.h"
#include "./Game.h"

int main(int argc, char* args[]){
    Game *game = new Game();

    game->initialize(WINDOW_WIDTH, WINDOW_HEIGHT);

    while(game->isRunning()){
        game->processInput();
        game->update();
        game->render();
    }

    game->destroy();

    return 0;
}
