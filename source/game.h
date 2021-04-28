#include "well.h"
#include <iostream>

class Game
{
public:
	Game(SDL_Window* , SDL_Renderer* );
	~Game();
	bool tick();
	void exit();
	bool stop = false;
	bool outgame = false;
	int mark();

private:
	
	SDL_Window* window;
	SDL_Renderer* renderer;
	Well well_;
	Tetromino tetromino_;
	uint32_t moveTime_;
	void check(const Tetromino&);
};
