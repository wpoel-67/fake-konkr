#include "unit.h"

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

extern std::shared_ptr<Gui> gui;

Unit::Unit() {}

Unit::~Unit() {
    gui->remove(image);
}

void Unit::setType(UnitType type) {
    this->type = type;
}

void Unit::setPower(uint power) {
    this->power = power;
}

void Unit::setImage(std::shared_ptr<GuiImage> image) {
    this->image = image;
}

void Unit::setHasMoved(bool hasMoved) {
    this->hasMoved = hasMoved;
}

UnitType Unit::getType() const {
    return type;
}

uint Unit::getPower() const {
    return power;
}

bool Unit::getHasMoved() const {
    return hasMoved;
}

void Unit::setCoord(int x, int y) {
    image->setPosition(x, y);
}

std::shared_ptr<GuiImage> Unit::getImage() const {
    return image;
}
