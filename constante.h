/*******************************/
/***** Fichier constante.h *****/
/*******************************/

#ifndef CONSTANTE_H_INCLUDED
#define CONSTANTE_H_INCLUDED

//defninir taille ecran
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

//key
#define NBPLAYERS 1

//hero
#define SPRITE_HERO_WIDTH  20
#define SPRITE_HERO_HEIGHT 20
#define HERO 0
#define SPEED 10

//tile
#define LARGEUR_TILE 50
#define HAUTEUR_TILE 50

// map
#define NOMBRE_BLOCK_LARGEUR 10
#define NOMBRE_BLOCK_HAUTEUR 5
typedef struct vect
{
  double x;
  double y;
}vect;

typedef struct Point_2D
{
    double x;
    double y;
}P2D;

typedef struct BLOCK_GLASS
{
    SDL_Rect position;
    int type;
}block;

typedef struct AABB
{
    P2D HG;
    P2D HD;
    P2D BG;
    P2D BD;
    vect Size;
    P2D middel;

}AABB;

typedef struct perso
{
    SDL_Rect position;
    vect pos;
    AABB point;
}perso;



// mouvement
enum mov{GAUCHE,DROITE,SAUT,ACCROUPIE};
enum sprite_type{VIDE, BLOCK_GLASS};




#endif
