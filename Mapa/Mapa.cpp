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

#define SCALE 65.f
#define MAP_ITERATION 10000
#define TAM_LISTA 8

 Mapa::Mapa() {
    renderEngine::rClock optimo_clock;
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

    //-----------VARIABLES DE CLASE-----------//
    pop = false;
    
    //LO UTILIZO AL LEER TODOS LOS NODOS DE LA MATRIZ
    x_max = 0;
    
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
    
    longitud = 0;
    end = false;
    
    std::cout << "TIEMPO DE CARGA DEL MAPA " << optimo_clock.getElapsedTime().asSeconds() << std::endl;
}

//INICIALIZAR LA MATRIZ DE ADYACENCIA
void Mapa::InitMatrix() {
    //////////////////////////////
    // SI SE MODIFICA, ENTONCES //
    // CAMBIAR TAMBIEN EL .h !! //
    //////////////////////////////
    
    //  v es n x n
    //  n = 15
    int x;
    
    //NODO 0
    x = 0;
    // <editor-fold defaultstate="collapsed" desc="NODO 0">
    v[x][0] = 0;
    v[x][1] = 1;
    v[x][2] = 1;
    v[x][3] = 1;
    v[x][4] = 0;
    v[x][5] = 0;
    v[x][6] = 0;
    v[x][7] = 1;
    v[x][8] = 0;
    v[x][9] = 0;
    v[x][10] = 0;
    v[x][11] = 0;
    v[x][12] = 0;
    v[x][13] = 0;
    v[x][14] = 0; 
    // </editor-fold>

    //NODO 1
    x = 1;
    // <editor-fold defaultstate="collapsed" desc="NODO 1">
    v[x][0] = 0;
    v[x][1] = 0;
    v[x][2] = 1;
    v[x][3] = 1;
    v[x][4] = 1;
    v[x][5] = 1;
    v[x][6] = 1;
    v[x][7] = 1;
    v[x][8] = 0;
    v[x][9] = 0;
    v[x][10] = 1;
    v[x][11] = 0;
    v[x][12] = 0;
    v[x][13] = 0;
    v[x][14] = 1; 
    // </editor-fold>
    
    //NODO 2
    x = 2;
    // <editor-fold defaultstate="collapsed" desc="NODO 2">
    v[x][0] = 0;
    v[x][1] = 1;
    v[x][2] = 0;
    v[x][3] = 1;
    v[x][4] = 1;
    v[x][5] = 1;
    v[x][6] = 1;
    v[x][7] = 1;
    v[x][8] = 0;
    v[x][9] = 0;
    v[x][10] = 1;
    v[x][11] = 0;
    v[x][12] = 0;
    v[x][13] = 0;
    v[x][14] = 0; 
    // </editor-fold>
    
    //NODO 3
    x = 3;
    // <editor-fold defaultstate="collapsed" desc="NODO 3">
    v[x][0] = 0;
    v[x][1] = 1;
    v[x][2] = 1;
    v[x][3] = 0;
    v[x][4] = 1;
    v[x][5] = 1;
    v[x][6] = 1;
    v[x][7] = 0;
    v[x][8] = 0;
    v[x][9] = 0;
    v[x][10] = 0;
    v[x][11] = 0;
    v[x][12] = 0;
    v[x][13] = 0;
    v[x][14] = 0; 
    // </editor-fold>

    //NODO 4
    x = 4;
    // <editor-fold defaultstate="collapsed" desc="NODO 4">
    v[x][0] = 0;
    v[x][1] = 0;
    v[x][2] = 1;
    v[x][3] = 1;
    v[x][4] = 1;
    v[x][5] = 0;
    v[x][6] = 1;
    v[x][7] = 1;
    v[x][8] = 0;
    v[x][9] = 0;
    v[x][10] = 1;
    v[x][11] = 1;
    v[x][12] = 0;
    v[x][13] = 1;
    v[x][14] = 0; 
    // </editor-fold>

    //NODO 5
    x = 5;
    // <editor-fold defaultstate="collapsed" desc="NODO 5">
    v[x][0] = 0;
    v[x][1] = 0;
    v[x][2] = 0;
    v[x][3] = 1;
    v[x][4] = 0;
    v[x][5] = 0;
    v[x][6] = 1;
    v[x][7] = 1;
    v[x][8] = 1;
    v[x][9] = 0;
    v[x][10] = 0;
    v[x][11] = 1;
    v[x][12] = 0;
    v[x][13] = 1;
    v[x][14] = 0; 
    // </editor-fold>

    //NODO 6 (MINIJUEGO TETRIS)
    x = 6;
    // <editor-fold defaultstate="collapsed" desc="NODO 6">
    v[x][0] = 0;
    v[x][1] = 1;
    v[x][2] = 1;
    v[x][3] = 1;
    v[x][4] = 1;
    v[x][5] = 1;
    v[x][6] = 0;
    v[x][7] = 1;
    v[x][8] = 1;
    v[x][9] = 0;
    v[x][10] = 0;
    v[x][11] = 1;
    v[x][12] = 0;
    v[x][13] = 1;
    v[x][14] = 0; 
    // </editor-fold>

    //NODO 7
    x = 7;
    // <editor-fold defaultstate="collapsed" desc="NODO 7">
    v[x][0] = 0;
    v[x][1] = 0;
    v[x][2] = 0;
    v[x][3] = 0;
    v[x][4] = 1;
    v[x][5] = 0;
    v[x][6] = 1;

    v[x][7] = 0;
    v[x][8] = 1;
    v[x][9] = 1;
    v[x][10] = 0;
    v[x][11] = 0;
    v[x][12] = 1;
    v[x][13] = 0;
    v[x][14] = 0; 
    // </editor-fold>

    //NODO 8
    x = 8;
    // <editor-fold defaultstate="collapsed" desc="NODO 8">
    v[x][0] = 0;
    v[x][1] = 0;
    v[x][2] = 0;
    v[x][3] = 0;
    v[x][4] = 1;
    v[x][5] = 0;
    v[x][6] = 0;

    v[x][7] = 0;
    v[x][8] = 1;
    v[x][9] = 1;
    v[x][10] = 0;
    v[x][11] = 0;
    v[x][12] = 1;
    v[x][13] = 0;
    v[x][14] = 0; 
    // </editor-fold>

    //NODO 9
    x = 9;
    // <editor-fold defaultstate="collapsed" desc="NODO 9">
    v[x][0] = 0;
    v[x][1] = 1;
    v[x][2] = 0;
    v[x][3] = 1;
    v[x][4] = 0;
    v[x][5] = 1;
    v[x][6] = 0;

    v[x][7] = 1;
    v[x][8] = 1;
    v[x][9] = 0;
    v[x][10] = 1;
    v[x][11] = 0;
    v[x][12] = 1;
    v[x][13] = 1;
    v[x][14] = 1; 
    // </editor-fold>

    //NODO 10
    x = 10;
    // <editor-fold defaultstate="collapsed" desc="NODO 10">
    v[x][0] = 0;
    v[x][1] = 1;
    v[x][2] = 0;
    v[x][3] = 0;
    v[x][4] = 0;
    v[x][5] = 0;
    v[x][6] = 0;

    v[x][7] = 0;
    v[x][8] = 0;
    v[x][9] = 1;
    v[x][10] = 0;
    v[x][11] = 1;
    v[x][12] = 1;
    v[x][13] = 0;
    v[x][14] = 0; 
    // </editor-fold>

    //NODO 11
    x = 11;
    // <editor-fold defaultstate="collapsed" desc="NODO 11">
    v[x][0] = 0;
    v[x][1] = 1;
    v[x][2] = 1;
    v[x][3] = 1;
    v[x][4] = 0;
    v[x][5] = 1;
    v[x][6] = 0;

    v[x][7] = 0;
    v[x][8] = 1;
    v[x][9] = 1;
    v[x][10] = 1;
    v[x][11] = 0;
    v[x][12] = 1;
    v[x][13] = 1;
    v[x][14] = 1; 
    // </editor-fold>
        
    //NODO 12
    x = 12;
    // <editor-fold defaultstate="collapsed" desc="NODO 12">
    v[x][0] = 0;
    v[x][1] = 0;
    v[x][2] = 0;
    v[x][3] = 0;
    v[x][4] = 0;
    v[x][5] = 0;
    v[x][6] = 0;

    v[x][7] = 1;
    v[x][8] = 1;
    v[x][9] = 1;
    v[x][10] = 0;
    v[x][11] = 1;
    v[x][12] = 0;
    v[x][13] = 1;
    v[x][14] = 0; 
    // </editor-fold>
        
    //NODO 13
    x = 13;
    // <editor-fold defaultstate="collapsed" desc="NODO 13">
    v[x][0] = 0;
    v[x][1] = 0;
    v[x][2] = 0;
    v[x][3] = 1;
    v[x][4] = 1;
    v[x][5] = 0;
    v[x][6] = 0;

    v[x][7] = 0;
    v[x][8] = 1;
    v[x][9] = 0;
    v[x][10] = 0;
    v[x][11] = 1;
    v[x][12] = 1;
    v[x][13] = 0;
    v[x][14] = 1; 
    // </editor-fold>
        
    //NODO 14
    x = 14;
    // <editor-fold defaultstate="collapsed" desc="NODO 14">
    v[x][0] = 0;
    v[x][1] = 1;
    v[x][2] = 0;
    v[x][3] = 0;
    v[x][4] = 0;
    v[x][5] = 1;
    v[x][6] = 1;

    v[x][7] = 0;
    v[x][8] = 1;
    v[x][9] = 0;
    v[x][10] = 1;
    v[x][11] = 0;
    v[x][12] = 1;
    v[x][13] = 1;
    v[x][14] = 1; 
    // </editor-fold>

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

    std::cout << "Creando nodo" << std::endl;
    hex_list.emplace_back("tiles_definitivo/tilesheet.png");
    
    hex_list.back().setRectVector(spriteSheetRects);
    
    //CONSIGO EL TEXTO
    std::string v_mapa = map->FirstChildElement("layer")->FirstChildElement("data")->GetText();
    std::string partes;
    std::string p_aux;
    int x_max_aux = x_max;


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
                hex_list.back().addTile(stoi(partes)-1, x_max + (ancho * j), alto * i);
                CreaCasilla(stoi(partes), x_max + (ancho * j), alto * i);
            }
            
            x_max_aux = (x_max_aux < x_max + ancho*j) ? (x_max + ancho*j) : x_max_aux;

        }

        partes = v_mapa.erase(0, 1);
    }
    
    // </editor-fold> 
    
    tinyxml2::XMLElement *obj;
    obj = map->FirstChildElement("objectgroup");
    
    while(obj){
        
        //Puntero a funcion
        pFunc funcion = mapa_funciones[obj->Attribute("name")];   
        
        if(funcion != nullptr) (this->*funcion)(obj, hex_list.back());
       
        obj = obj->NextSiblingElement("objectgroup");
    }

    x_max = x_max_aux+ancho;
    
    hex_list.back().setPop(x_max);
    
    std::cout << "CREADO" << std::endl;
    /*
    
    //GUARDO LOS PINCHOS
    if(l_pinchos.size()<TAM_LISTA){
        l_pinchos.push_back(vector_pinchos);
        vector_pinchos.clear();
    }
    else{
        l_pinchos_aux.push_back(vector_pinchos);
        vector_pinchos.clear();
    }
    vector_pinchos.clear();
     */
}

