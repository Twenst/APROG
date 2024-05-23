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
void draw_glowing(Personnage player, Img glow_ul[nb_glow],Img glow_dl[nb_glow],Img glow_ur[nb_glow],Img glow_dr[nb_glow]);
void draw_cave(Img cave, int timer);
void draw_background(Img background);
void draw_shadow(Img shadows[nb_shadow]);
void draw_shadow(Img shadows[nb_shadow], Personnage player);

// Load functions
void load_textures(Img grass_textures[nb_grass],Img dirt_textures[nb_dirt], Img sky_textures[nb_sky]);
void load_arrow(Img left[2], Img right[2], Img up[2], Img down[2]);
void load_glow(Img glow_ul[nb_glow],Img glow_dl[nb_glow],Img glow_ur[nb_glow],Img glow_dr[nb_glow]);
void load_cave(Img & cave);
void load_background(Img & background);
void load_shadow(Img shadows[nb_shadow]);

// Edit functions
Img rotate(Img I);
Img applyMaskCircle(Img target, int radius, Coord center);