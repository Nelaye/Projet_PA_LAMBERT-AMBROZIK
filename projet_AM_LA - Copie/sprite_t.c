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
    sprite->point.HG.x = sprite->R_sprite->x ;
    sprite->point.HG.y = sprite->R_sprite->y ;

    sprite->point.BG.x = sprite->R_sprite->x;
    sprite->point.BG.y = sprite->R_sprite->y + sprite->R_sprite->h;

    sprite->point.HD.x = sprite->R_sprite->x + sprite->R_sprite->w ;
    sprite->point.HD.y = sprite->R_sprite->y ;

    sprite->point.BD.x = sprite->R_sprite->x + sprite->R_sprite->w ;
    sprite->point.BD.y = sprite->R_sprite->y + sprite->R_sprite->h ;

     sprite->point.middle.x = sprite->R_sprite->x + sprite->R_sprite->w/ 2;
    sprite->point.middle.y = sprite->R_sprite->y + sprite->R_sprite->h/ 2;

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
        block.h=SIZE_PICTURE_HEIGHT_CURSOR;
        block.w=SIZE_PICTURE_WIDTH_CURSOR ;

        switch (power)
        {
        case POWER_GLASS:
            block.x=0;
            break;
        case  PISTOL:
            block.x = SIZE_PICTURE_WIDTH_CURSOR;

            break;
        case  SHOT_GUN:
            block.x = SIZE_PICTURE_WIDTH_CURSOR ;

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



    void animation_boucle(SDL_Rect *block, int sens, timer *t, float seconde )
    {
        int animation;
        if (t->actualTime-t->previousTime > seconde *1000)
        {
            t->previousTime = t->actualTime ;
            if (sens == TOMBE )
            {
                animation= MAX_ANIMATION_PERSO_NO_MOVE ;
                block->y = PICTURE_HERO_HEIGHT*6;
            }
            if (sens == GAUCHE)
            {

                animation= MAX_ANIMATION_PERSO_NO_MOVE ;
                block->y = PICTURE_HERO_HEIGHT * 5 ;
            }
            else
            {

                animation= MAX_ANIMATION_PERSO_NO_MOVE ;
                block->y = PICTURE_HERO_HEIGHT*4 ;
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

           block.w = size_with ;
           block.h= size_height ;
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
                animation =  MAX_ANIMATION_PERSO_MOVE ;
                block.y = 0 ;
               }
               else
               {
                animation =  MAX_ANIMATION_PERSO_MOVE ;
                block.y = PICTURE_HERO_HEIGHT*2 ;
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
                animation =  MAX_ANIMATION_PERSO_MOVE ;
                block.y = PICTURE_HERO_HEIGHT ;
               }
               else
               {
                animation =  MAX_ANIMATION_PERSO_MOVE ;
                block.y = PICTURE_HERO_HEIGHT*3 ;
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

void sprite_update (character* hero)
{
    hero->R_sprite->x = hero->point.middle.x - SPRITE_HERO_WIDTH/2;
    hero->R_sprite->y = hero->point.middle.y - SPRITE_HERO_HEIGHT/2;


    hero->point.HG.x = hero->point.middle.x - SPRITE_HERO_WIDTH/2;
    hero->point.HG.y = hero->point.middle.y - SPRITE_HERO_HEIGHT/2;

    hero->point.BG.x = hero->point.middle.x - SPRITE_HERO_WIDTH/2;
    hero->point.BG.y = hero->point.middle.y + SPRITE_HERO_HEIGHT/2;

    hero->point.HD.x = hero->point.middle.x + SPRITE_HERO_WIDTH/2;
    hero->point.HD.y = hero->point.middle.y - SPRITE_HERO_HEIGHT/2;

    hero->point.BD.x = hero->point.middle.x + SPRITE_HERO_WIDTH/2;
    hero->point.BD.y = hero->point.middle.y + SPRITE_HERO_HEIGHT/2;

}

void Collide( char** tab2, character *hero, bool *down, bool *saut, int scrolling_x, int *touche)
{
    int X,Y,X2,Y2,X3,Y3,X4,Y4, Ybis;

    // point where it is in the table

    X=(hero->point.HG.x) / (WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR) ;
    Y=(hero->point.HG.y) / (WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR);
    X2=(hero->point.HD.x) / (WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR);
    Y2=(hero->point.HD.y) / (WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR);
    X3=(hero->point.BG.x) / (WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR);
    Y3=(hero->point.BG.y) / (WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR);
    X4=(hero->point.BD.x) / (WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR);
    Y4=(hero->point.BD.y) / (WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR);

    Ybis= ((hero->point.BD.y)/ (WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR)) +1;

    AABB box;
    bool stop = false;
    int k =((WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR)/10)*10;
    int scrol = 0; //(scrolling_x/k);
    if (tab2[Y][X + scrol] != '0')
    {
        stop = true;

        box.HG.x = X*(WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR);
        box.HG.y = Y*(WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR);

        box.HD.x = box.HG.x + (WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR);
        box.HD.y = box.HG.y;

        box.BD.x = box.HG.x + (WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR);
        box.BD.y = box.HG.y + (WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR);
        box.BG.x = box.HG.x;
        box.BG.y = box.HG.y + (WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR);


        retour(hero->pos, hero,box,0.01);
        touche[3]=0;

    }

    else
    {

        if (tab2[Y2][X2+ scrol] != '0')
        {
            stop = true;

            box.HG.x = X2*(WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR);
            box.HG.y = Y2*(WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR);

            box.HD.x = box.HG.x + (WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR);
            box.HD.y = box.HG.y;

            box.BD.x = box.HG.x + (WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR);
            box.BD.y = box.HG.y + (WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR);

            box.BG.x = box.HG.x;
            box.BG.y = box.HG.y + (WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR);

            retour(hero->pos, hero,box,0.01);
            touche[1]=0;

        }
        else
        {



            if (tab2[Y3][X3+ scrol] != '0')
            {
                stop = true;
                *saut=false;
                *down = false;

                box.HG.x = X3*(WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR);
                box.HG.y = Y3*(WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR);

                box.HD.x = box.HG.x + (WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR);
                box.HD.y = box.HG.y;

                box.BD.x = box.HG.x + (WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR);
                box.BD.y = box.HG.y + (WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR);

                box.BG.x = box.HG.x;
                box.BG.y = box.HG.y + (WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR);

                retour(hero->pos, hero,box,0.01);
               // touche[3]=0;

            }
            else
            {



                if (tab2[Y4][X4+ scrol] != '0')
                {
                    stop = true;
                    *saut=false;
                    *down = false;

                    box.HG.x = X4*(WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR);
                    box.HG.y = Y4*(WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR);

                    box.HD.x = box.HG.x + (WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR);
                    box.HD.y = box.HG.y;

                    box.BD.x = box.HG.x + (WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR);
                    box.BD.y = box.HG.y + (WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR);

                    box.BG.x = box.HG.x;
                    box.BG.y = box.HG.y + (WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR);

                    retour(hero->pos, hero,box,0.01);
                   // touche[1]=0;

                }

            }
        }
    }
     if (tab2[Ybis][X4] != '0')
    {
        *down=true;}


    if (stop)
    {
        hero->pos.y=0;
    }
}

void retour(vecteur V, character *hero, AABB box, double eps)
{
    double min,max,mid;
    min = 0.0;
    max = 1.0;
    mid = (max+min)/2;
    hero->point.middle.x = hero->point.middle.x-(V.x);
    hero->point.middle.y = hero->point.middle.y-(V.y);

    sprite_update(hero);

    P2D tmp= hero->point.middle;

    while(max-min>eps)
    {
        hero->point.middle.x = hero->point.middle.x + (V.x * mid);
        hero->point.middle.y = hero->point.middle.y + (V.y * mid);
        sprite_update(hero);

        if(testbox(hero->point,box))
        {
            max=mid;
        }
        else
        {
            min=mid;
        }
        hero->point.middle = tmp;
        mid = (max+min)/2;

    }
    hero->point.middle.x = hero->point.middle.x + (V.x * (mid - eps/2) );
    hero->point.middle.y = hero->point.middle.y + (V.y * (mid - eps/2) );
    sprite_update(hero);
}

bool testpoint(P2D point,AABB box)
{
    if (point.x>box.BG.x && point.x<box.HD.x)
    {
        return true;
    }

    if (point.y<box.BG.y && point.y>box.HD.y)
    {
        return true;
    }
    return false;
}

bool testbox(AABB box1,AABB box2)
{
    if (testpoint(box1.HG,box2))
    {
        return true;
    }
    if (testpoint(box1.BG,box2))
    {
        return true;
    }

    if (testpoint(box1.HD,box2))
    {
        return true;
    }

    if (testpoint(box1.BD,box2))
    {
        return true;
    }
    return false;
}




















