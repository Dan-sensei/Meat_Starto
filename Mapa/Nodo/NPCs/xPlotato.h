/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   xPlotato.h
 * Author: dan
 *
 * Created on 9 de abril de 2018, 8:27
 */

#ifndef XPLOTATO_H
#define XPLOTATO_H

#include "NPC.h"
#include "../../../renderEngine/rSoundBuffer.h"
#include "../../../renderEngine/rSound.h"

class xPlotato : public NPC {
public:
    xPlotato(int x_, int y_, int x_b, int x_e);
    xPlotato(const xPlotato& orig);
    virtual ~xPlotato();
    
    void update();
    void salta(int s);
    
private:
    void persigue();
    void direccion();
    
    bool xplotar;
    int pj;
    renderEngine::rClock xclock;
    renderEngine::rClock animationClock;
    Animator animator;
    
    physicsEngine::type* t;
    int x_begin;
    int x_end;
    int target;
    
    bool readyToDie;

    rSound xPlosion1;
    rSound xPlosion2;
};

#endif /* XPLOTATO_H */