void Mapa::leeColisiones(tinyxml2::XMLElement *obj, Nodo &actual){
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
        //std::cout << poly->Attribute("points") << std::endl;

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
                    x2 = x + x_max + stoi(v_aux);
                else 
                    y2 = y + stoi(v_aux);
                
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
        //VACIAR vec -> !IMPORTANTE
        vec.clear();

        obj = obj->NextSiblingElement("object");
    }
}

void Mapa::leexPlotatos(tinyxml2::XMLElement* obj, Nodo& actual){

    obj = obj->FirstChildElement("object");

    int xCoord = 0;
    int yCoord = 0;
    int width = 0;
    int height = 0;
    
    while (obj) {
        obj->QueryIntAttribute("x", &xCoord);
        xCoord += x_max;
        obj->QueryIntAttribute("width", &width);

        obj->QueryIntAttribute("y", &yCoord);
        obj->QueryAttribute("height", &height);

        int y_spawn = yCoord + height - AssetManager::GetTexture("assets/BOSS.jpg").getYSize() / 2;
        int x_rand = physicsEngine::Instance().genIntRandom(xCoord, xCoord+width);

        actual.addxPlotato(x_rand, y_spawn, xCoord, xCoord+width);

        obj = obj->NextSiblingElement("object");
    }
}

