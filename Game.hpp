#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "TextManager.hpp"

enum GameMode {
    PLAYER_CONTROL,
    TEXT_INPUT
};

class Game{
    public:
        Game();
        ~Game();
        bool Init(const std::string& title, int width, int height);
        void Run();
        void CloseSDL(SDL_Window* window, SDL_Renderer* renderer) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }


    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        TextManager* textManager;
        bool running;

};

#endif 