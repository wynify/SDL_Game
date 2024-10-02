// init.cpp
#include "init.hpp"
#include "init_text.hpp"
#include <iostream>

bool InitSDL(SDL_Window** window, SDL_Renderer** renderer) {
    // Иннициализация SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Иннициализация SDL_Text
    if (TTF_Init() == -1) {
    std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
    return false;
    }

    // Create a window
    *window = SDL_CreateWindow(
        "SDL Window",                // Window title
        SDL_WINDOWPOS_UNDEFINED,     // Initial x position
        SDL_WINDOWPOS_UNDEFINED,     // Initial y position
        800,                         // Width in pixels
        600,                         // Height in pixels
        SDL_WINDOW_SHOWN             // Flags (visible by default)
    );

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

    if (*window == nullptr || *renderer == nullptr) {
        std::cerr << "Failed to create window or renderer! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void RunMainLoop(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font) {
    bool quit = false;
    SDL_Event e;
    SDL_Color color = {255, 255, 255};  // Белый цвет текста

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Очищаем экран
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Черный фон
        SDL_RenderClear(renderer);

        // Выводим текст через PrintText
        PrintText(renderer, font, "Hello, SDL!", color, 100, 100);

        // Обновляем экран
        SDL_RenderPresent(renderer);
    }
    CloseFont(font);
    TTF_Quit();
}

void CloseSDL(SDL_Window* window, SDL_Renderer* renderer) {
    CloseSDL(window, renderer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
