#include "gui.h"
#include "guiButton.h"
#include "transitions.h"
#include "guiImage.h"


/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

void switchToWinnerScreen(std::shared_ptr<Graphics> window ,std::shared_ptr<Gui> gui) {
    gui->clear();
    auto winner_button = std::make_shared<GuiButton>(window, kWidth / 2, kHeight / 3, 400, 100, "Victory");
    auto main_menu_button = std::make_shared<GuiButton>(window, kWidth / 2, kHeight / 2, 400, 100, "Main menu");
    winner_button->setColor(243, 227, 214);
    winner_button->setEnabled(false);
    main_menu_button->setColor(255, 255, 255);
    main_menu_button->setHoverColor(200, 200, 200);
    main_menu_button->setOnClick([window, gui]() {
        switchToMenu(window, gui);
    });
    gui->add(winner_button);
    gui->add(main_menu_button);
}