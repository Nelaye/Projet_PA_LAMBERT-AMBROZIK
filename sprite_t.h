/******************************/
/***** Fichier sprite_t.h *****/
/******************************/
#ifndef SPRITE_T_H_INCLUDED
#define SPRITE_T_H_INCLUDED

    #include <SDL2/SDL.h>
    #include <stdbool.h>

    /*############################# Abstract Type #############################*/



		   /*################################ Function ###############################*/

		void *sprite_cons(SDL_Rect* sprite, int width, int height, int x, int y);
		int Collide(SDL_Rect* m,SDL_Rect* n);
		void CollideDown(SDL_Rect *object, char** table, int X, int Y);

//		int EssaiDeplacement(Sprite* perso,SDL_Rect* mur,int vx,int vy);
		//int DeplaceSprite(Sprite* perso,SDL_Rect* mur, int vx, int vy);
        //void Affine(Sprite* perso,SDL_Rect* mur,int vx,int vy);


#endif // SPRITE_T_H_INCLUDED
