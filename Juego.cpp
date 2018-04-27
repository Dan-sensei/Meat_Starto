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

Juego::Juego() { 
    
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
    Mapa::Instance().CreaMapa();
    
    //VISTA
    view = new renderEngine::rView(0, 0, sfml->Instance().getSize()[0], sfml->Instance().getSize()[1]);
    //ZUMO
    view->zoom(target_zoom);
    sfml->Instance().setView(*view);
    
    
    view->setCenter(view->getCenter()[0], CAM_H);
    
    //INTERPOLACION
    accumulator = 0.0f;
    masterClock.restart();
    tick = 0.0f;

    //FPS
    lastTime = 0;
    
    
    //JUGADORES

    int i = 0;

    do {
        
        readyPlayer.push_back(new Player(i, "Jugador " + std::to_string(i+1), 60.f, 60.f, 1200, 1200, 'D', keys));
        ++i;
        
    }while( i < MenuInicio::Instance()->numplayers );
    
    // MUSICA
    THE_ARID_FLATS.openFromFile("assets/Sounds/THE_ARID_FLATS.ogg");
    THE_ARID_FLATS.setLoop(true);
    //THE_ARID_FLATS.play();

    rain.setPosition(1500, 200);                    // Posicion del sistema de partículas
    rain.setType(1);                                // Tipo: Determina el área de generado | 0 = Círculo - 1 = Rectángulo (Por defecto tienen tamaño 0 y emitirán hacia el exterior aleatoriamente)
    rain.setParticleSpeed(500);                     // Velocidad lineal de las partículas
    rain.setMaxParticleAmout(500);                  // Máximo número de partículas
    rain.setGenerationTimer(4);                     // Tiempo (ms) de delay entre la generación de partículas (En este caso se genera una partícula cada 4 ms)
    rain.setParticleLifeTime(1);                    // Tiempo de vida en segundos, de vida d elas partículas
    rain.setParticleDirection(-0.1, 1);             // Dirección de las partículas, debe ser un número entre 0 y 1
    rain.setRectangle(4000, 200);                   // Área de generado, en este caso es un rectángulo, así que le digo ancho y alto, si fuera un círculo, llamaría a setCircle(float radius);
    rain.alignToDirection(true);                    // Alinea las partículas a la dirección del movimiento, por defecto es false, si está a true, se ingora la rotación inicial
    rain.setSprite("assets/THE_WATER_DROP.png");    // Cambia el sprite
    rain.setSpriteSize(1, 0.8);                     // Cambia el tamaño del sprite
    
    hud= new Hud(readyPlayer);
    
    Mapa::Instance().setPlayers(&readyPlayer);
    cameraDirection = 0;
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
                    
                    //JUGADOR 2
                    
                    case 71:
                        if(readyPlayer.size()>=2){
                            readyPlayer[1]->moveLeft_b();
                        }
                    break;

                    case 72:
                        if(readyPlayer.size()>=2){
                            readyPlayer[1]->moveRigth_b();
                        }
                    break;
                   //JUGADOR 1                    
                    case 0:
                        if(readyPlayer.size()>=1){
                            readyPlayer[0]->moveLeft_b();
                        }
                    break;
                    
                    case 3:
                        if(readyPlayer.size()>=1){
                            readyPlayer[0]->moveRigth_b();
                        }
                    break; 
                    
                    //JUGADOR 3
                    
                    case 10:
                        if(readyPlayer.size()>=3){
                            readyPlayer[2]->moveLeft_b();
                        }
                    break;

                    case -1:
                        if(readyPlayer.size()>=3){
                            readyPlayer[2]->moveRigth_b();
                        }
                    break;
                    
                    //JUGADOR 4
                    
                    case 21:
                        if(readyPlayer.size()>=4){
                            readyPlayer[3]->moveLeft_b();
                        }
                    break;

                    case 13:
                        if(readyPlayer.size()>=4){
                            readyPlayer[3]->moveRigth_b();
                        }
                    break;
                   case 57:
                       /*ESPACIO PARA CAMBIAR DE PUNYO CORTO A LARGO*/
                        std::cout<<"CAMBIO"<<std::endl;
                        readyPlayer[0]->double_hit(true);
                        
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
        float zoom = (1005*target_zoom)/window_height;

        view->setSize(window_width, window_height);
        view->zoom(zoom);
        sfml->Instance().setView(*view);
        
        rain.setPosition(view->getCenter()[0], rain.getYPosition());

        // LÓGICA DE LOS NPC Y JUGADORES
        for(int i=0; i< readyPlayer.size(); i++){
            readyPlayer[i]->movement();
        }
        
        mapa->Instance().update();
        rain.update();

        // BUCLE DE STEPS DE BOX2D
        for(int i = 0; i < FRAMERATE/UPDATE_STEP; i++){
            //std::cout << "      |--STEP: V " << player.getLinearXVelocity() << std::endl;
            world->Instance().updateWorld(BOX2D_STEP);
            //std::cout << "             : V " << player.getLinearXVelocity() << std::endl;
        }

        accumulator -= 1/UPDATE_STEP;

        // ACTUALIZO EL ESTADO ACTUAL
        for(int i=0; i< readyPlayer.size(); i++){
            readyPlayer[i]->newState();
        }        
        mapa->Instance().newState();
        rain.newState();
    }
    //std::cout << "CAMERA DIR " << cameraDirection << std::endl;
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
    for(int i=0; i< readyPlayer.size(); i++){
        readyPlayer[i]->update();
        readyPlayer[i]->interpola(tick);
    }
    
    
    //ACTUALIÇAÇAO DE LA CAMARA
    if(!tetris->Instance().isTetrisOn() && !javi->Instance().isBossOn()){    //TRUE: SE MUEVE LA CAMARA
        int n=0;
        for(int i=0; i< readyPlayer.size(); i++){
            if(readyPlayer[i]->getXPosition() > readyPlayer[n]->getXPosition()){
                n=i;
            }
        }
        //std::cout << readyPlayer[0]->getXPosition() << ", " << readyPlayer[0]->getYPosition() << std::endl;
        
        //COMENTAR EL IF SI SE QUIERE QUE LA CAMARA VAYA HACIA ATRAS
        if(cameraDirection == 0){
            if(readyPlayer[n]->getXPosition()>view->getCenter()[0])
                view->setCenter(readyPlayer[n]->getXPosition(), view->getCenter()[1]);
        }    
        else{
            if(readyPlayer[n]->getYPosition()<view->getCenter()[1])
                view->setCenter(view->getCenter()[0], readyPlayer[n]->getYPosition());
        }
        
        //view->setCenter(view->getCenter()[0]+20, Mapa::Instance().getYMax()+1400);        <- Esta línea hace que recorra el mapa la camara
                                                                                            // Si solo ves nubes, es porque se ha generado el minijueg de subir, y la altura se ha puesto automáticamente ahí, np.
        
        //std::cout << "CAMARA > X: " << sfml->Instance().getViewCenter()[0] << " | Y: " << sfml->Instance().getViewCenter()[1] << std::endl;
    }

    sfml->Instance().setView(*view);

    //ACTUALIÇAÇAO DEL MAPA
    mapa->Instance().updateMini();
    mapa->Instance().render(tick);
    rain.draw(tick);
    for(int i=0; i< readyPlayer.size(); i++){
        readyPlayer[i]->draw();
    }
    
    
    hud->render();

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

void Juego::switchCameradirection() {
    cameraDirection = (cameraDirection == 0) ? 1 : 0;
    Mapa::Instance().setCameraDirection(cameraDirection);
}
