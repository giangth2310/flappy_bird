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
#endif // Object__h

