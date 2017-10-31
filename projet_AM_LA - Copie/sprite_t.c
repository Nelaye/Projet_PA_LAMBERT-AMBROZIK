#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#include "constante.h"
#include "sprite_t.h"
   	/*################################ Function ###############################*/

		/**
			Create a special sprite from parameters
		**/
    void initialization(character *sprite,int type , int width ,int height ,int x ,int y )
    {
        sprite->R_sprite->x= x;
        sprite->R_sprite->y = y;
        sprite->R_sprite->h = height ;
        sprite->R_sprite->w = width ;
        sprite->sprite_type = type ;
    switch (type)
    {
        case HERO :
        {

            sprite->life= HERO_START_LIFE ;
            sprite->protection= 0 ;
            sprite->print = true ;
            sprite->shield = false ;
            sprite->helmet = false ;

            break;
        }

    }

    }
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
        SDL_Rect destination = {b->x,b->y,HAUTEUR_BULLET,LARGEUR_BULLET};
        SDL_RenderCopy(renderer,b->T_Bullet,NULL, &destination );
    }

    void animation_boucle(SDL_Rect *block, int sens)
    {
            int animation = MAX_ANIMATION ;
            if (sens == GAUCHE)
            {
                block->y = 500 ;
            }
            else
            {
                block->y = 400 ;
            }
            if ((animation-1)* (PICTURE_HERO_WIDTH ) <=  block->x )
                    {
                        block->x = 0 ;

                        return block;
                    }
                    else
                    {
                        block->x = block->x + PICTURE_HERO_WIDTH ;

                        return block;
                    }
    }

SDL_Rect initialization_animation(int size_with,int size_height, int x , int y )
{
    SDL_Rect block ;

           block.h = size_with ;
           block.w = size_height ;
           block.x = x ;
           block.y = y ;


return block ;
}

SDL_Rect  left_movement(character *sprite, mouse m, SDL_Rect block )
{
    int animation  ;
    switch (sprite->sprite_type)
        {
        case HERO :
            {
               if( sprite->R_sprite->x > m.x )
               {
                animation =  MAX_ANIMATION ;
                block.y = 0 ;
               }
               else
               {
                animation =  MAX_ANIMATION ;
                block.y = 200 ;
               }
                if ((animation-1)* (PICTURE_HERO_WIDTH ) <=  block.x )
                {
                    block.x = 0 ;

                    return block;
                }
                else
                {
                    block.x = block.x + PICTURE_HERO_WIDTH ;

                    return block;
                }
                break;


            }

        }
}

SDL_Rect right_movement(character *sprite, mouse m, SDL_Rect block  )
{
    int animation  ;
    switch (sprite->sprite_type)
        {
        case HERO :
            {
               if( sprite->R_sprite->x <= m.x )
               {
                animation =  MAX_ANIMATION ;
                block.y = 100 ;
               }
               else
               {
                animation =  MAX_ANIMATION ;
                block.y = 300 ;
               }
                if ((animation-1)* (PICTURE_HERO_WIDTH ) <=  block.x )
                {
                    block.x = 0 ;

                    return block;
                }
                else
                {
                    block.x = block.x + PICTURE_HERO_WIDTH ;

                    return block;
                }
                break;


            }

        }
}


void aim_arm(sprite_t* arm , mouse c, SDL_Rect* block, int power )
{
	double vx = c.x - arm->R_sprite->x ;
	double vy = c.y - arm->R_sprite->y ;
	double angle  = atan2(-vy, vx);
    int num =  ((int)(angle/M_PI*180/10)+18)%36;
	block->x = num * 10 ;
	block->y =power * 10 ;
}














