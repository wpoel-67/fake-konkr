#include "guiElement.h"

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

GuiElement::GuiElement(std::shared_ptr<Graphics> graphics, int x, int y)
    : graphics(graphics), x(x), y(y), is_clickable(false) {}

GuiElement::~GuiElement() {}

bool GuiElement::isClickable() const {
    return is_clickable;
}

void GuiElement::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}

int GuiElement::getX() const {
    return x;
}

int GuiElement::getY() const {
    return y;
}
