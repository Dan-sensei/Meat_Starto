/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tile.h
 * Author: pablomanez
 *
 * Created on 23 de febrero de 2018, 15:42
 */

#ifndef TILE_H
#define TILE_H

#include <tinyxml2.h>
#include <vector>
#include <list>
#include <Box2D/Box2D.h>
#include "AssetManager.h"

#include "renderEngine.h"
#include "mj_t.h"
#include "boss.h"
#include "NPCs/NPC.h"
#include "NPCs/xPlotato.h"

class Tile {
public:
    //----------------SINGLETON
    static Tile& Instance(){
        static Tile instance;
        return instance;
    }
    
    void CreaMapa();
    void render(float tick_);
    void update(float x, float y);
    void updateNPCs();
    void preStateNPCs();
    void newStateNPCs();
    
    virtual ~Tile();
    
private:
    Tile();
    Tile(const Tile& orig);
    void operator=(Tile const& orig);
    
    //----------------METODOS PRIVADOS
    void LeeNodo(std::string const& node_path);
    void CreaCasilla(int id, int x, int y);
    void InitMatrix();
    
    //----------------ATRIBUTOS
    //DOCUMENTO XML/TMX QUE TIENE LOS ATRIBUTOS DE LAS TILES
    tinyxml2::XMLDocument doc;
    
    //ALTO Y ANCHO DE CADA TILE
    int ancho;
    int alto;
    
    //ALMACENA EL PATH DE LA IMAGEN Y SU ID
    tinyxml2::XMLDocument ts_doc;   //XML DEL TILESHEET
    renderEngine::rImage ts;        //PNG DEL TILESHEET
    struct _tile{
        int id;
        renderEngine::rIntRect ir;  //CUADRADO DE RECORTE
        renderEngine::rTexture t;   //TEXTURA
        std::string path;           //PATH DEL TILE (NO SE USA)
    };
    _tile *tiles[37];
    
    //OBJETOS (colisiones del mapa)
    std::vector<renderEngine::rConvexShape> objetos;
    std::vector<std::vector<std::array<float, 2>>> colision;
    std::vector<std::array<float, 2>> spawn;
    
    //PARA CONSTRUIR EL MAPA
    int x_max;
    struct _cas{
        int id;
        renderEngine::rRectangleShape rect;
        renderEngine::rTexture *text;
    };
    struct _miArray{
        _cas *casillas;     //PUNTERO A ARRAY DE _cas
        int size;           //TAMANYO
        int aux_pop;
    };
    //std::list<std::vector<_cas>> lista_casillas;
    std::list<_miArray> lista_casillas;
    std::list<_miArray> lista_casillas_aux;
    bool pop;       //TRUE: HAY QUE HACER POP DE lista_casillas
    
    std::vector<_cas> vector_casillas;
    std::vector<NPC*> vector_enemigos;
    int v[15][15];
    
    //TETRIS
    bool m_tetris;
};

#endif /* TILE_H */

