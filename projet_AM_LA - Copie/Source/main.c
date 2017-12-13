/***** Projet L2 S3 2017 Programmation avancé *****/
/***** LAMBERT Emilien AMBROZIK Hugo *****/

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
#include "constante.h"
#include "Sprite/sprite_t.h"
#include "Map/map.h"
#include "Liste/liste.h"
#include "Niveau/niveau.h"

int main(int argc, char **argv)
{

    int movementx_ship = 0;
    int movementy_ship = 1;
    int play_time =0 ;
    int recharge_cpt = 0 ;
    int bullet_shot_gun_cpt, bullet_pistol_cpt  ;
    int touche_actif[10]={0,0,0,0,0,0,0,0,0,0};
    int go = 0 ;
    int cpt = 0 ;
    int power;
    int game=1;

    int scroll_Larg= 0 ;
    float tempsActuel=0;
    float tempsPrecedent = 0 ;
    float gravity = 0.2;

    bool running = true;
    bool scrol_actif = true  ;
    bool recharge  =  false;

    char **monde1,**tab_power ;
    monde1 = NULL;
    tab_power = NULL;

    character *hero, *ship, *enemi;

    bullet b , enemies_bullet;
    bullet_shot_gun_cpt = 0 ;
    bullet_pistol_cpt = 0 ;

    liste liste_bullet_enemies = l_vide();
    liste liste_bullet_hero = l_vide() ;

    timer t , cpt_t   ;
    cpt_t.previousTime = 0 ;
    t.previousTime = 0 ;

    mouse m ;
    m.print = false ;

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;
    SDL_Rect block1, block2, b_bras, b_left_barrel;
    SDL_Surface *temp ;

    sprite_t  *tiple, *curseur, *glass, *menu,*game_over, *player1, *player2, *bras, *left_barrel, *right_barrel, *background, *bullet_hero_image ;

    window = SDL_CreateWindow("Project AMBROZIK LAMBERT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, 0);



/*********************************** LOAD ***********************************/
    //Load bullet

    bullet_hero_image=loading( "picture/bullet.xcf", WINDOW_WIDTH, WINDOW_HEIGHT,0,0, renderer, true);

    //Load background

    background=loading( "picture/background.jpg", WINDOW_WIDTH, WINDOW_HEIGHT,0,0, renderer, true);

    game_over=loading( "picture/game_over.xcf", WINDOW_WIDTH, WINDOW_HEIGHT,0,0, renderer, true);
    //Load power/pistol cursor

    curseur=loading( "picture/cursor.xcf", 0, 0,0,0, renderer, false);

    //Load menu

    //menu->T_sprite = NULL;
    //temp = NULL ;
    //temp = IMG_Load("picture/menu.xcf");
    //menu->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    //sprite_cons(menu, WINDOW_WIDTH,WINDOW_HEIGHT,0,0 );
    //menu->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    menu=loading( "picture/menu.xcf", WINDOW_WIDTH, WINDOW_HEIGHT,0,0,renderer, true);

    //Load arm
    /*bras->T_sprite = NULL;
    temp = NULL ;
    temp = IMG_Load("picture/bras.xcf");
    bras->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);*/
    bras=loading( "picture/bras.xcf", 0,0,0,0,renderer, false );

    //Load barrel
    /*left_barrel->T_sprite = NULL;
    right_barrel->T_sprite = NULL;
    temp = NULL ;

    temp = IMG_Load("picture/bras.xcf");
    left_barrel->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    right_barrel->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);*/
    left_barrel=loading( "picture/bras.xcf", 0, 0,0,0, renderer, false);
    right_barrel=loading( "picture/bras.xcf", 0, 0,0,0, renderer, false);

    //Load player1
    /*player1->T_sprite = NULL;
    temp = NULL ;
    temp = IMG_Load("picture/joueur_1.xcf");
    player1->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(player1, 200,200,200,200 );*/
    player1=loading( "picture/joueur1.xcf", 200,200,200,200, renderer, true);

    //Load player 2
/*  player2->T_sprite = NULL;
    temp = NULL ;
    player2->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/joueur_2.xcf");
    player2->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(player2, 200,200,600,200 );*/
    player2=loading( "picture/joueur2.xcf", 200,200,600,200, renderer, true);


    //Load tiple
    /*tiple->T_sprite = NULL;
    temp = NULL;
    temp = IMG_Load("picture/block.xcf");
    tiple->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(tiple, WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR,WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR,0,0 );*/
    tiple=loading( "picture/block.xcf", WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR,WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR,0,0, renderer, true );

    //Load glass
/*  glass->T_sprite = NULL;
    temp =NULL;
    temp = IMG_Load("picture/block_glass.xcf");
    glass->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(glass,WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR_POWER ,WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR_POWER , 0, 0);*/
    glass=loading( "picture/block_glass.xcf", WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR,WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR,0,0, renderer, true);

    sprite_cons(glass,WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR_POWER ,WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR_POWER , 0, 0);
   //Load ship
    ship = (character*)malloc(sizeof(character));
    ship->T_sprite= NULL;
    ship->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = NULL;
    temp = IMG_Load("picture/joueur_1_animation.xcf");
    ship->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);


    //Load enemi

    enemi= (character*)malloc(sizeof(character));
    enemi->T_sprite= NULL;
    temp = NULL;
    enemi->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/joueur_1_animation.xcf");
    enemi->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);

    //Load sprite
    hero = (character*)malloc(sizeof(character));
    hero->T_sprite= NULL;
    hero->R_sprite=(SDL_Rect*)malloc(sizeof(SDL_Rect));

    //touche

    int jeu = 0 ;

