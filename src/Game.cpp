#include <iostream>

#include "./Constants.h"
#include "./Game.h"

Game::Game(){
    this->running = false;
}

Game::~Game(){
}

bool Game::isRunning() const {
    return this->running;
}

// velocity is measured in pixels per frame per second
float projectilePosX = 0.0f;
float projectilePosY = 0.0f;
float projectileVelX = 0.05f;
float projectileVelY = 0.05f;

void Game::initialize(int width, int height){
    if( SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cerr << "Error init SDL!" << std::endl;
        return;
    }
    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_BORDERLESS
    );
    if( !window ){
        std::cerr << "Error creating SDL window" << std:: endl;
        return;
    }
    // -1: default driver to render
    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }
    running = true;
    return;
}

void Game::processInput(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch(event.type){
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN: 
            if(event.key.keysym.sym == SDLK_ESCAPE){
                running = false;
            }
            break;
        default:
            break;       
    }   
    return;
}

void Game::update(){
    projectilePosX += projectileVelX;
    projectilePosY += projectileVelY;
}

void Game::render(){
    // numbers are rgb and opacity
    SDL_SetRenderDrawColor(renderer, 21,21,21,255);
    SDL_RenderClear(renderer);

    SDL_Rect projectile{
        (int) projectilePosX,
        (int) projectilePosY,
        10,
        10
    };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &projectile);

    SDL_RenderPresent(renderer);
}

void Game::destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
