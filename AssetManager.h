/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AssetManager.h
 * Author: dan
 *
 * Created on 5 de febrero de 2018, 11:40
 */

#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include "renderEngine/rSoundBuffer.h"
#include "renderEngine/renderEngine.h"

class AssetManager{
    public:
        //======== SINGLETON =========
        static AssetManager& Instance(){
            static AssetManager instance;        // Las variables estáticas se destruyen al terminar el programa
            return instance;                // Return molón
        }
        //============================
        
        static renderEngine::rTexture& GetTexture(std::string const& filename);
        static rSoundBuffer& GetSoundBuffer(std::string const& filename);
        //static sf::Font& GetFont(std::string const& filename);
        
    private:
        //============ SINGLETON ============
        AssetManager();
        AssetManager(AssetManager const& orig);           // <--------------------- No implementar estos métodos
        void operator=(AssetManager const& orig);    // <----------------'
        //===================================
        
        std::map<std::string, renderEngine::rTexture> m_Textures;
        std::map<std::string, rSoundBuffer> m_SoundBuffers;
        //std::map<std::string, sf::Font> m_Fonts;
};

#endif /* ASSETMANAGER_H */

