#pragma once

#include <string>
#include <Imagine/Graphics.h>
using namespace Imagine;

typedef IntPoint2 Coord;

// Taille de la fenetre de jeu
const int w = 1024;
const int h = 1024;
const double fac = 8.;
const int msleep = 15;

// Niveau du sol
const int floor_level = (10./16.)*h;

// Carac du personnage
const int size_x = 4*fac; //hitbox de cette taille, image de largeur 8*fac
const int size_y = 12*fac;
const int crds_x_init = w/2 - size_x/2;
const int crds_y_init = floor_level - size_y;
const int lightforce_init = 16;

// Saut
const double jump_lenght = 1.2;

// Textures
const int nb_grass = 2;
const int nb_dirt = 3;
const int nb_sky = 5;
//const int nb_glow = 4;
const int nb_shadow = 5;
const std::string grass[nb_grass] = {"./assets/grass1.png","./assets/grass2.png"};
const std::string dirt[nb_dirt] = {"./assets/dirt1.png","./assets/dirt2.png","./assets/dirt3.png"};
const std::string sky[nb_sky] = {"./assets/sky1.png","./assets/sky2.png","./assets/sky3.png","./assets/sky4.png","./assets/sky5.png"};
const std::string left_arrow[2] = {"./assets/left_red.png","./assets/left_green.png"};
const std::string up_arrow[2] = {"./assets/up_red.png","./assets/up_green.png"};
const std::string right_arrow[2] = {"./assets/right_red.png","./assets/right_green.png"};
const std::string down_arrow[2] = {"./assets/down_red.png","./assets/down_green.png"};
//const std::string glow[nb_glow] = {"./assets/glow1.png","./assets/glow2.png","./assets/glow3.png","./assets/glow2.png"};
const std::string cave_name = "./assets/double_grotte.png";
const std::string background_name = "./assets/background.png";
const std::string shadows_name[nb_shadow] = {"./assets/shadow1.png","./assets/shadow2.png","./assets/shadow3.png","./assets/shadow4.png","./assets/shadow5.png"};
const std::string heart_name[2] = {"./assets/heart.png","./assets/heart_lost.png"};
const std::string earth_name = "./assets/start_background.png";

const std::string player_right_name[5] = {"./assets/character/right_walk1.png","./assets/character/right_walk2.png","./assets/character/right_walk3.png","./assets/character/right_walk4.png","./assets/character/right_down.png"};
const std::string player_right_alter_name[5] = {"./assets/character/right_walk1_alter.png","./assets/character/right_walk2_alter.png","./assets/character/right_walk3_alter.png","./assets/character/right_walk4_alter.png","./assets/character/right_down_alter.png"};
const std::string bat_name = "./assets/bat.png";

//Score
const std::string score_path = "./Score.txt";

//Title
const std::string gameover_name = "./assets/gameover.png";
const std::string keyboard_name = "./assets/keyboard.png";

//const std::string title = {"./assets/title"};
