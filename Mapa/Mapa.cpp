/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mapa.cpp
 * Author: pablomanez
 * 
 * Created on 23 de febrero de 2018, 15:42
 */

#include <random>
#include <iostream>
#include <complex>

#include "Mapa.h"
#include "Nodo/Minijuegos/goingUp.h"
#include <math.h>

#define SCALE 65.f
#define MAP_ITERATION 0
#define TAM_LISTA 7
#define BACKGROUND_SCALE 1.9
#define altura_minijuego 9

 Mapa::Mapa() {
    std::cout << "Creando mapa..." << std::endl;
    
    //CARGA DEL DOCUMENTO
    doc.LoadFile("tiles_definitivo/tiles_fv.tsx");
    
    //GUARDO ANCHO Y ALTO
    tinyxml2::XMLDocument *d_aux = doc.GetDocument();
    
    ancho = atoi(d_aux->FirstChildElement("tileset")->Attribute("tilewidth"));
    alto = atoi(d_aux->FirstChildElement("tileset")->Attribute("tileheight"));
    
    Factory::Instance().setTileSize(ancho, alto);
    
    //ALMACENO LA INFORMACION DE LAS TILES
    tinyxml2::XMLElement *map;
    map = doc.FirstChildElement("tileset")->FirstChildElement("tile");
    
    //ANYADO EL PATH DE LA CARPETA
    
    int n = 37; //NUMERO TOTAL DE TILES
                //SI SE CAMBIA, CAMBIAR TAMBIEN _tile *tiles[37] EN EL .h;
    
    //LEO EL TILESHEET Y ALMACENO LOS CUADRADOS DE RECORTE
    ts1 = "tiles_definitivo/tilesheet.png";
    ts2 = "tiles_definitivo/tilesheet2.png";
    ts.loadFromFIle(ts1);
    ts_doc.LoadFile("tiles_definitivo/xml_spritesheet.xml");
    map = ts_doc.FirstChildElement("TextureAtlas")->FirstChildElement("sprite");
    
    for(int i=0 ; i<n ; i++){
        
        int x = atoi(map->Attribute("x"));
        int y = atoi(map->Attribute("y"));
        int w = atoi(map->Attribute("w"));
        int h = atoi(map->Attribute("h"));
        
        // Este y+1 es igual de mierda a lo que Using namespace std; es al std::
        renderEngine::rIntRect ir_aux(x,y,w,h);
        
        spriteSheetRects.push_back(ir_aux);
 
            //std::cout << tiles[i]->id << " -> " << tiles[i]->path << "      INTRECT-> X: " << tiles[i]->ir.left << ", Y: " << tiles[i]->ir.top << ", W: " << tiles[i]->ir.widht << ", H: " << tiles[i]->ir.height << std::endl;

        map = map->NextSiblingElement("sprite");
    }
    
    //INICIALIZO LA MATRIZ DE ADYACENCIA
    InitMatrix();

    //-----------VARIABLES DE CLASE-----------//
    pop = false;
    
    //LO UTILIZO AL LEER TODOS LOS NODOS DE LA MATRIZ
    x_max = 0;
    y_max = 0;
    
    //TETRIS
    mj_t *tetris;
    tetris->Instance();     //INICIALIZO EL SINGLETON
    m_tetris = false;
    
    //BOSS
    boss *javi;
    javi->Instance();       //INICIALIZO EL BOSS  
    
    longitud = 0;
    end = false;
    
    //img_fondo.loadFromFIle("assets/fondo.PNG");
    //f1.t.loadFromImage(f1.img,*f1.ir);
    x_view = -1;
    y_view = -1;
    text_fondo.loadFromFile("assets/fondo.PNG");

    f1.setTexture(text_fondo);
    f1.setSize(1920*BACKGROUND_SCALE,1080*BACKGROUND_SCALE);
    
    f2.setTexture(text_fondo);
    f2.setSize(1920*BACKGROUND_SCALE,1080*BACKGROUND_SCALE);
    
    DEATH.setOutlineThickness(2.f);
    DEATH.setFillColor('t');
    DEATH.setOutlineColor('r');
    DEATH.setSize(8000, 400);
    DEATH.setOrigin(DEATH.getSize()[0]/2, DEATH.getSize()[1]/2);
    
    cameraDir = 0;
    direction = 0;
    debug.setFillColor('r');
    debug.setSize(20, 20);
    debug.setOrigin(10,10);
    debug.setPosition(1330, 1050+845-70*3);
    
    //LeeNodo("tiles_definitivo/nodos/0.tmx");
    
    Factory::Instance().LeeNodo("tiles_definitivo/nodos/15.tmx");
    
    std::string path;
    for(int i = 0; i < 16; ++i){
        path = "tiles_definitivo/nodos/";
        std::string number = std::to_string(i);
        path = path.operator +=(number);
        path = path.operator +=(".tmx");
        
        Factory::NodeStruct n;
        n = Factory::Instance().LeeNodo(path);
        
        NODOS.push_back(n);
    }
    
    
    for(int i = 1; i < 10; ++i){
        path = "tiles_definitivo/nodos/Up/Mininode_";
        std::string number = std::to_string(i);
        path = path.operator +=(number);
        path = path.operator +=(".tmx");
        
        Factory::NodeStruct n;
        n = Factory::Instance().LeeNodo(path);
        
        MININODOS.push_back(n);
    }
    BOSS = Factory::Instance().LeeNodo("tiles_definitivo/nodos/fin.tmx");
    
}

