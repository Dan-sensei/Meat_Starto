/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   goingUp.h
 * Author: dan
 *
 * Created on 22 de abril de 2018, 20:02
 */

#ifndef GOINGUP_H
#define GOINGUP_H

#include "renderEngine/renderEngine.h"
#include "Minijuego.h"

class goingUp : public Minijuego {
public:
    goingUp(int x, int y, int width, int height);
    goingUp(const goingUp& orig);
    virtual ~goingUp();
    
    void update();
    
private:
    float minX, maxX;
    renderEngine::rRectangleShape initArea;
};

#endif /* GOINGUP_H */

