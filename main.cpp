/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: pablomanez
 *
 * Created on 21 de febrero de 2018, 15:28
 */

#include <cstdlib>
#include <iostream>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <math.h>

#include "Tile.h"
#include "physicsEngine.h"
#include "renderEngine.h"

#define FRAMERATE 60
#define TICKS_PER_SEC 60.0

#define TIME_STEP 1.0/TICKS_PER_SEC
#define CAM_H 1250

#define force 200
#define speed 15.f
#define jump 2500

#define PLAYER_DIM_X 1.9f
#define PLAYER_DIM_Y 1.9f

using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {

    renderEngine* sfml;
    sfml->Instance(); //CREO EL SINGLETON, SE CREA ADEMAS LA WINDOW
    
    //41 - 6
    
    //TEST
    int finisher;
    std::string test  = "Tes:LUJAN:MoarTesting";
    std::string out;
    finisher = test.find_first_of(":");
    out.append(test, finisher+1, test.size());
    test.erase(finisher);

    std::cout << "OUT " << out << std::endl;
    std::cout << "TEST " << test << std::endl;
    //TEST
    
    
    
    physicsEngine* world;
    world->Instance();  //Creo el Singleton en la primera llamada a Instancia
    world->Instance().setGravity(0.f, 100.f);
    
    physicsEngine::pBody player = world->Instance().createBody(76.f, 64.f, 2400, 1200, 'D');
    //player.setFixedRotation(false);
    
    //MUNDO
    Tile *tile;
    tile->Instance();
    tile->Instance().CreaMapa();

    
    //38x32
    renderEngine::rTexture boxTexture("assets/prueba.png");
    renderEngine::rSprite Sprite;
    Sprite.setTexture(boxTexture);
    Sprite.setOrigin(19.f, 16.f);
    Sprite.setScale(-PLAYER_DIM_X, PLAYER_DIM_Y);
    
    //VISTA
    renderEngine::rView view(0,0,sfml->Instance().getSize()[0],sfml->Instance().getSize()[1]);
    //view.zoom(2.7);
    view.zoom(2);
    sfml->Instance().setView(view);
    
    renderEngine::rClock masterClock;
    double dt;
    bool keys[256];
    for(int i = 0; i<256; i++) keys[i]=false;
    
    float accumulator = 0.0f;
    masterClock.restart();

    
    while(sfml->Instance().isOpen()){
        /*
        sf::Event event;
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::EventType::KeyPressed:
                    keys[event.key.code] = true;
                    break;
                case sf::Event::EventType::KeyReleased:
                    keys[event.key.code] = false;     
                    break;
                default:
                    break;
            }
            
        }
        
        //UPDATE
        
        
        // FIXED TIME STEP UPDATE
        dt = masterClock.restart().asSeconds();
        //Spiral of death
        if(dt > 0.25f)   dt = 0.25f;
        
        accumulator+=dt;
        while(accumulator >= TIME_STEP){
            //std::cout << "UPDATE " << accumulator << std::endl;
            
            if(keys[16]) window.close();  //Cerrar

            if( keys[0])  {                 // A
                if(player.getLinearXVelocity() > -speed)
                    player.addForceToCenter(-force, player.getLinearYVelocity()); 
                else 
                    player.setLinealVelocicity(-speed, player.getLinearYVelocity());
                
                Sprite.setScale(PLAYER_DIM_X, PLAYER_DIM_Y); 
            }
            
            else if( keys[3]) {             //D
                if(player.getLinearXVelocity() < speed)
                    player.addForceToCenter(force, player.getLinearYVelocity()); 
                else
                    player.setLinealVelocicity(speed, player.getLinearYVelocity());

                Sprite.setScale(-PLAYER_DIM_X, PLAYER_DIM_Y); 
            }
            
            
            if(!keys[0] && !keys[3])   //W
                player.setLinealVelocicity(0, player.getLinearYVelocity());
            
            if(keys[57] || keys[22]){
                keys[57] = false;
                keys[22] = false;
                player.addForceToCenter(0, -jump*TICKS_PER_SEC/60);
            }
            
            
            //std::cout << "V " << player.getLinearXVelocity() << std::endl;
            
            world->Instance().updateWorld(TIME_STEP);
            accumulator -= TIME_STEP;
        }
        
        
        double tick = accumulator/dt;
        
        //std::cout << "RENDER == " << tick << std::endl;
        */
        sfml->Instance().clear('y');
        
        //Sprite.setPosition(player.getXPosition(), player.getYPosition());
        Sprite.setPosition(100,100);
        Sprite.setRotation(player.getRotation());
        /*
        //DRAW
        tile->Instance().DibujaCasillas(window, Sprite.getPosition().x, CAM_H);
        view.setCenter(Sprite.getPosition().x,CAM_H);
        
        window.setView(view);
        */
        Sprite.draw();
                
        //RENDER
        
        sfml->Instance().display();


    }
    
    return 0;
}

