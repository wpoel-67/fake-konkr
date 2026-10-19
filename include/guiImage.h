#ifndef GUIIMAGE_H
#define GUIIMAGE_H

#include "guiElement.h"
#include <iostream>
#include <memory>

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

class GuiImage : public GuiElement {
private:
    std::string path;
    int radius;
    
public:
    GuiImage(std::shared_ptr<Graphics> graphics, int x = 0, int y = 0);
    ~GuiImage();
    /**
     * @brief Sets the path of the image to display.
     * 
     * @param path Image path.
     */
    void setPath(std::string path);
    /**
     * @brief Sets the size of the image.
     * 
     * @param radius Radius of the image.
     */
    void setSize(int radius);
    /**
     * @brief Draws the image using the Graphics API.
     */
    void draw() override;
};

#endif // GUIIMAGE_H