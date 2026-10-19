#ifndef GRID_H
#define GRID_H

#include "guiElement.h"
#include "guiClickable.h"
#include "graphics.h"
#include "gui.h"
#include "guiHexagon.h"
#include "guiImage.h"
#include "tile.h"
#include "unit.h"
#include "village.h"
#include "transitions.h"
#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <queue>

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */


constexpr double kSqrt3 = 1.732050807568877293;

using Coord = std::pair<int, int>;

/**
 * @brief Class representing the game board.
 */
class Grid {
protected:
    int x_start, y_start;
    int radius;
    bool player = 1;
    uint move_count = 0;
    std::shared_ptr<Graphics> graphics;
    std::shared_ptr<Gui> gui;
    std::map<Coord, std::shared_ptr<Tile>> tile_map;
    std::shared_ptr<GuiButton> money_button;
    std::shared_ptr<Unit> selected_unit;
    Coord blue_village = {-10, -10};
    Coord red_village = {-10, -10};

private:
    void onHexagonClick(Coord coord);
    bool isTileFromPlayer(TileType type);

public:
    Grid(std::shared_ptr<Graphics> graphics, std::shared_ptr<Gui> gui, int x_start, int y_start, int radius);
    ~Grid();
    /**
     * @brief Creates a hexagon at position (x, y) with the given tile type.
     * 
     * @param coord Coordinates of the hexagon.
     * @param type Tile type.
     */
    void setHexagon(Coord coord, TileType type);
    /**
     * @brief Creates a village at position (x, y).
     * 
     * @param coord Coordinates of the village.
     * @param money Money of the village.
     */
    void setVillage(Coord coord, uint money);
    /**
     * @brief Creates a soldier at position (x, y).
     * 
     * @param coord Coordinates of the unit.
     * @param type Unit type.
     */
    void setUnit(Coord coord, UnitType type);
    /**
     * @brief Extracts hexagon coordinates from a file and converts them.
     * 
     * @param filename name of the file to read
     */
    void extractFromFile(const std::string& filename);
    /**
     * @brief Saves the hexagon coordinates to a file.
     * 
     * @param filename name of the file to write
     */
    void saveToFile(const std::string& filename);
    /**
     * @brief Returns the list of hexagons adjacent to the given tile.
     * 
     * @param tile The tile whose adjacent tiles are requested.
     * @return std::vector<Coord> The list of adjacent tiles.
     */
    std::vector<Coord> neighbors(Coord coord);
    /**
     * @brief Converts logical coordinates into physical coordinates.
     * Physical coordinates (x, y) are passed by reference.
     * 
     * @param coord Logical coordinates.
     * @param x Physical x-coordinate.
     * @param y Physical y-coordinate.
     */
    inline void logicalToPhysical(Coord coord, int &x, int &y) {
        x = x_start + coord.first * (1.5 * radius);
        y = y_start + coord.second * (kSqrt3 * radius) - (coord.first % 2) * (kSqrt3 / 2 * radius);
    }
    /**
     * @brief Pathfinding method between two tiles.
     * Uses a BFS.
     *
     * @param start starting tile
     * @param end destination tile
     * @return true if a path exists between the two tiles
     * @return false otherwise
     */
    bool pathFinding(Coord start, Coord end);
    /**
     * @brief Flood-fill function that traverses adjacent tiles
     * of the same color as the given tile,
     * and calls `action(coord)` on each tile.
     * Uses a BFS.
     * 
     * @param coord starting tile
     * @param action function to call on each tile
     */
    void flood(Coord coord, std::function<void(Coord)> action);
    /**
     * @brief Changes the current player.
     * 
     * @param player true if the player is the blue player, false otherwise.
     */
    void setPlayer(bool player);
    /**
     * @brief Returns the current player.
     * 
     * @return true if the player is the blue player, false otherwise.
     */
    bool getPlayer() const;
    /**
     * @brief Associates the money management button with the grid.
     * 
     * @param button Button to associate.
     */
    void setMoneyButton(std::shared_ptr<GuiButton> button);
    /**
     * @brief Enables interaction with a given tile.
     * 
     * @param coord Coordinates of the tile to enable.
     */
    void enableTile(Coord coord);
    /**
     * @brief Disables interaction with a given tile.
     * 
     * @param coord Coordinates of the tile to disable.
     */
    void disableTile(Coord coord);
    /**
     * @brief Highlights a tile.
     * 
     * @param coord Coordinates of the tile to highlight.
     */
    void highlightTile(Coord coord);
    /**
     * @brief Removes the highlight from a tile.
     * 
     * @param coord Coordinates of the tile to unhighlight.
     */
    void unHighlightTile(Coord coord);
    /**
     * @brief Recalculates tile states.
     * 
     * @param resetUnits Indicates whether to reset units (false by default).
     */
    void recalculateTiles(bool resetUnits = false);
    /**
     * @brief Buys a unit of the given type for the current player.
     * 
     * @param type Type of unit to buy.
     */
    void buyUnit(UnitType type);
    /**
     * @brief Returns the current player's money.
     * 
     * @return Available amount of money.
     */
    uint getPlayerMoney();
    /**
     * @brief Updates the money button display.
     */
    void updateMoneyButton();
    /**
     * @brief Undoes the last move made.
     */
    void undoLastMove();
    /**
     * @brief Deletes temporary files generated during the turn.
     */
    void removeTmpFiles();
    /**
     * @brief Collects money from the current player's villages.
     */
    void collectMoney();
    /**
     * @brief Moves bandits on the map according to their movement logic.
     */
    void moveBandits();

};

#endif // GRID_H