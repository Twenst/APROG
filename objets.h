#pragma once
#include "affichage.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

typedef Image<AlphaColor> Img;


class Obstacle
{
    Coord crds; // Coords du coin gauche haut
    Coord size; // Taille de l'obstacle

    Color clr;

    int speed = 16; // Vitesse de l'obstacle

    int type; // Type de l'obstacle (1 : dangereux , 2 : Bonus)
    int flying = 0; //Obstacle qui vole ou non (0 : non , 1 : oui)
    int bonus_type = 0 ;//(0 : aucun bonus, 1 : bonus 1, 2 : bonus 2, 3 : bonus 3)
    bool is_visible = true;


public:
    Obstacle();
    Coord getSize() const;
    Coord getCoord() const;
    void draw(const Img & shield_bonus,Img light_bonus[2], Img heart_bonus[2], int timer) const;
    void move(int scrollingType);
    bool outOfBounds() const;
    void init(int scrollingType = 0); //Pour relancer l'obstacle depuis le début
    bool alreadyHit = false; // vérifie si l'obstacle à déjà touché le joueur
    int getType() const;
    void setType(int new_type);
    int isFlying() const;
    int getBonusType() const;
    void setBonusType(int new_type);
    void set_visibility(bool visible);

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


