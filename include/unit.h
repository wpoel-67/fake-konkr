#ifndef UNIT_H
#define UNIT_H

#include "guiImage.h"
#include "gui.h"
#include <iostream>

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */


enum class UnitType {
    BANDIT,
    VILLAGER,
    SPIKER,
    KNIGHT,
    HERO
};

class Unit {
private:
    UnitType type;
    uint power;
    std::shared_ptr<GuiImage> image;
    bool hasMoved = false;

public:
    Unit();
    Unit(const Unit&) = default;
    ~Unit();
    /**
     * @brief Sets the unit type.
     * 
     * @param type Unit type.
     */
    void setType(UnitType type);
    /**
     * @brief Sets the unit's power.
     * 
     * @param power Unit's power.
     */
    void setPower(uint power);
    /**
     * @brief Associates an image with the unit.
     * 
     * @param image Unit's image.
     */
    void setImage(std::shared_ptr<GuiImage> image);
    /**
     * @brief Sets the unit's coordinates.
     * 
     * @param x x-position.
     * @param y y-position.
     */
    void setCoord(int x, int y);
    /**
     * @brief Sets whether the unit has already moved.
     * 
     * @param hasMoved true if the unit has moved, false otherwise.
     */
    void setHasMoved(bool hasMoved);
    /**
     * @brief Returns the unit type.
     * 
     * @return UnitType The unit type.
     */
    UnitType getType() const;
    /**
     * @brief Returns the unit's power.
     * 
     * @return uint The unit's power.
     */
    uint getPower() const;
    /**
     * @brief Returns whether the unit has already moved.
     * 
     * @return true if the unit has moved, false otherwise.
     */
    bool getHasMoved() const;
    /**
     * @brief Returns the unit's image.
     * 
     * @return std::shared_ptr<GuiImage> The unit's image.
     */
    std::shared_ptr<GuiImage> getImage() const;

};

#endif // UNIT_H