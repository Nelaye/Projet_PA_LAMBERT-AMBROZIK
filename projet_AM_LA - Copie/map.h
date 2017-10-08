#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

    #include <SDL2/SDL.h>
    #include <stdbool.h>

#include <stdlib.h>
#include <stdio.h>
char** initialisation_tableau( int x , int y  );
void Afficher(SDL_Rect *R_tileset,SDL_Texture* T_tileset,char** table,int nombre_blocs_largeur,int nombre_blocs_hauteur, SDL_Renderer *renderer, int scrolling_x, int* tempsactuel , int* tempsPrecedent,int* cpt  );

#endif // MAP_H_INCLUDED
