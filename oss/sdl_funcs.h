#ifndef SDL_FUNCS_H
#define SDL_FUNCS_H
#include <iostream> // load basic input/output
#include <SDL2/SDL.h> // load simple directmedia layer 2
#include <SDL2/SDL_image.h> // load sdl2 image library

void logSDLError(std::ostream&, const std::string&);
SDL_Texture* loadTexture(const std::string, SDL_Renderer);
void renderTexture(SDL_Texture, SDL_Renderer, int, int, int, int);
void renderTexture(SDL_Texture, SDL_Renderer, int, int);



#endif


