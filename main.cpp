#include "Game.hpp"

int main() {
    Game game;
    if (game.Init("SDL Text Input Example", 1000, 1000)) {
        game.Run();
    }
    return 0;
}