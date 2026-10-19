#include "guiHexagon.h"

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

GuiHexagon::GuiHexagon(std::shared_ptr<Graphics> graphics, int x, int y, int radius) : GuiClickable(graphics, x, y), 
radius(radius), r(128), g(128), b(128), is_hovered(false) {}

GuiHexagon::~GuiHexagon() {}

void GuiHexagon::draw() {
    graphics->drawHexagonTexture(x, y, radius, r, g, b);
    if(is_highlighted) {
        graphics->drawHexagon(x, y, radius - 1, 255, 255, 0);
    }
    if(is_hovered) {
        graphics->drawHexagon(x, y, radius - 1, 255, 255, 255);
        graphics->drawHexagon(x, y, radius, 255, 255, 255);
        graphics->drawHexagon(x, y, radius + 1, 255, 255, 255);
    }
}

void GuiHexagon::onClick() {
    if(onClickAction) {
        onClickAction();
    }
}

void GuiHexagon::onHover() {
    if(onHoverAction) {
        onHoverAction();
    }
    graphics->setHandCursor();
    is_hovered = true;
}

void GuiHexagon::onLeave() {
    if(onLeaveAction) {
        onLeaveAction();
    }
    graphics->setArrowCursor();
    is_hovered = false;
}

bool GuiHexagon::isHit(int x, int y) {
    if(!enabled) {
        return false;
    }
    double r = (radius - 2) * sqrt(3) / 2; // rayon du cercle inscrit d'un hexagone r = (a * sqrt(3)) / 2
    return (x - this->x) * (x - this->x) + (y - this->y) * (y - this->y) <= r * r;
}

void GuiHexagon::setColor(uint8_t r, uint8_t g, uint8_t b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void GuiHexagon::setOnClick(std::function<void()> onClickAction) {
    this->onClickAction = onClickAction;
}

void GuiHexagon::setOnHover(std::function<void()> onHoverAction) {
    this->onHoverAction = onHoverAction;
}

void GuiHexagon::setOnLeave(std::function<void()> onLeaveAction) {
    this->onLeaveAction = onLeaveAction;
}

void GuiHexagon::setHighlighted(bool highlighted) {
    this->is_highlighted = highlighted;
}