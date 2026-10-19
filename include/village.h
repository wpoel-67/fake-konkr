#ifndef VILLAGE_H
#define VILLAGE_H

#include "guiImage.h"
#include "gui.h"
#include <iostream>

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

class Village {
private:
    uint power;
    uint money;
    std::shared_ptr<GuiImage> image;

public:
    Village();
    Village(const Village&) = default;
    ~Village();
        /**
     * @brief Sets the power (normally 1) of the village.
     * 
     * @param power Power of the village.
     */
    void setPower(uint power);
    /**
     * @brief Sets the village's money.
     * 
     * @param money Amount of money in the village.
     */
    void setMoney(uint money);
    /**
     * @brief Associates an image with the village.
     * 
     * @param image Image of the village.
     */
    void setImage(std::shared_ptr<GuiImage> image);
    /**
     * @brief Sets the coordinates of the village.
     * 
     * @param x x-position.
     * @param y y-position.
     */
    void setCoord(int x, int y);
    /**
     * @brief Returns the power of the village.
     * 
     * @return uint The power of the village.
     */
    uint getPower() const;
    /**
     * @brief Returns the village's money.
     * 
     * @return uint The village's money.
     */
    uint getMoney() const;
    /**
     * @brief Returns the image of the village.
     * 
     * @return std::shared_ptr<GuiImage> The image of the village.
     */
    std::shared_ptr<GuiImage> getImage() const;

};

#endif // VILLAGE_H