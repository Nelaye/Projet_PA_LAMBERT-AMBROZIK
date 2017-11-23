
#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sprite_t.h"
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
/* IMPLANTATION DES OPERATIONS PRIMITIVES */
/* Constructeurs */
liste l_vide ()
{
return NULL ;
}
liste cons (bullet x, liste L)
{
liste M ;
/* Réservation de la place mémoire nécessaire */
M = malloc (sizeof (*M)) ;
M->premier = x ;
M->suivant = L ;
return M ;
}
/* Accès */
bool est_vide (liste L)
{
return L == NULL ;
}
bullet prem (liste L)
{
if (est_vide (L))
{
printf ("Calcul de prem sur liste vide !\n") ;
exit (0) ;
}
return L->premier ;
}
liste reste (liste L)
{
return L->suivant ;
}
void ecrire_prem (bullet x, liste L)
{
  L->premier = x ;
}
int longueur(liste L)
{
  unsigned int lg ;
  lg = 0 ;
  while (!est_vide (L))
    {
      lg = lg + 1 ;
      L = reste (L) ;
    }
  return lg ;
}
void liberer_liste(liste L)
{
  if (est_vide (L))
    {
      return ;
    }
  liberer_liste (reste (L)) ;
  free(L) ;
}

liste update_bullet(liste b, SDL_Renderer *renderer,int scrolling )
{
    liste L ;
    bullet premier_liste_L ;
    L = b;

    SDL_Rect destination ;
    if(est_vide(b))
    {

            return b;
    }
    premier_liste_L = prem(L);


    premier_liste_L.x =premier_liste_L.x + (premier_liste_L.v.x) * 10 ;
    premier_liste_L.y =premier_liste_L.y + (premier_liste_L.v.y) * 10 ;
    destination.x = floor(premier_liste_L.x-scrolling);
    destination.y = floor(premier_liste_L.y);
    destination.h = HAUTEUR_BULLET;
    destination.w = LARGEUR_BULLET;

    SDL_RenderCopy(renderer,premier_liste_L.T_Bullet,NULL, &destination );

    return cons(premier_liste_L,update_bullet(reste(b)  ,renderer,scrolling ));
    }




#endif // LISTE_H_INCLUDED
