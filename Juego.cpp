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

    physicsEngine::Instance().setGravity(0.f, 100.f);


    keys = new bool [256];
    for(int i = 0; i<256; i++) keys[i]=false;

    //SINGLETON MUNDO
    Mapa::Instance().CreaMapa();

    //VISTA
    view = new renderEngine::rView(0, 0, renderEngine::Instance().getSize()[0], renderEngine::Instance().getSize()[1]);
    //ZUMO
    view->zoom(target_zoom);
    renderEngine::Instance().setView(*view);

    backgroundView = new renderEngine::rView(0, 0, renderEngine::Instance().getSize()[0], renderEngine::Instance().getSize()[1]);
    backgroundView->zoom(1);


    //INTERPOLACION
    accumulator = 0.0f;
    masterClock.restart();
    tick = 0.0f;

    //FPS
    lastTime = 0;


    //JUGADORES

    float x_arr[4] = {2240,1750,1260,770};
    std::string names[4] = {"Jack","Amy","Ike","Violet"};

    int i = 0;
    do {
        readyPlayer.push_back(new Player(i, names[i], 60.f, 50.f, x_arr[i], 800, 'D', keys));
        ++i;

    }while( i < MenuInicio::Instance()->numplayers );

    float xmax = 0;
    for(int j=0 ; j<readyPlayer.size() ; j++){
        if(readyPlayer[j]->getXPosition() > xmax){
            xmax = readyPlayer[j]->getXPosition();
        }
    }
    view->setCenter(xmax, CAM_H);

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
    rain.drawGenerationArea(true);
    
    minirain.setPosition(1500, 200);                    
    minirain.setType(1);                               
    minirain.setParticleSpeed(300);                     
    minirain.setMaxParticleAmout(750);                  
    minirain.setGenerationTimer(3);                  
    minirain.setParticleLifeTime(1);
    minirain.setParticleDirection(-0.1, 1);
    minirain.setRectangle(4000, 200);
    minirain.alignToDirection(true);
    minirain.setSprite("assets/THE_WATER_DROP.png");
    minirain.setSpriteSize(0.7, 0.4);

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

    int jAxis;
    float jPosition;
    int der;
    int izq;

    while(sfml->Instance().pollEvent(event)){

        /* CODIGOS DE LOS MANDOS:
         * ----------------------
         * XBOX:        biba la plei
         *  A:  0
         *  B:  1
         *  X:  2
         *  Y:  3
         *  LB: 4
         *  RB: 5
         */

        switch(event.sfType()){
            case renderEngine::rEvent::EventType::JoystickButtonPressed :
                if(event.getJoystickButton()==6) renderEngine::Instance().close();
                if(event.getJoystickButton()==7) renderEngine::Instance().ChangeState(MenuPausa::Instance());
                for(int i=0 ; i<getPlayers()->size() ; i++){
                    if(renderEngine::Instance().isJoystickConnected(i)){
                        //std::cout << "BUTTON: " << event.getJoystickButton() << std::endl;
                        switch (i){
                            case 0:
                                //std::cout << "J1" << std::endl;
                                if(event.getJoystickButton()==0 && event.getJoystickId()==i) keys[22] = true;
                                if(event.getJoystickButton()==2 && event.getJoystickId()==i) keys[4] = true;
                                if(event.getJoystickButton()==3 && event.getJoystickId()==i) keys[28] = true;
                                break;
                            case 1:
                                //std::cout << "J2" << std::endl;
                                if(event.getJoystickButton()==0 && event.getJoystickId()==i) keys[73] = true;
                                if(event.getJoystickButton()==2 && event.getJoystickId()==i) keys[4] = true;
                                if(event.getJoystickButton()==3 && event.getJoystickId()==i) keys[57] = true;
                                break;
                            case 2:
                                //std::cout << "J3" << std::endl;
                                if(event.getJoystickButton()==0 && event.getJoystickId()==i) keys[14] = true;
                                if(event.getJoystickButton()==2 && event.getJoystickId()==i) keys[4] = true;
                                if(event.getJoystickButton()==3 && event.getJoystickId()==i) keys[8] = true;
                                break;
                            case 3:
                                //std::cout << "J4" << std::endl;
                                if(event.getJoystickButton()==0 && event.getJoystickId()==i) keys[6] = true;
                                if(event.getJoystickButton()==2 && event.getJoystickId()==i) keys[4] = true;
                                if(event.getJoystickButton()==3 && event.getJoystickId()==i) keys[9] = true;
                                break;
                        }
                    }
                }
                break;
            case renderEngine::rEvent::EventType::JoystickButtonReleased :
                //std::cout << "BUTTON: " << event.getJoystickButton() << std::endl;
                for(int i=0 ; i<getPlayers()->size() ; i++){
                    if(renderEngine::Instance().isJoystickConnected(i)){
                        //std::cout << "BUTTON: " << event.getJoystickButton() << std::endl;
                        switch (i){
                            case 0:
                                //std::cout << "J1" << std::endl;
                                if(event.getJoystickButton()==0 && event.getJoystickId()==i) keys[22] = false;
                                if(event.getJoystickButton()==2 && event.getJoystickId()==i) keys[4] = false;
                                if(event.getJoystickButton()==3 && event.getJoystickId()==i) keys[28] = false;
                                break;
                            case 1:
                                //std::cout << "J2" << std::endl;
                                if(event.getJoystickButton()==0 && event.getJoystickId()==i) keys[73] = false;
                                if(event.getJoystickButton()==2 && event.getJoystickId()==i) keys[4] = false;
                                if(event.getJoystickButton()==3 && event.getJoystickId()==i) keys[57] = false;
                                break;
                            case 2:
                                //std::cout << "J3" << std::endl;
                                if(event.getJoystickButton()==0 && event.getJoystickId()==i) keys[14] = false;
                                if(event.getJoystickButton()==2 && event.getJoystickId()==i) keys[4] = false;
                                if(event.getJoystickButton()==3 && event.getJoystickId()==i) keys[8] = false;
                                break;
                            case 3:
                                //std::cout << "J4" << std::endl;
                                if(event.getJoystickButton()==0 && event.getJoystickId()==i) keys[6] = false;
                                if(event.getJoystickButton()==2 && event.getJoystickId()==i) keys[4] = false;
                                if(event.getJoystickButton()==3 && event.getJoystickId()==i) keys[9] = false;
                                break;
                        }
                    }
                }
                break;
            case renderEngine::rEvent::EventType::JoystickMoved :
                    jAxis = event.getJoystickMoveAxis();
                    jPosition = event.getJoystickMovePosition();

                    for(int i=0 ; i<getPlayers()->size(); i++){
                        if(renderEngine::Instance().isJoystickConnected(i) && abs(event.getJoystickMovePosition())>20){
                            switch(event.getJoystickId()){
                                case 0:
                                    der = 3;
                                    izq = 0;
                                    if(jAxis == 0 && jPosition > 0 && !keys[der]){
                                        keys[der] = true;
                                        if(keys[izq]==true) keys[izq]=false;
                                    }
                                    if(jAxis == 0 && jPosition < 0 && !keys[izq]){
                                        keys[izq] = true;
                                        if(keys[der]==true) keys[der]=false;
                                    }
                                    break;
                                case 1:
                                    der = 72;
                                    izq = 71;
                                    if(jAxis == 0 && jPosition > 0 && !keys[der]){
                                        keys[der] = true;
                                        if(keys[izq]==true) keys[izq]=false;
                                    }
                                    if(jAxis == 0 && jPosition < 0 && !keys[izq]){
                                        keys[izq] = true;
                                        if(keys[der]==true) keys[der]=false;
                                    }
                                    break;
                                case 2:
                                    der = -1;
                                    izq = 10;
                                    if(jAxis == 0 && jPosition > 0 && !keys[der]){
                                        keys[der] = true;
                                        if(keys[izq]==true) keys[izq]=false;
                                    }
                                    if(jAxis == 0 && jPosition < 0 && !keys[izq]){
                                        keys[izq] = true;
                                        if(keys[der]==true) keys[der]=false;
                                    }
                                    break;
                                case 3:
                                    der = 13;
                                    izq = 21;
                                    if(jAxis == 0 && jPosition > 0 && !keys[der]){
                                        keys[der] = true;
                                        if(keys[izq]==true) keys[izq]=false;
                                    }
                                    if(jAxis == 0 && jPosition < 0 && !keys[izq]){
                                        keys[izq] = true;
                                        if(keys[der]==true) keys[der]=false;
                                    }
                                    break;
                            }
                        }
                        else if(renderEngine::Instance().isJoystickConnected(i)){
                            switch(event.getJoystickId()){
                                case 0:
                                    der = 3;
                                    izq = 0;
                                    if(jAxis == 0 && abs(jPosition) < 20 && keys[der]){
                                        keys[der] = false;
                                    }
                                    if(jAxis == 0 && abs(jPosition) < 20 && keys[izq]){
                                        keys[izq] = false;
                                    }
                                    break;
                                case 1:
                                    der = 72;
                                    izq = 71;
                                    if(jAxis == 0 && abs(jPosition) < 20 && keys[der]){
                                        keys[der] = false;
                                    }
                                    if(jAxis == 0 && abs(jPosition) < 20 && keys[izq]){
                                        keys[izq] = false;
                                    }
                                    break;
                                case 2:
                                    der = -1;
                                    izq = 10;
                                    if(jAxis == 0 && abs(jPosition) < 20 && keys[der]){
                                        keys[der] = false;
                                    }
                                    if(jAxis == 0 && abs(jPosition) < 20 && keys[izq]){
                                        keys[izq] = false;
                                    }
                                    break;
                                case 3:
                                    der = 13;
                                    izq = 21;
                                    if(jAxis == 0 && abs(jPosition) < 20 && keys[der]){
                                        keys[der] = false;
                                    }
                                    if(jAxis == 0 && abs(jPosition) < 20 && keys[izq]){
                                        keys[izq] = false;
                                    }
                                    break;
                            }

                        }
                    }
                break;

            case renderEngine::rEvent::EventType::KeyPressed :
                keys[event.getKeyCode()] = true;
                //    std::cout << "Tecla " << event.getKeyCode() << std::endl;

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
        //sfml->Instance().ChangeState(MPuntuaciones::Instance());                 //P
    }
}

