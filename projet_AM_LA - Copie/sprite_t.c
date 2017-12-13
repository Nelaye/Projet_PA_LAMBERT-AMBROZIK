#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#include "constante.h"
#include "sprite_t.h"

/*################################ Function ###############################*/

void initialization_timer(timer *t){

    t->actualTime=SDL_GetTicks();
    t->previousTime=0 ;
}

void initialization(character* sprite, int type, int width, int height, int x, int y){

    sprite->R_sprite->x= x;
    sprite->R_sprite->y = y;
    sprite->R_sprite->h = height ;
    sprite->R_sprite->w = width ;
    sprite->sprite_type = type ;
    sprite->down= true ;
    sprite->jump = false;
    switch (type){
        case HERO :
            {

                sprite->life= HERO_START_LIFE ;
                sprite->protection= 0 ;
                sprite->print = true ;
                sprite->shield = false ;
                sprite->helmet = false ;
                break;
            }
        case SHIP :
            {
                sprite->life=SHIP_START_LIFE  ;
                sprite->protection= 0 ;
                sprite->print = true ;
                sprite->shield = false ;
                sprite->helmet = false ;
                break;
            }
        case ENEMI :
            {
                sprite->life=ENEMI_START_LIFE  ;
                sprite->protection= 0 ;
                sprite->print = true ;
                sprite->shield = false ;
                sprite->helmet = false ;
                break;
            }
    }
    sprite->point.HG.x = sprite->R_sprite->x ;
    sprite->point.HG.y = sprite->R_sprite->y ;

    sprite->point.BG.x = sprite->R_sprite->x;
    sprite->point.BG.y = sprite->R_sprite->y + sprite->R_sprite->h;

    sprite->point.HD.x = sprite->R_sprite->x + sprite->R_sprite->w ;
    sprite->point.HD.y = sprite->R_sprite->y ;

    sprite->point.BD.x = sprite->R_sprite->x + sprite->R_sprite->w ;
    sprite->point.BD.y = sprite->R_sprite->y + sprite->R_sprite->h ;

    sprite->point.middle.x = sprite->R_sprite->x + sprite->R_sprite->w/ 2;
    sprite->point.middle.y = sprite->R_sprite->y + sprite->R_sprite->h/ 2;
}

void sprite_cons(sprite_t *sprite,int width ,int height ,int x ,int y ){

    sprite->R_sprite->x= x;
    sprite->R_sprite->y = y;
    sprite->R_sprite->h = height ;
    sprite->R_sprite->w = width ;
}

void cursor(sprite_t *curseur , SDL_Renderer *renderer, int power ){

    SDL_Rect block;
    block.y=0;
    block.h=SIZE_PICTURE_HEIGHT_CURSOR;
    block.w=SIZE_PICTURE_WIDTH_CURSOR ;

    switch (power){
    case POWER_GLASS:
        block.x=0;
        break;
    case  PISTOL:
        block.x = SIZE_PICTURE_WIDTH_CURSOR;

        break;
    case  SHOT_GUN:
        block.x = SIZE_PICTURE_WIDTH_CURSOR ;

        break;
    default:
        break;

    }
    SDL_RenderCopy(renderer,curseur->T_sprite,&block,curseur->R_sprite);
}

vecteur sbullet(SDL_Rect *hero, int Xcursor, int Ycursor){

    vecteur v ;
    float length ;

    v.x = Xcursor - hero->x ;
    v.y = Ycursor - hero->y ;
    length = sqrt(pow(v.x,2)+ pow(v.y,2));
    v.x /= length ;
    v.y /= length ;

    return v ;

}



void animation_boucle(SDL_Rect *block, int sens, timer *t, float second ){
    int animation;
    if (t->actualTime-t->previousTime > second *1000){
        t->previousTime = t->actualTime ;

        if (sens == TOMBE ){
            animation= MAX_ANIMATION_PERSO_NO_MOVE ;
            block->y = PICTURE_HERO_HEIGHT*6;
        }

        if (sens == GAUCHE){
            animation= MAX_ANIMATION_PERSO_NO_MOVE ;
            block->y = PICTURE_HERO_HEIGHT * 5 ;
        }
        else{
            animation= MAX_ANIMATION_PERSO_NO_MOVE ;
            block->y = PICTURE_HERO_HEIGHT*4 ;
        }

        if ((animation-1)* (PICTURE_HERO_WIDTH ) <=  block->x ){
            block->x = 0 ;
        }
        else{
            block->x = block->x + PICTURE_HERO_WIDTH ;
        }
    }
}

