#include "tile.h"

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

extern std::shared_ptr<Gui> gui;

Tile::Tile() {}

Tile::~Tile() {
    gui->remove(hexagon);
}

void Tile::setType(TileType type) {
    this->type = type;
    if(type == TileType::RED) {
        if(isConnected) {
            hexagon->setColor(255, 0, 0);
        } else {
            hexagon->setColor(128, 0, 0);
        }
    } else if(type == TileType::BLUE) {
        if(isConnected) {
            hexagon->setColor(0, 0, 255);
        } else {
            hexagon->setColor(0, 0, 128);
        }
    } else {
        hexagon->setColor(128, 128, 128);
    }
}

void Tile::setHexagon(std::shared_ptr<GuiHexagon> hexagon) {
    this->hexagon = hexagon;
}

void Tile::setVillage(std::shared_ptr<Village> village) {
    this->village = village;
    village->setCoord(hexagon->getX(), hexagon->getY());
}

void Tile::setHasVillage(bool hasVillage) {
    this->hasVillage = hasVillage;
    if(!hasVillage && village)
        village = nullptr;
}

void Tile::setHasUnit(bool hasUnit) {
    this->hasUnit = hasUnit;
    if(!hasUnit && unit)
        unit = nullptr;
}

void Tile::setUnit(std::shared_ptr<Unit> unit) {
    if(unit == nullptr) {
        std::cerr << "Error: do not assign nullptr to setUnit" << std::endl;
        return;
    }
    this->unit = unit;
    unit->setCoord(hexagon->getX(), hexagon->getY());
}

void Tile::setConnected(bool isConnected) {
    this->isConnected = isConnected;
    setType(type);
}

bool Tile::getHasUnit() const {
    return hasUnit;
}

TileType Tile::getType() const {
    return type;
}

bool Tile::getHasVillage() const {
    return hasVillage;
}

bool Tile::getIsConnected() const {
    return isConnected;
}

std::shared_ptr<GuiHexagon> Tile::getHexagon() const {
    return hexagon;
}

std::shared_ptr<Village> Tile::getVillage() const {
    return village;
}

std::shared_ptr<Unit> Tile::getUnit() const {
    return unit;
}