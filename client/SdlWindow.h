#ifndef __SDL_WINDOW_H__
#define __SDL_WINDOW_H__

class SDL_Window;
class SDL_Renderer;
class SDL_Texture;

class SdlWindow {
public:
    SdlWindow(int width, int height);
    ~SdlWindow();
    void fill(int r, int g, int b, int alpha);
    void render();
    SDL_Renderer* getRenderer() const;
private:
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif