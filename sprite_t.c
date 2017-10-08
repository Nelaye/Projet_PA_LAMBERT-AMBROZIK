/******************************/
/***** Fichier sprite_t.c *****/
/******************************/
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#include "constante.h"
#include "sprite_t.h"

#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))

#define ABS(X) ((((X)<0)?(-(X)):(X)))

	/*################################ Function ###############################*/

		/**
			Create a special sprite from parameters
		**/
void sprite_cons(SDL_Rect *object, int width , int height , int x ,int y )
{
    object->x = x;
    object->y = y;
    object->h = height ;
    object->w = width ;
}

void Collide( char** tab2, SDL_Rect *hero, bool *Right, bool *Left, bool *Up)
{
    int X,Y,X2,Y2;

    X=(hero->x) / HAUTEUR_TILE;
    Y=(hero->y + 1 + hero->w) / HAUTEUR_TILE;
    X2=(hero->x + hero->h - 1) / HAUTEUR_TILE;
    Y2=(hero->y + 1 + hero->w) / HAUTEUR_TILE;

    //down
    if ( ((tab2[Y][X])=='0') && (tab2[Y2][X2]=='0'))
    {
        hero->y++;
    }
    else
    {

    }

    Y= (hero->y - 5) / HAUTEUR_TILE;

    //up
    if ((tab2[Y][X])=='0')
    {
        *Up=true;
    }
    else
    {
        *Up = false;
    }

    X= (hero->x + 4 + hero->h) / HAUTEUR_TILE;
    Y= hero->y / HAUTEUR_TILE;
    X2= (hero->x + 4 + hero->h) / HAUTEUR_TILE;
    Y2= (hero->y + hero->w) / HAUTEUR_TILE;

    //right
    if ( ((tab2[Y][X])=='0') && (tab2[Y2][X2]=='0') )
    {
        *Right=true;
    }
    else
    {
        *Right = false;
    }

    X= (hero->x - 5) / HAUTEUR_TILE;
    X2= (hero->x - 5) / HAUTEUR_TILE;

    //left
    if (((tab2[Y][X])=='0')&&((tab2[Y2][X2])=='0'))
    {
        *Left=true;
    }
    else
    {
        *Left = false;
    }

}
