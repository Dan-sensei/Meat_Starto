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


class Nodo;

class goingUp : public Minijuego {
public:
    goingUp(int x, int y, int width, int height, std::vector<int> IDs_mininodo);
    goingUp(const goingUp& orig);
    virtual ~goingUp();
    
    void update();
    void draw(float tick_);
    
    void setEndArea(float x, float y, float width, float height);
    bool hasStarted();
    std::list<Nodo>* getAscensionList();
    
private:
    
    bool BEGIN;
    bool END;
    float minX, maxX;
    renderEngine::rRectangleShape initArea;
    renderEngine::rRectangleShape endArea;
    
    std::vector<int> IDs;
    std::list<Nodo> ascension;
};

#endif /* GOINGUP_H */

