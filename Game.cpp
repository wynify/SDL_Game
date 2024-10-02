#include "Game.hpp"
#include "TextManager.hpp"
#include "Player.hpp"

Game::Game() : window(nullptr), renderer(nullptr), textManager(nullptr), running(true){}
Player player(100, 100, 50, 50, {255, 0, 0, 255});
GameMode currentMode = PLAYER_CONTROL;

Game::~Game() {
    delete textManager;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();
}

bool Game::Init(const std::string& title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    textManager = new TextManager(renderer);
    if (!textManager->InitFont("dos2000.ttf", 48)) {
        return false;
    }

    SDL_StartTextInput(); // Ініціалізуємо текстовий ввід
    return true;
}

void Game::Run() {
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            // Перемикання режимів за допомогою клавіші TAB
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_TAB) {
                if (currentMode == PLAYER_CONTROL) {
                    currentMode = TEXT_INPUT;
                } else {
                    currentMode = PLAYER_CONTROL;
                }
            }

            // Обробка подій залежно від поточного режиму
            if (currentMode == PLAYER_CONTROL) {
                // Режим керування гравцем
                if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
                    player.HandlePlayerEvent(event); // Обробка подій гравця
                }
            } else if (currentMode == TEXT_INPUT) {
                // Режим введення тексту
                if (event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN) {
                    textManager->HandleInput(event); // Обробка введення тексту
                }
            }
        }

        // Очищення екрану
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Рух гравця, якщо в режимі гравця
        if (currentMode == PLAYER_CONTROL) {
            player.PlayerMove(640, 480);
        }

        // Рендеринг гравця
        player.PlayerRender(renderer);

        // Виведення тексту
        textManager->PrintText(textManager->GetUserInput(), {255, 255, 255, 255}, 100, 100);

        // Оновлення екрану
        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput(); // Вимикаємо текстовий ввід після завершення гри
}

void CloseSDL(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}