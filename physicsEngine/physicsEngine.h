/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   physicsEngine.h
 * Author: dan
 *
 * Created on 16 de marzo de 2018, 10:00
 */

#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include "pBody.h"
#include "pConverter.h"
#include "math.h"
#include "contactListener.h"


    
class physicsEngine {
public:
    //======== SINGLETON =========
    static physicsEngine& Instance(){
        static physicsEngine instance;        // Las variables estáticas se destruyen al terminar el programa
        return instance;                // Return molón
    }
    //============================
    
    struct type{
        int id;
        void* data;
    };
    type* t;

    pBody createPlayer(float width_, float height_, float px_, float py_, type* main, type* bottom);
    pBody createBody(float width_, float height_, float px_, float py_, char type_, type* data);        // Crea y devuelve un pBody pasándole, ancho, alto, posicionX, posicionY, tipo ('S'tatic, 'D'ynamic, 'K'inematic)
    pBody createGround(std::vector<std::array<int, 2>> vertex_, type* data);              // Crea el suelo del mapa, pasándole un vector de coordenadas, que serán los vértices que lo forman, y el número de vértices totales
    void setGravity(float gx_, float gy_);                                                  // Ajusta la gravedad del mundo
    void updateWorld(float tick_);                                                          // Actualiza el mundo
    void detroyBody(pBody body);
    int getBodyListSize();
    
    //Genera un número aleatorio entre min y max (ambos incluídos)
    float genFloatRandom(float min, float max);
    int genIntRandom(int min, int max);
    
    
private:
    
    //============ SINGLETON ============
    physicsEngine();
    physicsEngine(physicsEngine const& orig);           // <--------------------- No implementar estos métodos
    void operator=(physicsEngine const& orig);    // <----------------'
    //===================================
    
    contactListener listener;
    b2World world;                              // Variable b2World de Box2D
    
};



#endif /* PHYSICSENGINE_H */
