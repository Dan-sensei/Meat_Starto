/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   xPlotato.cpp
 * Author: dan
 * 
 * Created on 9 de abril de 2018, 8:27
 */

#include <complex>
#include "../../../Juego.h"
#include "xPlotato.h"
#include "math.h"

#define velocity 2.f

xPlotato::xPlotato(int x_, int y_, int x_b, int x_e) : animator(sprite) {
    //std::cout << "Creando xPlotato" << std::endl;

    std::string sprite_name = "assets/potatoboy1.png";
    /*ANIMACIONES*/
    Animator::Animation*  base = &animator.CreateAnimation("base","assets/potatoboy1.png", renderEngine::rTime(1), false);
    base->AddFrames(sf::Vector2i(0,420), sf::Vector2i(65,65) ,1);
    animator.SwitchAnimation("base");
    
    
    Animator::Animation*  xplota = &animator.CreateAnimation("xplota","assets/potatoboy1.png", renderEngine::rTime(0.5), false);
    xplota->AddFrames(sf::Vector2i(0,0), sf::Vector2i(225,140) ,4);
    xplota->AddFrames(sf::Vector2i(0,140), sf::Vector2i(225,140) ,5);    
    
    int width = 65;
    int height = 65;


    sprite.setOrigin(width / 2, height / 2);
    sprite.setPosition(x_, y_);
    
    t = new physicsEngine::type;
    t->id = 3;
    t->data = this;
    
    //body = world->Instance().createBody(width, height, x_, y_, 'K');
    body = physicsEngine::Instance().createBody(width, height, x_, y_, 'd', t);

    body.setUserData(t);
    

    //Zona en la que se puede mover teniendo en cuenta el ancho del sprite
    x_begin = x_b + width/2;
    x_end = x_e - width/2;
    
    target = x_begin;
    
    hp = 1;
    
    previous.x = actual.x = body.getXPosition();
    previous.y = actual.y = body.getYPosition();
    previous.r = actual.r = body.getRotation();
    
    xplotar = false;
    alive = true;
    readyToDie = false;
    
 
    xPlosion1.setBuffer(AssetManager::GetSoundBuffer("assets/Sounds/Explosion1.ogg"));
    xPlosion2.setBuffer(AssetManager::GetSoundBuffer("assets/Sounds/Explosion2.ogg"));
}

xPlotato::xPlotato(const xPlotato& orig): animator(sprite) {
    t = orig.t;
    x_begin = orig.x_begin;
    x_end = orig.x_end;
    target = orig.target;
    
    hp = orig.hp;
    sprite = orig.sprite;
    body = orig.body;
    previous = orig.previous;
    actual = orig.actual;
}

xPlotato::~xPlotato() {
    //std::cout << "Destruyendo xPlotato..." << std::endl;
    delete t;
    t = nullptr;
}

void xPlotato::update(){
    if(!readyToDie){
        std::vector<Player*>* players = Juego::Instance().getPlayers();
        //GOLPEO DEL PERSONAJE
        for(int i=0 ; i<players->size() ; i++){
            Player* ready = (*players)[i];
            
            if(ready->getMano().intersects(sprite)){
                alive = !ready->enemigosMasMas();
            }
        }
        
        //PROXIMIDAD POR PERSONAJE

        for(int i=0 ; i<players->size() ; i++){
            Player* ready = (*players)[i];
            
            if(!ready->getEscudo()){
                if(ready->getSprite().intersects(sprite)){
                    sprite.setOrigin(112,120);
                    sprite.setRotation(0);
                    sprite.setScale(2.5, 2.5);
                    body.setLinealVelocicity(0, body.getLinearYVelocity());
                    if(animator.GetCurrentAnimationName()!="xplota"){
                        animator.SwitchAnimation("xplota");
                    }
                    
                    if(!ready->isInmortal())
                        Mapa::Instance().movePlayerToClosestCheckPoint(ready);
                    
                    int randomSound = physicsEngine::Instance().genIntRandom(0, 1);
                    (randomSound == 0) ? xPlosion1.play() : xPlosion2.play();
                    readyToDie = true;
                    physicsEngine::Instance().detroyBody(body);
                    xclock.restart();
                }
            }
            else{
                ready->setEscudo(false);
            }
        }

        if(xplotar && !readyToDie){
            direccion();
            //std::cout << xclock.getElapsedTime().asSeconds() << std::endl;
            if(xclock.getElapsedTime().asSeconds() > 2.8){
                sprite.setOrigin(112,120);
                sprite.setRotation(0);
                sprite.setScale(2.5, 2.5);
                body.setLinealVelocicity(0, body.getLinearYVelocity());
                if(animator.GetCurrentAnimationName()!="xplota"){
                    animator.SwitchAnimation("xplota");
                }
                readyToDie = true;
                int randomSound = physicsEngine::Instance().genIntRandom(0, 1);
                (randomSound == 0) ? xPlosion1.play() : xPlosion2.play();
                physicsEngine::Instance().detroyBody(body);
                xclock.restart();
            }
            else{
                if(body.getLinearXVelocity() > 0)
                    sprite.rotate(17);
                else
                    sprite.rotate(-17);
            }

        }

        if(!xplotar && !readyToDie){
            persigue();

            if(abs(body.getLinearXVelocity()) < 1){
                body.setLinealVelocicity(-velocity, body.getLinearYVelocity());
                sprite.setScale(-1, 1);
            }

            if(target == x_begin && body.getXPosition() <= target ){
                target = x_end;
                body.setLinealVelocicity(velocity, body.getLinearYVelocity());
                sprite.setScale(1, 1);

            }
            else if(target == x_end && body.getXPosition() >= target){
                target = x_begin;
                body.setLinealVelocicity(-velocity, body.getLinearYVelocity());
                sprite.setScale(-1, 1);
            }

            if(body.getLinearXVelocity() > 0)
                sprite.rotate(10);
            else
                sprite.rotate(-10);
        }
    
    }
    if(readyToDie && xclock.getElapsedTime().asSeconds() > 2){
        alive = false;
    }
    
    animator.Update(animationClock.restart());
    
    
}

void xPlotato::persigue() {
    int np = Juego::Instance().getPlayers()->size();
    int r = physicsEngine::Instance().genIntRandom(0,np-1);

    float x_ = (Juego::Instance().getPlayers()[0][r]->getXPosition()-sprite.getPosition()[0]);
    float y_ = (Juego::Instance().getPlayers()[0][r]->getYPosition()-sprite.getPosition()[1]);

    if(sqrt((x_*x_)+(y_*y_)) < 70*5){
        std::cout << "LA PATATA TE OBSERVA: " << Juego::Instance().getPlayers()[0][r]->getName() << std::endl;
        xplotar = true;
        pj = r;
        direccion();
        xclock.restart();
    }
}

void xPlotato::direccion() {
    if(sprite.getPosition()[0] > Juego::Instance().getPlayers()[0][pj]->getXPosition()){
        body.setLinealVelocicity(-4.f,body.getLinearYVelocity());
        //sprite.setScale(-1, 1);
    }
    else{
        body.setLinealVelocicity(4.f,body.getLinearYVelocity());
        //sprite.setScale(1, 1);
    }
}

void xPlotato::salta(int s) {
    float imp = -15;
    if(xplotar){
        if(s==1){
            //std::cout << "Salto hacia la derecha" << std::endl; 
            body.applyLinearImpulse(0,imp);
        }
        else if(s==0){
            //std::cout << "Salto hacia la izquierda" << std::endl;
            body.applyLinearImpulse(0,imp);
        }
        else if(s==-1){
            body.applyLinearImpulse(0,0);
        }
    }
}