/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.cpp
 * Author: claudiac
 * 
 * Created on 21 de marzo de 2018, 0:47
 */

#include "Player.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Animator.h"
#include "Mapa/Mapa.h"

#define FRAMERATE 60.f
#define UPDATE_STEP 15.f
#define force 50.f*FRAMERATE/UPDATE_STEP
#define speed 12.f
#define jump 2500
#define stop_mult 1.2f

Player::Player(int id, std::string name, float width_, float height_, float x_, float y_, char type_, bool *keys_) : animator(sprite) {
    setId(id);
    setName(name);
    
    physicsEngine* world;
    
    keys = keys_;
    body = world->Instance().createBody(width_, height_, x_, y_, type_);
    
    t = new physicsEngine::type;
    t->id = 2;
    t->data = this;
    body.setUserData(t);
    onAir = 0;
    level=1;

    
    sprite.setOrigin(30, 39);
    sprite.setScale(1.4f, 1.5f);
    switch(id){
    //Asigna la textura con su color dependiendo del id del jugador
        case 0:
                texture="assets/player0.png";
                //KeyCode                
                key_r=3;
                key_l=0;
                key_up=22;
                key_hit=4;
        break;
        case 1:
                texture="assets/player1.png";
                //KeyCode                
                key_r=72;
                key_l=71;
                key_up=73;
                key_hit=4;
                sprite.setPosition(x_, y_);
        break;
        case 2:
                texture="assets/player2.png"; 
                //KeyCode                
                key_r=-1;
                key_l=10;
                key_up=14;
                key_hit=4;    
        break;
        case 3:
                texture="assets/player3.png"; 
                //KeyCode                
                key_r=13;
                key_l=21;
                key_up=6;
                key_hit=4;                       
        break;                           
    }
   
    
    sf::Vector2i spriteSize(60,60);
    
    Animator::Animation* anim = &animator.CreateAnimation("a_bas",texture, renderEngine::rTime(3), false);
    anim->AddFrames(sf::Vector2i(0,0), sf::Vector2i(60,60), 1);
    animator.SwitchAnimation("a_bas");
    
    Animator::Animation* a_base = &animator.CreateAnimation("a_base",texture, renderEngine::rTime(3), false);
    a_base->AddFrames(sf::Vector2i(0,0), spriteSize ,1);
    
    //Giro Derecha
    Animator::Animation* a_rigth = &animator.CreateAnimation("a_rigth",texture, renderEngine::rTime(0.3), false);
    a_rigth->AddFrames(sf::Vector2i(300,0), spriteSize , 3);
    Animator::Animation* a_base_r = &animator.CreateAnimation("a_base_r",texture, renderEngine::rTime(0.2), false);
    a_base_r->AddFrames(sf::Vector2i(480,0), spriteSize , 2);
    
    //Giro Izquierda
    Animator::Animation* a_left = &animator.CreateAnimation("a_left",texture, renderEngine::rTime(0.3), false);
    a_left->AddFrames(sf::Vector2i(0,0), spriteSize , 3);
    Animator::Animation* a_base_l = &animator.CreateAnimation("a_base_l",texture, renderEngine::rTime(0.2), false);
    a_base_l->AddFrames(sf::Vector2i(180,0), spriteSize , 2);
    
    /*
    //Salto izquierda
    Animator::Animation* a_jump_l = &animator.CreateAnimation("a_jump_l",texture, renderEngine::rTime(0.5), false);
    a_jump_l->AddFrames(sf::Vector2i(0,60), spriteSize ,9);          
    
    //Salto derecha
    Animator::Animation*  a_jump_r = &animator.CreateAnimation("a_jump_r",texture, renderEngine::rTime(0.5), false);
    a_jump_r->AddFrames(sf::Vector2i(0,180), spriteSize ,9);   
    
    //Para colision
    Animator::Animation*  a_fall_l = &animator.CreateAnimation("a_fall_l",texture, renderEngine::rTime(0.5), false);
    a_fall_l->AddFrames(sf::Vector2i(0,120), spriteSize ,3);
    Animator::Animation*  a_fall_r = &animator.CreateAnimation("a_fall_r",texture, renderEngine::rTime(0.5), false);
    a_fall_r->AddFrames(sf::Vector2i(180,120), spriteSize ,3);
    */
    //Prueba de salto
    //Salto izquierda
    Animator::Animation* a_jump_l = &animator.CreateAnimation("a_jump_l",texture, renderEngine::rTime(0.7), false);
    a_jump_l->AddFrames(sf::Vector2i(0,60), spriteSize ,9);  
    a_jump_l->AddFrames(sf::Vector2i(0,120), spriteSize ,3);
    
    //Salto derecha
    Animator::Animation*  a_jump_r = &animator.CreateAnimation("a_jump_r",texture, renderEngine::rTime(0.7), false);
    a_jump_r->AddFrames(sf::Vector2i(0,180), spriteSize ,9); 
    a_jump_r->AddFrames(sf::Vector2i(180,120), spriteSize ,3);  
    
    //Para colision
    Animator::Animation*  a_fall_l = &animator.CreateAnimation("a_fall_l",texture, renderEngine::rTime(0.5), false);
    a_fall_l->AddFrames(sf::Vector2i(0,120), spriteSize ,3);
    Animator::Animation*  a_fall_r = &animator.CreateAnimation("a_fall_r",texture, renderEngine::rTime(0.5), false);
    a_fall_r->AddFrames(sf::Vector2i(180,120), spriteSize ,3);
   
    previous.x = actual.x = body.getXPosition();
    previous.y = actual.y = body.getYPosition();
    previous.r = actual.r = body.getRotation();
    
    sprite.setPosition(actual.x, actual.y);
    
}

