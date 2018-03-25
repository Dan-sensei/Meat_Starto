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

Player::Player(int id, std::string name) {
    setId(id);
    setName(name);
    switch(id){
    //Asigna la textura con su color dependiendo del id del jugador
                case 0:
                        texture="resources/player0.png";
                break;
                case 1:
                        texture="resources/player1.png";
                break;
                case 2:
                        texture="resources/player2.png";             
                break;
                case 3:
                        texture="resources/player3.png";                        
                break;                           
            }
    
    sf::Vector2i spriteSize(60,60);
    //Cargo la imagen donde reside la textura del sprite
    sf::Texture tex;
    if (!tex.loadFromFile("resources/player6.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    
    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite sprite2(tex);
    sprite2.setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
    sprite2.setPosition(320, 240);
    
    sprite=sprite2;
    //Animator animator(sprite);
   
    //Animator animatorp(sprite);
    
    //auto& p = animatorp.CreateAnimation("p","resources/player6.png", sf::seconds(3), false);
     //Y creo el spritesheet a partir de la imagen anterior
   
    //Cojo el sprite que me interesa por defecto del sheet
    //sprite.setTexture("resources/player6.png");
    //sprite.setTextureRect(sf::IntRect(0*75, 0*75, 75, 75));
    // Lo dispongo en el centro de la pantalla
    //sprite.setPosition(320, 240);
    
    //Animator animator2(sprite);
    //auto& a_base2 = animator2.CreateAnimation("a_base",texture, sf::seconds(3), false);
    //a_base2.AddFrames(sf::Vector2i(0,0), spriteSize ,1);
    std::cout<<"animacion";
    //std::cout<< animator2.GetCurrentAnimationName();
    
}

Player::Player(const Player& orig) {
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




