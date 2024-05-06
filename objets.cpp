#include "objets.h"
#include "constantes.h"
#include <math.h>
#include <random>

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
    else
    {
        nbr_obstacle = 3;
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


Personnage::Personnage()
{
    size = Coord(size_x,size_y);
    crds = Coord(crds_x_init,crds_y_init);
    clr = BLUE;
    hp = 7;
    jumping = false;
    t_jump = 0;
    jump_height = 0;
}

void Personnage::draw() const
{
    // A FAIRE: AFFICHER LE SPRITE A LA PLACE DE LA COULEUR

    fillRect(crds.x(),crds.y(),size.x(),size.y(),clr);
}

int Personnage::getHp() const
{
    return hp;
}

void Personnage::jump(float force)
{
    if (not jumping)
    {
        jumping = true;
        jump_height = (floor_level - size_y) * (force/max_jump_force);
        t_jump = 0;
    }
}

void Personnage::update_color(float power)
{
    Color col(255 - (power*255)/max_jump_force,0,255 - (power*255)/max_jump_force );
    clr =  col;
}

void Personnage::update_jump() //eq saut: y = (t - sqrt(max_height))² - max_height 
{
    if (jumping)
    {
        int new_y = pow(t_jump - sqrt(jump_height),2) - jump_height + floor_level; 

        if (new_y <= floor_level)
        {
            crds.y() = new_y - size_y;
            t_jump++;
        }
        else
        {
            crds.y() = crds_y_init;
            t_jump = 0;
            jumping = false;
            jump_height = 0;
            flushEvents();
        }
    } 
}

bool Personnage::is_jumping() const
{
    return jumping;
}

void Personnage::walk()
{
    Event e;
    getEvent(-1,e);
    if ((e.type == EVT_KEY_ON) and (e.key == KEY_RIGHT))
    {
        crds.x() = crds.x() + speed;
        flushEvents();

    }
    if ((e.type == EVT_KEY_ON) and (e.key == KEY_LEFT))
    {
        crds.x() = crds.x() - speed;
        flushEvents();

    }
}

bool Personnage::getHit(Obstacle& obstacle) const
{
    if(obstacle.alreadyHit == false)
    {
        if(crds.x() + size.x() < obstacle.getCoord().x() or crds.y()+size.y() < obstacle.getCoord().y()
            or crds.x() > obstacle.getCoord().x() + obstacle.getSize().x() or crds.y()> obstacle.getCoord().y()+ obstacle.getSize().y())
        {
            return false;
        }
        else
        {
            obstacle.alreadyHit = true;
            return true;
        }
    }
    else
    {
        return false;
    }
}

void Personnage::looseHP()
{
    hp --;
}


Obstacle::Obstacle()
{
    srand((unsigned int) time(0));
    size = Coord(35,40 + rand()%200);

    clr = BLACK;
    crds = Coord(w,floor_level - size.y());
    type = 1;
}


void Obstacle::draw() const
{
    fillRect(crds.x(),crds.y(),size.x(),size.y(),clr);
}

void Obstacle::move(int scrollingType)
{
    if(scrollingType == 0 or scrollingType == 1)
    {
      crds.x() = crds.x() - speed;//Gauche ou Droite
    }
    if(scrollingType == 2 or scrollingType == 3)
    {
      crds.y() = crds.y() - speed;//Gauche ou Droite
    }


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

    if(scrollingType == 0)
    {
        //Obstacles viennent de la droite
        speed = abs(speed)*1;
        size = Coord(35,40 + rand()%50);
        crds = Coord(w,floor_level - size.y());
    }
    if(scrollingType == 1)
    {
        //Obstacles viennent de la gauche
        speed = - abs(speed)*1;
        size = Coord(35,40 + rand()%50);
        crds = Coord(0,floor_level - size.y());
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
}

Coord Obstacle::getSize() const
{
    return size;
}

Coord Obstacle::getCoord() const
{
    return crds;
}
