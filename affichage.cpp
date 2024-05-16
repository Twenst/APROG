#include "affichage.h"

#include <Imagine/Graphics.h>
using namespace Imagine;
#include <Imagine/Images.h>
using namespace Imagine;

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

void load_arrow(Image<AlphaColor> left[2], Image<AlphaColor> right[2], Image<AlphaColor> up[2], Image<AlphaColor> down[2])
{
  for (int i = 0; i < 2; i++)
  {
    load(left[i],stringSrcPath(left_arrow[i]));
    load(down[i],stringSrcPath(down_arrow[i]));
    load(right[i],stringSrcPath(right_arrow[i]));
    load(up[i],stringSrcPath(up_arrow[i]));
  }
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
      drawString(350 + i*115,110,u8"❤️",RED,45);
    }
}


void draw_scrolling(int typescrolling,Image<AlphaColor> left[2], Image<AlphaColor> right[2], Image<AlphaColor> up[2], Image<AlphaColor> down[2])
{
  	if(typescrolling == 0)
    {
      	//Les obstacles viennent de la droite
        display(left[rand()%2],w/2-4*fac,3*h/4,false,fac);
    }
    if(typescrolling == 1)
    {
      	//Les obstacles viennent de la gauche
        display(right[rand()%2],w/2-4*fac,3*h/4,false,fac);
    }
    if(typescrolling == 2)
    {
      	//Les obstacles viennent du haut
        display(down[rand()%2],w/2-4*fac,3*h/4,false,fac);

    }
    if(typescrolling == 3)
    {
        //Les obstacles viennent du bas
        display(up[rand()%2],w/2-4*fac,3*h/4,false,fac);

    }
}

void draw_timer(int Timer)
{
    drawString(30,90,std::to_string(Timer) + "M",BLACK,30,0,false,true);
}

void load_glow(Image<AlphaColor> glow_ul[3],Image<AlphaColor> glow_dl[3],Image<AlphaColor> glow_ur[3],Image<AlphaColor> glow_dr[3])
{
	for (int i = 0; i < nb_glow; i++)
	{
		load(glow_ul[i],stringSrcPath(glow[i]));
		glow_dl[i] = rotate(glow_ul[i]);
		glow_dr[i] = rotate(glow_dl[i]);
		glow_ur[i] = rotate(glow_dr[i]);
	}
}

void draw_glowing(Personnage player, Image<AlphaColor> glow_ul[nb_glow],Image<AlphaColor> glow_dl[nb_glow],Image<AlphaColor> glow_ur[nb_glow],Image<AlphaColor> glow_dr[nb_glow])
{
	// Affiche l'effet d'éclairement sur le centre du joueur
	Coord c = player.getPos() + player.getSize()/2;

	int i = time(NULL)%nb_glow;
	display(glow_ul[i],c.x()-16*fac,c.y()-16*fac,false,fac);
	display(glow_ur[i],c.x(),c.y()-16*fac,false,fac);
	display(glow_dr[i],c.x(),c.y(),false,fac);
	display(glow_dl[i],c.x()-16*fac,c.y(),false,fac);
}

Image<AlphaColor> rotate(Image<AlphaColor> I) // rotate an square image clockwise
{
	int w = I.width(), h = I.height();
	Image<AlphaColor> Ir(h,w);

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			Ir(j,w-1-i) = I(i,j);
		}
	}
	return Ir;
}

void draw_score(std::string score)
{
    drawString(20,h-10,"Meilleur Score: " + score + "M",BLACK,20,0,false,true);
}

void draw_cave(Image<AlphaColor> cave, int timer)
{
	display(cave,0,0,false,fac);
}

void load_cave(Image<AlphaColor> cave)
{
	load(cave,stringSrcPath(cave_name));
}

void draw_background(Image<AlphaColor> background)
{
	display(background,0,0,false,fac);
}

void load_background(Image<AlphaColor> background)
{
	load(background, stringSrcPath(background_name));
}