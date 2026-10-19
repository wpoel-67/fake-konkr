# Fake Konkr Project

This project was made for one of my Master's degree classes. It is a reproduction of [konkr.io](https://konkr.io) by Michal Bureš.
All game code and sprites were created by me.

Since the project was originally hosted on the university's GitLab instance, the commit history was lost when uploading it to GitHub.

## Installation

### Linux (Ubuntu)
Install SDL2:

```bash
sudo apt update
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

## Build the project
```bash
make
```
The executable file will be located in the `build` folder.

## Run the project
```bash
./build/main
```

## Project Architecture

The project is structured into 3 main layers:

* Low-level graphics / SDL2 wrapper: `graphics.h`
* High-level GUI management (buttons, images, etc.): `gui*.h`
* Game logic (game board, movements, etc.): `grid.h`, `tile.h`, `unit.h`, `village.h`

along with a few intermediate functions (transition functions) used to switch between GUI screens.

### Graphics Class
This class acts as a wrapper around the SDL2 library. All calls to SDL2 must go through it. It also provides additional helper utilities, such as simplified one-line calls for SDL2 operations that would otherwise require multiple lines of code.

### Graphical User Interface (GUI)
The `Gui` class serves as a container for graphical elements. In short, you create a graphical element (such as a `GuiButton`), specify which callback function to invoke on click, hover, etc., and add it to the `Gui` container, which handles rendering everything it holds. When an event occurs (e.g., a mouse click), `main` calls `gui->treatClick(event.button.x, event.button.y)`, which iterates through all graphical elements to check if any of them was hit by the click and calls its `onClick` method. Each element is responsible for computing whether the provided coordinates fall within its own hitbox (`isHit` method).

### Polymorphism
All graphical elements derive from the abstract class `GuiElement`.
Clickable elements (buttons and hexagons) inherit from the abstract class `GuiClickable` (which itself inherits from `GuiElement`).
This way, if we want to modify behavior shared by all clickable elements, we only need to make the change once in `GuiClickable`.

### Game Logic
Most of the game logic is located in `play.cpp` and `grid.cpp`. The code for this part is still a bit messy.



Léo Piveteau-Wernert