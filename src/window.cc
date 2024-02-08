#include "window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cstddef>

#include <iostream>
#include <math.h>
#include <ostream>
#include <cstdio>

Window::Window(uint32_t width, uint32_t height, std::string caption) {
  SDL_Init(SDL_INIT_EVERYTHING);

  this->width = width;
  this->height = height;
  this->caption = caption;

  this->pixels = new uint32_t[width * height];

  this->window = SDL_CreateWindow(caption.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
  this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
  this->surface = SDL_CreateRGBSurfaceWithFormatFrom(this->pixels, this->width, this->height, sizeof(uint32_t)*8, this->width * sizeof(uint32_t), SDL_PIXELFORMAT_RGBA8888);

  this->isRunning = true;
}

Window::~Window() {
  delete this->pixels;

  SDL_DestroyRenderer(this->renderer);
  SDL_DestroyWindow(this->window);

  SDL_Quit();
}

void Window::BeginFrame() {
  SDL_Event e;

  while( SDL_PollEvent(&e) ) {
    switch(e.type) {
      case SDL_QUIT:
        isRunning = false;
        break;
    }
  }
}

void Window::EndFrame() {
  SDL_LockSurface(this->surface);
  SDL_memcpy(this->surface->pixels, this->pixels, this->width * this->height * sizeof(uint32_t));
  SDL_UnlockSurface(this->surface);

  SDL_Texture* texture = SDL_CreateTextureFromSurface(this->renderer, surface);

  SDL_RenderCopy(this->renderer, texture, NULL, NULL);
  SDL_RenderPresent(this->renderer);

  SDL_DestroyTexture(texture);
}


void Window::SetPixel(uint32_t x, uint32_t y, uint32_t c) {
  if(x >= this->width || y >= this->height) return;

  this->pixels[y * this->width + x] = c;
}

void Window::Clear(uint32_t c) {
  this->FillRect(0, 0, this->width, this->height, c);
}

void Window::FillRect(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t c) {
  for(uint32_t y1 = 0; y1 < h; ++y1) {
    for(uint32_t x1 = 0; x1 < w; ++x1) {
      this->SetPixel(x+x1, y+y1, c);
    }
  }
}

#define ABS(x) ( (x>0)? x:(x*-1) )

void Window::DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t c) {
  int32_t dx = x2-x1;
  int32_t dy = y2-y1;

  uint32_t steps = 0;
  if(ABS(dx) > ABS(dy)) {
    steps = ABS(dx);
  } else {
    steps = ABS(dy);
  }

  float xinc = dx / (float)steps;
  float yinc = dy / (float)steps;

  float x = x1;
  float y = y1;

  for(uint32_t v = 0; v < steps; ++v) {
    this->SetPixel(x, y, c);

    x += xinc;
    y += yinc;
  }
}
