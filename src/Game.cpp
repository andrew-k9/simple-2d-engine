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
float projectileVelX = 10.0f;
float projectileVelY = 10.0;

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

/*
 * Timestep - how a computer view the render cycle
 * - This funtion says 'while the game is running, update'
 *   - How fast it loops depends on the machine's clock cycle
 * `projectile.position.x +=3` says every clock cycle, increment pos by 3
 *   - this is not consistent over multiple computers
 * delta time - (final - initial) how many ms from this frame to last frame?
 *   - SDL_GetTicks() since init, it counts how many tics elapsed in ms
 *   - deltaTime is the difference in ticks from last frame converted to seconds
 * What happens when we rener faster that the frame rate??
 *   - we need to delay the update until the time elapsed between frames is up!
 */
void Game::update(){
    // Wait untill 16ms ellapsed since last frame
    //SDL_Delay(16);
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));
    float deltaTime = ( SDL_GetTicks() - ticksLastFrame ) / 1000.0f;

    // Clamp delta time to max value
    deltaTime = (deltaTime > 20.0f) ? 0.05f : deltaTime;

    // Sets the new ticks for curr frame for the next pass
    ticksLastFrame = SDL_GetTicks();

    // the ` * deltaTime` smooths out the frame rate
    projectilePosX += projectileVelX * deltaTime;
    projectilePosY += projectileVelY * deltaTime;
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
