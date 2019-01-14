#pragma once
/**
 * We're going to over-zealously include the entirety of SDL so we don't
 * have to deal with the different ways the file can be included or installed
 * on different systems. Since we need to call SDL_Init anyway there's no actual
 * penalty in compilation speeds.
 */
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
