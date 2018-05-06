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
#include "../AssetManager.h"

#define SCALE 65.f
#define MAP_ITERATION 5
#define TAM_LISTA 7
#define BACKGROUND_SCALE 1.9
#define altura_minijuego 9
#define nodoInicial 0
#define BACKGROUND_VELOCITY 2

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
    x_view = renderEngine::Instance().getViewCenter()[0];
    y_view = renderEngine::Instance().getViewCenter()[1];
    text_fondo = AssetManager::GetTexture("assets/fondo.PNG");
    background1.setTexture(text_fondo);
    background1.setPosition(-875, 200);
    background2.setTexture(text_fondo);
    background2.setPosition(-875, 200);
    background1.setScale(2, 2);
    background2.setScale(2, 2);

    f1.setTexture(text_fondo);
    f1.setSize(1920,1080);

    f2.setTexture(text_fondo);
    f2.setSize(1920,1080);

    cameraDir = 0;
    direction = 0;


    //LeeNodo("tiles_definitivo/nodos/0.tmx");

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

    for(int i = 0; i < 11; ++i){
        path = "tiles_definitivo/nodos/CAVE/";
        std::string number = std::to_string(i);
        path = path.operator +=(number);
        path = path.operator +=(".tmx");

        Factory::NodeStruct n;
        n = Factory::Instance().LeeNodo(path);

        NODOS.push_back(n);
    }
    std::cout << "NODOS " << NODOS.size() << std::endl;
    BOSS = Factory::Instance().LeeNodo("tiles_definitivo/nodos/fin.tmx");
    SPECIAL = Factory::Instance().LeeNodo("tiles_definitivo/nodos/Up/Special_1.tmx");

    secondPhase = false;
    stopBackgroundMovement = true;

    //INICIO DEL JUEGO
    bInit = false;
    initClock.restart();
    initBloques = new bloque;

    t = new physicsEngine::type;
    t->id = 1;
    t->data = this;

    float x_b = 70*8;
    float y_b = 70*15;
    float w_b = 70*27;
    float h_b = 70;

    initBloques->rs.setPosition(x_b,y_b);
    initBloques->rs.setSize(w_b,h_b);
    initBloques->rs.setFillRGBAColor(72,60,72);

    initBloques->body = physicsEngine::Instance().createBody(w_b,h_b,x_b+(w_b/2),y_b+(h_b/2),'k',t);

    initFont.loadFromFile("resources/fuente.ttf");
    initText = new renderEngine::rText;
    initText->setFont(initFont);
    initText->setCharacterSize(200);
    initText->setFillColor('k');
}

