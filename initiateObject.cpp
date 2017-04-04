#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Object.h"

using namespace std;

SDL_Texture* loadTexture(string filePath, SDL_Renderer* &renderTarget)
{
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (surface == nullptr)
        cout << "Error :" << SDL_GetError() << endl;
    else
    {
        texture = SDL_CreateTextureFromSurface(renderTarget, surface);
        if (texture == nullptr)
            cout << "Error :" << SDL_GetError() << endl;
    }
    SDL_FreeSurface(surface);
    return texture;
}

void updateObject(Object &object_1, Object &object_2)
{
    object_1.frame.x += VELOCITY;
    object_1.frame.w = object_1.position.w = object_1.frame.w - VELOCITY;
    object_2.position.x -= VELOCITY;
    object_2.frame.w = object_2.position.w = object_2.frame.w + VELOCITY;
}

void initiateGround(SDL_Renderer* &renderer, Object &ground_1, Object &ground_2, const Object &background_1)
{
    SDL_QueryTexture(ground_1.image, nullptr, nullptr, &ground_1.imgWidth, &ground_1.imgHeight);
    ground_1.position.y = background_1.frame.h;
    ground_1.position.x = 0;
    ground_1.position.w = ground_1.frame.w = background_1.frame.w;
    ground_1.position.h = ground_1.frame.h = SCREEN_HEIGHT - background_1.frame.h;
    ground_1.frame.x = ground_1.frame.y = 0;

    ground_2.position.x = ground_1.position.w;
    ground_2.position.y = ground_1.position.y;
    ground_2.position.h = ground_2.frame.h = ground_1.position.h;
    ground_2.frame.x = ground_2.frame.y = ground_2.frame.w = ground_2.position.w = 0;
}

void initiateBackground(SDL_Renderer* &renderer, Object &background_1, Object &background_2)
{
    SDL_QueryTexture(background_1.image, nullptr, nullptr, &background_1.imgWidth, &background_1.imgHeight);
    background_1.position.x = background_1.position.y = background_1.frame.x = background_1.frame.y = 0;
    background_1.position.w = background_1.frame.w = background_1.imgWidth;
    background_1.position.h = background_1.frame.h = background_1.imgHeight;

    background_2.position.x = background_1.position.w;
    background_2.position.y = 0;
    background_2.position.w = 0;
    background_2.position.h = background_2.frame.h = background_1.position.h;
    background_2.frame.x = background_2.frame.y = background_2.frame.w = 0;
}

void initiateBird(SDL_Renderer* &renderer, Object &bird)
{
    bird.image = loadTexture("data/bird.png", renderer);
    bird.position.x = SCREEN_WIDTH/3;
    bird.position.y = SCREEN_HEIGHT/3;
    bird.position.h = 32; bird.position.w = 36;
    SDL_QueryTexture(bird.image, nullptr, nullptr, &bird.imgWidth, &bird.imgHeight);
    bird.frame.w = bird.imgWidth / 3;
    bird.frame.h = bird.imgHeight;
    bird.frame.x = bird.frame.y = 0;
}

void updateBlock(SDL_Renderer* &renderer, Object &upBlock, Object &downBlock)
{
    upBlock.position.x = downBlock.position.x = upBlock.position.x - VELOCITY;
}

void initiateBlock(SDL_Renderer* &renderer, Object &upBlock, Object &downBlock)
{
    upBlock.image = loadTexture("data/tube1.png", renderer);
    SDL_QueryTexture(upBlock.image, nullptr, nullptr, &upBlock.imgWidth, &upBlock.imgHeight);
    upBlock.frame.w = upBlock.position.w = upBlock.imgWidth;
    upBlock.frame.h = upBlock.position.h = 40 + rand()%184;
    upBlock.frame.x = 0;
    upBlock.frame.y = upBlock.imgHeight - upBlock.frame.h;
    upBlock.position.x = SCREEN_WIDTH;
    upBlock.position.y = 0;

    downBlock.image = loadTexture("data/tube2.png", renderer);
    SDL_QueryTexture(downBlock.image, nullptr, nullptr, &downBlock.imgWidth, &downBlock.imgHeight);
    downBlock.frame.w = downBlock.position.w = downBlock.imgWidth;
    downBlock.frame.h = downBlock.position.h = 384 - upBlock.frame.h - 120;
    downBlock.frame.x = downBlock.frame.y = 0;
    downBlock.position.x = upBlock.position.x;
    downBlock.position.y = upBlock.position.h + 120;
}

bool hitTheBlocks(const Object &bird, const Object &UpBlock, const Object &DownBlock)
{
    if (bird.position.x + bird.position.w > DownBlock.position.x && bird.position.y + bird.position.h > DownBlock.position.y && bird.position.x + bird.position.w < DownBlock.position.x + DownBlock.position.w) return true;
    if (bird.position.x < DownBlock.position.x + DownBlock.position.w && bird.position.y + bird.position.h > DownBlock.position.y && bird.position.x > DownBlock.position.x) return true;
    if (bird.position.x + bird.position.w > UpBlock.position.x && bird.position.y < UpBlock.position.y + UpBlock.position.h && bird.position.x + bird.position.w < UpBlock.position.x + UpBlock.position.w) return true;
    if (bird.position.x > UpBlock.position.x && bird.position.y < UpBlock.position.y + UpBlock.position.h && bird.position.x < UpBlock.position.x + UpBlock.position.w) return true;
    return false;
}

bool hitTheGrounds(const Object &bird, const Object &background)
{
    return (bird.position.y >= background.imgHeight - bird.imgHeight);
}
