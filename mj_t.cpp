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
    m2.rect.setFillColor('k');
    
    y = a;
    m2.pb = world->Instance().createBody(a,a*44,x+(a/2),y-DES,'k');
    
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
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> dx(0,24);
    std::uniform_int_distribution<int> dp(0,6);
    
    //std::uniform_real_distribution<float> dv(4,8);
    std::uniform_real_distribution<float> dv(8,10);
    
    //RANDOM
    int rx = dx(gen);
    int np = dp(gen);
    float rv = dv(gen);
    
    //COORD
    int a = 70;
    int x = rx*70+(x_min-(16*70))+(a);
    int y = 0;
    int xb = x+(a/2);
    //int yb = y+(a/2);
    int yb = y+a;
    
    int xb2;
    int yb2;
    int y2;
    int x2;
    
    //PIEZAS
    pieza_ *p = new pieza_;
    p->vel = rv;
    
    for(int i=0 ; i<4 ; i++){
        p->r[i].setSize(a,a);
        p->r[i].setFillColor('r');
    }
    switch(np){
        case 1:
            x2 = x;
            xb2 = xb;
            yb2 = yb;
            p->r[0].setPosition(x2,y);
            p->pb[0] = world->Instance().createBody(a,a,xb2,yb2,'k');

            x2 = x+a;
            xb2 = xb+a;
            yb2 = yb;
            p->r[1].setPosition(x2,y);
            p->pb[1] = world->Instance().createBody(a,a,xb2,yb2,'k');

            x2 = x+(a*2);
            xb2 = xb+(a*2);
            yb2 = yb;
            p->r[2].setPosition(x2,y);
            p->pb[2] = world->Instance().createBody(a,a,xb2,yb2,'k');

            x2 = x+(a*3);
            xb2 = xb+(a*3);
            yb2 = yb;
            p->r[3].setPosition(x2,y);
            p->pb[3] = world->Instance().createBody(a,a,xb2,yb2,'k');
            
            break;
        default:
            x2 = x;
            y2 = y;
            xb2 = xb;
            yb2 = yb;
            p->r[0].setPosition(x2,y2);
            p->pb[0] = world->Instance().createBody(a,a,xb2,yb2,'k');

            x2 = x+a;
            y2 = y;
            xb2 = xb+a;
            yb2 = yb;
            p->r[1].setPosition(x2,y2);
            p->pb[1] = world->Instance().createBody(a,a,xb2,yb2,'k');

            x2 = x;
            y2 = y+a;
            xb2 = xb;
            yb2 = yb+a;
            p->r[2].setPosition(x2,y);
            p->pb[2] = world->Instance().createBody(a,a,xb2,yb2,'k');

            x2 = x+a;
            y2 = y+a;
            xb2 = xb+a;
            yb2 = yb+a;
            p->r[3].setPosition(x2,y);
            p->pb[3] = world->Instance().createBody(a,a,xb2,yb2,'k');
            
            break;
    }
    
    
    
    
    
    
    /*
    switch(np){
        case 1:
            //I
            for(int i=0 ; i<1 ; i++){
                p->r[i].setSize(a,a);
            }
            p->r[0].setPosition(x,y);
            p->pb[0] = world->Instance().createBody(a,a,x,y,'k');




            p->c.setPointCount(5);
            p->c.setPoint(0,x,-y);
            p->c.setPoint(1,x+(a*4),-y);
            p->c.setPoint(2,x+(a*4),-y+a);
            p->c.setPoint(3,x,-y+a);
            p->c.setPoint(4,x,-y);
            
            p->t.loadFromFile("assets/tetris/1.png");
            //p->c.setFillColor('b');
            break;
        case 2:
            //Z
            p->c.setPointCount(9);
            p->c.setPoint(0,x,-y);
            p->c.setPoint(1,x+a,-y);
            p->c.setPoint(2,x+a,-y+(a*2));
            p->c.setPoint(3,x,-y+(a*2));
            p->c.setPoint(4,x,-y+(a*3));
            p->c.setPoint(5,x-a,-y+(a*3));
            p->c.setPoint(6,x-a,-y+a);
            p->c.setPoint(7,x,-y+a);
            p->c.setPoint(8,x,-y);
            
            p->t.loadFromFile("assets/tetris/3.png");
            //p->c.setFillColor('g');
            break;
        case 3:
            //L (AL REVES)
            p->c.setPointCount(11);
            p->c.setPoint(0,x,-y);
            p->c.setPoint(1,x+a,-y);
            p->c.setPoint(2,x+a,-y+a);
            p->c.setPoint(3,x+(a*2),-y+a);
            p->c.setPoint(4,x+(a*3),-y+a);
            p->c.setPoint(5,x+(a*3),-y+(a*2));
            p->c.setPoint(6,x+(a*2),-y+(a*2));
            p->c.setPoint(7,x+a,-y+(a*2));
            p->c.setPoint(8,x,-y+(a*2));
            p->c.setPoint(9,x,-y+a);
            p->c.setPoint(10,x,-y);

            p->t.loadFromFile("assets/tetris/4.png");
            //p->c.setFillColor('k');
            break;
        case 4:
            //L (NORMAL)
            p->c.setPointCount(7);
            p->c.setPoint(0,x,-y);
            p->c.setPoint(1,x+(a*2),-y);
            p->c.setPoint(2,x+(a*2),-y+(a*3));
            p->c.setPoint(3,x+a,-y+(a*3));
            p->c.setPoint(4,x+a,-y+a);
            p->c.setPoint(5,x,-y+a);
            p->c.setPoint(6,x,-y);
            
            p->t.loadFromFile("assets/tetris/2.png");
            //p->c.setFillColor('m');
            break;
        default:
            //O
            p->c.setPointCount(5);
            p->c.setPoint(0,x,-y);
            p->c.setPoint(1,x+(a*2),-y);
            p->c.setPoint(2,x+(a*2),-y+(a*2));
            p->c.setPoint(3,x,-y+(a*2));
            p->c.setPoint(4,x,-y);
            
            p->t.loadFromFile("assets/tetris/t_tetris.png");
            //p->c.setFillColor('y');
            break;
    }
    */
    
    
    
    
    
    //p->c.setFillColor('r');
    //p->c.setOutlineColor('r');
    //p->c.setOutlineThickness(7);
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
            if(dt.getElapsedTime().asSeconds() >= 0.5 && clock.getElapsedTime().asSeconds() < 55){
                std::cout << "CREO PIEZA: " << clock.getElapsedTime().asSeconds() << std::endl;
                dt.restart();
                crearPieza();
            }
            
            //MUEVO LAS PIEZAS
            int fin_pieza = 5000;
            float v = 0.5f;
            
            int x;
            int y;
            for(int i = 0 ; i<v_piezas.size() ; i++){
                for(int j=0 ; j<4 ; j++){
                    v_piezas[i].pb[j].setLinealVelocicity(0,3);
                    
                    x = v_piezas[i].pb[j].getXPosition();
                    y = v_piezas[i].pb[j].getYPosition();
                    
                    v_piezas[i].r[j].setPosition(x,y);
                }
                
                /*
                if(v_piezas[i].c.getPosition()[i] < fin_pieza){
                    if(clock.getElapsedTime().asSeconds()<20){
                        v_piezas[i].c.move(0,v_piezas[i].vel);
                    }
                    else if(clock.getElapsedTime().asSeconds()<40){
                        v_piezas[i].c.move(0,v_piezas[i].vel+v);
                    }
                    else if(clock.getElapsedTime().asSeconds()<50){
                        v_piezas[i].c.move(0,v_piezas[i].vel+(v*2));
                    }
                    else{
                        v_piezas[i].c.move(0,v_piezas[i].vel+(v*10));
                    }
                }
                else{
                    v_piezas[i].c.setPosition(x_min, 2000);
                }
                */
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
    
    if(on == true){
        /*
        for(int i = 0 ; i<v_piezas.size() ; i++){
            v_piezas[i].c.setTexture(v_piezas[i].t);
            v_piezas[i].c.draw();
        }
        */
        for(int i = 0 ; i<v_piezas.size() ; i++){
            for(int j = 0 ; j<4 ; j++){
                //std::cout << "x: " <<  v_piezas[i].r[j].getPosition()[0] << " | y: " << v_piezas[i].r[j].getPosition()[1] << std::endl;

                v_piezas[i].r[j].draw();
            }
        }
    }
}






mj_t::mj_t(const mj_t& orig) {
}