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
#include "Nodo/NPCs/xPlotato.h"
#include "Nodo/Minijuegos/goingUp.h"
#include <math.h>

#define SCALE 65.f
#define MAP_ITERATION 0
#define TAM_LISTA 7
#define BACKGROUND_SCALE 1.9

 Mapa::Mapa() {
    std::cout << "Creando mapa..." << std::endl;
    
    //CARGA DEL DOCUMENTO
    doc.LoadFile("tiles_definitivo/tiles_fv.tsx");
    
    //GUARDO ANCHO Y ALTO
    tinyxml2::XMLDocument *d_aux = doc.GetDocument();
    
    ancho = atoi(d_aux->FirstChildElement("tileset")->Attribute("tilewidth"));
    alto = atoi(d_aux->FirstChildElement("tileset")->Attribute("tileheight"));
    
    //ALMACENO LA INFORMACION DE LAS TILES
    tinyxml2::XMLElement *map;
    map = doc.FirstChildElement("tileset")->FirstChildElement("tile");
    
    //WHILE
    tinyxml2::XMLElement *m_aux;
    
    //ANYADO EL PATH DE LA CARPETA
    
    int n = 37; //NUMERO TOTAL DE TILES
                //SI SE CAMBIA, CAMBIAR TAMBIEN _tile *tiles[37] EN EL .h;
    
    //LEO EL TILESHEET Y ALMACENO LOS CUADRADOS DE RECORTE
    ts.loadFromFIle("tiles_definitivo/tilesheet.png");
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
    
    std::cout << "MATRIZ DE ADYACENCIA" << std::endl;
    for(int i = 0; i < 16; i++){
        if(i<10)
        std::cout << "Nodo  " << i << " => ";
        else
        std::cout << "Nodo " << i << " => ";
        for(int j = 0; j < matriz_v2[i].size(); j++){
            if(matriz_v2[i][j] <10)
                std::cout << " " << matriz_v2[i][j] << ",  ";
            else
                std::cout << matriz_v2[i][j] << ",  ";
                
        }
        std::cout << std::endl;
    }

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
    

    //MAPA DE PUNTEROS A FUNCION
    mapa_funciones.insert(std::make_pair("colision", &Mapa::leeColisiones));
    mapa_funciones.insert(std::make_pair("spawn", &Mapa::leexPlotatos));
    mapa_funciones.insert(std::make_pair("skull", &Mapa::leeSkulls));
    mapa_funciones.insert(std::make_pair("power", &Mapa::leePorwerUps));
    mapa_funciones.insert(std::make_pair("checkpoint", &Mapa::leeCheckPoints));
    
    longitud = 0;
    end = false;
    
    //img_fondo.loadFromFIle("assets/fondo.PNG");
    //f1.t.loadFromImage(f1.img,*f1.ir);
    x_view = -1;
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

//LEE Y CONSTRUYE EL NODO QUE LE PASES POR PARAMETRO
void Mapa::LeeNodo(std::string const& node_path) {
    // <editor-fold defaultstate="collapsed" desc="LEO EL MAPA">
    
    int map_width;
    int map_height;

    //ABRO EL ARCHIVO
    tinyxml2::XMLDocument map_doc;
    map_doc.LoadFile(node_path.c_str());

    //CONSIGO EL ANCHO Y EL ALTO DEL NODO (Número de casillas del mapa)
    tinyxml2::XMLElement *map;
    map = map_doc.FirstChildElement("map");
    map->QueryIntAttribute("width", &map_width);
    map->QueryIntAttribute("height", &map_height);

    hex_list.emplace_back("tiles_definitivo/tilesheet.png");
    
    hex_list.back().setRectVector(spriteSheetRects);
    
    //CONSIGO EL TEXTO
    std::string v_mapa = map->FirstChildElement("layer")->FirstChildElement("data")->GetText();
    std::string partes;
    std::string p_aux;
    int x_max_aux;
    int y_max_aux;

    for (int i = 0; i < map_height; i++) {
        for (int j = 0; j < map_width; j++) {

            //ELIMINO EL SALTO DE LINEA DE CADA FILA
            v_mapa.erase(0, 1);
            
            //CONSIGO EL NUMERO
            partes = v_mapa.substr(0, 1);
            v_mapa.erase(0, 1);
            p_aux = v_mapa.substr(0, 1);

            while (p_aux != "," && p_aux != "") {
                partes = partes.operator+=(v_mapa.substr(0, 1));
                v_mapa.erase(0, 1);
                p_aux = v_mapa.substr(0, 1);
            }

            if (stoi(partes) != 0) {
                hex_list.back().addTile(stoi(partes)-1, x_max + (ancho * j), y_max + alto * i);
            }
        }
        partes = v_mapa.erase(0, 1);
    }
    
    
    if(direction == 0)
        x_max_aux = ancho * (map_width-1);
    else
        y_max_aux = alto  * (map_height-1);
    

    // </editor-fold> 
    
    tinyxml2::XMLElement *obj;
    tinyxml2::XMLElement *objMinijuego;
    
    obj = map->FirstChildElement("objectgroup");
    objMinijuego = map->FirstChildElement("objectgroup");
    std::string m = "minijuego";
    bool miniG = false;
    while(obj){

        if(m.compare(objMinijuego->Attribute("name")) == 0)
            miniG = true;
        else
            objMinijuego = objMinijuego->NextSiblingElement("objectgroup");
        
        
        //Puntero a funcion
        pFunc funcion = mapa_funciones[obj->Attribute("name")];   

        //std::cout << obj->Attribute("name") << std::endl;

        if(funcion != nullptr) (this->*funcion)(obj, hex_list.back(), x_max, y_max);

        obj = obj->NextSiblingElement("objectgroup");
        
    }

    if(miniG)
        leeMinijuego(objMinijuego, hex_list.back(), x_max, y_max);
    
    if(direction == 0){
        x_max += x_max_aux+ancho;
        hex_list.back().setPop(x_max);
    }
    else{
        y_max -= y_max_aux-alto;
        hex_list.back().setPop(y_max);
    }
    
}

void Mapa::leeColisiones(tinyxml2::XMLElement *obj, Nodo &actual, int x_starto, int y_starto){
    //CONSIGO LOS OBJETOS (COLISIONES)
    //NO COMPRUEBO SI NO TIENE COLISION, YA QUE SE SUPONE QUE TODOS LOS NODOS VAN A TENER COLISION, SI O SI
    tinyxml2::XMLElement *poly;
    int x, x2;
    int y, y2;
    std::string vertex, v_aux, v_aux2;
    std::vector<std::array<float, 2>> vec;
    renderEngine::rConvexShape *cs;

    obj = obj->FirstChildElement("object");

    while (obj) {
        x = atoi(obj->Attribute("x")); //COORDENADA X ABSOLUTA
        y = atoi(obj->Attribute("y")); //COORDENADA Y ABSOLUTA

        //============================================//
        //PARA CREAR LOS VERTICES DEL ConvexShape
        cs = new renderEngine::rConvexShape;

        //============================================//

        poly = obj->FirstChildElement("polyline"); //OBJETO POLYLINE
        vertex = poly->Attribute("points"); //STRING CON LAS COORDENADAS

        //CONSIGO EL NUMERO
        while (1) {
            for (int i = 0; i < 2; i++) {
                v_aux = vertex.substr(0, 1);
                vertex.erase(0, 1);
                v_aux2 = vertex.substr(0, 1);

                while (v_aux2 != "," && v_aux2 != " " && v_aux2 != "") {
                    v_aux = v_aux.operator+=(vertex.substr(0, 1));
                    vertex.erase(0, 1);
                    v_aux2 = vertex.substr(0, 1);
                }
                vertex.erase(0, 1);

                if (i == 0) 
                    x2 = x + x_starto + stoi(v_aux);
                else 
                    y2 = y + y_starto + stoi(v_aux);
                
            }

            //ALMACENO EL VERTICE
            std::array<float, 2> coords = {(float)x2, (float)y2};
            vec.push_back(coords);
            
            if (vertex == "") {
                break;
            }
        }

        cs->setPointCount(vec.size());
        for (int i = 0; i < vec.size(); i++) {
            cs->setPoint(i, vec[i][0], vec[i][1]);
        }
        
        //<DEBUG>
        cs->setFillColor('t');
        cs->setOutlineColor('r');
        cs->setOutlineThickness(5);
        //</DEBUG>
        
        
        actual.addGround(vec);
        
        objetos.push_back(*cs);     //GUARDO LOS ConvexShapes PARA DEBUG
        //BORRAR cs -> !IMPORTANTE
        delete cs;
        cs = nullptr;
        //VACIAR vec -> !IMPORTANTE
        vec.clear();

        obj = obj->NextSiblingElement("object");
    }
}

void Mapa::leexPlotatos(tinyxml2::XMLElement* obj, Nodo& actual, int x_starto, int y_starto){

    obj = obj->FirstChildElement("object");

    int xCoord = 0;
    int yCoord = 0;
    int width = 0;
    int height = 0;
    
    while (obj) {
        obj->QueryIntAttribute("x", &xCoord);
        obj->QueryIntAttribute("width", &width);

        obj->QueryIntAttribute("y", &yCoord);
        obj->QueryAttribute("height", &height);

        xCoord += x_starto;
        yCoord += y_starto;
        
        int y_spawn = yCoord + height - AssetManager::GetTexture("assets/BOSS.jpg").getYSize() / 2;
        int x_rand = physicsEngine::Instance().genIntRandom(xCoord, xCoord+width);

        actual.addxPlotato(x_rand, y_spawn, xCoord, xCoord+width);

        obj = obj->NextSiblingElement("object");
    }
}

void Mapa::leePorwerUps(tinyxml2::XMLElement* obj, Nodo& actual, int x_starto, int y_starto){
    
    //POWER UP/DOWN 
    obj = obj->FirstChildElement("object");

    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    while (obj) {
        obj->QueryIntAttribute("x", &x);
        obj->QueryIntAttribute("y", &y);
        obj->QueryIntAttribute("width", &w);
        obj->QueryIntAttribute("height", &h);
        
        int   random = physicsEngine::Instance().genIntRandom(0, 3);
        
        actual.addPower(random, x_starto + x, x + x_starto + w, y_starto + y + 35);
        obj = obj->NextSiblingElement("object");
    }
}

void Mapa::leeSkulls(tinyxml2::XMLElement* obj, Nodo& actual, int x_starto, int y_starto){
    
    obj = obj->FirstChildElement("object");

    int xCoord = 0;
    int yCoord = 0;
    int width = 0;
    int height = 0;


    tinyxml2::XMLElement* number;
    int n = 1;
    
    while (obj) {
        
        //Número de enemigos en esta área
        number = obj->FirstChildElement("properties");
        if(number) number->FirstChildElement("property")->QueryAttribute("value", &n);
        
        obj->QueryIntAttribute("x", &xCoord);
        obj->QueryIntAttribute("width", &width);

        obj->QueryIntAttribute("y", &yCoord);
        obj->QueryAttribute("height", &height);

        xCoord += x_starto;
        yCoord += y_starto;
        
        float randomX = physicsEngine::Instance().genIntRandom(xCoord, xCoord + width);
        float randomY = physicsEngine::Instance().genIntRandom(yCoord, yCoord + height);
        
        for (int i = 0; i < n; i++)
            actual.addSkull(randomX, randomY, xCoord, xCoord+width, yCoord, yCoord+height);

        obj = obj->NextSiblingElement("object");
    }
}

void Mapa::leeCheckPoints(tinyxml2::XMLElement* obj, Nodo& actual, int x_starto, int y_starto) {
    
    obj = obj->FirstChildElement("object");

    int xCoord = 0;
    int yCoord = 0;
    int width = 0;
    int height = 0;
    
    while (obj) {
        obj->QueryIntAttribute("x", &xCoord);
        obj->QueryIntAttribute("width", &width);

        obj->QueryIntAttribute("y", &yCoord);
        obj->QueryAttribute("height", &height);
        
        xCoord += x_starto;
        yCoord += y_starto;
        
        checkPoint checkpoint;
        checkpoint.active = false;
        checkpoint.shape.setSize(width, height);
        checkpoint.shape.setPosition(xCoord, yCoord);
        checkpoint.shape.setOutlineThickness(2);
        checkpoint.shape.setOutlineColor('r');
        checkpoint.shape.setFillColor('t');
        
        every_points.push_back(checkpoint);
        
        //actual.addCheckPoint(xCoord, yCoord, width, height);

        obj = obj->NextSiblingElement("object");
    }
    
}

void Mapa::leeMinijuego(tinyxml2::XMLElement* obj, Nodo& actual, int x_starto, int y_starto) {

    tinyxml2::XMLElement* property;
    int type = -1;
    
    property = obj->FirstChildElement("properties");
    if(property) property->FirstChildElement("property")->QueryAttribute("value", &type);
    
    obj = obj->FirstChildElement("object");
    
    int x, width;
    int y, height;
    
    // Área donde todos los jugadores deben estar para dar comienzo al minijuego
    obj->QueryIntAttribute("x", &x);
    obj->QueryIntAttribute("width", &width);
    obj->QueryIntAttribute("y", &y);
    obj->QueryIntAttribute("height", &height);
    
    x += x_max;
    y += y_max;

    Minijuego* mini = actual.addMinigame(type, x, y, width, height);
    if(type == 1){
        y -= y_max;
        y += height;
        y -= 70*2;      //Quiero que se empiecen a generar 2 por encima de la plataforma

        bool flag;
        for(int i = 0; i < 16; i++){
            flag = false;
            for(int j = 0; j < matriz_v2[i].size() && !flag; j++)
                if(matriz_v2[i][j] == 15){
                    matriz_v2[i].erase(matriz_v2[i].begin()+j);
                    flag = true;
                }
        }
        
        goingUp* up = static_cast<goingUp*>(mini);
        
        std::list<Nodo>* nodosUp = up->getAscensionList();
        std::string path;
        changeDirection(1);
        for(int i = 0; i < 9; i++){
            path = "tiles_definitivo/nodos/Up/Mininode_";
            int rand = physicsEngine::Instance().genIntRandom(1, 8);
            path = path.operator +=( std::to_string(rand) );
            path = path.operator +=(".tmx");
            
            LeeNodoAux(*nodosUp, path, x, y);
        }
        path = "tiles_definitivo/nodos/Up/Mininode_9.tmx";
        LeeNodoAux(*nodosUp, path, x, y);
        up->setEndArea(x, y, 43*ancho, 19*alto);
        y_max = y;
        changeDirection(0);
        
    }
        std::cout << "YMAX "<<y_max << std::endl;
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
    std::string path = "tiles_definitivo/nodos/";
    path = path.operator +=("0.tmx");
        //std::cout << path << std::endl;
    //nodo_actual = 15;
    LeeNodo(path);
    
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

    LeeNodo(path);
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
        javi->Instance().init(x_max,y_max);

        path = "tiles_definitivo/nodos/fin.tmx";
            //std::cout << path << std::endl;

        LeeNodo(path);
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
    DEATH.setPosition(renderEngine::Instance().getViewCenter()[0], renderEngine::Instance().getViewCenter()[1] + renderEngine::Instance().getViewSize()[1]-50);
    handleCheckPoints();
}

void Mapa::updateFondo() {
    renderEngine *sfml;
    float x,y;
    float mv = 2;
    
    if(x_view == -1){
        x_view = sfml->Instance().getViewCenter()[0];
        
        x = x_view-70*26;
        y = sfml->Instance().getViewCenter()[1]-70*15;

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
        
        
        x = x_view-70*26;
        y = sfml->Instance().getViewCenter()[1]-70*15;

        //f1.rect.setPosition(x,y);
        signo ? f1.move(-mv,0) : f1.move(mv,0);
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
    if(ready->getSprite().intersects(DEATH))
        Mapa::Instance().movePlayerToClosestCheckPoint(ready);
}

void Mapa::changeDirection(int dir) {
    direction = dir;
}

void Mapa::LeeNodoAux(std::list<Nodo>& lista, const std::string& node_path, int &x_start, int &y_start) {
    int map_width;
    int map_height;

    tinyxml2::XMLDocument map_doc;
    map_doc.LoadFile(node_path.c_str());

    tinyxml2::XMLElement *map;
    map = map_doc.FirstChildElement("map");
    map->QueryIntAttribute("width", &map_width);
    map->QueryIntAttribute("height", &map_height);

    lista.emplace_back("tiles_definitivo/tilesheet.png");
    lista.back().setRectVector(spriteSheetRects);
    
    //CONSIGO EL TEXTO
    std::string v_mapa = map->FirstChildElement("layer")->FirstChildElement("data")->GetText();
    std::string partes;
    std::string p_aux;
    int x_max_aux;
    
    y_start -= map_height*alto;

    for (int i = 0; i < map_height; i++) {
        for (int j = 0; j < map_width; j++) {
            v_mapa.erase(0, 1);
            partes = v_mapa.substr(0, 1);
            v_mapa.erase(0, 1);
            p_aux = v_mapa.substr(0, 1);
            while (p_aux != "," && p_aux != "") {
                partes = partes.operator+=(v_mapa.substr(0, 1));
                v_mapa.erase(0, 1);
                p_aux = v_mapa.substr(0, 1);
            }
            if (stoi(partes) != 0) {
                lista.back().addTile(stoi(partes)-1, x_start + (ancho * j), y_start + alto * i);
            }
        }
        partes = v_mapa.erase(0, 1);
    }
    
    if(direction == 0)
        x_max_aux = ancho * (map_width-1);
    
    tinyxml2::XMLElement *obj;
    obj = map->FirstChildElement("objectgroup");
    
    while(obj){
        
        //Puntero a funcion
        pFunc funcion = mapa_funciones[obj->Attribute("name")];   
        
        //std::cout << obj->Attribute("name") << std::endl;
        
        if(funcion != nullptr) (this->*funcion)(obj, hex_list.back(), x_start, y_start);
       
        obj = obj->NextSiblingElement("objectgroup");
    }
    
    if(direction == 0){
        x_start += x_max_aux+ancho;
        lista.back().setPop(x_start);
    }
    else{
        lista.back().setPop(y_start);
    }
    
}

void Mapa::setCameraDirection(int i) {
    cameraDir = i;
}
