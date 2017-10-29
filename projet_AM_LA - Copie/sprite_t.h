#ifndef SPRITE_T_H_INCLUDED
#define SPRITE_T_H_INCLUDED
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

    /*############################# Abstract Type #############################*/
typedef struct Animation
{
    int nb ;
}animation ;

typedef struct Mouse
{
    unsigned short int  x,y ;
    bool print ;
}mouse ;
typedef struct Compteur
{
    int nb ;
}compteur ;
typedef struct Sprite_t
{
    SDL_Texture *T_sprite ;
    SDL_Rect *R_sprite ;
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

typedef struct Character
{
    SDL_Texture *T_sprite ;
    SDL_Rect *R_sprite ;
    int life ;
    int protection ;
    bool print ;
    int type_shield ;
    bool shield ;
    bool helmet ;
    int player ;
    int sprite_type ;
}character;
		    /*################################ Function ###############################*/

        ///////////////////////////movement//////////////////////////////////
        SDL_Rect  left_movement(character *sprite, mouse m, SDL_Rect block );
        SDL_Rect right_movement(character *sprite, mouse m, SDL_Rect block );
        /////////////////////////////////////////////////////////////////////
        SDL_Rect initialization_animation(int sprite, int x , int y );
		void initialization(character *sprite,int type , int width ,int height ,int x ,int y );
        void sprite_cons(sprite_t *sprite,int width ,int height ,int x ,int y );
		//void sprite_cons(SDL_Rect* sprite, int width, int height, int x, int y);
        void cursor(sprite_t *curseur , SDL_Renderer *renderer, int power );
        char ** init_tab_dynamic( int x, int y, FILE *fichier );
        vecteur sbullet(SDL_Rect *hero ,  int Xcursor , int Ycursor);
        void update_bullet(bullet *b,vecteur v,  SDL_Renderer *renderer);
        void animation_boucle(SDL_Rect *block, int y, int taille_sprite, int nombre_sprite, int *cpt);
#endif // SPRITE_T_H_INCLUDED
