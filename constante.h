/*******************************/
/***** Fichier constante.h *****/
/*******************************/

#ifndef CONSTANTE_H_INCLUDED
#define CONSTANTE_H_INCLUDED

//defninir taille ecran
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

//hero
#define SPRITE_HERO_WIDTH  15
#define SPRITE_HERO_HEIGHT 15
#define HERO 0
#define SPEED 10

//tile
#define LARGEUR_TILE 100
#define HAUTEUR_TILE 100

// map
#define NOMBRE_BLOCK_LARGEUR 10
#define NOMBRE_BLOCK_HAUTEUR 5
typedef struct vect
{
  double x;
  double y;
}vect;

typedef struct BLOCK_GLASS
{
    SDL_Rect position;
    int type;
}block;

// mouvement
enum mov{GAUCHE,DROITE,SAUT,ACCROUPIE};
enum sprite_type{VIDE, BLOCK_GLASS};




#endif
