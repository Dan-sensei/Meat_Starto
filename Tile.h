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
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <list>
#include <SFML/Graphics/ConvexShape.hpp>
#include <Box2D/Box2D.h>
#include "physicsEngine.h"

class Tile {
public:
    //----------------SINGLETON
    static Tile& Instance(){
        static Tile instance;
        return instance;
    }
    
    void CreaMapa();
    void DibujaCasillas(sf::RenderWindow &window, int x, int y);
    
    virtual ~Tile();
    
private:
    Tile();
    Tile(const Tile& orig);
    void operator=(Tile const& orig);
    
    //----------------METODOS PRIVADOS
    void LeeNodo(std::string node_path);
    void CreaCasilla(int id, int x, int y);
    void InitMatrix();
    void createGround(b2World& world_, std::vector<sf::Vector2f> vertex_, int n_);
    
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
    std::vector<sf::ConvexShape> objetos;
    std::vector<std::vector<std::array<float, 2>>> colision;
    
    //PARA CONSTRUIR EL MAPA
    int x_max;
    struct _cas{
        int id;
        sf::RectangleShape rect;
        sf::Texture text;
    };
    std::vector<_cas> vector_casillas;
    int v[15][15];
    
    bool m_tetris;
    
};

#endif /* TILE_H */

