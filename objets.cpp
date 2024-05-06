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
    falling = 1;
}

void Personnage::draw() const
{
    // A FAIRE: AFFICHER UN SPRITE A LA PLACE DE LA COULEUR

    fillRect(crds.x(),crds.y(),size.x(),size.y(),clr);
}

int Personnage::getHp() const
{
    return hp;
}

void Personnage::jump()
{
    if (not jumping)
    {
        jumping = true;
        t_jump = 0;
    }
}

void Personnage::update_color(float power)
{
    Color col(255 - (power*255)/max_jump_force,0,255 - (power*255)/max_jump_force);
    clr =  col;
}

void Personnage::update_jump() //eq saut: y = (t - sqrt(max_height))² - max_height 
{
    // falling = 1 -> montée, falling = 0 -> début de la chute, falling = -1 -> chute
    if (jumping)
    {
        if (falling == 1) // Monte
        {
            int max_height = floor_level - size_y;
            int new_y = pow(t_jump - sqrt(max_height),2) - max_height + floor_level - size_y; 

            if (crds.y() >= new_y)
            {
                crds.y() = new_y;
                t_jump++;
            }
            else // on est arrivé en haut du saut -> mtn chute
            {
                falling = 0;
            }
        }

        if (falling == -1) // Chute
        {
            int new_y = pow(t_jump,2) + jump_height; 

            if (new_y + size_y <= floor_level)
            {
                crds.y() = new_y;
                t_jump++;
            }
            else
            {
                crds.y() = crds_y_init;
                t_jump = 0;
                jumping = false;
                jump_height = 0;
                falling = 1;
                flushEvents();
            }
        }

        if (falling == 0) // début de la chute, on récupère la hauteur du saut pour change l'eq
        {
            falling = -1;
            jump_height = crds.y();
            t_jump = 0;
        } 
    } 
}

void Personnage::setFalling(int f)
{
    falling = f;
}

int Personnage::getFalling() const
{
    return falling;
}

bool Personnage::is_jumping() const
{
    return jumping;
}

void Personnage::walk()
{
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
