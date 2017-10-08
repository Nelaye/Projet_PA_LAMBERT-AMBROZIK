
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constante.h"
#include "sprite_t.h"*
#include "map.h"



int main(int argc, char **argv)
{
    int Xmouse,Ymouse ;
    int tempsActuel=0;
    int tempsPrecedent = 0 ;
    int cpt = 0 ;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    bool running = true;
    SDL_Texture *T_sprite_hero, *temp, *T_background , *T_sous, *T_tiple,*T_cursor;
    SDL_Rect *R_sprite_hero, *R_background , *R_sous, *R_tiple,*R_cursor ;
    unsigned int i, j;
    char **monde1,**tab_power ;
    int power;
     int scroll_Larg;
        scroll_Larg = 0 ;

    window = SDL_CreateWindow("Project AMBROZIK LAMBERT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    //charger power cursor
    T_cursor = NULL;
    temp = NULL ;
    R_cursor  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = SDL_LoadBMP("picture/cursor.bmp");
    T_cursor = SDL_CreateTextureFromSurface(renderer, temp);

    //charger background
    T_background = NULL;
    temp = NULL;
    R_background  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = SDL_LoadBMP("picture/1.bmp");
    T_background = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(R_background, 1500,1000,0, 0);
    //charger tiple
    T_tiple = NULL;
    temp = NULL;
    R_tiple  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = SDL_LoadBMP("picture/block.bmp");
    T_tiple = SDL_CreateTextureFromSurface(renderer, temp);
    //charger(R_tiple, T_tiple,table,NOMBRE_BLOCK_LARGEUR,NOMBRE_BLOCK_HAUTEUR);
    sprite_cons(R_tiple, WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR,WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR,0,0 );
    SDL_RenderCopy(renderer,T_tiple,NULL, R_tiple);

    //charger gugusse
    T_sprite_hero = NULL;
    temp = NULL;
    R_sprite_hero  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = SDL_LoadBMP("picture/sprite.bmp");
    T_sprite_hero = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(R_sprite_hero, 15,15,10,350);

    SDL_ShowCursor(SDL_DISABLE);


    while (running)
        {
        SDL_GetMouseState(&Xmouse,&Ymouse) ;
        sprite_cons(R_cursor,CURSOR_WIDTH,CURSOR_HEIGHT,Xmouse-10,Ymouse-10);


        while (SDL_PollEvent(&event))
            {
                //mouvement
                if (event.type == SDL_QUIT) running = false;
                if (event.type== SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_z)
                    {
                        R_sprite_hero->y-=10;
                    }
                    if (event.key.keysym.sym == SDLK_d)
                    {
                        if(R_sprite_hero->x > WINDOW_WIDTH/2 )
                        {

                            R_sprite_hero->x  = WINDOW_WIDTH/2 ;
                            scroll_Larg+=1;
                        }


                            R_sprite_hero->x+=10;

                    }
                    if (event.key.keysym.sym == SDLK_q) R_sprite_hero->x-=10;
                    if (event.key.keysym.sym == SDLK_s) R_sprite_hero->y+=10;

                }
                //power_glass
                if (event.key.keysym.sym == SDLK_1)
                {
                    power = POWER_GLASS ;

                }
               if (event.key.keysym.sym == SDLK_2)
               {
                   power = PISTOL ;
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

        FILE *monde ;
        //monde exemple
        monde = fopen("text.txt", "r");
        monde1 = NULL;

        if (monde==NULL)
        {
            printf("erreur fichier");
            return EXIT_FAILURE ;
        }
        monde1 = init_tab_dynamic(NOMBRE_BLOCK_HAUTEUR,NOMBRE_BLOCK_LARGEUR,monde);
        // power
        tab_power=initialisation_tableau(NOMBRE_BLOCK_LARGEUR_POWER,NOMBRE_BLOCK_HAUTEUR_POWER);
        tempsActuel = SDL_GetTicks();

        fclose(monde) ;

        SDL_RenderCopy(renderer,T_background,NULL, NULL);

        Afficher(R_tiple, T_tiple,monde1,NOMBRE_AFFICHER_LARGEUR,NOMBRE_AFFICHER_HAUTEUR, renderer,scroll_Larg,&tempsActuel, &tempsPrecedent, &cpt );
        SDL_RenderCopy(renderer,T_sprite_hero,NULL, R_sprite_hero);
        cursor(R_cursor, T_cursor,renderer,power );
        ///////////////////////////text //////////////

        SDL_RenderPresent(renderer);

        SDL_Delay(50);
        }
}
