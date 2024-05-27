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

int max(int a, int b)
{
	return (a < b) ? b : a;
}

bool is_within_square(Coord x, Coord c1, Coord c2)
{
	bool res = (x.x() <= max(c1.x(), c2.x()));
	res = res and (x.y() <= max(c1.y(), c2.y()));
	res = res and (x.y() >= min(c1.y(), c2.y()));
	res = res and (x.x() >= min(c1.x(), c2.x()));

	return res;
}

bool is_within_circle(Coord x, int radius, Coord center)
{
	Coord p = 8*x - center;
	return (radius*radius >= p.x()*p.x() + p.y()*p.y());
}

void load_textures(Img grass_textures[nb_grass],Img dirt_textures[nb_dirt], Img sky_textures[nb_sky])
{
	for (int i = 0; i < nb_grass; i++) load(grass_textures[i],stringSrcPath(grass[i]));
	for (int i = 0; i < nb_dirt; i++) load(dirt_textures[i],stringSrcPath(dirt[i]));
	for (int i = 0; i < nb_sky; i++) load(sky_textures[i],stringSrcPath(sky[i]));
}

void load_arrow(Img left[2], Img right[2], Img up[2], Img down[2])
{
  for (int i = 0; i < 2; i++)
  {
    load(left[i],stringSrcPath(left_arrow[i]));
    load(down[i],stringSrcPath(down_arrow[i]));
    load(right[i],stringSrcPath(right_arrow[i]));
    load(up[i],stringSrcPath(up_arrow[i]));
  }
}

void draw_background(Img grass_textures[nb_grass],Img dirt_textures[nb_dirt], Img sky_textures[nb_sky])
{
	draw_sky(sky_textures);
    draw_floor(grass_textures,dirt_textures);
}

void draw_sky(Img sky_textures[nb_sky])
{
	for (int i = 0; 8*i*fac <= w; i++)
	{
		for (int j = 0; 8*j*fac < floor_level; j++)
		{
			display(sky_textures[min(pos(nb_sky-1-j),nb_sky-1)],8*i*fac,8*j*fac,false,fac);
		}
	}
}

void draw_floor(Img grass_textures[nb_grass],Img dirt_textures[nb_dirt])
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


void draw_scrolling(int typescrolling,Img left[2], Img right[2], Img up[2], Img down[2])
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
    drawString(30,90,std::to_string(Timer) + "M",WHITE,30,0,false,true);
}

/* void load_glow(Img glow_ul[3],Img glow_dl[3],Img glow_ur[3],Img glow_dr[3])
{
	for (int i = 0; i < nb_glow; i++)
	{
		load(glow_ul[i],stringSrcPath(glow[i]));
		glow_dl[i] = rotate(glow_ul[i]);
		glow_dr[i] = rotate(glow_dl[i]);
		glow_ur[i] = rotate(glow_dr[i]);
	}
}

void draw_glowing(Personnage player, Img glow_ul[nb_glow],Img glow_dl[nb_glow],Img glow_ur[nb_glow],Img glow_dr[nb_glow])
{
	// Affiche l'effet d'éclairement sur le centre du joueur
	Coord c = player.getPos() + player.getSize()/2;

	int i = time(NULL)%nb_glow;
	display(glow_ul[i],c.x()-16*fac,c.y()-16*fac,false,fac);
	display(glow_ur[i],c.x(),c.y()-16*fac,false,fac);
	display(glow_dr[i],c.x(),c.y(),false,fac);
	display(glow_dl[i],c.x()-16*fac,c.y(),false,fac);
} */

Img rotate(Img I) // rotate an square image clockwise
{
	int w = I.width(), h = I.height();
	Img Ir(h,w);

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
    drawString(20,h-10,"Meilleur Score: " + score + "M",WHITE,20,0,false,true);
}

void draw_cave(Img cave, int timer)
{
	display(cave,0,0,false,fac);
}

void load_cave(Img & cave)
{
	load(cave,stringSrcPath(cave_name));
}

void draw_background(Img background)
{
	display(background,0,0,false,fac);
}

void load_background(Img & background)
{
	load(background, stringSrcPath(background_name));
}

void load_shadow(Img shadows[nb_shadow])
{
	for (int i = 0; i < nb_shadow; i++)
	{
		load(shadows[i],stringSrcPath(shadows_name[i]));
	}
}

void draw_shadow(Img shadows[nb_shadow])
{
	display(shadows[rand()%nb_shadow],0,0,false,fac);
}

void draw_shadow(Img shadows[nb_shadow], Personnage player)
{
	std::vector<int> radius;
	for (int i = 0; i < player.getLighForce(); i++) radius.push_back(4*(i+1)*fac); 

	std::vector<double> alphas(radius.size(), 0.75);
	Img shadow_mask = applyMaskCircle(shadows[rand()%nb_shadow],radius,player.getCenter(),alphas);
	display(shadow_mask,0,0,false,fac);
}

Img applyMaskCircle(Img target, int radius, Coord center)
{
	Img res = target.clone();
	int wid = target.width(), hei = target.height(); 

	for (int i = 0; i < wid; i++)
	{
		for (int j = 0; j < hei; j++)
		{
			Coord x(i,j);
			if (is_within_circle(x,radius,center))
			{
				res(i,j).a() = 0;
			}
		}
	}

	return res;
}

Img applyMaskCircle(Img target, int radius, Coord center, double alpha)
{
	Img res = target.clone();
	int wid = target.width(), hei = target.height(); 

	for (int i = 0; i < wid; i++)
	{
		for (int j = 0; j < hei; j++)
		{
			Coord x(i,j);
			if (is_within_circle(x,radius,center))
			{
				res(i,j).a() *= alpha;
			}
		}
	}

	return res;
}

int max(const std::vector<int>& radius)
{
	int m = radius[0];
	for (int i = 0; i < radius.size(); i++)
	{
		m = (radius[i] > m) ? radius[i] : m;
	}
	return m;
}

Img applyMaskCircle(Img target, const std::vector<int>& radius, Coord center, const std::vector<double>& alphas)
{
	assert(radius.size() == alphas.size());
	Img res = target.clone();
	int wid = target.width(), hei = target.height(); 
	int rad_max = max(radius);

	for (int i = center.x()/fac - rad_max; i <= center.x()/fac + rad_max; i++)
	{
		for (int j = center.y()/fac - rad_max; j <= center.y()/fac + rad_max; j++)
		{
			Coord x(i,j);
			for (int k = 0; k < radius.size(); k++)
			{
				if (is_within_square(x, Coord(0,0), Coord(wid,hei)) and is_within_circle(x,radius[k],center))
				{
				res(i,j).a() *= alphas[k];
				}
			}
		}
	}

	return res;
}

void load_heart(Img heart[2])
{
	load(heart[0],stringSrcPath(heart_name[0]));
	load(heart[1],stringSrcPath(heart_name[1]));
}

void draw_heart(Img heart[2], Personnage player)
{
	int hp = player.getHp();
	for (int i = 1; i <= player.getMaxHp(); i++)
	{
		display(heart[(i <= hp) ? 0 : 1],w - 8*(i+1)*fac,8*fac,false,fac);
	}
}

void draw_gameover(Img gameover)
{
	display(gameover,0,0,false,fac*2);
}

void load_gameover(Img & gameover)
{
	load(gameover,stringSrcPath(gameover_name));
}

void draw_keyboard(Img keyboard)
{
	display(keyboard,0,0,false,fac*2);
}

void load_keyboard(Img & keyboard)
{
	load(keyboard,stringSrcPath(keyboard_name));
}