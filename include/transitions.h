#ifndef TRANSITIONS_H
#define TRANSITIONS_H

#include "gui.h"

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

/**
 * @brief Transitions to the main menu.
 * 
 * @param window Graphics window to manipulate.
 * @param gui GUI to manipulate.
 */
void switchToMenu(std::shared_ptr<Graphics> window, std::shared_ptr<Gui> gui);
/**
 * @brief Transitions to the game scene.
 * 
 * @param window Graphics window to manipulate.
 * @param gui GUI to manipulate.
 */
void switchToPlay(std::shared_ptr<Graphics> window, std::shared_ptr<Gui> gui);
/**
 * @brief Transitions to the victory screen.
 * 
 * @param window Graphics window to manipulate.
 * @param gui GUI to manipulate.
 */
void switchToWinnerScreen(std::shared_ptr<Graphics> window, std::shared_ptr<Gui> gui);


#endif // TRANSITIONS_H