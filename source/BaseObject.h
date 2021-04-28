#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>


class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	virtual bool LoadImageFile(std::string path, SDL_Renderer* screen);
	void Free();
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
private:
	SDL_Texture* p_object_;
	SDL_Rect rect_;
};
#endif