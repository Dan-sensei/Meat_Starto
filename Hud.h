/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hud.h
 * Author: alba
 *
 * Created on 4 de abril de 2018, 13:10
 */

#ifndef HUD_H
#define HUD_H

#include <iostream>
#include "renderEngine/renderEngine.h"
#include "Player.h"


class Hud {
public:
    Hud(std::vector<Player*> jugadores);
    Hud(const Hud& orig);
    virtual ~Hud();

    void render();
    void cambiarHud(Player* player);
   // void cambiarHud2(Player* player);
    
    
private:
    renderEngine::rFont font;
    renderEngine::rText menu[3];
    renderEngine::rSprite hudsprite;
    std::vector<Player*> players;
    renderEngine::rSprite cuadrado;

    
    float width;
    float height;
    
    float posx;
    float posy;
    
    renderEngine *sfml;
    
};

#endif /* HUD_H */

