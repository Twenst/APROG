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
void start_cinematic(Personnage& player,Img grass_textures[nb_grass],Img dirt_textures[nb_dirt], Img sky_textures[nb_sky],std::string score);
void start_cinematic2(Personnage& player, Img player_right[10], Img player_left[10], Img cave, Img background, Img shadows[nb_shadow], std::string score);
void end_cinematic(Personnage player, Img cave, Img background, Img shadows[nb_shadow], Img player_right[5], Img player_left[5], int Timer);

//---Main---//
int main(int argc, char** argv)
{
    //Affichage score
    std::ifstream fileScoreRead(stringSrcPath(score_path));
    if (!fileScoreRead.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier de lecture du score"<< std::endl;
        return 1;
    }
    std::string Score;
    fileScoreRead >> Score;
    fileScoreRead.close();



    srand(time(NULL));
    openWindow(w,h,"CaveScroll");
    Partie partie;
    Personnage player;
    int nbr_obstacle = partie.get_nbr_obstacle();
    Obstacle* obstacle = new Obstacle[nbr_obstacle];
    float spacebar_timer = 1.5;
    int type_scrolling = 0;
    Event e;

    // Chargement des textures
    //Img grass_textures[nb_grass], dirt_textures[nb_dirt], sky_textures[nb_sky];
	//load_textures(grass_textures,dirt_textures,sky_textures);
    Img left[2], right[2], up[2], down[2];
    load_arrow(left,right,up,down);
    Img cave; load_cave(cave);
    Img background; load_background(background);
    Img shadows[nb_shadow]; load_shadow(shadows);
    Img heart[2]; load_heart(heart);
    Img player_right[10], player_left[10]; load_charac(player_right, player_left);
    Img shield_bonus;Img light_bonus;Img heart_bonus;load_bonus(shield_bonus,light_bonus,heart_bonus);

    start_cinematic2(player,player_right, player_left,cave,background,shadows,Score);
    player.setLighForce(lightforce_init);

    while(player.getHp() > 0)
    {
        getEvent(0,e);
        player.update_jump();
        player.update_walk();
        player.update_dash();
        player.update_status();


        partie.Timer += 1;

        // AFFICHAGE
        noRefreshBegin();
        
        clearWindow();
        draw_background(background);
        draw_cave(cave,partie.Timer);
        draw_shadow(shadows, player);
        //draw_hp(player.getHp());
        draw_heart(heart, player);
        draw_timer(partie.Timer);
        draw_score(Score);
        draw_scrolling(type_scrolling,left,right,up,down);
        //player.draw(partie.Timer);
        draw_charac(player_right, player_left, player, partie.Timer);

        noRefreshEnd();

        // JOUEUR :
        load_jumping(player,e);
        player.walk(e);
        player.dash(e);
        player.crouch(e);
        if(partie.Timer%100 ==0)
        {
            player.setLighForce(player.getLighForce() - 1);
        }
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
            obstacle[i].draw(shield_bonus,light_bonus,heart_bonus);

        }

        //Le joueur se fait touché
        for (int i = 0; i < nbr_obstacle; ++i)
        {
            player.getHit(obstacle[i]);
        }

        //Changement de scrolling quand le timer atteint 1000
        if(partie.Timer % 70 == 0)
        {
            if(partie.Timer% 100 == 0)
            {
                partie.update_scrolling(4);//Bonus
            }
            else
            {
                partie.update_scrolling(rand()%4) ;//Scrolling d'obstacles
            }
        }
        
        milliSleep(msleep);
    }

    end_cinematic(player, cave, background, shadows, player_right, player_left, partie.Timer);

    delete[] obstacle;
    if(partie.Timer > std::stoi(Score))
    {
        std::ofstream fileScoreWrite(stringSrcPath(score_path));
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

void start_cinematic2(Personnage& player, Img player_right[5], Img player_left[5], Img cave, Img background, Img shadows[nb_shadow], std::string score)
{
    int crd = 0;
    int cinematic_lenght_1 = 80;
    int cinematic_lenght_2 = 50;
    int cinematic_speed_x = w/(cinematic_lenght_1*(5.6/4));
    int cinematic_speed_y = crds_y_init/(cinematic_lenght_2);
    int crdx = 0;int crdy = crds_y_init;
    int fall_lenght = 50;
    
    Img keyboard; load_keyboard(keyboard);
    Img startbackground; load_startback(startbackground);
    Img rock; load_rock(rock);
    Img click; load_click(click);

    for(int i = 0 ; i < cinematic_lenght_1 - 1; i++)
    {
        crdx += cinematic_speed_x;
        player.setCoords(crdx,crds_y_init);

        noRefreshBegin();
        clearWindow();

        draw_startback(startbackground);

        if(i < cinematic_lenght_1 /2)
        {

            drawString(w/2 - 150,h/3,"De retour...",BLACK,20,0,false,true);

        }
        else
        {
             drawString(w/2 - 760/2,h/3,"Déjà " + score +" mètres explorés...",BLACK,20,0,false,true);
        }
        draw_charac(player_right, player_left, player, 0);
        draw_rock(rock);

        noRefreshEnd();
        milliSleep(msleep);
    }
    //Attente avant de tomber
    for(int i = 0; i < fall_lenght;i++)
    {
        if(i > cinematic_lenght_1 /4)
        {
            noRefreshBegin();
            clearWindow();

            draw_startback(startbackground);
            // Pour ralentir le rafraichissement de la direction du personnage
            int k = i/7;
            player.set_facing(k%2);
            draw_charac(player_right, player_left, player, 0);
            draw_rock(rock);

            noRefreshEnd();
        }
        milliSleep(msleep);
    }

    //Deuxième partie : le personnage tombe
    for(int i = 0; i<cinematic_lenght_2;i++)
    {
        crdy += cinematic_speed_y;
        player.setCoords(crdx,crdy);
        noRefreshBegin();

        clearWindow();
        draw_startback(startbackground);



        draw_charac(player_right, player_left, player, 0);
        draw_rock(rock);

        noRefreshEnd();
        milliSleep(msleep);

    }
    //Affichage titre + touche

    // Fondu noir
    int fondu_duree = 50;
    AlphaColor noir(0,0,0,0);
    for (int i = 0; i < fondu_duree; i++)
    {
        noRefreshBegin();
        clearWindow();

        draw_startback(startbackground);
        noir.a() = 255 * i/fondu_duree;
        fillRect(0,0,w,h,noir);

        noRefreshEnd();
        milliSleep(msleep);
    }

    for (int i = 0; i < fondu_duree; i++)
    {
        noRefreshBegin();
        clearWindow();

        draw_background(background);
        draw_cave(cave,0);
        draw_shadow(shadows);
        noir.a() = 255 - 255 * i/fondu_duree;
        fillRect(0,0,w,h,noir);

        noRefreshEnd();
        milliSleep(msleep);
    }

    noRefreshBegin();

    clearWindow();

    draw_background(background);
    draw_cave(cave,0);
    draw_shadow(shadows);
    //drawString(w/2 - 760/2,h/3,"Scrolling (mettre vrai png)",BLACK,20,0,false,true);
    // TJRS A FAIRE, PEUT ETRE AFFICHER AVANT
    draw_click(click);
    draw_keyboard(keyboard);

    noRefreshEnd();

    anyClick();

    // chute du personnage par le haut
    player.setCoords(crds_x_init,0);
    player.setFalling(0);
    player.set_jumping(true);

    while(player.is_jumping())
    {
        player.update_jump();
        player.update_walk();
        player.update_dash();

        noRefreshBegin();
        
        clearWindow();
        draw_background(background);
        draw_cave(cave,0);
        draw_shadow(shadows, player);
        draw_charac(player_right, player_left, player, 0);


        noRefreshEnd();
        milliSleep(msleep);
    }

}

void end_cinematic(Personnage player, Img cave, Img background, Img shadows[nb_shadow], Img player_right[5], Img player_left[5], int Timers)
{
    Img gameover; load_gameover(gameover);
    int cinematic_lenght = 35;
    player.set_crouching(true);
    player.setCoords(player.getPos().x(),player.getPos().y() + size_y/2);

    for(int i = 0 ; i < cinematic_lenght ; i++)
    {
        noRefreshBegin();
        clearWindow();

        draw_background(background);
        draw_cave(cave,0);

        std::vector<int> radius;
	    for (int i = 2; i < 4; i++) radius.push_back(player.getLighForce()*i*fac);

	    std::vector<double> alphas(radius.size(), 0.75 + 0.25*i/cinematic_lenght);
	    Img shadow_mask = applyMaskCircle(shadows[rand()%nb_shadow],radius,player.getCenter() - size_y/4,alphas);
	    display(shadow_mask,0,0,false,fac);

        draw_timer(Timers);
        draw_charac(player_right, player_left, player, 0);

        noRefreshEnd();
        milliSleep(msleep);
    }
    noRefreshBegin();
    draw_gameover(gameover);
    draw_timer(Timers);
    noRefreshEnd();
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
