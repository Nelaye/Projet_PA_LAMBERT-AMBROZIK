#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#include "constante.h"
#include "sprite_t.h"
   	/*################################ Function ###############################*/

		/**
			Create a special sprite from parameters
		**/
    void initialization_timer(timer *t)
    {
        t->actualTime=SDL_GetTicks();
        t->previousTime=0 ;
    }
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
    void update_bullet(bullet *b, SDL_Renderer *renderer)
    {
        SDL_Rect destination ;
        int i ;
        for (i =0 ; i < NB_MAX_BULLETS ; i++)
        {
            if(b[i].print)
            {
                if(b[i].x > WINDOW_WIDTH || b[i].x + LARGEUR_BULLET< 0 || b[i].y > WINDOW_WIDTH || b[i].y+HAUTEUR_BULLET < 0 )
                {
                    b[i].print = false ;
                }
                b[i].x += b[i].v.x;
                b[i].y += b[i].v.y;
                destination.x = floor(b[i].x);
                destination.y = floor(b[i].y);
                destination.h = HAUTEUR_BULLET;
                destination.w = LARGEUR_BULLET;
                SDL_RenderCopy(renderer,b[i].T_Bullet,NULL, &destination );

            }
        }

    }

    void animation_boucle(SDL_Rect *block, int sens, timer *t, float seconde )
    {
        int animation;
        if (t->actualTime-t->previousTime > seconde *1000)
        {
            t->previousTime = t->actualTime ;
            if (sens == TOMBE )
            {
                animation= 2 ;
                block->y = 600;
            }
            if (sens == GAUCHE)
            {

                animation= 2 ;
                block->y = 500 ;
            }
            else
            {

                animation= 2 ;
                block->y = 400 ;
            }
            if ((animation-1)* (PICTURE_HERO_WIDTH ) <=  block->x )
                {
                    block->x = 0 ;
                }
                else
                {
                    block->x = block->x + PICTURE_HERO_WIDTH ;

                }


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
SDL_Rect  left_movement(character *sprite, mouse m,timer *t,  SDL_Rect block, float seconde)
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
               if (t->actualTime-t->previousTime > seconde *1000)
               {
                    t->previousTime = t->actualTime ;
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
}

SDL_Rect  right_movement(character *sprite, mouse m,timer *t,  SDL_Rect block, float seconde)
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
               if (t->actualTime-t->previousTime > seconde *1000)
               {
                    t->previousTime = t->actualTime ;
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










