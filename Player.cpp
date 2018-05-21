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
#include <complex>
#include "Animator.h"
#include "Mapa/Mapa.h"
#include "Juego.h"
#include "AssetManager.h"

#define FRAMERATE 60.f
#define UPDATE_STEP 15.f
#define force 50.f*FRAMERATE/UPDATE_STEP

#define jump 2000
#define minJumpVelocity 13
#define stop_mult 1.5f

#define inmortalityTime 5.f
#define speedTime 5.f
#define constMaxSeed 14.f
#define meatEXP 250.f

Player::Player(int id_, std::string name_, float width_, float height_, float x_, float y_, bool *keys_) : animator(sprite) {
    
    id = id_;
    name = name_;
    keys = keys_;
    
    t = new physicsEngine::type;
    t->id = 2;
    t->data = this;
    
    bottom = new physicsEngine::type;
    bottom->id = 5;
    bottom->data = this;
    
    body = physicsEngine::Instance().createPlayer(width_, height_, x_, y_, t, bottom);

    onAir = 0;
    level=3;

    hit=false;
    dead=false;

    std::string texture = "assets/player"+std::to_string(id)+"a.png";
    std::string texture2 = "assets/player"+std::to_string(id)+"explosion.png";
    
    int keyCodes[4][5] = 
    //   R      L       UP    HIT     /KILL
    {    3,     0,      22,     4,      28,
        72,     71,     73,     4,      57,
        -1,     10,     14,     4,       8,
        13,     21,      6,     4,       9
    };
    
    key_r       =   keyCodes[id][0];
    key_l       =   keyCodes[id][1];
    key_up      =   keyCodes[id][2];
    key_hit     =   keyCodes[id][3];
    key_suicide =   keyCodes[id][4];
    
    sprite.setOrigin(48/2, 40/2+4);
    sprite.setScale(1.4f, 1.6f);
    
   /*MANO*/
    
    int width = AssetManager::GetTexture(texture).getXSize();
    int height = AssetManager::GetTexture(texture).getYSize();

    mano.setTexture(AssetManager::GetTexture(texture));
    renderEngine::rIntRect hit_s_(60,200,67,49);
    renderEngine::rIntRect hit_double_(20,200,130,49);
    mano.setTextureRect(hit_s_);
    mano.setOrigin(-20,25);
    
    
    /*ANIMACIONES*/
    //sf::Vector2i spriteSize(60,60);
    sf::Vector2i spriteSize(48,40);
    Animator::Animation* anim = &animator.CreateAnimation("a_bas", texture, renderEngine::rTime(3), false);
    anim->AddFrames(sf::Vector2i(0,0), sf::Vector2i(48,40), 1);
    animator.SwitchAnimation("a_bas");
    
    Animator::Animation* a_base = &animator.CreateAnimation("a_base", texture, renderEngine::rTime(3), false);
    a_base->AddFrames(sf::Vector2i(0,0), spriteSize ,1);
    
    //Giro Derecha
    Animator::Animation* a_rigth = &animator.CreateAnimation("a_rigth", texture, renderEngine::rTime(0.3), false);
    a_rigth->AddFrames(sf::Vector2i(240,0), spriteSize , 3);
    Animator::Animation* a_base_r = &animator.CreateAnimation("a_base_r", texture, renderEngine::rTime(0.2), false);
    a_base_r->AddFrames(sf::Vector2i(384,0), spriteSize , 2);
    
    //Giro Izquierda
    Animator::Animation* a_left = &animator.CreateAnimation("a_left", texture, renderEngine::rTime(0.3), false);
    a_left->AddFrames(sf::Vector2i(0,0), spriteSize , 3);
    Animator::Animation* a_base_l = &animator.CreateAnimation("a_base_l", texture, renderEngine::rTime(0.2), false);
    a_base_l->AddFrames(sf::Vector2i(144,0), spriteSize , 2);
    
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
    Animator::Animation* a_jump_l = &animator.CreateAnimation("a_jump_l", texture, renderEngine::rTime(0.7), false);
    a_jump_l->AddFrames(sf::Vector2i(0,40), spriteSize ,9);  
    a_jump_l->AddFrames(sf::Vector2i(48,80), spriteSize ,2);
    
    //Salto derecha
    Animator::Animation*  a_jump_r = &animator.CreateAnimation("a_jump_r", texture, renderEngine::rTime(0.7), false);
    a_jump_r->AddFrames(sf::Vector2i(0,120), spriteSize ,9); 
    a_jump_r->AddFrames(sf::Vector2i(192,80), spriteSize ,2);  
    
    //Para colision
    Animator::Animation*  a_fall_l = &animator.CreateAnimation("a_fall_l", texture, renderEngine::rTime(0.5), false);
    a_fall_l->AddFrames(sf::Vector2i(0,120), spriteSize ,3);
    Animator::Animation*  a_fall_r = &animator.CreateAnimation("a_fall_r", texture, renderEngine::rTime(0.5), false);
    a_fall_r->AddFrames(sf::Vector2i(180,120), spriteSize ,3);
    
    //Para suicidio
    Animator::Animation*  xplota = &animator.CreateAnimation("xplota", texture2, renderEngine::rTime(0.5), false);
    xplota->AddFrames(sf::Vector2i(0,0), sf::Vector2i(225,140) ,4);
    xplota->AddFrames(sf::Vector2i(0,140), sf::Vector2i(225,140) ,4);
    xplota->AddFrames(sf::Vector2i(0,280), sf::Vector2i(225,140) ,3);
   
    previous.x = actual.x = body.getXPosition();
    previous.y = actual.y = body.getYPosition();
    previous.r = actual.r = body.getRotation();
    
    sprite.setPosition(actual.x, actual.y);
    mano.setPosition(actual.x, actual.y);
    
    
    inmortal = false;
    freezed = false;
    inv_control = false;
    exp_for_next_level = 500;
    exp = 0;
    
    MAXSPEED = constMaxSeed;
    
    spawned = false;
    
    /*
    blood.setPosition(x_, y_);                    // Posicion del sistema de partículas
    blood.setType(1);                                // Tipo: Determina el área de generado | 0 = Círculo - 1 = Rectángulo (Por defecto tienen tamaño 0 y emitirán hacia el exterior aleatoriamente)
    blood.setParticleSpeed(0);                     // Velocidad lineal de las partículas
    blood.setMaxParticleAmout(500);                  // Máximo número de partículas
    blood.setGenerationTimer(5);                     // Tiempo (ms) de delay entre la generación de partículas (En este caso se genera una partícula cada 4 ms)
    blood.setParticleLifeTime(0.25);                    // Tiempo de vida en segundos, de vida d elas partículas
    blood.setParticleDirection(-1, 0);             // Dirección de las partículas, debe ser un número entre 0 y 1
    blood.setRectangle(60, 20);                   // Área de generado, en este caso es un rectángulo, así que le digo ancho y alto, si fuera un círculo, llamaría a setCircle(float radius);
    //blood.setCircle(30);
    blood.setParticleRotationRandomBetween(-180, 180);
    blood.setSprite("assets/RED.png");    // Cambia el sprite
    blood.setSpriteSize(1, 1);                     // Cambia el tamaño del sprite
    blood.setParticleAngularVelocityRandomBetween(-10, -15);
    //blood.drawGenerationArea(true);
    */
    
    touchingWall = false;
    stopJump = false;
    muertes=0;
    enemigos=0;
    
    indicadores_power.loadFromFIle("assets/powers/indicadores_power.png");
    invincible = NULL;
    speed = NULL;
    expup = NULL;
    freeze = NULL;
    controls = NULL;
    lvl1 = NULL;
    
    escudo = false;
    
     /*escudo*/
    std::string sprite_name1 = "assets/powers/indicador_escudo.png";
    
    int widthp = AssetManager::GetTexture(sprite_name1).getXSize();
    int heightp = AssetManager::GetTexture(sprite_name1).getYSize();
    
    spescudo.setTexture(AssetManager::GetTexture(sprite_name1));
    spescudo.setOrigin(widthp / 2, heightp / 2);
    spescudo.setScale(1, 1);
    
    lvlUp();
    inmortalRespawn = false;

}