/*
//MAIN SIN FAÇADE
int main(int argc, char** argv) {

    sf::RenderWindow window(sf::VideoMode(1920,1080),"Carga de mapa",sf::Style::Default);
    window.setFramerateLimit(60);
    //41 - 6
    
    
    int finisher;
    std::string test  = "Tes:LUJAN:MoarTesting";
    std::string out;
    finisher = test.find_first_of(":");
    out.append(test, finisher+1, test.size());
    test.erase(finisher);

    std::cout << "OUT " << out << std::endl;
    std::cout << "TEST " << test << std::endl;
    
    physicsEngine* world;
    world->Instance();  //Creo el Singleton en la primera llamada a Instancia
    world->Instance().setGravity(0.f, 100.f);
    
    physicsEngine::pBody player = world->Instance().createBody(76.f, 64.f, 2400, 1200, 'D');
    //player.setFixedRotation(false);
    
    //MUNDO
    Tile *tile;
    tile->Instance();
    
    tile->Instance().CreaMapa();
    
    //38x32
    sf::Texture boxTexture;
    boxTexture.loadFromFile("assets/prueba.png");
    sf::Sprite Sprite;
    Sprite.setTexture(boxTexture);
    Sprite.setOrigin(19.f, 16.f);
    Sprite.setScale(-PLAYER_DIM_X, PLAYER_DIM_Y);
    
    //VISTA
    sf::View view(sf::FloatRect(0,0,window.getSize().x,window.getSize().y));

    //view.zoom(2.7);
    view.zoom(2);
    window.setView(view);
    
    sf::Clock masterClock;
    double dt;
    bool keys[256];
    for(int i = 0; i<256; i++) keys[i]=false;
    
    float accumulator = 0.0f;
    masterClock.restart();

    
    
    while(window.isOpen()){
        
        sf::Event event;
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::EventType::KeyPressed:
                    keys[event.key.code] = true;
                    break;
                case sf::Event::EventType::KeyReleased:
                    keys[event.key.code] = false;     
                    break;
                default:
                    break;
            }
            
        }
        
        //UPDATE
        
        
        // FIXED TIME STEP UPDATE
        dt = masterClock.restart().asSeconds();
        //Spiral of death
        if(dt > 0.25f)   dt = 0.25f;
        
        accumulator+=dt;
        while(accumulator >= TIME_STEP){
            //std::cout << "UPDATE " << accumulator << std::endl;
            
            if(keys[16]) window.close();  //Cerrar

            if( keys[0])  {                 // A
                if(player.getLinearXVelocity() > -speed)
                    player.addForceToCenter(-force, player.getLinearYVelocity()); 
                else 
                    player.setLinealVelocicity(-speed, player.getLinearYVelocity());
                
                Sprite.setScale(PLAYER_DIM_X, PLAYER_DIM_Y); 
            }
            
            else if( keys[3]) {             //D
                if(player.getLinearXVelocity() < speed)
                    player.addForceToCenter(force, player.getLinearYVelocity()); 
                else
                    player.setLinealVelocicity(speed, player.getLinearYVelocity());

                Sprite.setScale(-PLAYER_DIM_X, PLAYER_DIM_Y); 
            }
            
            
            if(!keys[0] && !keys[3])   //W
                player.setLinealVelocicity(0, player.getLinearYVelocity());
            
            if(keys[57] || keys[22]){
                keys[57] = false;
                keys[22] = false;
                player.addForceToCenter(0, -jump*TICKS_PER_SEC/60);
            }
            
            
            //std::cout << "V " << player.getLinearXVelocity() << std::endl;
            
            world->Instance().updateWorld(TIME_STEP);
            accumulator -= TIME_STEP;
        }
        
        
        double tick = accumulator/dt;
        
        //std::cout << "RENDER == " << tick << std::endl;
        window.clear(sf::Color::Yellow);
        
        Sprite.setPosition(player.getXPosition(), player.getYPosition());
        Sprite.setRotation(player.getRotation());
        
        //DRAW
        tile->Instance().DibujaCasillas(window, Sprite.getPosition().x, CAM_H);
        view.setCenter(Sprite.getPosition().x,CAM_H);
        
        window.draw(Sprite);
        window.setView(view);
                
        //RENDER
        
        window.display();
        


    }
    
    return 0;
}

*/
