#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "TextManager.hpp"

class Game{
    public:
        Game();
        ~Game();
        bool Init(const std::string& title, int width, int height);
        void Run();

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        TextManager* textManager;
        bool running;

};

#endif 