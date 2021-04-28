#pragma once

#include "Tetromino.h"

class Well
{
public:
	Well();
	void draw(SDL_Renderer*);
	enum { Width = 10, Height = 20 };
	bool Collision(const Tetromino& /*t*/) const;
	void unite(const Tetromino& );
	int  count = 0;

private:
	bool data[Width][Height];
	
};

