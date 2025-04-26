#define SDL_MAIN_HANDLED
#include "SdlApp.h"

int main(int argc, char* argv[]) {
    SdlApp app("My Rasterizer", 800, 600);

    while (app.isRunning()) {
        app.handleEvents();
        app.render();
        app.updateFPS();
    }

    return 0;
}