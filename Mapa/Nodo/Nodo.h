/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nodo.h
 * Author: dan
 *
 * Created on 11 de abril de 2018, 3:33
 */

#ifndef NODO_H
#define NODO_H

#include <array>
#include <vector>

#include "Ground.h"
#include "NPCs/NPC.h"

class Nodo {
public:

    Nodo(std::string sheet);
    Nodo(const Nodo& orig);
    virtual ~Nodo();
    
    void addTile(int id, int x, int y);
    void setRectVector(std::vector<renderEngine::rIntRect> rect_);
    void setPop(int i);
    int getPop();
    
    void draw(renderEngine::rIntRect limit);
    
    int getSize();
    
private:
    
    renderEngine::rSprite tile;
    
    std::vector<std::array<int, 2>> tilePosition;
    std::vector<renderEngine::rIntRect> tileRect;
    std::vector<int> tileId;
    
    NPC* npcs;
    Ground ground;
    int aux_pop;
    
    int counter;
};

#endif /* NODO_H */

