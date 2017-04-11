#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "SDL_utils.h"
#include "initiateObject.h"
#include "Object.h"
#include "display.h"

using namespace std;

    Object bird, background_1, background_2, ground_1, ground_2;
    Object *UpBlock_1 = new Object, *DownBlock_1 = new Object,
           *UpBlock_2 = new Object, *DownBlock_2 = new Object;

void init(SDL_Renderer* &renderer);
bool play(SDL_Renderer* &renderer);
bool tryAgain(SDL_Renderer* &renderer);

int main(int argc, char *argv[])
{
    srand(time(0));
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE.c_str());

    do
    {
        if (play(renderer)) break;
    }
    while (tryAgain(renderer));

    delete UpBlock_1, DownBlock_1, UpBlock_2, DownBlock_2;
    quitSDL(window, renderer);
    return 0;
}

void init(SDL_Renderer* &renderer)
{
    initBird(renderer, bird);

    background_1.image = loadTexture(BACKGROUND_IMG_PATH.c_str(), renderer);
    background_2.image = loadTexture(BACKGROUND_IMG_PATH.c_str(), renderer);
    initBackground(renderer, background_1, background_2);

    ground_1.image = loadTexture(GROUND_IMG_PATH.c_str(), renderer);
    ground_2.image = loadTexture(GROUND_IMG_PATH.c_str(), renderer);
    initGround(renderer, ground_1, ground_2, background_1);

    initBlock(renderer, *UpBlock_1, *DownBlock_1, ground_1.position.h);
    initBlock(renderer, *UpBlock_2, *DownBlock_2, ground_1.position.h);
}

bool play(SDL_Renderer* &renderer)
{
    init(renderer);

    Mix_Chunk *wing  = Mix_LoadWAV("data/wing.wav");
    Mix_Chunk *point = Mix_LoadWAV("data/point.wav");
    Mix_Chunk *hit   = Mix_LoadWAV("data/hit.wav");

    SDL_Event event;
    bool gameOver = false, pressedSpace = false, isScore = true;
    int lastUpdate = 0, currentTime = 0;
    const Uint8 *keyState = nullptr;
    int score = 0;

    while (!gameOver)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_1.image, &background_1.frame, &background_1.position);
        SDL_RenderCopy(renderer, background_2.image, &background_2.frame, &background_2.position);
        SDL_RenderCopy(renderer, ground_1.image    , &ground_1.frame    , &ground_1.position);
        SDL_RenderCopy(renderer, ground_2.image    , &ground_2.frame    , &ground_2.position);
        //make background and ground endless moving
        updateObject(background_1, background_2);
        if (background_1.frame.w <= 0)
        {
            initBackground(renderer, background_1, background_2);
        }

        updateObject(ground_1, ground_2);
        if (ground_1.frame.w <= 0)
        {
            initGround(renderer, ground_1, ground_2, background_1);
        }

        currentTime = SDL_GetTicks();

        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
                return true;
            else if (event.type == SDL_KEYDOWN)
                if (event.key.keysym.sym == SDLK_SPACE)
                    if (!pressedSpace)
                    {
                        pressedSpace = true;
                    } else Mix_PlayChannel(-1, wing, 0);
        }
        //handle bird animation
        if (currentTime - lastUpdate >= 150)
        {
            lastUpdate = currentTime;
            bird.frame.x += bird.frame.w;
            if (bird.frame.x >= bird.imgWidth)
            {
                bird.frame.x = 0;
            }
        }
        //game start
        if (pressedSpace)
        {
            keyState = SDL_GetKeyboardState(nullptr);
            if (keyState[SDL_SCANCODE_SPACE])
            {
                bird.position.y -= 10;
            }
            bird.position.y += GRAVITY;
            if (bird.position.y <0) bird.position.y = 0;
            if (hitTheGrounds(bird, background_1))
            {
                gameOver = true;
                Mix_HaltChannel(-1);
                Mix_PlayChannel(-1, hit, 0);
            }
            if (hitTheBlocks(bird, *UpBlock_1, *DownBlock_1))
            {
                gameOver = true;
                Mix_HaltChannel(-1);
                Mix_PlayChannel(-1, hit, 0);
            }

            updateBlock(renderer, *UpBlock_1, *DownBlock_1);
            SDL_RenderCopy(renderer, UpBlock_1->image  , &UpBlock_1->frame  , &UpBlock_1->position);
            SDL_RenderCopy(renderer, DownBlock_1->image, &DownBlock_1->frame, &DownBlock_1->position);

            if (UpBlock_1->position.x <= 0)
            {
                updateBlock(renderer, *UpBlock_2, *DownBlock_2);
                SDL_RenderCopy(renderer, UpBlock_2->image  , &UpBlock_2->frame  , &UpBlock_2->position);
                SDL_RenderCopy(renderer, DownBlock_2->image, &DownBlock_2->frame, &DownBlock_2->position);
            }

            if (UpBlock_1->position.x + UpBlock_1->position.w <=0)
            {
                isScore = true;
                delete UpBlock_1, DownBlock_1;
                UpBlock_1   = UpBlock_2;
                DownBlock_1 = DownBlock_2;
                UpBlock_2   = new Object;
                DownBlock_2 = new Object;
                initBlock(renderer, *UpBlock_2, *DownBlock_2, ground_1.position.h);
            }

            if (isScore && bird.position.x > UpBlock_1->position.x)
            {
                score++;
                isScore = false;
                Mix_PlayChannel(-1, point, 0);
            }
            displayScore(renderer, score);
        }
        else displayText(renderer, "Press SPACE to play", 0, 100);
        SDL_RenderCopy(renderer, bird.image, &bird.frame, &bird.position);
        SDL_RenderPresent(renderer);
    }

    int highestScore = getHighestScore();
    if (highestScore < score) saveScore(score);

    displayGameover(renderer, score);
    SDL_RenderPresent(renderer);

    SDL_Delay(500);

    Mix_FreeChunk(wing);
    Mix_FreeChunk(point);
    Mix_FreeChunk(hit);
    return false;
}

bool tryAgain(SDL_Renderer* &renderer)
{
    displayText(renderer, "Play again ? (y/n)", 0, 300);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_WaitEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
            return false;
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_y)
                return true;
            if (event.key.keysym.sym == SDLK_n)
                return false;
        }
    }
}
