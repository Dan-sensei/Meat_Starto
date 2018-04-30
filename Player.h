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
#include "renderEngine/renderEngine.h"
#include "physicsEngine/pBody.h"
#include "physicsEngine/physicsEngine.h"
#include "particleSystem.h"

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
    
    int getExp();
    int getExp_levelup();
    int getMuertes();
    int getEnemigos();
    
    
    void update();
    void double_hit(bool b);
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
    
    bool isInmortal();
    
    struct state{
        float x;     // Posicion X
        float y;     // Posicion Y
        float r;     // Rotacion
    };
    state previous;
    state actual;
    
    void preState();
    void newState();
    
    int onAir;
    bool touchingWall;
    void setAir(int i);
    bool isOnAir();
    int getAir();
    
    void powerUpInmortalidad();     // 0
    void powerUpSpeed();            // 1
    void powerUpExperience();       // 2
    
    void powerDownJump();           // 3
    void powerDownFreeze();         // 4
    void powerDownLevelOne();       // 5
    void powerDownFish();           // 6
    
    void lvlDown();
    void lvlUp();
    
    void hazInmortal();
    void setTouchingWall(bool flag);
    
    void setPosition(float x, float y);
    void transportToSecondPhase(float x, float y);
    std::string anima();
    
private:
    int id;
    int level;
    std::string name; 
    std::string texture;
    std::string texture2;
    renderEngine::rSprite sprite;
    renderEngine::rSprite mano;    
    bool hit;
    bool dead;
    int hand_length;
    Animator animator;
    int key_r,key_l,key_up,key_hit,key_suicide;
    
    bool* keys;
    renderEngine::rClock animationClock;
    float MAXSPEED;
    int exp_for_next_level;
    int exp;
    
    bool stopJump;
    bool inmortal;
    bool doublehit;
    renderEngine::rClock inmortalityClock;
    renderEngine::rClock speedClock;
    renderEngine::rClock deadClock;
    
    renderEngine::rClock respawnTimeClock;
    bool spawned;
    
    pBody body;
    
    physicsEngine::type* t;
    physicsEngine::type* bottom;
    
    particleSystem blood;
    
    int muertes;
    int enemigos;
  //  renderEngine::rImage indicador_escudo;

    
    renderEngine::rImage indicadores_power;
    struct indicador{
        renderEngine::rIntRect *ir;
        renderEngine::rTexture t;
        renderEngine::rSprite sprite;
    };
    indicador *invincible;
    indicador *speed;
    
    indicador *expup;
    renderEngine::rClock exp_clock;
    
    indicador *freeze;
    bool freezed;
    renderEngine::rClock frigoclock;
    
    indicador *controls;
    renderEngine::rClock controls_clock;
    bool inv_control;
    
    indicador *lvl1;
    renderEngine::rClock baby_clock;
   // indicador *escudo;
};

#endif /* PLAYER_H */