void Juego::Update(){

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

        float window_width = static_cast<float>(renderEngine::Instance().getSize()[0]);
        float window_height = static_cast<float>(renderEngine::Instance().getSize()[1]);
        float zoom = (1005*target_zoom)/window_height;

        view->setSize(window_width, window_height);
        view->zoom(zoom);
        renderEngine::Instance().setView(*view);

        rain.setPosition(view->getCenter()[0], view->getCenter()[1]-renderEngine::Instance().getViewSize()[1]/2 -120);
        minirain.setPosition(view->getCenter()[0], view->getCenter()[1]-renderEngine::Instance().getViewSize()[1]/2 -120);

        // LÓGICA DE LOS NPC Y JUGADORES
        for(int i=0; i< readyPlayer.size(); i++){
            readyPlayer[i]->movement();
        }

        Mapa::Instance().update();
        rain.update();
        minirain.update();

        // BUCLE DE STEPS DE BOX2D
        for(int i = 0; i < FRAMERATE/UPDATE_STEP; i++){
            physicsEngine::Instance().updateWorld(BOX2D_STEP);
        }

        accumulator -= 1/UPDATE_STEP;

        // ACTUALIZO EL ESTADO ACTUAL
        for(int i=0; i< readyPlayer.size(); i++){
            readyPlayer[i]->newState();
        }
        Mapa::Instance().newState();
        rain.newState();
        minirain.newState();
    }
}

