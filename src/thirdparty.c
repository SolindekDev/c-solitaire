#include <core.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <thirdparty.h>

static bool __init_thirdparty = false;

#define SDL_IMG_FLAGS (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP)

unsigned char initialize_thirdparty() 
{
  int _sdl_base = SDL_Init(SDL_INIT_EVERYTHING);
  if (_sdl_base != 0) {
    printf("error: SDL failed to initialize.\n");
    printf("sdl: %s\n", SDL_GetError());
    return (unsigned char)EXIT_FAILURE;
  }

  int _sdl_ttf = TTF_Init();
  if (_sdl_ttf != 0) {
    printf("error: SDL ttf failed to initialize.\n");
    printf("sdl: %s\n", SDL_GetError());
    return (unsigned char)EXIT_FAILURE;
  }

  int _sdl_img = IMG_Init(SDL_IMG_FLAGS);
  if (_sdl_img != SDL_IMG_FLAGS) {
    printf("error: SDL img failed to initialize.\n");
    printf("sdl: %s\n", SDL_GetError());
    return (unsigned char)EXIT_FAILURE;
  }

  __init_thirdparty = true;
  return (unsigned char)EXIT_SUCCESS;
}

unsigned char quit_thirdparty() 
{
  SDL_Quit();
  TTF_Quit();
  IMG_Quit();

  return (unsigned char)EXIT_SUCCESS;
}

bool is_init_thirdparty() 
{ 
  return __init_thirdparty; 
}