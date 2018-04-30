/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Factory.h
 * Author: dan
 *
 * Created on 25 de abril de 2018, 19:10
 */

#ifndef FACTORY_H
#define FACTORY_H

#include "tinyxml2.h"
#include <array>
#include <vector>
#include <map>

class Factory {
private:
    
    struct TileStruct{
        int id;
        int x;
        int y;
    };
    
    struct xPlotatoStruct{
        int xMin;
        int xMax;
        int y;
    };
    
    struct SkullStruct{
        int n;
        int xMin;
        int xMax;
        int yMin;
        int yMax;
    };
    
    struct CheckpointStruct{
        int x;
        int y;
        int width;
        int height;
    };
    
    struct PowerStruct{
        int id;
        int xMin;
        int xMax;
        int y;
    };
    
    struct GroundStruct{
        std::vector<std::array<int, 2>> coords;
    };
    
    struct MinijuegoStruct{
        int type;
        int x;
        int y;
        int width;
        int height;
    };
    
    int tileWidth;
    int tileHeight;
    
public:
    
    static Factory& Instance(){
        static Factory instance;
        return instance;
    }
   
    virtual ~Factory();
    
    struct NodeStruct{
        int map_width;
        int map_height;
        int tile_width;
        int tile_height;
        std::vector<TileStruct> Tiles;
        std::vector<xPlotatoStruct> xPlotatos;
        std::vector<SkullStruct> Skulls;
        std::vector<CheckpointStruct> Checkpoints;
        std::vector<PowerStruct> Powers;
        std::vector<GroundStruct> Grounds;
        MinijuegoStruct minijuego;
    };
    
    NodeStruct LeeNodo(std::string const& path);
    void setTileSize(int width, int height);
    
    
private:
    
    Factory();
    Factory(const Factory& orig);
    void operator=(Factory const& orig);
    
    typedef void (Factory::*pFunc)(tinyxml2::XMLElement *, NodeStruct &);
    std::map<std::string, pFunc> mapa_funciones;
    
    void leeColisiones(tinyxml2::XMLElement *obj, NodeStruct &node);
    void leexPlotatos(tinyxml2::XMLElement *obj, NodeStruct &node);
    void leeSkulls(tinyxml2::XMLElement *obj, NodeStruct &node);
    void leePorwerUps(tinyxml2::XMLElement *obj, NodeStruct &node);
    void leeCheckPoints(tinyxml2::XMLElement *obj, NodeStruct &node);
    void leeMinijuego(tinyxml2::XMLElement *obj, NodeStruct &node);

};

#endif /* FACTORY_H */

