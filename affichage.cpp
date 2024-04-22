#include "constantes.h"
#include "affichage.h"

#include <Imagine/Graphics.h>
using namespace Imagine;

Color floor_color = ORANGE;

void draw_background()
{
    draw_floor();
}

void draw_floor()
{
    //affiche le sol au niveau défini
    fillRect(0,floor_level,w,h,floor_color);
}