//INICIALIZAR LA MATRIZ DE ADYACENCIA
void Mapa::InitMatrix() {
    //////////////////////////////
    // SI SE MODIFICA, ENTONCES //
    // CAMBIAR TAMBIEN EL .h !! //
    //////////////////////////////

    //  v es n x n
    //  n = 15

    int aux[27][27] = {

    /* ====================================================== NODOS ==================================================== */
    /*                                                                        Nodo up!                                      */
    /*                                                                        |                                             */
    /*        0   1   2   3   4   5   6   7   8   9   10  11  12  13  14      15      16  17  18  19  20  21  22  23  24  25  26 */
    /*    ¯¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯¯¯¯¯|¯¯¯¯¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|¯¯¯|  */
    /*  0 */  0,  1,  1,  1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,      0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*  1 */  0,  0,  1,  1,  1,  1,  1,  1,  0,  0,  1,  0,  0,  0,  1,      0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*  2 */  0,  1,  0,  1,  1,  1,  1,  1,  0,  0,  1,  0,  0,  0,  0,      0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*  3 */  0,  1,  1,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,      0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*  4 */  0,  0,  1,  1,  1,  0,  1,  1,  0,  0,  1,  1,  0,  1,  0,      0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*  5 */  0,  0,  0,  1,  0,  0,  1,  1,  1,  0,  0,  1,  0,  0,  0,      0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*  6 */  0,  1,  0,  1,  1,  1,  0,  1,  1,  0,  0,  1,  0,  1,  0,      0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*  7 */  0,  0,  0,  0,  1,  0,  1,  0,  1,  1,  0,  0,  1,  0,  0,      0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*  8 */  0,  0,  0,  0,  1,  0,  0,  0,  1,  1,  0,  0,  1,  0,  0,      0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /*  9 */  0,  1,  0,  1,  0,  1,  0,  1,  1,  0,  1,  0,  1,  1,  1,      0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /* 10 */  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0,  1,  1,  0,  0,      0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /* 11 */  0,  1,  1,  1,  0,  1,  0,  0,  1,  1,  1,  0,  1,  1,  1,      0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /* 12 */  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  1,  0,  1,  0,      0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /* 13 */  0,  0,  0,  1,  1,  0,  0,  0,  1,  0,  0,  1,  1,  0,  1,      0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    /* 14 */  0,  1,  0,  0,  0,  1,  1,  0,  1,  0,  1,  0,  1,  1,  1,      0,      0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,


    /* 15 */  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,      1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,

    // CUEVA___________________________________________________________________________________________________________________
    /* 16 */  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,      0,  1,  0,  0,  0,  1,  0,  0,  1,  1,  1,
    /* 17 */  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,      0,  0,  1,  0,  1,  1,  0,  0,  1,  1,  0,
    /* 18 */  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,      0,  0,  0,  1,  0,  0,  1,  1,  0,  0,  0,
    /* 19 */  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,      0,  0,  1,  0,  1,  1,  0,  0,  1,  1,  0,
    /* 20 */  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,      0,  1,  0,  0,  1,  1,  0,  0,  1,  1,  1,
    /* 21 */  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,      0,  0,  0,  1,  0,  0,  1,  1,  0,  0,  0,
    /* 22 */  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,      0,  0,  0,  1,  0,  0,  1,  1,  0,  0,  0,
    /* 23 */  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,      0,  1,  0,  0,  1,  1,  0,  0,  1,  1,  1,
    /* 24 */  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,      0,  0,  1,  0,  1,  1,  0,  0,  1,  1,  0,
    /* 25 */  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,      0,  0,  1,  0,  1,  1,  0,  0,  1,  1,  0,
    /* 26 */  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,      0,      0,  1,  0,  0,  1,  1,  0,  0,  1,  1,  1

    };

    for(int i = 0; i < 27; i++)
        for(int j = 0; j < 27; j++)
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

    lista.back().setSpriteSheet(ts1);
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

    // CARGO LAS LUCES
    for(int i = 0; i < nodo.Lights.size(); ++i){
        lista.back().addLight(x_ + nodo.Lights[i].x, y_ + nodo.Lights[i].y);
    }

    // MINIJUEGO
    if(nodo.minijuego.type == 1){
        std::cout << "GOING UP GENERADO!" << std::endl;
        std::vector<int> IDs_mininodo;
        for(int i = 0; i < altura_minijuego; ++i){
            IDs_mininodo.push_back(physicsEngine::Instance().genIntRandom(0, 7));
        }

        Minijuego* mini = lista.back().addMinigame(nodo.minijuego.type, x_ + nodo.minijuego.x, y_ + nodo.minijuego.y, nodo.minijuego.width, nodo.minijuego.height, IDs_mininodo);

        y_ += nodo.minijuego.y;
        y_ += nodo.minijuego.height;
        y_ -= 70*2;

        for(int i = 0; i < IDs_mininodo.size(); ++i){
            y_ -= MININODOS[IDs_mininodo[i]].map_height*MININODOS[IDs_mininodo[i]].tile_height;
        }

        y_ -= MININODOS[8].map_height*MININODOS[8].tile_height;
        y_ += 14*MININODOS[8].tile_height;
        x_ += MININODOS[8].map_width * MININODOS[8].tile_width - nodo.minijuego.width;

        std::vector<renderEngine::rSprite> superiorLayer;
        for(int i = 0; i < SPECIAL.Tiles.size(); ++i){
            renderEngine::rSprite sprite;
            sprite.setTexture(AssetManager::GetTexture(ts1));
            int x_special = x_ + nodo.map_width * nodo.tile_width - SPECIAL.map_width * SPECIAL.tile_width;
            int y_special = y_;
            sprite.setTextureRect(spriteSheetRects[SPECIAL.Tiles[i].id]);
            sprite.setPosition(x_special + SPECIAL.Tiles[i].x, y_special + SPECIAL.Tiles[i].y);
            superiorLayer.push_back(sprite);
        }
        transportation.setOutlineThickness(2);
        transportation.setPosition(x_ + nodo.map_width * nodo.tile_width - 7*70, y_);
        transportation.setSize(7*70, MININODOS[8].map_height*MININODOS[8].tile_height);
        lista.back().addSuperiorLayer(superiorLayer);
        superiorLayer.clear();
        renderEngine::rSprite degradado;
        degradado.setScale(2, 2);
        degradado.setTexture(AssetManager::GetTexture("assets/Degradado.png"));
        degradado.setPosition(x_ + nodo.map_width * nodo.tile_width - AssetManager::GetTexture("assets/Degradado.png").getXSize()*2, y_);
        superiorLayer.push_back(degradado);
        lista.back().addSuperiorLayer(superiorLayer);
        finisher = x_ + nodo.map_width * nodo.tile_width;
    }

    if(direction == 0){
        x_ += nodo.map_width * nodo.tile_width;
        renderEngine::rRectangleShape r;
        r.setFillColor('r');
        r.setSize(20, 20);
        r.setOrigin(10,10);
        r.setPosition(x_max, y_max);
        debug.push_back(r);
    }

    lista.back().setPop(x_);
}

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

    for(std::list<Nodo>::iterator it=hex_list.begin(); it!=hex_list.end(); ++it){

        (*it).draw(tick_, ir, x_min_, x_max_);

        if(iterator == TAM_LISTA/2-1 && (*it).getPop() < sfml->Instance().getViewCenter()[0]){
            pop = true;
        }

        iterator++;
    }

    //------------|  BLOQUE DE INICIO |------------//
    if(initBloques) initBloques->rs.draw();

    //------------|  CHECKPOINTS - DEBUG  |------------//
    std::list<checkPoint>::iterator it = active_points.begin();
    while(it != active_points.end()){
        (*it).shape.draw();
        ++it;
    }

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


    //JUGADORES
    for(int i=0; i< players->size(); i++){
        (*players)[i]->draw();
    }

    for(std::list<Nodo>::iterator it=hex_list.begin(); it!=hex_list.end(); ++it){
        (*it).drawSuperiorLayer(ir);
    }

    //------------|  TEXTO DE INICIO  |------------//
    if(initText) initText->draw();
}

