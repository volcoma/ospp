#pragma once
/**
 * We're going to over-zealously include the entirety of SDL so we don't
 * have to deal with the different ways the file can be included or installed
 * on different systems. Since we need to call SDL_Init anyway there's no actual
 * penalty in compilation speeds.
 */
#define SDL_MAIN_HANDLED
#if defined(__has_include)
#if __has_include(<SDL2/SDL.h>)
#include <SDL2/SDL.h>
#elif __has_include(<SDL/SDL.h>)
#include <SDL/SDL.h>
#elif __has_include(<SDL.h>)
#include <SDL.h>
#endif
#else
#include <SDL.h>
#endif

#if defined(__has_include)
#if __has_include(<SDL2/SDL_syswm.h>)
#include <SDL2/SDL_syswm.h>
#elif __has_include(<SDL/SDL_syswm.h>)
#include <SDL/SDL_syswm.h>
#elif __has_include(<SDL_syswm.h>)
#include <SDL_syswm.h>
#endif
#else
#include <SDL_syswm.h>
#endif
