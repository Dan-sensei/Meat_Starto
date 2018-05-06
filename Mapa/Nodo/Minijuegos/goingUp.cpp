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
#include "../../../Juego.h"

#define OFFSET 70*20

goingUp::goingUp(int x, int y, int width, int height, std::vector<int> IDs_mininodo) {
    initArea.setPosition(x+OFFSET, y);
    initArea.setSize(width, height);
    initArea.setOutlineThickness(2.f);
    initArea.setOutlineColor('r');
    initArea.setFillColor('t');
    std::cout << x << ", " << y << std::endl;
    BEGIN = false;
    END = false;
    endArea.setOutlineThickness(2.f);
    endArea.setOutlineColor('r');
    
    for(int i = 0; i < IDs_mininodo.size(); ++i)
        IDs.push_back(IDs_mininodo[i]);
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
            // Inicio el juego
            if(starter == players->size()){
                Mapa::Instance().changeSpriteSheet("tiles_definitivo/tilesheet.png");
                int x = initArea.getPosition()[0]-OFFSET;
                int y = initArea.getPosition()[1];
                y += initArea.getSize()[1];
                y -= 70*2;      //Quiero que se empiecen a generar 2 por encima de la plataforma
                BEGIN = true;
                Juego::Instance().switchCameradirection();
                Mapa::Instance().changeDirection(1);
                for(int i = 0; i < IDs.size(); i++){
                    Mapa::Instance().CargaNodo(ascension, Mapa::Instance().getMINI(IDs[i]), x, y);
                }
                y += 14*70;
                
                Mapa::Instance().CargaNodo(ascension, Mapa::Instance().getMINI(8), x, y); // Último
                setEndArea(x, y, 43*70, 24*70);
                Mapa::Instance().changeDirection(0);
                Mapa::Instance().changeSpriteSheet("tiles_definitivo/tilesheet2.png");
            }
        }
        else{
            for(int i = 0; i < players->size(); i++){
                Player* ready = (*players)[i];
                if(ready->getSprite().intersects(endArea)){
                    Juego::Instance().switchCameradirection();
                    END = true;
                    std::cout << "VIEW CENTER: " << renderEngine::Instance().getViewCenter()[0] << ", " << renderEngine::Instance().getViewCenter()[1] << std::endl;
                }
            }
        }
    }
    
}

void goingUp::draw(float tick_) {
    //initArea.draw();
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
