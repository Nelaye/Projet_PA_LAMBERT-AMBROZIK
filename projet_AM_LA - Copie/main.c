/***** Projet L2 S3 2017 Programmation avancé *****/
/***** LAMBERT Emilien AMBROZIK Hugo *****/

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SDL2/SDL_image.h>

#include "constante.h"
#include "sprite_t.h"
#include "map.h"
#include "liste.h"

int main(int argc, char **argv)
{
    int x = 2;
    int y = 1;
    int play_time =0 ;
    bool recharge  =  false;
    int recharge_cpt = 0 ;
    int bullet_shot_gun_cpt, bullet_pistol_cpt  ;
    int touche_actif[5]={0,0,0,0,0};
    int go = 0 ;
    int cpt = 0 ;
    int power;

    float scroll_Larg= 0 ;
    float tempsActuel=0;

    float tempsPrecedent = 0 ;
    float gravity = 0.2;

    bool running = true;
    bool jump = false;
    bool down = true;
    bool scrol_actif = true  ;

    char **monde1,**tab_power ;
    monde1 = NULL;
    tab_power = NULL;

    character *hero, *ship;

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
    SDL_Rect block1,block2,  b_bras, b_left_barrel ;
    SDL_Surface *temp ;

    sprite_t   *tiple , *curseur, *glass,*menu, *joueur1 , *joueur2 , *bras,*left_barrel,*right_barrel , *background, *bullet_hero_image;

    window = SDL_CreateWindow("Project AMBROZIK LAMBERT", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, 0);



/**********************************************************************/

    //Load bullet
    bullet_hero_image = (sprite_t*)malloc(sizeof(sprite_t));
    bullet_hero_image->T_sprite = NULL;
    temp = NULL ;
    bullet_hero_image->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/bullet.xcf");
    bullet_hero_image->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(bullet_hero_image, WINDOW_WIDTH,WINDOW_HEIGHT,0,0 );
    bullet_hero_image->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);

    //Load background
    background = (sprite_t*)malloc(sizeof(sprite_t));
    background->T_sprite = NULL;
    temp = NULL ;
    background->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/background.jpg");
    background->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(background, WINDOW_WIDTH,WINDOW_HEIGHT,0,0 );
    background->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);

    //Load power/pistol cursor
    curseur = (sprite_t*)malloc(sizeof(sprite_t));
    curseur->T_sprite = NULL;
    temp = NULL ;
    curseur->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/cursor.xcf");
    curseur->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);

    //Load menu
    menu = (sprite_t*)malloc(sizeof(sprite_t));
    menu->T_sprite = NULL;
    temp = NULL ;
    menu->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/menu.xcf");
    menu->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(menu, WINDOW_WIDTH,WINDOW_HEIGHT,0,0 );

    //Load arm
    bras = (sprite_t*)malloc(sizeof(sprite_t));
    bras->T_sprite = NULL;
    temp = NULL ;
    bras->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/bras.xcf");
    bras->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    //Load barrel
    left_barrel = (sprite_t*)malloc(sizeof(sprite_t));
    right_barrel = (sprite_t*)malloc(sizeof(sprite_t));
    left_barrel->T_sprite = NULL;
    right_barrel->T_sprite = NULL;
    temp = NULL ;
    left_barrel->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    right_barrel->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/bras.xcf");
    left_barrel->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    right_barrel->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);

    //Load player1
    joueur1 = (sprite_t*)malloc(sizeof(sprite_t));
    joueur1->T_sprite = NULL;
    temp = NULL ;
    joueur1->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/joueur_1.xcf");
    joueur1->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(joueur1, 200,200,200,200 );

    //Load player 2
    joueur2 = (sprite_t*)malloc(sizeof(sprite_t));
    joueur2->T_sprite = NULL;
    temp = NULL ;
    joueur2->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/joueur_2.xcf");
    joueur2->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(joueur2, 200,200,600,200 );

    //Load tiple
    tiple = (sprite_t*)malloc(sizeof(sprite_t));
    tiple->T_sprite = NULL;
    temp = NULL;
    tiple->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/block.xcf");
    tiple->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(tiple, WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR,WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR,0,0 );

    //Load glass
    glass = (sprite_t*)malloc(sizeof(sprite_t));
    glass->T_sprite = NULL;
    temp =NULL;
    glass->R_sprite = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = IMG_Load("picture/block_glass.xcf");
    glass->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
    sprite_cons(glass,WINDOW_WIDTH/NOMBRE_AFFICHER_LARGEUR_POWER ,WINDOW_HEIGHT/NOMBRE_AFFICHER_HAUTEUR_POWER , 0, 0);


    ship = (character*)malloc(sizeof(character));
    ship->T_sprite= NULL;
    ship->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    temp = NULL;
    temp = IMG_Load("picture/joueur_1_animation.xcf");
    ship->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);

    //Load sprite
    hero = (character*)malloc(sizeof(character));
    hero->T_sprite= NULL;
    hero->R_sprite  = (SDL_Rect*)malloc(sizeof(SDL_Rect));
    //Load ship_sprite

    //touche

    int jeu = 0 ;

