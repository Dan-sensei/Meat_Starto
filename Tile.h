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
#include "physicsEngine.h"
#include "renderEngine.h"

class Tile {
public:
    //----------------SINGLETON
    static Tile& Instance(){
        static Tile instance;
        return instance;
    }
    
    void CreaMapa();
    void DibujaCasillas(int x, int y);
    
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
    struct _tile{
        int id;
        std::string path;
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
        //sf::RectangleShape rect;
        renderEngine::rRectangleShape rect;
        
        //sf::Texture text;
        renderEngine::rTexture text;
    };
    std::vector<_cas> vector_casillas;
    std::vector<renderEngine::rSprite> vector_enemigos;
    int v[15][15];
    
    bool m_tetris;
    
};

#endif /* TILE_H */

