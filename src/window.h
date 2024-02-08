#pragma once

#include <SDL2/SDL.h>
#include <cstdint>
#include <string>

#define COLOUR(r, g, b) ((uint32_t)(r)<<24) + ((uint32_t)(g)<<16) + ((uint32_t)b<<8) + 0xff

class Window {
  private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;

  public:
    uint32_t* pixels;
    uint32_t width;
    uint32_t height;
    std::string caption;

    bool isRunning;

    Window(uint32_t width, uint32_t height, std::string caption);
    ~Window();

    void BeginFrame();
    void EndFrame();

    void SetPixel(uint32_t x, uint32_t y, uint32_t c);
    void Clear(uint32_t c);
    void FillRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t c);
    void DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t c);
};