//INICIALIZAR LA MATRIZ DE ADYACENCIA
void Mapa::InitMatrix() {
    //////////////////////////////
    // SI SE MODIFICA, ENTONCES //
    // CAMBIAR TAMBIEN EL .h !! //
    //////////////////////////////
    
    //  v es n x n
    //  n = 15

    int aux[16][16] = {
        
    /* ================================ NODOS ==============================  */
    /*        0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15     */
    /*    ¯¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|      */
    /*  0 */  0,  1,  1,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,
    /*  1 */  0,  0,  1,  1,  1,  1,  1,  1,  0,  0,  1,  0,  0,  0,  1,  1,
    /*  2 */  0,  1,  0,  1,  1,  1,  1,  1,  0,  0,  1,  0,  0,  0,  0,  1,
    /*  3 */  0,  1,  1,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  1,
    /*  4 */  0,  0,  1,  1,  1,  0,  1,  1,  0,  0,  1,  1,  0,  1,  0,  1,
    /*  5 */  0,  0,  0,  1,  0,  0,  1,  1,  1,  0,  0,  1,  0,  1,  0,  0,
    /*  6 */  0,  1,  1,  1,  1,  1,  0,  1,  1,  0,  0,  1,  0,  1,  0,  0,
    /*  7 */  0,  0,  0,  0,  1,  0,  1,  0,  1,  1,  0,  0,  1,  0,  0,  1,
    /*  8 */  0,  0,  0,  0,  1,  0,  0,  0,  1,  1,  0,  0,  1,  0,  0,  1,
    /*  9 */  0,  1,  0,  1,  0,  1,  0,  1,  1,  0,  1,  0,  1,  1,  1,  1,
    /* 10 */  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  1,  1,  0,  0,  0,
    /* 11 */  0,  1,  1,  1,  0,  1,  0,  0,  1,  1,  1,  0,  1,  1,  1,  1,
    /* 12 */  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  1,  0,  1,  0,  1,
    /* 13 */  0,  0,  0,  1,  1,  0,  0,  0,  1,  0,  0,  1,  1,  0,  1,  1,
    /* 14 */  0,  1,  0,  0,  0,  1,  1,  0,  1,  0,  1,  0,  1,  1,  1,  0,
    /* 15 */  0,  1 , 1,  1,  1,  0,  0,  1,  1,  1,  0,  1,  1,  1,  0,  0      
    };

    for(int i = 0; i < 16; i++)
        for(int j = 0; j < 16; j++)
            if(aux[i][j] == 1)
                matriz_v2[i].push_back(j);
}

