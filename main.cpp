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
#include "physicsEngine/physicsEngine.h"
#include "physicsEngine/pBody.h"
#include "renderEngine.h"
#include "mj_t.h"
#include "Player.h"
#include "boss.h"

#define FRAMERATE 60.f
#define UPDATE_STEP 15.f
#define BOX2D_STEP 1.f/FRAMERATE

#define CAM_H 1250

#define force 50.f*FRAMERATE/UPDATE_STEP
#define speed 12.f
#define jump 2500
#define stop_mult 1.2f

#define PLAYER_DIM_X 1.9f
#define PLAYER_DIM_Y 1.9f

using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {

    renderEngine* sfml;
    sfml->Instance(); //CREO EL SINGLETON, SE CREA ADEMAS LA WINDOW
    
    physicsEngine* world;
    world->Instance();  //Creo el Singleton en la primera llamada a Instancia
    world->Instance().setGravity(0.f, 100.f);
    
    //player.setFixedRotation(false);
    //player.setUserData("Player1")
    bool* keys = new bool [256];
    for(int i = 0; i<256; i++) keys[i]=false;
    
    Player readyPlayerOne(0, "Jugador 1", 60.f, 60.f, 1260, 1200, 'D', keys);
    //SINGLETON MUNDO
    Tile *tile;
    tile->Instance();
    tile->Instance().CreaMapa();
    
    //SINGLETON TETRIS
    mj_t *tetris;
    
    //SINGLETON BOSS
    boss *javi;
    
    //VISTA
    renderEngine::rView view(0,0,sfml->Instance().getSize()[0],sfml->Instance().getSize()[1]);
    //view.zoom(2.7);
    view.zoom(2);
    
    sfml->Instance().setView(view);
    
    renderEngine::rClock masterClock;
    renderEngine::rClock animationClock;
    
    double dt;
    
    float accumulator = 0.0f;
    masterClock.restart();

    //FPS
    renderEngine::rClock cl_fps;
    float lastTime = 0;
    float currentTime;
    float fps;
    
    while(sfml->Instance().isOpen()){
        //<FPS>
        currentTime = cl_fps.restart().asSeconds();
        fps = 1.f/(currentTime/lastTime);
        lastTime = currentTime;
            //cout << "FPS: " << fps*60.f << endl;
        //</FPS>
        
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
        
        accumulator += dt;
        while(accumulator >= 1/UPDATE_STEP){
            //std::cout << "UPDATE-- " << accumulator << std::endl;
            
            readyPlayerOne.preState();  
            tile->Instance().preStateNPCs();
            
            readyPlayerOne.movement();
            tile->Instance().updateNPCs();
            
            // BUCLE DE STEPS DE BOX2D
            for(int i = 0; i < FRAMERATE/UPDATE_STEP; i++){
                //std::cout << "      |--STEP: V " << player.getLinearXVelocity() << std::endl;
                world->Instance().updateWorld(BOX2D_STEP);
                //std::cout << "             : V " << player.getLinearXVelocity() << std::endl;
            }
            
            accumulator -= 1/UPDATE_STEP;
            
            // ACTUALIZO EL ESTADO ACTUAL
            readyPlayerOne.newState();
            tile->Instance().newStateNPCs();
        }
        
        // TICK PARA LA INTERPOLAÇAO
        double tick = min(1.f, static_cast<float>( accumulator/(1/UPDATE_STEP) ));
        
        //std::cout << "RENDER == " << tick << std::endl;
        sfml->Instance().clear('w');
        
        
        readyPlayerOne.update(animationClock.restart());
        
        //ACTUALIÇAÇAO
        readyPlayerOne.interpola(tick);
        
        if(!tetris->Instance().isTetrisOn() && !javi->Instance().isBossOn())    //TRUE: SE MUEVE LA CAMARA
            view.setCenter(readyPlayerOne.getXPosition(),CAM_H);
        tile->Instance().update(readyPlayerOne.getXPosition(),readyPlayerOne.getYPosition());
        
        //DRAW
        sfml->Instance().setView(view);
        tile->Instance().render(tick);
        
        readyPlayerOne.draw();
        
        //RENDER
        
        sfml->Instance().display();


    }
    
    return 0;
}
