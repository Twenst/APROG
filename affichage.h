#pragma once
#include "constantes.h"
#include "objets.h"
#include <Imagine/Images.h>
using namespace Imagine;

void draw_background(Image<AlphaColor> grass_textures[nb_grass],Image<AlphaColor> dirt_textures[nb_dirt], Image<AlphaColor> sky_textures[nb_sky]);
void draw_floor(Image<AlphaColor> grass_textures[nb_grass],Image<AlphaColor> dirt_textures[nb_dirt]);
void draw_sky(Image<AlphaColor> sky_textures[nb_sky]);
void draw_hp(int hp_num);
void draw_timer(int Timer);
void draw_scrolling(int typescrolling);
void draw_scrolling(int typescrolling,Image<AlphaColor> left[2], Image<AlphaColor> right[2], Image<AlphaColor> up[2], Image<AlphaColor> down[2]);
void draw_glowing(Personnage player, Image<AlphaColor> glow_ul[nb_glow],Image<AlphaColor> glow_dl[nb_glow],Image<AlphaColor> glow_ur[nb_glow],Image<AlphaColor> glow_dr[nb_glow]);
void load_textures(Image<AlphaColor> grass_textures[nb_grass],Image<AlphaColor> dirt_textures[nb_dirt], Image<AlphaColor> sky_textures[nb_sky]);
void load_arrow(Image<AlphaColor> left[2], Image<AlphaColor> right[2], Image<AlphaColor> up[2], Image<AlphaColor> down[2]);
void load_glow(Image<AlphaColor> glow_ul[nb_glow],Image<AlphaColor> glow_dl[nb_glow],Image<AlphaColor> glow_ur[nb_glow],Image<AlphaColor> glow_dr[nb_glow]);
Image<AlphaColor> rotate(Image<AlphaColor> I);