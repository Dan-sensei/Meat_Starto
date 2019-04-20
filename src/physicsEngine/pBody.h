/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pBody.h
 * Author: dan
 *
 * Created on 28 de marzo de 2018, 14:48
 */

#ifndef PBODY_H
#define PBODY_H
#include "pConverter.h"
#include "math.h"
#include <Box2D/Box2D.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

class pBody {   // Façade de b2Body, dado que no deberían existir sin un mundo donde ponerlos, lo creo como una Nested Class dentro de PhysicsEngine
                // Con una clase independiente se puede crear múltiples instancias de pBodies, y referenciarlos desde otras clases
    public:

        pBody();
        pBody(const pBody& orig);
        
        void setLinealVelocicity(float vx_, float vy_);      // Ajusta la velocidad lineal del cuerpo
        void applyForceToCenter(float vx_, float vy_);       // Añade una fuerza al centro del cuerpo
        void applyLinearImpulse(float ix_, float iy_);
        void setFixedRotation(bool flag_);                  // Determina si la rotación es fija
        float getLinearXVelocity();                         // Obtiene la velocidad lineal en el eje X
        float getLinearYVelocity();                         // Obtiene la velocidad lienal en el eje Y
        
        void setActive(bool flag);
        
        float getXPosition();                               // Posición en el eje X
        float getYPosition();                               // Posición en el eje Y
        float getRotation();                                // Rotación
        
        void setPosition(float x, float y);
        
        void setUserData(void* data);
        void setBody(b2Body* body_);                        // Da valor a la variable Body de Box2D (usado en createBody(...))
        b2Body* getBody();                                  // Devuelve la variable Body de Box2D

    private:
        
        b2Body* body;                                       //Variable b2Body de Box2D
};

#endif /* PBODY_H */

