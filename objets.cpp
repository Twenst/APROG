#include "objets.h"
#include "constantes.h"
#include <math.h>
#include <random>

//---------------------PARTIE---------------------//

Partie::Partie()
{
    type_scrolling = 0;
    Timer = 0;
    nbr_obstacle = 1;
}

int Partie::get_scrolling_type() const
{
    return type_scrolling;
}

void Partie::update_scrolling(int type)
{
    type_scrolling = type;
    if(type == 0 or type == 1)
    {
        nbr_obstacle = 1;
    }
    if(type == 2 or type == 3)
    {
        nbr_obstacle = 9;
    }
    if(type == 4)
    {
        nbr_obstacle = 1;

    }
}

int Partie::get_nbr_obstacle() const
{
    return nbr_obstacle;
}

void Partie::init(Obstacle* obstacle) const
{
    for(int i = 0; i < nbr_obstacle;i++)
    {
        obstacle[i].init(type_scrolling);
    }
}



//---------------------OBSTACLE ET BONUS---------------------//

Obstacle::Obstacle()
{
    srand((unsigned int) time(0));
    size = Coord(35,40 + rand()%200);

    clr = BLACK;
    crds = Coord(w,floor_level - size.y());
    type = 0;
    is_visible = true;
}

void Obstacle::draw(const Img & shield_bonus,Img light_bonus[2],Img heart_bonus[2], int timer) const
{
    if(type == 0)
    {
        fillRect(crds.x(),crds.y(),size.x(),size.y(),clr);
    }
    else if(type == 1)
    {
        draw_bonus(bonus_type,shield_bonus,light_bonus,heart_bonus,crds,is_visible,timer);
    }
}

void Obstacle::move(int scrollingType)
{
    if(scrollingType == 0 or scrollingType == 1 or scrollingType == 4)
    {
      crds.x() = crds.x() - speed;//Gauche ou Droite
    }
    if(scrollingType == 2 or scrollingType == 3)
    {
      crds.y() = crds.y() - speed;//Gauche ou Droite
    }


}

int Obstacle::isFlying() const
{
    return flying;
}

bool Obstacle::outOfBounds() const
{
    if(crds.x()> w or crds.x() < -size.x() or crds.y() < -size.y() or crds.y() > h)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Obstacle::init(int scrollingType)
{

    alreadyHit = false;
    flying = 0;
    clr = BLACK;
    setType(0);
    is_visible = true;
    if(scrollingType == 0)
    {
        //Obstacles viennent de la droite
        flying = rand()%2; // Volant ou non
        speed = abs(speed)*1;
        size = Coord(35,40 + rand()%50);
        crds = Coord(w,floor_level - size.y());
        if(flying == 0)
        {
            size = Coord(60,20);
            crds.y() = floor_level - size.y() - size_y/2-rand()%30 ;
        }
    }
    if(scrollingType == 1)
    {
        //Obstacles viennent de la gauche
        flying = rand()%2; // Volant ou non
        speed = - abs(speed)*1;
        size = Coord(35,40 + rand()%50);
        crds = Coord(0,floor_level - size.y());
        if(flying == 0)
        {
            size = Coord(60,20);
            crds.y() = floor_level - size.y() - size_y/2 -rand()%30;
        }
    }
    if(scrollingType == 2)
    {
        //Obstacles viennent du haut
        speed = - abs(speed)*1;
        size = Coord(35 + rand()%70,35);
        crds = Coord(rand()%w,0);
    }
    if(scrollingType == 3)
    {
        //Obstacles viennent du bas
        speed =  abs(speed)*1;
        size = Coord(35 + rand()%70,35);
        crds = Coord(rand()%w,h);
    }
    if(scrollingType == 4)
    {
        //Bonus
        speed =  abs(speed)*1;
        size = Coord(40,40);
        crds = Coord(w,h/2);
        clr = RED;
        setType(1);
        setBonusType(rand()%3 + 1);
    }
}

int Obstacle::getBonusType() const
{
    return bonus_type;
}

void Obstacle::setBonusType(int new_type)
{
    bonus_type= new_type;
}


Coord Obstacle::getSize() const
{
    return size;
}

Coord Obstacle::getCoord() const
{
    return crds;
}
int Obstacle::getType() const
{
    return type;
}

void Obstacle::setType(int new_type)
{
    type = new_type;
}

void Obstacle::set_visibility(bool visible)
{
    is_visible = false;
}
