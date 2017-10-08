#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#include "constante.h"
#include "sprite_t.h"



/*########################FUNCTION##################*/
char** initialisation_tableau( int x , int y  )
{
  int i,j;
   char ** tab = malloc( x*sizeof(char*) );
   for ( i = 0; i<x; i++ )
   {
      tab[i] = malloc( y*sizeof(char) );
     for ( j = 0; j<y; j++ )
        {
             tab[i][j] =   'o';
        }
   }
    return tab;
}

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
   return tab;
}

void Afficher(SDL_Rect *R_tileset,SDL_Texture* T_tileset,char** table,int nombre_blocs_largeur,int nombre_blocs_hauteur, SDL_Renderer *renderer, int scrolling_x, int* tempsactuel , int* tempsPrecedent,int* cpt  )
{
    int largeur_map = WINDOW_WIDTH/nombre_blocs_largeur;
    int hauteur_map = WINDOW_HEIGHT/nombre_blocs_hauteur;
    int i,j, affichage_hauteur ;
    SDL_RenderClear(renderer);
    SDL_Rect block;
    block.h=HAUTEUR_TILE;
    block.w=LARGEUR_TILE;
    block.y=0;

    affichage_hauteur = NOMBRE_BLOCK_HAUTEUR - NOMBRE_AFFICHER_HAUTEUR;
    for(i=0;i<nombre_blocs_largeur;i++)
	{
		for(j=0;j<nombre_blocs_hauteur;j++)
		{
			switch (table[j+affichage_hauteur][i+scrolling_x]) {
            case '0':
                block.x = 0;
                block.y=0;
                break;
            case '1':
                block.x = 100;
                block.y=0;
                break;
            case '2':
                block.x = 200;
                block.y=0;
                break;
            case '3':
                block.x = 300;
                block.y=0;
                break;
             case '4':
                block.x= * cpt;
                block.y=100;
                if (*tempsactuel - *tempsPrecedent > 1000 )
                {

                    block.x = *cpt  ;

                    if (block.x > 600)
                    {
                        block.x = 0;
                        *cpt = 0 ;
                    }
                    *tempsPrecedent = *tempsactuel ;
                *   cpt = *cpt + 100;
                }

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