// CONSTRUYE EL NODO i DEL VECTOR "NODOS" QUE CONTIENE LA INFORMACIÓN NECESARIA PARA CREARLO
void Mapa::CargaNodo(std::list<Nodo> &lista, Factory::NodeStruct const& nodo, int &x_, int &y_) {

    lista.emplace_back();
    
    int randomX = 0;
    int randomY = 0;
    
    if(direction == 1)
        y_ -= nodo.map_height*nodo.tile_height;
    
    lista.back().setRectVector(spriteSheetRects);
    
    // CARGO LAS TILES
    for(int i = 0; i < nodo.Tiles.size(); ++i)
        lista.back().addTile(nodo.Tiles[i].id, x_ + nodo.Tiles[i].x, y_ + nodo.Tiles[i].y);
    
    // CARGO EL SUELO
    for(int i = 0; i < nodo.Grounds.size(); ++i){
        std::vector<std::array<int, 2>> newCoords;
        for(int j = 0; j < nodo.Grounds[i].coords.size(); ++j){
            std::array<int, 2> updated;
            updated[0] =  x_ + nodo.Grounds[i].coords[j][0];
            updated[1] =  y_ + nodo.Grounds[i].coords[j][1];
            newCoords.push_back(updated);
        }
        lista.back().addGround(newCoords);
        newCoords.clear();
    }
    
    // CARGO LAS XPLOTATOS
    for(int i = 0; i < nodo.xPlotatos.size(); ++i){
        randomX = physicsEngine::Instance().genIntRandom(nodo.xPlotatos[i].xMin, nodo.xPlotatos[i].xMax);
        lista.back().addxPlotato(x_ + randomX, y_ + nodo.xPlotatos[i].y, x_ + nodo.xPlotatos[i].xMin, x_ + nodo.xPlotatos[i].xMax);
    }
    
    // CARGO LOS SKULLS
    for(int i = 0; i < nodo.Skulls.size(); ++i){
        randomX = physicsEngine::Instance().genIntRandom(nodo.Skulls[i].xMin, nodo.Skulls[i].xMax);
        randomY = physicsEngine::Instance().genIntRandom(nodo.Skulls[i].yMin, nodo.Skulls[i].yMax);
        lista.back().addSkull(x_ + randomX, y_ + randomY, x_ + nodo.Skulls[i].xMin, x_ + nodo.Skulls[i].xMax, y_ + nodo.Skulls[i].yMin, y_ + nodo.Skulls[i].yMax);
    }
    
    // CARGO LOS POWERS
    for(int i = 0; i < nodo.Powers.size(); ++i){
        lista.back().addPower(nodo.Powers[i].id, x_ + nodo.Powers[i].xMin, x_ + nodo.Powers[i].xMax, y_ + nodo.Powers[i].y);
    }
    
    // CARGO LOS PUNTOS DE CONTROL
    for(int i = 0; i < nodo.Checkpoints.size(); ++i){
        checkPoint checkpoint;
        checkpoint.active = false;
        checkpoint.shape.setSize(nodo.Checkpoints[i].width, nodo.Checkpoints[i].height);
        checkpoint.shape.setPosition(x_ + nodo.Checkpoints[i].x, y_ + nodo.Checkpoints[i].y);
        checkpoint.shape.setOutlineThickness(2);
        checkpoint.shape.setOutlineColor('r');
        checkpoint.shape.setFillColor('t');
        every_points.push_back(checkpoint);
    }
    
    // MINIJUEGO
    if(nodo.minijuego.type == 1){
        std::cout << "GOING UP GENERADO!" << std::endl;
        std::vector<int> IDs_mininodo;
        for(int i = 0; i < altura_minijuego; ++i){
            IDs_mininodo.push_back(physicsEngine::Instance().genIntRandom(0, 7));
        }
        
        Minijuego* mini = lista.back().addMinigame(nodo.minijuego.type, x_ + nodo.minijuego.x, y_ + nodo.minijuego.y, nodo.minijuego.width, nodo.minijuego.height, IDs_mininodo);
        
        for(int i = 0; i < IDs_mininodo.size(); ++i){
            y_ -= MININODOS[IDs_mininodo[i]].map_height*MININODOS[IDs_mininodo[i]].tile_height;
        }
        y_ += 2*nodo.tile_height;
        
        bool flag;
        for(int i = 0; i < 16; i++){
            flag = false;
            for(int j = 0; j < matriz_v2[i].size() && !flag; j++)
                if(matriz_v2[i][j] == 15){
                    matriz_v2[i].erase(matriz_v2[i].begin()+j);
                    flag = true;
                }
        }
    }
    
    if(direction == 0)
        x_ += nodo.map_width * nodo.tile_width;
    
    lista.back().setPop(x_);
}




