#pragma once

#include <string>
#include <Imagine/Graphics.h>
using namespace Imagine;

typedef IntPoint2 Coord;

// Taille de la fenetre de jeu
const int w = 1024;
const int h = 1024;
const double fac = 8.;

// Niveau du sol
const int floor_level = (10./16.)*h;

// Carac du personnage
const int size_x = 4*fac;
const int size_y = 8*fac;
const int crds_x_init = w/2 - size_x/2;
const int crds_y_init = floor_level - size_y;

// Saut
const double jump_lenght = 1.2;

// Textures
const int nb_grass = 2;
const int nb_dirt = 3;
const int nb_sky = 5;
const int nb_glow = 4;
const std::string grass[nb_grass] = {"./assets/grass1.png","./assets/grass2.png"};
const std::string dirt[nb_dirt] = {"./assets/dirt1.png","./assets/dirt2.png","./assets/dirt3.png"};
const std::string sky[nb_sky] = {"./assets/sky1.png","./assets/sky2.png","./assets/sky3.png","./assets/sky4.png","./assets/sky5.png"};
const std::string left_arrow[2] = {"./assets/left_red.png","./assets/left_green.png"};
const std::string up_arrow[2] = {"./assets/up_red.png","./assets/up_green.png"};
const std::string right_arrow[2] = {"./assets/right_red.png","./assets/right_green.png"};
const std::string down_arrow[2] = {"./assets/down_red.png","./assets/down_green.png"};
const std::string glow[nb_glow] = {"./assets/glow1.png","./assets/glow2.png","./assets/glow3.png","./assets/glow2.png"};
const std::string cave_name = "./assets/double_grotte.png";
const std::string background_name = "./assets/background.png";

//Score
const std::string score_path = "./Score.txt";
