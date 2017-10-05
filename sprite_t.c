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
void *sprite_cons(SDL_Rect *object, int width , int height , int x ,int y )
{
    object->x = x;
    object->y = y;
    object->h = height ;
    object->w = width ;
}

void CollideDown(SDL_Rect *object, char** table, int X, int Y)
{
    if (table[X][Y+1]!='0')// si block en dessous est dur
    {
        int Y2=(Y+1)*HAUTEUR_TILE;

        if(object->y>Y2)
        {
            object->y=+1;
        }
    }
}












/* Collide test between the  hero and a wall for example
int Collide(SDL_Rect* m,SDL_Rect* n)
{
    if((m->x >= n->x + n->w)//à droite
        || (m->x + m->w <= n->x)//à gauche
        || (m->y >= n->y + n->h)//en bas
        || (m->y + m->h <= n->y))//en haut
        {
            return 0;
        }

    return 1;
}

        int CollisionDecor(SDL_Rect* perso)
        {

            int xmin, xmax, ymin, ymax, i, j, indicetile;
            //Map* m = perso->m;

            if (perso->x<0 || (perso->x + perso->w -1)>=  m->NOMBRE_BLOCK_LARGEUR* m->LARGEUR_TILE
            || perso->y<0 || (perso->y + perso->h -1)>=   m->NOMBRE_BLOCK_HAUTEUR* m->HAUTEUR_TILE)
            {
                return 1;
            }

            xmin = perso->x / m->LARGEUR_TILE;
            ymin = perso->y / m->HAUTEUR_TILE;
            xmax = (perso->x + perso->w -1) / m->LARGEUR_TILE;
            ymax = (perso->y + perso->h -1) / m->HAUTEUR_TILE;

            for(i=xmin;i<=xmax;i++)
            {
                for(j=ymin;j<=ymax;j++)
                {
                    indicetile = m->schema[i][j];
                    if (m->props[indicetile].plein)
                    {
                        return 1;
                    }

                }

            }

            return 0;

        }

int EssaiDeplacement(Sprite* perso,SDL_Rect* mur,int vx,int vy)
{
    SDL_Rect test;
    test = perso->position;
    test.x+=vx;
    test.y+=vy;

    if (Collide(mur,&test)==0)
    {
        perso->position = test;
        return 1;
    }
    return 0;
}


int DeplaceSprite(Sprite* perso,SDL_Rect* mur, int vx, int vy)
{
    if (EssaiDeplacement(perso,mur,vx,vy)==1)
    {
       return 1;
    }

    //Affine(mur,perso,vx,vy);
    return 2;
}


        ///////////////////////////////

void Affine(Sprite* perso,SDL_Rect* mur,int vx,int vy)
{
    int i;

    for(i=0;i<ABS(vx);i++)
    {
        if (EssaiDeplacement(perso,mur,SGN(vx),0)==0)
            break;
    }

    for(i=0;i<ABS(vy);i++)
    {
        if (EssaiDeplacement(perso,mur,0,SGN(vy))==0)
            break;
    }
}*/
