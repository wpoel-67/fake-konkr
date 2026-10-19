#include "grid.h"

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

extern std::shared_ptr<Gui> gui;
extern std::shared_ptr<Graphics> window;

Grid::Grid(std::shared_ptr<Graphics> graphics,  std::shared_ptr<Gui> gui, int x_start, int y_start, int radius)
    :  x_start(x_start), y_start(y_start), radius(radius), graphics(graphics), gui(gui) {}

Grid::~Grid() {}

void Grid::onHexagonClick(Coord coord) {
    auto tile = tile_map[coord];

    // Case where a soldier is clicked
    if(tile->getHasUnit() && selected_unit == nullptr) {
        // Save the game state unless called by buyUnit
        if(!tile_map[coord]->getHasVillage()) {
            saveToFile("tmp" + std::to_string(move_count));
            move_count++;
        }

        // If it's a bandit, do nothing
        if(tile->getUnit()->getType() == UnitType::BANDIT) {
            return;
        }

        // If the soldier has already moved, do nothing
        if(tile->getUnit()->getHasMoved()) {
            return;
        }

        // Add soldier to drag and drop
        this->selected_unit = tile->getUnit();
        gui->setDraggedElement(tile->getUnit()->getImage());
        tile->setHasUnit(false);
        
        // Only enable tiles reachable by the soldier,
        // i.e. tiles reachable via flood-fill from the village and
        // tiles adjacent to that flood-fill
        Coord village;
        for(auto& [c, t] : tile_map) {
            disableTile(c);
            unHighlightTile(c);
        }
        if(player) {
            village = blue_village;
            
        } else {
            village = red_village;
        }
        flood(village, [this](Coord c) {
            enableTile(c);
            for(auto& n : neighbors(c)) {
                enableTile(n);
                if(!isTileFromPlayer(tile_map[n]->getType())) {
                    highlightTile(n);
                }
            }
        });
        
        return;
    } 
    
    // Case where a tile is clicked while a soldier is selected
    if(selected_unit) {

        // If an enemy soldier is on the tile and its power is lower
        // than the selected soldier's power, remove it
        if(!isTileFromPlayer(tile->getType())) {
            uint power = selected_unit->getPower();
            power = power == 4 ? 5 : power; // A hero can kill another hero
            if(tile->getHasUnit() && (tile->getUnit()->getPower() >= power)) {
                return;
            }
        }

        // If an enemy village is on the tile and its power is lower
        // than the selected soldier's power, destroy it
        if(tile->getHasVillage()) {
            if(!isTileFromPlayer(tile->getType())) {
                if(tile->getVillage()->getPower() <= selected_unit->getPower()) {
                    tile->setHasVillage(false);
                    switchToWinnerScreen(window, gui);
                } else {
                    return;
                }
            } else {
                return;
            }
        }
        
        // If the tile is occupied by an allied soldier, do nothing
        if(tile->getHasUnit() && isTileFromPlayer(tile->getType())) {
            if(tile->getUnit()->getType() != UnitType::BANDIT) {
                return;
            }
        }

        // Drop the dragged soldier onto the tile
        gui->releaseDraggedElement();
        tile->setHasUnit(true);
        tile->setUnit(selected_unit);

        // Color the tile red or blue depending on the player
        if(player) {
            tile->setType(TileType::BLUE);
        } else {
            tile->setType(TileType::RED);
        }
        selected_unit->setHasMoved(true);
        selected_unit = nullptr;
        for(auto& [c, t] : tile_map) {
            enableTile(c);
        }
        recalculateTiles();
        return;
    }
}


void Grid::setHexagon(Coord coord, TileType type) {
    auto tile = std::make_shared<Tile>();
    int x, y;
    logicalToPhysical(coord, x, y);
    auto hexagon = std::make_shared<GuiHexagon>(graphics, x, y, radius);
    hexagon->setOnClick([coord, this]() {
        this->onHexagonClick(coord);
    });
    tile->setHexagon(hexagon);
    tile->setType(type);
    tile_map[coord] = tile;
    gui->add(hexagon, false);
}

void Grid::setVillage(Coord coord, uint money) {
    auto village = std::make_shared<Village>();
    int x, y;
    if(tile_map[coord]->getType() == TileType::RED) {
        red_village = coord;
    } else if(tile_map[coord]->getType() == TileType::BLUE) {
        blue_village = coord;
    }
    logicalToPhysical(coord, x, y);
    auto village_image = std::make_shared<GuiImage>(graphics, x, y);
    village_image->setPath("img/village.png");
    village_image->setSize(radius - 15);
    village->setPower(2);
    village->setMoney(money);
    village->setImage(village_image);
    tile_map[coord]->setHasVillage(true);
    tile_map[coord]->setVillage(village);
    gui->add(village_image);
}

