#ifndef SPRITE_T_H_INCLUDED
#define SPRITE_T_H_INCLUDED
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*############################# Abstract Type #############################*/

/// \struct mouse " coordinate of the mouse "
typedef struct Mouse
{
    unsigned short int  x,y ;
    bool print ;
}mouse ;

/// \struct compteur " ... "
typedef struct Compteur
{
    int nb ;
}compteur ;

/// \struct sprite_t "..."
typedef struct Sprite_t
{
    SDL_Texture *T_sprite ;
    SDL_Rect *R_sprite ;
    bool print ;
}sprite_t;

/// \struct vecteur " vector type"

typedef struct Vector
{
    float x ;
    float y ;
}vecteur ;

/// \struct P2D " coordinates of a point "

typedef struct Point_2d
{
    float x ;
    float y ;
}P2D ;

/// \struct AABB " Axis-Aligned Bounding Box "

typedef struct AABB
{
    P2D HG;
    P2D HD;
    P2D BG;
    P2D BD;
    vecteur Size ;
    P2D middle ;
} AABB;

/// \struct character " gather of all attribute for a sprite "

typedef struct Character
{
    bool jump ;
    bool down;
    int player ;
    int sprite_type ;
    int life ;

    SDL_Texture *T_sprite ;
    SDL_Rect *R_sprite ;

    bool print ;

    AABB point ;
    vecteur pos ;
    int protection ;
    int type_shield ;
    bool shield ;
    bool helmet ;

}character;

/// \struct timer " ... "

typedef struct Timer
{
    int actualTime;
    int previousTime;
}timer;

/// \struct bullet " gather of all attribute for a bullet "

typedef struct Bullet
{
    int vitesse ;

    SDL_Rect *R_Bullet ;
    SDL_Texture *T_Bullet ;

    float x,y ;
    float DirX,DirY ;

    bool print ;

    vecteur v ;

}bullet;

/*################################ Function ###############################*/

    /// \brief Procedure who initialize the timer
    /// Procedure ...
    /// \param t : timer*, ...
    void initialization_timer(timer *t);

    ///////////////////////////movement//////////////////////////////////

    /// \brief Function left movement
    /// Function which return  a picture animation and change the position's sprite
    /// \param sprite :character*, choose the character you want to animate
    /// \param m : mouse, value of the mouse to know where the sprite looks
    /// \param t : timer*
    /// \param block : SDL_Rect, choose picture
    /// \param second : float,  how long is an amimation
    /// \return SDL_Rect, picture choose
   // SDL_Rect  left_movement(character *sprite, mouse m,timer *t, SDL_Rect block, float second);

    SDL_Rect  left_movement(int type, character *sprite, mouse m, timer *t,  SDL_Rect block, float second);
    ///\brief Function right movement
    /// Function which return  a picture animation and change the position's sprite
    /// \param sprite :character*, choose the character you want to animate
    /// \param m : mouse, value of the mouse to know where the sprite looks
    /// \param t : timer*
    /// \param block : SDL_Rect, choose picture
    /// \param second : float,  how long is an amimation
    /// \return SDL_Rect, picture choose
    SDL_Rect  right_movement(character *sprite, mouse m,timer *t,  SDL_Rect block, float second, bool scrolling_actif);

    /// \brief Procedure aim
    /// Procedure which choose the position on the picture which arm a sprite
    /// \param arm : sprite_t* you can to animate
    /// \param int aimX x coordinate  you can aim
    /// \param int aimY y coordinate  you can aim
    /// \param block : SDL_Rect*, ...
    /// \param power : int, chose your power for choose the picture list
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

    /// \brief Procedure which  initialize character
    /// Procedure which initialize all
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
    /// \param t : timer*,
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
    void collide( bool *scrolling_active,char** tab2, character* hero, bool *down, bool *jump, int scrolling_x, int *key,int number_display_width,int number_display_height);

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

    /// \brief Procedure loading
    /// Procedure to initialize the texture display and her coordinate
    /// \param S_t : struct , the struct for the initialize
    /// \param name_picture : char* , the name and the way of the file .xcf
    /// \param width : int, the width of the SDL_texture
    /// \param height : int, the height of the SDL_texture
    /// \param x : int, the coordinate x of the SDL_texture
    /// \param y : int, the coordinate y of the SDL_texture
    /// \param renderer : SDL_Renderer, ...
    /// \param cons : boolean, if it is necessary to call the function sprite_cons
    sprite_t* loading ( char* name_picture, int width ,int height ,int x ,int y, SDL_Renderer* renderer, bool cons);

   // void enemi_movement(character* sprite, character* target, int scrolling );



#endif // SPRITE_T_H_INCLUDED
