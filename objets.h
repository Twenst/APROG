#pragma once

#include "constantes.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

typedef IntPoint2 Coord;

class Personnage
{
    Coord crds; // coords du coin gauche haut
    Coord size; // taille du personnage

    //à ajouter l'image(s) à afficher; pour l'instant couleur
    Color clr;

    // Gameplay
    int hp;
    int scrolling_type;

    // Saut
    bool jumping;
    int t_jump; // cf eq saut
    int jump_height;

    public:
        Personnage();
        void draw() const;
        int getHp() const;
        void jump(float force = max_jump_force);
        void update_jump();
        bool is_jumping() const;
        void walk();

};

class Obstacle
{
    Coord crds; // coords du coin gauche haut
    Coord size; // taille de l'obstacle

    Color clr;

    int type; // Type de l'obstaccle

    public:
        Obstacle();
        void draw();




};
