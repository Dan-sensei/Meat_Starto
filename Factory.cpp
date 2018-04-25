/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Factory.cpp
 * Author: dan
 * 
 * Created on 25 de abril de 2018, 19:10
 */

#include "Factory.h"
#include "physicsEngine/physicsEngine.h"

Factory::Factory() {
    //MAPA DE PUNTEROS A FUNCION
    mapa_funciones.insert(std::make_pair("colision", &Factory::leeColisiones));
    mapa_funciones.insert(std::make_pair("spawn", &Factory::leexPlotatos));
    mapa_funciones.insert(std::make_pair("skull", &Factory::leeSkulls));
    mapa_funciones.insert(std::make_pair("power", &Factory::leePorwerUps));
    mapa_funciones.insert(std::make_pair("checkpoint", &Factory::leeCheckPoints));
    mapa_funciones.insert(std::make_pair("minijuegi", &Factory::leeMinijuego));
}


Factory::~Factory() {
}

void Factory::setTileSize(int width, int height) {
    tileWidth = width;
    tileHeight = height;
}


Factory::NodeStruct Factory::LeeNodo(std::string const& path) {
    
    NodeStruct NODO;

    //ABRO EL ARCHIVO
    tinyxml2::XMLDocument map_doc;
    map_doc.LoadFile(path.c_str());

    //CONSIGO EL ANCHO Y EL ALTO DEL NODO (Número de casillas del mapa)
    tinyxml2::XMLElement *map;
    map = map_doc.FirstChildElement("map");
    map->QueryIntAttribute("width", &(NODO.map_width));
    map->QueryIntAttribute("height", &(NODO.map_height));
    
    NODO.tile_width = tileWidth;
    NODO.tile_height = tileHeight;

    //CONSIGO EL TEXTO
    std::string v_mapa = map->FirstChildElement("layer")->FirstChildElement("data")->GetText();
    std::string partes;
    std::string p_aux;

    for (int i = 0; i < NODO.map_height; i++) {
        for (int j = 0; j < NODO.map_width; j++) {

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
                TileStruct tile;
                
                tile.id = stoi(partes)-1;
                tile.x = tileWidth * j;
                tile.y = tileHeight * i;
                
                NODO.Tiles.push_back(tile);
            }
        }
        partes = v_mapa.erase(0, 1);
    }

    tinyxml2::XMLElement *obj;

    obj = map->FirstChildElement("objectgroup");
    
    while(obj){ 
        
        //Puntero a funcion
        pFunc funcion = mapa_funciones[obj->Attribute("name")];   

        if(funcion != nullptr) (this->*funcion)(obj, NODO);

        obj = obj->NextSiblingElement("objectgroup");
        
    }
    
    return NODO;
}

void Factory::leeColisiones(tinyxml2::XMLElement* obj, NodeStruct& node) {
    GroundStruct ground;
        //CONSIGO LOS OBJETOS (COLISIONES)
    //NO COMPRUEBO SI NO TIENE COLISION, YA QUE SE SUPONE QUE TODOS LOS NODOS VAN A TENER COLISION, SI O SI
    tinyxml2::XMLElement *poly;
    int x, x2;
    int y, y2;
    std::string vertex, v_aux, v_aux2;
    std::vector<std::array<int, 2>> vec;
    //renderEngine::rConvexShape *cs;

    obj = obj->FirstChildElement("object");

    while (obj) {
        x = atoi(obj->Attribute("x")); //COORDENADA X ABSOLUTA
        y = atoi(obj->Attribute("y")); //COORDENADA Y ABSOLUTA
        /*
        //============================================//
        //PARA CREAR LOS VERTICES DEL ConvexShape
        cs = new renderEngine::rConvexShape;
        //============================================//
        */

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
                    x2 = x + stoi(v_aux);
                else 
                    y2 = y + stoi(v_aux);
                
            }

            //ALMACENO EL VERTICE
            std::array<int, 2> coords = {x2, y2};
            vec.push_back(coords);
            
            if (vertex == "") {
                break;
            }
        }
        
        ground.coords = vec;
        /*
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
        */
        vec.clear();

        node.Grounds.push_back(ground);
        
        obj = obj->NextSiblingElement("object");
    }
}

void Factory::leexPlotatos(tinyxml2::XMLElement* obj, NodeStruct& node) {
    
    xPlotatoStruct xPlot;
    
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
        
        int y_spawn = yCoord + height - AssetManager::GetTexture("assets/kawaii_potato.png").getYSize() / 2;
        
        xPlot.xMin = xCoord;
        xPlot.xMax = xCoord + width;
        xPlot.y = y_spawn;
        
        node.xPlotatos.push_back(xPlot);
        
        obj = obj->NextSiblingElement("object");
    }
}

void Factory::leeSkulls(tinyxml2::XMLElement* obj, NodeStruct& node) {
    
    SkullStruct skull;
    
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

        skull.n = n;
        skull.xMin = xCoord;
        skull.xMax = xCoord + width;
        skull.yMin = yCoord;
        skull.yMax = yCoord + height;
       
        node.Skulls.push_back(skull);
        
        obj = obj->NextSiblingElement("object");
    }
}

void Factory::leePorwerUps(tinyxml2::XMLElement* obj, NodeStruct& node) {

    PowerStruct power;
    
    obj = obj->FirstChildElement("object");

    int x = 0;
    int y = 0;
    int width = 0;

    while (obj) {
        obj->QueryIntAttribute("x", &x);
        obj->QueryIntAttribute("y", &y);
        obj->QueryIntAttribute("width", &width);
        
        int random = physicsEngine::Instance().genIntRandom(0, 6);
        
        power.id = random;
        power.xMin = x;
        power.xMax = x + width;
        power.y = y + 35;
        
        node.Powers.push_back(power);
        
        obj = obj->NextSiblingElement("object");
    }
}

void Factory::leeCheckPoints(tinyxml2::XMLElement* obj, NodeStruct& node) {
    
    CheckpointStruct check;
    
    obj = obj->FirstChildElement("object");
    
    while (obj) {
        obj->QueryIntAttribute("x", &(check.x));
        obj->QueryIntAttribute("width", &(check.width));

        obj->QueryIntAttribute("y", &(check.y));
        obj->QueryAttribute("height", &(check.height));

        node.Checkpoints.push_back(check);
        
        obj = obj->NextSiblingElement("object");
    } 
}

void Factory::leeMinijuego(tinyxml2::XMLElement* obj, NodeStruct& node) {
    
    MinijuegoStruct mini;
    
    tinyxml2::XMLElement* property;
    property = obj->FirstChildElement("properties");
    if(property) property->FirstChildElement("property")->QueryAttribute("value", &(mini.type));
    
    obj = obj->FirstChildElement("object");
    
    // Área donde todos los jugadores deben estar para dar comienzo al minijuego
    obj->QueryIntAttribute("x", &(mini.x));
    obj->QueryIntAttribute("width", &(mini.width));
    obj->QueryIntAttribute("y", &(mini.y));
    obj->QueryIntAttribute("height", &(mini.height));
    
    node.minijuego = mini;
}
