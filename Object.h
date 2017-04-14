#ifndef Object__h
#define Object__h
#include <SDL.h>

using namespace std;

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

const int FPS = 60;

const int GOLD_MEDAL_POINT_MIN   = 30;
const int SILVER_MEDAL_POINT_MIN = 20;


const int SCREEN_WIDTH  = 288;
const int SCREEN_HEIGHT = 490;
const string WINDOW_TITLE = "Flappy bird";

const SDL_Rect BIRD_START_POSITION = {SCREEN_WIDTH/3, SCREEN_HEIGHT/3, 36, 32};
const int BIRD_ANIMATION_IMG = 3;
const int VELOCITY           = 2;
const int GRAVITY            = 2;

const int MIN_BLOCK_HEIGHT       = 40;
const int HEIGHT_BETWEEN_2_BLOCK = 120;

const string BIRD_IMG_PATH       = "data/bird.png";
const string UPBLOCK_IMG_PATH    = "data/tube1.png";
const string DOWNBLOCK_IMG_PATH  = "data/tube2.png";
const string BACKGROUND_IMG_PATH = "data/bg.png";
const string GROUND_IMG_PATH     = "data/ground.png";
const string FONT_PATH           = "data/04B_19__.TTF";
const string SCORE_PATH          = "data/score.txt";

const SDL_Color CYAN_COLOR   = {  0, 255, 255};
const SDL_Color BLUE_COLOR   = {  0,   0, 255};
const SDL_Color ORANGE_COLOR = {255, 165,   0};
const SDL_Color YELLOW_COLOR = {255, 255,   0};
const SDL_Color LIME_COLOR   = {0  , 255,   0};
const SDL_Color PURPLE_COLOR = {128,   0, 128};
const SDL_Color RED_COLOR    = {255,   0,   0};
const SDL_Color WHITE_COLOR  = {255, 255, 255};
const SDL_Color BLACK_COLOR  = {  0,   0,   0};
const SDL_Color GREEN_COLOR  = {  0, 128,   0};

const SDL_Color DEFAULT_COLOR = BLACK_COLOR;
#endif // Object__h

