#include "Tetromino.h"

Tetromino::Tetromino(Type type) :
    type_(type),
    x_(3),
    y_(0),
    angle_(0)
{}

void Tetromino::draw(SDL_Renderer* renderer)
{
    switch (type_)
    {
    case I:
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        break;
    case J:
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        break;
    case L:
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        break;
    case O:
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        break;
    case S:
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        break;
    case T:
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        break;
    case Z:
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        break;
    }

    for (auto x = 0; x < 4; ++x)
        for (auto y = 0; y < 4; ++y)
            if (Block(x, y))
            {
                SDL_Rect rect{ (x + x_) * 720 / 2 / 10 + 1, (y + y_) * 720 / 2 / 10 + 1, 720 / 2 / 10 - 2, 720 / 2 / 10 - 2 };
                SDL_RenderFillRect(renderer, &rect);
            }
}

void Tetromino::move(int dx, int dy)
{
    x_ += dx;
    y_ += dy;
}
void Tetromino::rotate() 
{
    angle_ += 3;
    angle_ %= 4;
}

bool Tetromino::Block(int x, int y) const
{
    static const char* Shapes[][4] = {
      {
        " *  "
        " *  "
        " *  "
        " *  ",
        "    "
        "****"
        "    "
        "    ",
        " *  "
        " *  "
        " *  "
        " *  ",
        "    "
        "****"
        "    "
        "    ",
      },
      {
        "  * "
        "  * "
        " ** "
        "    ",
        "    "
        "*   "
        "*** "
        "    ",
        " ** "
        " *  "
        " *  "
        "    ",
        "    "
        "    "
        "*** "
        "  * ",
      },
      {
        " *  "
        " *  "
        " ** "
        "    ",
        "    "
        "*** "
        "*   "
        "    ",
        " ** "
        "  * "
        "  * "
        "    ",
        "  * "
        "*** "
        "    "
        "    ",
      },
      {
        "    "
        " ** "
        " ** "
        "    ",
        "    "
        " ** "
        " ** "
        "    ",
        "    "
        " ** "
        " ** "
        "    ",
        "    "
        " ** "
        " ** "
        "    ",
      },
      {
        "  * "
        " ** "
        " *  "
        "    ",
        "    "
        "**  "
        " ** "
        "    ",
        "  * "
        " ** "
        " *  "
        "    ",
        "    "
        "**  "
        " ** "
        "    ",
      },
      {
        " *  "
        " ** "
        " *  "
        "    ",
        "    "
        "*** "
        " *  "
        "    ",
        " *  "
        "**  "
        " *  "
        "    ",
        " *  "
        "*** "
        "    "
        "    ",
      },
      {
        " *  "
        " ** "
        "  * "
        "    ",
        "    "
        " ** "
        "**  "
        "    ",
        " *  "
        " ** "
        "  * "
        "    ",
        "    "
        " ** "
        "**  "
        "    ",
      },
    };
    return Shapes[type_][angle_][x + y * 4] == '*';
}
int Tetromino::x() const
{
    return x_;
}
int Tetromino::y() const
{
    return y_;
}
