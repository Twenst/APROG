#include <Imagine/Graphics.h>
#include <iostream>
#include <string>
using namespace Imagine;

//---Constantes---//
#include "constantes.h"

//---Prototypes---//
#include "affichage.h"
#include "objets.h"
float minf(float a, float b);
void load_jumping(Personnage & player);

//---Main---//
int main(int argc, char** argv)
{
    openWindow(w,h,"Swolling");
    Partie partie;
    Personnage player;
    Obstacle obstacle;
    int type_scrolling = 0;

    while(player.getHp() > 0)
    {
        player.update_jump();
        //player.update_color(spacebar_timer);
        partie.Timer ++;

        noRefreshBegin();
        
        clearWindow();
        draw_background();
        draw_hp(player.getHp());
        draw_timer(partie.Timer);
        draw_scrolling(type_scrolling);



        // JOUEUR :

        //player.walk(); Ca marche pas cette merde
        player.draw();

        // OBSTACLES :
        if(obstacle.outOfBounds())
        {

            obstacle.init(partie.get_scrolling_type());
            type_scrolling = partie.get_scrolling_type();
        }
        obstacle.move();
        obstacle.draw();

        noRefreshEnd();

        //Le joueur se fait touché
        if(player.getHit(obstacle))
        {
            player.looseHP();
        }

        // Saut
        load_jumping(player);

        //Changement de scrolling quand le timer atteint 1000
        if(partie.Timer % 100 == 0)
        {
            partie.update_scrolling(rand()%2) ;
        }

        
        milliSleep(25);
    }

    endGraphics();
    return 0;
}

//---Fonctions---//
float minf(float a, float b)
{
    return (a < b) ? a : b;
}

void load_jumping(Personnage & player)
{
    Event e2;
    getEvent(0,e2); // J'ai modifié à 0 ( et ça marche )
    if (not player.is_jumping())
    {
        if (e2.type == EVT_KEY_ON and e2.key == KEY_UP)
        {
            player.setFalling(1);
            player.jump();
        }
    }
    else
    {
        if (e2.type == EVT_KEY_OFF and e2.key == KEY_UP and player.getFalling() == 1) 
        {
            player.setFalling(0);
        }
    }
}
