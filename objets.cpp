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
    if(type == 2 or type == 3)
    {
        nbr_obstacle = 6;
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
    max_height = (floor_level - size_y)/2;
    speed = 0;
    dash_speed = 1.;
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
    hp --;
}

void Personnage::addHP()
{
    hp ++;
}


Obstacle::Obstacle()
{
    srand((unsigned int) time(0));
    size = Coord(35,40 + rand()%200);

    clr = BLACK;
    crds = Coord(w,floor_level - size.y());
    type = 0;
}


void Obstacle::draw() const
{
    fillRect(crds.x(),crds.y(),size.x(),size.y(),clr);
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
    clr = BLACK;
    setType(0);
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
    if(scrollingType == 4)
    {
        //Bonus
        speed =  abs(speed)*1;
        size = Coord(35 + rand()%70,35);
        crds = Coord(w,h/2);
        clr = RED;
        setType(1);
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
int Obstacle::getType() const
{
    return type;
}

void Obstacle::setType(int new_type)
{
    type = new_type;
}

void Obstacle::erase()
{
    size = (0);
}
