#include "game.h"
#include <iostream>

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

Game::Game(SDL_Window* window , SDL_Renderer* renderer ) :
    tetromino_{ static_cast<Tetromino::Type>(rand() % 7) },
    moveTime_(SDL_GetTicks())
{   

    this->window = window;
    this->renderer = renderer;
}

Game::~Game()
{
  //  SDL_DestroyRenderer(renderer);
  //  SDL_DestroyWindow(window);
  //  SDL_Quit();
  //  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  //  SDL_RenderClear(renderer);
}

bool Game::tick()
{

    SDL_Event e;
    if (SDL_WaitEventTimeout(&e, 250))
    {
        switch (e.type)
        {
        case SDL_KEYDOWN:
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_DOWN:
            {
                Tetromino t = tetromino_;
                t.move(0, 1);
                if (!well_.Collision(t))
                    tetromino_ = t;
            }
            break;
            case SDLK_RIGHT:
            {
                Tetromino t = tetromino_;
                t.move(1, 0);
                if (!well_.Collision(t))
                    tetromino_ = t;
            }
            break;
            case SDLK_LEFT:
            {
                Tetromino t = tetromino_;
                t.move(-1, 0);
                if (!well_.Collision(t))
                    tetromino_ = t;
            }
            break;
            case SDLK_UP:
            {
                Tetromino t = tetromino_;
                t.rotate();
                if (!well_.Collision(t))
                    tetromino_ = t;
            }
            break;
            case SDLK_ESCAPE:
            {
                outgame = true;

            }

            }

        }
        break;
        case SDL_QUIT:
        {
            outgame = true;

        }

        }

    }

    SDL_Rect Rect;
    Rect.x = 0;
    Rect.y = 0;
    Rect.w = 360;
    Rect.h = 720;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &Rect);
    //SDL_RenderClear(renderer);             
    well_.draw(renderer);
    tetromino_.draw(renderer);
    if (SDL_GetTicks() > moveTime_)
    {
        moveTime_ += 500;  
        Tetromino t = tetromino_;
        t.move(0, 1); 
        check(t);
    }
    SDL_RenderPresent(renderer);
    if (stop) {
        SDL_Delay(500);
        return false;
    }
    return true;
};

void Game::check(const Tetromino& t)
{
    if (well_.Collision(t))
    {
        well_.unite(tetromino_);

        tetromino_ = Tetromino{ static_cast<Tetromino::Type>(rand() % 7) };

        if (well_.Collision(tetromino_))
        {
            stop = true;
        }
    }
    else
    {
        tetromino_ = t;
    }
}
int Game:: mark()
{
    return well_.count;
}
