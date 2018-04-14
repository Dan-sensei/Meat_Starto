/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Skull.h
 * Author: dan
 *
 * Created on 14 de abril de 2018, 12:05
 */

#ifndef SKULL_H
#define SKULL_H

#include "NPC.h"


class Skull : public NPC{
public:
    Skull(int x_, int y_, int x_b, int x_e, int y_b, int y_e);
    Skull(const Skull& orig);
    virtual ~Skull();
    
    void update();
    
    
private:
    void recalcula();
    
    physicsEngine::type* t;
    int x_min;;
    int x_max;
    int y_min;
    int y_max;
    int targetX;
    int targetY;

};

#endif /* SKULL_H */

