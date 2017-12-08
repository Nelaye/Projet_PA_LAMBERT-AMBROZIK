#include "niveau.h"

/*int start(SDL_Renderer* renderer , sprite_t* background, int* touche_actif)
{
    TTF_Font *police;
    SDL_Rect pos;
    SDL_Texture *texture ;
    pos.x = 500;
    pos.y = 250 ;
    char start = "PRESS SPACE TO START" ;
    SDL_Color write={255,255,255};
    SDL_Surface *surface= TTF_RenderText_Solid(police, start,write);
    texture= SDL_CreateTextureFromSurface(renderer,surface);
    SDL_RenderCopy(renderer,texture,NULL,&pos);

    SDL_RenderCopy(renderer,background->T_sprite,NULL, background->R_sprite);
    if (touche_actif[space]==1){
        touche_actif[space]=0;
        return MENU_HERO;
    }

}*/
level init_level(char** monde_tab ,char** power_tab, char monde_text )
{
    level l ;
    FILE *monde;
    monde = fopen(monde_text , "r");
    if (monde==NULL){
        printf("erreur fichier");

    }
    monde_tab = init_tab_dynamic(NOMBRE_BLOCK_HAUTEUR,NOMBRE_BLOCK_LARGEUR,monde);
    fclose(monde);
    power_tab = initialisation_tableau(30,400);

    l.monde=monde_tab ;
    l.power=power_tab ;
    return l ;
}

