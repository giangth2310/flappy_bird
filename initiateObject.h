#ifndef initiateObject__h
#define initiateObject__h
#include "Object.h"

using namespace std;

SDL_Texture* loadTexture(const string& filePath, SDL_Renderer* &renderTarget);

void initBird(SDL_Renderer* &renderer, Object &bird);
void initBackground(SDL_Renderer* &renderer, Object &background_1, Object &background_2);
void initGround(SDL_Renderer* &renderer, Object &ground_1, Object &ground_2, const Object &background_1);
void initBlock(SDL_Renderer* &renderer, Object &upBlock, Object &downBlock, const int groundHeight);

void updateObject(Object &object_1, Object &object_2);
void updateBlock(SDL_Renderer* &renderer, Object &upBlock, Object &downBlock);

bool hitTheBlocks(const Object &bird, const Object &UpBlock, const Object &DownBlock);
bool hitTheGrounds(const Object &bird, const Object &background);

#endif // initiateObject__h