void Juego::Render(){
    //std::cout << "RENDER == " << tick << std::endl;

    renderEngine::Instance().clear('w');

    // TICK PARA LA INTERPOLAÇAO
    tick = std::min(1.f, static_cast<float>( accumulator/(1/UPDATE_STEP) ));

    //ACTUALIÇAÇAO DEL PERSONAJE
    for(int i=0; i< readyPlayer.size(); i++){
        readyPlayer[i]->update();
        readyPlayer[i]->interpola(tick);
    }


    //ACTUALIÇAÇAO DE LA CAMARA
    if(!Mapa::Instance().getInit()){
        //LA CAMARA SE MUEVE DEPENDIENDO DE LA ALTURA DE LOS JUGADORES
        if(readyPlayer[0]->getYPosition()>view->getCenter()[1]){
            view->setCenter(readyPlayer[0]->getXPosition(), readyPlayer[0]->getYPosition());
        }
    }
    else if(!mj_t::Instance().isTetrisOn() && !boss::Instance().isBossOn()){    //TRUE: SE MUEVE LA CAMARA
        int n=0;
        for(int i=0; i< readyPlayer.size(); i++){
            if(cameraDirection == 0){

                if(readyPlayer[i]->getXPosition() > readyPlayer[n]->getXPosition()){
                    n=i;
                }
            }
            else{

                if(readyPlayer[i]->getYPosition() < readyPlayer[n]->getYPosition()){
                    n=i;
                }
            }
        }
        //std::cout << readyPlayer[0]->getXPosition() << ", " << readyPlayer[0]->getYPosition() << std::endl;

        //COMENTAR EL IF SI SE QUIERE QUE LA CAMARA VAYA HACIA ATRAS
        float m;
        float difference;

        if(cameraDirection == 0){
            difference = readyPlayer[n]->getXPosition() - view->getCenter()[0];
            if( difference > 12 ){
                m = difference;
                view->move(abs(m) / 15, 0);
            }

        }
        else{
            difference = readyPlayer[n]->getYPosition()-210 - view->getCenter()[1];
            if(difference < -12){
                m = difference;
                view->move(0, -abs(m) / 15);
            }
            trimCamera();
        }

        //view->setCenter(view->getCenter()[0]+12, Mapa::Instance().getYMax()+1400);        // <- Esta línea hace que recorra el mapa la camara
                                                                                            // Si solo ves nubes, es porque se ha generado el minijueg de subir, y la altura se ha puesto automáticamente ahí, np.

    }



    renderEngine::Instance().setView(*view);

    //ACTUALIÇAÇAO DEL MAPA
    Mapa::Instance().updateMini();

    Mapa::Instance().renderBackground();

    renderEngine::Instance().setView(*view);
    minirain.draw(tick);
    rain.draw(tick);
    Mapa::Instance().render(tick);

    hud->render();

    renderEngine::Instance().display();
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
    delete view;
    view = nullptr;
    delete backgroundView;
    backgroundView = nullptr;
    std::cout << "Destroying game==================================" << std::endl;
}

std::vector<Player*>* Juego::getPlayers() {
    return &readyPlayer;
}

renderEngine::rView* Juego::getPrincipalView() {
    return view;
}

void Juego::switchCameradirection() {
    cameraDirection = (cameraDirection == 0) ? 1 : 0;
    Mapa::Instance().setCameraDirection(cameraDirection);
}

void Juego::trimCamera() {
    view->setCenter(view->getCenter()[0], static_cast<int>(view->getCenter()[1]));
    if(static_cast<int>(view->getCenter()[1]) % 2 != 0)
        view->move(0, 1);
}

void Juego::changeRain() {
    rain.setParticleSpeed(220);                     // Velocidad lineal de las partículas
    rain.setGenerationTimer(200);                     // Tiempo (ms) de delay entre la generación de partículas (En este caso se genera una partícula cada 4 ms)
    rain.setParticleLifeTime(2);                    // Tiempo de vida en segundos, de vida d elas partículas
    rain.setParticleDirection(0, 1);             // Dirección de las partículas, debe ser un número entre 0 y 1
          
    minirain.setParticleSpeed(200);                                  
    minirain.setGenerationTimer(150);                  
    minirain.setParticleLifeTime(2);
    minirain.setParticleDirection(0, 1);
}
