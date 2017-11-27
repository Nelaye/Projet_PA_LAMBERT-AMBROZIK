
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

liste update_bullet_collide(liste b, SDL_Renderer *renderer,int scrolling ,int vitesse)
{

    if(est_vide(b)){
        return b;
    }



    liste L ;
    bullet premier_liste_L ;
    L = b;

    SDL_Rect destination ;

    premier_liste_L = prem(L);


    premier_liste_L.x =premier_liste_L.x + (premier_liste_L.v.x) * vitesse ;
    premier_liste_L.y =premier_liste_L.y + (premier_liste_L.v.y) * vitesse ;
    destination.x = floor(premier_liste_L.x-scrolling);
    destination.y = floor(premier_liste_L.y);
    destination.h = HAUTEUR_BULLET;
    destination.w = LARGEUR_BULLET;

    SDL_RenderCopy(renderer,premier_liste_L.T_Bullet,NULL, &destination );

    return cons(premier_liste_L,update_bullet_collide(reste(b)  ,renderer,scrolling,vitesse));
    }

    liste collide_bullet( liste l , char** tile, int number_display_width , int number_display_height, int scrolling )
    {
      if(est_vide(l)){
        return l;
    }

    int   X_H_G=((prem(l).x) / (WINDOW_WIDTH / number_display_width)) ;
    int   Y_H_G=(prem(l).y) / (WINDOW_HEIGHT / number_display_height);

    int X_H_D=((prem(l).x+LARGEUR_BULLET) / (WINDOW_WIDTH / number_display_width)) ;
    int Y_H_D=(prem(l).y) / (WINDOW_HEIGHT / number_display_height);

    int X_B_G=((prem(l).x) / (WINDOW_WIDTH / number_display_width)) ;
    int Y_B_G=(prem(l).y+HAUTEUR_BULLET) / (WINDOW_HEIGHT / number_display_height);

    int X_B_D=((prem(l).x+LARGEUR_BULLET) / (WINDOW_WIDTH / number_display_width)) ;
    int Y_B_D=(prem(l).y+HAUTEUR_BULLET) / (WINDOW_HEIGHT / number_display_height);
   if( tile[Y_H_G][X_H_G]!='0' ||  tile[Y_B_G][X_B_G]!='0'  || tile[Y_H_D][X_H_D]!='0' || tile[Y_B_G][X_B_G]!='0' || tile[Y_B_G][X_B_G]!='0'){
        return collide_bullet( reste(l),tile,  number_display_width , number_display_height, scrolling );
   // }
   }
    if (prem(l).y<0 || prem(l).x<0 +scrolling || prem(l).y>WINDOW_HEIGHT || prem(l).x>WINDOW_WIDTH +scrolling){
            return collide_bullet( reste(l),tile,  number_display_width , number_display_height , scrolling);
        }
        return cons(prem(l),collide_bullet( reste(l),tile,  number_display_width , number_display_height , scrolling ));
    }










#endif // LISTE_H_INCLUDED
