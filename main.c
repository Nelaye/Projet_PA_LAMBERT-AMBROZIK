/************************************************************/
/*********** PROJET LAMBERT Emilien AMBROZIK Hugo ***********/
/************* ANNEE: 2017 LICENCE INFORMATIQUE *************/
/** SEMESTRE 3 FACULTE DE SCIENCES ET TECHNOLOGIE DE NANCY **/

/************************************************************/

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "constante.h"

#include "sprite_t.h"
#include "event.h"
#include "animation.h"

char ** init_tab_dynamic( int x, int y, FILE *fichier )
{
    char caracterActuel= NULL;

    int i,j;
    char ** tab = malloc( x*sizeof(char*) );
    for ( i = 0; i<x; i++ )
    {
        tab[i] = malloc( y*sizeof(char) );
        for ( j = 0; j<y; j++ )
        {
            if(caracterActuel != EOF)
            {
                caracterActuel = fgetc(fichier);
                if(caracterActuel=='\n')
                {
                    caracterActuel = fgetc(fichier);
                }
            tab[i][j] =  caracterActuel ;

            }
        }
   }
   fclose(fichier) ;
   return tab;
}

void Afficher(SDL_Rect *R_tileset,SDL_Texture* T_tileset,char** table,int nombre_blocs_largeur,int nombre_blocs_hauteur, SDL_Renderer *renderer)
{
    int i,j ;
    SDL_RenderClear(renderer);
    SDL_Rect block;
    block.h=100;
    block.w=100;
    block.y=0;
    for(i=0;i<NOMBRE_BLOCK_LARGEUR;i++)
	{
		for(j=0;j<NOMBRE_BLOCK_HAUTEUR;j++)
		{
			switch (table[j][i]) {
            case '0':
                block.x = 0;
                break;
            case '1':
                block.x = 100;
                break;
            case '2':
                block.x = 200;
                break;
            default:
                break;
			}
            R_tileset->x=i*LARGEUR_TILE;
            R_tileset->y=j*HAUTEUR_TILE;
            SDL_RenderCopy(renderer,T_tileset,&block, R_tileset);

		}

	}

	SDL_RenderPresent(renderer);

}
/************************************************************/
int main(int argc, char **argv)
{
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;

  SDL_Event event;

  bool running = true;
  bool Right = true;
  bool Left = true;
  bool Up = true;
  bool Saut= false;

  int compt=0;

    SDL_Texture *T_sprite_hero, *T_background, *T_tiple;
    SDL_Rect *R_sprite_hero, *R_background, *R_tiple;
    SDL_Surface *temp;

    char **tab2 ;

    window = SDL_CreateWindow("Project AMBROZIK LAMBERT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);


/*************************load picture*******************************/

    //afficher background
    T_background = NULL;
    temp = NULL;
    R_background  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = SDL_LoadBMP("picture/1.bmp");
    T_background = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(R_background, 1500,1000,0, 0);

    //afficher tiple
    T_tiple = NULL;
    temp = NULL;
    R_tiple  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = SDL_LoadBMP("picture/block.bmp");
    T_tiple = SDL_CreateTextureFromSurface(renderer, temp);

    //Afficher(R_tiple, T_tiple,table,NOMBRE_BLOCK_LARGEUR,NOMBRE_BLOCK_HAUTEUR);
    sprite_cons(R_tiple, 50,50,0,0 );
    SDL_Rect block;
    block.h=15;
    block.w=15;
    block.y=0;
    block.x=0;

    SDL_RenderCopy(renderer,T_tiple,NULL, R_tiple);

    //afficher gugusse
    T_sprite_hero = NULL;
    temp = NULL;
    R_sprite_hero  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = SDL_LoadBMP("picture/sprite.bmp");
    T_sprite_hero = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(R_sprite_hero, 20,20,10,50);



/********************************************************************************/
    while (running)
        {

        while (SDL_PollEvent(&event))
            {

                if (event.type == SDL_QUIT) running = false;

                if (event.type== SDL_KEYDOWN)
                {
                    if ((event.key.keysym.sym == SDLK_z) && (Up==true))
                    {
                        Saut=true;
                    }

                    if (event.key.keysym.sym == SDLK_d)
                    {
                         if ((event.key.keysym.sym == SDLK_z) && (event.key.keysym.sym == SDLK_d) )
                        {

                        }
                        else
                        {
                            if (Right==true)
                            {
                                R_sprite_hero->x+=5;

                            }

                        }

                    }
                    if ((event.key.keysym.sym == SDLK_q) &&  (Left == true))
                    {
                        R_sprite_hero->x-=5;

                    }

                    if (event.key.keysym.sym == SDLK_s)
                    {


                    }


                    //X=R_sprite_hero->x/LARGEUR_TILE;
                    //Y=R_sprite_hero->y/HAUTEUR_TILE;



                }//end if keydown
            }// end while pollenvent


        /**DeplaceSprite(R_sprite_hero,);**/

        if(R_sprite_hero->x<0)
        {
            R_sprite_hero->x=0;
        }

        if(R_sprite_hero->y+SPRITE_HERO_HEIGHT>WINDOW_HEIGHT)
        {
            R_sprite_hero->y=WINDOW_HEIGHT-SPRITE_HERO_HEIGHT;
        }

        if(R_sprite_hero->x+SPRITE_HERO_WIDTH>WINDOW_WIDTH)
        {
            R_sprite_hero->x=WINDOW_WIDTH-SPRITE_HERO_WIDTH;
        }

        if(R_sprite_hero->y<0)
        {
            R_sprite_hero->y=0;
        }

        if (Saut == true)
        {
            R_sprite_hero->y = R_sprite_hero->y - 10;
            compt = compt + 1;

            if (compt==10)
            {
                Saut=false;
                compt=0;
            }
        }

        //monde exemple
        FILE *fichier;
        fichier = fopen("text.txt", "r");
        tab2 = NULL;
        if (fichier==NULL)
        {
            printf("erreur fichier");
            return EXIT_FAILURE ;
        }
        tab2 = init_tab_dynamic(NOMBRE_BLOCK_HAUTEUR,NOMBRE_BLOCK_LARGEUR,fichier);

        /** Test d�placement**/

        Collide(tab2, R_sprite_hero, &Right, &Left, &Up);

        /** Draw **/

        SDL_RenderCopy(renderer,T_background,NULL, NULL);

        Afficher(R_tiple, T_tiple,tab2,NOMBRE_BLOCK_LARGEUR,NOMBRE_BLOCK_HAUTEUR, renderer);

        SDL_RenderCopy(renderer,T_sprite_hero,NULL, R_sprite_hero);

        ///////////////////////////text //////////////

        SDL_RenderPresent(renderer);

        SDL_Delay(20);
        }
    return 1;
    }