void Mapa::leePorwerUps(tinyxml2::XMLElement* obj, Nodo& actual){
    
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

        
        int     xpos = physicsEngine::Instance().genIntRandom(0, (w / 70) - 1);
        float random = physicsEngine::Instance().genFloatRandom(0, 1);
        
        renderEngine::rRectangleShape raux;
        if (random < 0.5) {
            //CREO UN POWER UP
            raux.setFillColor('g');
            raux.setSize(20, 20);
            raux.setOrigin(10, 10);
            raux.setPosition(x_max + x + (xpos * 70) + 35, y + 35);
        } else {
            //CREO UN POWER DOWN
            raux.setFillColor('r');
            raux.setSize(20, 20);
            raux.setOrigin(10, 10);
            raux.setPosition(x_max + x + (xpos * 70) + 35, y + 35);
        }
        power.push_back(raux);
        obj = obj->NextSiblingElement("object");
    }
}

void Mapa::leeSkulls(tinyxml2::XMLElement* obj, Nodo& actual){
    
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
        xCoord += x_max;
        obj->QueryIntAttribute("width", &width);

        obj->QueryIntAttribute("y", &yCoord);
        obj->QueryAttribute("height", &height);

        float randomX = physicsEngine::Instance().genIntRandom(xCoord, xCoord + width);
        float randomY = physicsEngine::Instance().genIntRandom(yCoord, yCoord + height);
        
        for (int i = 0; i < n; i++)
            actual.addSkull(randomX, randomY, xCoord, xCoord+width, yCoord, yCoord+height);

        obj = obj->NextSiblingElement("object");
    }
}

