#ifndef GUIHEXAGON_H
#define GUIHEXAGON_H

#include "guiClickable.h"
#include <iostream>
#include <memory>
#include <functional>

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */


class GuiHexagon : public GuiClickable {
protected:
    int radius;
    uint8_t r, g, b;
    bool is_hovered;
    bool is_highlighted;
    std::function<void()> onClickAction;
    std::function<void()> onHoverAction;
    std::function<void()> onLeaveAction;

public:
    GuiHexagon(std::shared_ptr<Graphics> graphics, int x, int y, int radius);
    ~GuiHexagon();
    /**
     * @brief Draws the hexagon using the Graphics API.
     */
    void draw() override;
    /**
     * @brief Method called when the hexagon is clicked.
     */
    void onClick() override;
    /**
     * @brief Method called when the mouse hovers over the hexagon.
     */
    void onHover() override;
    /**
     * @brief Method called when the mouse leaves the hexagon.
     */
    void onLeave() override;
    /**
     * @brief Indicates whether the coordinates (x, y) hit the hexagon.
     * 
     * @param x x-position.
     * @param y y-position.
     * @return true if the position hits the hexagon, false otherwise.
     */
    bool isHit(int x, int y) override;
    /**
     * @brief Sets the background color of the hexagon.
     * 
     * @param r red
     * @param g green
     * @param b blue
     */
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    /**
     * @brief Associates an action to perform when the hexagon is clicked.
     * 
     * @param onClickAction Function to call.
     */
    void setOnClick(std::function<void()> onClickAction);
    /**
     * @brief Associates an action to perform when the hexagon is hovered over.
     * 
     * @param onHoverAction Function to call.
     */
    void setOnHover(std::function<void()> onHoverAction);
    /**
     * @brief Associates an action to perform when the mouse leaves the hexagon.
     * 
     * @param onLeaveAction Function to call.
     */
    void setOnLeave(std::function<void()> onLeaveAction);
    /**
     * @brief Sets whether the hexagon is highlighted.
     * 
     * @param highlighted true to highlight, false to remove the highlight.
     */
    void setHighlighted(bool highlighted);

};

#endif // GUIHEXAGON_H