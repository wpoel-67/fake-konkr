#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include "guiClickable.h"
#include <iostream>
#include <memory>
#include <functional>

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

class GuiButton : public GuiClickable {
protected:
    int width, height;
    std::string text;
    uint8_t r, g, b;
    uint8_t r_hover, g_hover, b_hover;
    bool is_hovered = false;
    uint font_size;
    uint8_t r_text, g_text, b_text;
    std::function<void()> onClickAction;
    std::function<void()> onHoverAction;
    std::function<void()> onLeaveAction;
    
public:
    GuiButton(std::shared_ptr<Graphics> graphics, int x, int y, int width, int height, std::string text);
    ~GuiButton();
    /**
     * @brief Draws the button using the Graphics API.
     */
    void draw() override;
    /**
     * @brief Method called when the button is clicked.
     */
    void onClick() override;
    /**
     * @brief Method called when the mouse hovers over the button.
     */
    void onHover() override;
    /**
     * @brief Method called when the mouse leaves the button.
     */
    void onLeave() override;
    /**
     * @brief Indicates whether the coordinates (x, y) are inside the button.
     * 
     * @param x x-position.
     * @param y y-position.
     * @return true if the position is inside the button, false otherwise.
     */
    bool isHit(int x, int y) override;
    /**
     * @brief Sets the background color of the button.
     * 
     * @param r red
     * @param g green
     * @param b blue
     */
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    /**
     * @brief Modifies the text displayed on the button.
     * 
     * @param text New text.
     */
    void setText(std::string text);
    /**
     * @brief Sets the background color when hovering over the button.
     * 
     * @param r red
     * @param g green
     * @param b blue
     */
    void setHoverColor(uint8_t r, uint8_t g, uint8_t b);
    /**
     * @brief Sets the font size of the text.
     * 
     * @param fontSize Font size in pixels.
     */
    void setFontSize(uint fontSize);
    /**
     * @brief Sets the color of the text.
     * 
     * @param r red
     * @param g green
     * @param b blue
     */
    void setTextColor(uint8_t r, uint8_t g, uint8_t b);
    /**
     * @brief Associates an action to perform when the button is clicked.
     * 
     * @param onClickAction Function to call.
     */
    void setOnClick(std::function<void()> onClickAction);
    /**
     * @brief Associates an action to perform when the button is hovered over.
     * 
     * @param onHoverAction Function to call.
     */
    void setOnHover(std::function<void()> onHoverAction);
    /**
     * @brief Associates an action to perform when the mouse leaves the button.
     * 
     * @param onLeaveAction Function to call.
     */
    void setOnLeave(std::function<void()> onLeaveAction);

};

#endif // GUIBUTTON_H