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
#include "AssetManager.h"

Player::Player(int id, std::string name) : animator(sprite) {
    setId(id);
    setName(name);
    
    switch(id){
    //Asigna la textura con su color dependiendo del id del jugador
                case 0:
                        texture="resources/player0.png";
                break;
                case 1:
                        texture="resources/player1.png";
                        sprite.setPosition(100,0);
                break;
                case 2:
                        texture="resources/player2.png";    
                break;
                case 3:
                        texture="resources/player3.png";                        
                break;                           
            }
   
    
    sf::Vector2i spriteSize(60,60);
   
    Animator::Animation* anim = &animator.CreateAnimation("a_bas",texture, sf::seconds(3), false);
    anim->AddFrames(sf::Vector2i(0,0), sf::Vector2i(60,60), 1);
    animator.SwitchAnimation("a_bas");
    
    Animator::Animation* a_base = &animator.CreateAnimation("a_base",texture, sf::seconds(3), false);
    a_base->AddFrames(sf::Vector2i(0,0), spriteSize ,1);
    
    //Giro Derecha
    Animator::Animation* a_rigth = &animator.CreateAnimation("a_rigth",texture, sf::seconds(0.3), false);
    a_rigth->AddFrames(sf::Vector2i(300,0), spriteSize , 3);
    Animator::Animation* a_base_r = &animator.CreateAnimation("a_base_r",texture, sf::seconds(0.2), false);
    a_base_r->AddFrames(sf::Vector2i(480,0), spriteSize , 2);
    
    //Giro Izquierda
    Animator::Animation* a_left = &animator.CreateAnimation("a_left",texture, sf::seconds(0.3), false);
    a_left->AddFrames(sf::Vector2i(0,0), spriteSize , 3);
    Animator::Animation* a_base_l = &animator.CreateAnimation("a_base_l",texture, sf::seconds(0.2), false);
    a_base_l->AddFrames(sf::Vector2i(180,0), spriteSize , 2);
    
    //Salto izquierda
    Animator::Animation* a_jump_l = &animator.CreateAnimation("a_jump_l",texture, sf::seconds(2), false);
    a_jump_l->AddFrames(sf::Vector2i(0,60), spriteSize ,9);          
    
    //Salto derecha
    Animator::Animation*  a_jump_r = &animator.CreateAnimation("a_jump_r",texture, sf::seconds(2), false);
    a_jump_r->AddFrames(sf::Vector2i(0,180), spriteSize ,9);   
    
    //Para colision
    Animator::Animation*  a_fall_l = &animator.CreateAnimation("a_fall_l",texture, sf::seconds(0.5), false);
    a_fall_l->AddFrames(sf::Vector2i(0,120), spriteSize ,3);
    Animator::Animation*  a_fall_r = &animator.CreateAnimation("a_fall_r",texture, sf::seconds(0.5), false);
    a_fall_r->AddFrames(sf::Vector2i(180,120), spriteSize ,3);
   
    
}

Player::~Player() {
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
void Player::setSpeed(float f){
    speed=f;
}
float Player::getSpeed(){
    return speed;
}
void Player::setName(std::string n){
    name=n;
}
std::string Player::getName(){
    return name;
}

sf::Sprite Player::getSprite(){
    return sprite;
}

void Player::update(sf::Time deltatime){
    animator.Update(deltatime);
}


void Player::moveRigth(){
    if(animator.GetCurrentAnimationName() != "a_rigth"){
        animator.SwitchAnimation("a_rigth");
    }
}

void Player::moveRigth_b(){
    if(animator.GetCurrentAnimationName() != "a_base_r"){
        animator.SwitchAnimation("a_base_r");
    }
}

void Player::moveLeft(){
    if(animator.GetCurrentAnimationName() != "a_left"){
        animator.SwitchAnimation("a_left");
    }
}

void Player::moveLeft_b(){
    if(animator.GetCurrentAnimationName() != "a_base_l"){
        animator.SwitchAnimation("a_base_l");
    }
}

void Player::moveUp(){
    if(animator.GetCurrentAnimationName() == "a_base_r"){
                                
    }                     
    if(animator.GetCurrentAnimationName() == "a_left"){
        animator.SwitchAnimation("a_jump_l");
    }
    if(animator.GetCurrentAnimationName() == "a_rigth"){
        animator.SwitchAnimation("a_jump_r");
    }
}

void Player::moveDown(){
    if(animator.GetCurrentAnimationName() == "a_jump_l" || animator.GetCurrentAnimationName() == "a_base_l" || animator.GetCurrentAnimationName() == "a_left" ){
        animator.SwitchAnimation("a_fall_l");
    }
    if(animator.GetCurrentAnimationName() == "a_jump_r" || animator.GetCurrentAnimationName() == "a_base_r" || animator.GetCurrentAnimationName() == "a_rigth"){
        animator.SwitchAnimation("a_fall_r");
    }                       
}
