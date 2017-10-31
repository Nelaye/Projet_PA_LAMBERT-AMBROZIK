
#include "map.h"


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
             tab[i][j] = '0';
        }
   }
    return tab;
}

char ** init_tab_dynamic( int x, int y, FILE *fichier )
{
     char caracterActuel = 0;

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
void afficher_power(sprite_t *glass, char** tab , SDL_Renderer *renderer)
{
    int  i , j  ;
    SDL_Rect block;
    block.h = 20;
    block.w = 20;
    for(i=0;i<NOMBRE_BLOCK_LARGEUR_POWER;i++)
	{
		for(j=0;j<NOMBRE_BLOCK_HAUTEUR_POWER;j++)
		{
		    switch (tab[j][i]) {
            case '0':
              block.x = 0;
              block.y=0;
            break;
            case '1':
              block.x = 20;
              block.y=0;
            break;
            default:
                break;
			}
        glass->R_sprite->x=i*WINDOW_WIDTH/NOMBRE_BLOCK_LARGEUR_POWER;
        glass->R_sprite->y=j*WINDOW_HEIGHT/NOMBRE_BLOCK_HAUTEUR_POWER;

        SDL_RenderCopy(renderer,glass->T_sprite,&block, glass->R_sprite);
		}
	}
}
void Afficher(SDL_Rect *R_tileset,SDL_Texture* T_tileset,char** table,int nombre_blocs_largeur,int nombre_blocs_hauteur, SDL_Renderer *renderer, int scrolling_x,timer t[],int *cpt  )
{
    int largeur_map = WINDOW_WIDTH/nombre_blocs_largeur;
    int hauteur_map = WINDOW_HEIGHT/nombre_blocs_hauteur;
    int i,j, affichage_hauteur ;
    SDL_RenderClear(renderer);
    SDL_Rect block;
    block.h=HAUTEUR_TILE;
    block.w=LARGEUR_TILE;

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
                block.y = 100;
                block.x = block.x + (*cpt/(TILE_4_NOMBRE_ANIM_MILI_SECONDE/10)%TILE_4_NOMBRE_ANIM) * LARGEUR_TILE;
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

void  modifTabPower(mouse m ,char** tab)
{
    int posX, posY ;
    posX = (m.x+10) / (WINDOW_WIDTH/NOMBRE_BLOCK_LARGEUR_POWER) ;
    posY = (m.y+10) / (WINDOW_HEIGHT/NOMBRE_BLOCK_HAUTEUR_POWER) ;
    tab[posY][posX]='1';
}














