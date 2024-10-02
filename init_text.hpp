#ifndef INIT_TEXT_H
#define INIT_TEXT_H

#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

bool InitFont(TTF_Font** font, const std::string& path, int fontSize);  // Функция загрузки шрифта
void InitText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int x, int y);
void InputText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int x, int y);
void PrintText(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color, int x, int y);
void CloseFont(TTF_Font* font);  // Для освобождения памяти шрифта

#endif
