/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   boss.cpp
 * Author: pablomanez
 * 
 * Created on 5 de abril de 2018, 16:11
 */

#include "boss.h"

#define DES 2000

boss::boss() {
}

void boss::init(int x_) {
    //x_ ES LA POSICION MAXIMA DEL ANTERIOR NODO DIBUJADO

    //COORDENADAS
    float a = 70;
    x_min = x_+(a*12);
    x_max = x_+(a*53);
    
    on = false;
    restart = false;
    
    //BOSS
    javi.r.setSize(70,70);
    javi.r.setPosition(x_min+(a*5),560);
    javi.r.setFillColor('r');
    javi.move = true;
    
    //CREO LA "PUERTA"
    puerta[0].r.setSize(a*12,a*5);
    puerta[0].r.setPosition(x_min-(a*8),(a*20)+DES);
    puerta[1].r.setPosition(x_min+(a*4),(a*20)+DES);
    puerta[2].r.setPosition(x_min+(a*4),(a*21)+DES);
    puerta[3].r.setPosition(x_min+(a*4),(a*22)+DES);
    puerta[4].r.setPosition(x_min+(a*4),(a*23)+DES);
    puerta[5].r.setPosition(x_min+(a*4),(a*24)+DES);
    puerta[6].r.setPosition(x_min+(a*5),(a*22)+DES);
    puerta[7].r.setPosition(x_min+(a*5),(a*23)+DES);
    puerta[8].r.setPosition(x_min+(a*5),(a*24)+DES);
    puerta[9].r.setPosition(x_min+(a*6),(a*23)+DES);
    puerta[10].r.setPosition(x_min+(a*6),(a*24)+DES);
    puerta[11].r.setPosition(x_min+(a*7),(a*24)+DES);
    
    for(int i=0 ; i<12 ; i++){
        if(i != 0){
            puerta[i].r.setSize(a,a);
        }
        puerta[i].r.setFillColor('r');
    }
}

void boss::update(int x_m, float x_, float y_) {
    //x_ MARCA LA POSICION CENTRAL DE LA VISTA
    physicsEngine *world;
    
    if(x_m> (x_min+(70*20)) && x_m < x_max){
        //COMIENZA LA BATALLA FINAL
        on = true;
        
        if(!restart){
            //AQUI SOLO ENTRA UNA VEZ
            //CREO LAS COLISIONES DE LA PUERTA 
            for(int i=0 ; i<12 ; i++){
                float x = puerta[i].r.getPosition()[0];
                float y = puerta[i].r.getPosition()[1]-DES;
                puerta[i].r.setPosition(x,y);

                float w = puerta[i].r.getSize()[0];
                float h = puerta[i].r.getSize()[1];
                x = puerta[i].r.getPosition()[0]+(w/2);
                y = puerta[i].r.getPosition()[1]+(h/2);
                puerta[i].b = world->Instance().createBody(w,h,x,y,'k');
            }
            
            clock_boss.restart();   //REINICIO LOS RELOJES
            dt_boss.restart();
            restart = true;
        }
        
        //UPDATE DE JAVI
        javi.move ? javi.r.move(5,0) : javi.r.move(-5,0);
        
        if(javi.r.getPosition()[0]>x_min+(70*33) && javi.move){
            javi.move = false;
        }
        else if(javi.r.getPosition()[0]<x_min+(70*5) && !javi.move){
            javi.move = true;
        }
        
        if(dt_boss.getElapsedTime().asSeconds() > 0.2){
                //std::cout << "CREO BALA" << std::endl;
            crearProyectil(x_,y_);
            dt_boss.restart();
        }
        
        //MOVIMIENTO DE LOS PROYECTILES
        for(int i=0 ; i<javi.proy.size() ; i++){
            float vx = javi.proy[i].v_x;
            float vy = javi.proy[i].v_y;

            javi.proy[i].r.move(vx,vy);
        }

    }
    else{
        on = false;
    }
}

void boss::crearProyectil(float x_, float y_) {
    //CREO EL PROYECTIL
    //LO AÑADO AL VECTOR DEL JEFE
    int a = 70;
    float factor = 100;
    
    float w = 15;
    float h = 15;
    
    float x = javi.r.getPosition()[0];
    float y = javi.r.getPosition()[1];
    
    proyectil aux;
    aux.r.setSize(w,h);
    aux.r.setPosition(x+(a/2),y+(a/2));
    aux.r.setFillColor('k');
    
    //AQUI SE DEBERIAN DE CONSEGUIR LAS POSICIONES DE LOS PERSONAJES
    //HE TENIDO QUE PASARLAS A TRAVES DE 3 FUNCIONES
        //std::cout << "X: " << x_ << std::endl;
        //std::cout << "Y: " << y_ << std::endl;
    aux.v_x = (x_ - x)/factor;
    aux.v_y = (y_ - y)/factor;
        //std::cout << "V (" << aux.v_x << "," << aux.v_y << ")" << std::endl;
    
    javi.proy.push_back(aux);
    
}

void boss::render() {
    
    if(on){
        for(int i=0 ; i<12 ; i++){
            puerta[i].r.draw();
        }
        for(int i=0 ; i<javi.proy.size() ; i++){
            javi.proy[i].r.draw();
        }
        javi.r.draw();
    }
}

bool boss::isBossOn() { return on;}




boss::boss(const boss& orig) {
}
