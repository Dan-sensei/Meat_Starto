/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


//Esta clase forma parte del libro "SFML Essentials" para optimizar la carga de texturas

#include "AssetManager.h"
#include <iostream>
#include <assert.h>



AssetManager::AssetManager(){}

renderEngine::rTexture& AssetManager::GetTexture(const std::string& filename){
    
    auto& texMap = Instance().m_Textures;
    auto pairFound = texMap.find(filename);
    if(pairFound != texMap.end()){
        return pairFound->second;
    }
    else{
        auto& texture = texMap[filename];
        texture.loadFromFile(filename);
        return texture;
    }
}
/*
sf::SoundBuffer& AssetManager::GetSoundBuffer(const std::string& filename){
    
    auto& sBufferMap = sInstance->m_SoundBuffers;
    auto pairFound = sBufferMap.find(filename);
    
    if(pairFound != sBufferMap.end()){
        return pairFound->second;
    }
    else{
        auto& sBuffer = sBufferMap[filename];
        sBuffer.loadFromFile(filename);
        return sBuffer;
    }
}

sf::Font& AssetManager::GetFont(const std::string& filename){
    
    auto& fontMap = sInstance->m_Fonts;
    auto pairFound = fontMap.find(filename);
    
    if(pairFound != fontMap.end()){
        return pairFound->second;
    }
    else{
        auto& font = fontMap[filename];
        font.loadFromFile(filename);
        return font;
    }
}
 */