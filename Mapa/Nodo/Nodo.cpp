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
    tile.setTexture(AssetManager::GetTexture("tilesheet.png"));
}

Nodo::Nodo(const Nodo& orig) {
}

Nodo::~Nodo() {
}

void Nodo::addTile(int id, int x, int y){

    tileId.push_back(id);
    tilePosition.push_back(std::array<int, 2>{x, y});
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
            tile.setTexture(AssetManager::GetTexture("tilesheet.png"));
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