Player::~Player() {
    delete t;
    t = nullptr;
}


void Player::hazInmortal(){
    if (inmortal==false){
        inmortal=true;
    }else{
        inmortal=false;

    }
}

void Player::update(){
    if(exp>=exp_for_next_level && level<4){
        std::cout << "Subo nivel con exp" << std::endl;
        lvlUp();
        exp = exp-exp_for_next_level;
        //exp_for_next_level+=100;
    }
    animator.Update(animationClock.restart());
    
    
    if(invincible){
        invincible->sprite.setPosition(sprite.getPosition()[0]-135,sprite.getPosition()[1]+50);
    }
    if(speed){
        speed->sprite.setPosition(sprite.getPosition()[0]-135,sprite.getPosition()[1]+50);
    }
    if(expup){
        expup->sprite.setPosition(sprite.getPosition()[0]-135,sprite.getPosition()[1]+50);
    }
    if(freeze){
        freeze->sprite.setPosition(sprite.getPosition()[0]-135,sprite.getPosition()[1]+50);
    }
    if(controls){
        controls->sprite.setPosition(sprite.getPosition()[0]-120,sprite.getPosition()[1]-120);
    }
    if(lvl1){
        lvl1->sprite.setPosition(sprite.getPosition()[0]-55,sprite.getPosition()[1]-120);
    }
    if(escudo==true){
        spescudo.setPosition(sprite.getPosition()[0],sprite.getPosition()[1]);

    }
 
}

