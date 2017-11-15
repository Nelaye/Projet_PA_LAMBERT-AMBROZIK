
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "constante.h"
#include "sprite_t.h"
#include "map.h"
#include <SDL2/SDL_image.h>


int main(int argc, char **argv)
{
    int touche_actif[5]={0,0,0,0,0};
    int go = 0 ;
    int i ;
    int cpt = 0 ;
    timer t ,t_glass, cpt_t   ;
    t_glass.previousTime=0;
    cpt_t.previousTime = 0 ;
    t.previousTime = 0 ;
    mouse m ;
    m.print = false ;
    vecteur vbullet;
    double tempsActuel=0;
    double tempsPrecedent = 0 ;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    bool running = true;
    sprite_t   *tiple , *curseur, *glass,*menu, *joueur1 , *joueur2 , *bras , *background;
    character *hero;
    SDL_Rect block1, b_bras ;
    SDL_Surface *temp ;
    bullet b[NB_MAX_BULLETS] ;
    char **monde1,**tab_power ;
    int power;

    float scroll_Larg;
    scroll_Larg = 0 ;
    tab_power = NULL;
    monde1 = NULL;
    window = SDL_CreateWindow("Project AMBROZIK LAMBERT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, 0);
    //charger bullet
    for(i=0; i < NB_MAX_BULLETS; i++)
    {
    b[i].T_Bullet = NULL;
    temp = NULL;
    b[i].R_Bullet = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/bullet.xcf");
    b[i].T_Bullet = SDL_CreateTextureFromSurface(renderer, temp);
    b[i].x= 0 ;
    b[i].y = 0 ;
    b[i].print = false ;
    }
    //charger background
     background = (sprite_t*)malloc(sizeof(sprite_t));
    background->T_sprite = NULL;
    temp = NULL ;
    background->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/background.jpg");
    background->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(background, WINDOW_WIDTH,WINDOW_HEIGHT,0,0 );
    background->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    //charger power/pistol cursor
    curseur = (sprite_t*)malloc(sizeof(sprite_t));
    curseur->T_sprite = NULL;
    temp = NULL ;
    curseur->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/cursor.xcf");
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
    temp = IMG_Load("picture/block.png");
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
    hero = (character*)malloc(sizeof(character));
    hero->T_sprite= NULL;

    hero->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    //touche

    int jeu = 0 ;

    while (running)
        {
        SDL_SetRenderDrawColor(renderer,100,100,100,10);
        t_glass.actualTime =   SDL_GetTicks();
        cpt_t.actualTime =  SDL_GetTicks();
        ////////////////compteur ////////////

        if (cpt_t.actualTime - cpt_t.previousTime > 1 )
        {
            cpt = cpt + 1 ;
            cpt_t.previousTime = cpt_t.actualTime;
        }
        if (cpt> 10000)
        {
            cpt = 0 ;
        }
        t.actualTime = SDL_GetTicks();
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
                    if(event.type==SDL_KEYUP)
                    {
                         if (event.key.keysym.sym == SDLK_z)
                         {
                             touche_actif[0]=0 ;
                         }
                           if (event.key.keysym.sym == SDLK_d)
                         {
                             touche_actif[1]=0 ;
                         }
                           if (event.key.keysym.sym == SDLK_s)
                         {
                             touche_actif[2]=0 ;
                         }
                           if (event.key.keysym.sym == SDLK_q)
                         {
                             touche_actif[3]=0 ;
                         }
                    }
                    if (event.type== SDL_KEYDOWN)
                    {
                        if (event.key.keysym.sym == SDLK_ESCAPE) running = false ;
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

                                block1 = right_movement(hero, m,&t, block1,0.2);

                        }
                        if (event.key.keysym.sym == SDLK_s)
                        {
                            hero->R_sprite->y+=10;
                            touche_actif[2]=1;
                        }
                        if (event.key.keysym.sym == SDLK_q)
                        {
                               touche_actif[3]=1;
                            hero->R_sprite->x-=10;

                            block1 = left_movement(hero, m,&t, block1, 0.2 );

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
                            for(i=0; i < NB_MAX_BULLETS ; i++)
                            {
                                if( !b[i].print )
                                {
                                    b[i].x = hero->R_sprite->x ;
                                    b[i].y = hero->R_sprite->y ;
                                    b[i].v = sbullet(hero->R_sprite,m.x,m.y );
                                    b[i].print = true ;
                                    break;
                                }
                            }

                        }

                        if (power == POWER_GLASS )
                        {
                            modifTabPower(m ,tab_power);
                        }
                    }

                     if (event.key.keysym.sym == SDLK_m )
                    {
                        if ( power == PISTOL )
                        {
                            for(i=0; i < NB_MAX_BULLETS ; i=i+3)
                            {
                                if( !b[i].print)
                                {
                                    b[i].x = hero->R_sprite->x ;
                                    b[i].y = hero->R_sprite->y ;
                                    b[i].v = sbullet(hero->R_sprite,m.x,m.y );
                                    b[i].print = true ;

                                     b[i+1].x = hero->R_sprite->x ;
                                    b[i+1].y = hero->R_sprite->y ;
                                    b[i+1].v = sbullet(hero->R_sprite,m.x+30,m.y+30 );
                                    b[i+1].print = true ;

                                     b[i+2].x = hero->R_sprite->x ;
                                    b[i+2].y = hero->R_sprite->y ;
                                    b[i+2].v = sbullet(hero->R_sprite,m.x-30,m.y-30 );
                                    b[i+2].print = true ;
                                    break;
                                }
                            }

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
            if(hero->R_sprite->x+SPRITE_HERO_WIDTH>WINDOW_WIDTH)
            {
                hero->R_sprite->x=WINDOW_WIDTH-SPRITE_HERO_WIDTH;
            }
            if(hero->R_sprite->y<0)
            {
                hero->R_sprite->y=0;
            }

            if(touche_actif[3]==0 && touche_actif[1]==0 )
               {
                    if (m.x > hero->R_sprite->x)
                    {
                        animation_boucle(&block1,GAUCHE, &t, 0.50);
                    }
                    else
                    {
                        animation_boucle(&block1,DROIT, &t, 0.50 );
                    }
                }
            }
            //////////menu///////////////////
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

            SDL_RenderCopy(renderer,background->T_sprite,NULL,background->R_sprite);
            Afficher(tiple->R_sprite, tiple->T_sprite,monde1,NOMBRE_AFFICHER_LARGEUR,NOMBRE_AFFICHER_HAUTEUR, renderer,scroll_Larg,&cpt);
            afficher_power(glass,tab_power,renderer);

            cursor(curseur , renderer,power );
            sprite_cons(bras,50,50,hero->R_sprite->x-10,hero->R_sprite->y-10);
            aim_arm(bras,m,&b_bras,power);
            if(hero->print)
            {
            SDL_RenderCopy(renderer,hero->T_sprite,&block1, hero->R_sprite);
            }
            SDL_RenderCopy(renderer,bras->T_sprite,&b_bras, bras->R_sprite);



            update_bullet(&b,renderer);

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

        SDL_DestroyTexture(hero->T_sprite);
        SDL_DestroyTexture(tiple->T_sprite);
        SDL_DestroyTexture(curseur->T_sprite);
        SDL_DestroyTexture(glass->T_sprite);
}