void Grid::setUnit(Coord coord, UnitType type) {
    if(tile_map[coord]->getHasVillage()) {
        return;
    }
    auto unit = std::make_shared<Unit>();
    int x, y;
    logicalToPhysical(coord, x, y);
    auto unit_image = std::make_shared<GuiImage>(graphics, x, y);
    unit->setType(type);
    unit_image->setSize(radius - 15);
    switch(type) {
        case UnitType::BANDIT:
            unit_image->setPath("img/bandit.png");
            unit->setPower(0);
            break;
        case UnitType::VILLAGER:
            unit_image->setPath("img/villager.png");
            unit->setPower(1);
            break;
        case UnitType::SPIKER:
            unit_image->setPath("img/spiker.png");
            unit->setPower(2);
            break;
        case UnitType::KNIGHT:
            unit_image->setPath("img/knight.png");
            unit->setPower(3);
            break;
        case UnitType::HERO:
            unit_image->setPath("img/hero.png");
            unit->setPower(4);
            break;
    }
    unit->setImage(unit_image);
    tile_map[coord]->setHasUnit(true);
    tile_map[coord]->setUnit(unit);
    gui->add(unit_image, true);
}

void Grid::extractFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if(!file.is_open()) {
        std::cerr << "Error, can't open file " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    char type, color;
    char unit_type;
    uint money;
    int x, y;
    std::string line;

    while(std::getline(file, line)) {
        if(line.empty())
            continue;

        std::istringstream iss(line);
        if(!(iss >> type >> x >> y)) {
            std::cerr << "Invalid line in file: " << line << std::endl;
            continue;
        }

        switch(type) {
            case 'H':
                iss >> color;
                switch(color) {
                    case 'R':
                        setHexagon({x, y}, TileType::RED);
                        break;
                    case 'B':
                        setHexagon({x, y}, TileType::BLUE);
                        break;
                    default:
                        setHexagon({x, y}, TileType::EMPTY);
                        break;
                }
                break;
            case 'V':
                iss >> money;
                setVillage({x, y}, money);
                break;
            case 'U':
                iss >> unit_type;
                switch(unit_type) {
                    case 'V':
                        setUnit({x, y}, UnitType::VILLAGER);
                        break;
                    case 'S':
                        setUnit({x, y}, UnitType::SPIKER);
                        break;
                    case 'K':
                        setUnit({x, y}, UnitType::KNIGHT);
                        break;
                    case 'H':
                        setUnit({x, y}, UnitType::HERO);
                        break;
                    case 'B':
                        setUnit({x, y}, UnitType::BANDIT);
                        break;
                }
                break;
        }
    }

    file.close();
}

