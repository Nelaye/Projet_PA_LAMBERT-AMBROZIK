
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constante.h"
#include "sprite_t.h"
#include "map.h"




int main(int argc, char **argv)
{

    mouse m ;
    vecteur vbullet;
    double tempsActuel=0;
    double tempsPrecedent = 0 ;
    int cpt = 0 ;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    bool running = true;
    sprite_t *hero , *background , *tiple , *curseur ;
    //SDL_Texture *T_sprite_hero, *temp, *T_background , *T_sous, *T_tiple,*T_cursor;
    //SDL_Rect *R_sprite_hero, *R_background , *R_sous, *R_tiple,*R_cursor ;
    SDL_Surface *temp ;
    bullet b ;
    unsigned int i, j;
    char **monde1,**tab_power ;
    int power;
    float scroll_Larg;
    scroll_Larg = 0 ;


    window = SDL_CreateWindow("Project AMBROZIK LAMBERT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    //charger bullet

    b.T_Bullet = NULL;
    temp = NULL;
    b.R_Bullet = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = SDL_LoadBMP("picture/bullet.bmp");
    b.T_Bullet = SDL_CreateTextureFromSurface(renderer, temp);
    b.x= 0 ;
    b.y = 0 ;
    //charger power cursor
    curseur = (sprite_t*)malloc(sizeof(sprite_t));
    curseur->T_sprite = NULL;
    temp = NULL ;
    curseur->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = SDL_LoadBMP("picture/cursor.bmp");
    curseur->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    //charger tiple
    tiple = (sprite_t*)malloc(sizeof(sprite_t));
    tiple->T_sprite = NULL;
    temp = NULL;
    tiple->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = SDL_LoadBMP("picture/block.bmp");
    tiple->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);

    sprite_cons(tiple, WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR,WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR,0,0 );

    SDL_RenderCopy(renderer,tiple->T_sprite,NULL, tiple->R_sprite);

    //charger gugusse
    hero = (sprite_t*)malloc(sizeof(sprite_t));
    hero->T_sprite= NULL;
    temp = NULL;
    hero->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = SDL_LoadBMP("picture/sprite.bmp");
    hero->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(hero, 15,15,10,350);

    SDL_ShowCursor(SDL_DISABLE);


    while (running)
        {
            tempsActuel = SDL_GetTicks();
            if (tempsActuel -tempsPrecedent > 1000.0/120.0)
            {


        while (SDL_PollEvent(&event))
            {
                //mouvement
                if (event.type == SDL_QUIT) running = false;
                if (event.type == SDL_MOUSEMOTION)
                {
                    m.x = event.motion.x ;
                    m.y = event.motion.y ;
                    sprite_cons(curseur,CURSOR_WIDTH,CURSOR_HEIGHT,m.x-10,m.y-10);
                }
                if (event.type== SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_z)
                    {
                        hero->R_sprite->y-=10;
                    }
                    if (event.key.keysym.sym == SDLK_d)
                    {
                        if(hero->R_sprite->x > WINDOW_WIDTH/2 )
                        {

                            hero->R_sprite->x  = WINDOW_WIDTH/2 ;
                            scroll_Larg+=1;
                        }


                            hero->R_sprite->x+=10;

                    }
                    if (event.key.keysym.sym == SDLK_q) hero->R_sprite->x-=10;
                    if (event.key.keysym.sym == SDLK_s) hero->R_sprite->y+=10;

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
               if (event.key.keysym.sym == SDLK_3)
               {
                   b.x = hero->R_sprite->x ;
                   b.y = hero->R_sprite->y ;
                   vbullet = sbullet(hero->R_sprite,m.x,m.y );
               }
               if (event.key.keysym.sym == SDLK_4)
               {
               }

            }
        hero->R_sprite->y++;
        if(hero->R_sprite->x<0)
        {
            hero->R_sprite->x=0;
        }
        if(hero->R_sprite->y+SPRITE_HERO_HEIGHT>WINDOW_HEIGHT)
        {
            hero->R_sprite->y=WINDOW_HEIGHT-SPRITE_HERO_HEIGHT;
        }
        if(hero->R_sprite->x+SPRITE_HERO_WIDTH>WINDOW_WIDTH)
        {
            hero->R_sprite->x=WINDOW_WIDTH-SPRITE_HERO_WIDTH;
        }
        if(hero->R_sprite->y<0)
        {
            hero->R_sprite->y=0;
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

        fclose(monde) ;
        // power
        tab_power=initialisation_tableau(NOMBRE_BLOCK_LARGEUR_POWER,NOMBRE_BLOCK_HAUTEUR_POWER);







        //SDL_RenderCopy(renderer,T_background,NULL, NULL);

        Afficher(tiple->R_sprite, tiple->T_sprite,monde1,NOMBRE_AFFICHER_LARGEUR,NOMBRE_AFFICHER_HAUTEUR, renderer,scroll_Larg,&tempsActuel, &tempsPrecedent, &cpt );
        SDL_RenderCopy(renderer,hero->T_sprite,NULL, hero->R_sprite);
        cursor(curseur , renderer,power );
        //cursor(curseur->R_sprite,curseur->T_sprite ,renderer,power );
         if(b.x != 0 && b.y != 0 )
        {

            update_bullet(&b, vbullet ,renderer);
        }
        ///////////////////////////text //////////////

        SDL_RenderPresent(renderer);
        tempsPrecedent = tempsActuel;

            }
            else
            {
                SDL_Delay((1000.0/120.0)-(tempsActuel - tempsPrecedent) );
            }
        }
}

