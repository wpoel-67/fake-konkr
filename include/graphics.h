#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */


constexpr double kPi = 3.141592653589793238;
constexpr int kWidth = 1800;
constexpr int kHeight = 1000;

/**
 * @brief Structure to store the return value of the textSize function.
 */
using TextSize = struct TextSize {
    int h;
    int w;
};

/**
 * @brief SDL2 wrapper class to manage rendering. The main goal is to group
 * all SDL2 calls into a single class. Calling SDL2 functions outside of this
 * class is discouraged, hence the SDL_PollEvent wrapper.
 */
class Graphics {
private:
    int width, height;
    std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
    std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer;
    std::map<uint, std::shared_ptr<TTF_Font>> fonts;
    std::unique_ptr<SDL_Cursor, void(*)(SDL_Cursor*)> cursor_hand;
    std::unique_ptr<SDL_Cursor, void(*)(SDL_Cursor*)> cursor_arrow;
    std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> hexagon_image;
    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> hexagon_texture;
    std::map<std::string, std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)>> images;
    std::map<std::string, std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>> image_textures;
    std::map<std::string, std::shared_ptr<SDL_Texture>> text_textures;

public:
    Graphics();
    ~Graphics();
    /**
     * @brief Initializes the window by calling SDL_Init, SDL_CreateWindow, and 
     * SDL_CreateRenderer.
     * 
     * @param title window title
     * @param width window width
     * @param height window height
     */
    void init(const std::string& title, int width, int height);
    /**
     * @brief Clears the window by calling SDL_RenderClear.
     */
    void clear();
    /**
     * @brief Updates the window by calling SDL_RenderPresent.
     */
    void update();
    /**
     * @brief Draws a pixel of color (r, g, b) at position (x, y).
     * 
     * @param x x-coordinate of the pixel (width)
     * @param y y-coordinate of the pixel (height)
     * @param r red
     * @param g green
     * @param b blue
     */
    void drawPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);
    /**
     * @brief Draws a line of color (r, g, b) between points (x1, y1) and (x2, y2).
     * 
     * @param x1 x-coordinate of the first point
     * @param y1 y-coordinate of the first point
     * @param x2 x-coordinate of the second point
     * @param y2 y-coordinate of the second point
     * @param r red
     * @param g green
     * @param b blue
     */
    void drawLine(int x1, int y1, int x2, int y2, uint8_t r, uint8_t g, uint8_t b);
    /**
     * @brief Draws a rectangle of color (r, g, b) centered at (x, y) 
     * with width w and height h.
     * 
     * @param x x-coordinate of the rectangle
     * @param y y-coordinate of the rectangle
     * @param w width of the rectangle
     * @param h height of the rectangle
     * @param r red
     * @param g green
     * @param b blue
     */
    void drawRect(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b);
    /**
     * @brief Draws a hollow hexagon of color (r, g, b) centered at (x, y) with radius radius
     * by drawing 6 lines, with a 60-degree angle between each line.
     * 
     * @param x x-coordinate of the hexagon
     * @param y y-coordinate of the hexagon
     * @param radius radius of the hexagon
     * @param r red
     * @param g green
     * @param b blue
     */
    void drawHexagon(int x, int y, double radius, uint8_t r, uint8_t g, uint8_t b);
    /**
     * @brief Draws a hexagon texture centered at (x, y), of color (r, g, b) 
     * and with radius radius.
     * 
     * @param x x-coordinate of the hexagon
     * @param y y-coordinate of the hexagon
     * @param radius radius of the hexagon
     */
    void drawHexagonTexture(int x, int y, int radius, uint8_t r, uint8_t g, uint8_t b);
    /**
     * @brief Draws text at position (x, y) with color (r, g, b).
     * 
     * @param x x-coordinate of the text
     * @param y y-coordinate of the text
     * @param text text to display
     * @param r red
     * @param g green
     * @param b blue
     * @param size font size
     */
    void drawText(int x, int y, const std::string& text,
                uint8_t r, uint8_t g, uint8_t b, uint size);      
    /**
     * @brief Returns the size of the text that will be created by drawText.
     * 
     * @param text text to display
     * @param size font size
     */
    TextSize textSize(const std::string& text, uint size);
    /**
     * @brief Draws an image at position (x, y) with size radius.
     * 
     * @param path image path
     * @param x x-coordinate of the image
     * @param y y-coordinate of the image
     * @param w width of the image
     * @param h height of the image
     */
    void drawImage(const std::string& path, int x, int y, int radius);
    /**
     * @brief Changes the mouse cursor to a hand.
     */
    void setHandCursor();
    /**
     * @brief Changes the mouse cursor to an arrow.
     */
    void setArrowCursor();
    /**
     * @brief Wrapper for SDL_PollEvent.
     * 
     * @param event 
     * @return int: The return value of SDL_PollEvent.
     */
    inline int pollEvent(SDL_Event& event) {
        return SDL_PollEvent(&event);
    }
    /**
     * @brief Wrapper for SDL_Delay.
     * 
     * @param ms 
     */
    inline void delay(Uint32 ms) {
        SDL_Delay(ms);
    }
};

#endif // GRAPHICS_H