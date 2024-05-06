#include <Imagine/Graphics.h>
using namespace Imagine;
#include <Imagine/Images.h>
using namespace Imagine;
#include <iostream>
#include <string>

//---Constantes---//
#include "constantes.h"

//---Prototypes---//
#include "affichage.h"
#include "objets.h"
float minf(float a, float b);
void load_jumping(Personnage & player,Event e);

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
    Event e;

    Image<AlphaColor> grass_textures[nb_grass]; Image<AlphaColor> dirt_textures[nb_dirt]; Image<AlphaColor> sky_textures[nb_sky];
	load_textures(grass_textures,dirt_textures,sky_textures);

    while(player.getHp() > 0)
    {
        getEvent(0,e);
        player.update_jump();
        //player.update_color(spacebar_timer);
        partie.Timer ++;

        noRefreshBegin();
        
        clearWindow();
        draw_background(grass_textures,dirt_textures,sky_textures);
        draw_hp(player.getHp());
        draw_timer(partie.Timer);
        draw_scrolling(type_scrolling);

        // JOUEUR :

        player.walk(e);
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
            nbr_obstacle = partie.get_nbr_obstacle();
            obstacle = new Obstacle[nbr_obstacle];
            partie.init(obstacle);
            type_scrolling = partie.get_scrolling_type();


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
            player.getHit(obstacle[i]);
        }

        // Saut
        load_jumping(player,e);

        //Changement de scrolling quand le timer atteint 1000
        if(partie.Timer % 100 == 0)
        {
            partie.update_scrolling(rand()%5) ;
        }

        
        milliSleep(15);
    }

    endGraphics();
    return 0;
}

//---Fonctions---//
float minf(float a, float b)
{
    return (a < b) ? a : b;
}

void load_jumping(Personnage & player,Event e)
{
    if (not player.is_jumping())
    {
        if (e.type == EVT_KEY_ON and e.key == KEY_UP)
        {
            player.setFalling(1);
            player.jump();
        }
    }
    else
    {
        if (e.type == EVT_KEY_OFF and e.key == KEY_UP and player.getFalling() == 1)
        {
            player.setFalling(0);
        }
    }
}
