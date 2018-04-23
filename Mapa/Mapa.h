/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mapa.h
 * Author: pablomanez
 *
 * Created on 23 de febrero de 2018, 15:42
 */

#ifndef MAPA_H
#define MAPA_H


#include <vector>
#include <list>


#include "../mj_t.h"
#include "../boss.h"
#include "Nodo/Nodo.h"
#include "Nodo/NPCs/NPC.h"
#include "Nodo/NPCs/xPlotato.h"

class Mapa {
public:
    //----------------SINGLETON
    static Mapa& Instance(){
        static Mapa instance;
        return instance;
    }
    
    void CreaMapa();
    void leeRandom();
    void render(float tick_);
    void updateMini();
    void update();
    void preState();
    void newState();
    
    virtual ~Mapa();
    
private:
    Mapa();
    Mapa(const Mapa& orig);
    void operator=(Mapa const& orig);
    
    //----------------METODOS PRIVADOS
    void LeeNodo(std::string const& node_path);
    void InitMatrix();
    void updateFondo();
    
    typedef void (Mapa::*pFunc)(tinyxml2::XMLElement *, Nodo &);
    std::map<std::string, pFunc> mapa_funciones;
    
    void leeColisiones(tinyxml2::XMLElement *obj, Nodo &actual);
    void leexPlotatos(tinyxml2::XMLElement *obj, Nodo &actual);
    void leeSkulls(tinyxml2::XMLElement *obj, Nodo &actual);
    void leePorwerUps(tinyxml2::XMLElement *obj, Nodo &actual);
    void leeCheckPoints(tinyxml2::XMLElement *obj, Nodo &actual);
    void leeMinijuego(tinyxml2::XMLElement *obj, Nodo &actual);
    void leeDEATH(tinyxml2::XMLElement *obj, Nodo &actual);
    
    //----------------ATRIBUTOS
    //DOCUMENTO XML/TMX QUE TIENE LOS ATRIBUTOS DE LAS MAPAS
    tinyxml2::XMLDocument doc;
    
    //ALTO Y ANCHO DE CADA MAPA
    int ancho;
    int alto;
    
    //ALMACENA EL PATH DE LA IMAGEN Y SU ID
    tinyxml2::XMLDocument ts_doc;   //XML DEL MAPASHEET
    renderEngine::rImage ts;        //PNG DEL MAPASHEET

    
    //OBJETOS (colisiones del mapa)
    std::vector<renderEngine::rConvexShape> objetos;
    std::vector<renderEngine::rRectangleShape> power;   //POWER UPS/DOWNS
    
    //PARA CONSTRUIR EL MAPA
    int x_max;
    
    std::list<Nodo> hex_list;
    std::vector<renderEngine::rIntRect> spriteSheetRects;
    int longitud;
    bool end;

    bool pop;       //TRUE: HAY QUE HACER POP DE lista_casillas
    
    std::vector<int> matriz_v2[16];     // Guarda sólo los nodos a los que está conectada cada posición del array
    int nodo_actual;
    
    //TETRIS
    bool m_tetris;
    bool goingUp;
    
    //FONDOS
    float x_view;
    renderEngine::rTexture text_fondo;
    renderEngine::rRectangleShape f1;
    renderEngine::rRectangleShape f2;
};

#endif /* MAPA_H */

