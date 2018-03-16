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

#include "Tile.h"
#include "physicsEngine.h"

#define SCALE 65.f
#define FRAMERATE 60
#define TICKS_PER_SEC 60.0
#define TIME_STEP 1.0/TICKS_PER_SEC

#define speed 10
#define jump 1000

using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {

    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height),"Carga de mapa",sf::Style::Default);
    //sf::RenderWindow window(sf::VideoMode(1920,1080),"Carga de mapa",sf::Style::Default);
    window.setFramerateLimit(60);
    //41 - 6
    
    physicsEngine* world;
    world->Instance();  //Creo el Singleton en la primera llamada a Instancia
    
    physicsEngine::body player = world->Instance().createBody(38.f, 32.f, 1200, 1200, 'D');
 
    
    Tile tile;
    tile.CreaMapa();
    
    //38x32
    
    sf::Texture boxTexture;
    boxTexture.loadFromFile("assets/prueba.png");
    sf::Sprite Sprite;
    Sprite.setTexture(boxTexture);
    Sprite.setOrigin(19.f, 16.f);
    Sprite.setScale(-1.9, 1.9);
    
    //VISTA
    sf::View view(sf::FloatRect(0,0,window.getSize().x,window.getSize().y));

    //view.zoom(2.7);
    view.zoom(1.7);
    window.setView(view);
    
    sf::Clock masterClock;
    double dt;
    bool keys[256];
    for(int i = 0; i<256; i++) keys[i]=false;
    
    float accumulator = 0.0f;
    masterClock.restart();

    
    while(window.isOpen()){
        
        sf::Event event;
        if(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::EventType::KeyPressed:
                    keys[event.key.code] = true;
                        //std::cout << event.key.code << std::endl;
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

            /* IZQ */ if( keys[0])  {        player.setLinealVelocicty(-speed, player.getLinearVelocityY()); Sprite.setScale(2, 2); } 
            /* DER */ else if( keys[3]) {    player.setLinealVelocicty(speed, player.getLinearVelocityY()); Sprite.setScale(-2, 2);}
            /* STOP */ else if(!keys[0] && !keys[3]) player.setLinealVelocicty(0, player.getLinearVelocityY());
                
            if(keys[57] || keys[22]){
                keys[57] = false;
                keys[22] = false;
                player.addForceToCenter(0, -jump*TICKS_PER_SEC/60);
            }
            
            world->Instance().updateWorld(TIME_STEP);
            accumulator -= TIME_STEP;
        }
        
     
        double tick = accumulator/dt;
        
        //std::cout << "RENDER == " << tick << std::endl;
        window.clear(sf::Color::Yellow);
        
        Sprite.setPosition(player.getXPosition(), player.getYPosition());
        Sprite.setRotation(player.getRoation());
        
        tile.DibujaCasillas(window, Sprite.getPosition().x, Sprite.getPosition().y);

        view.setCenter(Sprite.getPosition());
        window.draw(Sprite);
        window.setView(view);
                

        //RENDER
        
        window.display();
        
    }
    
    return 0;
}

