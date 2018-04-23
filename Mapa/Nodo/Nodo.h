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
#include "Ground.h"
#include "../../Player.h"
#include "Minijuegos/Minijuego.h"

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

    Nodo(std::string sheet);
    Nodo(const Nodo& orig);
    virtual ~Nodo();
    
    void addTile(int id, int x, int y);
    void addGround(std::vector<std::array<float, 2>> coords);
    void addxPlotato(int x_, int y_, int x_min, int x_max);
    void addSkull(int x_, int y_, int x_min, int x_max, int y_min, int y_max);
    void addPower(int id, int xMin, int xMax, int y_);
    void addCheckPoint(int x, int y, int width, int height);
    void addMinigame(int type, int x, int y, int width, int height);
    
    
    //Eventos
    void checkColisionsPinchos(Player* ready);
    
    void setRectVector(std::vector<renderEngine::rIntRect> rect_);
    void setPop(int i);
    int getPop();
    void setPreviousCheckPoint(Nodo::checkPoint prev);
    Nodo::checkPoint getLastCheckPoint();
    
    virtual void update();
    void preState();
    void newState();
    
    void draw(float tick_, renderEngine::rIntRect limit, int min, int max);
    
private:
    
    renderEngine::rSprite tile;
    
    physicsEngine::type* t;
    
    std::vector<renderEngine::rIntRect> tileRect;
    
    // Objetos que contiene el nodo
    std::vector<NPC*> npcs;
    std::vector<pBody> ground;
    std::vector<renderEngine::rRectangleShape> pinchos;
    std::vector<renderEngine::rSprite> v_esprait;
    float maxXCheckPoint;
    std::list<checkPoint> checkpoints;
    
    Minijuego* minijuego;
    
    typedef void (Player::*pFunc)(void);
    pFunc array_funciones[4];
    
    
    
    std::vector<power> powers;
    
    int aux_pop;
    
};

#endif /* NODO_H */

