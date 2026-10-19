#ifndef GUICLICKABLE_H
#define GUICLICKABLE_H

#include "guiElement.h"
#include <iostream>
#include <memory>

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

class GuiClickable : public GuiElement {
protected:
    bool enabled = true;
public:
    GuiClickable(std::shared_ptr<Graphics> graphics, int x, int y);
    ~GuiClickable();
        /**
     * @brief Enables or disables interaction with the element.
     * 
     * @param enabled true to enable, false to disable.
     */
    void setEnabled(bool enabled);
    /**
     * @brief Method called when the element is clicked.
     */
    virtual void onClick() = 0;
    /**
     * @brief Method called when the mouse hovers over the element.
     */
    virtual void onHover() = 0;
    /**
     * @brief Method called when the mouse leaves the element.
     */
    virtual void onLeave() = 0;
    /**
     * @brief Indicates whether the coordinates (x, y) hit the element.
     * 
     * @param x x-position.
     * @param y y-position.
     * @return true if the position hits the element, false otherwise.
     */
    virtual bool isHit(int x, int y) = 0;

};
    
#endif // GUICLICKABLE_H