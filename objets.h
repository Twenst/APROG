#pragma once

#include "constantes.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

typedef IntPoint2 Coord;

class Partie
{
    int type_scrolling;

public:
    Partie();
    int Timer;
    void update_scrolling(int type);
    int get_scrolling_type() const;

};

class Obstacle
{
    Coord crds; // Coords du coin gauche haut
    Coord size; // Taille de l'obstacle

    Color clr;

    int speed = 12; // Vitesse de l'obstacle

    int type; // Type de l'obstacle


public:
    Obstacle();
    Coord getSize() const;
    Coord getCoord() const;
    void draw() const;
    void move();
    bool outOfBounds() const;
    void init(int scrollingType = 0); //Pour relancer l'obstacle depuis le début
    bool alreadyHit = false; // vérifie si l'obstacle à déjà touché le joueur



};

class Personnage
{
    Coord crds; // coords du coin gauche haut
    Coord size; // taille du personnage

    //à ajouter l'image(s) à afficher; pour l'instant couleur
    Color clr;

    //Vitesse
    int speed = 10;

    // Gameplay
    int hp;
    int scrolling_type;

    // Saut
    bool jumping;
    int t_jump; // cf eq saut
    int jump_height;
    int falling; // falling = 1 -> montée, falling = 0 -> début de la chute, falling = -1 -> chute

    public:
        Personnage();
        void draw() const;
        int getHp() const;
        void jump();
        void update_jump();
        void update_color(float power); //Selon la force du saut
        bool is_jumping() const;
        void walk();
        bool getHit(Obstacle& obstacle) const;
        void looseHP();
        void setFalling(int f);
        int getFalling() const;

};


