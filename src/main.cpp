#include <iostream>

#include "application.h"

int main() {

    Application game;

    if(game.init()){
        spdlog::info("starting update loop");
        game.update();
    }



    return 0;
}
