#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED
/*##################################################*/
/* on utilise le cours d'AP2  pour faire les listes */
/*##################################################*/
#<include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Liste *liste ;
struct Liste
{
  int premier ;
  liste suivant ;
} ;

/* SIGNATURES DES OPERATIONS PRIMITIVES */
liste l_vide () ;
liste cons (int x, liste L) ;
bool est_vide (liste L) ;
int prem (liste L) ;
liste reste (liste L) ;

/* IMPLANTATION DES OPERATIONS PRIMITIVES */
/* Constructeurs */
liste l_vide ()
{
  return NULL ;
}

liste cons (int x, liste L)
{
  liste M ;
  M = malloc (sizeof (*M)) ;
  (*M).premier = x ;
  (*M).suivant = L ;
  return M ;
}

/* Accès */
bool est_vide (liste L)
{
  return L == NULL ;
}

int prem (liste L)
{
  if (est_vide (L))
    {
      printf ("Calcul de prem sur liste vide !\n") ;
      exit (0) ;
    }
  return (*L).premier ;
}

liste reste (liste L)
{
  return (*L).suivant ;
}

/* OPERATIONS NON PRIMITIVES */
unsigned int longueurR (liste L)
{
  if (est_vide (L))
    return 0 ;
  return 1 + longueurR (reste (L)) ;
}

unsigned int longueurI (liste L)
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

void afficher_liste (liste L)
{
  printf ("(") ;
  while (!est_vide (L))
    {
      printf ("%d%s",
	      prem (L),
	      (est_vide (reste(L)) ? "" : " ")) ;
      L = reste (L) ;
    }
  printf (")") ;
}


#endif // LISTE_H_INCLUDED
