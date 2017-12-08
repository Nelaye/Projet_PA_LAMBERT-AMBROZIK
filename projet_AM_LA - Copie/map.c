
#include "map.h"


/*########################FUNCTION##################*/

char** initialisation_tableau( int x , int y  ){
    int i,j;
    char ** tab = malloc( x*sizeof(char*) );

    for ( i = 0; i<x; i++ ){
        tab[i] = malloc( y*sizeof(char) );

        for ( j = 0; j<y; j++ ){
            tab[i][j] = '0';
        }
    }
    return tab;
}

char** init_tab_dynamic( int x, int y, FILE *file ){
    int i,j;
    char caracterActuel = 0;
    char ** tab = malloc( x*sizeof(char*) );

    for ( i = 0; i<x; i++ ){
        tab[i] = malloc( y*sizeof(char) );

        for ( j = 0; j<y; j++ ){

            if(caracterActuel != EOF){
                caracterActuel = fgetc(file);

                if(caracterActuel=='\n'){
                    caracterActuel = fgetc(file);

                }
                tab[i][j] =  caracterActuel ;
            }
        }
    }
    return tab;
}





void Afficher( SDL_Rect *R_tileset,SDL_Texture* T_tileset,char** table,int nombre_blocs_largeur,int nombre_blocs_hauteur, SDL_Renderer *renderer, int scrolling_x, bool scrolling_actif, int *cpt, character* ship )
{
    int largeur_map = WINDOW_WIDTH/nombre_blocs_largeur;
    int hauteur_map = WINDOW_HEIGHT/nombre_blocs_hauteur;
    int x,i,j,k;
    SDL_Rect block;
    block.h=HAUTEUR_TILE;
    block.w=LARGEUR_TILE;
    k =(largeur_map/10)*10;
    x = (scrolling_x/k);

    for(i=0;i<nombre_blocs_largeur+2+(largeur_map - k) ;i++)
	{
		for(j=0;j<nombre_blocs_hauteur;j++)
		{
			switch (table[j][i+x]) {
            case '0':
                block.x = 0;
                block.y=0;
                break;
            case '1':
                block.x = LARGEUR_TILE;
                block.y=0;
                break;
            case '2':
                block.x = LARGEUR_TILE * 2;
                block.y=0;
                break;
            case '3':
                block.x = LARGEUR_TILE * 3;
                block.y=0;
                break;
            case '4':
                block.y = HAUTEUR_TILE;
                block.x = block.x + (*cpt/(TILE_4_NOMBRE_ANIM_MILI_SECONDE/10)%TILE_4_NOMBRE_ANIM) * LARGEUR_TILE;
            break;
            case 'B':
                ship->print = true ;
                scrolling_actif = false;
                table[j][i+x]='0';

            default:
                break;
			}
			R_tileset->x=i*largeur_map- scrolling_x%((100/nombre_blocs_largeur)*10);

            R_tileset->y=j*hauteur_map;
            SDL_RenderCopy(renderer,T_tileset,&block, R_tileset);
		}

	}
}

void  modifTabPower(mouse m,int scrolling ,char** tab)
{
    int posX, posY ;


    posX = (m.x+10+ scrolling ) / ((WINDOW_WIDTH)/NOMBRE_AFFICHER_LARGEUR_POWER)  ;
    posY = (m.y+10) / (WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR_POWER) ;

        tab[posY][posX]='1';

}
/*int  compteur_tab_power( char** tab, char valeur_a_chercher)
{
    int i , j , *cpt ;
    for(i=0;i<NOMBRE_BLOCK_LARGEUR_POWER;i++)
	{
        for(j=0;j<NOMBRE_BLOCK_HAUTEUR_POWER;j++)
		{
		    if (tab[j][i]=valeur_a_chercher)
            {
                cpt = cpt + 1;
            }
		}
	}
    return cpt;
}
*/











