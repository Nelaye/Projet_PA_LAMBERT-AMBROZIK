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

    sprite_update(hero);

    hero->pos.x=Vx;
    hero->pos.y=Vy;
}

void sprite_update (perso* hero)
{
    hero->point.HG.x=hero->position.x;
    hero->point.HG.y=hero->position.y;

    hero->point.BG.x=hero->position.x;
    hero->point.BG.y=hero->position.y + hero->position.h;

    hero->point.HD.x=hero->position.x + hero->position.w;
    hero->point.HD.y=hero->position.y;

    hero->point.BD.x = hero->position.x + hero->position.w;
    hero->point.BD.y = hero->position.y + hero->position.h;

    hero->point.middel.x = hero->position.x + hero->position.w/ 2;
    hero->point.middel.y = hero->position.y + hero->position.h/ 2;

}

void Collide( char** tab2, perso *hero, bool *Right, bool *Left, bool *Up, bool *Saut)
{
    int X,Y,X2,Y2,X3,Y3,X4,Y4;

    // point where it is in the table

    X=(hero->point.HG.x) / LARGEUR_TILE;
    Y=(hero->point.HG.y) / HAUTEUR_TILE;

    AABB box;
    bool down = false;
    if (tab2[Y][X] != '0')
    {
        down = true;

        box.HG.x = X*LARGEUR_TILE;
        box.HG.y = Y*HAUTEUR_TILE;

        box.HD.x = box.HG.x + LARGEUR_TILE;
        box.HD.y = box.HG.y;

        box.BD.x = box.HG.x + LARGEUR_TILE;
        box.BD.y = box.HG.y + HAUTEUR_TILE;

        box.BG.x = box.HG.x;
        box.BG.y = box.HG.y + HAUTEUR_TILE;


        retour(hero->pos, hero,box,0.1);
    }

    X2=(hero->point.HD.x) / LARGEUR_TILE;
    Y2=(hero->point.HD.y) / HAUTEUR_TILE;

    if (tab2[Y2][X2] != '0')
    {
        down = true;

        box.HG.x = X2*LARGEUR_TILE;
        box.HG.y = Y2*HAUTEUR_TILE;

        box.HD.x = box.HG.x + LARGEUR_TILE;
        box.HD.y = box.HG.y;

        box.BD.x = box.HG.x + LARGEUR_TILE;
        box.BD.y = box.HG.y + HAUTEUR_TILE;

        box.BG.x = box.HG.x;
        box.BG.y = box.HG.y + HAUTEUR_TILE;

        retour(hero->pos, hero,box,0.1);


    }

    X3=(hero->point.BG.x) / LARGEUR_TILE;
    Y3=(hero->point.BG.y) / HAUTEUR_TILE;
    if (tab2[Y3][X3] != '0')
    {
        down = true;

        box.HG.x = X3*LARGEUR_TILE;
        box.HG.y = Y3*HAUTEUR_TILE;

        box.HD.x = box.HG.x + LARGEUR_TILE;
        box.HD.y = box.HG.y;

        box.BD.x = box.HG.x + LARGEUR_TILE;
        box.BD.y = box.HG.y + HAUTEUR_TILE;

        box.BG.x = box.HG.x;
        box.BG.y = box.HG.y + HAUTEUR_TILE;

        retour(hero->pos, hero,box,0.1);
    }

    X4=(hero->point.BD.x) / LARGEUR_TILE;
    Y4=(hero->point.BD.y) / HAUTEUR_TILE;
    if (tab2[Y4][X4] != '0')
    {
        down = true;

        box.HG.x = X4*LARGEUR_TILE;
        box.HG.y = Y4*HAUTEUR_TILE;

        box.HD.x = box.HG.x + LARGEUR_TILE;
        box.HD.y = box.HG.y;

        box.BD.x = box.HG.x + LARGEUR_TILE;
        box.BD.y = box.HG.y + HAUTEUR_TILE;

        box.BG.x = box.HG.x;
        box.BG.y = box.HG.y + HAUTEUR_TILE;

        retour(hero->pos, hero,box,0.1);
    }

    if (down)
    {
        hero->pos.y=0;
    }

}

void retour(vect V, perso *hero, AABB box, double eps)
{
    double min,max,mid;
    min = 0.0;
    max = 1.0;
    mid = (max+min)/2;
    hero->point.middel.x = hero->point.middel.x-(V.x*mid);
    hero->point.middel.y = hero->point.middel.y-(V.y*mid);

    sprite_update(hero);



    while(max-min>eps)
    {
        if(testbox(hero->point,box))
        {
            max=mid;
        }
        else
        {
            min=mid;
        }

        mid = (max+min)/2;
        hero->point.middel.x = hero->point.middel.x-(V.x*mid);
        hero->point.middel.y = hero->point.middel.y-(V.y*mid);
        sprite_update(hero);

    }
    printf("mid : %f\n", mid);
    hero->point.middel.x = hero->point.middel.x-(V.x*mid);
    hero->point.middel.y = hero->point.middel.y-(V.y*mid);
    sprite_update(hero);
}


bool testpoint(P2D point,AABB box)
{
    if (point.x>box.BD.x && point.x<box.HD.x)
    {
        return true;
    }

    if (point.y<box.BD.y && point.y>box.HD.y)
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