/********************************** MAIN LOOP *********************************/

    while (running){

        play_time = SDL_GetTicks() ;
        cpt_t.actualTime =  SDL_GetTicks();

        hero->pos.x=0;
        enemi->pos.x=0;

        /************** Counter **************/
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

/************************** ALL EVENT ******************************/

        if (tempsActuel -tempsPrecedent > 1000.0/120.0){

            while (SDL_PollEvent(&event)){

                if (event.type == SDL_QUIT) running = false;

                if (event.type == SDL_MOUSEMOTION){
                    m.x = event.motion.x ;
                    m.y = event.motion.y ;
                    sprite_cons(curseur,CURSOR_WIDTH,CURSOR_HEIGHT,m.x,m.y);
                }

                if(event.type==SDL_KEYUP){
                    if(event.key.keysym.sym == SDLK_z){
                        touche_actif[z]=0;
                    }
                    if(event.key.keysym.sym == SDLK_d){
                        touche_actif[d]=0;
                    }
                    if(event.key.keysym.sym == SDLK_s){
                        touche_actif[s]=0;
                    }
                    if(event.key.keysym.sym == SDLK_q){
                        touche_actif[q]=0;
                    }
                     if(event.key.keysym.sym == SDLK_SPACE){
                        touche_actif[space]=0;
                    }
                }// end if keyup

                if (event.type== SDL_KEYDOWN){

                    if(event.key.keysym.sym == SDLK_ESCAPE) running = false ;

                    if(event.key.keysym.sym == SDLK_z){
                        touche_actif[z]=1;
                    }
                    if(event.key.keysym.sym == SDLK_d){
                        touche_actif[d]=1;
                    }
                    if(event.key.keysym.sym == SDLK_s){
                        touche_actif[s]=1;
                    }
                    if(event.key.keysym.sym == SDLK_q){
                        touche_actif[q]=1;
                    }
                    if(event.key.keysym.sym == SDLK_1){
                        bras->print = true ;
                        curseur->print = true ;
                        power = POWER_GLASS;
                    }
                    if(event.key.keysym.sym == SDLK_2){
                        bras->print = true ;
                        curseur->print = true ;
                        power = PISTOL;
                    }
                    if(event.key.keysym.sym == SDLK_3){
                        bras->print = true ;
                        curseur->print = true ;
                        power = SHOT_GUN;
                    }
                    if(event.key.keysym.sym == SDLK_m){
                        if( power == PISTOL ){
                            if( bullet_pistol_cpt < MAGAZINE_GUN && !recharge ){
                                liste_bullet_hero=  shoot_bullet(liste_bullet_hero,b,bullet_hero_image,hero,scroll_Larg, m.x,m.y ,0,0,0);
                                bullet_pistol_cpt =bullet_pistol_cpt + 1;
                            }
                            break;
                        }
                        if (power == SHOT_GUN ){
                            if ( bullet_shot_gun_cpt < MAGAZINE_SHOT_GUN && !recharge ){
                                liste_bullet_hero=  shoot_bullet(liste_bullet_hero,b,bullet_hero_image,hero,scroll_Larg, m.x,m.y,0,0,0 );
                                liste_bullet_hero=  shoot_bullet(liste_bullet_hero,b,bullet_hero_image,hero,scroll_Larg, m.x,m.y,30,0,0 );
                                liste_bullet_hero=  shoot_bullet(liste_bullet_hero,b,bullet_hero_image,hero,scroll_Larg, m.x,m.y,-30,0,0 );
                                bullet_shot_gun_cpt =bullet_shot_gun_cpt + 1;
                                break;
                            }
                        }//end if shotgun

                        if (power == POWER_GLASS ){
                            modifTabPower(m ,scroll_Larg,tab_power);
                        }
                    }// end sdl key m

                    if(event.key.keysym.sym == SDLK_r){
                        recharge = 1 ;
                        recharge_cpt =SDL_GetTicks()+ 1000;
                    }
                    if(event.key.keysym.sym == SDLK_SPACE){
                        touche_actif[space]=1;
                    }
                }// end if keydown
            }// end while event

        /*********************ACTION'S EVENT************************/


        /***** q *****/

        if(touche_actif[q]==1){

            block1 = left_movement(HERO,hero, m,&t, block1, 0.2 );
        }
        /***** d *****/
        if(touche_actif[d]==1){

            if(hero->R_sprite->x >= WINDOW_WIDTH/2 ){
                if (scrol_actif){
                    scroll_Larg+=MOUVEMENT_HERO;
                }
                if (!ship->print){

                    if (hero->R_sprite->x > (WINDOW_WIDTH/2))
                    {
                        scrol_actif=true ;
                    }
                }else {
                    scrol_actif=false;

                }
            }
                block1 = right_movement(hero, m,&t, block1, 0.2,scrol_actif );
        }

        /***** z *****/
        if((touche_actif[z]==1) && (!hero->jump)){
            hero->pos.y=-5;
           // jump = true;
            hero->jump= true;
            hero->down = true ;
        }



        /******************************/

        if(touche_actif[q]==0 && touche_actif[d]==0 ){
            if (m.x > hero->R_sprite->x){
                animation_boucle(&block1,GAUCHE, &t, 0.50);
            }
            else{
                animation_boucle(&block1,DROIT, &t, 0.50 );
            }
        }

        if(recharge){
            bras->print = false ;

            if (recharge_cpt < play_time){
                bras->print = true;
                recharge  = 0 ;
                if(power == PISTOL){
                    bullet_pistol_cpt = 0 ;
                }
                if (power==SHOT_GUN){
                    bullet_shot_gun_cpt = 0 ;
                }
            }
        }

    /******************** MOUVEMENT *********************/

    /******** shot_boss **********/
    if(play_time%50==0){
        if (ship->print){

            liste_bullet_enemies=  shoot_bullet(liste_bullet_enemies,enemies_bullet,bullet_hero_image,ship,scroll_Larg,hero->R_sprite->x,hero->R_sprite->y, 0, 10,0 );
            liste_bullet_enemies=  shoot_bullet(liste_bullet_enemies,enemies_bullet,bullet_hero_image,ship,scroll_Larg,hero->R_sprite->x,hero->R_sprite->y, 0, -10,0);
        }
    }
    /*******shot_enemi**********/


            //liste_bullet_enemies=  shoot_bullet(liste_bullet_enemies,enemies_bullet,bullet_hero_image,enemi,scroll_Larg,hero->R_sprite->x,hero->R_sprite->y, 0, 0,0);

    //If the sprite is outside of the screen
    if(hero->R_sprite->x<0){

        hero->R_sprite->x=0 + scroll_Larg;

    }

    /*************** Menu ***************/
    if (game == START){
        //game= start(renderer ,menu ,touche_actif);
    }
    if(game == MENU_HERO){
        sprite_cons(menu, WINDOW_WIDTH,WINDOW_HEIGHT,0,0 );
        SDL_RenderCopy(renderer,menu->T_sprite,NULL, menu->R_sprite);
        SDL_RenderCopy(renderer,player1->T_sprite,NULL, player1->R_sprite);
        SDL_RenderCopy(renderer,player2->T_sprite,NULL, player2->R_sprite);

        if ( m.x>600 && m.x<800 && (m.y>200 && m.y<400)&& touche_actif[space]==1){
            hero->player = 1 ;
            game  = GAME_GO ;
            temp = IMG_Load("picture/joueur_1_animation.xcf");
            hero->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
        }
        if (m.x>200 && m.x<400 && (m.y>200 && m.y<400)&& touche_actif[space]==1){
            hero->player = 2 ;
            game  = GAME_GO ;
            temp = NULL;
            temp = IMG_Load("picture/joueur_2_animation.xcf");
            hero->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
        }
        scroll_Larg = 0 ;
    }

    /*************** Level 1 **************/
    else if(game == GAME_GO){

            /***** initialisation player *****/
            if (go == 0 ){
                b_bras = initialization_animation(10,10,0,0);
                block1 = initialization_animation(PICTURE_HERO_WIDTH,PICTURE_HERO_HEIGHT,0,4);
                block2 = initialization_animation(PICTURE_HERO_WIDTH,PICTURE_HERO_HEIGHT,0,4);
                initialization(hero, HERO,SPRITE_HERO_WIDTH,SPRITE_HERO_HEIGHT,HERO_START_POS_X,HERO_START_POS_Y);
                initialization(ship, SHIP,SPRITE_SHIP_WIDTH,SPRITE_SHIP_HEIGHT,300,10);
                initialization(enemi, ENEMI,SPRITE_ENEMI_WIDTH,SPRITE_ENEMI_HEIGHT,400,350);
                ship->print=false;
               // enemi->print=false;
               // l1= init_level(monde1, tab_power,"text.txt");
                go = 1 ;
            }
            /***** initialisation power *****/
            if (tab_power == NULL){

               // tab_power=initialisation_tableau(NOMBRE_BLOCK_HAUTEUR*(NOMBRE_AFFICHER_HAUTEUR_POWER/NOMBRE_AFFICHER_HAUTEUR)  ,NOMBRE_BLOCK_LARGEUR*(NOMBRE_AFFICHER_LARGEUR_POWER/NOMBRE_AFFICHER_LARGEUR) );
                tab_power = initialisation_tableau(30,400);
            }
            /***** initialisation tile *****/
            if (monde1 == NULL){
                SDL_ShowCursor(SDL_DISABLE);
                FILE *monde ;
                monde = fopen("text.txt", "r");

                if (monde==NULL){
                    printf("erreur fichier");
                    return EXIT_FAILURE ;
                }

                monde1 = init_tab_dynamic(NOMBRE_BLOCK_HAUTEUR,NOMBRE_BLOCK_LARGEUR,monde);
                fclose(monde);
            }
            /********** print ship *******/

            /********** Collide **********/

            hero->point.middle.x = hero->point.middle.x + hero->pos.x;//Application of the mouvement on axes x
            hero->point.middle.y = hero->point.middle.y + hero->pos.y;//Application of the mouvement on axes y
             sprite_update(hero);
              if (hero->down){
                hero->pos.y =hero->pos.y + gravity;
            }
           //,SPRITE_ENEMI_WIDTH,SPRITE_ENEMI_HEIGHT, NOMBRE_AFFICHER_LARGEUR, NOMBRE_AFFICHER_HAUTEUR);


           // enemi_movement(enemi,hero,scroll_Larg, monde1,NOMBRE_AFFICHER_LARGEUR,NOMBRE_AFFICHER_HAUTEUR, hero);

            enemi_jump_tab(enemi,hero,monde1, NOMBRE_AFFICHER_LARGEUR, NOMBRE_AFFICHER_HAUTEUR , scroll_Larg);
            enemi->point.middle.x = enemi->point.middle.x + enemi->pos.x;  //enemi->pos.x;//Application of the mouvement on axes x
            enemi->point.middle.y = enemi->point.middle.y + enemi->pos.y;

           // Update the coordinate of the sprite
            sprite_update(enemi);

          //  if (enemi->down)
            {
                enemi->pos.y =enemi->pos.y + gravity;
            }

            collide(&scrol_actif, monde1, hero, &hero->down ,&hero->jump, scroll_Larg, touche_actif, NOMBRE_AFFICHER_LARGEUR, NOMBRE_AFFICHER_HAUTEUR);
            collide(&scrol_actif, monde1, enemi, &enemi->down ,&enemi->jump, scroll_Larg, touche_actif, NOMBRE_AFFICHER_LARGEUR, NOMBRE_AFFICHER_HAUTEUR);
            collide(&scrol_actif,tab_power, hero, &hero->down ,&hero->jump, scroll_Larg,touche_actif,NOMBRE_AFFICHER_LARGEUR_POWER,NOMBRE_AFFICHER_HAUTEUR_POWER);



            /********** Print **********/
            SDL_RenderCopy(renderer,background->T_sprite,NULL,background->R_sprite);
            Afficher(glass->R_sprite, glass->T_sprite,tab_power,NOMBRE_AFFICHER_LARGEUR_POWER,NOMBRE_AFFICHER_HAUTEUR_POWER, renderer,scroll_Larg,scrol_actif,&cpt,ship);
            Afficher(tiple->R_sprite, tiple->T_sprite,monde1,NOMBRE_AFFICHER_LARGEUR,NOMBRE_AFFICHER_HAUTEUR, renderer,scroll_Larg,scrol_actif,&cpt,ship);

            if (curseur->print){
            cursor(curseur , renderer,power );
            }

            if (ship->print){
                movement_ship(ship,&movementx_ship,&movementy_ship);
                liste_bullet_enemies = update_bullet_collide(liste_bullet_enemies,renderer,scroll_Larg,10);
                SDL_RenderCopy(renderer,ship->T_sprite,NULL, ship->R_sprite);
            }
            if (hero->print){
                sprite_cons(bras,50,50,hero->R_sprite->x-10,hero->R_sprite->y-10);
                aim_arm(bras,m.x,m.y,&b_bras,power);
                SDL_RenderCopy(renderer,hero->T_sprite,&block1, hero->R_sprite);
                liste_bullet_hero = update_bullet_collide(liste_bullet_hero,renderer,scroll_Larg,10);
                if(bras->print){
                    SDL_RenderCopy(renderer,bras->T_sprite,&b_bras, bras->R_sprite);
                }

            }
             if(!hero->print){
                 game = DEAD;
             }

            if (enemi->print){

                SDL_RenderCopy(renderer,enemi->T_sprite,NULL, enemi->R_sprite);
                liste_bullet_enemies = update_bullet_collide(liste_bullet_enemies,renderer,scroll_Larg,10);
            }


            liste_bullet_hero = collide_bullet(liste_bullet_hero ,monde1,  NOMBRE_AFFICHER_LARGEUR , NOMBRE_AFFICHER_HAUTEUR,scroll_Larg,16,16) ;
            liste_bullet_hero = collide_bullet(liste_bullet_hero ,tab_power,  NOMBRE_AFFICHER_LARGEUR_POWER , NOMBRE_AFFICHER_HAUTEUR_POWER,scroll_Larg,16,16 ) ;

            liste_bullet_enemies = collide_bullet(liste_bullet_enemies ,monde1,  NOMBRE_AFFICHER_LARGEUR , NOMBRE_AFFICHER_HAUTEUR,scroll_Larg,16,16 ) ;
            liste_bullet_enemies = collide_bullet(liste_bullet_enemies ,tab_power,  NOMBRE_AFFICHER_LARGEUR_POWER , NOMBRE_AFFICHER_HAUTEUR_POWER,scroll_Larg,16,16 ) ;

            liste_bullet_enemies= collide_bullet_sprite(liste_bullet_enemies , hero , HAUTEUR_BULLET,scroll_Larg);
            liste_bullet_hero = collide_bullet_sprite(liste_bullet_hero , ship , HAUTEUR_BULLET,scroll_Larg);
            printf("%d\n", hero->R_sprite->x);
            }
            else if (game == DEAD){

        sprite_cons(game_over, WINDOW_WIDTH,WINDOW_HEIGHT,0,0 );
        SDL_RenderCopy(renderer,game_over->T_sprite,NULL, game_over->R_sprite);
         if(event.key.keysym.sym == SDLK_SPACE) running = false ;
                   }

            /********** Text *********/
            SDL_RenderPresent(renderer);
            tempsPrecedent = tempsActuel;


        }
        else
        {
            SDL_Delay((1000.0/120.0)-(tempsActuel - tempsPrecedent) );
        }
        SDL_RenderClear(renderer);
    }// end while running

        free(tiple->R_sprite);
        free(curseur->R_sprite);
        free(glass->R_sprite);
        free(menu->R_sprite);
        free(player1->R_sprite);
        free(player2->R_sprite);
        free(bras->R_sprite);
        free(left_barrel->R_sprite);
        free(right_barrel->R_sprite);
        free(background->R_sprite);
        free(bullet_hero_image->R_sprite);
        free(hero->R_sprite);
        free(ship->R_sprite);
        SDL_DestroyTexture(tiple->T_sprite);
        SDL_DestroyTexture(curseur->T_sprite);
        SDL_DestroyTexture(glass->T_sprite);
        SDL_DestroyTexture(menu->T_sprite);
        SDL_DestroyTexture(player1->T_sprite);
        SDL_DestroyTexture(player2->T_sprite);
        SDL_DestroyTexture(bras->T_sprite);
        SDL_DestroyTexture(left_barrel->T_sprite);
        SDL_DestroyTexture(right_barrel->T_sprite);
        SDL_DestroyTexture(background->T_sprite);
        SDL_DestroyTexture(bullet_hero_image->T_sprite);
        SDL_DestroyTexture(hero->T_sprite);
        SDL_DestroyTexture(ship->T_sprite);
        liberer_liste(liste_bullet_enemies);
        liberer_liste(liste_bullet_hero);

        return EXIT_SUCCESS;
}// end main

