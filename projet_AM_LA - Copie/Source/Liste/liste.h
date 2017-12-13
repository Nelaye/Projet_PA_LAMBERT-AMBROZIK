
#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Sprite/sprite_t.h"
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
liste shoot_bullet(liste l,bullet b,sprite_t* img_bullet,character* sprite,int scrolling, int aimX ,int aimY, int shift,int  startingX , int startingY )
{
    b.R_Bullet=img_bullet->R_sprite ;
    b.T_Bullet=img_bullet->T_sprite;
    b.x = sprite->R_sprite->x + scrolling+ startingX ;
    b.y = sprite->R_sprite->y + startingY;
    b.v = sbullet(sprite->R_sprite,aimX+ shift,aimY+shift) ;
    b.print = true;
    l = cons(b,l);
    return l ;
}

liste update_bullet_collide(liste b, SDL_Renderer *renderer,int scrolling ,int vitesse)
{

    if(est_vide(b)){
        return b;
    }
    bullet premier_liste_L ;

    SDL_Rect destination ;

    premier_liste_L = prem(b);

    premier_liste_L.x =premier_liste_L.x + (premier_liste_L.v.x) * vitesse ;
    premier_liste_L.y =premier_liste_L.y + (premier_liste_L.v.y) * vitesse ;
    destination.x = floor(premier_liste_L.x-scrolling);
    destination.y = floor(premier_liste_L.y);
    destination.h = HAUTEUR_BULLET;
    destination.w = LARGEUR_BULLET;

    SDL_RenderCopy(renderer,premier_liste_L.T_Bullet,NULL, &destination );

    return cons(premier_liste_L,update_bullet_collide(reste(b)  ,renderer,scrolling,vitesse));
}

liste collide_bullet( liste l , char** tile, int number_display_width , int number_display_height, int scrolling, int size_array_X , int size_array_Y )
{
      if(est_vide(l)){
        return l;
    }

    int X_H_G=((prem(l).x) / (WINDOW_WIDTH / number_display_width)) ;
    int Y_H_G=(prem(l).y) / (WINDOW_HEIGHT / number_display_height);
    if ( X_H_G<0 &&  X_H_G>size_array_X && Y_H_G<0 && Y_H_G > size_array_Y){
        return  collide_bullet( reste(l),tile,  number_display_width , number_display_height, scrolling,  size_array_X,size_array_Y);
    }
    int X_H_D=((prem(l).x+LARGEUR_BULLET) / (WINDOW_WIDTH / number_display_width)) ;
    int Y_H_D=(prem(l).y) / (WINDOW_HEIGHT / number_display_height);
    if ( X_H_D<0 &&  X_H_D>size_array_X && Y_H_D<0 && Y_H_D > size_array_Y){
        return collide_bullet( reste(l),tile,  number_display_width , number_display_height, scrolling,  size_array_X,size_array_Y);
    }
    int X_B_G=((prem(l).x) / (WINDOW_WIDTH / number_display_width)) ;
    int Y_B_G=(prem(l).y+HAUTEUR_BULLET) / (WINDOW_HEIGHT / number_display_height);
    if ( X_B_G<0 &&  X_B_G>size_array_X && Y_B_G<0 && Y_B_G > size_array_Y){
        return  collide_bullet( reste(l),tile,  number_display_width , number_display_height, scrolling,  size_array_X,size_array_Y);
    }
    int X_B_D=((prem(l).x+LARGEUR_BULLET) / (WINDOW_WIDTH / number_display_width)) ;
    int Y_B_D=(prem(l).y+HAUTEUR_BULLET) / (WINDOW_HEIGHT / number_display_height);
    if ( X_B_D<0 &&  X_B_D>size_array_X && Y_B_D<0 && Y_B_D > size_array_Y){
        return  collide_bullet( reste(l),tile,  number_display_width , number_display_height, scrolling,  size_array_X,size_array_Y);
    }
    if( tile[Y_H_G][X_H_G]!='0' ||  tile[Y_B_G][X_B_G]!='0'  || tile[Y_H_D][X_H_D]!='0' || tile[Y_B_G][X_B_G]!='0' || tile[Y_B_D][X_B_D]!='0'){
            return collide_bullet( reste(l),tile,  number_display_width , number_display_height, scrolling,size_array_X,size_array_Y );
    }
    if (prem(l).y<0 || prem(l).x<0 +scrolling || prem(l).y>WINDOW_HEIGHT || prem(l).x>WINDOW_WIDTH +scrolling){
        return collide_bullet( reste(l),tile,  number_display_width , number_display_height , scrolling,size_array_X,size_array_Y);
    }
    return cons(prem(l),collide_bullet( reste(l),tile,  number_display_width , number_display_height , scrolling,size_array_X,size_array_Y ));
    }

    liste collide_bullet_sprite(liste L , character* sprite, int size_bullet, int scrolling )
    {
        if(est_vide(L)){
            return L;
        }

        int weidth_sprite ;
        int height_sprite ;

        switch (sprite->sprite_type){
        case HERO :
            weidth_sprite = SPRITE_HERO_WIDTH ;
            height_sprite = SPRITE_HERO_HEIGHT ;
            break;
        case SHIP :
            weidth_sprite = SPRITE_SHIP_WIDTH ;
            height_sprite = SPRITE_SHIP_HEIGHT ;
            break ;
        }

        int MX = ((prem(L).x)+(HAUTEUR_BULLET)/2);
        int MY = ((prem(L).y)+ (LARGEUR_BULLET)/2);

        int X1 = sprite->R_sprite->x + scrolling;
        int X2 = sprite->R_sprite->x + weidth_sprite + scrolling;
        int Y1 = sprite->R_sprite->y  ;
        int Y2 = sprite->R_sprite->y + height_sprite;

        printf("%f\n",prem(L).y);

        if((MX>X1 && MX<X2) && (MY>Y1 && MY<Y2)) {

            if (sprite->life > 0 ){
                sprite->life = sprite->life - 1 ;

            }else{
                sprite->print = false ;
            }

            return collide_bullet_sprite(reste(L),sprite,size_bullet,scrolling);
        }
       return cons(prem(L),collide_bullet_sprite(reste(L),sprite,size_bullet,scrolling));
    }









#endif // LISTE_H_INCLUDED