Player::~Player() {
    delete t;
    t = nullptr;
}

void Player::setId(int i){
    id = i;
}
int Player::getId(){
    return id;
}
int Player::getLevel(){
    return level;
}

void Player::setName(std::string n){
    name=n;
}
std::string Player::getName(){
    return name;
}

renderEngine::rSprite Player::getSprite(){
    return sprite;
}

void Player::update(renderEngine::rTime deltatime){
    animator.Update(deltatime);
}


void Player::moveRigth(){
    if(animator.GetCurrentAnimationName() != "a_rigth" && animator.GetCurrentAnimationName() != "a_jump_r"){
        animator.SwitchAnimation("a_rigth");
        //std::cout<<"derecha"<<id;
    }
}

void Player::moveRigth_b(){
    //if(animator.GetCurrentAnimationName() != "a_base_r"){
        animator.SwitchAnimation("a_base_r");
    //}
       
}

void Player::moveLeft(){
    if(animator.GetCurrentAnimationName() != "a_left" && animator.GetCurrentAnimationName() != "a_jump_l"){
        animator.SwitchAnimation("a_left");
    }
    //std::cout<<"izquierda"<<id;
                                                                         

}

void Player::moveLeft_b(){
    //if(animator.GetCurrentAnimationName() != "a_base_l"){
        animator.SwitchAnimation("a_base_l");
    //}

}

void Player::moveUp(){
    if(!isOnAir()){
        
        if(animator.GetCurrentAnimationName() == "a_left" || animator.GetCurrentAnimationName() == "a_jump_l"){
            animator.SwitchAnimation("a_jump_l");
        }
        if(animator.GetCurrentAnimationName() == "a_rigth"||animator.GetCurrentAnimationName() == "a_jump_r" ){
            animator.SwitchAnimation("a_jump_r");
        }
    }
}
void Player::moveUp_r(){
    if(animator.GetCurrentAnimationName() != "a_jump_r"){
        animator.SwitchAnimation("a_jump_r");
    }                  
  
}
void Player::moveUp_l(){
    if(animator.GetCurrentAnimationName() != "a_jump_l"){
        animator.SwitchAnimation("a_jump_l");
    } 

}

void Player::moveDown(){
    /*if(animator.GetCurrentAnimationName() == "a_jump_l" || animator.GetCurrentAnimationName() == "a_base_l" || animator.GetCurrentAnimationName() == "a_left" ){
        animator.SwitchAnimation("a_fall_l");
    }
    if(animator.GetCurrentAnimationName() == "a_jump_r" || animator.GetCurrentAnimationName() == "a_base_r" || animator.GetCurrentAnimationName() == "a_rigth"){
        animator.SwitchAnimation("a_fall_r");
    } */
    if(animator.GetCurrentAnimationName() == "a_jump_l"){
        animator.SwitchAnimation("a_left");
    }
    if(animator.GetCurrentAnimationName() == "a_jump_r"){
        animator.SwitchAnimation("a_rigth");
    }

}

