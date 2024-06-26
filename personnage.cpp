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
    max_hp = 5;
    invincible = false;
    invincible_count = 0;
    invincible_duration = 40;
    light_force = 16;
    facing_right = true;
    crouching = false;
    bonus_duration = 800;
    bonus_count = 0;
    bonus = false;
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
    return hp;
}

int Personnage::getMaxHp() const
{
    return max_hp;
}

void Personnage::jump()
{
    if(not crouching)
    {
        if (not jumping)
        {
            jumping = true;
            t_jump = 0;
        }
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

void Personnage::set_facing(int side)
{
    // side = 0 : droite, side = 1 : gauche
    if(side == 0)
    {
        facing_right = true;
    }
    else
    {
        facing_right = false;
    }
}

bool Personnage::is_jumping() const
{
    return jumping;
}

void Personnage::walk(Event e)
{
    if ((e.type == EVT_KEY_ON) and (e.key == KEY_RIGHT))
    {
        speed = max_speed;
        facing_right = true;
    }
    else if ((e.type == EVT_KEY_ON) and (e.key == KEY_LEFT))
    {
        speed = -max_speed;
        facing_right = false;
    }
    else if (e.type == EVT_KEY_OFF and (e.key == KEY_LEFT or e.key == KEY_RIGHT))
    {
        speed = 0;
    }
}

void Personnage::crouch(Event e)
{
    if(not jumping)
    {
        if ((e.type == EVT_KEY_ON) and (e.key == KEY_DOWN))
        {
            crouching = true;
            size = Coord(size_x,size_y/2);
            crds = Coord(getPos().x(),crds_y_init + size_y/2);
        }
        else if (e.type == EVT_KEY_OFF and e.key == KEY_DOWN)
        {
            size = Coord(size_x,size_y);
            crds = Coord(getPos().x(),crds_y_init);
            crouching = false;
        }
    }
}

void Personnage::update_walk()
{
    crds.x() += speed*dash_speed;
    if (crds.x() < 0)
    {
        crds.x() = 0;
    }
    if (crds.x() > w - size_x)
    {
        crds.x() = w - size_x;
    }
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


    if (invincible and bonus_value != 3) //invincibilité
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
    else if(bonus) //bonus
    {
        if(bonus_count == bonus_duration)
        {

            bonus = false;
            bonus_count = 0;
           // if (bonus_value == 2)
            //{
            //    max_speed -= 15;
            //}
            if(bonus_value ==3)
            {
                invincible = false;
            }
            bonus_value = 0;
        }
        else
        {
            bonus_count ++;
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
    obstacle.set_visibility(false);
    if(obstacle.getBonusType() == 1)//Coeur
    {
        addHP();
        bonus_value = 1;
    }
    if(obstacle.getBonusType() == 2)//Vitesse (lumière désormais
    {
        bonus = true;
        //max_speed += 15;
        bonus_value = 2;
        setLighForce(16);
    }
    if(obstacle.getBonusType() == 3)//Invulnérabilité
    {
        bonus = true;
        bonus_value = 3;
        invincible = true;
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
    if(hp < max_hp)
    {
        hp ++;
    }
}

void Personnage::setSpeed(int newSpeed)
{
    speed = newSpeed;
}

Coord Personnage::getPos() const
{
    return crds;
}

Coord Personnage::getSize() const
{
    return size;
}

int Personnage::getSpeed() const
{
    return speed;
}

Coord Personnage::getCenter() const
{
    return crds + size/2;
}

int Personnage::getLighForce() const
{
    return light_force;
}

void Personnage::setLighForce(int light_lvl)
{
    light_force = light_lvl;   
}

bool Personnage::is_crouching() const
{
    return crouching;
}

bool Personnage::is_facing_right() const
{
    return facing_right;
}

void Personnage::set_crouching(bool b)
{
    crouching = b;
}

bool Personnage::is_invicible() const
{
    return invincible;
}

void Personnage::set_jumping(bool b)
{
    jumping = b;
}
