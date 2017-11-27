#ifndef CONSTANTE_H_INCLUDED
#define CONSTANTE_H_INCLUDED

//defninir taille ecran
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500
//taille cursor
#define SIZE_PICTURE_HEIGHT_CURSOR 40
#define SIZE_PICTURE_WIDTH_CURSOR 40
#define CURSOR_HEIGHT 20
#define CURSOR_WIDTH  20
//hero
#define SPRITE_HERO_WIDTH  20
#define SPRITE_HERO_HEIGHT 30
#define HERO_START_LIFE 1
#define PICTURE_HERO_WIDTH 50
#define PICTURE_HERO_HEIGHT 100
#define MAX_ANIMATION_PERSO_NO_MOVE 2
#define MAX_ANIMATION_PERSO_MOVE 2
//SHIP
#define SPRITE_SHIP_WIDTH  40
#define SPRITE_SHIP_HEIGHT 20
#define SHIP_START_LIFE 1
#define PICTURE_SHIP_WIDTH 50
#define PICTURE_SHIP_HEIGHT 100
//bullet
#define HAUTEUR_BULLET 16
#define LARGEUR_BULLET 16
//tile
#define LARGEUR_TILE 100
#define HAUTEUR_TILE 100
//power_glass tab
#define NOMBRE_BLOCK_LARGEUR_POWER 200
#define NOMBRE_BLOCK_HAUTEUR_POWER 35
#define NOMBRE_AFFICHER_HAUTEUR_POWER 20
#define NOMBRE_AFFICHER_LARGEUR_POWER 50
//level
#define PICTURE_LEVEL_WIDTH 100
#define PICTURE_LEVEL_HEIGHT 100
// map
#define NOMBRE_BLOCK_LARGEUR 100
#define NOMBRE_BLOCK_HAUTEUR 10
#define MOUVEMENT_HERO 6
//tile
#define NOMBRE_AFFICHER_LARGEUR 20
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
enum touche{z,d,s,q};

enum mov{GAUCHE,DROIT,TOMBE};
enum sprite_type{HERO,SHIP};





#endif
