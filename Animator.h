/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Animator.h
 * Author: claudiac
 *
 * Created on 22 de marzo de 2018, 20:23
 
*/
#ifndef ANIMATION_H
#define ANIMATION_H


#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

class Animator {
public:
    struct Animation
    {
        std::string m_Name;
        std::string m_TextureName;
        std::vector<renderEngine::rIntRect> m_Frames;
        renderEngine::rTime m_Duration;
        bool m_Looping;

        Animation(std::string const& name, std::string const& textureName,
            renderEngine::rTime const& duration, bool looping)
            : m_Name(name), m_TextureName(textureName), m_Duration(duration), m_Looping (looping)
        {}
        //Adds frames horizontaly
        void AddFrames(sf::Vector2i const& startFrom,
                sf::Vector2i const& frameSize, unsigned int frames)
        {
            sf::Vector2i current = startFrom;
            for (unsigned int i = 0; i < frames; i++)
            {
                //Add current frame from position and frame size
                m_Frames.push_back(renderEngine::rIntRect(current.x, current.y, frameSize.x, frameSize.y));
                //Advance current frame horizontally
                current.x += frameSize.x;
            }

        }

    };
    
    Animator(renderEngine::rSprite& sprite);
    Animator::Animation& CreateAnimation(std::string const& name, std::string const& textureName, renderEngine::rTime const& duration, bool loop = false);

    void Update(renderEngine::rTime const& dt);
    //Devuelve si el switch fue bien
    bool SwitchAnimation(std::string const& name);
    std::string GetCurrentAnimationName() const;
    renderEngine::rSprite& GetSprite();

private:
        //Returns the animation with the passed name
        //Return nullptr si no encuentra la animacion

        Animator::Animation* FindAnimation(std::string const& name);
        void SwitchAnimation(Animator::Animation* animation);
        
        //Reference to the sprite que se ha de crear fuera de la clase 
        renderEngine::rSprite& m_Sprite;
        renderEngine::rTime m_CurrentTime;
        std::list <Animator::Animation> m_Animations;
        Animator::Animation* m_CurrentAnimation;
        

};

#endif /* ANIMATOR_H */
