#include "Game.hpp"
#include "TextManager.hpp"

Game::Game() : window(nullptr), renderer(nullptr), textManager(nullptr), running(true){}

Game::~Game(){
    delete textManager;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();
}

bool Game::Init(const std::string& title, int width, int height){
     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
        SDL_StartTextInput(); // Инициализируем текстовый ввод
        return textManager->InitFont("dos2000.ttf", 24);
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return false;
    }

    textManager = new TextManager(renderer);
    return textManager->InitFont("dos2000.ttf", 24); // Укажите правильный путь к шрифту
}

void Game::Run() {
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            textManager->HandleInput(event); // Обрабатываем ввод текста
        }

        // Очищаем экран
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Отображаем текст, если нужно
        textManager->PrintText(textManager->GetUserInput(), {255, 255, 255, 255}, 100, 100);

        SDL_RenderPresent(renderer);
    }
}