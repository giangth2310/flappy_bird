#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "initiateObject.h"

const int SCREEN_WIDTH = 288;
const int SCREEN_HEIGHT = 490;

using namespace std;

string ToString(int i)
{
    stringstream ss;
    ss << i;
    string str = ss.str();
    return str;
}

SDL_Texture *GetTextureOf(SDL_Renderer* &renderer, const string s, int TextSize)
{
    TTF_Font *font = TTF_OpenFont("data/04B_19__.TTF", TextSize);
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, s.c_str(), textColor);
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    return text;
}

void DisplayScore(SDL_Renderer* &renderer, const int score)
{
    string str = ToString(score);
    SDL_Texture *text = GetTextureOf(renderer, str, 25);
    SDL_Rect textRect;
    SDL_QueryTexture(text, nullptr, nullptr, &textRect.w, &textRect.h);
    textRect.x = (SCREEN_WIDTH - textRect.w) / 2;
    textRect.y = 20;
    SDL_RenderCopy(renderer, text, nullptr, &textRect);
    SDL_DestroyTexture(text);
}

int getHighestScore()
{
    int highestScore;
    ifstream ifile("data/score.txt");
    if (ifile.is_open())
    {
        ifile >> highestScore;
    }
    else cout << "Unable to open data file" << endl;
    return highestScore;
}

void saveScore(const int score)
{
    ofstream ofile("data/score.txt");
    if (ofile.is_open())
    {
        ofile << score;
    }
    else cout << "Unable to open data file" << endl;
}

void DisplayGameOver(SDL_Renderer* &renderer, const int score, const int highestScore)
{
    SDL_Texture* gameOver = loadTexture("data/scoreboard.png", renderer);
    SDL_Rect scoreBoard;
    SDL_QueryTexture(gameOver, nullptr, nullptr, &scoreBoard.w, &scoreBoard.h);
    scoreBoard.x = (SCREEN_WIDTH - scoreBoard.w)/2;
    scoreBoard.y = 80;
    SDL_RenderCopy(renderer, gameOver, nullptr, &scoreBoard);

    string str = ToString(score);
    SDL_Texture *text = GetTextureOf(renderer, str, 25);
    SDL_Rect textRect;
    SDL_QueryTexture(text, nullptr, nullptr, &textRect.w, &textRect.h);
    textRect.x = 230 - textRect.w;
    textRect.y = 185;
    SDL_RenderCopy(renderer, text, nullptr, &textRect);
    SDL_DestroyTexture(text);

    str = ToString(highestScore);
    text = GetTextureOf(renderer, str, 25);
    SDL_QueryTexture(text, nullptr, nullptr, &textRect.w, &textRect.h);
    textRect.x = 230 - textRect.w;
    textRect.y = 225;
    SDL_RenderCopy(renderer, text, nullptr, &textRect);
    SDL_DestroyTexture(text);

    SDL_DestroyTexture(gameOver);
}

void DisplayMedal(SDL_Renderer* &renderer, const int score)
{
    MedalRank Rank;
    Object medal;
    medal.image = loadTexture("data/medals.png", renderer);
    medal.position.x = 56;
    medal.position.y = 190;
    medal.position.w = 50;
    medal.position.h = 60;
    SDL_QueryTexture(medal.image, nullptr, nullptr, &medal.imgWidth, &medal.imgHeight);
    if (score > 30) Rank = GOLD;
    else if (score > 20) Rank = SILVER;
    else Rank = BRONZE;
    medal.frame.w = medal.imgWidth/3;
    medal.frame.h = medal.imgHeight;
    medal.frame.x = medal.frame.w * Rank;
    medal.frame.y = 0;
    SDL_RenderCopy(renderer, medal.image, &medal.frame, &medal.position);
}
