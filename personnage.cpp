#include "constantes.h"
#include "personnage.h"
#include <math.h>
#include <random>

Personnage::Personnage()
{
    size = Coord(size_x,size_y);
    crds = Coord(0,crds_y_init);
    clr = BLUE;
    hp = 5;
    jumping = false;
    t_jump = 0;
    jump_height = 0;
    falling = 1;
    max_height = (floor_level - size_y)/2;
    speed = 0;
    dash_speed = 1.;
}

void Personnage::draw(int Timer) const
{
    // A FAIRE: AFFICHER UN SPRITE A LA PLACE DE LA COULEUR
    if(invincible)
    {
        if(Timer%2 == 0)
        {
            fillRect(crds.x(),crds.y(),size.x(),size.y(),clr);
        }
    }
    else
    {
        fillRect(crds.x(),crds.y(),size.x(),size.y(),clr);
    }

}

int Personnage::getHp() const
{
    if(hp < max_hp)
    {
        return hp;
    }
}

void Personnage::jump()
{
    if (not jumping)
    {
        jumping = true;
        t_jump = 0;
    }
}

void Personnage::update_jump() //eq saut: y = (t - sqrt(max_height))² - max_height
{
    // falling = 1 -> montée, falling = 0 -> début de la chute, falling = -1 -> chute
    if (jumping)
    {
        if (falling == 1) // Monte
        {
            int new_y = pow(t_jump/jump_lenght - sqrt(max_height),2) - max_height + floor_level - size_y;

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

void Personnage::walk(Event e)
{
    if ((e.type == EVT_KEY_ON) and (e.key == KEY_RIGHT))
    {
        speed = 10;
    }
    else if ((e.type == EVT_KEY_ON) and (e.key == KEY_LEFT))
    {
        speed = -10;
    }
    else if (e.type == EVT_KEY_OFF and (e.key == KEY_LEFT or e.key == KEY_RIGHT))
    {
        speed = 0;
    }
}

void Personnage::update_walk()
{
    crds.x() += speed*dash_speed;
}

void Personnage::dash(Event e)
{
    if (e.type == EVT_KEY_ON and e.key == ' ' and dash_speed <= 1.1)
    {
        dash_speed = 4.;
    }
}

void Personnage::update_dash()
{
    if (dash_speed > 1.2)
    {
        dash_speed -= .2;
    }
    else
    {
        dash_speed = 1.;
    }
}

void Personnage::setCoords(int x,int y)
{
    crds = Coord(x,y);

}

void Personnage::update_status()
{
    //invincibilité
    if(invincible)
    {
        if(invincible_count == invincible_duration)
        {
            invincible = false;
            invincible_count = 0;
        }
        else
        {
            invincible_count ++;
        }

    }

}


void Personnage::getHit(Obstacle& obstacle)
{
    if(obstacle.alreadyHit == false)
    {
        if(crds.x() + size.x() < obstacle.getCoord().x() or crds.y()+size.y() < obstacle.getCoord().y()
            or crds.x() > obstacle.getCoord().x() + obstacle.getSize().x() or crds.y()> obstacle.getCoord().y()+ obstacle.getSize().y())
        {

        }
        else
        {
            obstacle.alreadyHit = true;
            if(obstacle.getType() == 0)
            {
                looseHP();
            }
            else
            {
                getBonus(obstacle);
            }

        }
    }
}

void Personnage::getBonus(Obstacle& obstacle)
{
    obstacle.erase();
    if(obstacle.getType() == 1)
    {
        addHP();
    }
}

void Personnage::looseHP()
{
    if(invincible == false)
    {
        hp --;
        invincible = true;
    }

}

void Personnage::addHP()
{
    hp ++;
}

Coord Personnage::getPos() const
{
    return crds;
}

Coord Personnage::getSize() const
{
    return size;
}

Obstacle::Obstacle()
{
    srand((unsigned int) time(0));
    size = Coord(35,40 + rand()%200);

    clr = BLACK;
    crds = Coord(w,floor_level - size.y());
    type = 0;
}

