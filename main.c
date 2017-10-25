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
        caracterActuel = 48;
        j = 0;
        while (caracterActuel != '\n')
        {
            caracterActuel = fgetc(fichier);
            if (caracterActuel != '\n')
            {
                tab[i][j] =  caracterActuel ;
                j = j +1;
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

    double grav=0.2;


    SDL_Texture *T_sprite_hero, *T_background, *T_tiple;
    SDL_Rect *R_background, *R_tiple;
    SDL_Surface *temp;
    perso *hero = malloc(sizeof(perso));

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
    Rect_cons(R_background, 1500,1000,0,0);

    //afficher tiple
    T_tiple = NULL;
    temp = NULL;
    R_tiple  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = SDL_LoadBMP("picture/block.bmp");
    T_tiple = SDL_CreateTextureFromSurface(renderer, temp);

    //Afficher(R_tiple, T_tiple,table,NOMBRE_BLOCK_LARGEUR,NOMBRE_BLOCK_HAUTEUR);
    Rect_cons(R_tiple, 50,50,0,0);
    SDL_Rect block;
    block.h=15;
    block.w=15;
    block.y=0;
    block.x=0;

    SDL_RenderCopy(renderer,T_tiple,NULL, R_tiple);

    //afficher gugusse
    T_sprite_hero = NULL;
    temp = NULL;
    temp = SDL_LoadBMP("picture/sprite.bmp");
    T_sprite_hero = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(hero, 20,20,0,0,0,0);


    //monde exemple
    FILE *fichier;
    fichier = fopen("text.txt", "r");

    if (fichier==NULL)
    {
        printf("erreur fichier");
        return EXIT_FAILURE ;
    }

    tab2 = init_tab_dynamic(NOMBRE_BLOCK_HAUTEUR,NOMBRE_BLOCK_LARGEUR,fichier);

/********************************************************************************/
bool key[SDL_NUM_SCANCODES] = {0};


    while (running)
        {
            hero->pos.x=0;
        while (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    {
                        running=false;
                        break;
                    }
                case SDL_KEYDOWN:
                    {
                        key[event.key.keysym.scancode] = true;
                        break;
                    }
                case SDL_KEYUP:
                    {
                        key[event.key.keysym.scancode] = false;
                        break;
                    }
                }
            }

            if (key[SDL_SCANCODE_W])
            {
                hero->pos.y = -4;
            }
            if (key[SDL_SCANCODE_A])
            {
                hero->pos.x=-5;
            }
             if (key[SDL_SCANCODE_D])
            {
                hero->pos.x=5;
            }
            if (key[SDL_SCANCODE_ESCAPE])
            {
                running = false;
            }

        // end while pollenvent

        /** Test déplacement**/


        hero->position.x += hero->pos.x;
        hero->position.y += hero->pos.y;

        sprite_update(hero);

        Collide(tab2, hero, &Right, &Left, &Up, &Saut);

        if(hero->pos.y+grav<HAUTEUR_TILE)
        {
            hero->pos.y += grav;
        }

        /** Hyper espace **/

        if(hero->position.x<0)
        {
            hero->position.x=0;
        }

        if(hero->position.y+SPRITE_HERO_HEIGHT>WINDOW_HEIGHT)
        {
            hero->position.y=WINDOW_HEIGHT-SPRITE_HERO_HEIGHT;
        }

        if(hero->position.x+SPRITE_HERO_WIDTH>WINDOW_WIDTH)
        {
            hero->position.x=WINDOW_WIDTH-SPRITE_HERO_WIDTH;
        }

        if(hero->position.y<0)
        {
            hero->position.y=0;
            hero->pos.y=0;
        }





        /** Draw **/

        SDL_RenderCopy(renderer,T_background,NULL, NULL);

        Afficher(R_tiple, T_tiple,tab2,NOMBRE_BLOCK_LARGEUR,NOMBRE_BLOCK_HAUTEUR, renderer);

        SDL_RenderCopy(renderer,T_sprite_hero,NULL, &(hero->position));

        ///////////////////////////text //////////////

        SDL_RenderPresent(renderer);

        SDL_Delay(20);
        }
    return 1;
        }
