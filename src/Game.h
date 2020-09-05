#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Game{
    public:
        Game();
        ~Game();
        bool isRunning() const;
        void initialize(int width, int height);
        void processInput();
        void update();
        void render();
        void destroy();
    private:
        bool running;
        SDL_Renderer *renderer;
        SDL_Window *window;
};

#endif
