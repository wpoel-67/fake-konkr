#ifndef TILE_H
#define TILE_H

#include "guiHexagon.h"
#include "guiImage.h"
#include "unit.h"
#include "village.h"
#include <iostream>

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

enum class TileType {
    EMPTY,
    BLUE,
    RED
};

class Tile {
private:
    TileType type;
    bool hasVillage = false;
    bool hasUnit = false;
    bool isConnected = false;
    std::shared_ptr<GuiHexagon> hexagon;
    std::shared_ptr<Village> village;
    std::shared_ptr<Unit> unit;

public:
    Tile();
    Tile(const Tile&) = default;
    ~Tile();
    /**
     * @brief Sets the tile type.
     * 
     * @param type Tile type.
     */
    void setType(TileType type);
    /**
     * @brief Sets whether the tile has a village.
     * 
     * @param hasVillage true if the tile has a village, false otherwise.
     */
    void setHasVillage(bool hasVillage);
    /**
     * @brief Sets whether the tile has a unit.
     * 
     * @param hasUnit true if the tile has a unit, false otherwise.
     */
    void setHasUnit(bool hasUnit);
    /**
     * @brief Associates a unit (soldier) with the tile.
     * 
     * @param unit The unit to associate.
     */
    void setUnit(std::shared_ptr<Unit> unit);
    /**
     * @brief Associates a hexagon with the tile.
     * 
     * @param hexagon The hexagon to associate.
     */
    void setHexagon(std::shared_ptr<GuiHexagon> hexagon);
    /**
     * @brief Associates a village with the tile.
     * 
     * @param village The village to associate.
     */
    void setVillage(std::shared_ptr<Village> village);
    /**
     * @brief Sets whether the tile is connected to other tiles.
     * 
     * @param connected true if the tile is connected, false otherwise.
     */
    void setConnected(bool connected);
    /**
     * @brief Returns the hexagon associated with the tile.
     * 
     * @return std::shared_ptr<GuiHexagon> The tile's hexagon.
     */
    std::shared_ptr<GuiHexagon> getHexagon() const;
    /**
     * @brief Returns the village associated with the tile.
     * 
     * @return std::shared_ptr<Village> The tile's village.
     */
    std::shared_ptr<Village> getVillage() const;
    /**
     * @brief Returns the unit associated with the tile.
     * 
     * @return std::shared_ptr<Unit> The tile's unit.
     */
    std::shared_ptr<Unit> getUnit() const;
    /**
     * @brief Returns the tile type.
     * 
     * @return TileType The tile type.
     */
    TileType getType() const;
    /**
     * @brief Returns whether the tile has a village.
     * 
     * @return true if the tile has a village, false otherwise.
     */
    bool getHasVillage() const;
    /**
     * @brief Returns whether the tile has a unit.
     * 
     * @return true if the tile has a unit, false otherwise.
     */
    bool getHasUnit() const;
    /**
     * @brief Returns whether the tile is connected to other tiles.
     * 
     * @return true if the tile is connected, false otherwise.
     */
    bool getIsConnected() const;

    
};

#endif // TILE_H