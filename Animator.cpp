/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Animator.cpp
 * Author: claudiac
 * 
 * Created on 22 de marzo de 2018, 20:23
 */

#include "Animator.h"
#include "AssetManager.h"

#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>



Animator::Animator(renderEngine::rSprite& sprite) 
    :m_Sprite(sprite), m_CurrentTime(), m_CurrentAnimation(nullptr){

}

Animator::Animation& Animator::CreateAnimation(std::string const& name, std::string const& textureName, renderEngine::rTime const& duration, bool loop)
{
   //Nombre para referenciarlo fuera de la clase
   //loop--> si se repite o reproducirse solo una vez
    
    //metemos instancia de la animacion en la lista m_Animations
    m_Animations.push_back(        
            Animator::Animation(name, textureName,duration,loop));
    //si no hay otra animacion utiliza la actual
    if(m_CurrentAnimation == nullptr){
        SwitchAnimation(&m_Animations.back());
    }
    
    return m_Animations.back();
}

void Animator::SwitchAnimation(Animator::Animation* animation)
{
    //Cambia la textura al sprite
    if(animation != nullptr)
    {
        m_Sprite.setTexture(AssetManager::GetTexture(animation->m_TextureName));
        /*
        sf::Texture tex;
        if (!tex.loadFromFile("resources/player6.png"))
        {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
        }
        m_Sprite.setTexture(tex);
        */
        
    }
    m_CurrentAnimation = animation;
    m_CurrentTime.Zero(); //Reset time
}   



bool Animator::SwitchAnimation(std::string const& name)
{//Trata de uscar la animacion con el nombre que le pasan
    auto animation = FindAnimation(name);
    if(animation !=nullptr)
    {
        SwitchAnimation(animation);
        return true;
    }
    return false;
}
 

Animator::Animation* Animator::FindAnimation(std::string const& name)
{
    for(auto it = m_Animations.begin(); it != m_Animations.end(); ++it)
    {
        if(it-> m_Name == name)
            return &*it;
            
    }
    
    return nullptr;
}

std::string Animator::GetCurrentAnimationName() const
{
    if(m_CurrentAnimation != nullptr)
        return m_CurrentAnimation->m_Name;
 
    //Si no hay ninguna animacion funcionando devuelve string vacio
    return "";
}

void Animator::Update(renderEngine::rTime const& dt)
{
    //Si no hay animaciones devuelve un return
    if(m_CurrentAnimation == nullptr)
        return;
    m_CurrentTime.incrementTime(dt);
    
    //Coje el frame actual de la animacion
    float scaledTime = (m_CurrentTime.asSeconds() / m_CurrentAnimation->m_Duration.asSeconds());
    int numFrames = m_CurrentAnimation->m_Frames.size();
    int currentFrame = static_cast<int>(scaledTime * numFrames);
    
    //Si la animacion está en marcha calcula el frame correcto
    if(m_CurrentAnimation-> m_Looping)
        currentFrame %=numFrames;
    else if(currentFrame >= numFrames)
        currentFrame = numFrames -1;
    
    //Pone la textura
    m_Sprite.setTextureRect(m_CurrentAnimation->m_Frames[currentFrame]);
    
    
}

renderEngine::rSprite& Animator::GetSprite(){
    
    m_Sprite.rotate(m_Sprite.getRotation()+30);
    
    return m_Sprite;
}



