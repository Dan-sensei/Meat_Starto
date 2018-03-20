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


class physicsEngine {
public:
    //======== SINGLETON =========
    static physicsEngine& Instance(){
        static physicsEngine instance;        // Las variables estáticas se destruyen al terminar el programa
        return instance;                // Return molón
    }
    //============================
    
    class pBody {   // Façade de b2Body, dado que no deberían existir sin un mundo donde ponerlos, lo creo como una Nested Class dentro de PhysicsEngine
                    // Con una clase independiente se puede crear múltiples instancias de Bodies, y referenciarlos desde otras clases
        public:

            pBody();

            void setLinealVelocicty(float vx_, float vy_);      // Ajusta la velocidad lineal del cuerpo
            void addForceToCenter(float vx_, float vy_);        // Añade una fuerza al centro del cuerpo
            float getLinearXVelocity();                         // Obtiene la velocidad lineal en el eje X
            float getLinearYVelocity();                         // Obtiene la velocidad lienal en el eje Y

            float getXPosition();                               // Posición en el eje X
            float getYPosition();                               // Posición en el eje Y
            float getRotation();                                // Rotación

            void setBody(b2Body* body_);                        // Da valor a la variable Body de Box2D (usado en createBody(...)
            b2Body* getBody();                                  // Devuelve la variable Body de Box2D

        private:

            b2Body* body;                                       //Variable b2Body de Box2D
    };
    
    pBody createBody(float width_, float height_, float px_, float py_, char type_);        // Crea y devuelve un pBody pasándole, ancho, alto, posicionX, posicionY, tipo ('S'tatic, 'D'ynamic, 'K'inematic)
    void createGround(std::vector<std::array<float, 2>> vertex_, int n_);                   // Crea el suelo del mapa, pasándole un vector de coordenadas, que serán los vértices que lo forman, y el número de vértices totales
    void setGravity(float gx_, float gy_);                                                  // Ajusta la gravedad del mundo
    void updateWorld(float tick_);                                                          // Actualiza el mundo
    
private:
    
    //============ SINGLETON ============
    physicsEngine();
    physicsEngine(physicsEngine const& orig);           // <--------------------- No implementar estos métodos
    void operator=(physicsEngine const& orig);    // <----------------'
    //===================================
    
    float static pixelToWorld(float p_);        // Convierte los pixeles de pantalla al sistema de coordenadas de Box2D
    float static worldToPixel(float w_);        // Convierte del sitema de coordenadas de Box2D a pixeles en patanlla
    
    b2World world;                              // Variable b2World de Box2D
    
};

#endif /* PHYSICSENGINE_H */

/*  SINGLETON: FORMA DEL PDF DE FV___________________

 public:
    static physicsEngine* Instance();
    int getVar();
    void setVar(int n_);
    
protected:
    physicsEngine();
    physicsEngine(const physicsEngine &);
    physicsEngine &operator = (const physicsEngine &);
private:
    static physicsEngine* pInstance;
    int var;
 
 */