//LEE LA MATRIZ DE ADYACENCIA
void Mapa::CreaMapa() {

    nodo_actual = nodoInicial;
    CargaNodo(hex_list, NODOS[nodo_actual], x_max, y_max);

    checkPoint first;
    first = every_points.front();
    active_points.push_back(first);
    active_points.front().active = true;
    active_points.front().shape.setOutlineColor('g');

    every_points.erase(every_points.begin());

    //EMPIEZA A LEER LA MATRIZ
    int iter = 0;   //CUENTA EL NUMERO DE ITERACIONES

    for(; iter<std::min(TAM_LISTA, MAP_ITERATION); iter++) {
        leeRandom();
    }

}

void Mapa::leeRandom(){
    //GENERO EL NUMERO ALEATORIO
    int r;
    int target;

    if(longitud == MAP_ITERATION/2){
        CargaNodo(hex_list, NODOS[15], x_max, y_max);
        ts1 = "tiles_definitivo/tilesheet2.png";
        secondPhase = true;
        target = 15;
    }
    else {
        r = physicsEngine::Instance().genIntRandom(0, matriz_v2[nodo_actual].size()-1);
        target = matriz_v2[nodo_actual][r];
        CargaNodo(hex_list, NODOS[target], x_max, y_max);
    }

    longitud++;

    if(target == 6 && !m_tetris) {

        //DETECTA QUE YA SE HA DIBUJADO EL MINIJUEGO
        std::cout << "He creado el minijuego Tetris" << std::endl;

        //Borro el nodo Tetris de todos los vectores
        bool flag;
        for(int i = 0; i < 15; i++){
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

    //UPDATE DEL INICIO DEL JUEGO
    updateInit();

    //ACTUALIZO DEL FONDO
    updateFondo();

    if(pop){

        hex_list.pop_front();
        if(longitud < MAP_ITERATION)
            leeRandom();

        pop = false;
    }
    if(longitud >= MAP_ITERATION && !end){
        boss *javi;
        javi->Instance().init(x_max, y_max);

        CargaNodo(hex_list, BOSS, x_max, y_max);
        end = true;
    }

    tetris->Instance().update();
    javi->Instance().update();
}

void Mapa::updateInit() {
    if(!bInit){
        float x_text = renderEngine::Instance().getViewCenter()[0];
        float y_text = renderEngine::Instance().getViewCenter()[1];
        initText->setPosition(x_text,y_text);

        float time = initClock.getElapsedTime().asSeconds();
        if(time < 5){
            initText->setString("Get ready!");
        }
        else if(time > 5 && time < 8){
            //PARA QUE LA CUENTA ATRAS SALGA COMO 3,2,1
            initText->setString(std::to_string(static_cast<int>(-(time-9))));
        }
        else if(time > 8 && time < 8.5){
            initText->setString("MEAT");
        }
        else if(time > 8.5 && time < 9){
            initText->setString("MEAT STARTO!");
        }
        else if(time > 9){
            //std::cout << "MEAT STARTO!" << std::endl;
            bInit = true;

            //ELIMINAR TODO LO DEL INIT
            physicsEngine::Instance().detroyBody(initBloques->body);
            delete initBloques;
            initBloques = NULL;
            delete initText;
            initText = NULL;
        }

        if(initText) initText->setOrigin(initText->getSize()[0]/2,initText->getSize()[1]/2);
    }
}

void Mapa::update(){
    for(std::list<Nodo>::iterator it=hex_list.begin(); it!=hex_list.end(); ++it){
        (*it).preState();
        (*it).update();
    }
    handleCheckPoints();
    for(int i = 0; i< players->size(); ++i) {
        Player* ready = (*players)[i];
        if(ready->getSprite().intersects(transportation)){
            text_fondo = AssetManager::GetTexture("assets/bg.jpg");
            background1.setTexture(text_fondo);
            background2.setTexture(text_fondo);
            ready->transportToSecondPhase(transportation.getPosition()[0] + 27*70, transportation.getPosition()[1] + 20*70);
            Juego::Instance().changeRain();
        }
    }
}

void Mapa::renderBackground() {
    //EMPIEZO A RENDERIZAR
    background1.draw();
    background2.draw();
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

        background1.setPosition(x,y);
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
        signo ? background1.setPosition(-mv+background1.getPosition()[0], background1.getPosition()[1]) : background1.setPosition(mv + background1.getPosition()[0], background1.getPosition()[1]);
    }
    else if(y_view != sfml->Instance().getViewCenter()[1] && abs(y_view-sfml->Instance().getViewCenter()[1])>5){
        y_view = sfml->Instance().getViewCenter()[1];

        //x = x_view-70*27;
        y = y_view-70*15;

        background1.setPosition(background1.getPosition()[0],y);
    }

    background2.setPosition(background1.getPosition()[0]+text_fondo.getXSize()*2, background1.getPosition()[1]);

    if(background1.getPosition()[0] <= (sfml->Instance().getViewCenter()[0]-70*26)-text_fondo.getXSize()*2){
        background1.setPosition(background2.getPosition()[0],background2.getPosition()[1]);
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
                if(ready->getYPosition() < (*it).shape.getPosition()[1] && (*it).shape.getPosition()[0] < finisher){
                    checkPoint aux;
                    aux = (*it);
                    aux.active = true;
                    aux.shape.setOutlineColor('g');

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

void Mapa::checkOutOfMap(Player* ready) {
    if(ready->getYPosition() > renderEngine::Instance().getViewCenter()[1] + renderEngine::Instance().getViewSize()[1]/2+50)
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

void Mapa::changeSpriteSheet(std::string path) {
    ts1 = path;
}

void Mapa::stopBackground(bool flag) {
    stopBackgroundMovement = flag;
}

bool Mapa::getInit() {
    return bInit;
}
