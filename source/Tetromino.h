#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>

class Tetromino
{
public:
	enum Type { I = 0, J, L, O, S, T, Z };
	Tetromino(Type);
	void draw(SDL_Renderer*);
	void move(int dx, int dy);
	void rotate();
	bool Block(int x, int y) const;
	int x() const;
	int y() const;
private:
	Type type_;
	int x_;
	int y_;
	int angle_; 
};
