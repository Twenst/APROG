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
    void erase();

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


