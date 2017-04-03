#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "SDL_utils.h"
#include "initiateObject.h"
#include "Object.h"
#include "display.h"

using namespace std;

const int SCREEN_WIDTH = 288;
const int SCREEN_HEIGHT = 490;
const int VELOCITY = 3;
const int GRAVITY = 2;

Object bird, background_1, background_2, ground_1, ground_2;
Object *UpBlock_1 = new Object, *DownBlock_1 = new Object,
       *UpBlock_2 = new Object, *DownBlock_2 = new Object;

void initiateEverything(SDL_Renderer* &renderer);

int main(int argc, char *argv[])
{
    srand(time(0));
    SDL_Window *window;
    SDL_Renderer *renderer;
    initSDL(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird");

    if (TTF_Init() < 0)
        cout << "Error: " << TTF_GetError() << endl;

    SDL_Texture *text = GetTextureOf(renderer, "Press SPACE to Play", 25);
    SDL_Rect textRect;
    SDL_QueryTexture(text, nullptr, nullptr, &textRect.w, &textRect.h);
    textRect.x = (SCREEN_WIDTH - textRect.w) / 2;
    textRect.y = 100;

    initiateEverything(renderer);

    SDL_Event event;
    bool gameOver = false, pressedSpace = false, isScore = true;
    int lastUpdate = 0, currentTime = 0;
    const Uint8 *keyState;
    int score = 0;

    while (!gameOver)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background_1.image, &background_1.frame, &background_1.position);
        SDL_RenderCopy(renderer, background_2.image, &background_2.frame, &background_2.position);
        SDL_RenderCopy(renderer, ground_1.image    , &ground_1.frame    , &ground_1.position);
        SDL_RenderCopy(renderer, ground_2.image    , &ground_2.frame    , &ground_2.position);

        updateObject(background_1, background_2);
        if (background_1.frame.w <= 0)
        {
            initiateBackground(renderer, background_1, background_2);
        }

        updateObject(ground_1, ground_2);
        if (ground_1.frame.w <= 0)
        {
            initiateGround(renderer, ground_1, ground_2, background_1);
        }

        currentTime = SDL_GetTicks();

        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
                gameOver = true;
            else if (event.type == SDL_KEYDOWN && !pressedSpace)
                if (event.key.keysym.sym == SDLK_SPACE)
                    pressedSpace = true;
        }

        if (currentTime - lastUpdate >= 150)
        {
            lastUpdate = currentTime;
            bird.frame.x += bird.frame.w;
            if (bird.frame.x >= bird.imgWidth)
            {
                bird.frame.x = 0;
            }
        }

        if (pressedSpace)
        {
            keyState = SDL_GetKeyboardState(nullptr);
            if (keyState[SDL_SCANCODE_SPACE])
            {
                bird.position.y -= 10;
            }
            bird.position.y += GRAVITY;
            if (bird.position.y <0) bird.position.y = 0;
            if (hitTheGrounds(bird, background_1)) gameOver = true;
            if (hitTheBlocks(bird, *UpBlock_1, *DownBlock_1)) gameOver = true;

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
                UpBlock_1 = UpBlock_2;
                DownBlock_1 = DownBlock_2;
                UpBlock_2 = new Object;
                DownBlock_2 = new Object;
                initiateBlock(renderer, *UpBlock_2, *DownBlock_2);
            }

            if (isScore && bird.position.x > UpBlock_1->position.x)
            {
                score++;
                isScore = false;
            }
            DisplayScore(renderer, score);
        }
        else SDL_RenderCopy(renderer, text, nullptr, &textRect);
        SDL_RenderCopy(renderer, bird.image        , &bird.frame        , &bird.position);
        SDL_RenderPresent(renderer);
    }

    int highestScore = getHighestScore();
    if (highestScore < score) saveScore(score);
    DisplayGameOver(renderer, score, highestScore);
    DisplayMedal(renderer, score);
    SDL_RenderPresent(renderer);

    cout << score << endl;
    waitUntilKeyPressed();

    quitSDL(window, renderer);
    SDL_DestroyTexture(text);
    delete UpBlock_1, DownBlock_1, UpBlock_2, DownBlock_2;
    IMG_Quit();
    TTF_Quit();
    return 0;
}

void initiateEverything(SDL_Renderer* &renderer)
{
    initiateBird(renderer, bird);

    background_1.image = loadTexture("data/bg.png", renderer);
    background_2.image = loadTexture("data/bg.png", renderer);
    initiateBackground(renderer, background_1, background_2);

    ground_1.image = loadTexture("data/ground.png", renderer);
    ground_2.image = loadTexture("data/ground.png", renderer);
    initiateGround(renderer, ground_1, ground_2, background_1);

    initiateBlock(renderer, *UpBlock_1, *DownBlock_1);
    initiateBlock(renderer, *UpBlock_2, *DownBlock_2);
}
