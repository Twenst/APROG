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
    int max_hp = 5;
    int scrolling_type;

    // Invincibilité
    bool invincible = false;
    int invincible_duration = 20;
    int invincible_count = 0;

    // Bonus
    int bonus_duration = 100; // même durée pour chaque bonus, on pourrait en avoir différent si on le voulait
    int bonus_count = 0;
    bool bonus = false;

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
        void update_status(Obstacle& obstacle); // Pour l'invincibilité par exemple et les bonus aussi
        void setSpeed(int newSpee);
        int getSpeeed() const;
};


