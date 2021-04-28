#include "Menu.h"

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;



int function::ShowMenu(SDL_Renderer* g_screen, TTF_Font* font, const std::string& menu1,const std::string& menu2,const std::string& img_name)
{
    char* ch1 = (char*)menu1.c_str();
    char* ch2 = (char*)menu2.c_str();
    char* img_file = (char*)img_name.c_str();

    int size1 = menu1.length();
    int size2 = menu2.length();

    int time = 0;
    int x = 0;
    int y = 0;
    const int Menu_Number = 2;
    char* labels[Menu_Number];

    labels[0] = new char[size1 + 1];
    labels[1] = new char[size2 + 1];

    strcpy_s(labels[0], size1 + 1, ch1);
    strcpy_s(labels[1], size2 + 1, ch2);

    SDL_Texture* menu[Menu_Number];
    bool selected[Menu_Number] = { 0, 0 };
    SDL_Color color[2] = { { 255, 255, 255 },{ 255, 0, 0 } };

    TextObject text_object[Menu_Number];
    text_object[0].SetText(labels[0]);
    text_object[0].setColor(color[0].r, color[0].g, color[0].b);
    text_object[0].loadFromRenderedText(font, g_screen);

    text_object[1].SetText(labels[1]);
    text_object[1].setColor(color[0].r, color[0].g, color[0].b);
    text_object[1].loadFromRenderedText(font, g_screen);


    SDL_Rect pos[Menu_Number];
    pos[0].x = SCREEN_WIDTH * 0.3 - 150;
    pos[0].y = SCREEN_HEIGHT * 0.8 - 40;
    pos[1].x = SCREEN_WIDTH * 0.3 - 150;
    pos[1].y = SCREEN_HEIGHT * 0.8 + 40;

    BaseObject Background;
    bool ret = Background.LoadImageFile(img_file, g_screen);

    SDL_Event event;
    while (1)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                text_object[0].Free();
                text_object[0].Free();
                Background.Free();
                return 1;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                for (int i = 0; i < Menu_Number; ++i)
                {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        if (!selected[i])
                        {
                            selected[i] = 1;
                            text_object[i].SetText(labels[i]);
                            text_object[i].setColor(color[1].r, color[1].g, color[1].b);
                            text_object[i].loadFromRenderedText(font, g_screen);
                        }
                    }
                    else
                    {
                        if (selected[i])
                        {
                            selected[i] = 0;
                            text_object[i].Free();
                            text_object[i].SetText(labels[i]);
                            text_object[i].setColor(color[0].r, color[0].g, color[0].b);
                            text_object[i].loadFromRenderedText(font, g_screen);
                        }
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < Menu_Number; ++i) {
                    if (x >= pos[i].x && x <= pos[i].x + pos[i].w &&
                        y >= pos[i].y && y <= pos[i].y + pos[i].h)
                    {
                        text_object[0].Free();
                        text_object[1].Free();
                        Background.Free();
                        return i;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    text_object[0].Free();
                    text_object[1].Free();
                    Background.Free();
                    return 1;
                }
            }
        }

        Background.Render(g_screen, NULL);

        for (int i = 0; i < Menu_Number; ++i)
        {
            text_object[i].RenderText(g_screen, pos[i].x, pos[i].y);
            pos[i].w = text_object[i].getWidth();
            pos[i].h = text_object[i].getHeight();
        }
        SDL_RenderPresent(g_screen);       
    }

    return 0;
}

