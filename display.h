#ifndef display__h
#define display__h
string ToString(int i);
SDL_Texture *GetTextureOf(SDL_Renderer* &renderer, const string PrintedText, int TextSize, const SDL_Color textColor);
void DisplayScore(SDL_Renderer* &renderer, const int score);
void saveScore(const int score);
int getHighestScore();
void DisplayGameOver(SDL_Renderer* &renderer, const int score);
void DisplayMedal(SDL_Renderer* &renderer, const int score);
#endif // display__h
