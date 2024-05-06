#include "objets.h"
#include "constantes.h"
#include <math.h>
#include <random>

Partie::Partie()
{
    type_scrolling = 0;
    Timer = 0;
}

int Partie::get_scrolling_type() const
{
    return type_scrolling;
}

void Partie::update_scrolling(int type)
{
    type_scrolling = type;
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
<<<<<<< HEAD
    Event e;
    getEvent(-2,e);
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

void Obstacle::move()
{
    crds.x() = crds.x() - speed;

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
    size = Coord(35,40 + rand()%200);


    if(scrollingType == 0)
    {
        //Obstacle se dirige vers la droite
        crds = Coord(w,floor_level - size.y());
        speed = abs(speed)*1.1;
    }
    else
    {
         //Obstacle se dirige vers la gauche
        crds = Coord(0,floor_level - size.y());
        speed = - abs(speed)*1.1;
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
=======
    int k = getKey();

    if (k == KEY_LEFT)
    {
        crds.x() -= 5; 
    }
    if (k == KEY_RIGHT)
    {
        crds.x() += 5;
    }
}
>>>>>>> 5e1b5dd670e312d01e37ac2477d2156eb18df91a
