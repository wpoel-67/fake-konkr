#include "graphics.h"

/**
 * @Author: Léo Piveteau-Wernert
 * 
 */

Graphics::Graphics()
    : width(0), height(0),
    window(nullptr, SDL_DestroyWindow),
    renderer(nullptr, SDL_DestroyRenderer),
    cursor_hand(nullptr, SDL_FreeCursor),
    cursor_arrow(nullptr, SDL_FreeCursor),
    hexagon_image(nullptr, SDL_FreeSurface),
    hexagon_texture(nullptr, SDL_DestroyTexture) {}

Graphics::~Graphics() {
    fonts.clear();
    images.clear();
    image_textures.clear();
    text_textures.clear();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Graphics::init(const std::string& title, int width, int height) {
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    if(TTF_Init() != 0) {
        std::cerr << "Error: " << TTF_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    this->width = width;
    this->height = height;

    window.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN));
    if(!window) {
        std::cerr << "Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
    if(!renderer) {
        std::cerr << "Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    cursor_hand.reset(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
    if(!cursor_hand) {
        std::cerr << "Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    cursor_arrow.reset(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
    if(!cursor_arrow) {
        std::cerr << "Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "Error: " << IMG_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    hexagon_image.reset(IMG_Load("img/grey_hexagon.png"));
    if(!hexagon_image) {
        std::cerr << "Error: " << IMG_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    hexagon_texture.reset(SDL_CreateTextureFromSurface(renderer.get(), hexagon_image.get()));
    if(!hexagon_texture) {
        std::cerr << "Error: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Graphics::clear() {
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
    SDL_RenderClear(renderer.get());
}

void Graphics::update() {
    SDL_RenderPresent(renderer.get());
}

void Graphics::drawPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    if(x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }
    SDL_SetRenderDrawColor(renderer.get(), r, g, b, 255);
    SDL_RenderDrawPoint(renderer.get(), x, y);
}

void Graphics::drawLine(int x1, int y1, int x2, int y2, uint8_t r, uint8_t g, uint8_t b) {
    SDL_SetRenderDrawColor(renderer.get(), r, g, b, 255);
    SDL_RenderDrawLine(renderer.get(), x1, y1, x2, y2);
}

void Graphics::drawRect(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b) {
    SDL_Rect rect = {x - w / 2, y - h / 2, w, h};
    SDL_SetRenderDrawColor(renderer.get(), r, g, b, 255);
    SDL_RenderFillRect(renderer.get(), &rect);
}

void Graphics::drawHexagon(int x, int y, double radius, uint8_t r, uint8_t g, uint8_t b) {
    double angle = 0, theta = kPi / 3; // 60 degrees
    for(int i = 0; i < 6; i++) {
        double x1 = x + radius * cos(angle);
        double y1 = y + radius * sin(angle);
        double x2 = x + radius * cos(angle + theta);
        double y2 = y + radius * sin(angle + theta);
        drawLine(x1, y1, x2, y2, r, g, b);
        angle += theta;
    }
}

void Graphics::drawHexagonTexture(int x, int y, int radius, uint8_t r, uint8_t g, uint8_t b) {
    if(!hexagon_texture) {
        std::cerr << "Hexagon texture not initialized!" << std::endl;
        return;
    }
    SDL_SetTextureColorMod(hexagon_texture.get(), r, g, b);
    SDL_Rect rect = {x - radius, y - radius, 2 * radius, 2 * radius};
    SDL_RenderCopy(renderer.get(), hexagon_texture.get(), nullptr, &rect);
}

void Graphics::drawText(int x, int y, const std::string& text,
    uint8_t r, uint8_t g, uint8_t b, uint size) {
    
    std::string key = text + "_" + std::to_string(size) + "_" + 
                      std::to_string(r) + "_" + std::to_string(g) + "_" + std::to_string(b);

    auto tex_it = text_textures.find(key);
    if(tex_it == text_textures.end()) {
        auto font_it = fonts.find(size);
        if(font_it == fonts.end()) {
            auto new_font = std::shared_ptr<TTF_Font>(TTF_OpenFont("font/Arial.ttf", size), TTF_CloseFont);
            if(!new_font) {
                std::cerr << "Error: " << TTF_GetError() << std::endl;
                exit(EXIT_FAILURE);
            }
            font_it = fonts.emplace(size, std::move(new_font)).first;
        }

        SDL_Color color = {r, g, b, 255};
        std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)> surface(
            TTF_RenderUTF8_Solid(font_it->second.get(), text.c_str(), color), SDL_FreeSurface);
        if(!surface) {
            std::cerr << "Error: " << TTF_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }

        std::shared_ptr<SDL_Texture> texture(
            SDL_CreateTextureFromSurface(renderer.get(), surface.get()), SDL_DestroyTexture);
        if(!texture) {
            std::cerr << "Error: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        tex_it = text_textures.emplace(key, std::move(texture)).first;
    }

    int w = 0, h = 0;
    SDL_QueryTexture(tex_it->second.get(), nullptr, nullptr, &w, &h);
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(renderer.get(), tex_it->second.get(), nullptr, &rect);
}

TextSize Graphics::textSize(const std::string& text, uint size) {
    TextSize ts;
    auto it = fonts.find(size);
    if(it == fonts.end()) {
        auto font = std::shared_ptr<TTF_Font>(TTF_OpenFont("font/Arial.ttf", size), TTF_CloseFont);
        if(!font) {
            std::cerr << "Error: " << TTF_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        it = fonts.emplace(size, std::move(font)).first;
    }
    TTF_SizeUTF8(it->second.get(), text.c_str(), &ts.w, &ts.h);
    return ts;
}

void Graphics::drawImage(const std::string& path, int x, int y, int radius) {
    auto it = images.find(path);
    if(it == images.end()) {
        auto surface = std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)>(IMG_Load(path.c_str()), SDL_FreeSurface);
        if(!surface) {
            std::cerr << "Error: " << IMG_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        it = images.emplace(path, std::move(surface)).first;
    }
    auto it2 = image_textures.find(path);
    if(it2 == image_textures.end()) {
        auto texture = std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>(SDL_CreateTextureFromSurface(renderer.get(), it->second.get()), SDL_DestroyTexture);
        if(!texture) {
            std::cerr << "Error: " << SDL_GetError() << std::endl;
            exit(EXIT_FAILURE);
        }
        it2 = image_textures.emplace(path, std::move(texture)).first;
    }
    SDL_Rect rect = {x - radius, y - radius, 2 * radius, 2 * radius};
    SDL_RenderCopy(renderer.get(), it2->second.get(), nullptr, &rect);
}

void Graphics::setHandCursor() {
    SDL_SetCursor(cursor_hand.get());
}

void Graphics::setArrowCursor() {
    SDL_SetCursor(cursor_arrow.get());
}


