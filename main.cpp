#include "init.hpp"
#include "init_text.hpp"
#include <iostream>

int main(int argc, char* args[]) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    // Инициализация SDL
    if (!InitSDL(&window, &renderer)) {
        std::cerr << "Failed to initialize SDL!" << std::endl;
        return -1;
    }

    // Инициализируем шрифт
    TTF_Font* font = nullptr;
    if (!InitFont(&font, "./dos2000.ttf", 24)) {
        CloseSDL(window, renderer);
        return -1;
    }

    // Запуск основного цикла
    RunMainLoop(window, renderer, font);

    // Завершение работы и освобождение ресурсов
    CloseSDL(window, renderer);

    return 0;
}
