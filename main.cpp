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

#define SCALE 30.f

using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {

    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height),"Carga de mapa",sf::Style::Default);
    //sf::RenderWindow window(sf::VideoMode(1920,1080),"Carga de mapa",sf::Style::Default);
    window.setFramerateLimit(60);
    //41 - 6
    Tile tile;
    tile.CreaMapa();
    
    //BOX2D EJEMPLO DE CUERPO DINAMICO
    b2Vec2 gravity(0.0f,-9.8f);                //VECTOR GRAVEDAD
    b2World world (gravity);                   //OBJETO 'MUNDO'
    
    b2BodyDef bodyDef;                         //CREO UN b2BodyDef Y LE ASIGNO UNA POSICION
    bodyDef.type = b2_dynamicBody;                      
    bodyDef.position.Set(0.0f,10.0f);
    
    b2Body *body = world.CreateBody(&bodyDef); //AÑADO EL b2Body AL MUNDO
    
    b2PolygonShape dBox;                       //CREO UNA FORMA PARA EL BODY Y LE DOY DIMENSION DE 10mx10m
    dBox.SetAsBox(5.0f,5.0f);
    
    b2FixtureDef fixDef;                       //CREO LA FIXTURE
    fixDef.shape = &dBox;
    fixDef.density = 1.0f;
    fixDef.friction = 3.0f;
    
    body->CreateFixture(&fixDef);
    
    //BOX2D EJEMPLO DE CUERPO ESTATICO
    /*
    b2BodyDef cajaDef;
    bodyDef.position.Set(0.0f,-5.0f);
    b2Body *caja = world.CreateBody(&cajaDef);
    
    b2PolygonShape cBox;
    cBox.SetAsBox(10.0f,2.0f);
    
    caja->CreateFixture(&cBox,0.0f);
    */
    

    
    
    //SPRITE PARA PROBAR
    sf::Sprite pl;
    sf::Texture text;
    text.loadFromFile("assets/prueba.png");
    pl.setTexture(text);
    pl.scale(sf::Vector2f(-1.9,1.9));
    pl.setOrigin(19,16);
    pl.setPosition(1000,1200);
    
    //MOVIMIENTO
    bool pl_d = false;
    bool pl_w = false;
    bool pl_a= false;
    bool pl_s = false;
    
    //VISTA
    sf::View view(sf::FloatRect(0,0,window.getSize().x,window.getSize().y));
    view.setCenter(pl.getPosition());
    //view.zoom(1.7);
    view.zoom(2.5);
    window.setView(view);
    
    
    float32 anterior = body->GetPosition().y;
    while(window.isOpen()){
        int mov = 20;
        
        sf::Event event;
        if(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::EventType::KeyPressed:
                        if(event.key.code == sf::Keyboard::Q){
                            window.close();
                        }
                        if(event.key.code == sf::Keyboard::D){
                            pl_d = true;
                        }
                        if(event.key.code == sf::Keyboard::A){
                            pl_a = true;
                        }
                        if(event.key.code == sf::Keyboard::W){
                            pl_w = true;
                        }
                        if(event.key.code == sf::Keyboard::S){
                            pl_s = true;
                        }
                    break;
                case sf::Event::EventType::KeyReleased:
                    if(event.key.code == sf::Keyboard::D){
                        pl_d = false;
                    }
                    if(event.key.code == sf::Keyboard::A){
                        pl_a = false;
                    }
                    if(event.key.code == sf::Keyboard::W){
                        pl_w = false;
                    }
                    if(event.key.code == sf::Keyboard::S){
                        pl_s = false;
                    }
                    
                    break;
                default:
                    break;
            }
            
        }
        
        //UPDATE
        
        if(pl_d){
            pl.move(mov,0);
        }
        if(pl_a){
            pl.move(-mov,0);
        }
        if(pl_w){
            pl.move(0,-mov);
        }
        if(pl_s){
            pl.move(0,mov);
        }
        
        /*
        world.Step(1.0f/60.0f,6,2);
        pl.move(sf::Vector2f(0,anterior-body->GetPosition().y));
        float32 anterior = body->GetPosition().y;
        cout << "x: " << body->GetPosition().x << " | y: " << body->GetPosition().y <<endl;
        */
        
        
        
        view.setCenter(pl.getPosition().x,1200);
        window.setView(view);
        
        //RENDER
        
        window.clear(sf::Color::Yellow);
        
        tile.DibujaCasillas(window,pl.getPosition().x,1200);
        
        window.draw(pl);
        
        window.display();
        
    }
    
    return 0;
}

