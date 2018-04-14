/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mj_t.cpp
 * Author: pablomanez
 * 
 * Created on 1 de abril de 2018, 10:50
 */

#include <iostream>
#include "mj_t.h"
#include <random>

#define DES 700

mj_t::mj_t() {}

void mj_t::init(int x_) {
    //LE PASO LA x_max DE TILE
    x_max = x_;
    x_min = x_ - 19*70; //LONTIGUD YA PREFEDINIDA DE TILED
                        //CUANDO LLEGUE A LA MITAD DEL MINIJUEGO EMPIEZA
    
    restart = false;
    on = false;
    fin = false;
    
    //------ CREO LOS DOS MUROS ------//
    physicsEngine *world;
    //  MURO1 (DERECHA)
    int a = 70; //ANCHO TILE
    float x = x_max-(6*a);
    float y = a*2;
    int n = 23;
    
    m1.rect.setSize(a,a*n);
    m1.rect.setPosition(x,y);
    m1.rect.setFillColor('k');
    
    y = a;
    m1.pb = world->Instance().createBody(a,a*44,x+(m1.rect.getSize()[0]/2),y-DES+(m1.rect.getSize()[1]/2),'k');
    m1.pb.setUserData((void*)"Pared");
    float px = m1.pb.getXPosition();
    float py = m1.pb.getYPosition();
    m1.rect.setPosition(x,py);
    
    
    //  MURO2 (IZQUIERDA)
    x = x_min-(16*a);
    y = a*2;
    n = 23;
        
    m2.rect.setSize(a,a*n);
    m2.rect.setPosition(x,y);
    m2.rect.setFillColor('k');
    
    y = a;
    m2.pb = world->Instance().createBody(a,a*44,x+(m2.rect.getSize()[0]/2),y-DES+(m2.rect.getSize()[1]/2),'k');
    
    px = m2.pb.getXPosition();
    py = m2.pb.getYPosition();
    m2.rect.setPosition(x,py);
    
    //m1.text.loadFromFile("assets/tetris/t_tetris.png");
    //m2.text.loadFromFile("assets/tetris/t_tetris.png");
    
    /*
    //CREO LAS PIEZAS
    for(int i = 0 ; i<100 ; i++){
        crearPieza();
    }
    */
    
}

void mj_t::crearPieza() {
    physicsEngine *world;
    

    //GENERO EL NUMERO ALEATORIO
    //std::uniform_real_distribution<float> dv(4,8);
    
    //RANDOM
    int rx = physicsEngine::Instance().genIntRandom(0, 24);
    int np = physicsEngine::Instance().genIntRandom(0, 6);
    float rv = physicsEngine::Instance().genFloatRandom(8, 10);
    int nt;
    
    //COORD
    int a = 70;
    int x = rx*70+(x_min-(16*70))+(a);
    int y = 0;
    
    int x2, y2;
    
    //PIEZAS
    pieza_ *p = new pieza_;
    p->vel = rv;
    
    for(int i=0 ; i<4 ; i++){
        nt = physicsEngine::Instance().genIntRandom(0, 6);
        p->r[i].setFillColor('r');
        p->r[i].setSize(a,a);
        switch(nt){
            case 1:
                p->t[i].loadFromFile("tiles_definitivo/tiles/slice03_03_1.png");
                break;
            case 2:
                p->t[i].loadFromFile("tiles_definitivo/tiles/slice03_03_2.png");
                break;
            case 3:
                p->t[i].loadFromFile("tiles_definitivo/tiles/slice03_03_3.png");
                break;
            case 4:
                p->t[i].loadFromFile("tiles_definitivo/tiles/slice03_03_4.png");
                break;
            case 5:
                p->t[i].loadFromFile("tiles_definitivo/tiles/slice03_03_5.png");
                break;
            case 6:
                p->t[i].loadFromFile("tiles_definitivo/tiles/slice03_03.png");
                break;
            default:
                p->t[i].loadFromFile("tiles_definitivo/tiles/slice03_03_1.png");
                break;
        }
    }
    switch(np){
        case 1:
            //I
            x2 = x;
            y2 = y;
            p->r[0].setPosition(x2,y2);

            x2 = x+a;
            y2 = y;
            p->r[1].setPosition(x2,y2);

            x2 = x+(a*2);
            y2 = y;
            p->r[2].setPosition(x2,y2);

            x2 = x+(a*3);
            y2 = y;
            p->r[3].setPosition(x2,y2);
            
            break;
        case 2:
            //L NORMAL
            x2 = x;
            y2 = y;
            p->r[0].setPosition(x2,y2);

            x2 = x+a;
            y2 = y;
            p->r[1].setPosition(x2,y2);

            x2 = x+(a*2);
            y2 = y;
            p->r[2].setPosition(x2,y2);

            x2 = x+(a*2);
            y2 = y-a;
            p->r[3].setPosition(x2,y2);
            
            break;
        case 3:
            //T
            x2 = x;
            y2 = y;
            p->r[0].setPosition(x2,y2);

            x2 = x+a;
            y2 = y;
            p->r[1].setPosition(x2,y2);

            x2 = x+(a*2);
            y2 = y;
            p->r[2].setPosition(x2,y2);

            x2 = x+a;
            y2 = y+a;
            p->r[3].setPosition(x2,y2);
            
            break;
        case 4:
            //Z
            x2 = x;
            y2 = y;
            p->r[0].setPosition(x2,y2);

            x2 = x+a;
            y2 = y;
            p->r[1].setPosition(x2,y2);

            x2 = x+a;
            y2 = y+a;
            p->r[2].setPosition(x2,y2);

            x2 = x+(a*2);
            y2 = y+a;
            p->r[3].setPosition(x2,y2);
            
            break;
        case 5:
            //S
            x2 = x;
            y2 = y;
            p->r[0].setPosition(x2,y2);

            x2 = x;
            y2 = y+a;
            p->r[1].setPosition(x2,y2);

            x2 = x+a;
            y2 = y+a;
            p->r[2].setPosition(x2,y2);

            x2 = x+a;
            y2 = y+(a*2);
            p->r[3].setPosition(x2,y2);
            
            break;
        case 6:
            //O
            x2 = x;
            y2 = y;
            p->r[0].setPosition(x2,y2);

            x2 = x+a;
            y2 = y;
            p->r[1].setPosition(x2,y2);

            x2 = x;
            y2 = y+a;
            p->r[2].setPosition(x2,y2);

            x2 = x+a;
            y2 = y+a;
            p->r[3].setPosition(x2,y2);
            
            break;
    }
    
    //p->c.setFillColor('r');
    //p->c.setOutlineColor('r');
    //p->c.setOutlineThickness(7);
    v_piezas.push_back(*p);
    
    delete p;
}

