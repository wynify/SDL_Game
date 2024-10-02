#include "Game.hpp"

int main() {
    Game game;
    if (game.Init("SDL Text Input Example", 640, 480)) {
        game.Run();
    }
    return 0;
}