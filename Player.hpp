#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SDL2/SDL.h>

class Player{
    public:
        Player(int x, int y, int width, int height, SDL_Color color);

        // Оновлення положення гравця
        void HandlePlayerEvent(SDL_Event& e);
        void PlayerMove(int window_width, int window_height);
        
        // Рендеринг гравця
        void PlayerRender(SDL_Renderer* renderer);

    private:
        int posX, posY; // Положення гравця
        int width, height; // Розміри гравця
        float velX, velY; // Швидкість руху
        float playerSpeed;
        SDL_Color playerColor; // Колір гравця
};

#endif