SDL_Rect initialization_animation(int size_width, int size_height, int x , int y ){

    SDL_Rect block ;

    block.w = size_width ;
    block.h= size_height ;
    block.x = x ;
    block.y = y ;

    return block ;
}

SDL_Rect  left_movement(int type, character *sprite, mouse m, timer *t,  SDL_Rect block, float second){

    sprite->pos.x-=5;
    int animation;
    switch (sprite->sprite_type){
        case HERO :
        {
            if( sprite->R_sprite->x > m.x ){
                animation =  MAX_ANIMATION_PERSO_MOVE ;
                block.y = 0 ;
            }
            else{
                animation =  MAX_ANIMATION_PERSO_MOVE ;
                block.y = PICTURE_HERO_HEIGHT*2 ;
            }
            if (t->actualTime-t->previousTime > second *1000){
                t->previousTime = t->actualTime ;

                if ((animation-1)* (PICTURE_HERO_WIDTH ) <=  block.x ){
                    block.x = 0 ;
                    return block;
                }
                else{
                    block.x = block.x + PICTURE_HERO_WIDTH ;
                    return block;
                }
                break;
            }
        }
        default:
            break;
    }
    return block;
}

SDL_Rect right_movement(character *sprite, mouse m, timer *t,  SDL_Rect block, float second, bool scrolling_actif){

    int animation  ;
    switch (sprite->sprite_type){

        case HERO :
        {
            if( scrolling_actif )
            {
                if(sprite->R_sprite->x  < WINDOW_WIDTH/2  ){
                sprite->pos.x+=MOUVEMENT_HERO;
                }
                if(sprite->R_sprite->x  > WINDOW_WIDTH/2 + 16  ){
                    sprite->pos.x=-MOUVEMENT_HERO;
                }
            }
            if (!scrolling_actif){
                sprite->pos.x+=5;
            }
            if( sprite->R_sprite->x <= m.x ){
                animation =  MAX_ANIMATION_PERSO_MOVE ;
                block.y = PICTURE_HERO_HEIGHT ;
            }
            else{
                animation =  MAX_ANIMATION_PERSO_MOVE ;
                block.y = PICTURE_HERO_HEIGHT*3 ;
            }
            if (t->actualTime-t->previousTime > second *1000){
                t->previousTime = t->actualTime ;

                if ((animation-1)* (PICTURE_HERO_WIDTH ) <=  block.x ){
                    block.x = 0 ;
                    return block;
                }
                else{
                    block.x = block.x + PICTURE_HERO_WIDTH ;
                    return block;
                }

            }
             break;
        }
        case SHIP :
            {
                 sprite->pos.x+=5; ;
            }


    }

    return block;
}


void aim_arm(sprite_t* arm , int aimX, int aimY, SDL_Rect* block, int power ){

	double vx = aimX - arm->R_sprite->x ;
	double vy = aimY - arm->R_sprite->y ;
	double angle  = atan2(-vy, vx);
    int num = ((int)(angle/M_PI*180/10)+18)%36;

	block->x = num * 10 ;
	block->y = power * 10 ;
}

void sprite_update (character* hero){

    hero->R_sprite->x = hero->point.middle.x - SPRITE_HERO_WIDTH/2;
    hero->R_sprite->y = hero->point.middle.y - SPRITE_HERO_HEIGHT/2;

    hero->point.HG.x = hero->point.middle.x - SPRITE_HERO_WIDTH/2;
    hero->point.HG.y = hero->point.middle.y - SPRITE_HERO_HEIGHT/2;

    hero->point.BG.x = hero->point.middle.x - SPRITE_HERO_WIDTH/2;
    hero->point.BG.y = hero->point.middle.y + SPRITE_HERO_HEIGHT/2;

    hero->point.HD.x = hero->point.middle.x + SPRITE_HERO_WIDTH/2;
    hero->point.HD.y = hero->point.middle.y - SPRITE_HERO_HEIGHT/2;

    hero->point.BD.x = hero->point.middle.x + SPRITE_HERO_WIDTH/2;
    hero->point.BD.y = hero->point.middle.y + SPRITE_HERO_HEIGHT/2;

}

