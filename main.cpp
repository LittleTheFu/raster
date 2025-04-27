#define SDL_MAIN_HANDLED

#include "config.h"
#include "SdlApp.h"

int main(int argc, char* argv[]) {
    SdlApp app("My Rasterizer", SCREEN_WIDTH, SCREEN_HEIGHT);

    while (app.isRunning()) {
        app.handleEvents();
        app.render();
        app.updateFPS();
    }

    return 0;
}