/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   goingUp.cpp
 * Author: dan
 * 
 * Created on 22 de abril de 2018, 20:02
 */

#include "goingUp.h"
#include "Juego.h"

goingUp::goingUp(int x, int y, int width, int height) {
    initArea.setPosition(x, y);
    initArea.setSize(width, height);
    BEGIN = false;
    END = false;
    endArea.setOutlineThickness(2.f);
    endArea.setOutlineColor('r');
}


goingUp::goingUp(const goingUp& orig) {
}

goingUp::~goingUp() {
}

void goingUp::update() {
    std::vector<Player*>* players = Juego::Instance().getPlayers();
    if(!END){  
        if(!BEGIN){
            int starter = 0;
            for(int i = 0; i < players->size(); i++){
                Player* ready = (*players)[i];
                if(ready->getSprite().intersects(initArea))
                    starter++;

            }
            if(starter == players->size()){
                BEGIN = true;
                Juego::Instance().switchCameradirection();
            }
        }
        else{
            for(int i = 0; i < players->size(); i++){
                Player* ready = (*players)[i];
                if(ready->getSprite().intersects(endArea)){
                    Juego::Instance().switchCameradirection();
                    END = true;
                }
            }
        }
    }
    //std::cout << "UEEEEE" << std::endl;
}

void goingUp::draw(float tick_) {
    
    for(std::list<Nodo>::iterator it=ascension.begin(); it!=ascension.end(); ++it){
        (*it).miniDraw(tick_);
    }
    endArea.draw();
}



std::list<Nodo>* goingUp::getAscensionList() {
    return &ascension;
}

bool goingUp::hasStarted() {
    return BEGIN;
}

void goingUp::setEndArea(float x, float y, float width, float height) {
    endArea.setPosition(x, y);
    endArea.setSize(width, height);
    endArea.setFillColor('t');
}
