#include <guiImage.h>

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

GuiImage::GuiImage(std::shared_ptr<Graphics> graphics, int x, int y) 
    : GuiElement(graphics, x, y), radius(10) {}

GuiImage::~GuiImage() {}

void GuiImage::setPath(std::string path) {
    this->path = std::move(path);
}

void GuiImage::setSize(int radius) {
    this->radius = radius;
}

void GuiImage::draw() {
    graphics->drawImage(path, x, y, radius);
}