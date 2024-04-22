#pragma once

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

    // Saut
    bool jumping;
    int t_jump; // cf eq saut
    int jump_height;

    public:
        Personnage();
        void draw() const;
        int getHp() const;
        void jump(int force = 3); // 3 saut max
        void update_jump();

};

class Obstacle
{

};