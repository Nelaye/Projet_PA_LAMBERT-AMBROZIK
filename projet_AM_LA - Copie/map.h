#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <SDL2/SDL.h>
#include <stdbool.h>

#include <stdlib.h>
#include <stdio.h>
#include "sprite_t.h"
#include "constante.h"

    /*############################# Abstract Type #############################*/
    typedef struct Block_glass
    {
        SDL_Texture *T_sprite ;
        SDL_Rect    *R_sprite ;
    }block_glass ;

    /*#############################   function    #############################*/
void ma(char** tab);
char** initialisation_tableau( int x , int y  );

void afficher_power(sprite_t *glass, char** tab ,int scrolling_x,  SDL_Renderer *renderer );
void Afficher(SDL_Rect *R_tileset,SDL_Texture* T_tileset,char** table,int nombre_blocs_largeur,int nombre_blocs_hauteur, SDL_Renderer *renderer, int scrolling_x,int *cpt  );

void  modifTabPower(mouse m,int scrolling ,char** tab);
void anim( SDL_Rect *block, int *cpt, int nombre_sprite, int ligne_sprite );

//int  compteur_tab_power( char** tab, char valeur_a_chercher);
#endif // MAP_H_INCLUDED
