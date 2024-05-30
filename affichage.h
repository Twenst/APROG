#pragma once
#include "constantes.h"
#include "personnage.h"
#include <Imagine/Images.h>
using namespace Imagine;

typedef Image<AlphaColor> Img;

// Draw functions
void draw_background(Img grass_textures[nb_grass],Img dirt_textures[nb_dirt], Img sky_textures[nb_sky]);
void draw_floor(Img grass_textures[nb_grass],Img dirt_textures[nb_dirt]);
void draw_sky(Img sky_textures[nb_sky]);
void draw_score(std::string score);
void draw_hp(int hp_num);
void draw_timer(int Timer);
void draw_scrolling(int typescrolling);
void draw_scrolling(int typescrolling,Img left[2], Img right[2], Img up[2], Img down[2]);
//void draw_glowing(Personnage player, Img glow_ul[nb_glow],Img glow_dl[nb_glow],Img glow_ur[nb_glow],Img glow_dr[nb_glow]);
void draw_cave(Img cave, int timer);
void draw_background(Img background);
void draw_shadow(Img shadows[nb_shadow]);
void draw_shadow(Img shadows[nb_shadow], Personnage player);
void draw_heart(Img heart[2], Personnage player);
void draw_gameover(Img gameover);
void draw_keyboard(Img keyboard);
void draw_charac(Img player_right[10], Img player_left[10], Personnage player, int Timer);
void test_charac(Img player_right[10], Img player_left[10], Personnage player);
void draw_bat(Img bat, Coord c);
void draw_startback(Img starbackground);

// Load functions
void load_textures(Img grass_textures[nb_grass],Img dirt_textures[nb_dirt], Img sky_textures[nb_sky]);
void load_arrow(Img left[2], Img right[2], Img up[2], Img down[2]);
//void load_glow(Img glow_ul[nb_glow],Img glow_dl[nb_glow],Img glow_ur[nb_glow],Img glow_dr[nb_glow]);
void load_cave(Img & cave);
void load_background(Img & background);
void load_shadow(Img shadows[nb_shadow]);
void load_heart(Img heart[2]);
void load_gameover(Img & gameover);
void load_keyboard(Img & keyboard);
void load_charac(Img player_right[10], Img player_left[10]);
void load_bat(Img & bat);
void load_startback(Img & startbackground);

// Edit functions
Img rotate(Img I);
Img mirrorVert(Img I);
Img applyMaskCircle(Img target, int radius, Coord center);
Img applyMaskCircle(Img target, int radius, Coord center, double alpha);
Img applyMaskCircle(Img target, const std::vector<int>& radius, Coord center, const std::vector<double>& alphas);