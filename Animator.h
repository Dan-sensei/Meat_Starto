/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Animation.h
 * Author: dan
 *
 * Created on 10 de marzo de 2018, 16:25
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <list>
#include <string>
#include <iostream>


class Animator {
    
public:
    struct Animation{
        std::string animName;
        std::string animTexture;
        std::vector<sf::IntRect> animFrames;
        sf::Time animDuration;
        bool animLoop;
        
        Animation(std::string const& n, std::string const& tex, sf::Time const& d, bool l)
                :animName(n), animTexture(tex), animDuration(d), animLoop(l){}
        
        void AddFrames(const sf::Vector2i& startFrom, const sf::Vector2i& frameSize, unsigned int nFrames){
            sf::Vector2i currentFrame = startFrom;
            for(unsigned int i = 0; i < nFrames; i++){
                animFrames.push_back(sf::IntRect(currentFrame.x, currentFrame.y, frameSize.x, frameSize.y));
                currentFrame.x += frameSize.x;
            }
        }
    };

    Animator(sf::Sprite& s);
    
    Animator::Animation& createAnimation(std::string const& name, std::string const& textureName, sf::Time const& duration, bool loop = false);
    void update(sf::Time const& dt);
    
private:
    sf::Sprite& sprite;
    sf::Time currentTime;
    std::list<Animation> animations;
    Animation* currentAnimation;

    void switchAnimation(Animation* anim);
};

#endif /* ANIMATION_H */

