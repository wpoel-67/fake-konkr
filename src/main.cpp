#include "graphics.h"
#include "guiButton.h"
#include "guiHexagon.h"
#include "gui.h"
#include "grid.h"
#include "transitions.h"
#include <iostream>

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

std::shared_ptr<Grid> grid;
std::shared_ptr<Gui> gui;
std::shared_ptr<Graphics> window;

int main(int argc, char* argv[]) {
    window = std::make_shared<Graphics>();
    window->init("Konkr", kWidth, kHeight);
    gui = std::make_shared<Gui>(window, kWidth, kHeight);
    gui->setBgColor(50, 125, 160);    
    switchToMenu(window, gui);
    SDL_Event event;
    bool running = true;

    while(running) {
        bool needs_redraw = false;

        while(window->pollEvent(event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            } else if(event.type == SDL_MOUSEBUTTONDOWN) {
                gui->treatClick(event.button.x, event.button.y);
                needs_redraw = true;
            } else if(event.type == SDL_MOUSEMOTION) {
                gui->treatHover(event.motion.x, event.motion.y);
                gui->treatDrag(event.motion.x, event.motion.y);
                needs_redraw = true;
            }
        }

        if(needs_redraw) {
            gui->update();
        }

        window->delay(1);
    }

    return EXIT_SUCCESS;
}
