/******************************/
/***** Fichier sprite_t.h *****/
/******************************/
#ifndef SPRITE_T_H_INCLUDED
#define SPRITE_T_H_INCLUDED

    #include <SDL2/SDL.h>
    #include <stdbool.h>

    /*############################# Abstract Type #############################*/



		   /*################################ Function ###############################*/

		void Rect_cons(SDL_Rect *object, int width , int height , int x ,int y );
		void sprite_cons(perso *hero, int width, int height, int x, int y, double Vx, double Vy);
        void sprite_update (perso* hero);
        void Collide(char** tab2, perso *hero, bool *down, bool *Saut, bool* key );
        void retour(vect V, perso *hero, AABB box, double eps);
        bool testpoint(P2D point,AABB box);
        bool testbox(AABB box1,AABB box2);



#endif // SPRITE_T_H_INCLUDED
