#include <Imagine/Graphics.h>
using namespace Imagine;

//---Constantes---//
#include "constantes.h"

//---Prototypes---//
#include "affichage.h"
#include "objets.h"

//---Main---//
int main(int argc, char** argv)
{
    openWindow(w,h);

    Personnage player;
    while(player.getHp() > 0)
    {
        noRefreshBegin();
        
        clearWindow();
        draw_background();
        player.jump();
        player.update_jump();
        player.draw();

        noRefreshEnd();

        milliSleep(50);
    }


    endGraphics();
    return 0;
}

//---Fonctions---//