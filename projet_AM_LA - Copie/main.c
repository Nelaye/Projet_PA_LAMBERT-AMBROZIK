
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constante.h"
#include "sprite_t.h"
#include "map.h"
#include <SDL2/SDL_image.h>


int main(int argc, char **argv)
{
    int touche_actif[5]={0,0,0,0,0};
    int go = 0 ;
    int kaka = 0 ;
    mouse m ;
    m.print = false ;
    vecteur vbullet;
    double tempsActuel=0;
    double tempsPrecedent = 0 ;
    int anim = 0 ;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    bool running = true;
    sprite_t  *background , *tiple , *curseur, *glass,*menu, *joueur1 , *joueur2 , *bras ;
    character *hero;
    SDL_Rect block1, b_bras ;
    SDL_Surface *temp ;
    bullet b ;
    unsigned int i, j;
    char **monde1,**tab_power ;
    int power;
    float scroll_Larg;
    scroll_Larg = 0 ;
    tab_power = NULL;
    monde1 = NULL;
    window = SDL_CreateWindow("Project AMBROZIK LAMBERT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, 0);
    //charger bullet
    b.T_Bullet = NULL;
    temp = NULL;
    b.R_Bullet = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/bullet.bmp");
    b.T_Bullet = SDL_CreateTextureFromSurface(renderer, temp);
    b.x= 0 ;
    b.y = 0 ;
    //charger power/pistol cursor
    curseur = (sprite_t*)malloc(sizeof(sprite_t));
    curseur->T_sprite = NULL;
    temp = NULL ;
    curseur->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/cursor.bmp");
    curseur->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    //charger menu
       menu = (sprite_t*)malloc(sizeof(sprite_t));
    menu->T_sprite = NULL;
    temp = NULL ;
    menu->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/menu.xcf");
    menu->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(menu, WINDOW_WIDTH,WINDOW_HEIGHT,0,0 );
    menu->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    //charger bras
       bras = (sprite_t*)malloc(sizeof(sprite_t));
    bras->T_sprite = NULL;
    temp = NULL ;
    bras->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/bras.xcf");
    bras->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    //b_level = initialization_animation(PICTURE_LEVEL_WIDTH,PICTURE_LEVEL_HEIGHT,0,0);
    sprite_cons(bras,WINDOW_WIDTH,WINDOW_HEIGHT,0,0);
    //charger joueur1
    joueur1 = (sprite_t*)malloc(sizeof(sprite_t));
    joueur1->T_sprite = NULL;
    temp = NULL ;
    joueur1->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/joueur_1.xcf");
    joueur1->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(joueur1, 200,200,200,200 );
    //charger joueur2
    joueur2 = (sprite_t*)malloc(sizeof(sprite_t));
    joueur2->T_sprite = NULL;
    temp = NULL ;
    joueur2->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/joueur_2.xcf");
    joueur2->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(joueur2, 200,200,600,200 );
    //charger tiple
    tiple = (sprite_t*)malloc(sizeof(sprite_t));
    tiple->T_sprite = NULL;
    temp = NULL;
    tiple->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/block.xcf");
    tiple->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(tiple, WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR,WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR,0,0 );
    //charger glass
    glass = (sprite_t*)malloc(sizeof(sprite_t));
    glass->T_sprite = NULL;
    temp =NULL;
    glass->R_sprite = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/block_glass.xcf");
    glass->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(glass,WINDOW_WIDTH/NOMBRE_BLOCK_LARGEUR_POWER ,WINDOW_HEIGHT/NOMBRE_BLOCK_HAUTEUR_POWER , 0, 0);
    //charger gugusse
    hero = (sprite_t*)malloc(sizeof(sprite_t));
    hero->T_sprite= NULL;

    hero->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    //touche



    int jeu = 0 ;



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
                        sprite_cons(curseur,CURSOR_WIDTH,CURSOR_HEIGHT,m.x,m.y);

                    }
                    if (event.type)
                    if (event.type== SDL_KEYDOWN)
                    {
                        if (event.key.keysym.sym == SDLK_z)
                        {
                            hero->R_sprite->y-=10;
                              touche_actif[0]=1;
                        }
                        if (event.key.keysym.sym == SDLK_d)
                        {
                            touche_actif[1]=1;
                            if(hero->R_sprite->x > WINDOW_WIDTH/2 )
                            {

                                hero->R_sprite->x  = WINDOW_WIDTH/2 ;
                                scroll_Larg+=1;

                            }


                                hero->R_sprite->x+=10;

                            block1 = right_movement(hero, m, block1);

                        }
                        if (event.key.keysym.sym == SDLK_q)
                        {
                               touche_actif[2]=1;
                            hero->R_sprite->x-=10;

                            block1 = left_movement(hero, m, block1);

                        }
                        if (event.key.keysym.sym == SDLK_s) hero->R_sprite->y+=10;
                        if (event.key.keysym.sym == !SDLK_s)
                        {
                             touche_actif[3]=1;

                        }

                    }
                    //power_glass
                    if (event.key.keysym.sym == SDLK_1)
                    {
                        m.print = true ;
                        power = POWER_GLASS ;
                    }
                    if (event.key.keysym.sym == SDLK_2)
                    {
                        m.print = true ;
                        power = PISTOL ;
                    }
                    if (event.key.keysym.sym == SDLK_3 )
                    {
                        if ( power == PISTOL )
                        {
                            b.x = hero->R_sprite->x ;
                            b.y = hero->R_sprite->y ;
                            vbullet = sbullet(hero->R_sprite,m.x,m.y );
                        }
                        if (power == POWER_GLASS )
                        {
                            modifTabPower(m ,tab_power);
                        }
                    }
                    if (event.key.keysym.sym == SDLK_4)
                    {
                    }
                    if(touche_actif[2]==0 && touche_actif[1]==0 )
                {
                    if (m.x > hero->R_sprite->x)
                    {
                        animation_boucle(&block1,GAUCHE);
                    }
                    else
                    {
                        animation_boucle(&block1,DROIT);
                    }
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
            //////////menu///////////////////
   touche_actif[1]=0;
                 touche_actif[2]=0;
    if(jeu == 0 )
        {

            sprite_cons(menu, WINDOW_WIDTH,WINDOW_HEIGHT,0,0 );
            SDL_RenderCopy(renderer,menu->T_sprite,NULL, menu->R_sprite);
            SDL_RenderCopy(renderer,joueur1->T_sprite,NULL, joueur1->R_sprite);
            SDL_RenderCopy(renderer,joueur2->T_sprite,NULL, joueur2->R_sprite);

                if((m.x>200 && m.x<400)&& (m.y>200 && m.y<400))
                {
                    joueur1->R_sprite->y=joueur1->R_sprite->y-1 ;
                }
                if((m.x>600 && m.x<800)&& (m.y>200 && m.y<400))
                {
                    joueur2->R_sprite->y=joueur2->R_sprite->y-1 ;
                }

                if (joueur1->R_sprite->y==0)
                {
                    hero->player = 1 ;
                    jeu  = 1 ;
                    temp = IMG_Load("picture/joueur_1_animation.xcf");
                    hero->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
                }
                if (joueur2->R_sprite->y==0)
                {
                    hero->player = 2 ;
                    jeu  = 1 ;
                    temp = NULL;
                    temp = IMG_Load("picture/joueur_2_animation.xcf");
                    hero->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);

                }

        }
        //////////////////////NIVEAU 1 //////////////////////////////////

        else if(jeu == 1)
            {

            //////initialisation joueur///////
            if (go == 0 )
            {

                b_bras = initialization_animation(10,10,0,0);
                block1 = initialization_animation(PICTURE_HERO_WIDTH,PICTURE_HERO_HEIGHT,0,4);
                initialization(hero, HERO,SPRITE_HERO_WIDTH,SPRITE_HERO_HEIGHT,HERO_START_POS_X,HERO_START_POS_Y);
                go = 1 ;
            }

            //////initialisation power///////
            if (tab_power == NULL)
            {
             tab_power=initialisation_tableau(NOMBRE_BLOCK_HAUTEUR_POWER,NOMBRE_BLOCK_LARGEUR_POWER);
            }
            /////initialisation tile ////////
            if (monde1 == NULL)
            {
                SDL_ShowCursor(SDL_DISABLE);
                FILE *monde ;
                monde = fopen("text.txt", "r");
                if (monde==NULL)
                {
                    printf("erreur fichier");
                    return EXIT_FAILURE ;
                }
                monde1 = init_tab_dynamic(NOMBRE_BLOCK_HAUTEUR,NOMBRE_BLOCK_LARGEUR,monde);
                fclose(monde);
            }
            //////////////////////PRINT/////////////
           // Afficher(tiple->R_sprite, tiple->T_sprite,monde1,NOMBRE_AFFICHER_LARGEUR,NOMBRE_AFFICHER_HAUTEUR, renderer,scroll_Larg,&tempsActuel, &tempsPrecedent);
            afficher_power(glass,tab_power,renderer);

            sprite_cons(bras,50,50,hero->R_sprite->x-10,hero->R_sprite->y-10);
            aim_arm(bras,m,&b_bras,power);
            SDL_RenderCopy(renderer,hero->T_sprite,&block1, hero->R_sprite);
            SDL_RenderCopy(renderer,bras->T_sprite,&b_bras, bras->R_sprite);

            cursor(curseur , renderer,power );
            if(b.x != 0 && b.y != 0 )
            {
                update_bullet(&b, vbullet ,renderer);
            }
        }

        ///////////////////////////text //////////////
        SDL_RenderPresent(renderer);
        tempsPrecedent = tempsActuel;

            }
            else
            {
                SDL_Delay((1000.0/120.0)-(tempsActuel - tempsPrecedent) );
            }
          SDL_RenderClear(renderer);

        }

        SDL_DestroyTexture(hero);
        SDL_DestroyTexture(tiple);
        SDL_DestroyTexture(curseur);
        SDL_DestroyTexture(glass);
}

