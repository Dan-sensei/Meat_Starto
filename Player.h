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

class Player {
public:
    Player(int id, std::string name, float width_, float height_, float x_, float y_, char type_, bool *keys_);
    Player(const Player& orig);
    virtual ~Player();
    void setId(int i);
    int getId();
    float getXPosition();
    float getYPosition();
    int getLevel();
    void setName(std::string n);
    std::string getName();
    renderEngine::rSprite getSprite();
    
    void update(renderEngine::rTime deltatime);
    void moveRigth();
    void moveRigth_b();
    void moveLeft();
    void moveLeft_b();
    void moveUp();
    void moveUp_r();
    void moveUp_l();
    void moveDown();
    
    void movement();
    void interpola(float tick_);
    void draw();
    
    struct state{
        float x;     // Posicion X
        float y;     // Posicion Y
        float r;     // Rotacion
    };
    state previous;
    state actual;
    
    void preState();
    void newState();
    
    physicsEngine::type* t;
    
    int onAir;
    void setAir(int i);
    bool isOnAir();
    
    void powerUpInmortalidad();
    void powerUpSpeed();
    void powerDownJump();
    void powerDownFreeze();
    
    void setPosition(float x, float y);
    
private:
    int id;
    int level;
    float speed;
    std::string name; 
    std::string texture;
    renderEngine::rSprite sprite;
    Animator animator;
    
    bool* keys;
    
    
    pBody body;
};

#endif /* PLAYER_H */

