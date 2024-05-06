#include "constantes.h"
#include "affichage.h"

#include <Imagine/Graphics.h>
using namespace Imagine;
#include <Imagine/Images.h>
using namespace Imagine;

Color floor_color = ORANGE;

void draw_background()
{
    draw_floor();
}

void draw_floor()
{
	Image<AlphaColor> grass_texture; Image<AlphaColor> dirt_texture;
	load(grass_texture,stringSrcPath(grass)); load(dirt_texture,stringSrcPath(dirt));

	for (int i = 0; 8*i*fac <= w; i++)
	{
		display(grass_texture,8*i*fac,floor_level,false,fac);
	}
    //affiche le sol au niveau défini
    //fillRect(0,floor_level,w,h,floor_color);
}

void draw_hp(int num_hp)
{
    for(int i = 0;i < num_hp ; i++)
    {
      drawString(200 + i*115,110,u8"❤️",RED,45);
    }

}

void draw_scrolling(int typescrolling)
{
    if(typescrolling == 0)
    {
      drawString(w/3 + rand()%2,h/4 + rand()%2,"DROITE",RED,46);
      drawString(w/3 + rand()%2,h/4 + rand()%2,"DROITE",BLUE,45);
    }
    if(typescrolling == 1)
    {
      drawString(w/3 + rand()%2,h/4 + rand()%2,"GAUCHE",RED,46);
      drawString(w/3 + rand()%2,h/4 + rand()%2,"GAUCHE",BLUE,45);
    }
}

void draw_timer(int Timer)
{
    drawString(30,90,std::to_string(Timer),BLACK,30);
}
