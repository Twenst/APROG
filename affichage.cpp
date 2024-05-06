#include "affichage.h"

#include <Imagine/Graphics.h>
using namespace Imagine;
#include <Imagine/Images.h>
using namespace Imagine;

Color floor_color = ORANGE;

int pos(int a)
{
	return (a>0) ? a : 0;
}

int min(int a, int b)
{
	return (a > b) ? b : a;
}

void load_textures(Image<AlphaColor> grass_textures[nb_grass],Image<AlphaColor> dirt_textures[nb_dirt], Image<AlphaColor> sky_textures[nb_sky])
{
	for (int i = 0; i < nb_grass; i++) load(grass_textures[i],stringSrcPath(grass[i]));
	for (int i = 0; i < nb_dirt; i++) load(dirt_textures[i],stringSrcPath(dirt[i]));
	for (int i = 0; i < nb_sky; i++) load(sky_textures[i],stringSrcPath(sky[i]));
}

void draw_background(Image<AlphaColor> grass_textures[nb_grass],Image<AlphaColor> dirt_textures[nb_dirt], Image<AlphaColor> sky_textures[nb_sky])
{
	draw_sky(sky_textures);
    draw_floor(grass_textures,dirt_textures);
}

void draw_sky(Image<AlphaColor> sky_textures[nb_sky])
{
	for (int i = 0; 8*i*fac <= w; i++)
	{
		for (int j = 0; 8*j*fac < floor_level; j++)
		{
			display(sky_textures[min(pos(nb_sky-1-j),nb_sky-1)],8*i*fac,8*j*fac,false,fac);
		}
/* 		for (int j = floor_level/(8*fac); j > 0; j--)
		{
			display(sky_textures[pos(min(nb_sky-1-j,nb_sky-1))],8*i*fac,8*j*fac,false,fac);
		} */
	}
}

void draw_floor(Image<AlphaColor> grass_textures[nb_grass],Image<AlphaColor> dirt_textures[nb_dirt])
{
	for (int i = 0; 8*i*fac <= w; i++)
	{
		display(grass_textures[i%nb_grass],8*i*fac,floor_level,false,fac);

		for (int j = 1; 8*j*fac <= h-floor_level; j++)
		{
			display(dirt_textures[(i+j)%nb_dirt],8*i*fac,floor_level + 8*j*fac,false,fac);
		}
	}
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
      //Les obstacles viennent de la droite
      drawString(w/2 - 200 + rand()%2,h/4 + rand()%2,"DROITE",RED,46);
      drawString(w/2 - 200 + rand()%2,h/4 + rand()%2,"DROITE",BLUE,45);
    }
    if(typescrolling == 1)
    {
      //Les obstacles viennent de la gauche
      drawString(w/2 - 200 + rand()%2,h/4 + rand()%2,"GAUCHE",RED,46);
      drawString(w/2 - 200 + rand()%2,h/4 + rand()%2,"GAUCHE",BLUE,45);
    }
    if(typescrolling == 2)
    {
      //Les obstacles viennent du haut
      drawString(w/2 - 80 + rand()%2,h/4 + rand()%2,"HAUT",RED,46);
      drawString(w/2 - 80 + rand()%2,h/4 + rand()%2,"HAUT",BLUE,45);
    }
    if(typescrolling == 3)
    {
        //Les obstacles viennent du haut
      drawString(w/2 - 80 + rand()%2,h/4 + rand()%2,"BAS",RED,46);
      drawString(w/2 - 80 + rand()%2,h/4 + rand()%2,"BAS",BLUE,45);
    }
}

void draw_timer(int Timer)
{
    drawString(30,90,std::to_string(Timer),BLACK,30);
}
