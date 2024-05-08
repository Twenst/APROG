#pragma once

#include "constantes.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

class Obstacle
{
    Coord crds; // Coords du coin gauche haut
    Coord size; // Taille de l'obstacle

    Color clr;

    int speed = 12; // Vitesse de l'obstacle

    int type; // Type de l'obstacle (1 : dangereux , 2 : Bonus)


public:
    Obstacle();
    Coord getSize() const;
    Coord getCoord() const;
    void draw() const;
    void move(int scrollingType);
    bool outOfBounds() const;
    void init(int scrollingType = 0); //Pour relancer l'obstacle depuis le début
    bool alreadyHit = false; // vérifie si l'obstacle à déjà touché le joueur
    int getType() const;
    void setType(int new_type);

};
class Partie
{
    int type_scrolling;
    int nbr_obstacle;

public:
    Partie();
    int Timer;
    void update_scrolling(int type);
    int get_scrolling_type() const;
    int get_nbr_obstacle() const;
    void init(Obstacle* obstacle) const;

};


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
    int scrolling_type;

    // Saut
    int max_height;
    bool jumping;
    double t_jump; // cf eq saut
    int jump_height;
    int falling; // falling = 1 -> montée, falling = 0 -> début de la chute, falling = -1 -> chute

    public:
        Personnage();
        void draw() const;
        int getHp() const;
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
};


