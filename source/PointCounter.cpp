#include "PointCounter.h"

bool PointCounter::ShowPoint(SDL_Renderer* renderer, TTF_Font* font,
    const std::string& option1,
    const std::string& option2,
    const int SCREEN_WIDTH,
    const int SCREEN_HEIGHT,
    int point, int start_time)
{
    
    std::string option3 = std::to_string(point);
    std::string option4 = std::to_string(start_time);
    

    font = TTF_OpenFont("font//PTC75F.ttf", 80);

    char* ch1 = (char*)option1.c_str();
    char* ch2 = (char*)option2.c_str();
    char* ch3 = (char*)option3.c_str();
    char* ch4 = (char*)option4.c_str();

    int size1 = option1.length();
    int size2 = option2.length();
    int size3 = option3.length();
    int size4 = option4.length();

    int x = 0;
    int y = 0;
    const int Rows = 4;
    char* labels[Rows];

    labels[0] = new char[size1 + 1];
    labels[1] = new char[size2 + 1];
    labels[2] = new char[size3 + 1];
    labels[3] = new char[size4 + 1];

    strcpy_s(labels[0], size1 + 1, ch1);
    strcpy_s(labels[1], size2 + 1, ch2);
    strcpy_s(labels[2], size3 + 1, ch3);
    strcpy_s(labels[3], size4 + 1, ch4);

    SDL_Color color[4] = { { 0, 255, 0 },{ 255, 255, 0 }, { 255, 255, 255 } , { 255, 255, 255 }  };

    TextObject text_object[Rows];
    
    text_object[0].SetText(labels[0]);
    text_object[0].setColor(color[0].r, color[0].g, color[0].b);
    text_object[0].loadFromRenderedText(font, renderer);
    text_object[0].RenderText(renderer, (SCREEN_WIDTH + 360 - text_object[0].getWidth()) / 2 - 150 , 40);

    
    text_object[1].SetText(labels[1]);
    text_object[1].setColor(color[1].r, color[1].g, color[1].b);
    text_object[1].loadFromRenderedText(font, renderer);
    text_object[1].RenderText(renderer, (SCREEN_WIDTH + 360 - text_object[1].getWidth()) / 2 - 150 , 200);

    
    text_object[2].SetText(labels[2]);
    text_object[2].setColor(color[2].r, color[2].g, color[2].b);
    text_object[2].loadFromRenderedText(font, renderer);
    text_object[2].RenderText(renderer, (SCREEN_WIDTH + 360 - text_object[2].getWidth()) / 2 - 150 ,  120);

    
    text_object[3].SetText(labels[3]);
    text_object[3].setColor(color[3].r, color[3].g, color[3].b);
    text_object[3].loadFromRenderedText(font, renderer);
    text_object[3].RenderText(renderer, (SCREEN_WIDTH + 360 - text_object[3].getWidth()) / 2 - 150 ,  280);

    SDL_RenderPresent(renderer);
    return true;
}