void collide(bool *scrolling_active, char** tab2, character* sprite, bool* down, bool* jump, int scrolling_x, int* key, int number_display_width, int number_display_height)
{
    int X,Y,X2,Y2,X3,Y3,X4,Y4, Ybis, Ybis2, Xbis, Xbis2;
    int size_w = (WINDOW_WIDTH / number_display_width);
    int size_h = (WINDOW_HEIGHT / number_display_height);

    AABB box;
    bool stop = false;

    X=((sprite->point.HG.x+scrolling_x) / size_w) ;
    Y=(sprite->point.HG.y) / size_h;
    X2=(sprite->point.HD.x+scrolling_x) / size_w;
    Y2=(sprite->point.HD.y) / size_h;
    X3=(sprite->point.BG.x+scrolling_x)/ size_w;
    Y3=(sprite->point.BG.y) / size_h;
    X4=(sprite->point.BD.x+scrolling_x)/ size_w;
    Y4=(sprite->point.BD.y) / size_h;

    Ybis= (sprite->point.BD.y+1) / size_h;
    Ybis2= (sprite->point.BD.y+1) / size_h;

    Xbis= (sprite->point.HD.x+SPRITE_HERO_WIDTH) / size_w;
    Xbis2= (sprite->point.BG.x+1) / size_h;


    //int k =(size_w/10)*10;
    int scrol = 0; //(scrolling_x/k);

    if (tab2[Y][X + scrol] != '0'){
        stop = true;

        box.HG.x = (X*(WINDOW_WIDTH / number_display_width));
        box.HG.y = Y*(WINDOW_HEIGHT / number_display_height);
        box.HD.x = box.HG.x + size_w;
        box.HD.y = box.HG.y;

        box.BD.x = box.HG.x + size_w;
        box.BD.y = box.HG.y + size_h;

        box.BG.x = box.HG.x;
        box.BG.y = box.HG.y + size_h;


        retour(sprite->pos, sprite,box,0.01);
        if (sprite->sprite_type== HERO){
        key[q]=0;
        }
    }
    else{
        if (tab2[Y2][X2+ scrol] != '0'){
            stop = true;
            *scrolling_active=false;
            box.HG.x = X2*size_w;
            box.HG.y = Y2*size_h;

            box.HD.x = box.HG.x + size_w;
            box.HD.y = box.HG.y;

            box.BD.x = box.HG.x + size_w;
            box.BD.y = box.HG.y + size_h;

            box.BG.x = box.HG.x;
            box.BG.y = box.HG.y + size_h;

            retour(sprite->pos, sprite,box,0.01);
             if (sprite->sprite_type== HERO){
            key[d]=0;
             }
        }
        else{
            if (tab2[Y3][X3+ scrol] != '0'){
                stop = true;
                *jump=false;
                *down = false;

                box.HG.x = X3*size_w;
                box.HG.y = Y3*size_h;

                box.HD.x = box.HG.x + size_w;
                box.HD.y = box.HG.y;

                box.BD.x = box.HG.x + size_w;
                box.BD.y = box.HG.y + size_h;

                box.BG.x = box.HG.x;
                box.BG.y = box.HG.y + size_h;

                retour(sprite->pos, sprite,box,0.01);
            }
            else{
                if (tab2[Y4][X4+ scrol] != '0'){
                    stop = true;
                    *jump=false;
                    *down = false;
                    *scrolling_active=false;
                    box.HG.x = X4*size_w;
                    box.HG.y = Y4*size_h;

                    box.HD.x = box.HG.x + size_w;
                    box.HD.y = box.HG.y;

                    box.BD.x = box.HG.x + size_w;
                    box.BD.y = box.HG.y + size_h;

                    box.BG.x = box.HG.x;
                    box.BG.y = box.HG.y + size_h;

                    retour(sprite->pos, sprite,box,0.01);
                }
            }
        }
    }
    if ((tab2[Ybis][Xbis] == '0') && (tab2[Ybis2][Xbis2] == '0')){
        *down=true;
    }

   /* if ((tab2[Y2][Xbis2+scrol] == '0')){// && (tab2[Y3][Xbis2+scrol] != '0')){
        *scrolling_active=true;
    } */
    if (stop){
        sprite->pos.y=0;
    }
}

void retour(vecteur V, character *hero, AABB box, double eps)
{
    double min,max,mid;
    min = 0.0;
    max = 1.0;
    mid = (max+min)/2;


    hero->point.middle.x = hero->point.middle.x - (V.x);// recupération de la position précédente du sprite
    hero->point.middle.y = hero->point.middle.y - (V.y);

    sprite_update(hero);

    P2D tmp= hero->point.middle;

    while(max-min>eps){ // Lorsqu'on a pas ateint la précision epsilon donnée on continue la dicotomie

        hero->point.middle.x = hero->point.middle.x + (V.x * mid);
        hero->point.middle.y = hero->point.middle.y + (V.y * mid);
        sprite_update(hero);

        if( testbox( hero->point,box ) ){
            max=mid;
        }
        else{
            min=mid;
        }
        hero->point.middle = tmp;
        mid = (max+min)/2;
    }

    hero->point.middle.x = hero->point.middle.x + (V.x * (mid - eps/2) );// Application du vecteur précédement calculé afin de ce coller au plus près du bloc
    hero->point.middle.y = hero->point.middle.y + (V.y * (mid - eps/2) );
    sprite_update(hero);
}

