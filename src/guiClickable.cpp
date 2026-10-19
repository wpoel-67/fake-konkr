#include "guiClickable.h"

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

GuiClickable::GuiClickable(std::shared_ptr<Graphics> graphics, int x, int y)
    : GuiElement(graphics, x, y) {
        is_clickable = true;
    }

GuiClickable::~GuiClickable() {}

void GuiClickable::setEnabled(bool enabled) {
    this->enabled = enabled;
}