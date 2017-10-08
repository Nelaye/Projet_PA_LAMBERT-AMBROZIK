/******************************/
/***** Fichier sprite_t.h *****/
/******************************/
#ifndef SPRITE_T_H_INCLUDED
#define SPRITE_T_H_INCLUDED

    #include <SDL2/SDL.h>
    #include <stdbool.h>

    /*############################# Abstract Type #############################*/



		   /*################################ Function ###############################*/

		void sprite_cons(SDL_Rect* sprite, int width, int height, int x, int y);
        void Collide(char** tab2, SDL_Rect *hero, bool *Right, bool *Left, bool *Up);

#endif // SPRITE_T_H_INCLUDED
