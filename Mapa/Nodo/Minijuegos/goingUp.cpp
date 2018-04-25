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
            // Inicio el juego
            if(starter == players->size()){
                int x = initArea.getPosition()[0];
                int y = initArea.getPosition()[1];
                y += initArea.getSize()[1];
                y -= 70*2;      //Quiero que se empiecen a generar 2 por encima de la plataforma
                BEGIN = true;
                Juego::Instance().switchCameradirection();
                std::string path;
                Mapa::Instance().changeDirection(1);
                for(int i = 0; i < 9; i++){
                    path = "tiles_definitivo/nodos/Up/Mininode_";
                    int rand = physicsEngine::Instance().genIntRandom(1, 8);
                    path = path.operator +=( std::to_string(rand) );
                    path = path.operator +=(".tmx");

                    //Mapa::Instance().LeeNodoAux(ascension, path, x, y);
                }
                path = "tiles_definitivo/nodos/Up/Mininode_9.tmx";
                //Mapa::Instance().LeeNodoAux(ascension, path, x, y);
                setEndArea(x, y, 43*70, 19*70);
                Mapa::Instance().changeDirection(0);
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