void mj_t::update() {
    renderEngine *sfml;
    
    int x_ = sfml->Instance().getViewCenter()[0];
    
    if(!fin){
        if(x_ > x_min && x_ < x_max){
            //ACTUALIZO EL MINIJUEGO
                //std::cout << "Estoy dentro del tetris wey" << std::endl;
            on = true;

            if(restart == false){
                //(RE)INICIO DEL JUEGO
                    //std::cout << "REINICIO RELOJ" << std::endl;
                clock.restart();
                dt.restart();
                
                restart = true;
            }
            else{
                //std::cout << "  Tiempo TETRIS: " << clock.getElapsedTime().asSeconds() << std::endl;
            }
            
            //MUEVO LOS MUROS (BOX2D+SFML)
            if(m2.pb.getYPosition()>500){
                m2.pb.setLinealVelocicity(0,0);
            }
            else{
                m2.pb.setLinealVelocicity(0,5);
                m2.rect.setPosition(m2.rect.getPosition()[0],m2.pb.getYPosition());
            }
            
            if(m1.pb.getYPosition()>500){
                m1.pb.setLinealVelocicity(0,0);
            }
            else{
                m1.pb.setLinealVelocicity(0,5);
                m1.rect.setPosition(m1.rect.getPosition()[0],m1.pb.getYPosition());
            }
            
            //CREO LAS PIEZAS
            if(dt.getElapsedTime().asSeconds() >= 0.2 && clock.getElapsedTime().asSeconds() < 55){
                std::cout << "CREO PIEZA: " << clock.getElapsedTime().asSeconds() << std::endl;
                dt.restart();
                crearPieza();
            }
            
            //MUEVO LAS PIEZAS
            int fin_pieza = 5000;
            float v = 0.5f;
            
            for(int i = 0 ; i<v_piezas.size() ; i++){
                for(int j=0 ; j<4 ; j++){
                    if(v_piezas[i].r[j].getPosition()[1] < fin_pieza){
                        if(clock.getElapsedTime().asSeconds()<20){
                            v_piezas[i].r[j].move(0,v_piezas[i].vel);
                        }
                        else if(clock.getElapsedTime().asSeconds()<40){
                            v_piezas[i].r[j].move(0,v_piezas[i].vel+v);
                        }
                        else if(clock.getElapsedTime().asSeconds()<50){
                            v_piezas[i].r[j].move(0,v_piezas[i].vel+(v*2));
                        }
                        else{
                            v_piezas[i].r[j].move(0,v_piezas[i].vel+(v*10));
                        }
                    }
                    else{
                        v_piezas[i].r[j].setPosition(x_min, 2000);
                    }
                }
            }
            
            //DETECTA EL FIN DEL MINIJUEGO
            if(clock.getElapsedTime().asSeconds() > 60){
                fin = true;
                on = false;
                
                v_piezas.clear();
                m1.pb.setLinealVelocicity(0,-20);
                m1.rect.setPosition(m1.rect.getPosition()[0],-140);
            }
        }
        else if(x_ < x_min || x_ > x_max){
            on = false;
        }
    }
}

bool mj_t::isTetrisOn() {
    return on;
}

void mj_t::render() {
    m1.rect.draw(); 
    m2.rect.draw(); 
    
    if(on){
        for(int i = 0 ; i<v_piezas.size() ; i++){
            for(int j = 0 ; j<4 ; j++){
                v_piezas[i].r[j].setTexture(v_piezas[i].t[j]);
                v_piezas[i].r[j].draw();
            }
        }
    }
}






mj_t::mj_t(const mj_t& orig) {
}