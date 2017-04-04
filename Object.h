#ifndef Object__h
#define Object__h
struct Object
{
    SDL_Rect position, frame;
    SDL_Texture *image = nullptr;
    int imgWidth, imgHeight;
};

enum MedalRank
{
    GOLD,
    SILVER,
    BRONZE
};


const int SCREEN_WIDTH = 288;
const int SCREEN_HEIGHT = 490;
const int VELOCITY = 2;
const int GRAVITY = 2;

const int GOLD_MEDAL_POINT = 30;
const int SILVER_MEDAL_POINT = 20;

const SDL_Color CYAN_COLOR = {0, 255, 255};
const SDL_Color BLUE_COLOR = {0, 0, 255};
const SDL_Color ORANGE_COLOR = {255, 165, 0};
const SDL_Color YELLOW_COLOR = {255, 255, 0};
const SDL_Color LIME_COLOR = {0, 255, 0};
const SDL_Color PURPLE_COLOR = {128, 0, 128};
const SDL_Color RED_COLOR = {255, 0, 0};
const SDL_Color WHITE_COLOR = {255, 255, 255};
const SDL_Color BLACK_COLOR = {0, 0, 0};
const SDL_Color GREEN_COLOR = {0, 128, 0};

const SDL_Color DEFAULT_COLOR = BLACK_COLOR;
#endif // Object__h

