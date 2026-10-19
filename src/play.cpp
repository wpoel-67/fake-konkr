#include "gui.h"
#include "guiButton.h"
#include "guiHexagon.h"
#include "grid.h"
#include "transitions.h"

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

extern std::shared_ptr<Grid> grid;

uint nb_laps = 0;

void turn(std::shared_ptr<Graphics> window ,std::shared_ptr<Gui> gui, std::shared_ptr<GuiButton> player_button, std::shared_ptr<GuiButton> money_button) {
    nb_laps++;
    bool player = !grid->getPlayer();
    grid->setPlayer(player);
    if(player) {
        player_button->setText("Player: blue");
        player_button->setColor(0, 0, 255);
    } else {
        player_button->setText("Player: red");
        player_button->setColor(255, 0, 0);
    }
    grid->removeTmpFiles();
    grid->recalculateTiles(true);
    if(nb_laps >= 2)
        grid->collectMoney();
    grid->updateMoneyButton();
    grid->moveBandits();
}

void switchToPlay(std::shared_ptr<Graphics> window ,std::shared_ptr<Gui> gui) {
    int radius = kRadius;
    auto turn_button = std::make_shared<GuiButton>(window, kWidth / 2 + 400, kHeight - 100, 300, 100, "Turn");
    auto money_button = std::make_shared<GuiButton>(window, kWidth / 2, kHeight - 100, 300, 100, "Money:  0");
    auto undo_button = std::make_shared<GuiButton>(window, kWidth / 2 - 400, kHeight - 100, 300, 100, "Undo");
    auto player_button = std::make_shared<GuiButton>(window, 200, kHeight - 100, 300, 100, "Player: blue");
    auto buy_villager_button = std::make_shared<GuiButton>(window, kWidth / 2 - 600, kHeight - 200, 300, 100, "Buy Villager");
    auto buy_spiker_button = std::make_shared<GuiButton>(window, kWidth / 2 - 200, kHeight - 200, 300, 100, "Buy Spiker");
    auto buy_knight_button = std::make_shared<GuiButton>(window, kWidth / 2 + 200, kHeight - 200, 300, 100, "Buy Knight");
    auto buy_hero_button = std::make_shared<GuiButton>(window, kWidth / 2 + 600, kHeight - 200, 300, 100, "Buy Hero");

    buy_villager_button->setColor(100, 200, 100);
    buy_villager_button->setHoverColor(80, 180, 80);
    buy_villager_button->setOnClick([]() {
        grid->buyUnit(UnitType::VILLAGER);
    });

    buy_spiker_button->setColor(100, 200, 100);
    buy_spiker_button->setHoverColor(80, 180, 80);
    buy_spiker_button->setOnClick([]() {
        grid->buyUnit(UnitType::SPIKER);
    });

    buy_knight_button->setColor(100, 200, 100);
    buy_knight_button->setHoverColor(80, 180, 80);
    buy_knight_button->setOnClick([]() {
        grid->buyUnit(UnitType::KNIGHT);
    });

    buy_hero_button->setColor(100, 200, 100);
    buy_hero_button->setHoverColor(80, 180, 80);
    buy_hero_button->setOnClick([]() {
        grid->buyUnit(UnitType::HERO);
    });

    grid.reset(new Grid(window, gui, 100, 100, radius));
    turn_button->setColor(255, 165, 10);
    turn_button->setHoverColor(200, 110, 0);
    turn_button->setOnClick([window, gui, player_button, money_button]() {
        turn(window, gui, player_button, money_button);
    });
    money_button->setColor(243, 227, 214);
    money_button->setEnabled(false);
    undo_button->setColor(255, 165, 10);
    undo_button->setHoverColor(200, 110, 0);
    undo_button->setOnClick([]() {
        grid->undoLastMove();
    });
    player_button->setColor(0, 0, 255);
    player_button->setTextColor(255, 255, 255);
    player_button->setEnabled(false);
    gui->clear();
    gui->setBgColor(50, 125, 160);
    gui->add(turn_button);
    gui->add(money_button);
    gui->add(undo_button);
    gui->add(player_button);
    gui->add(buy_villager_button);
    gui->add(buy_spiker_button);
    gui->add(buy_knight_button);
    gui->add(buy_hero_button);
    grid->extractFromFile("map.txt");
    grid->setMoneyButton(money_button);
    grid->setPlayer(true);
    grid->recalculateTiles(true);
    money_button->setText("Money: " + std::to_string(grid->getPlayerMoney()));
}