bool testpoint(P2D point,AABB box){
    if (point.x>box.BG.x && point.x<box.HD.x){
        return true;
    }
    if (point.y<box.BG.y && point.y>box.HD.y){
        return true;
    }
    return false;
}

bool testbox(AABB box1,AABB box2){
    if (testpoint(box1.HG,box2)){
        return true;
    }
    if (testpoint(box1.BG,box2)){
        return true;
    }
    if (testpoint(box1.HD,box2)){
        return true;
    }
    if (testpoint(box1.BD,box2)){
        return true;
    }
    return false;
}
void movement_ship(character* ship,int* movementX, int* movementY)
{
    if (*movementX == 1){
        ship->R_sprite->x= ship->R_sprite->x - 5 ;
    }
    else{
         ship->R_sprite->x= ship->R_sprite->x + 5 ;
    }
    if (ship->R_sprite->x >WINDOW_WIDTH -  SPRITE_SHIP_WIDTH ){
       *movementX =  1 ;
    }
    if (ship->R_sprite->x < 0  ){
        *movementX = 0 ;
    }

     if (*movementY == 1){
        ship->R_sprite->y = ship->R_sprite->y- 1 ;
    }
    else{
         ship->R_sprite->y = ship->R_sprite->y + 1 ;
    }
    if (ship->R_sprite->y >  100 )
    {
        *movementY = 1;
    }
    if (ship->R_sprite->y <  20 )
    {
        *movementY = 0;
    }
}

sprite_t* loading ( char* name_picture, int width ,int height ,int x ,int y, SDL_Renderer* renderer, bool cons)
{
    sprite_t* S_t;

    SDL_Surface* temp;
    temp = NULL;

    S_t=(sprite_t*)malloc(sizeof(sprite_t));
    S_t->R_sprite=(SDL_Rect*)malloc(sizeof(SDL_Rect));
    S_t->T_sprite = NULL;

    temp=IMG_Load(name_picture);
    S_t->T_sprite = SDL_CreateTextureFromSurface(renderer, temp);

    if(cons){
        sprite_cons( S_t, width, height, x , y);
    }
    SDL_FreeSurface(temp);

    return S_t;
}
void jump_enemi(character* sprite, char** tab )
{
if (!sprite->jump){
            sprite->pos.y=-5;
            sprite->jump= true;
            sprite->down = true ;
        }
}

/*void  enemi_movement(character* sprite, character* target , int scrolling)
{
    if(sprite->R_sprite->x > target->R_sprite->x){

        if(sprite->R_sprite->x- 100 > target->R_sprite->x){
        sprite->pos.x = -1 ;
    }else{
    sprite->pos.x = 0 ;
    }
  }
  else{
     if(sprite->R_sprite->x + 100 < target->R_sprite->x){
         sprite->pos.x = 1 ;
     }else{
      sprite->pos.x = 0 ;
     }
  }

}*/

void enemi_jump_tab(character* sprite,character* target, char** tab,int number_display_width, int number_display_height, int scrolling)
{

    int X = (sprite->R_sprite->x+ scrolling) /(WINDOW_WIDTH/number_display_width);

    int Y = sprite->R_sprite->y /(WINDOW_WIDTH/number_display_height);
    Y = number_display_height - Y    ;
    //printf("%d\n",  sprite->R_sprite->x);
    if(sprite->R_sprite->x > target->R_sprite->x){

        if(sprite->R_sprite->x- 100 > target->R_sprite->x){
            sprite->pos.x = -1 ;


            if( tab[Y][X-1]!='0'){
                sprite->pos.x =-2;
                jump_enemi(sprite, tab );
            }
        }else{
            sprite->pos.x = 0 ;
        }
    }
     else{
     if(sprite->R_sprite->x + 100 < target->R_sprite->x){
         sprite->pos.x = 1 ;

    if( tab[Y][X+1]!='0'){
        sprite->pos.x =2;
        jump_enemi(sprite, tab );

    }
     }else{
      sprite->pos.x = 0 ;
     }
  }



}