//MOVIMIENTO
void Player::movement(){
    preState();
    // SALTO======================================================================
    if((keys[key_up]) && !isOnAir()){                                               //
        body.applyForceToCenter(0, -jump);                                          //
        moveUp();                                                                   //
    }else{
        //IZQUIERDA==================================================================
        if( keys[key_l])  {                                                         //
            if(body.getLinearXVelocity() > -speed)                                  //
                body.applyForceToCenter(-force, 0);                                 //
            else                                                                    //  
                body.setLinealVelocicity(-speed, body.getLinearYVelocity());        //
            if(!isOnAir()){
                moveLeft(); 
            }                                                                       //
        }                                                                           //
        // ===========================================================================

        // DERECHA==================================================================
        if( keys[key_r]) {                                                          //
            if(body.getLinearXVelocity() < speed)                                   //
                body.applyForceToCenter(force, 0);                                  //
            else                                                                    //  
                body.setLinealVelocicity(speed, body.getLinearYVelocity());         //
            if(!isOnAir()){
                moveRigth();
            }                                                                       //
        }                                                                           //
        // ===========================================================================
        
    }                                                                           
    // =============================================================================//    

    //STOP CON DESLIZAMIENTO FRENADO==========================================================================
    if(!keys[key_l] && body.getLinearXVelocity() < -2){                                                     //
        body.applyForceToCenter(force*stop_mult, 0);                                                        //
    }                                                                                                       //
    else if(!keys[key_r] && body.getLinearXVelocity() > 2)                                                  //
        body.applyForceToCenter(-force*stop_mult, 0);                                                       //
                                                                                                            // 
    if(!keys[key_l] && !keys[key_r] && body.getLinearXVelocity() >= -2 && body.getLinearXVelocity() <= 2){  //
        body.applyForceToCenter(0, 0);                                                                      //
        body.setLinealVelocicity(0, body.getLinearYVelocity());                                             //
    }                                                                                                       //
    //  ======================================================================================================
}

void Player::interpola(float tick_){
    // CALCULO LAS POSICIONES INTERPOLADAS DE ACUERDO AL TICK
    float x = previous.x *(1-tick_) + actual.x*tick_;
    float y = previous.y *(1-tick_) + actual.y*tick_;
        // Para las rotaciones es mejor interpolar los senos y cosenos, ya que si no, al calcular el ángulo entre 350 y 10, por ejemplo, no nos devolvería 20, que sería lo correcto
    float s = sin(previous.r * M_PI/180) * (1-tick_) + sin(actual.r * M_PI/180)*tick_;
    float c = cos(previous.r * M_PI/180) * (1-tick_) + cos(actual.r * M_PI/180)*tick_;
    
    sprite.setPosition(x, y);
    sprite.setRotation(atan2(s,c)*180/M_PI);
}
std::string Player::anima(){
    return animator.GetCurrentAnimationName(); 
}

void Player::draw(){
    sprite.draw();
}

void Player::preState(){
    previous = actual;      // GUARDO EL ESTADO ANTERIOR
}

void Player::newState(){
    actual.x = body.getXPosition();
    actual.y = body.getYPosition();
    actual.r = body.getRotation();
}

float Player::getXPosition(){
    return  sprite.getPosition()[0];
}

float Player::getYPosition() {
    return  sprite.getPosition()[1];
}


bool Player::isOnAir(){
    return (onAir <= 0) ? true : false;
}
void Player::setAir(int i){
    onAir += i;
}

void Player::powerUpInmortalidad() {

}

void Player::powerUpSpeed() {

}

void Player::powerDownJump() {

}

void Player::powerDownFreeze() {

}

void Player::setPosition(float x, float y) {
    body.setPosition(x, y);
}

int Player::getAir() {
    return onAir;
}
