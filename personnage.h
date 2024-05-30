#pragma once
#include "objets.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

class Obstacle;

class Personnage
{
    Coord crds; // coords du coin gauche haut
    Coord size; // taille du personnage

    //à ajouter l'image(s) à afficher; pour l'instant couleur
    Color clr;

    //Vitesse
    int speed;
    double dash_speed;
    int max_speed = 13;

    // Gameplay
    int hp;
    int max_hp;
    int scrolling_type;
    bool invincible;
    int invincible_duration;
    int invincible_count;
    int light_force;
    bool crouching;
    bool facing_right;

    // Bonus
    int bonus_duration; // même durée pour chaque bonus, on pourrait en avoir différent si on le voulait
    int bonus_count;
    int bonus_value;
    bool bonus;

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
        int getMaxHp() const;
        void setCoords(int x,int y);//Cinématique
        void jump();
        void update_jump();
        bool is_jumping() const;
        void walk(Event e);
        void update_walk();
        void dash(Event e);
        void crouch(Event e);
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
        void update_status(Obstacle& obstacle); // Pour l'invincibilité par exemple
        void setSpeed(int newSpeed);
        int getSpeed() const;
        int getLighForce() const;
        void setLighForce(int light_lvl);
        bool is_crouching() const;
        bool is_facing_right() const;
        void set_facing(int side);
        void set_crouching(bool b);
        bool is_invicible() const;
        void set_jumping(bool b);
};


