#ifndef display__h
#define display__h

string ToString(int i);

SDL_Texture *GetTextureOf(SDL_Renderer* &renderer, const string PrintedText, int TextSize, const SDL_Color textColor);
void displayScore(SDL_Renderer* &renderer, const int score);
void saveScore(const int score);
int getHighestScore();

void displayGameover(SDL_Renderer* &renderer, const int score);
void displayMedal(SDL_Renderer* &renderer, const int score);

#endif // display__h
