#include "gui.h"

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

Gui::Gui(std::shared_ptr<Graphics> graphics, int width, int height)
    : width(width), height(height), graphics(graphics), last_hovered(nullptr) {}

Gui::~Gui() {
    clear();
}

std::vector<std::shared_ptr<GuiElement>>::iterator Gui::begin() {
    return elements.begin();
}

std::vector<std::shared_ptr<GuiElement>>::iterator Gui::end() {
    return elements.end();
}

void Gui::add(std::shared_ptr<GuiElement> element, bool append) {
    if(append) {
        elements.push_back(element);
    } else {
        elements.insert(elements.begin(), element);
    }
}

void Gui::remove(int index) {
    elements.erase(elements.begin() + index);
}

void Gui::remove(std::shared_ptr<GuiElement> element) {
    auto it = std::find(elements.begin(), elements.end(), element);
    if(it != elements.end()) {
        elements.erase(it);
    }
}

void Gui::treatClick(int x, int y) {
    for(auto& element : elements) {
        if(element->isClickable()) {
            std::shared_ptr<GuiClickable> clickable = std::dynamic_pointer_cast<GuiClickable>(element);
            if(clickable->isHit(x, y)) {
                clickable->onClick();
                break;
            }
        }
    }
}

void Gui::treatHover(int x, int y) {
    for(auto& element : elements) {
        if(element->isClickable()) {
            auto* clickable = static_cast<GuiClickable*>(element.get());
            if(clickable->isHit(x, y)) {
                if(last_hovered.get() != clickable) {
                    if(last_hovered != nullptr) {
                        last_hovered->onLeave();
                    }
                    last_hovered = std::static_pointer_cast<GuiClickable>(element);
                    clickable->onHover();
                }
                return;
            }
        }
    }
    if(last_hovered != nullptr) {
        last_hovered->onLeave();
        last_hovered = nullptr;
    }
}

void Gui::treatDrag(int x, int y) {
    if(dragged_element) {
        dragged_element->setPosition(x + 50, y);
    }
}

void Gui::setDraggedElement(std::shared_ptr<GuiElement> element) {
    dragged_element = element;
}

void Gui::releaseDraggedElement() {
    dragged_element = nullptr;
}

void Gui::setBgColor(uint8_t r, uint8_t g, uint8_t b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void Gui::drawBackground() {
    graphics->drawRect(width / 2, height / 2, width, height, r, g, b);
}

void Gui::drawAll() {
    for(auto& element : elements) {
        element->draw();
    }
}

void Gui::update() {
    drawBackground();
    drawAll();
    graphics->update();
}

void Gui::clear() {
    elements.clear();
    graphics->clear();
    graphics->update();
}