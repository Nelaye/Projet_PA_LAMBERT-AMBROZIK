/******************************/
/***** Fichier sprite_t.c *****/
/******************************/
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#include "constante.h"
#include "sprite_t.h"


	/*################################ Function ###############################*/

		/**
			Create a special sprite from parameters
		**/
void Rect_cons(SDL_Rect *object, int width , int height , int x ,int y )
{
    object->x = x;
    object->y = y;
    object->h = height ;
    object->w = width ;
}

void sprite_cons(perso *hero, int width , int height , int x ,int y, double Vx, double Vy )
{
    hero->position.x = x;
    hero->position.y = y;
    hero->position.h = height ;
    hero->position.w = width ;

    hero->point.HG.x=hero->position.x;
    hero->point.HG.y=hero->position.y;

    hero->point.BG.x=hero->position.x;
    hero->point.BG.y=hero->position.y + hero->position.h;

    hero->point.HD.x=hero->position.x + hero->position.w;
    hero->point.HD.y=hero->position.y;

    hero->point.BD.x = hero->position.x + hero->position.w;
    hero->point.BD.y = hero->position.y + hero->position.h;

    hero->point.middle.x = hero->position.x + hero->position.w/ 2;
    hero->point.middle.y = hero->position.y + hero->position.h/ 2;

    hero->pos.x=Vx;
    hero->pos.y=Vy;
}

void sprite_update (perso* hero)
{
    hero->position.x = hero->point.middle.x - SPRITE_HERO_WIDTH/2;
    hero->position.y = hero->point.middle.y - SPRITE_HERO_HEIGHT/2;


    hero->point.HG.x = hero->point.middle.x - SPRITE_HERO_WIDTH/2;
    hero->point.HG.y = hero->point.middle.y - SPRITE_HERO_HEIGHT/2;

    hero->point.BG.x = hero->point.middle.x - SPRITE_HERO_WIDTH/2;
    hero->point.BG.y = hero->point.middle.y + SPRITE_HERO_HEIGHT/2;

    hero->point.HD.x = hero->point.middle.x + SPRITE_HERO_WIDTH/2;
    hero->point.HD.y = hero->point.middle.y - SPRITE_HERO_HEIGHT/2;

    hero->point.BD.x = hero->point.middle.x + SPRITE_HERO_WIDTH/2;
    hero->point.BD.y = hero->point.middle.y + SPRITE_HERO_HEIGHT/2;

}

void Collide( char** tab2, perso *hero, bool *down, bool *Saut, bool* key)
{
    int X,Y,X2,Y2,X3,Y3,X4,Y4;

    // point where it is in the table

    X=(hero->point.HG.x) / LARGEUR_TILE;
    Y=(hero->point.HG.y) / HAUTEUR_TILE;
    X2=(hero->point.HD.x) / LARGEUR_TILE;
    Y2=(hero->point.HD.y) / HAUTEUR_TILE;
    X3=(hero->point.BG.x) / LARGEUR_TILE;
    Y3=(hero->point.BG.y) / HAUTEUR_TILE;
    X4=(hero->point.BD.x) / LARGEUR_TILE;
    Y4=(hero->point.BD.y) / HAUTEUR_TILE;

    AABB box;
    bool stop = false;

    if (tab2[Y][X] != '0')
    {
        stop = true;

        box.HG.x = X*LARGEUR_TILE;
        box.HG.y = Y*HAUTEUR_TILE;

        box.HD.x = box.HG.x + LARGEUR_TILE;
        box.HD.y = box.HG.y;

        box.BD.x = box.HG.x + LARGEUR_TILE;
        box.BD.y = box.HG.y + HAUTEUR_TILE;

        box.BG.x = box.HG.x;
        box.BG.y = box.HG.y + HAUTEUR_TILE;


        retour(hero->pos, hero,box,0.01);

    }

    else
    {

        if (tab2[Y2][X2] != '0')
        {
            stop = true;

            box.HG.x = X2*LARGEUR_TILE;
            box.HG.y = Y2*HAUTEUR_TILE;

            box.HD.x = box.HG.x + LARGEUR_TILE;
            box.HD.y = box.HG.y;

            box.BD.x = box.HG.x + LARGEUR_TILE;
            box.BD.y = box.HG.y + HAUTEUR_TILE;

            box.BG.x = box.HG.x;
            box.BG.y = box.HG.y + HAUTEUR_TILE;

            retour(hero->pos, hero,box,0.01);
        }
        else
        {



            if (tab2[Y3][X3] != '0')
            {
                stop = true;
                *Saut=false;
                *down = false;

                box.HG.x = X3*LARGEUR_TILE;
                box.HG.y = Y3*HAUTEUR_TILE;

                box.HD.x = box.HG.x + LARGEUR_TILE;
                box.HD.y = box.HG.y;

                box.BD.x = box.HG.x + LARGEUR_TILE;
                box.BD.y = box.HG.y + HAUTEUR_TILE;

                box.BG.x = box.HG.x;
                box.BG.y = box.HG.y + HAUTEUR_TILE;

                retour(hero->pos, hero,box,0.01);
            }
            else
            {



                if (tab2[Y4][X4] != '0')
                {
                    stop = true;
                    *Saut=false;
                    *down = false;

                    box.HG.x = X4*LARGEUR_TILE;
                    box.HG.y = Y4*HAUTEUR_TILE;

                    box.HD.x = box.HG.x + LARGEUR_TILE;
                    box.HD.y = box.HG.y;

                    box.BD.x = box.HG.x + LARGEUR_TILE;
                    box.BD.y = box.HG.y + HAUTEUR_TILE;

                    box.BG.x = box.HG.x;
                    box.BG.y = box.HG.y + HAUTEUR_TILE;

                    retour(hero->pos, hero,box,0.01);
                }
                else
                {

                }
            }
        }
    }

    if (stop)
    {
        hero->pos.y=0;
        stop=false;
    }
}

void retour(vect V, perso *hero, AABB box, double eps)
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
    printf("mid : %f\n", mid);
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

