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
void load_jumping(Personnage & player, float & spacebar_timer);

//---Main---//
int main(int argc, char** argv)
{
    openWindow(w,h,"Swolling");
    Partie partie;
    Personnage player;
    int nbr_obstacle = partie.get_nbr_obstacle();
    Obstacle* obstacle = new Obstacle[nbr_obstacle];
    float spacebar_timer = 1.5;
    int type_scrolling = 0;

    while(player.getHp() > 0)
    {
        player.update_jump();
        partie.Timer ++;

        noRefreshBegin();
        
        clearWindow();
        draw_background();
        draw_hp(player.getHp());
        draw_timer(partie.Timer);
        draw_scrolling(type_scrolling);

        // JOUEUR :

        //player.walk();
        player.draw();

        // OBSTACLES :
        bool outOfBounds = true;
        for(int i = 0 ; i<nbr_obstacle;i++)
        {
            if(obstacle[i].outOfBounds() == false)
            {
                outOfBounds= false;
            }
        }
        if(outOfBounds)
        {
            delete[] obstacle;
            Obstacle* obstacle = new Obstacle[nbr_obstacle];
            partie.init(obstacle);
            type_scrolling = partie.get_scrolling_type();
            nbr_obstacle = partie.get_nbr_obstacle();

        }
        for(int i = 0 ; i<nbr_obstacle;i++)
        {
            obstacle[i].move(type_scrolling);
            obstacle[i].draw();

        }

        noRefreshEnd();

        //Le joueur se fait touché
        for (int i = 0; i < nbr_obstacle; ++i)
        {
            if(player.getHit(obstacle[i]))
            {
                player.looseHP();
            }
        }

        load_jumping(player, spacebar_timer);

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

void load_jumping(Personnage & player, float & spacebar_timer)
{

    if (not player.is_jumping())
    {
        Event e2;
        getEvent(0,e2); // J'ai modifié à 0 ( et ça marche )
        if ((e2.type == EVT_KEY_ON) and (e2.key == KEY_UP))
        {
            spacebar_timer += 0.75;
        }
        if ((spacebar_timer >= max_jump_force) or ((e2.type == EVT_KEY_OFF) and (e2.key == KEY_UP)))
        {
            player.jump(minf(max_jump_force,spacebar_timer));
            spacebar_timer = 1.5;
        }
    }
}
