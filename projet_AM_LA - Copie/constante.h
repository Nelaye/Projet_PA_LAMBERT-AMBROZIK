#ifndef CONSTANTE_H_INCLUDED
#define CONSTANTE_H_INCLUDED

//defninir taille ecran
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500
//taille cursor
#define CURSOR_HEIGHT 20
#define CURSOR_WIDTH  20
//hero
#define SPRITE_HERO_WIDTH  30
#define SPRITE_HERO_HEIGHT 30
#define HERO_START_LIFE 1
#define PICTURE_HERO_WIDTH 100
#define PICTURE_HERO_HEIGHT 100
#define MAX_ANIMATION 2
#define ANIMATION
//bullet
#define HAUTEUR_BULLET 16
#define LARGEUR_BULLET 16
//tile
#define LARGEUR_TILE 100
#define HAUTEUR_TILE 100
//power_glass tab
#define NOMBRE_BLOCK_LARGEUR_POWER 50
#define NOMBRE_BLOCK_HAUTEUR_POWER 25
//level
#define PICTURE_LEVEL_WIDTH 100
#define PICTURE_LEVEL_HEIGHT 100
// map
#define NOMBRE_BLOCK_LARGEUR 100
#define NOMBRE_BLOCK_HAUTEUR 10
//tile
#define NOMBRE_AFFICHER_LARGEUR 10
#define NOMBRE_AFFICHER_HAUTEUR 10
// tile 4
#define TILE_4_NOMBRE_ANIM 6
#define TILE_4_NOMBRE_ANIM_MILI_SECONDE 500
//power
#define POWER_GLASS 0
#define PISTOL 1
#define MAGAZINE_GUN 12

#define SHOT_GUN 2
#define MAGAZINE_SHOT_GUN 2
//niveau 1 //
#define HERO_START_POS_X 10
#define HERO_START_POS_Y 350
//pistol
#define NB_MAX_BULLETS 100
// mouvement
enum mov{GAUCHE,DROIT,TOMBE};
enum sprite_type{HERO};




#endif
