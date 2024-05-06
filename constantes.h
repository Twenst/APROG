#pragma once

// Taille de la fenetre de jeu
const int w = 1200;
const int h = 1024;

// Niveau du sol
const int floor_level = (2./3.)*h;

// Carac du personnage
const int size_x = 30;
const int size_y = 60;
const int crds_x_init = w/2 - size_x/2;
const int crds_y_init = floor_level - size_y;

// Saut
const float max_jump_force = 10.;
//eq saut: y = (t - sqrt(max_height))² - max_height

