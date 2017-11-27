#ifndef SPRITE_T_H_INCLUDED
#define SPRITE_T_H_INCLUDED
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
    /*############################# Abstract Type #############################*/


typedef struct Mouse
{
    unsigned short int  x,y ;
    bool print ;
}mouse ;

typedef struct Compteur
{
    int nb ;
}compteur ;

typedef struct Sprite_t
{
    SDL_Texture *T_sprite ;
    SDL_Rect *R_sprite ;
    bool print ;
}sprite_t;

typedef struct Vecteur
{
    float x ;
    float y ;
}vecteur ;

typedef struct Point_2d
{
    float x ;
    float y ;
}P2D ;

typedef struct AABB // Axis-Aligned Bounding Box
{
    P2D HG;
    P2D HD;
    P2D BG;
    P2D BD;
    vecteur Size ;
    P2D middle ;
} AABB;

typedef struct Character
{
    SDL_Texture *T_sprite ;
    SDL_Rect *R_sprite ;
    int life ;
    int protection ;
    bool print ;
    int type_shield ;
    bool shield ;
    bool helmet ;
    int player ;
    int sprite_type ;
    AABB point ;
    vecteur pos ;
}character;

typedef struct Timer
{
    int actualTime;
    int previousTime;
}timer;

typedef struct Bullet
{
    float x,y ;
    float DirX,DirY ;
    int vitesse ;
    vecteur v ;
    bool print ;
    SDL_Rect *R_Bullet ;
    SDL_Texture *T_Bullet ;
    AABB point ;
}bullet;
		    /*################################ Function ###############################*/
    /// \brief Procedure who initialize the timer
    /// Procedure ...
    /// \param t : timer*, ...
    void initialization_timer(timer *t);

    ///////////////////////////movement//////////////////////////////////

    /// \brief Function ...
    /// Function...
    /// \param sprite :character*, ...
    /// \param m : mouse, ...
    /// \param t : timer*
    /// \param block : SDL_Rect, ...
    /// \param second : float, ...
    /// \return SDL_Rect, ...
    SDL_Rect  left_movement(character *sprite, mouse m,timer *t, SDL_Rect block, float second);

    /// \brief Function
    /// Function...
    /// \param sprite :character*, ...
    /// \param m : mouse, ...
    /// \param t : timer*
    /// \param block : SDL_Rect, ...
    /// \param second : float, ...
    /// \return SDL_Rect, ...
    SDL_Rect  right_movement(character *sprite, mouse m,timer *t,  SDL_Rect block, float second);

    /// \brief Procedure
    /// Procedure ...
    /// \param arm : sprite_t*, ...
    /// \param c : mouse, ...
    /// \param block : SDL_Rect*, ...
    /// \param power : int, ...
    void aim_arm(sprite_t* arm , int aimX, int aimY, SDL_Rect* block, int power );

    /// \brief Function
    /// Function...
    /// \param size_width : int, ...
    /// \param size_height : int, ...
    /// \param x : int, ...
    /// \param y : int, ...
    /// \return SDL_Rect, ...
    SDL_Rect initialization_animation(int size_width, int size_height, int x , int y );

    /// \brief Procedure
    /// Procedure ...
    /// \param sprite : character*, ...
    /// \param type : int, ...
    /// \param width : int, ...
    /// \param height : int, ...
    /// \param x : int, ...
    /// \param y : int, ...
    void initialization(character* sprite, int type, int width, int height, int x, int y );

    /// \brief Procedure
    /// Procedure ...
    /// \param sprite : sprite_t*, ...
    /// \param width : int, ...
    /// \param height : int, ...
    /// \param x : int, ...
    /// \param y : int, ...
    void sprite_cons(sprite_t* sprite,int width ,int height ,int x ,int y );

    /// \brief Procedure
    /// Procedure ...
    /// \param cursor : sprite_t*, ...
    /// \param renderer : SDL_Renderer*, ...
    /// \param power : int, ...
    void cursor(sprite_t *cursor , SDL_Renderer *renderer, int power );

    /// \brief Function filling a array
    /// Function filling a array from a text file
    /// \param x : int, ...
    /// \param y : int, ...
    /// \param file : FILE*, ...
    /// \return char**, the array filling
    char** init_tab_dynamic( int x, int y, FILE *file );

    /// \brief Function
    /// Function ...
    /// \param hero : SDL_Rect*, ...
    /// \param Xcursor : int, ...
    /// \param Ycursor : int, ...
    /// \return vecteur, ...
    vecteur sbullet(SDL_Rect* hero, int Xcursor, int Ycursor);

    /// \brief Procedure
    /// Procedure ...
    /// \param block : SDL_Rect*, ...
    /// \param sens : int, ...
    /// \param t : timer*, ...
    /// \param second : float, ....
    void animation_boucle(SDL_Rect* block, int sens, timer* t, float second);

    /// \brief Procedure update coordinates of the sprite
    /// Procedure to update coordinates of the points of the sprite start to the sprite's middle point
    /// \param hero : character*, the sprite
    void sprite_update(character* hero);

    /// \brief Procedure collide beetween two thing
    /// Procedure if there is a collision between two sprites then it stop the sprite
    /// \param tab2 : char** , array of tile
    /// \param hero : character* , the sprite
    /// \param down : bool* , the boolean if the sprite can fell
    /// \param jump : bool* , the boolean if the sprite can jump
    /// \param scrolling_x : int , ...
    /// \param key: int* , a array of key
    /// \param scrol_actif : bool* , ...
    /// \param number_display_width : int , the number of tile in width
    /// \param number_display_height : int , the number of tile in height
    void collide( bool *scrolling_active,char** tab2, character* hero, bool *down, bool *jump, int scrolling_x, int *key, bool *scrol_actif,int number_display_width,int number_display_height);

    /// \brief Procedure return
    /// Procedure to stick the sprite to the closest position out the box
    /// \param V : vector , ...
    /// \param hero : character* , structure of the sprite
    /// \param box : AABB , box who is test the collide
    /// \param eps : double , constant of precision of the function
    void retour(vecteur V, character* hero, AABB box, double eps);

    /// \brief Function test box in other box
    /// Function return true if the box 1 in box 2
    /// \param box1 : AABB , first box
    /// \param box2 : AABB , second box
    /// \return bool, the test result : true if in or false is not in
    bool testbox(AABB box1,AABB box2);

    /// \brief Function test point in other box
    /// Function return true if the point 2D in the box
    /// \param point :P2D , The point
    /// \param box1 : AABB , The box
    /// \return bool, the test result : true if in or false is not in
    bool testpoint(P2D point,AABB box);



#endif // SPRITE_T_H_INCLUDED
