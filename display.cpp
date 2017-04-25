#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "initiateObject.h"

using namespace std;

string ToString(const int i)
{
    stringstream ss;
    ss << i;
    string str = ss.str();
    return str;
}

SDL_Texture *GetTextureOf(SDL_Renderer* &renderer, const string PrintedText, int TextSize,const SDL_Color textColor)
{
    TTF_Font *font = TTF_OpenFont(FONT_PATH.c_str(), TextSize);
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, PrintedText.c_str(), textColor);
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    return text;
}

//display text at (x,y)
void displayText(SDL_Renderer* &renderer, const string &textInput, const int x = 0, const int y = 0)
{
    SDL_Texture *text = GetTextureOf(renderer, textInput, 25, DEFAULT_COLOR);
    SDL_Rect textRect;
    SDL_QueryTexture(text, nullptr, nullptr, &textRect.w, &textRect.h);
    if (x == 0) textRect.x = (SCREEN_WIDTH - textRect.w) / 2;
    else textRect.x = x;
    textRect.y = y;
    SDL_RenderCopy(renderer, text, nullptr, &textRect);
    SDL_DestroyTexture(text);
}

//display score at (x,y)
void displayScore(SDL_Renderer* &renderer, const int score, const int x = 0, const int y = 20)
{
    string str = ToString(score);
    SDL_Texture *text = GetTextureOf(renderer, str, 25, DEFAULT_COLOR);
    SDL_Rect textRect;
    SDL_QueryTexture(text, nullptr, nullptr, &textRect.w, &textRect.h);
    if (x == 0)
    {
        textRect.x = (SCREEN_WIDTH - textRect.w) / 2;
        textRect.y = y;
    }
    else
    {
        textRect.x = x - textRect.w;
        textRect.y = y;
    }
    SDL_RenderCopy(renderer, text, nullptr, &textRect);
    SDL_DestroyTexture(text);
}

int getHighestScore()
{
    int highestScore;
    ifstream ifile(SCORE_PATH);
    if (ifile.is_open())
    {
        ifile >> highestScore;
    }
    else cout << "Unable to open data file" << endl;
    return highestScore;
}

void saveScore(const int score)
{
    ofstream ofile(SCORE_PATH);
    if (ofile.is_open())
    {
        ofile << score;
    }
    else cout << "Unable to open data file" << endl;
}

void displayMedal(SDL_Renderer* &renderer, const int score)
{
    MedalRank Rank;
    Object medal;
    medal.image = loadTexture("data/medals.png", renderer);
    medal.position.x = 56;
    medal.position.y = 190;
    medal.position.w = 50;
    medal.position.h = 60;
    SDL_QueryTexture(medal.image, nullptr, nullptr, &medal.imgWidth, &medal.imgHeight);
    if (score > GOLD_MEDAL_POINT_MIN) Rank = GOLD;
    else if (score > SILVER_MEDAL_POINT_MIN) Rank = SILVER;
    else Rank = BRONZE;
    medal.frame.w = medal.imgWidth/3;
    medal.frame.h = medal.imgHeight;
    medal.frame.x = medal.frame.w * Rank;
    medal.frame.y = 0;
    SDL_RenderCopy(renderer, medal.image, &medal.frame, &medal.position);
}

void displayGameover(SDL_Renderer* &renderer, const int score)
{
    SDL_Texture* gameOver = loadTexture("data/scoreboard.png", renderer);
    SDL_Rect scoreBoard;
    SDL_QueryTexture(gameOver, nullptr, nullptr, &scoreBoard.w, &scoreBoard.h);
    scoreBoard.x = (SCREEN_WIDTH - scoreBoard.w)/2;
    scoreBoard.y = 80;
    SDL_RenderCopy(renderer, gameOver, nullptr, &scoreBoard);

    displayScore(renderer, score, 230, 185);

    displayScore(renderer, getHighestScore(), 230, 225);

    displayMedal(renderer, score);

    SDL_DestroyTexture(gameOver);
}