void Grid::saveToFile(const std::string& filename) {
    std::ofstream file(filename);

    if(!file.is_open()) {
        std::cerr << "Error, can't open file " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
    for(const auto& [coord, tile] : tile_map) {
        switch(tile->getType()) {
            case TileType::EMPTY:
                file << "H " << coord.first << " " << coord.second << " E" << std::endl;
                break;
            case TileType::RED:
                file << "H " << coord.first << " " << coord.second << " R" << std::endl;
                break;
            case TileType::BLUE:
                file << "H " << coord.first << " " << coord.second << " B" << std::endl;
                break;
        }

        if(tile->getHasVillage()) {
            file << "V " << coord.first << " " << coord.second << " " << tile->getVillage()->getMoney() << std::endl;
        }

        if(tile->getHasUnit()) {
            switch(tile->getUnit()->getType()) {
                case UnitType::BANDIT:
                    file << "U " << coord.first << " " << coord.second << " B" << std::endl;
                    break;
                case UnitType::VILLAGER:
                    file << "U " << coord.first << " " << coord.second << " V" << std::endl;
                    break;
                case UnitType::SPIKER:
                    file << "U " << coord.first << " " << coord.second << " S" << std::endl;
                    break;
                case UnitType::KNIGHT:
                    file << "U " << coord.first << " " << coord.second << " K" << std::endl;
                    break;
                case UnitType::HERO:
                    file << "U " << coord.first << " " << coord.second << " H" << std::endl;
                    break;
            }
        }
    }
    file.close();
}

std::vector<Coord> Grid::neighbors(Coord coord) {
    std::vector<Coord> neighbors;
    int x = coord.first;
    int y = coord.second;

    neighbors.push_back({x, y - 1}); // Top neighbor
    neighbors.push_back({x, y + 1}); // Bottom neighbor
    if(x % 2 == 0) {
        neighbors.push_back({x + 1, y}); // Top-right neighbor
        neighbors.push_back({x - 1, y}); // Top-left neighbor
        neighbors.push_back({x + 1, y + 1}); // Bottom-right neighbor
        neighbors.push_back({x - 1, y + 1}); // Bottom-left neighbor
    } else {
        neighbors.push_back({x + 1, y - 1}); // Top-right neighbor
        neighbors.push_back({x + 1, y}); // Bottom-right neighbor
        neighbors.push_back({x - 1, y}); // Bottom-left neighbor
        neighbors.push_back({x - 1, y - 1}); // Top-left neighbor    
    }

    neighbors.erase(std::remove_if(neighbors.begin(), neighbors.end(),
        [this](Coord n) {
            return tile_map.find(n) == tile_map.end();
        }), neighbors.end());

    return neighbors;
}

bool Grid::pathFinding(Coord start, Coord end) {
    if(tile_map.find(start) == tile_map.end() || tile_map.find(end) == tile_map.end()
       || tile_map[start]->getType() != tile_map[end]->getType()) {
        return false;
    }
    TileType type = tile_map[start]->getType();
    std::queue<Coord> queue;
    std::set<Coord> visited;
    queue.push(start);
    visited.insert(start);
    while(!queue.empty()) {
        Coord current = queue.front();
        queue.pop();

        if(current == end) {
            return true;
        }
        for(const auto& neighbor : neighbors(current)) {
            if(tile_map.find(neighbor) == tile_map.end())
                continue;
            if(visited.find(neighbor) == visited.end() && tile_map[neighbor]->getType() == type) {
                queue.push(neighbor);
                visited.insert(neighbor);
            }
        }
    }
    return false;
}


void Grid::flood(Coord coord, std::function<void(Coord)> action) {
    if(tile_map.find(coord) == tile_map.end())
        return;
    std::queue<Coord> queue;
    std::set<Coord> visited;
    queue.push(coord);
    visited.insert(coord);
    while(!queue.empty()) {
        Coord c = queue.front();
        queue.pop();
        for(const auto& neighbor : neighbors(c)) {
            if(tile_map.find(neighbor) == tile_map.end())
                continue;
            if(visited.find(neighbor) == visited.end() && tile_map[neighbor]->getType() == tile_map[c]->getType()) {
                queue.push(neighbor);
                visited.insert(neighbor);
            }
        }
        action(c);
    }
}

void Grid::setPlayer(bool player) {
    this->player = player;
}

bool Grid::getPlayer() const {
    return player;
}

void Grid::enableTile(Coord coord) {
    tile_map[coord]->getHexagon()->setEnabled(true);
}

void Grid::disableTile(Coord coord) {
    tile_map[coord]->getHexagon()->setEnabled(false);
}

void Grid::highlightTile(Coord coord) {
    tile_map[coord]->getHexagon()->setHighlighted(true);
}

void Grid::unHighlightTile(Coord coord) {
    tile_map[coord]->getHexagon()->setHighlighted(false);
}

bool Grid::isTileFromPlayer(TileType type) {
    return (type == TileType::RED && !player) || (type == TileType::BLUE && player);
}

void Grid::setMoneyButton(std::shared_ptr<GuiButton> button) {
    money_button = button;
}

uint Grid::getPlayerMoney() {
    if(player) {
        return tile_map[blue_village]->getVillage()->getMoney();
    } else {
        return tile_map[red_village]->getVillage()->getMoney();
    }
}

void Grid::recalculateTiles(bool resetUnits) {
    for(auto& [coord, tile] : tile_map) {
        tile->setConnected(false);
        unHighlightTile(coord);
        if(resetUnits && tile->getHasUnit()) {
            tile->getUnit()->setHasMoved(false);
        }
    }
    flood(blue_village, [this](Coord coord) {
        tile_map[coord]->setConnected(true);
    });
    flood(red_village, [this](Coord coord) {
        tile_map[coord]->setConnected(true);
    });
    for(auto& [coord, tile] : tile_map) {
        if(tile->getHasUnit() && tile->getUnit()->getType() != UnitType::BANDIT) {
            if(!tile->getIsConnected()) {
                auto unit = std::make_shared<Unit>();
                auto unit_image = std::make_shared<GuiImage>(graphics, -10, -10);
                tile->setHasUnit(false);
                unit->setType(UnitType::BANDIT);
                unit_image->setPath("img/bandit.png");
                unit_image->setSize(radius - 15);
                unit->setPower(0);
                unit->setImage(unit_image);
                tile->setHasUnit(true);
                tile->setUnit(unit);
                gui->add(unit_image);
            } 
        }
        if(isTileFromPlayer(tile->getType()) && tile->getIsConnected()) {
            enableTile(coord);
        } else {
            disableTile(coord);
        }
    }
}

void Grid::updateMoneyButton() {
    if(money_button) {
        std::shared_ptr<Village> village;
        if(player) {
            village = tile_map[blue_village]->getVillage();
        } else {
            village = tile_map[red_village]->getVillage();
        }
        money_button->setText("Money: " + std::to_string(village->getMoney()));
    }
}

void Grid::buyUnit(UnitType type) {
    if(selected_unit) {
        return;
    }
    saveToFile("tmp" + std::to_string(move_count));
    move_count++;
    auto unit = std::make_shared<Unit>();
    auto unit_image = std::make_shared<GuiImage>(graphics, -10, -10);
    std::shared_ptr<Village> village;
    if(player) {
        village = tile_map[blue_village]->getVillage();
    } else {
        village = tile_map[red_village]->getVillage();
    }
    unit->setType(type);
    unit_image->setSize(radius - 15);
    switch(type) {
        case UnitType::VILLAGER:
            if(village->getMoney() < 10) {
                return;
            }
            unit_image->setPath("img/villager.png");
            unit->setPower(1);
            village->setMoney(village->getMoney() - 10);
            break;
        case UnitType::SPIKER:
            if(village->getMoney() < 20) {
                return;
            }
            unit_image->setPath("img/spiker.png");
            unit->setPower(2);
            village->setMoney(village->getMoney() - 20);
            break;
        case UnitType::KNIGHT:
            if(village->getMoney() < 40) {
                return;
            }
            unit_image->setPath("img/knight.png");
            unit->setPower(3);
            village->setMoney(village->getMoney() - 40);
            break;
        case UnitType::HERO:
            if(village->getMoney() < 80) {
                return;
            }
            unit_image->setPath("img/hero.png");
            unit->setPower(4);
            village->setMoney(village->getMoney() - 80);
            break;
        default:
            return;
    }
    unit->setImage(unit_image);
    gui->add(unit_image);
    updateMoneyButton();
    if(player) {
        tile_map[blue_village]->setHasUnit(true);
        tile_map[blue_village]->setUnit(unit);
        tile_map[blue_village]->getHexagon()->onClick();
    } else {
        tile_map[red_village]->setHasUnit(true);
        tile_map[red_village]->setUnit(unit);
        tile_map[red_village]->getHexagon()->onClick();
    }
}

void Grid::undoLastMove() {
    if(move_count == 0) {
        return;
    }
    std::string filename = "tmp" + std::to_string(move_count - 1);
    move_count--;
    tile_map.clear();
    extractFromFile(filename);
    remove(filename.c_str());
    recalculateTiles();
    updateMoneyButton();
}

void Grid::removeTmpFiles() {
    for(uint i = 0; i < move_count; i++) {
        std::string filename = "tmp" + std::to_string(i);
        remove(filename.c_str());
    }
    move_count = 0;
}

void Grid::collectMoney() {
    Coord village;
    std::shared_ptr<Village> village_ptr;
    if(player) {
        village = blue_village;
        village_ptr = tile_map[blue_village]->getVillage();
    } else {
        village = red_village;
        village_ptr = tile_map[red_village]->getVillage();
    }
    
    flood(village, [this, village_ptr](Coord coord) {
        if(tile_map[coord]->getIsConnected()) {
            village_ptr->setMoney(village_ptr->getMoney() + 1);
        }
    });
}

void Grid::moveBandits() {
    for(auto& [coord, tile] : tile_map) {
        if(tile->getHasUnit() && tile->getUnit()->getType() == UnitType::BANDIT) {
            std::vector<Coord> n = this->neighbors(coord);
            if(n.empty()) {
                continue;
            }
            int random_index = rand() % n.size();
            Coord new_coord = n[random_index];
            if(tile_map[new_coord]->getHasUnit()) {
                continue;
            }
            tile_map[new_coord]->setHasUnit(true);
            tile_map[new_coord]->setUnit(tile->getUnit());
            tile_map[coord]->setHasUnit(false);
        }
    }
}