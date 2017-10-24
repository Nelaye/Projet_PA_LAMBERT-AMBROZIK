#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#include "constante.h"
#include "sprite_t.h"
   	/*################################ Function ###############################*/

		/**
			Create a special sprite from parameters
		**/
    void sprite_cons(sprite_t *sprite,int width ,int height ,int x ,int y )
		{
		    sprite->R_sprite->x= x;
		    sprite->R_sprite->y = y;
		    sprite->R_sprite->h = height ;
		    sprite->R_sprite->w = width ;
		}

		void cursor(sprite_t *curseur , SDL_Renderer *renderer, int power )
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
            SDL_RenderCopy(renderer,curseur->T_sprite,&block,curseur->R_sprite);
        }

		vecteur sbullet(SDL_Rect *hero ,  int Xcursor , int Ycursor)
		{
            vecteur v ;
            float length  ;
            v.x = Xcursor - hero->x ;
            v.y = Ycursor - hero->y ;
            length = sqrt(pow(v.x,2)+ pow(v.y,2));
            v.x /= length ;
            v.y /= length ;

            return v ;

		}
        void update_bullet(bullet *b,vecteur v,  SDL_Renderer *renderer)
        {
            b->x += v.x ;
            b->y += v.y ;
            SDL_Rect destination = {b->x,b->y,16,16};
            SDL_RenderCopy(renderer,b->T_Bullet,NULL, &destination );
        }

















