
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "constante.h"
#include "sprite_t.h"

#include <stdio.h>
#include <stdlib.h>
char ** init_tab_dynamic( int x, int y, FILE *fichier )
{
     char caracterActuel;
    caracterActuel = NULL;

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
    int largeur_map = WINDOW_WIDTH/NOMBRE_BLOCK_LARGEUR;
    int hauteur_map = WINDOW_HEIGHT/NOMBRE_BLOCK_HAUTEUR;
    int i,j ;
    SDL_RenderClear(renderer);
    SDL_Rect block;
    block.h=HAUTEUR_TILE;
    block.w=LARGEUR_TILE;
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
            case '3':
                block.x = 300;
                break;
            default:
                break;
			}
            R_tileset->x=i*largeur_map;
            R_tileset->y=j*hauteur_map;
            SDL_RenderCopy(renderer,T_tileset,&block, R_tileset);

		}

	}

	SDL_RenderPresent(renderer);

}


int main(int argc, char **argv)
{

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    bool running = true;
    SDL_Texture *T_sprite_hero, *temp, *T_background , *T_sous, *T_tiple;
    SDL_Rect *R_sprite_hero, *R_background , *R_sous, *R_tiple ;
    unsigned int i, j;
    char **tab2 ;


    window = SDL_CreateWindow("Project AMBROZIK LAMBERT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

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
     sprite_cons(R_tiple, WINDOW_WIDTH/NOMBRE_BLOCK_LARGEUR,WINDOW_HEIGHT/NOMBRE_BLOCK_HAUTEUR,0,0 );
    SDL_Rect block;
    block.h=100;
    block.w=100;
    block.y=0;
    block.x=0;

        SDL_RenderCopy(renderer,T_tiple,NULL, R_tiple);

    //afficher gugusse
    T_sprite_hero = NULL;
    temp = NULL;
    R_sprite_hero  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = SDL_LoadBMP("picture/sprite.bmp");
    T_sprite_hero = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(R_sprite_hero, 15,15,10,350);

    //sous
    T_sous = NULL;
    temp = NULL;
    R_sous = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = SDL_LoadBMP("picture/yo.bmp");
    T_sous = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(R_sous, 1900,100,0, 400);

    while (running)
        {

        while (SDL_PollEvent(&event))
            {

                if (event.type == SDL_QUIT) running = false;
                if (event.type== SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_z) R_sprite_hero->y-=10;
                    if (event.key.keysym.sym == SDLK_d)
                    {
                        if ((event.key.keysym.sym == SDLK_z) && (event.key.keysym.sym == SDLK_d) )
                        {

                        }
                        else
                        {
                              R_sprite_hero->x+=10;
                        }

                    }
                    if (event.key.keysym.sym == SDLK_q) R_sprite_hero->x-=10;
                    if (event.key.keysym.sym == SDLK_s) R_sprite_hero->y+=10;

                }


            }
        R_sprite_hero->y++;
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

       // SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer,T_background,NULL, NULL);
        //SDL_RenderCopy(renderer,sous,NULL, ss);
        SDL_RenderCopy(renderer,T_sprite_hero,NULL, R_sprite_hero);
        Afficher(R_tiple, T_tiple,tab2,NOMBRE_BLOCK_LARGEUR,NOMBRE_BLOCK_HAUTEUR, renderer);

        ///////////////////////////text //////////////

        SDL_RenderPresent(renderer);

        SDL_Delay(50);
        }
}
