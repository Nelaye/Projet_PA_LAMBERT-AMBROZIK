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

    void animation_boucle(SDL_Rect *block, int y, int taille_sprite, int nombre_sprite, int *cpt)
    {
        block->x = *cpt * taille_sprite;
        block->y = y;
        *cpt = *cpt + 1  ;
        block->x = *cpt * taille_sprite ;
        if ( block->x > nombre_sprite -1 )
        {
            block->x = 0 ;
            *cpt = 0 ;
        }
    }

SDL_Rect initialization_animation(int sprite, int x , int y )
{
    SDL_Rect block ;
    switch (sprite)
    {
    case HERO :
        {
           block.h = PICTURE_HERO_WIDTH ;
           block.w = PICTURE_HERO_HEIGHT ;
           block.x = x ;
           block.y = y ;
           break;
        }
    }
return block ;
}

SDL_Rect  left_movement(character *sprite, mouse m, SDL_Rect block )
{
    int animation  ;
    switch (sprite->sprite_type)
        {
        case HERO :
            {
                animation =  MAX_ANIMATION ;
                switch (m.print)
                {
                    case false :
                    {
                        if ((animation-1)* (PICTURE_HERO_WIDTH ) <=  block.x )
                        {
                            block.x = 0 ;
                            block.y =  0 ;
                            return block;
                        }
                        else
                        {
                            block.x = block.x + PICTURE_HERO_WIDTH ;
                            block.y =  0 ;
                            return block;
                        }
                        break;
                    }
                }
            }

        }
}

SDL_Rect right_movement(character *sprite, mouse m, SDL_Rect block )
{
    int animation  ;
    switch (sprite->sprite_type)
        {
        case HERO :
            {
                animation =  MAX_ANIMATION ;
                switch (m.print)
                {
                    case false :
                    {
                        if ((animation-1)* (PICTURE_HERO_WIDTH ) <=  block.x )
                        {
                            block.x = 0 ;

                            block.y =  PICTURE_HERO_HEIGHT ;
                            return block;
                        }
                        else
                        {
                            block.x = block.x + PICTURE_HERO_WIDTH ;
                            block.y =  PICTURE_HERO_HEIGHT ;
                            return block;
                        }
                        break;
                    }
                }
            }

        }
}

















