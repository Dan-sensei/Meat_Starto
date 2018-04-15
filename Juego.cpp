/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Juego.cpp
 * Author: alba
 * 
 * Created on 15 de marzo de 2018, 22:20
 */

#include "Juego.h"


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

#define target_zoom 2

Juego::Juego(){
    renderEngine* sfml;
    sfml->Instance(); //CREO EL SINGLETON, SE CREA ADEMAS LA VENTANA
    
    physicsEngine* world;
    world->Instance();  //Creo el Singleton en la primera llamada a Instancia
    world->Instance().setGravity(0.f, 100.f);
    
    //player.setFixedRotation(false);
    //player.setUserData("Player1")
    keys = new bool [256];
    for(int i = 0; i<256; i++) keys[i]=false;
    
    //SINGLETON MUNDO
    Mapa *mapa;
    mapa->Instance();
    mapa->Instance().CreaMapa();
    
    //VISTA
    view = new renderEngine::rView(0,0,sfml->Instance().getSize()[0],sfml->Instance().getSize()[1]);
    //ZUMO
    view->zoom(target_zoom);
    sfml->Instance().setView(*view);
    
    //INTERPOLACION
    accumulator = 0.0f;
    masterClock.restart();
    tick = 0.0f;

    //FPS
    lastTime = 0;
    
    //JUGADORES
    readyPlayer.push_back(new Player(0, "Jugador 1", 60.f, 60.f, 1260, 1200, 'D', keys));
    
    // MUSICA
    THE_ARID_FLATS.openFromFile("assets/Sounds/THE_ARID_FLATS.ogg");
    THE_ARID_FLATS.setLoop(true);
    THE_ARID_FLATS.play();
}


void Juego::Handle(){
    //BUCLE DEL JUEGO
    renderEngine *sfml;
    
    while(sfml->Instance().isOpen()){
        //<FPS>
        currentTime = cl_fps.restart().asSeconds();
        //fps = 1.f/(currentTime/lastTime);
        fps = 1.f/currentTime;
        lastTime = currentTime;
        //std::cout << "FPS: " << fps << std::endl;
        //</FPS>
        
        //EVENTOS
        HandleEvents();
        
        //UPDATE
        Update();
            //std::cout << "EVENTOS" << std::endl;
        
        //RENDER
        Render();
            //std::cout << "RENDER" << std::endl;
    }
    THE_ARID_FLATS.stop();
}

void Juego::HandleEvents(){
    renderEngine    *sfml;
    
    renderEngine::rEvent event;
        //0x7fff11e212f0
    while(sfml->Instance().pollEvent(event)){
        switch(event.sfType()){
            case renderEngine::rEvent::EventType::KeyPressed :
                keys[event.getKeyCode()] = true;
                //std::cout << "Tecla " << event.getKeyCode() << std::endl;
                break;
            case renderEngine::rEvent::EventType::KeyReleased :
                keys[event.getKeyCode()] = false;     
                switch(event.getKeyCode()) {
                    //JUGADOR 1
                    case 0:
                        readyPlayer[0]->moveLeft_b();
                    break;

                    case 16:
                        readyPlayer[0]->moveRigth_b();
                    break;
                }
                break;

            default:
                break;
        }

    }
    if(keys[16])    sfml->Instance().close();                                   //Q

    if(keys[36]){   
        keys[36]=false;                                                         //ESC
        sfml->Instance().ChangeState(MenuPausa::Instance());    
    }   

    if(keys[15]){   
        keys[15]=false;
        sfml->Instance().ChangeState(MPuntuaciones::Instance());                 //P
    } 
}

void Juego::Update(){
    renderEngine    *sfml;
    Mapa            *mapa;
    physicsEngine   *world;
    
    // FIXED TIME STEP UPDATE
    dt = masterClock.restart().asSeconds();

    //Spiral of death
    if(dt > 0.25f)   dt = 0.25f;

    // <editor-fold defaultstate="collapsed" desc="EXPLICACION DE LA INTERPOLAÇAO">
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
    // </editor-fold>

    accumulator += dt;
    while(accumulator >= 1/UPDATE_STEP){
        //std::cout << "UPDATE-- " << accumulator << std::endl;
        
        float window_width = static_cast<float>(sfml->Instance().getSize()[0]);
        float window_height = static_cast<float>(sfml->Instance().getSize()[1]);  
        float zoom = (1006*target_zoom)/window_height;

        view->setSize(window_width, window_height);
        view->zoom(zoom);
        sfml->Instance().setView(*view);
        
        // SOBRESCRIBO LOS ESTADOS ANTERIORES
        readyPlayer[0]->preState();  
        mapa->Instance().preState();

        // LÓGICA DE LOS NPC Y JUGADORES
        readyPlayer[0]->movement();
        mapa->Instance().update();

        // BUCLE DE STEPS DE BOX2D
        for(int i = 0; i < FRAMERATE/UPDATE_STEP; i++){
            //std::cout << "      |--STEP: V " << player.getLinearXVelocity() << std::endl;
            world->Instance().updateWorld(BOX2D_STEP);
            //std::cout << "             : V " << player.getLinearXVelocity() << std::endl;
        }

        accumulator -= 1/UPDATE_STEP;

        // ACTUALIZO EL ESTADO ACTUAL
        readyPlayer[0]->newState();
        mapa->Instance().newState();
    }
    physicsEngine* wold;
    //std::cout << "LISTA: " << world->Instance().getBodyListSize() << std::endl;
}

void Juego::Render(){
    //std::cout << "RENDER == " << tick << std::endl;
    renderEngine    *sfml;
    Mapa            *mapa;
    mj_t            *tetris;
    boss            *javi;
    
    sfml->Instance().clear('w');
        
    // TICK PARA LA INTERPOLAÇAO
    tick = std::min(1.f, static_cast<float>( accumulator/(1/UPDATE_STEP) ));
    
    //ACTUALIÇAÇAO DEL PERSONAJE
    readyPlayer[0]->update(animationClock.restart());
    readyPlayer[0]->interpola(tick);
    //ACTUALIÇAÇAO DE LA CAMARA
    if(!tetris->Instance().isTetrisOn() && !javi->Instance().isBossOn())    //TRUE: SE MUEVE LA CAMARA
        view->setCenter(readyPlayer[0]->getXPosition(),CAM_H);
    
    //ACTUALIÇAÇAO DE LOS MINIJUEGOS

    mapa->Instance().updateMini();
    
    sfml->Instance().setView(*view);
    mapa->Instance().render(tick);
    mapa->Instance().updateMini();
    readyPlayer[0]->draw();

    sfml->Instance().display();
    
}

std::array<float, 2> Juego::getPlayerPosition() {
    std::array<float,2> ret;
    
    ret[0] = readyPlayer[0]->getXPosition();
    ret[1] = readyPlayer[0]->getYPosition();
    
    return ret;
}

Juego::~Juego() {
    
    delete[] keys;
    keys = nullptr;
    std::cout << "Destroying game==================================" << std::endl;
}

std::vector<Player*>* Juego::getPlayers() {
    return &readyPlayer;
}
