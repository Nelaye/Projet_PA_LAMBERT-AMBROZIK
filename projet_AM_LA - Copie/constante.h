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
#define HERO 0
//bullet
#define HAUTEUR_BULLET 16
#define LARGEUR_BULLET 16
//tile
#define LARGEUR_TILE 100
#define HAUTEUR_TILE 100
//power_glass tab
#define NOMBRE_BLOCK_LARGEUR_POWER 50
#define NOMBRE_BLOCK_HAUTEUR_POWER 25

// map
#define NOMBRE_BLOCK_LARGEUR 100
#define NOMBRE_BLOCK_HAUTEUR 10
//tilte
#define NOMBRE_AFFICHER_LARGEUR 10
#define NOMBRE_AFFICHER_HAUTEUR 10
//power
#define PISTOL 1
#define POWER_GLASS 0
//niveau 1 //
#define HERO_START_POS_X 10
#define HERO_START_POS_Y 350
// mouvement
enum mov{GAUCHE,DROITE,SAUT,ACCROUPIE};
enum sprite_type{VIDE, BLOCK_GLASS};




#endif
