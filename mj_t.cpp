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

mj_t::mj_t() {}

void mj_t::init(int x_) {
    //LE PASO LA x_max DE TILE
    x_max = x_;
    x_min = x_ - 19*70; //LONTIGUD YA PREFEDINIDA DE TILED
                        //CUANDO LLEGUE A LA MITAD DEL MINIJUEGO EMPIEZA
    
    restart = false;
    on = false;
    fin = false;
    
    //CREO LOS DOS MUROS (EN REALIDAD AHORA SOLO CREO UNO, JK)
    int a = 70; //ANCHO TILE
    float x = x_max-(6*a);
    float y = a*2;
    int n = 26;
    
    physicsEngine *world;
    std::array<float,2> arr;
    
    m1.convex.setPointCount(5);
    m1.convex.setPoint(0,x,y);
    m1.convex.setPoint(1,x+a,y);
    m1.convex.setPoint(2,x+a,y+(a*n));
    m1.convex.setPoint(3,x,y+(a*n));
    m1.convex.setPoint(4,x,y);
    m1.convex.setFillColor('r');
    
    //SE NECESITA HACER UN METODO EN physicsEngine PARA DESTRUIR
    //EL BODY Y EL FIXTURE DEL QUE FORMAN LAS COLISIONES DE LOS DOS MUROS
    /*
    arr = {x    ,   y       };  m1.v.push_back(arr);
    arr = {x+a  ,   y       };  m1.v.push_back(arr);
    arr = {x+a  ,   y+(a*n) };  m1.v.push_back(arr);
    arr = {x    ,   y+(a*n) };  m1.v.push_back(arr);
    arr = {x    ,   y       ];  m1.v.push_back(arr);
    
    world->Instance().createGround(m1.v,m1.v.size());
    */
    
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
                    //std::cout << "REINICIO RELOJ" << std::endl;
                clock.restart();
                restart = true;
            }
            else{
                std::cout << "  Tiempo TETRIS: " << clock.getElapsedTime().asSeconds() << std::endl;
            }
            
            //MUEVO LAS PIEZAS
            int des = 1200;
            for(int i = 0 ; i<v_piezas.size() ; i++){
                if(v_piezas[i].c.getPosition()[1] < des){
                    v_piezas[i].c.move(0,5);
                }
                else{
                    v_piezas[i].c.setPosition(x_min, 2000);
                }
            }
            
            if(clock.getElapsedTime().asSeconds() > 15){
                fin = true;
                on = false;
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
    if(on == true){
        m1.convex.draw();
        
        for(int i = 0 ; i<v_piezas.size() ; i++){
            v_piezas[i].c.draw();
        }
    }
}






mj_t::mj_t(const mj_t& orig) {
}