/*******************************************************************/

    while (running){

        SDL_SetRenderDrawColor(renderer,100,100,100,10);

        play_time = SDL_GetTicks() ;
        cpt_t.actualTime =  SDL_GetTicks();

        hero->pos.x=0;


        /************** compteur **************/
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
                        m.print = true ;
                        power = POWER_GLASS;
                    }
                    if(event.key.keysym.sym == SDLK_2){
                        bras->print = true ;
                        m.print = true ;
                        power = PISTOL;
                    }
                    if(event.key.keysym.sym == SDLK_3){
                        bras->print = true ;
                        m.print = true ;
                        power = SHOT_GUN;
                    }
                    if(event.key.keysym.sym == SDLK_m){
                        if( power == PISTOL ){
                            if( bullet_pistol_cpt < MAGAZINE_GUN && !recharge ){
                                b.R_Bullet = bullet_hero_image->R_sprite ;
                                b.T_Bullet = bullet_hero_image->T_sprite ;
                                b.x = hero->R_sprite->x + scroll_Larg ;
                                b.y = hero->R_sprite->y ;
                                b.v =  sbullet(hero->R_sprite,m.x,m.y );
                                b.print = true ;
                                liste_bullet_hero = cons(b,liste_bullet_hero);
                                bullet_pistol_cpt =bullet_pistol_cpt + 1;
                            }
                            break;
                        }
                        if (power == SHOT_GUN ){
                            if ( bullet_shot_gun_cpt < MAGAZINE_SHOT_GUN && !recharge ){

                                b.R_Bullet = bullet_hero_image->R_sprite;
                                b.T_Bullet = bullet_hero_image->T_sprite ;

                                b.x = hero->R_sprite->x + scroll_Larg;
                                b.y = hero->R_sprite->y ;
                                b.v =  sbullet(hero->R_sprite,m.x,m.y );
                                b.print = true ;
                                liste_bullet_hero = cons(b,liste_bullet_hero);

                                b.x = hero->R_sprite->x + scroll_Larg;
                                b.y = hero->R_sprite->y ;
                                b.v =  sbullet(hero->R_sprite,m.x+30,m.y+30 );
                                b.print = true ;
                                liste_bullet_hero = cons(b,liste_bullet_hero);

                                liste_bullet_hero = cons(b,liste_bullet_hero);
                                b.x = hero->R_sprite->x + scroll_Larg ;
                                b.y = hero->R_sprite->y ;
                                b.v =  sbullet(hero->R_sprite,m.x-30,m.y-30 );
                                b.print = true ;
                                liste_bullet_hero = cons(b,liste_bullet_hero);

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
                }// end if keydown
            }// end while event

        /*********************ACTION'S EVENT************************/


        /***** q *****/

        if(touche_actif[q]==1){

            block1 = left_movement(hero, m,&t, block1, 0.2 );

        }
        /***** d *****/
        if(touche_actif[d]==1){

            if(hero->R_sprite->x >= WINDOW_WIDTH/2 ){
                if (scrol_actif){
                    scroll_Larg+=MOUVEMENT_HERO;
                }
                scrol_actif=true ;
            }
                block1 = right_movement(hero, m,&t, block1, 0.2 );

        }

        /***** z *****/
        if((touche_actif[z]==1) && (!jump)){
            hero->pos.y=-5;
            jump = true;
            down = true;
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

    /***************** Mouvement *********************/
    /******Enemie_mouvement********/
    if(ship->R_sprite->x > WINDOW_WIDTH -  SPRITE_SHIP_WIDTH)
    {
        x = -5 ;
    }
    if (ship->R_sprite->x < 0  ){
        x = 5 ;
    }
    ship->R_sprite->x = ship->R_sprite->x + x ;
    if (ship->R_sprite->y >  100 )
    {
        y = -1 ;
    }
    if (ship->R_sprite->y <  20 )
    {
        y = 1 ;
    }
    ship->R_sprite->y = ship->R_sprite->y + y ;
    /******** shot_enemies **********/
    if(play_time%50==0){
     enemies_bullet.R_Bullet = bullet_hero_image->R_sprite ;
                            enemies_bullet.T_Bullet = bullet_hero_image->T_sprite ;
                            enemies_bullet.x = ship->R_sprite->x + scroll_Larg ;
                            enemies_bullet.y = ship->R_sprite->y+ 10;
                            enemies_bullet.v =  sbullet(ship->R_sprite,hero->R_sprite->x,hero->R_sprite->y );
                             enemies_bullet.print = true ;
                            liste_bullet_enemies = cons(enemies_bullet,liste_bullet_enemies);
    enemies_bullet.R_Bullet = bullet_hero_image->R_sprite ;
                            enemies_bullet.T_Bullet = bullet_hero_image->T_sprite ;
                            enemies_bullet.x = ship->R_sprite->x + scroll_Larg + 30 ;
                            enemies_bullet.y = ship->R_sprite->y + 10;
                            enemies_bullet.v =  sbullet(ship->R_sprite,hero->R_sprite->x+10,hero->R_sprite->y );
                            enemies_bullet.print = true ;
                            liste_bullet_enemies = cons(enemies_bullet,liste_bullet_enemies);
    }
    /*******************************/
    hero->point.middle.x = hero->point.middle.x + hero->pos.x;//Application of the mouvement on axes x
    hero->point.middle.y = hero->point.middle.y + hero->pos.y;//Application of the mouvement on axes y

    sprite_update(hero);// Update the coordinate of the sprite

    if (down){// Activation of the gravity
        hero->pos.y =hero->pos.y + gravity;
    }

    //If the sprite is outside of the screen
    if(hero->R_sprite->x<0){
        hero->R_sprite->x=0;
    }

    if(hero->R_sprite->y+SPRITE_HERO_HEIGHT>WINDOW_HEIGHT){
        hero->R_sprite->y=WINDOW_HEIGHT-SPRITE_HERO_HEIGHT;
        down=false;
        hero->pos.y=0;
    }

    if(hero->R_sprite->x+SPRITE_HERO_WIDTH>WINDOW_WIDTH){
        hero->R_sprite->x=WINDOW_WIDTH-SPRITE_HERO_WIDTH;
    }

    if(hero->R_sprite->y<0){
        hero->R_sprite->y=0;
        hero->pos.y=0;
    }




    /*************** Menu ***************/
    if(jeu == 0 ){
        sprite_cons(menu, WINDOW_WIDTH,WINDOW_HEIGHT,0,0 );
        SDL_RenderCopy(renderer,menu->T_sprite,NULL, menu->R_sprite);
        SDL_RenderCopy(renderer,joueur1->T_sprite,NULL, joueur1->R_sprite);
        SDL_RenderCopy(renderer,joueur2->T_sprite,NULL, joueur2->R_sprite);

        if((m.x>200 && m.x<400)&& (m.y>200 && m.y<400)){
            joueur1->R_sprite->y=joueur1->R_sprite->y-1 ;
        }
        if((m.x>600 && m.x<800)&& (m.y>200 && m.y<400)){
            joueur2->R_sprite->y=joueur2->R_sprite->y-1 ;
        }
        if (joueur1->R_sprite->y==0){
            hero->player = 1 ;
            jeu  = 1 ;
            temp = IMG_Load("picture/joueur_1_animation.xcf");
            hero->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
        }
        if (joueur2->R_sprite->y==0){
            hero->player = 2 ;
            jeu  = 1 ;
            temp = NULL;
            temp = IMG_Load("picture/joueur_2_animation.xcf");
            hero->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);
        }
        scroll_Larg = 0 ;
    }

    /*************** Level 1 **************/
    else if(jeu == 1){

            /***** initialisation player *****/
            if (go == 0 ){
                b_bras = initialization_animation(10,10,0,0);
                block1 = initialization_animation(PICTURE_HERO_WIDTH,PICTURE_HERO_HEIGHT,0,4);
                initialization(hero, HERO,SPRITE_HERO_WIDTH,SPRITE_HERO_HEIGHT,HERO_START_POS_X,HERO_START_POS_Y);
                 initialization(ship, SHIP,SPRITE_SHIP_WIDTH,SPRITE_SHIP_HEIGHT,300,10);

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
            collide(&scrol_actif, monde1, hero, &down ,&jump, scroll_Larg, touche_actif, &scrol_actif, NOMBRE_AFFICHER_LARGEUR, NOMBRE_AFFICHER_HAUTEUR);
            collide(&scrol_actif,tab_power, hero, &down ,&jump, scroll_Larg,touche_actif,&scrol_actif,NOMBRE_AFFICHER_LARGEUR_POWER,NOMBRE_AFFICHER_HAUTEUR_POWER);
            sprite_update(hero);
            /********** Print **********/
            SDL_RenderCopy(renderer,background->T_sprite,NULL,background->R_sprite);
            Afficher(glass->R_sprite, glass->T_sprite,tab_power,NOMBRE_AFFICHER_LARGEUR_POWER,NOMBRE_AFFICHER_HAUTEUR_POWER, renderer,scroll_Larg,&cpt);
            Afficher(tiple->R_sprite, tiple->T_sprite,monde1,NOMBRE_AFFICHER_LARGEUR,NOMBRE_AFFICHER_HAUTEUR, renderer,scroll_Larg,&cpt);

            cursor(curseur , renderer,power );

            sprite_cons(bras,50,50,hero->R_sprite->x-10,hero->R_sprite->y-10);
            sprite_cons(left_barrel,100,100,ship->R_sprite->x-10,ship->R_sprite->y-10);

            aim_arm(left_barrel,hero->R_sprite->x,hero->R_sprite->y,&b_left_barrel,0);
            aim_arm(bras,m.x,m.y,&b_bras,power);
            SDL_RenderCopy(renderer,left_barrel->T_sprite,&b_left_barrel, left_barrel->R_sprite);
            printf("%d",longueur(liste_bullet_hero));
            SDL_RenderCopy(renderer,hero->T_sprite,&block1, hero->R_sprite);
            SDL_RenderCopy(renderer,ship->T_sprite,NULL, ship->R_sprite);
            if(bras->print==true ){
                SDL_RenderCopy(renderer,bras->T_sprite,&b_bras, bras->R_sprite);
            }
            liste_bullet_hero = collide_bullet(liste_bullet_hero ,monde1,  NOMBRE_AFFICHER_LARGEUR , NOMBRE_AFFICHER_HAUTEUR,scroll_Larg ) ;
            liste_bullet_hero = collide_bullet(liste_bullet_hero ,tab_power,  NOMBRE_AFFICHER_LARGEUR_POWER , NOMBRE_AFFICHER_HAUTEUR_POWER,scroll_Larg ) ;

            //liste_bullet_enemies = collide_bullet(liste_bullet_enemies ,monde1,  NOMBRE_AFFICHER_LARGEUR , NOMBRE_AFFICHER_HAUTEUR,scroll_Larg ) ;
            liste_bullet_enemies = collide_bullet(liste_bullet_enemies ,tab_power,  NOMBRE_AFFICHER_LARGEUR_POWER , NOMBRE_AFFICHER_HAUTEUR_POWER,scroll_Larg ) ;

            liste_bullet_enemies = update_bullet_collide(liste_bullet_enemies,renderer,scroll_Larg,10);

            liste_bullet_hero = update_bullet_collide(liste_bullet_hero,renderer,scroll_Larg,10);

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

        SDL_DestroyTexture(hero->T_sprite);
        SDL_DestroyTexture(tiple->T_sprite);
        SDL_DestroyTexture(curseur->T_sprite);
        SDL_DestroyTexture(glass->T_sprite);

        return EXIT_SUCCESS;
}// end main

