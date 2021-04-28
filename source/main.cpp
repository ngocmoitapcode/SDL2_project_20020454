#include "game.h"
#include "Menu.h"
#include"PointCounter.h"

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

TTF_Font* g_font_MENU = NULL;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Surface* tempSurface = NULL;
SDL_Texture* texture = NULL;
SDL_Rect sourceRect;
SDL_Rect desRect;
TTF_Font* font = NULL;
Mix_Chunk* chunk = NULL;
Mix_Music* music = NULL;

const int RENDER_DRAW_COLOR = 0XFF;

bool InitData()
{
    bool sucess = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
        return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    window = SDL_CreateWindow("Tetris 2021",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL);

    if (window != NULL)
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer != NULL)
        {
            SDL_SetRenderDrawColor(renderer, RENDER_DRAW_COLOR,
                RENDER_DRAW_COLOR,
                RENDER_DRAW_COLOR,
                RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags))
                sucess = false;
        }
        if (TTF_Init() == -1)   {sucess = false;}

        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)    { sucess = false; }

        g_font_MENU = TTF_OpenFont("font//FFF_Tusj.ttf", 80);

        if (g_font_MENU == NULL)    {  return false; }

    }

    return sucess;
}

void close()
{
   
}
int main(int argc, char* argv[])
{
    if (InitData() == false)
    {
        return -1;
    }
    int ret_menu = function::ShowMenu(renderer, g_font_MENU, "Play Game", "Exit", "img//MENU.jpg");
    if (ret_menu != 0)
    {
        return 0;
    }
    if (ret_menu == 0)
    {   

    label:   
        Game* game = new Game(window , renderer );
      //  std::cout << game << std::endl;
        music = Mix_LoadMUS("sound//background.mp3");
        if (Mix_PlayMusic(music, -1) == -1)
        {
            return 1;
        }
        int start = SDL_GetTicks()/1000;
        int x = 0;
        bool time_up = false;

        while ((*game).tick() && !time_up )
        {   
            
            int point = (*game).mark() / 180;
            tempSurface = IMG_Load("img//back.jpg");
            texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
            SDL_FreeSurface(tempSurface);
            SDL_QueryTexture(texture, NULL, NULL, &sourceRect.w, &sourceRect.h);
            sourceRect.x = 0;
            desRect.x = 360;
            sourceRect.y = 0;
            desRect.y = 0;
            desRect.w = sourceRect.w;  
            desRect.h = sourceRect.h;
            SDL_RenderCopy(renderer, texture, &sourceRect, &desRect);

            int current = SDL_GetTicks()/1000;
            bool ret = PointCounter::ShowPoint(renderer, font, "SCORE", "TIME", SCREEN_WIDTH, SCREEN_HEIGHT, point,  current - start );
            if (point > x) {
                chunk = Mix_LoadWAV("sound//ting.wav");
                if (chunk != NULL)
                    Mix_PlayChannel(-1, chunk, 0);
            }
            x = point;
            if ((game)->outgame == true) return 0;
           
            if (current - start >= 60)   time_up = true;
        };

        Mix_FreeChunk(chunk);
        TTF_CloseFont(font);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        Mix_CloseAudio();
        SDL_Quit();

        delete game;


        if (InitData() == false){ return -1;}
        int ret_menu = function::ShowMenu(renderer, g_font_MENU, "Play Again", "Exit", "img//END.jpg");
        if (ret_menu != 0) return 0;
        else { goto label;}
    }
	return 0;
}
