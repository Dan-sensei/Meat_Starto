/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NPC.h
 * Author: dan
 *
 * Created on 9 de abril de 2018, 8:22
 */

#ifndef NPC_H
#define NPC_H


#include "math.h"
#include "../../../renderEngine/renderEngine.h"
#include "../../../physicsEngine/physicsEngine.h"

class NPC {
public:
    NPC();
    NPC(const NPC& orig);
    virtual ~NPC();
    
    virtual void update();
    void draw();
    
    void preState();
    void newState();
    void interpola(float tick_);
    
    int getXPosition();
    int getYPosition();
    bool isAlive();
    
protected:
    int hp;
    renderEngine::rSprite sprite;
    pBody body;
    
    struct state{
        float x;     // Posicion X
        float y;     // Posicion Y
        float r;     // Rotacion
    };
    state previous;
    state actual;
    
    bool alive;

private:
    

};

#endif /* NPC_H */