//CREA LA CASILLA
void Mapa::CreaCasilla(int id, int x, int y) {
        //std::cout << tiles[id-1]->path << std::endl;
    
    renderEngine::rRectangleShape casilla(ancho,alto);
    //casilla.setTexture(AssetManager::GetTexture(tiles[id-1]->path));
    casilla.setPosition(x,y);
    
    int id2 = id-1;
    if(id2 == 36 || id2 == 35 || id2 == 34 || id2 == 33){
        //std::cout << id << std::endl;
        
        renderEngine::rRectangleShape rs;
        rs.setSize(70,70);
        rs.setPosition(x,y);
        rs.setFillColor('r');
        
        vector_pinchos.push_back(rs);
    }
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
    int ya = y-h-ancho;
    
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
    
    renderEngine::rRectangleShape *r;
    renderEngine::rTexture *t;
    
    for(std::list<Nodo>::iterator it=hex_list.begin(); it!=hex_list.end(); ++it){
       
        (*it).draw(tick_, ir, x_min_, x_max_);
        
        if(iterator == TAM_LISTA/2-1 && (*it).getPop() < sfml->Instance().getViewCenter()[0]){
            pop = true;
        }
        iterator++;
    }

    //------------|  COLISIONES (DEBUG)  |------------//
    /*
    for(int i=0 ; i<objetos.size() ; i++){
        window.draw(objetos[i]);
    }
    */
    
    //------------|  PINCHOS (DEBUG)  |------------//
    /*
    for(std::list<std::vector<renderEngine::rRectangleShape>>::iterator it=l_pinchos.begin(); it!=l_pinchos.end(); ++it){
        for(int i = 0 ; i<(*it).size() ; i++){
            (*it)[i].draw();
        }
    }
    */
    
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
    
    
}