void Player::double_hit(bool b){
    //Cambiar longitud del golpe. True = doble golpe // False = golpe simple
    if(doublehit != b){
        doublehit=b;             
        if(doublehit==false){
            renderEngine::rIntRect hit_s_(60,200,67,49);
            mano.setTextureRect(hit_s_);
        }else{
            renderEngine::rIntRect hit_double_(20,200,130,49);
            mano.setTextureRect(hit_double_);
        }
    }        
}

void Player::moveRigth(){
    if(animator.GetCurrentAnimationName() != "a_rigth" && animator.GetCurrentAnimationName() != "a_jump_r"){
        animator.SwitchAnimation("a_rigth");
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
    
    if(spawned && respawnTimeClock.getElapsedTime().asSeconds() > 0.50){
        body.setActive(true);
        spawned = false;
    }
    
    if(inmortalRespawn && inmortalRespawnClock.getElapsedTime().asSeconds() > 1){
        inmortalRespawn = false;
        if(!invincible){
            inmortal = false;
        }
    }
    
    if(!freezed){
        //GOLPE
        if(keys[key_hit]){
            hit=true;
            if(animator.GetCurrentAnimationName()== "a_rigth" || animator.GetCurrentAnimationName()== "a_base_r" || animator.GetCurrentAnimationName()== "a_jump_r"){
                //Golpe hacia la derecha
                mano.setScale(1,1);
            }else{
                //golpe a la izquierda
                mano.setScale(-1,1);
            }        

        }else{
            if(hit==true){
                hit=false;
            }      
        }

        // SALTO==========================================================================
        if((keys[key_up]) && !isOnAir()){                                               //
            body.applyForceToCenter(0, -jump);                                          //
            moveUp();                                                                   //
            stopJump = false;                                                           //
        }else{                                                                          //
            //IZQUIERDA===================================================================
            if( keys[key_l])  {
                if(!inv_control){
                    if(body.getLinearXVelocity() > -MAXSPEED)                               
                        body.applyForceToCenter(-force, 0);                                 
                    else                                                                      
                        body.setLinealVelocicity(-MAXSPEED, body.getLinearYVelocity());     
                    if(!isOnAir()){                                                         
                        moveLeft();                                                         
                    }                                                                       
                }
                else{
                    if(body.getLinearXVelocity() < MAXSPEED)                                   
                        body.applyForceToCenter(force, 0);                                  
                    else                                                                      
                        body.setLinealVelocicity(MAXSPEED, body.getLinearYVelocity());         
                    if(!isOnAir()){
                        moveRigth();
                    } 
                }
            }                                                                           
            // ===========================================================================

            // DERECHA==================================================================
            if( keys[key_r]) { 
                if(!inv_control){
                    if(body.getLinearXVelocity() < MAXSPEED)                                   
                        body.applyForceToCenter(force, 0);                                  
                    else                                                                      
                        body.setLinealVelocicity(MAXSPEED, body.getLinearYVelocity());         
                    if(!isOnAir()){
                        moveRigth();
                    }                                                                       
                }
                else{
                    if(body.getLinearXVelocity() > -MAXSPEED)                               
                        body.applyForceToCenter(-force, 0);                                 
                    else                                                                      
                        body.setLinealVelocicity(-MAXSPEED, body.getLinearYVelocity());     
                    if(!isOnAir()){                                                         
                        moveLeft();                                                         
                    } 
                }
            }                                                                           
            // ===========================================================================
            if(key_suicide != -1 && keys[key_suicide] && level>0 ){
                std::cout << "BUM" << std::endl;
                if(animator.GetCurrentAnimationName() != "xplota"){
                    sprite.setOrigin(90+48/2 , 100 + 40/2+4);
                    animator.SwitchAnimation("xplota"); 
                }

                if(!inmortal && dead==false){
                    dead=true;
                    deadClock.restart();               
                    //Mapa::Instance().movePlayerToClosestCheckPoint(this);
                }
                std::vector<Player*>* players = Juego::Instance().getPlayers();
                for(int i=0 ; i<players->size() ; i++){
                    Player* ready = (*players)[i];
                    int x = ready->getXPosition()-sprite.getPosition()[0];
                    int y = ready->getYPosition()-sprite.getPosition()[1];

                    if(id != ready->getId() && sqrt(x*x+y*y)<150){
                         if(ready->escudo==false){
                            Mapa::Instance().movePlayerToClosestCheckPoint(ready);
                            //ready->lvlDown();
                        }else{
                            ready->escudo=false;
                        }
                    }
                }

                keys[key_suicide] = false;
            }
        }
    }
    //-30
    //-13

    if(isOnAir()){
        if(!keys[key_up] && !stopJump){
            if(body.getLinearYVelocity() < -minJumpVelocity){
                stopJump = true;
                body.setLinealVelocicity(body.getLinearXVelocity(), -minJumpVelocity);
            } 
        }
    }
    // =============================================================================//    

    //STOP CON DESLIZAMIENTO FRENADO==========================================================================
    if(!keys[key_l] && body.getLinearXVelocity() < -3){                                                     //
        body.applyForceToCenter(force*stop_mult, 0);
        //!inv_control? body.applyForceToCenter(force*stop_mult, 0) : body.applyForceToCenter(-force*stop_mult, 0);
    }                                                                                                       //
    else if(!keys[key_r] && body.getLinearXVelocity() > 3)                                                  //
        body.applyForceToCenter(-force*stop_mult, 0);
        //!inv_control? body.applyForceToCenter(-force*stop_mult, 0) : body.applyForceToCenter(force*stop_mult, 0);
                                                                                                            // 
    if(!keys[key_l] && !keys[key_r] && body.getLinearXVelocity() >= -3 && body.getLinearXVelocity() <= 3){  //
        body.applyForceToCenter(0, 0);                                                                      //
        body.setLinealVelocicity(0, body.getLinearYVelocity());                                             //
    }                                                                                                       //
    //  ======================================================================================================
        
    if(dead==true && deadClock.getElapsedTime().asSeconds()>1){
        sprite.setOrigin(48/2 ,40/2+4);
        animator.SwitchAnimation("a_base");
        Mapa::Instance().movePlayerToClosestCheckPoint(this);
        std::cout<<"reinicio player"<<std::endl;
        deadClock.restart();        
        dead=false;
    }
    if(freezed && frigoclock.getElapsedTime().asSeconds()>0.5){
        delete freeze;
        freeze = NULL;
        
        freezed = false;
    }
    
    if(inv_control && controls_clock.getElapsedTime().asSeconds()>1){
        delete controls;
    
        controls = NULL;
        
        inv_control = false;
    }
    
    if(inmortal && !inmortalRespawn){
        if(inmortalityClock.getElapsedTime().asSeconds() > inmortalityTime){
            //std::cout << "VUELVE A LA TIERRA CHATO" << std::endl;
            inmortal = false;
            
            if(invincible){
                delete invincible;
                invincible = NULL;
            }
        }
    }
    
    if(speed){
        if(speedClock.getElapsedTime().asSeconds() > speedTime){
            //std::cout << "SE ACABÓ EL GAS WE" << std::endl;
            if(level >= 3){
                MAXSPEED = constMaxSeed+3;
            }
            else{
                MAXSPEED = constMaxSeed;
            }
            
            if(speed){
                delete speed;
                speed = NULL;
            }
        }
    }
    
    
    if(expup && exp_clock.getElapsedTime().asSeconds()>1){
        delete expup;
        expup = NULL;
    }
   
    if(lvl1 && baby_clock.getElapsedTime().asSeconds()>1){
        delete lvl1;
        lvl1 = NULL;
    }
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
    mano.setPosition(x,y);
    //blood.interpola(tick_);
}
std::string Player::anima(){
    return animator.GetCurrentAnimationName(); 
}

void Player::draw(){
    
    
    if(hit==true){
        mano.draw();
    }
    sprite.draw();
    //blood.NoUsarEstedraw();
    
    
    if(invincible){
        invincible->sprite.draw();
    }
    if(speed){
        speed->sprite.draw();
    }
    if(expup){
        expup->sprite.draw();
    }
    if(freeze){
        freeze->sprite.draw();
    }
    if(controls){
        controls->sprite.draw();
    }
    if(lvl1){
        lvl1->sprite.draw();
    }
    if(escudo==true){
        spescudo.setPosition(sprite.getPosition()[0],sprite.getPosition()[1]);
        spescudo.draw();
    }
 
}

void Player::preState(){
    previous = actual;      // GUARDO EL ESTADO ANTERIOR
}

void Player::newState(){
    actual.x = body.getXPosition();
    actual.y = body.getYPosition();
    actual.r = body.getRotation();
    //blood.newState();
}

float Player::getXPosition(){
    return  sprite.getPosition()[0];
}

float Player::getYPosition() {
    return  sprite.getPosition()[1];
}


bool Player::isOnAir(){ 
    return (onAir > 0) ? false : true;
}
void Player::setAir(int i){
    onAir += i;
}

// POWERS! =================================================================

void Player::powerUpInmortalidad() {
    invincible = new indicador;
    invincible->ir = new renderEngine::rIntRect(0,88,135,44);
    invincible->t.loadFromImage(indicadores_power,*invincible->ir);
    invincible->sprite.setTexture(invincible->t);
    invincible->sprite.setScale(2,2);
    
    inmortal = true;
    inmortalityClock.restart();
}

void Player::powerUpSpeed() {
    speed = new indicador;
    speed->ir = new renderEngine::rIntRect(0,0,135,44);
    speed->t.loadFromImage(indicadores_power,*speed->ir);
    speed->sprite.setTexture(speed->t);
    speed->sprite.setScale(2,2);
    
    MAXSPEED += 3;
    speedClock.restart();
}

void Player::powerUpExperience() {
    if(level!=4){
        exp += 250;
    }
    
    expup = new indicador;
    expup->ir = new renderEngine::rIntRect(0,44,135,44);
    expup->t.loadFromImage(indicadores_power,*expup->ir);
    expup->sprite.setTexture(expup->t);
    expup->sprite.setScale(2,2);
    
    exp_clock.restart();
    
}

void Player::powerDownFreeze() {
    //UN CALIPPO DE FRESA POR FAVOR
    
    std::vector<Player*>* v_players = Juego::Instance().getPlayers();
    
    for(int i=0 ; i<v_players->size() ; i++){
        if(i!=id){
            Player* ready = (*v_players)[i];
            
            ready->freeze = new indicador;
            ready->freeze->ir = new renderEngine::rIntRect(0,132,135,44);
            ready->freeze->t.loadFromImage(indicadores_power,*ready->freeze->ir);
            ready->freeze->sprite.setTexture(ready->freeze->t);
            ready->freeze->sprite.setScale(2,2);
            
            ready->frigoclock.restart();
            ready->freezed = true;
            
        }
    }
}

void Player::powerDownJump() {
    //FLANTASTICO
    
    std::vector<Player*>* v_players = Juego::Instance().getPlayers();
    
    for(int i=0 ; i<v_players->size() ; i++){
        if(i!=id){
            Player* ready = (*v_players)[i];
            
            ready->body.applyLinearImpulse(0,-25);
        }
    }
}


void Player::powerDownLevelOne() {
    if(level!=1){
        lvl1 = new indicador;
        lvl1->ir = new renderEngine::rIntRect(0,286,65,40);
        lvl1->t.loadFromImage(indicadores_power,*lvl1->ir);
        lvl1->sprite.setTexture(lvl1->t);
        lvl1->sprite.setScale(2,2);

        baby_clock.restart();
        level = 1;
    }
}

void Player::powerDownFish() {
    // ESTÁS BORRACHO WEY
    std::vector<Player*>* v_players = Juego::Instance().getPlayers();
    
    for(int i=0 ; i<v_players->size() ; i++){
        if(i!=id){
            Player* ready = (*v_players)[i];
            
            ready->controls = new indicador;
            ready->controls->ir = new renderEngine::rIntRect(0,176,107,110);
            ready->controls->t.loadFromImage(indicadores_power,*ready->controls->ir);
            ready->controls->sprite.setTexture(ready->controls->t);
            ready->controls->sprite.setScale(2,2);
            
            ready->controls_clock.restart();
            ready->inv_control = true;
            
        }
    }
}


void Player::setPosition(float x, float y) {
    lvlDown();
    
    body.setPosition(x,y);
    body.setActive(false);
    
    inmortalRespawnClock.restart();
    
    spawned = true;
    onAir = 0;
    
    respawnTimeClock.restart();
    inmortalRespawn = true;    //PARA QUE NO CAIGA EN BUCLE INFINITO EN EL BOSS
    inmortal = true;
    
    if(speed){
        delete speed;
        speed = NULL;
        if(level >= 3){
            MAXSPEED = constMaxSeed+3;
        }
        else{
            MAXSPEED = constMaxSeed;
        }
    }
    if(invincible){
        delete invincible;
        invincible = NULL;
    }
}

void Player::transportToSecondPhase(float x, float y) {
    body.setPosition(x,y);
}

void Player::lvlDown() {
    if(level>0){
        level--;
        
         switch(level){
            case 0: 
            case 1: 
                escudo = false;
                double_hit(false);
                MAXSPEED = constMaxSeed;
                break;
            case 2:
                escudo = false;
                double_hit(true);
                MAXSPEED = constMaxSeed;
                break;
            case 3:
                escudo = false;
                double_hit(true);
                MAXSPEED = constMaxSeed+3;
                break;
                
        }            
    }else if(level==0){
        //MUERE
    }
    muertes++;
}

void Player::lvlUp() {
    if(level<4){
        level++;
        
        switch(level){
            case 0:
            case 1:
                escudo = false;
                double_hit(false);
                MAXSPEED = constMaxSeed;
                break;
            case 2:
                //mayor rango de golpeo
                escudo = false;
                double_hit(true);
                MAXSPEED = constMaxSeed;
                break;
            case 3:
                //mas velocidad
                escudo = false;
                double_hit(true);
                MAXSPEED = constMaxSeed+3;
                break;
            case 4:
                //poner escudo
                escudo = true;
                double_hit(true);
                MAXSPEED = constMaxSeed+3;
                break;

        }
    }
}

// GETTERS
int Player::getId()             {   return id;          }
int Player::getLevel()          {   return level;       }
int Player::getExp()            {   return exp;         }
std::string Player::getName()   {   return name;        }
int Player::getMuertes()        {   return muertes;     }
int Player::getEnemigos()       {   return enemigos;    }
bool Player::getEscudo()        {   return escudo;      }
int Player::getAir()            {   return onAir;       }
bool Player::isInmortal()       {   return inmortal;    }
int Player::getExp_levelup()    {   return exp_for_next_level;  }
renderEngine::rSprite Player::getSprite()   {   return sprite;  }
renderEngine::rSprite Player::getMano()     {   return mano;    }

void Player::setEscudo(bool b) {       escudo = b;  }
void Player::setActive(bool flag) {    body.setActive(flag);    }

bool Player::enemigosMasMas() {
    if(hit){
        enemigos++;
        if(level!=4){
            exp+=250;
        } 
        return true;
    }
    else{
        return false;
    }
}