/*
        
 */

void Mapa::render(float tick_) {
    renderEngine *sfml;

    //------------|  CASILLAS DEL MAPA  |------------//
    int x = sfml->Instance().getViewCenter()[0];
    int y = sfml->Instance().getViewCenter()[1];
    int iterator = 0;
    
    //int w = sfml->Instance().getSize()[0];
    //int h = sfml->Instance().getSize()[1];
    int w = 1920;
    int h = 1080;
    int xa = x-w-ancho;
    int ya = y-h-alto;
    
    //w = 1366
    //h = 739
    renderEngine::rIntRect ir(xa,ya,(w*2)+70,(h*2)+70);
        //std::cout << "LEFT: " << ir.left << " | TOP: " << ir.top << " | WIDHT: " << ir.widht << " | HEIGHT: " << ir.height << std::endl;
    
    int i=0;
    
    //REDONDEO LA COORDENADA x
    int x_2;
    i = x/ancho+1;
    x_2 = i*ancho;

    //REDONDEO LA COORDENADA y
    int y_2;
    i = y/alto+1;
    y_2 = i*alto;

    int x_min_ = x_2 -(ancho*26);
    int x_max_ = x_2 +(ancho*24);
    
    /*
    int y_min = y_2 -(alto*15);
    int y_max = y_2 +(alto*15);
    */
    
    //EMPIEZO A RENDERIZAR
    f1.draw();
    f2.draw();

    for(std::list<Nodo>::iterator it=hex_list.begin(); it!=hex_list.end(); ++it){
       
        (*it).draw(tick_, ir, x_min_, x_max_);
        
        if(direction == 0 && iterator == TAM_LISTA/2-1 && (*it).getPop() < sfml->Instance().getViewCenter()[0]){
            pop = true;
        }
        else if(direction == 1 && iterator == TAM_LISTA/2-1 && (*it).getPop() > sfml->Instance().getViewCenter()[1]){
            pop = true;
        }
        iterator++;
    }

    //------------|  CHECKPOINTS - DEBUG  |------------//
    std::list<checkPoint>::iterator it = active_points.begin();
    while(it != active_points.end()){
        (*it).shape.draw();
        ++it;
    }
    
    DEATH.draw();
    
    it = every_points.begin();
    while(it != every_points.end()){
        (*it).shape.draw();
        ++it;
    }
    
    
    //------------|  TETRIS  |------------//
    for(int i=0 ; i<power.size() ; i++){
        power[i].draw();
    }
    
    //------------|  TETRIS  |------------//
    mj_t *tetris;            //std::cout << path << std::endl;

    tetris->Instance().render();
    
    //------------|  BOSS  |------------//
    boss *javi;
    javi->Instance().render();
    
    debug.draw();
}

//LEE LA MATRIZ DE ADYACENCIA
void Mapa::CreaMapa() {
    
    
    nodo_actual = 15;
    CargaNodo(hex_list, NODOS[nodo_actual], x_max, y_max);

    checkPoint first;
    first = every_points.front();
    active_points.push_back(first);
    active_points.front().active = true;
    active_points.front().shape.setOutlineColor('g');
    maxPoint = active_points.front().shape.getPosition()[0];

    every_points.erase(every_points.begin());
    
    //EMPIEZA A LEER LA MATRIZ
    int iter = 0;   //CUENTA EL NUMERO DE ITERACIONES
    
    for(; iter<std::min(TAM_LISTA, MAP_ITERATION); iter++) {
        leeRandom();
    }
    
}

