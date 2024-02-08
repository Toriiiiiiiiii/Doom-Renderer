#pragma once
#include <cstdint>

typedef int32_t i32;
typedef float f32;

typedef struct {
  f32 x, y;
} fVec2;

typedef struct {
  i32 x, y;
} iVec2;

typedef struct {
  iVec2 a;
  iVec2 b;

  i32 z;
  i32 h;

  bool isWall;
} Line;
