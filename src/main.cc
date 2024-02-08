#include <cstdio>
#include <cmath>
#include <math.h>
#include "arguments.h"
#include "window.h"
#include "map.h"

iVec2 playerPosition = {0,0};
f32 playerAngle = 0;

void printUsage(char *executablePath) {
  printf("Usage: %s [-h]\n", executablePath);
  printf(" -> -h : Displays this information.\n");
}

void renderScene(Window *window) {
  Line testLine = {
    .a = iVec2{ 100, 100 },
    .b = iVec2{ 200, 200 },
    .z = 0,
    .h = 100,
    .isWall = true
  };

  window->DrawLine(testLine.a.x, testLine.a.y, testLine.b.x, testLine.b.y, COLOUR(0xff, 0, 0));

  fVec2 aLocalPos = { 
    (testLine.a.x - playerPosition.x) * sin(playerAngle), 
    (testLine.a.y - playerPosition.y) * cos(playerAngle)
  };

  fVec2 bLocalPos = {
    (testLine.b.x - playerPosition.x) * sin(playerAngle),
    (testLine.b.y - playerPosition.y) * cos(playerAngle)
  };

  window->DrawLine((int)aLocalPos.x, (int)aLocalPos.y, (int)bLocalPos.x, (int)bLocalPos.y, COLOUR(0, 0xff, 0));

  f32 aDepth = sqrtf(aLocalPos.x * aLocalPos.x + aLocalPos.y * aLocalPos.y);
  f32 bDepth = sqrtf(bLocalPos.x * bLocalPos.x + bLocalPos.y * bLocalPos.y);

  fVec2 aScreenPos {
    (aLocalPos.x / aDepth) + (float)window->width / 2,
    (testLine.z / aDepth) + (float)window->height / 2,
  };

  fVec2 bScreenPos {
    (bLocalPos.x / bDepth) + (float)window->width / 2,
    (testLine.z / bDepth) + (float)window->height / 2,
  };

  printf("(%f, %f)  (%f, %f)\n", aScreenPos.x, aScreenPos.y, bScreenPos.x, bScreenPos.y);

  window->DrawLine((int)aScreenPos.x, (int)aScreenPos.y, (int)bScreenPos.x, (int)bScreenPos.y, COLOUR(0, 0, 0xff));
}

int main(int argc, char **argv) {
  std::vector<ArgumentTemplate> parameters = {
    ArgumentTemplate{ARG_IMPLIED | ARG_OPTIONAL, "-h", "help"},
  };

  ArgumentParser *argumentParser = new ArgumentParser(argc, argv, parameters);
  Window *window = new Window(640, 480, "Hello, World!");

  long double frame = 0;

  std::vector<Argument> args;
  bool parseSuccess = argumentParser->parseArguments(args);

  if(!parseSuccess) {
    printUsage(argv[0]);
    goto cleanup;
  }

  if(argumentParser->argumentExists(args, "help")) {
    printUsage(argv[0]);
    goto cleanup;
  }

  while(window->isRunning) {
    window->BeginFrame();

    renderScene(window);

    playerAngle = (float)frame / 60.0f;

    window->EndFrame();
    window->Clear(COLOUR(0, 0, 0));
    frame += 1;
  }

cleanup:
  delete argumentParser;
  delete window;
  return 0;
}
