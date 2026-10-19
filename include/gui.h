#ifndef GUI_H
#define GUI_H

#include "graphics.h"
#include "guiElement.h"
#include "guiClickable.h"
#include "guiButton.h"
#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

constexpr double kRadius = 30;

/**
 * @brief Class containing the graphical user interface elements.
 * 
 */
class Gui {
private:
    int width, height;
    uint8_t r, g, b;
    std::shared_ptr<Graphics> graphics;
    std::vector<std::shared_ptr<GuiElement>> elements;
    std::shared_ptr<GuiClickable> last_hovered;
    std::shared_ptr<GuiElement> dragged_element;

public:
    Gui(std::shared_ptr<Graphics> graphics, int width, int height);
    ~Gui();
    /**
     * @brief Returns an iterator to the beginning of the element list.
     * 
     * @return std::vector<std::shared_ptr<GuiElement>>::iterator 
     */
    std::vector<std::shared_ptr<GuiElement>>::iterator begin();
    /**
     * @brief Returns an iterator to the end of the element list.
     * 
     * @return std::vector<std::shared_ptr<GuiElement>>::iterator 
     */
    std::vector<std::shared_ptr<GuiElement>>::iterator end();
    /**
     * @brief Adds a graphical element (button, text, ...) to the element list.
     * 
     * @param element The element to add.
     * @param append If true (default), the element is added to the end of the list.
     */
    void add(std::shared_ptr<GuiElement> element, bool append = true);
    /**
     * @brief Removes a graphical element from the element list.
     * 
     * @param index The index of the element to remove.
     */
    void remove(int index);
    /**
     * @brief Removes a graphical element from the element list.
     * 
     * @param element The element to remove.
     */
    void remove(std::shared_ptr<GuiElement> element);
    /**
     * @brief Handles a mouse click at coordinates (x, y), where coordinates
     * are provided by SDL_PollEvent.
     * 
     * @param x The x-position of the click.
     * @param y The y-position of the click.
     */
    void treatClick(int x, int y);
    /**
     * @brief Handles a mouse hover at coordinates (x, y), where coordinates
     * are provided by SDL_PollEvent.
     * 
     * @param x The x-position of the hover.
     * @param y The y-position of the hover.
     */
    void treatHover(int x, int y);
    /**
     * @brief Handles a mouse drag at coordinates (x, y), where coordinates
     * are provided by SDL_PollEvent.
     * 
     * @param x The x-position of the drag.
     * @param y The y-position of the drag.
     */
    void treatDrag(int x, int y);
    /**
     * @brief Sets the graphical element that will be dragged with the mouse.
     * 
     * @param element The element to drag.
     */
    void setDraggedElement(std::shared_ptr<GuiElement> element);
    /**
     * @brief Releases the graphical element being dragged with the mouse.
     */
    void releaseDraggedElement();
    /**
     * @brief Sets the background color of the GUI.
     * 
     * @param r red.
     * @param g green.
     * @param b blue.
     */
    void setBgColor(uint8_t r, uint8_t g, uint8_t b);
    /**
     * @brief Draws the GUI background.
     * If a background image is set, it is drawn instead of the color.
     */
    void drawBackground();
    /**
     * @brief Draws all graphical elements.
     */
    void drawAll();
    /**
     * @brief Updates the display.
     */
    void update();
    /**
     * @brief Clears the window.
     */
    void clear();

};

#endif // GUI_H