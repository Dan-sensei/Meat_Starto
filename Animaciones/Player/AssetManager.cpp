/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AssetManager.cpp
 * Author: claudiac
 * 
 * Created on 22 de marzo de 2018, 22:52
 */

#include "AssetManager.h"
#include <assert.h>
#include <map>

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


AssetManager::AssetManager() {
    
    
}

sf::Texture& AssetManager::GetTexture(std::string const& filename)
{
    
    auto& texMap = Instance().m_Textures;
    //Mira si la textura ya ha sido cargada
    auto pairFound = texMap.find(filename);
    //Si es asi, devuelve la textura
    if(pairFound !=texMap.end())
    {
        return pairFound->second;
    } 
    else{
    //Carga la textura y la devuelve
        auto& texture = texMap[filename];
        texture.loadFromFile(filename);
        return texture;
    }
}


