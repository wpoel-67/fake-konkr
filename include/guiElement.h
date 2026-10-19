#ifndef GUIELEMENT_H
#define GUIELEMENT_H

#include "graphics.h"
#include <iostream>
#include <memory>

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

class GuiElement {
protected:
    std::shared_ptr<Graphics> graphics;
    int x, y;
    bool is_clickable = false;

public:
    GuiElement(std::shared_ptr<Graphics> graphics, int x, int y);
    ~GuiElement();
    /**
     * @brief Draws the element using the Graphics API.
     */
    virtual void draw() = 0;
    /**
     * @brief Changes the position of the element.
     * 
     * @param x New x-position.
     * @param y New y-position.
     */
    void setPosition(int x, int y);
    /**
     * @brief Indicates whether the element is clickable.
     * 
     * @return true if clickable, false otherwise.
     */
    bool isClickable() const;
    /**
     * @brief Returns the x-position of the element.
     * 
     * @return x-position.
     */
    int getX() const;
    /**
     * @brief Returns the y-position of the element.
     * 
     * @return y-position.
     */
    int getY() const;

};
#endif // GUIELEMENT_H