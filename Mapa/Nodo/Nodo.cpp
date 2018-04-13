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
    
    aux_pop = orig.aux_pop;
    tile = orig.tile;
}

Nodo::~Nodo() {
}

void Nodo::addTile(int id, int x, int y){
    tileId.push_back(id);
    tilePosition.push_back(std::array<int, 2>{x, y});
}
void Nodo::addGround(std::vector<std::array<float,2> > coords){
    ground.push_back(Ground(coords));
}


void Nodo::setPop(int i){
    aux_pop = i;
}

int Nodo::getPop(){
    return aux_pop;
}

void Nodo::draw(renderEngine::rIntRect limit){

    for(int i = 0; i < tileId.size(); i++){
        if(limit.contains(tilePosition[i][0], tilePosition[i][1])){
            tile.setPosition(tilePosition[i][0], tilePosition[i][1]);
            tile.setTextureRect(tileRect[tileId[i]]);
            tile.draw();
        }
    }
    
}

void Nodo::setRectVector(std::vector<renderEngine::rIntRect> rect_){
    tileRect = rect_;
}

int Nodo::getSize(){
    return tileId.size();
}