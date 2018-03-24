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
#include <math.h>

#include "Tile.h"
#include "physicsEngine.h"
#include "renderEngine.h"

#define FRAMERATE 60.f
#define UPDATE_STEP 15.f
#define BOX2D_STEP 1.f/FRAMERATE

#define CAM_H 1250

#define force 50.f*FRAMERATE/UPDATE_STEP
#define speed 12.f
#define jump 2500

#define PLAYER_DIM_X 1.9f
#define PLAYER_DIM_Y 1.9f

using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {

    renderEngine* sfml;
    sfml->Instance(); //CREO EL SINGLETON, SE CREA ADEMAS LA WINDOW
    
    //41 - 6
    
    //TEST
    int finisher;
    std::string test  = "Tes:LUJAN:MoarTesting";
    std::string out;
    finisher = test.find_first_of(":");
    out.append(test, finisher+1, test.size());
    test.erase(finisher);

    std::cout << "OUT " << out << std::endl;
    std::cout << "TEST " << test << std::endl;
    //TEST
    
    
    
    physicsEngine* world;
    world->Instance();  //Creo el Singleton en la primera llamada a Instancia
    world->Instance().setGravity(0.f, 100.f);
    
    physicsEngine::pBody player = world->Instance().createBody(76.f, 64.f, 2400, 1200, 'D');
    //player.setFixedRotation(false);
    
    //MUNDO
    Tile *tile;
    tile->Instance();
    tile->Instance().CreaMapa();

    
    //38x32
    renderEngine::rTexture boxTexture("assets/prueba.png");
    renderEngine::rSprite Sprite;
    Sprite.setTexture(boxTexture);
    Sprite.setOrigin(19.f, 16.f);
    Sprite.setScale(-PLAYER_DIM_X, PLAYER_DIM_Y);
    
    //VISTA
    renderEngine::rView view(0,0,sfml->Instance().getSize()[0],sfml->Instance().getSize()[1]);
    //view.zoom(2.7);
    view.zoom(2);
    sfml->Instance().setView(view);
    
    renderEngine::rClock masterClock;
    double dt;
    bool keys[256];
    for(int i = 0; i<256; i++) keys[i]=false;
    
    float accumulator = 0.0f;
    masterClock.restart();

    
    while(sfml->Instance().isOpen()){
        
        renderEngine::rEvent event;
        //0x7fff11e212f0
        while(sfml->Instance().pollEvent(event)){
            switch(event.sfType()){
                case renderEngine::rEvent::EventType::KeyPressed :
                    keys[event.getKeyCode()] = true;
                    break;
                
                case renderEngine::rEvent::EventType::KeyReleased :
                    keys[event.getKeyCode()] = false;     
                    break;
                
                default:
                    break;
            }
            
        }
        //UPDATE

        if(keys[16]) sfml->Instance().close();  //Cerrar
        
        // FIXED TIME STEP UPDATE
        dt = masterClock.restart().asSeconds();
        
        //Spiral of death
        if(dt > 0.25f)   dt = 0.25f;
        
        /*
        
            FRAMERATE A 60
               UPDATE A 15 
            STEP BOX2D = FRAMERATE
         
            0    5    10   15   20   25   30   35   40   45   50   55   60
            |----|----|----|----|----|----|----|----|----|----|----|----| 
                |                                                       Al cabo de un segundo_
             FRAME 4                                                    RENDER [ 60 VECES ] 
                |                                                       UPDATE [ 15 VECES ]     --> 60 / 15 = CADA 4
                |                                                       STEP DE BOX2D [ 60 VECES ]
                x1 UPDATE
                x4 STEPS DE BOX2D
         
            Por tanto dentro del update ejecutamos un bucle con las actualizaciones del mundo de Box2D con FRAMERATE / UPDATE iteraciones
         
            En la variable dt guardamos el tiempo que ha pasado desde el frame anterior y lo vamos acumulando en la variable accumulator de manera que:
            Si el acumulador es mayor que 0'067 (1/15) entramos al bucle, ejecutamos el UPDATE, y ejecutamos los STEPS necesarios en el mundo de Box2D
            Terminado esto, le restamos a nuestro accumulator 0'067 y como está en un bucle, comprobará de nuevo si puede volver a ejecutar el update
            Esto casi nunca ocurrirá pero, en caso de haya un bajón y se quede atrás, ejecutará tantos updates como sean necesarios
        
        
        */
        
        accumulator+=dt;
        while(accumulator >= 1/UPDATE_STEP){
            std::cout << "UPDATE-- " << accumulator << std::endl;
            
            // TECLA A
            if( keys[0])  {
                if(player.getLinearXVelocity() > -speed)
                    player.addForceToCenter(-force, 0); 
                else 
                    player.setLinealVelocicity(-speed, player.getLinearYVelocity());
                Sprite.setScale(PLAYER_DIM_X, PLAYER_DIM_Y);
            }
            
            // TECLA D
            else if( keys[3]) {             
                if(player.getLinearXVelocity() < speed)
                    player.addForceToCenter(force, 0); 
                else
                    player.setLinealVelocicity(speed, player.getLinearYVelocity());
                Sprite.setScale(-PLAYER_DIM_X, PLAYER_DIM_Y);
            }
            
            // TECLA W / ESPACIO
            if(keys[57] || keys[22]){ 
                keys[57] = false;
                keys[22] = false;
                player.addForceToCenter(0, -jump);
            }
            
            
            //STOP
            if(!keys[0] && !keys[3])        
                player.setLinealVelocicity(0, player.getLinearYVelocity());
            
            // BUCLE DE STEPS DE BOX2D
            for(int i = 0; i < FRAMERATE/UPDATE_STEP; i++){
                std::cout << "      |--STEP" << std::endl;
                world->Instance().updateWorld(BOX2D_STEP);
                //std::cout << "             : V " << player.getLinearXVelocity() << std::endl;
            }
            accumulator -= 1/UPDATE_STEP;
        }
        
        // TICK PARA LA INTERPOLAÇAO
        double tick = accumulator/dt;
        
        std::cout << "RENDER == " << tick << std::endl;
        sfml->Instance().clear('y');
        
        Sprite.setPosition(player.getXPosition(), player.getYPosition());
        Sprite.setRotation(player.getRotation());
        
        //DRAW
        tile->Instance().DibujaCasillas(Sprite.getPosition()[0], CAM_H);
        view.setCenter(Sprite.getPosition()[0],CAM_H);

        sfml->Instance().setView(view);

        Sprite.draw();
                
        //RENDER
        
        sfml->Instance().display();


    }
    
    return 0;
}
