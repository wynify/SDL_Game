// init.hpp
#ifndef INIT_HPP
#define INIT_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

bool InitSDL(SDL_Window** window, SDL_Renderer** renderer);
void CloseSDL(SDL_Window* window, SDL_Renderer* renderer);
void RunMainLoop(SDL_Window* window, SDL_Renderer* renderer, TTF_Font* font);   

#endif // INIT_HPP
