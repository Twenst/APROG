#include <Imagine/Graphics.h>
using namespace Imagine;
#include <Imagine/Images.h>
using namespace Imagine;
#include <iostream>
#include <fstream>
#include <string>

//---Constantes---//
#include "constantes.h"

//---Prototypes---//
#include "personnage.h"
#include "affichage.h"
#include "objets.h"
float minf(float a, float b);
void load_jumping(Personnage & player,Event e);
void cinematic(Personnage& player,Image<AlphaColor> grass_textures[nb_grass],Image<AlphaColor> dirt_textures[nb_dirt], Image<AlphaColor> sky_textures[nb_sky],std::string score);

//---Main---//
int main(int argc, char** argv)
{
    //Affichage score
    std::ifstream fileScoreRead(score_path);
    if (!fileScoreRead.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier de lecture du score"<< std::endl;
        return 1;
    }
    std::string Score;
    fileScoreRead >> Score;
    fileScoreRead.close();




    openWindow(w,h,"Swolling");
    Partie partie;
    Personnage player;
    int nbr_obstacle = partie.get_nbr_obstacle();
    Obstacle* obstacle = new Obstacle[nbr_obstacle];
    float spacebar_timer = 1.5;
    int type_scrolling = 0;
    Event e;

    Image<AlphaColor> grass_textures[nb_grass], dirt_textures[nb_dirt], sky_textures[nb_sky];
	load_textures(grass_textures,dirt_textures,sky_textures);
    Image<AlphaColor> left[2], right[2], up[2], down[2];
    load_arrow(left,right,up,down);
    Image<AlphaColor> glow_ul[nb_glow], glow_dl[nb_glow], glow_ur[nb_glow], glow_dr[nb_glow];
    load_glow(glow_ul, glow_dl, glow_ur, glow_dr);

    cinematic(player,grass_textures,dirt_textures,sky_textures,Score);

    while(player.getHp() > 0)
    {
        getEvent(0,e);
        player.update_jump();
        player.update_walk();
        player.update_dash();
        player.update_status();
        //player.update_color(spacebar_timer);
        partie.Timer ++;

        noRefreshBegin();
        
        clearWindow();
        draw_background(grass_textures,dirt_textures,sky_textures);
        draw_hp(player.getHp());
        draw_timer(partie.Timer);
        draw_score(Score);
        draw_scrolling(type_scrolling,left,right,up,down);
        draw_glowing(player,glow_ul, glow_dl, glow_ur, glow_dr);
        player.draw(partie.Timer);

        noRefreshEnd();

        // JOUEUR :
        load_jumping(player,e);
        player.walk(e);
        player.dash(e);

        // OBSTACLES :
        bool outOfBounds = true;
        for(int i = 0 ; i<nbr_obstacle;i++)
        {
            if(obstacle[i].outOfBounds() == false)
            {
                outOfBounds= false;
            }
        }
        if(outOfBounds)
        {
            delete[] obstacle;
            nbr_obstacle = partie.get_nbr_obstacle();
            obstacle = new Obstacle[nbr_obstacle];
            partie.init(obstacle);
            type_scrolling = partie.get_scrolling_type();


        }
        for(int i = 0 ; i<nbr_obstacle;i++)
        {
            obstacle[i].move(type_scrolling);
            obstacle[i].draw();

        }

        //Le joueur se fait touché
        for (int i = 0; i < nbr_obstacle; ++i)
        {
            player.getHit(obstacle[i]);
        }

        //Changement de scrolling quand le timer atteint 1000
        if(partie.Timer % 70 == 0)
        {
            if(partie.Timer% 1000 == 0)
            {
                partie.update_scrolling(4);
            }
            else
            {
                partie.update_scrolling(rand()%4) ;
            }
        }
        
        milliSleep(5);
    }
    delete[] obstacle;
    if(partie.Timer > std::stoi(Score))
    {
        std::ofstream fileScoreWrite(score_path);
        if (!fileScoreWrite.is_open()) {
            std::cerr << "Erreur lors de l'ouverture du fichier de modification du score" << std::endl;
            return 1;
        }

        fileScoreWrite << partie.Timer << std::endl;
        fileScoreWrite.close();
    }

    endGraphics();
    return 0;
}

//---Cinematique---//
void cinematic(Personnage& player,Image<AlphaColor> grass_textures[nb_grass],Image<AlphaColor> dirt_textures[nb_dirt], Image<AlphaColor> sky_textures[nb_sky],std::string score)
{
    int cinematic_lenght = 100;
    int cinematic_speed = w/cinematic_lenght;
    int crd = 0;
    for(int i = 0 ; i < cinematic_lenght ; i++)
    {
        crd += cinematic_speed;
        player.setCoords(crd,crds_y_init);

        noRefreshBegin();

        draw_background(grass_textures,dirt_textures,sky_textures);
        drawString(w/2 - 690/2,h/5,"SWOLLING",RED,50,0,false,true); //ON pourra prendre des vrai png pour les textes
        if(i < cinematic_lenght /2)
        {

            drawString(w/2 - 150,h/3,"De retour...",BLACK,20,0,false,true);

        }
        else
        {
             drawString(w/2 - 760/2,h/3,"Déjà " + score +" mètres explorés...",BLACK,20,0,false,true);
        }
        player.draw(0);

        noRefreshEnd();
        milliSleep(5);
    }
    player.setCoords(crds_x_init,crds_y_init);

}

//---Fonctions---//
float minf(float a, float b)
{
    return (a < b) ? a : b;
}

void load_jumping(Personnage & player,Event e)
{
    if (not player.is_jumping())
    {
        if (e.type == EVT_KEY_ON and e.key == KEY_UP)
        {
            player.setFalling(1);
            player.jump();
        }
    }
    else
    {
        if (e.type == EVT_KEY_OFF and e.key == KEY_UP and player.getFalling() == 1)
        {
            player.setFalling(0);
        }
    }
}
