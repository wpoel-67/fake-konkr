#include "village.h"

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

extern std::shared_ptr<Gui> gui;

Village::Village() {}

Village::~Village() {
    gui->remove(image);
}

void Village::setPower(uint power) {
    this->power = power;
}

void Village::setMoney(uint money) {
    this->money = money;
}

void Village::setImage(std::shared_ptr<GuiImage> image) {
    this->image = image;
}

void Village::setCoord(int x, int y) {
    image->setPosition(x, y);
}

uint Village::getPower() const {
    return power;
}

uint Village::getMoney() const {
    return money;
}

std::shared_ptr<GuiImage> Village::getImage() const {
    return image;
}
