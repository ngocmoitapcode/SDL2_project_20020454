#include "BaseObject.h"
#include "TextObject.h"

namespace PointCounter
{
	bool ShowPoint (SDL_Renderer* renderer,
					TTF_Font* font,
					const std::string& menu1,
					const std::string& menu2,
					const int SCREEN_WIDTH,
					const int SCREEN_HEIGHT,
		            int point, int start_time );

}
