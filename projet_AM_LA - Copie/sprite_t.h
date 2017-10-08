#ifndef SPRITE_T_H_INCLUDED
#define SPRITE_T_H_INCLUDED
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

    /*############################# Abstract Type #############################*/



		   /*################################ Function ###############################*/

		void sprite_cons(SDL_Rect* sprite, int width, int height, int x, int y);
		void cursor(SDL_Rect *R_cursor,SDL_Texture* T_cursor,SDL_Renderer *renderer,int power );
        char ** init_tab_dynamic( int x, int y, FILE *fichier );

#endif // SPRITE_T_H_INCLUDED
