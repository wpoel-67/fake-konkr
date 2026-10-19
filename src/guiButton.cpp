#include "guiButton.h"

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

GuiButton::GuiButton(std::shared_ptr<Graphics> graphics, int x, int y, int width, int height, std::string text)
    : GuiClickable(graphics, x, y), width(width), height(height),
    text(std::move(text)), r(255), g(255), b(255), font_size(24), r_text(0), g_text(0), b_text(0) {}

GuiButton::~GuiButton() {}

void GuiButton::draw() {
    TextSize ts = graphics->textSize(text, font_size);
    if(!is_hovered)
        graphics->drawRect(x, y, width, height, r, g, b);
    else
        graphics->drawRect(x, y, width, height, r_hover, g_hover, b_hover);
    graphics->drawLine(x - width / 2, y - height / 2, x + width / 2, y - height / 2, 0, 0, 0);
    graphics->drawLine(x - width / 2, y + height / 2, x + width / 2, y + height / 2, 0, 0, 0);
    graphics->drawLine(x - width / 2, y - height / 2, x - width / 2, y + height / 2, 0, 0, 0);
    graphics->drawLine(x + width / 2, y - height / 2, x + width / 2, y + height / 2, 0, 0, 0);
    graphics->drawText(x - ts.w / 2, y - ts.h / 2, text, r_text, g_text, b_text, font_size);
}

void GuiButton::onClick() {
    if(onClickAction) {
        onClickAction();
    }
}

void GuiButton::onHover() {
    if(onHoverAction) {
        onHoverAction();
    }
    is_hovered = true;
    graphics->setHandCursor();
}

void GuiButton::onLeave() {
    if(onLeaveAction) {
        onLeaveAction();
    }
    is_hovered = false;
    graphics->setArrowCursor();
}

bool GuiButton::isHit(int x, int y) {
    if(!enabled) {
        return false;
    }
    return x >= this->x - width / 2 && x <= this->x + width / 2 && y >= this->y - height / 2 && y <= this->y + height / 2;
}

void GuiButton::setColor(uint8_t r, uint8_t g, uint8_t b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void GuiButton::setText(std::string text) {
    this->text = text;
}

void GuiButton::setHoverColor(uint8_t r, uint8_t g, uint8_t b) {
    r_hover = r;
    g_hover = g;
    b_hover = b;
}

void GuiButton::setFontSize(uint fontSize) {
    this->font_size = fontSize;
}

void GuiButton::setTextColor(uint8_t r, uint8_t g, uint8_t b) {
    r_text = r;
    g_text = g;
    b_text = b;
}

void GuiButton::setOnClick(std::function<void()> onClickAction) {
    this->onClickAction = onClickAction;
}

void GuiButton::setOnHover(std::function<void()> onHoverAction) {
    this->onHoverAction = onHoverAction;
}

void GuiButton::setOnLeave(std::function<void()> onLeaveAction) {
    this->onLeaveAction = onLeaveAction;
}
