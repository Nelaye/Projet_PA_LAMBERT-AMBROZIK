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
    bool print ;
}sprite_t;


typedef struct Vecteur
{
    float x ;
    float y ;
}vecteur ;
typedef struct Point_2d
{
    float x ;
    float y ;
}P2D ;
typedef struct AABB
{
    P2D HG;
    P2D HD;
    P2D BG;
    P2D BD;
    vecteur Size ;
    P2D middle ;
} AABB;
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
    AABB point ;
    vecteur pos ;
}character;
typedef struct Timer
{
    int actualTime;
    int previousTime;
}timer;

typedef struct Bullet
{
    float x,y ;
    float DirX,DirY ;
    int vitesse ;
    vecteur v ;
    bool print ;
    SDL_Rect *R_Bullet ;
    SDL_Texture *T_Bullet ;
}bullet;
		    /*################################ Function ###############################*/

        void initialization_timer(timer *t);
        ///////////////////////////movement//////////////////////////////////

        SDL_Rect  left_movement(character *sprite, mouse m,timer *t, SDL_Rect block, float seconde);

SDL_Rect  right_movement(character *sprite, mouse m,timer *t,  SDL_Rect block, float seconde);

        void aim_arm(sprite_t* arm , mouse c, SDL_Rect* block, int power );
        /////////////////////////////////////////////////////////////////////
        SDL_Rect initialization_animation(int size_with,int size_height, int x , int y )
;
        void initialization(character *sprite,int type , int width ,int height ,int x ,int y );
        void sprite_cons(sprite_t *sprite,int width ,int height ,int x ,int y );
		//void sprite_cons(SDL_Rect* sprite, int width, int height, int x, int y);
        void cursor(sprite_t *curseur , SDL_Renderer *renderer, int power );
        char ** init_tab_dynamic( int x, int y, FILE *fichier );
        vecteur sbullet(SDL_Rect *hero ,  int Xcursor , int Ycursor);

//         void update_bullet(liste b, SDL_Renderer *renderer);

    void animation_boucle(SDL_Rect *block, int sens,timer *t, float seconde );


    bool testbox(AABB box1,AABB box2);
    bool testpoint(P2D point,AABB box);
    void Collide( char** tab2, character *hero, bool *down, bool *saut, int scrolling_x,int* touche);




#endif // SPRITE_T_H_INCLUDED
