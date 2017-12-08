#ifndef NIVEAU_H_INCLUDED
#define NIVEAU_H_INCLUDED
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "sprite_t.h"
#include "constante.h"

typedef struct Level
{
    SDL_Rect arm;
    SDL_Rect picture_anim_hero;
    char** monde ;
    char** power ;

}level ;






int start(SDL_Renderer* renderer , sprite_t* background, int* touche_actif);
#endif // NIVEAU_H_INCLUDED
