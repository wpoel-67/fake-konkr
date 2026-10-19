#include "gui.h"
#include "guiButton.h"
#include "transitions.h"
#include "guiImage.h"

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

void switchToMenu(std::shared_ptr<Graphics> window ,std::shared_ptr<Gui> gui) {
    gui->clear();
    auto playButton = std::make_shared<GuiButton>(window, kWidth / 2, kHeight / 3, 400, 100, "Play");
    playButton->setColor(255, 255, 255);
    playButton->setHoverColor(200, 200, 200);
    playButton->setOnClick([window, gui]() {
        switchToPlay(window, gui);
    });
    gui->add(playButton);
    
    auto quitButton = std::make_shared<GuiButton>(window, kWidth / 2, 2 * kHeight / 3, 400, 100, "Quit");
    quitButton->setColor(255, 255, 255);
    quitButton->setHoverColor(255, 0, 0);
    quitButton->setOnClick([window, gui]() {
        exit(EXIT_SUCCESS);
    });
    gui->add(quitButton);
}