void Mapa::leeRandom(){
    //GENERO EL NUMERO ALEATORIO
    int r = physicsEngine::Instance().genIntRandom(0, matriz_v2[nodo_actual].size()-1);
    
    int target = matriz_v2[nodo_actual][r];
    
    std::string path = "tiles_definitivo/nodos/";
    std::string rand = std::to_string(target);
    path = path.operator +=(rand);
    path = path.operator +=(".tmx");
    
    std::cout << path << std::endl;
    //std::cout << "Nodo actual " << nodo_actual << " | Next " << target << std::endl;

    CargaNodo(hex_list, NODOS[target], x_max, y_max);
    longitud++;

    if(target == 6 && !m_tetris) {
        
        //DETECTA QUE YA SE HA DIBUJADO EL MINIJUEGO
        std::cout << "He creado el minijuego Tetris" << std::endl;

        //Borro el nodo Tetris de todos los vectores
        bool flag;
        for(int i = 0; i < 16; i++){
            flag = false;
            for(int j = 0; j < matriz_v2[i].size() && !flag; j++)
                if(matriz_v2[i][j] == 6){
                    matriz_v2[i].erase(matriz_v2[i].begin()+j);
                    flag = true;
                }
        }

        //CREO LA CLASE TETRIS
        mj_t *tetris;
        tetris->Instance().init(x_max,y_max);

        m_tetris = true;
    }

    nodo_actual = target;
    
}

void Mapa::updateMini() {
    mj_t *tetris;
    boss *javi;
    
    //ACTUALIZO DEL FONDO
    updateFondo();
    
    if(pop){
        
        hex_list.pop_front();
        if(longitud < MAP_ITERATION)
            leeRandom();
        
        pop = false;
    }
    if(longitud >= MAP_ITERATION && !end){
        std::string path = "tiles_definitivo/nodos/";
        boss *javi;
        javi->Instance().init(x_max, y_max);

        path = "tiles_definitivo/nodos/fin.tmx";
            //std::cout << path << std::endl;
        std::cout << "GENERANDO BOSS... XMAX = " << x_max << " | YMAX = " << y_max << std::endl;
        CargaNodo(hex_list, BOSS, x_max, y_max);
        std::cout << "BOSS GENERADO " << "XMAX = " << x_max << " | YMAX = " << y_max << std::endl;
        end = true;
    }
    
    tetris->Instance().update();
    javi->Instance().update();
}

void Mapa::update(){
    for(std::list<Nodo>::iterator it=hex_list.begin(); it!=hex_list.end(); ++it){
        (*it).preState();
        (*it).update();
    }
    DEATH.setPosition(renderEngine::Instance().getViewCenter()[0], renderEngine::Instance().getViewCenter()[1] + renderEngine::Instance().getViewSize()[1]/2+250);
    handleCheckPoints();
}

void Mapa::updateFondo() {
    renderEngine *sfml;
    float x,y;
    float mv = 2;
    
    if(x_view == -1 && y_view == -1){
        x_view = sfml->Instance().getViewCenter()[0];
        y_view = sfml->Instance().getViewCenter()[1];
        
        x = x_view-70*27;
        y = y_view-70*15;

        f1.setPosition(x,y);
    }
    else if(x_view != sfml->Instance().getViewCenter()[0] && abs(x_view-sfml->Instance().getViewCenter()[0])>5){
        //SOLO SI SE MUEVE LA CAMARA SE ACTUALIZA LA POSICION
        bool signo; //TRUE: + , FALSE: -
        if((x_view-sfml->Instance().getViewCenter()[0])<0){
            signo = false;
        }
        else{
            signo = true;
        }
        x_view = sfml->Instance().getViewCenter()[0];
        
        x = x_view-70*27;
        y = y_view-70*15;

        //f1.rect.setPosition(x,y);
        signo ? f1.move(-mv,0) : f1.move(mv,0);
    }
    else if(y_view != sfml->Instance().getViewCenter()[1] && abs(y_view-sfml->Instance().getViewCenter()[1])>5){
        y_view = sfml->Instance().getViewCenter()[1];
        
        x = x_view-70*27;
        y = y_view-70*15;
        
        f1.setPosition(x,y);
    }
    
    f2.setPosition(f1.getPosition()[0]+f1.getSize()[0],f1.getPosition()[1]);
    
    if(f1.getPosition()[0] <= (sfml->Instance().getViewCenter()[0]-70*26)-f1.getSize()[0]){
        f1.setPosition(f2.getPosition()[0],f2.getPosition()[1]);
    }
    
}

