#include "objets.h"
#include "constantes.h"
#include <math.h>

Personnage::Personnage()
{
    size = Coord(size_x,size_y);
    crds = Coord(crds_x_init,crds_y_init);
    clr = BLUE;
    hp = 3;
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

void Personnage::jump(int force)
{
    if (not jumping)
    {
        jumping = true;
        jump_height = (floor_level - size_y) * float(force/max_jump_force);
        t_jump = 0;
    }
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
            jumping = 0;
            jump_height = 0;
        }
    } 
}