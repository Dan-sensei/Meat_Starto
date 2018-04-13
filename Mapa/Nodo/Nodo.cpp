/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nodo.cpp
 * Author: dan
 * 
 * Created on 11 de abril de 2018, 3:33
 */

#include "Nodo.h"
#include "NPCs/xPlotato.h"


Nodo::Nodo(std::string sheet) {    
    tile.setTexture(AssetManager::GetTexture(sheet));
}

Nodo::Nodo(const Nodo& orig) {

    for(int i = 0; i < orig.tilePosition.size(); i++){
        tilePosition.push_back(orig.tilePosition[i]);
        tileId.push_back(orig.tileId[i]);
    }
    
    for(int i= 0; i < orig.tileRect.size(); i++)
        tileRect.push_back(orig.tileRect[i]);
    
    for(int i=0; i< orig.ground.size(); i++)
        ground.push_back(orig.ground[i]);
    
    for(int i = 0; i < orig.npcs.size(); i++)
        npcs.push_back(orig.npcs[i]);
    
    aux_pop = orig.aux_pop;
    tile = orig.tile;
}

Nodo::~Nodo() {
}


void Nodo::setPop(int i){
    aux_pop = i;
}

int Nodo::getPop(){
    return aux_pop;
}

void Nodo::setRectVector(std::vector<renderEngine::rIntRect> rect_){
    tileRect = rect_;
}

int Nodo::getSize(){
    return tileId.size();
}


void Nodo::addTile(int id, int x, int y){
    tileId.push_back(id);
    tilePosition.push_back(std::array<int, 2>{x, y});
}

void Nodo::addGround(std::vector<std::array<float,2> > coords){
    physicsEngine* world;
    
    t = new physicsEngine::type;
    t->id = 1;
    t->data = this;
    
    ground.push_back(world->Instance().createGround(coords, t));
}

void Nodo::addNPC(int x_, int y_, int x_min, int x_max) {
    npcs.push_back(new xPlotato(x_, y_, x_min, x_max));
}



void Nodo::draw(float tick_, renderEngine::rIntRect limit, int min, int max){

    for(int i = 0; i < tileId.size(); i++){
        if(limit.contains(tilePosition[i][0], tilePosition[i][1])){
            tile.setPosition(tilePosition[i][0], tilePosition[i][1]);
            tile.setTextureRect(tileRect[tileId[i]]);
            tile.draw();
        }
    }   
    
    //------------|  ENEMIGOS  |------------//
    for(int j = 0; j < npcs.size(); j++)
        if(npcs[j]->getXPosition() > min && npcs[j]->getXPosition() < max){
            npcs[j]->interpola(tick_);
            npcs[j]->draw();
        }
    
}

void Nodo::update(){
    for(int i = 0; i < npcs.size(); i++){
        npcs[i]->update();
    }
}

void Nodo::preState(){
    for(int i = 0; i < npcs.size(); i++){
        npcs[i]->preState();
    }
}

void Nodo::newState(){
    for(int i = 0; i < npcs.size(); i++){
        npcs[i]->newState();
    }
}