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
#include "NPCs/Skull.h"
#include "Juego.h"


Nodo::Nodo(std::string sheet) {    
    tile.setTexture(AssetManager::GetTexture(sheet));
    
    array_funciones[0] = &Player::powerUpInmortalidad;
    array_funciones[1] = &Player::powerUpSpeed;
    array_funciones[2] = &Player::powerDownJump;
    array_funciones[3] = &Player::powerDownFreeze;
    
    
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
    
    for(int i = 0; i < orig.pinchos.size(); i++)
        pinchos.push_back(orig.pinchos[i]);
    
    aux_pop = orig.aux_pop;
    tile = orig.tile;
}

Nodo::~Nodo() {
    std::cout << "Borrando nodo..." << std::endl;
    for(int i = 0; i <npcs.size(); i++){
        delete npcs[i];
        npcs[i] = nullptr;
    }
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
    
    renderEngine::rSprite sprite;
    sprite.setTexture(AssetManager::GetTexture("tiles_definitivo/tilesheet.png"));
    sprite.setTextureRect(tileRect[id]);
    sprite.setPosition(x,y);
    
    v_esprait.push_back(sprite);
    
    if(id == 36 || id == 35 || id == 34 || id == 33){
        pinchos.emplace_back();
        pinchos.back().setSize(70,70);
        pinchos.back().setPosition(x,y);
        pinchos.back().setFillColor('r');
    }
}

void Nodo::addGround(std::vector<std::array<float,2> > coords){
    physicsEngine* world;
    
    t = new physicsEngine::type;
    t->id = 1;
    t->data = this;
    
    ground.push_back(world->Instance().createGround(coords, t));
}

void Nodo::addxPlotato(int x_, int y_, int x_min, int x_max) {
    npcs.push_back(new xPlotato(x_, y_, x_min, x_max));
}

void Nodo::addSkull(int x_, int y_, int x_min, int x_max, int y_min, int y_max){
    npcs.push_back(new Skull(x_, y_, x_min, x_max, y_min, y_max));
}

void Nodo::addPower(int id, int xMin, int xMax, int y_) {
    power p;
    p.id = id;
    
    std::string sprite[4];
    sprite[0] = "assets/powerUp.png";
    sprite[1] = "assets/powerUp.png";
    sprite[2] = "assets/powerDown.png";
    sprite[3] = "assets/powerDown.png";
    
    std::string target = sprite[id];
    
    int sizeY = AssetManager::GetTexture(target).getYSize();
    int sizeX = AssetManager::GetTexture(target).getXSize();
    int newX = physicsEngine::Instance().genIntRandom(xMin+sizeX+10, xMax-sizeX-10);
    
    p.sprite.setTexture(AssetManager::GetTexture(target));
    p.sprite.setOrigin(sizeY, sizeX);
    p.sprite.setPosition(newX, y_);
    powers.push_back(p);
   
}

void Nodo::draw(float tick_, renderEngine::rIntRect limit, int min, int max){

    for(int i = 0; i < tileId.size(); i++){
        if(limit.contains(v_esprait[i].getPosition()[0],v_esprait[i].getPosition()[1])){
            v_esprait[i].draw();
        }
            /*
        if(limit.contains(tilePosition[i][0], tilePosition[i][1])){
            tile.setPosition(tilePosition[i][0], tilePosition[i][1]);
            tile.setTextureRect(tileRect[tileId[i]]);
            tile.draw();
        }
             */
    }   
    
    //------------|  ENEMIGOS  |------------//
    for(int j = 0; j < npcs.size(); j++)
        if(npcs[j]->getXPosition() > min-250 && npcs[j]->getXPosition() < max+250){
            npcs[j]->interpola(tick_);
            npcs[j]->draw();
        }
    /*
    for(int i = 0; i < pinchos.size(); i++){
        pinchos[i].draw();
    }
    */
    
    for(int i = 0; i < powers.size(); i++)
        powers[i].sprite.draw();
}

void Nodo::update(){
    bool flag = false;
    for(int i = 0; i < npcs.size(); i++){
        npcs[i]->update();
    }
    
    std::vector<Player*>* players = Juego::Instance().getPlayers();
    
    for(int i = 0; i < players->size(); i++){
        
        Player* ready = (*players)[i];
        
       
        for(int j = 0; j < pinchos.size() && !flag; j++){
            if(ready->getSprite().intersects(pinchos[j])){

                flag = true;
            }
        }
        
        
        
        for(int j = 0; j < powers.size(); j++){
            if(ready->getSprite().intersects(powers[j].sprite)){
                 flag = true;
            }
        }
        
        
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