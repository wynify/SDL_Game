#include "Player.hpp"

Player::Player(int x, int y, int w, int h, SDL_Color color)
    : posX(x), posY(y), width(w), height(h), velX(0.0), velY(0.0), playerColor(color), playerSpeed(1.0){}

void Player::HandlePlayerEvent(SDL_Event& e) {
    // Обробка натискань клавіш
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: velY -= 0.5; break;
            case SDLK_DOWN: velY += 0.5; break;
            case SDLK_LEFT: velX -= 0.5; break;
            case SDLK_RIGHT: velX += 0.5; break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: velY += 0.5; break;
            case SDLK_DOWN: velY -= 0.5; break;
            case SDLK_LEFT: velX += 0.5; break;
            case SDLK_RIGHT: velX -= 0.5; break;
        }
    }
}

void Player::PlayerMove(int window_width, int window_height) {
    // Оновлюємо позицію гравця залежно від напрямку руху
    posX += velX;
    posY += velY;

    // Обмеження руху по осі X
    if (posX < 0) {
        posX = 0; // Ліва межа
    } else if (posX + width > window_width) {
        posX = window_width - width; // Права межа
    }

    // Обмеження руху по осі Y
    if (posY < 0) {
        posY = 0; // Верхня межа
    } else if (posY + height > window_height) {
        posY = window_height - height; // Нижня межа
    }
}


void Player::PlayerRender(SDL_Renderer* renderer) {
    // Рендеринг гравця
    SDL_Rect fillRect = { posX, posY, width, height };
    SDL_SetRenderDrawColor(renderer, playerColor.r, playerColor.g, playerColor.b, playerColor.a);
    SDL_RenderFillRect(renderer, &fillRect);
}
