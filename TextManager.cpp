#include "TextManager.hpp"

TextManager::TextManager(SDL_Renderer* renderer) : renderer(renderer), font(nullptr) {}

TextManager::~TextManager() {
    if (font) {
        TTF_CloseFont(font);
    }
}

bool TextManager::InitFont(const std::string& path, int fontSize){
    if(TTF_Init() == -1){
        std::cerr << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << std::endl;
        return false;        
    }

    font = TTF_OpenFont(path.c_str(), fontSize);
    if (font == nullptr) {
        std::cerr << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }
    
    return true;   
}

void TextManager::HandleInput(SDL_Event& event) {
    if (event.type == SDL_TEXTINPUT) {
        userInput += event.text.text; // Добавляем введённый символ
    }
    else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_BACKSPACE && !userInput.empty()) {
            userInput.pop_back(); // Удаляем последний символ
        }
        else if (event.key.keysym.sym == SDLK_RETURN) {
            // Обрабатываем ввод текста (например, отображаем его на экране)
            PrintText(userInput, {255, 255, 255, 255}, 20, 20); // Отобразите текст
            userInput.clear(); // Очищаем буфер после ввода
        }
    }
}

void TextManager::InputText(SDL_Color color, int x, int y) {
    std::cout << "Введите текст: ";
    std::getline(std::cin, userInput);
    
    // Убедимся, что введенный текст не пустой
    if (userInput.empty()) {
        std::cout << "Вы не ввели текст!" << std::endl;
        return; // Если текст пустой или состоит только из пробелов, ничего не делаем
    }

    PrintText(userInput, color, x, y);
}

// TextManager.cpp
const std::string& TextManager::GetUserInput() const {
    return userInput; // Возвращаем текущий текст
}

void TextManager::PrintText(const std::string& text, SDL_Color color, int x, int y) {
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (textSurface == nullptr) {
        std::cerr << "Failed to create text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == nullptr) {
        std::cerr << "Failed to create texture from surface! SDL Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}