void Mapa::preState(){
    for(std::list<Nodo>::iterator it=hex_list.begin(); it!=hex_list.end(); ++it){
        (*it).preState();   
    }
}

void Mapa::newState(){
    for(std::list<Nodo>::iterator it=hex_list.begin(); it!=hex_list.end(); ++it){
        (*it).newState();   
    }
}


Mapa::Mapa(const Mapa& orig) {
}

Mapa::~Mapa() {
}

void Mapa::setPlayers(std::vector<Player*>* ready) {
    players = ready;
}

void Mapa::handleCheckPoints() {
    bool flag;
    for(int i = 0; i< players->size(); ++i) {
        
        Player* ready = (*players)[i];
        flag = false;
        std::list<checkPoint>::iterator it = every_points.begin();
        if(cameraDir == 0){
            while(it != every_points.end()){
                if(ready->getXPosition() > (*it).shape.getPosition()[0]){
                    checkPoint aux;
                    aux = (*it);
                    aux.active = true;
                    aux.shape.setOutlineColor('g');
                    maxPoint = aux.shape.getPosition()[0];

                    if(!flag){
                        flag = true;
                        active_points.clear();
                    }

                    active_points.push_back(aux);
                    every_points.erase(it++);
                }
                else
                    ++it;
            }
        }
        else if(cameraDir == 1){
            
            while(it != every_points.end()){
                if(ready->getYPosition() < (*it).shape.getPosition()[1]){
                    checkPoint aux;
                    aux = (*it);
                    aux.active = true;
                    aux.shape.setOutlineColor('g');
                    maxPoint = aux.shape.getPosition()[1];

                    if(!flag){
                        flag = true;
                        active_points.clear();
                    }

                    active_points.push_back(aux);
                    every_points.erase(it++);
                }
                else
                    ++it;
            }
        }
        
        // COMPRUEBA SI SE HA CAÍDO DEL MAPA
        checkOutOfMap(ready);
    }
}

void Mapa::movePlayerToClosestCheckPoint(Player* ready) {
    if(!ready->isInmortal()){
        std::list<checkPoint>::iterator it = active_points.begin();

        float minX = active_points.front().shape.getPosition()[0];
        float minY = active_points.front().shape.getPosition()[1];

        float distX = minX - ready->getXPosition();
        float distY = minY - ready->getYPosition();
        float distance = sqrt(distX*distX + distY*distY);
        float aux_d;

        while(it != active_points.end()){
            if((*it).active){
                distX = (*it).shape.getPosition()[0] - ready->getXPosition();
                distY = (*it).shape.getPosition()[1] - ready->getYPosition();
                aux_d = sqrt(distX*distX + distY*distY);
                if (aux_d < distance){
                    distance = aux_d;
                    minX = (*it).shape.getPosition()[0];
                    minY = (*it).shape.getPosition()[1];
                }
            }
            ++it;
        }
        ready->setPosition(minX+35, minY+35);
    }
}

void Mapa::checkOutOfMap(Player* ready) {
    if(ready->getSprite().intersects(DEATH))
        Mapa::Instance().movePlayerToClosestCheckPoint(ready);
}

void Mapa::changeDirection(int dir) {
    direction = dir;
}

void Mapa::setCameraDirection(int i) {
    cameraDir = i;
}

int Mapa::getIterations() {
    return longitud;
}

int Mapa::getTotalIterations() {
    return MAP_ITERATION;
}

Factory::NodeStruct Mapa::getMINI(int i) {
    return MININODOS[i];
}

int Mapa::getYMax() {
    return y_max;
}
