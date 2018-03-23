/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   renderEngine.cpp
 * Author: pablomanez
 * 
 * Created on 21 de marzo de 2018, 15:30
 */

#include <SFML/Graphics.hpp>


#include "renderEngine.h"

#define FRAMERATE 60

renderEngine::renderEngine():
window(sf::VideoMode(1920,1080),"Carga de mapa",sf::Style::Default)
//window(sf::VideoMode(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height),"Carga de mapa",sf::Style::Default)
{
    window.setFramerateLimit(FRAMERATE);
}

bool renderEngine::isOpen() {
    return window.isOpen();
}

void renderEngine::display() {
    window.display();
}

void renderEngine::clear(char c) {
    switch(c){
        case 'r':
            window.clear(sf::Color::Red);
            break;
        case 'y':
            window.clear(sf::Color::Yellow);
            break;
        default:
            window.clear(sf::Color::Black);
            break;
    }
}

sf::RenderWindow* renderEngine::getWindow() {
    return &window;
}

std::array<float, 2> renderEngine::getSize() {
    std::array<float,2> v;

    v[0] = window.getSize().x;
    v[1] = window.getSize().y;
    
    return v;
}

void renderEngine::setView(rView v) {
    window.setView(v.getView());
}

bool renderEngine::pollEvent(rEvent &e) {
    return window.pollEvent(*e.getEvent());
}

void renderEngine::close() {
    window.close();
}

renderEngine::renderEngine(const renderEngine& orig) {
}

//============================= TEXTURA =============================//
renderEngine::rTexture::rTexture() {}

renderEngine::rTexture::rTexture(std::string path) {
    text.loadFromFile(path);
}

void renderEngine::rTexture::loadFromFile(std::string path) {
    text.loadFromFile(path);
}

sf::Texture* renderEngine::rTexture::getTexture() {
    return &text;
}


//============================= SPRITE =============================//
renderEngine::rSprite::rSprite() {}

void renderEngine::rSprite::draw() {
    renderEngine* sfml;
    sfml->Instance().getWindow()->draw(sprite);
}


void renderEngine::rSprite::setTexture(rTexture &t) {
    sprite.setTexture(*t.getTexture());
}

void renderEngine::rSprite::setOrigin(float x, float y) {
    sprite.setOrigin(x,y);
}

void renderEngine::rSprite::setScale(float x, float y) {
    sprite.setScale(x,y);
}

void renderEngine::rSprite::setPosition(float x, float y) {
    sprite.setPosition(x,y);
}

void renderEngine::rSprite::setRotation(float a) {
    sprite.setRotation(a);
}

std::array<float, 2> renderEngine::rSprite::getPosition() {
    std::array<float,2> ret;
    ret[0] = sprite.getPosition().x;
    ret[1] = sprite.getPosition().y;
    
    return ret;
}

//============================= VISTA =============================//
renderEngine::rView::rView(float pos_x, float pos_y, float size_x, float size_y):
view(sf::FloatRect(pos_x,pos_y,size_x,size_y))
{
}

void renderEngine::rView::zoom(float z) {
    view.zoom(z);
}

sf::View renderEngine::rView::getView() {
    return view;
}

std::array<float, 2> renderEngine::rView::getCenter() {
    std::array<float, 2> ret;
    ret[0] = view.getCenter().x;
    ret[1] = view.getCenter().y;
    
    return ret;
}

void renderEngine::rView::setCenter(float x, float y) {
    view.setCenter(x,y);
}

//============================= RELOJ =============================//
renderEngine::rClock::rClock() {}

renderEngine::rTime renderEngine::rClock::restart() {
    clock.restart();
}

float renderEngine::rClock::asSeconds() {
    
}
        
//============================= EVENTOS =============================//
renderEngine::rEvent::rEvent() {
    
}

int renderEngine::rEvent::getKeyCode() {
    return event.key.code;
}

sf::Event* renderEngine::rEvent::getEvent() {
    return &event;
}

sf::Event::EventType renderEngine::rEvent::sfType() {
    return event.type;
}


//============================= TIEMPO =============================//
renderEngine::rTime::rTime() {

}

float renderEngine::rTime::asSeconds() {
    return time.asSeconds();
}

float renderEngine::rTime::asMilliseconds() {
    return time.asMilliseconds();
}

float renderEngine::rTime::asMicroseconds() {
    return time.asMicroseconds();
}








