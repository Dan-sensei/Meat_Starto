/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: claudiac
 *
 * Created on 21 de marzo de 2018, 0:47
 */

#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include "Animator.h"
#include "AssetManager.h"


class Player {
public:
    Player(int id, std::string name);
    Player(const Player& orig);
    virtual ~Player();
    void setId(int i);
    int getId();
    void setSpeed(float f);
    float getSpeed();
    int getLevel();
    void setName(std::string n);
    std::string getName();
    sf::Sprite getSprite();
    
private:
    int id;
    int level;
    float speed;
    std::string name; 
    std::string texture;
    sf::Sprite sprite;
    Animator a();
    
};

#endif /* PLAYER_H */

