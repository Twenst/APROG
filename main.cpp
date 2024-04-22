#include <Imagine/Graphics.h>
using namespace Imagine;

//---Constantes---//
#include "constantes.h"

//---Prototypes---//
#include "affichage.h"
#include "objets.h"
float minf(float a, float b);

//---Main---//
int main(int argc, char** argv)
{
    openWindow(w,h,"Swolling");

    Personnage player;
    float spacebar_timer = 1.5;
    while(player.getHp() > 0)
    {
        player.update_jump();

        noRefreshBegin();
        
        clearWindow();
        draw_background();
        player.draw();

        noRefreshEnd();

        if (not player.is_jumping())
        {
            Event e;
            getEvent(-1,e);

            if ((e.type == EVT_KEY_ON) and (e.key == KEY_UP))
            {
                spacebar_timer += 0.75;
            }
            if ((spacebar_timer >= max_jump_force) or ((e.type == EVT_KEY_OFF) and (e.key == KEY_UP)))
            {
                player.jump(minf(max_jump_force,spacebar_timer));
                spacebar_timer = 1.5;
            }
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