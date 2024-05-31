#include "affichage.h"
#include <Imagine/Graphics.h>
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

void draw_scrolling(int typescrolling,Img left[2], Img right[2], Img up[2], Img down[2])
{
	double fac2 = fac/2;
  	if(typescrolling == 0)
    {
      	//Les obstacles viennent de la droite
        display(left[rand()%2],w/2-4*fac,3*h/4,false,fac2);
    }
    if(typescrolling == 1)
    {
      	//Les obstacles viennent de la gauche
        display(right[rand()%2],w/2-4*fac,3*h/4,false,fac2);
    }
    if(typescrolling == 2)
    {
      	//Les obstacles viennent du haut
        display(down[rand()%2],w/2-4*fac,3*h/4,false,fac2);

    }
    if(typescrolling == 3)
    {
        //Les obstacles viennent du bas
        display(up[rand()%2],w/2-4*fac,3*h/4,false,fac2);

    }
}

void draw_timer(int Timer)
{
    drawString(30,90,std::to_string(Timer) + "M",WHITE,30,0,false,true);
}

Img rotate(const Img & I) // rotate an square image clockwise
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

void draw_cave(const Img & cave, int timer)
{
	display(cave,0,0,false,fac);
}

void load_cave(Img & cave)
{
	load(cave,stringSrcPath(cave_name));
}

void draw_background(const Img & background)
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

void draw_shadow(Img shadows[nb_shadow], const Personnage & player)
{
	std::vector<int> radius;
	for (int i = 2; i < 4; i++) radius.push_back(player.getLighForce()*i*fac); 

	std::vector<double> alphas(radius.size(), 0.75);
	Img shadow_mask = applyMaskCircle(shadows[rand()%nb_shadow],radius,player.getCenter()-Coord(0,size_y/4),alphas);
	display(shadow_mask,0,0,false,fac);
}

Img applyMaskCircle(const Img & target, int radius, Coord center)
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

Img applyMaskCircle(const Img & target, int radius, Coord center, double alpha)
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

Img applyMaskCircle(const Img & target, const std::vector<int>& radius, Coord center, const std::vector<double>& alphas)
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
				if (is_within_square(x, Coord(0,0), Coord(wid-1,hei-1)) and is_within_circle(x,radius[k],center))
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

void draw_heart(Img heart[2], const Personnage & player)
{
	int hp = player.getHp();
	for (int i = 1; i <= player.getMaxHp(); i++)
	{
		display(heart[(i <= hp) ? 0 : 1],w - 8*(i+1)*fac,8*fac,false,fac);
	}
}

void draw_gameover(const Img & gameover)
{
	display(gameover,0,0,false,fac*2);
}

void load_gameover(Img & gameover)
{
	load(gameover,stringSrcPath(gameover_name));
}

void draw_keyboard(const Img & keyboard)
{
	display(keyboard,0,0,false,fac);
}

void load_keyboard(Img & keyboard)
{
	load(keyboard,stringSrcPath(keyboard_name));
}

void load_charac(Img player_right[10], Img player_left[10])
{
	for (int i = 0; i < 5; i++) 
	{
		load(player_right[i], stringSrcPath(player_right_name[i]));
		load(player_right[5+i], stringSrcPath(player_right_alter_name[i]));
	}
	for (int i = 0; i < 10; i++)
	{
		player_left[i] = mirrorVert(player_right[i]);
	}
}

Img mirrorVert(const Img & I)
{
	int w = I.width(), h = I.height();
	Img Im(w,h);

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			Im(w-1-i,j) = I(i,j);
		}
	}
	return Im;
}

void draw_charac(Img player_right[10], Img player_left[10], const Personnage & player, int Timer)
{
	double fac2 = fac/2;
	Timer /= 5;
	int x = player.getPos().x()-size_x/2;
	int y = player.getPos().y();
	int hurt = (player.is_invicible()) ? 5 : 0;
	if (player.is_facing_right()) // Right
	{
		if (player.is_crouching())
		{
			display(player_right[4 + hurt*(Timer%2)],x,y,false,fac2);
		}
		else
		{
			display(player_right[(player.getPos().x()/50)%4 + hurt*(Timer%2)],x,y,false,fac2);
		}
	}
	else // Left
	{
		if (player.is_crouching())
		{
			display(player_left[4 + hurt*(Timer%2)],x,y,false,fac2);
		}
		else
		{
			display(player_left[(player.getPos().x()/50)%4 + hurt*(Timer%2)],x,y,false,fac2);
		}
	}
}

void test_charac(Img player_right[5], Img player_left[5], const Personnage & player)
{
	double fac2 = fac/2;

	for (int i = 0; i < 5; i++)
	{
		display(player_right[i],16*fac2*i,0,false,fac2);
		display(player_left[i],16*fac2*i,24*fac2,false,fac2);
	}
}

void load_bat(Img & bat)
{
	load(bat, stringSrcPath(bat_name));
}

void draw_bat(const Img & bat, Coord c)
{
	display(bat,c.x(),c.y(),false,fac);
}

void load_startback(Img & startbackground)
{
	load(startbackground, stringSrcPath(earth_name));
}

void draw_startback(const Img & starbackground)
{
	display(starbackground,0,0,false,fac);
}

void load_rock(Img & rock)
{
	load(rock, stringSrcPath(rock_name));
}

void load_bonus(Img & shield_bonus,Img light_bonus[2],Img heart_bonus[2])
{
    load(shield_bonus,stringSrcPath(shield_bonus_path));
	for (int i = 0; i < 2; i++)
	{
    	load(light_bonus[i],stringSrcPath(light_bonus_path[i]));
    	load(heart_bonus[i],stringSrcPath(heart_bonus_path[i]));
	}
}

void draw_bonus(int type_bonus, const Img & shield_bonus, Img light_bonus[2], Img heart_bonus[2],Coord coord,bool is_visible, int timer)
{
    if(is_visible)
    {
		timer /= 25;
        int x = coord.x();
        int y = coord.y();
        if(type_bonus == 1)
        {
            display(heart_bonus[timer%2],x,y,false,fac);
        }
        else if (type_bonus == 2)
        {
            display(light_bonus[timer%2],x,y,false,fac);
        }
        else if (type_bonus == 3)
        {
            display(shield_bonus,x,y,false,fac);
        }
    }

}

void draw_rock(const Img & rock)
{
	display(rock,0,0,false,fac);
}

void draw_click(const Img & click)
{
	display(click,0,0,false,fac);
}

void load_click(Img & click)
{
	load(click, stringSrcPath(click_name));
}

void load_title(Img & title)
{
	load(title, stringSrcPath(title_path));
}

void draw_title(const Img & title)
{
	display(title,0,0,false,2*fac);
}