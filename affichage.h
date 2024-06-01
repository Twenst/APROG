#pragma once
#include "constantes.h"
#include "personnage.h"

typedef Image<AlphaColor> Img;
class Personnage;

// Draw functions
void draw_score(std::string score);
void draw_hp(int hp_num);
void draw_timer(int Timer);
void draw_scrolling(int typescrolling);
void draw_scrolling(int typescrolling,Img left[2], Img right[2], Img up[2], Img down[2]);
void draw_bonus(int type_bonus, const Img & shield_bonus, const Img & light_bonus, const Img & heart_bonus);
void draw_cave(const Img & cave, int timer);
void draw_background(const Img & background);
void draw_shadow(Img shadows[nb_shadow]);
void draw_shadow(Img shadows[nb_shadow], const Personnage & player);
void draw_heart(Img heart[2], const Personnage & player);
void draw_gameover(const Img & gameover);
void draw_keyboard(const Img & keyboard);
void draw_charac(Img player_right[10], Img player_left[10], const Personnage & player, int Timer);
void test_charac(Img player_right[10], Img player_left[10], const Personnage & player);
void draw_bat(const Img & bat, Coord c);
void draw_startback(const Img & starbackground);
void draw_rock(const Img & rock);
void draw_click(const Img & click);
void draw_bonus(int type_bonus, const Img & shield_bonus, Img light_bonus[2], Img heart_bonus[2], Coord coord, bool is_visible, int timer);
void draw_title(const Img & title);

// Load functions
void load_arrow(Img left[2], Img right[2], Img up[2], Img down[2]);
void load_cave(Img & cave);
void load_background(Img & background);
void load_shadow(Img shadows[nb_shadow]);
void load_heart(Img heart[2]);
void load_gameover(Img & gameover);
void load_keyboard(Img & keyboard);
void load_charac(Img player_right[10], Img player_left[10]);
void load_bat(Img & bat);
void load_startback(Img & startbackground);
void load_rock(Img & rock);
void load_click(Img & click);
void load_bonus(Img & shield_bonus,Img light_bonus[2],Img heart_bonus[2]);
void load_title(Img & title);

// Edit functions
Img rotate(const Img & I);
Img mirrorVert(const Img & I);
Img applyMaskCircle(const Img & target, int radius, Coord center);
Img applyMaskCircle(const Img & target, int radius, Coord center, double alpha);
Img applyMaskCircle(const Img & target, const std::vector<int>& radius, Coord center, const std::vector<double>& alphas);
