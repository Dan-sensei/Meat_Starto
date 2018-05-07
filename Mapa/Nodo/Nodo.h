/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nodo.h
 * Author: dan
 *
 * Created on 11 de abril de 2018, 3:33
 */

#ifndef NODO_H
#define NODO_H

#include <array>
#include <vector>

#include "NPCs/NPC.h"
#include "../../Player.h"
#include "Minijuegos/Minijuego.h"
#include "Minijuegos/goingUp.h"

class Nodo {
private:
    struct checkPoint{
        renderEngine::rRectangleShape shape;
        bool active;
    };
    struct power{
        int id = 0;
        renderEngine::rSprite sprite;
    };
public:

    Nodo();
    Nodo(const Nodo& orig);
    virtual ~Nodo();
    
    void addTile(int id, int x, int y);
    void addGround(std::vector<std::array<int, 2>> coords);
    void addxPlotato(int x_, int y_, int x_min, int x_max);
    void addSkull(int x_, int y_, int x_min, int x_max, int y_min, int y_max);
    void addPower(int id, int xMin, int xMax, int y_);
    void addSuperiorLayer(std::vector<renderEngine::rSprite> layer);
    void addLight(int x_, int y_);
    Minijuego* addMinigame(int type, int x, int y, int width, int height, std::vector<int> IDs_mininodo);
    
    //Eventos
    void checkColisionsPinchos(Player* ready);

    void setSpriteSheet(std::string path);
    void setRectVector(std::vector<renderEngine::rIntRect> rect_);
    void setPop(int i);
    int getPop();
    
    virtual void update();
    void preState();
    void newState();
    
    void draw(float tick_, renderEngine::rIntRect limit, int min, int max);
    void drawSuperiorLayer(renderEngine::rIntRect limit);
    void miniDraw(float tick_);
    
private:
    physicsEngine::type* t;
    
    std::vector<renderEngine::rIntRect> tileRect;
    renderEngine::rTexture spritesheet;
    
    // Objetos que contiene el nodo
    std::vector<NPC*> npcs;
    std::vector<pBody> ground;
    std::vector<renderEngine::rRectangleShape> pinchos;
    std::vector<renderEngine::rSprite> v_esprait;
    std::vector<renderEngine::rSprite> LIGHTS;
    std::vector< std::vector<renderEngine::rSprite> > superiorLayer;
    Minijuego* minijuego;
    
    std::vector<renderEngine::rRectangleShape> debug;

    typedef void (Player::*pFunc)(void);
    pFunc array_funciones[7];
    
    renderEngine::rImage img_powers;
    std::vector<power> powers;
    int aux_pop;
    
};

#endif /* NODO_H */

