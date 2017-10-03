#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#include "constante.h"
#include "sprite_t.h"

	/*################################ Function ###############################*/

		/**
			Create a special sprite from parameters
		**/
		void *sprite_cons(SDL_Rect *sprite, int width , int height , int x ,int y )
		{
            sprite->x = x;
		    sprite->y = y;
		    sprite->h = height ;
		    sprite->w = width ;

		}
