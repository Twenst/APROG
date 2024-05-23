#pragma once
#include "objets.h"
#include "constantes.h"
#include <Imagine/Graphics.h>
using namespace Imagine;



class Personnage
{
    Coord crds; // coords du coin gauche haut
    Coord size; // taille du personnage

    //à ajouter l'image(s) à afficher; pour l'instant couleur
    Color clr;

    //Vitesse
    int speed;
    double dash_speed;

    // Gameplay
    int hp;
    int max_hp;
    int scrolling_type;
    bool invincible;
    int invincible_duration;
    int invincible_count;
    int light_force;

    // Saut
    int max_height;
    bool jumping;
    double t_jump; // cf eq saut
    int jump_height;
    int falling; // falling = 1 -> montée, falling = 0 -> début de la chute, falling = -1 -> chute

    public:
        Personnage();
        void draw(int Timer) const;
        int getHp() const;
        void setCoords(int x,int y);//Cinématique
        void jump();
        void update_jump();
        bool is_jumping() const;
        void walk(Event e);
        void update_walk();
        void dash(Event e);
        void update_dash();
        void getHit(Obstacle& obstacle);
        void looseHP();
        void addHP();
        void setFalling(int f);
        int getFalling() const;
        void getBonus(Obstacle& obstacle);
        Coord getPos() const;
        Coord getSize() const;
        Coord getCenter() const;
        void update_status(); // Pour l'invincibilité par exemple
        int getLighForce() const;
        void setLighForce(int light_lvl);
};


