/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Animation.cpp
 * Author: dan
 * 
 * Created on 10 de marzo de 2018, 16:25
 */

//Esta clase forma parte del libro "SFML Essentials" para la animación de sprites

#include "Animator.h"
#include "AssetManager.h"

Animator::Animator(sf::Sprite& s)
    :sprite(s), currentTime(), currentAnimation(nullptr){}

Animator::Animation& Animator::createAnimation(const std::string& name, const std::string& textureName, const sf::Time& duration, bool loop){
    
    animations.push_back(Animation(name, textureName, duration, loop));
    
    if(currentAnimation == nullptr)
        switchAnimation(&animations.back());
    
    return animations.back();
}


void Animator::switchAnimation(Animation* anim){
    
    if(anim != nullptr)
        sprite.setTexture(AssetManager::GetTexture(anim->animTexture));
    
    currentAnimation = anim;
    currentTime = sf::Time::Zero;
}

void Animator::update(const sf::Time& dt){
    if(currentAnimation == nullptr)
        return;
    currentTime += dt;
    
    float ST = currentTime.asSeconds() / currentAnimation->animDuration.asSeconds();
    int n = currentAnimation->animFrames.size();
    int current = (int)(ST*n);
    
    if(currentAnimation->animLoop)
        current = current%n;
    else if(current >= n)
        current = n - 1;
    
    sprite.setTextureRect(currentAnimation->animFrames[current]);
    
}

