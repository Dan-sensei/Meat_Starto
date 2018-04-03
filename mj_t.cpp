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
    m1.rect.setFillColor('b');
    
    y = a;
    m1.pb = world->Instance().createBody(a,a*44,x+(a/2),y-DES,'k');
    
    float px = m1.pb.getXPosition();
    float py = m1.pb.getYPosition();
    m1.rect.setPosition(x,py);
    
    
    //  MURO2 (IZQUIERDA)
    x = x_min-(16*a);
    y = a*2;
    n = 23;
        
    m2.rect.setSize(a,a*n);
    m2.rect.setPosition(x,y);
    m2.rect.setFillColor('b');
    
    y = a;
    m2.pb = world->Instance().createBody(a,a*44,x+(a/2),y-DES,'k');
    
    px = m2.pb.getXPosition();
    py = m2.pb.getYPosition();
    m2.rect.setPosition(x,py);
    
    
    
    
    //CREO LAS PIEZAS
    for(int i = 0 ; i<1 ; i++){
        crearPieza();
    }
    
}

void mj_t::crearPieza() {
    //GENERO EL NUMERO ALEATORIO
    /*
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> distribution(0,n-1);
    */
    
    pieza_ *p = new pieza_;
    
    p->c.setPointCount(5);
    p->c.setPoint(0,x_min,0);
    p->c.setPoint(1,x_min+70,0);
    p->c.setPoint(2,x_min+70,0+70);
    p->c.setPoint(3,x_min,0+70);
    p->c.setPoint(4,x_min,0);
    p->c.setFillColor('g');
    
    v_piezas.push_back(*p);
    
    delete p;
}

void mj_t::update(int x_) {
    if(!fin){
        if(x_ > x_min && x_ < x_max){
            //ACTUALIZO EL MINIJUEGO
                //std::cout << "Estoy dentro del tetris wey" << std::endl;
            on = true;

            if(restart == false){
                //(RE)INICIO DEL JUEGO
                    //std::cout << "REINICIO RELOJ" << std::endl;
                clock.restart();
                restart = true;
            }
            else{
                std::cout << "  Tiempo TETRIS: " << clock.getElapsedTime().asSeconds() << std::endl;
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
            
            //MUEVO LAS PIEZAS
            int fin_pieza = 1500;
            for(int i = 0 ; i<v_piezas.size() ; i++){
                if(v_piezas[i].c.getPosition()[1] < fin_pieza){
                    v_piezas[i].c.move(0,7);
                }
                else{
                    v_piezas[i].c.setPosition(x_min, 2000);
                }
            }
            
            //DETECTA EL FIN DEL MINIJUEGO
            if(clock.getElapsedTime().asSeconds() > 15){
                fin = true;
                on = false;
                
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
    
    if(on == true){
        for(int i = 0 ; i<v_piezas.size() ; i++){
            v_piezas[i].c.draw();
        }
    }
}






mj_t::mj_t(const mj_t& orig) {
}