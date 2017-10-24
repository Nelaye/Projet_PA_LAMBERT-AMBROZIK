#ifndef SPRITE_T_H_INCLUDED
#define SPRITE_T_H_INCLUDED
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

    /*############################# Abstract Type #############################*/
typedef struct Mouse
{
    unsigned short int  x,y ;
}mouse ;

typedef struct Sprite_t
{
    SDL_Texture *T_sprite ;
    SDL_Rect *R_sprite ;
    int posX, posY ;

}sprite_t;

typedef struct Bullet
{
    float x,y ;
    float DirX,DirY ;
    int v ;
    SDL_Rect *R_Bullet ;
    SDL_Texture *T_Bullet ;
}bullet;
typedef struct Vecteur
{
    float x ;
    float y ;
}vecteur ;
		   /*################################ Function ###############################*/

        void sprite_cons(sprite_t *sprite,int width ,int height ,int x ,int y );
		//void sprite_cons(SDL_Rect* sprite, int width, int height, int x, int y);
        void cursor(sprite_t *curseur , SDL_Renderer *renderer, int power );
        char ** init_tab_dynamic( int x, int y, FILE *fichier );
        vecteur sbullet(SDL_Rect *hero ,  int Xcursor , int Ycursor);
        void update_bullet(bullet *b,vecteur v,  SDL_Renderer *renderer);
#endif // SPRITE_T_H_INCLUDED
