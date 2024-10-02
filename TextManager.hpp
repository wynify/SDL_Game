#ifndef TEXT_MANGER_H
#define TEXT_MANGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

class TextManager {
public:
    TextManager(SDL_Renderer* renderer);
    ~TextManager();
    bool InitFont(const std::string& path, int fontSize);
    void HandleInput(SDL_Event& event); // Обработка ввода
    void InputText(SDL_Color color, int x, int y);
    void PrintText(const std::string& text, SDL_Color color, int x, int y);
    const std::string& GetUserInput() const; // Новый метод для получения текста

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    std::string userInput; // Буфер для ввода текста
};

#endif