//LEE LA MATRIZ DE ADYACENCIA
void Mapa::CreaMapa() {
    std::string path = "tiles_definitivo/nodos/";
    path = path.operator +=("0.tmx");
        //std::cout << path << std::endl;
    
    LeeNodo(path);
    longitud++;
    //EMPIEZA A LEER LA MATRIZ
    int n = 15;     //DIMENSION DE LA MATRIZ DE ADYACENCIA
    int nodo = 0;   //NODOS ADYACENTES A 0
    int iter = 0;   //CUENTA EL NUMERO DE ITERACIONES
    int r;          //EL NUMERO RANDOM
    
    for(; iter<std::min(TAM_LISTA, MAP_ITERATION)-2; iter++) {
        bool num = false;
        while(!num){
            //GENERO EL NUMERO ALEATORIO
            r = physicsEngine::Instance().genIntRandom(0, n-1);
            //std::cout << r << std::endl;
            if(r!=6 || (r != 6 && !m_tetris))
                if(v[nodo][r]==1){
                    num = true;
                }
        }

        std::string path = "tiles_definitivo/nodos/";
        std::string rand = std::to_string(r);
        path = path.operator +=(rand);
        path = path.operator +=(".tmx");
            //std::cout << path << std::endl;
        
        LeeNodo(path);
        longitud++;
        nodo = r;
        
        std::cout << "Vector size " << hex_list.size() << std::endl;
        
        //DETECTA QUE YA SE HA DIBUJADO EL MINIJUEGO
        if(r == 6 && !m_tetris){
            std::cout << "He creado el minijuego Tetris" << std::endl;
            
            //CREO LA CLASE TETRIS
            mj_t *tetris;
            tetris->Instance().init(x_max);
            
            m_tetris = true;
        }
    }
    
    if(MAP_ITERATION < TAM_LISTA){
        boss *javi;
        javi->Instance().init(x_max);

        path = "tiles_definitivo/nodos/fin.tmx";
            //std::cout << path << std::endl;

        LeeNodo(path);
        end = true;
    }
        
    
    //CREO EL NODO FINAL
    //SIEMPRE VA A SER CREADO EL ULTIMO, AL IGUAL QUE EL NODO 0
    
}

void Mapa::leeRandom(){
    std::string path = "tiles_definitivo/nodos/";
    if(longitud == MAP_ITERATION-1){
        boss *javi;
        javi->Instance().init(x_max);

        path = "tiles_definitivo/nodos/fin.tmx";
            //std::cout << path << std::endl;

        LeeNodo(path);
        end = true;
    }
    else{
        int n = 15;
        int nodo = physicsEngine::Instance().genIntRandom(0, n-1);
        int r;
        bool num = false;
        while(!num){
            //GENERO EL NUMERO ALEATORIO
            r = physicsEngine::Instance().genIntRandom(0, n-1);
            
            if(r!=6 || (r != 6 && !m_tetris))
                if(v[nodo][r]==1){
                    num = true;
                }
        }

        std::string path = "tiles_definitivo/nodos/";
        std::string rand = std::to_string(r);
        path = path.operator +=(rand);
        path = path.operator +=(".tmx");

        LeeNodo(path);
        longitud++;
        //std::cout << "Vector size " << vector_casillas.size() << std::endl;
        
        //DETECTA QUE YA SE HA DIBUJADO EL MINIJUEGO
        if(r == 6 && !m_tetris){
            std::cout << "He creado el minijuego Tetris" << std::endl;
            
            //CREO LA CLASE TETRIS
            mj_t *tetris;
            tetris->Instance().init(x_max);
            
            m_tetris = true;
        }
    }
    
}

void Mapa::update(float x, float y) {
    renderEngine *sfml;
    mj_t *tetris;
    boss *javi;
    
    if(pop){
        std::cout << "Borrando..." << std::endl;
        //hex_list.front()->~Nodo();
        //std::cout << "HEX " << hex_list.size() << " | COMPLETE " << complete_list.size() << std::endl;
        hex_list.pop_front();
        if(longitud < MAP_ITERATION)
            leeRandom();
        else if(!end)
            leeRandom();
        //hex_list.emplace_back(std::move(complete_list.front()));
        //complete_list.pop_front();
        //std::cout << "HEX " << hex_list.size() << " | COMPLETE " << complete_list.size() << std::endl;
        //POP DE PINCHOS
        /*
        l_pinchos.pop_front();
        l_pinchos.push_back(l_pinchos_aux.front());
        l_pinchos_aux.pop_front();
         */
        
        pop = false;
    }
    

    int x_m = sfml->Instance().getViewCenter()[0];
    
    tetris->Instance().update(x_m);
    javi->Instance().update(x_m,x,y);
}

std::list<std::vector<renderEngine::rRectangleShape>>* Mapa::getPinchos() {
    return &l_pinchos;
}

void Mapa::update(){
    for(std::list<Nodo>::iterator it=hex_list.begin(); it!=hex_list.end(); ++it){
        (*it).update();   
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

