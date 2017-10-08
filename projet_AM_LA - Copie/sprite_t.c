#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#include "constante.h"
#include "sprite_t.h"

	/*################################ Function ###############################*/

		/**
			Create a special sprite from parameters
		**/
		void sprite_cons(SDL_Rect *sprite, int width , int height , int x ,int y )
		{
            sprite->x = x;
		    sprite->y = y;
		    sprite->h = height ;
		    sprite->w = width ;

		}
		void cursor(SDL_Rect *R_cursor,SDL_Texture* T_cursor,SDL_Renderer *renderer,int power )
		{

		    SDL_Rect block;
		    block.y=0;
		    block.h=40;
		    block.w=40 ;

            switch (power)
            {
            case 0:
                block.x=0;
                break;
            case 1:
                block.x = 40;

                break;
            default:
                break;

            }
            printf("%d\n",block.x);
            SDL_RenderCopy(renderer,T_cursor,&block, R_cursor);

		}
