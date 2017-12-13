
#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Sprite/sprite_t.h"
#include "../constante.h"

typedef struct Liste *liste ;
struct Liste
{
bullet premier ;
liste suivant ;
} ;
/* SIGNATURES DES OPERATIONS PRIMITIVES */
liste l_vide () ;
liste cons (bullet x, liste L) ;
bool est_vide (liste L) ;
bullet prem (liste L) ;
liste reste (liste L) ;

#endif // LISTE_H_INCLUDED
