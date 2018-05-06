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
#include <iostream>
#include <SFML/Window/WindowStyle.hpp>

#define FRAMERATE 60

renderEngine::renderEngine():
window(sf::VideoMode(1920,1080),"Meat STARTO!",sf::Style::Default)
//window(sf::VideoMode(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height),"Carga de mapa",sf::Style::Default)
{
    window.setFramerateLimit(FRAMERATE);
    window.setVerticalSyncEnabled(true);
    _state = 0;
    
}

void                renderEngine::display   ()          {   window.display();}
void                renderEngine::setView   (rView v)   {   window.setView(v.getView());}
void                renderEngine::close     ()          {   window.close();}

bool                renderEngine::isOpen    ()          {   return window.isOpen();}   //TRUE SI LA VENTANA ESTA ABIERTA
sf::RenderWindow*   renderEngine::getWindow ()          {   return &window;}   
bool                renderEngine::pollEvent (rEvent &e) {   return window.pollEvent(*e.getEvent());}
bool renderEngine::isJoystickConnected      (int j)     {   sf::Joystick::isConnected(j);}
void renderEngine::moveView(float x, float y) {
    const sf::View *view = &(window.getView());
    //FALTA IMPLEMENTACION
}

void renderEngine::ChangeState(State* pState) {
    _state = pState;
    if(NULL != _state){
        _state->Handle();
    }
}
void renderEngine::clear(char c) {              //COLOR DEL CLEAR
    switch(c){
        case 'w':   window.clear(sf::Color::White);       break;
        case 'r':   window.clear(sf::Color::Red);       break;
        case 'y':   window.clear(sf::Color::Yellow);    break;
        default:    window.clear(sf::Color::Black);     break;
    }
}
std::array<float, 2> renderEngine::getSize() {          //X: getSize()[0] , Y: getSize()[1]
    std::array<float,2> v;

    v[0] = window.getSize().x;
    v[1] = window.getSize().y;
    
    return v;
}

std::array<float, 2> renderEngine::getViewCenter() {
    std::array<float,2> v;
    
    v[0] = window.getView().getCenter().x;
    v[1] = window.getView().getCenter().y;
    
    return v;
}



std::array<float, 2> renderEngine::getViewSize() {
    std::array<float,2> v;
    
    v[0] = window.getView().getSize().x;
    v[1] = window.getView().getSize().y;
    
    return v;
}


renderEngine::renderEngine(const renderEngine& orig) {}

//============================= TEXTURA =============================//
renderEngine::rTexture::rTexture() {}
renderEngine::rTexture::rTexture(std::string path) {    text.loadFromFile(path);}

void            renderEngine::rTexture::loadFromFile(std::string path)  {   text.loadFromFile(path);    }
void renderEngine::rTexture::loadFromImage(renderEngine::rImage im, renderEngine::rIntRect ir) {
    text.loadFromImage(im.getImage(),ir.getIntRect());

}

int             renderEngine::rTexture::getXSize()                      {   text.getSize().x;           }
int             renderEngine::rTexture::getYSize()                      {   text.getSize().y;           }
sf::Texture*    renderEngine::rTexture::getTexture()                    {   return &text;               }


//============================= SPRITE =============================//
renderEngine::rSprite::rSprite() {}

void renderEngine::rSprite::setTexture  (rTexture &t)       {   sprite.setTexture(*t.getTexture()); }
void renderEngine::rSprite::setRotation (float a)           {   sprite.setRotation(a);              }
void renderEngine::rSprite::rotate      (float r)           {   sprite.rotate(r);                   }
float renderEngine::rSprite::getRotation()                  {   return sprite.getRotation();        }
void renderEngine::rSprite::setTextureRect(renderEngine::rIntRect rect){  sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.widht, rect.height));        }
void renderEngine::rSprite::setOrigin   (float x, float y)  {   sprite.setOrigin(x,y);              }
void renderEngine::rSprite::setScale    (float x, float y)  {   sprite.setScale(x,y);               }
void renderEngine::rSprite::setPosition (float x, float y)  {   sprite.setPosition(x,y);            }
bool renderEngine::rSprite::intersects(renderEngine::rSprite sprite_){
    return sprite.getGlobalBounds().intersects(sprite_.getSprite().getGlobalBounds());
}
void renderEngine::rSprite::draw() {
    renderEngine* sfml;
    sfml->Instance().getWindow()->draw(sprite);
}
bool renderEngine::rSprite::intersects(renderEngine::rRectangleShape rs) {
    return sprite.getGlobalBounds().intersects(rs.getRectShape().getGlobalBounds());
}
bool renderEngine::rSprite::intersects(renderEngine::rCircleShape cs) {
    return sprite.getGlobalBounds().intersects(cs.getCircleShape().getGlobalBounds());
}

std::array<float, 2> renderEngine::rSprite::getPosition() {
    std::array<float,2> ret;
    ret[0] = sprite.getPosition().x;
    ret[1] = sprite.getPosition().y;
    
    return ret;
}

sf::Sprite renderEngine::rSprite::getSprite(){return sprite;}

//============================= VISTA =============================//
renderEngine::rView::rView(float pos_x, float pos_y, float size_x, float size_y):
view(sf::FloatRect(pos_x,pos_y,size_x,size_y)){ hasTarget_ = false;}

void renderEngine::rView::zoom      (float z)           {   view.zoom(z);           }
void renderEngine::rView::setCenter (float x, float y)  {   view.setCenter(x,y);    }
void renderEngine::rView::move(float x, float y)        {   view.move(x,y);         }
void renderEngine::rView::setSize(float x, float y)     {   view.setSize(x, y);     }
void renderEngine::rSprite::setColor(int r, int g, int b)   {   sprite.setColor(sf::Color(r, g, b));}
void renderEngine::rSprite::setColor(int r, int g, int b, int alpha)   {   sprite.setColor(sf::Color(r, g, b, alpha));}


sf::View                renderEngine::rView::getView    () {    return view;}
std::array<float, 2>    renderEngine::rView::getCenter  () {
    std::array<float, 2> ret;
    ret[0] = view.getCenter().x;
    ret[1] = view.getCenter().y;
    
    return ret;
}


//============================= RELOJ =============================//
renderEngine::rClock::rClock() {}

renderEngine::rTime renderEngine::rClock::restart() {clock.restart();}
renderEngine::rTime renderEngine::rClock::getElapsedTime() {clock.getElapsedTime();}

//============================= EVENTOS =============================//
renderEngine::rEvent::rEvent() {}

int renderEngine::rEvent::getKeyCode()              {return event.key.code;}
int renderEngine::rEvent::getJoystickButton()       {return event.joystickButton.button;}
float renderEngine::rEvent::getJoystickMoveAxis()     {return event.joystickMove.axis;}
float renderEngine::rEvent::getJoystickMovePosition() {return event.joystickMove.position;}
int renderEngine::rEvent::getJoystickId()           {return event.joystickConnect.joystickId;}


sf::Event*              renderEngine::rEvent::getEvent  () {    return &event;}
sf::Event::EventType    renderEngine::rEvent::sfType    () {    return event.type;}

//============================= TIEMPO =============================//
renderEngine::rTime::rTime() {}
renderEngine::rTime::rTime(float sec){
    time = sf::seconds(sec);
}

float renderEngine::rTime::asSeconds        ()  {   return time.asSeconds();}
float renderEngine::rTime::asMilliseconds   ()  {   return time.asMilliseconds();}
float renderEngine::rTime::asMicroseconds   ()  {   return time.asMicroseconds();}
void renderEngine::rTime::Zero              ()  {   time = sf::Time::Zero;}
void renderEngine::rTime::incrementTime(renderEngine::rTime t){ time += t.getTime();}
sf::Time renderEngine::rTime::getTime()         {   return time; }

//============================= CONVEXSHAPE =============================//
renderEngine::rConvexShape::rConvexShape() {
}

void renderEngine::rConvexShape::draw() {
    renderEngine* sfml;
    sfml->Instance().getWindow()->draw(cs);
}
void renderEngine::rConvexShape::setPointCount      (int s)                     {   cs.setPointCount(s);}
void renderEngine::rConvexShape::setOutlineThickness(float f)                   {   cs.setOutlineThickness(f);}
void renderEngine::rConvexShape::setPoint           (int p, float x, float y)   {   cs.setPoint(p,sf::Vector2f(x,y));}
void renderEngine::rConvexShape::move               (float x, float y)          {   cs.move(x,y);}
void renderEngine::rConvexShape::setPosition        (float x, float y)          {   cs.setPosition(x,y);}
void renderEngine::rConvexShape::setTexture         (rTexture &t)               {   cs.setTexture(t.getTexture());}
void renderEngine::rConvexShape::setFillColor(char c) {
    switch(c){
        case 't':   cs.setFillColor(sf::Color::Transparent);    break;
        case 'r':   cs.setFillColor(sf::Color::Red);            break;
        case 'y':   cs.setFillColor(sf::Color::Yellow);         break;
        case 'm':   cs.setFillColor(sf::Color::Magenta);        break;
        case 'w':   cs.setFillColor(sf::Color::White);          break;
        case 'g':   cs.setFillColor(sf::Color::Green);          break;
        case 'b':   cs.setFillColor(sf::Color::Blue);           break;
        case 'k':   cs.setFillColor(sf::Color::Black);          break;
        default:    cs.setFillColor(sf::Color::Black);          break;
    }
}
void renderEngine::rConvexShape::setOutlineColor(char c) {
    switch(c){
        case 'r':   cs.setOutlineColor(sf::Color::Red);    break;
        case 'g':   cs.setOutlineColor(sf::Color::Green);  break;
        default:    break;
    }
}
std::array<float, 2> renderEngine::rConvexShape::getPosition() {
    std::array<float,2> a;
    
    a[0] = cs.getPosition().x;
    a[1] = cs.getPosition().y;
    
    return a;
}


//============================= RECTANGLESHAPE =============================//
renderEngine::rRectangleShape::rRectangleShape() {}

renderEngine::rRectangleShape::rRectangleShape(float x, float y):
rs(sf::Vector2f(x,y)){}

void renderEngine::rRectangleShape::draw() {
    renderEngine* sfml;
    sfml->Instance().getWindow()->draw(rs);
}
void renderEngine::rRectangleShape::setTexture  (rTexture &t)       {   rs.setTexture(t.getTexture());}
void renderEngine::rRectangleShape::setPosition (float x, float y)  {   rs.setPosition(x,y);}
void renderEngine::rRectangleShape::setSize     (float x, float y)  {   rs.setSize(sf::Vector2f(x,y));}
void renderEngine::rRectangleShape::move        (float x, float y)  {   rs.move(x,y);}
void renderEngine::rRectangleShape::setOrigin   (float x, float y)  {   rs.setOrigin(x,y);}
void renderEngine::rRectangleShape::setRotation (float a)           {   rs.setRotation(a);}
void renderEngine::rRectangleShape::rotate      (float a)           {   rs.rotate(a);}

std::array<float, 2> renderEngine::rRectangleShape::getSize() {
    std::array<float,2> ret;
    
    ret[0] = rs.getSize().x;
    ret[1] = rs.getSize().y;
    
    return ret;
}

void renderEngine::rRectangleShape::setFillColor(char c) {
    switch(c){
        case 't':   rs.setFillColor(sf::Color::Transparent);    break;
        case 'r':   rs.setFillColor(sf::Color::Red);            break;
        case 'g':   rs.setFillColor(sf::Color::Green);          break;
        case 'b':   rs.setFillColor(sf::Color::Blue);           break;
        case 'y':   rs.setFillColor(sf::Color::Yellow);         break;
        case 'k':   rs.setFillColor(sf::Color::Black);          break;
        default:    break;
    }
}

void renderEngine::rRectangleShape::setFillRGBAColor(int r, int g, int b, int a) {
    sf::Color color(r,g,b,a);
    rs.setFillColor(color);
}

void renderEngine::rRectangleShape::setOutlineColor(char c) {
    switch(c){
        case 't':   rs.setOutlineColor(sf::Color::Transparent);    break;
        case 'r':   rs.setOutlineColor(sf::Color::Red);            break;
        case 'g':   rs.setOutlineColor(sf::Color::Green);          break;
        case 'b':   rs.setOutlineColor(sf::Color::Blue);           break;
        case 'y':   rs.setOutlineColor(sf::Color::Yellow);         break;
        case 'k':   rs.setOutlineColor(sf::Color::Black);          break;
        default:    break;
    }
}

void renderEngine::rRectangleShape::setOutlineThickness(float f) {rs.setOutlineThickness(f);}

std::array<float, 2> renderEngine::rRectangleShape::getPosition() {
    std::array<float, 2> ret;
    ret[0] = rs.getPosition().x;
    ret[1] = rs.getPosition().y;
    
    return ret;
}

sf::RectangleShape renderEngine::rRectangleShape::getRectShape() {
    return rs;
}

//============================= INTRECT =============================//
renderEngine::rIntRect::rIntRect() {
    left = 0;
    top = 0;
    widht = 0;
    height = 0;
}

renderEngine::rIntRect::rIntRect(int x, int y, int w, int h) : ir(x,y,w,h){
    left = x;
    top = y;
    widht = w;
    height = h;
}

void renderEngine::rIntRect::setTop(int t) {
    top = t;
    ir.top = t;
}
void renderEngine::rIntRect::setLeft(int l) {
    left = l;
    ir.left = l;
}
void renderEngine::rIntRect::setWidth(int w) {
    widht = w;
    ir.width = w;
}
void renderEngine::rIntRect::setHeight(int h) {
    height = h;
    ir.height = h;
}

bool renderEngine::rIntRect::contains(float x, float y) {
    return ir.contains(x,y);
}

sf::IntRect renderEngine::rIntRect::getIntRect() {
    return ir;
}


//============================= IMAGE =============================//
renderEngine::rImage::rImage() {}

void renderEngine::rImage::loadFromFIle(std::string path) { im.loadFromFile(path);
}

sf::Image renderEngine::rImage::getImage() {
    return im;
}

//============================= TEXT =============================//
renderEngine::rText::rText(){    
    //font.loadFromFile("assets/fonts/8-bit_pusab.ttf");
}
void renderEngine::rText::draw() {
    renderEngine* sfml;
    sfml->Instance().getWindow()->draw(txt);
}
void renderEngine::rText::setPosition       (float x, float y)      {   txt.setPosition(x,y);}
void renderEngine::rText::setScale          (float fx, float fy)    {   txt.setScale(fx,fy);}
void renderEngine::rText::setString         (std::string str)       {   txt.setString(str);}
void renderEngine::rText::setCharacterSize  (int s)                 {   txt.setCharacterSize(s);}
void renderEngine::rText::setFont           (rFont &font)           {   txt.setFont(*font.getFont());}
void renderEngine::rText::setOrigin         (float x, float y)      {   txt.setOrigin(x,y);}

std::array<float, 2> renderEngine::rText::getSize() {
    std::array<float,2> ret;
    
    ret[0] = txt.getGlobalBounds().width;
    ret[1] = txt.getGlobalBounds().height;
    
    return ret;
}

void renderEngine::rText::setFillColor(char c) {
    switch(c){
        case 't':   txt.setFillColor(sf::Color::Transparent);    break;
        case 'r':   txt.setFillColor(sf::Color::Red);            break;
        case 'g':   txt.setFillColor(sf::Color::Green);          break;
        case 'b':   txt.setFillColor(sf::Color::Blue);           break;
        case 'y':   txt.setFillColor(sf::Color::Yellow);         break;
        case 'k':   txt.setFillColor(sf::Color::Black);          break;
        case 'w':   txt.setFillColor(sf::Color::White);          break;
        default:    break;
    }
}

sf::Color renderEngine::rText::getFillColor() {return txt.getFillColor();};

//============================= FONT =============================//
renderEngine::rFont::rFont() {}
void renderEngine::rFont::loadFromFile  (std::string str)   {   font.loadFromFile(str);}
sf::Font* renderEngine::rFont::getFont   ()                 {   return &font;}

//============================= CIRCLESHAPE =============================//

renderEngine::rCircleShape::rCircleShape(float r, int pc) : cs(r,pc) {}

void renderEngine::rCircleShape::draw() {
    renderEngine* sfml;
    sfml->Instance().getWindow()->draw(cs);
}

void renderEngine::rCircleShape::setFillColor(char c) {
    switch(c){
        case 't':   cs.setFillColor(sf::Color::Transparent);    break;
        case 'r':   cs.setFillColor(sf::Color::Red);            break;
        case 'g':   cs.setFillColor(sf::Color::Green);          break;
        case 'b':   cs.setFillColor(sf::Color::Blue);           break;
        case 'y':   cs.setFillColor(sf::Color::Yellow);         break;
        case 'k':   cs.setFillColor(sf::Color::Black);          break;
        default:    break;
    }
}

void renderEngine::rCircleShape::setRadius(float r) {
    cs.setRadius(r);
}

void renderEngine::rCircleShape::setPosition(float x, float y) {
    cs.setPosition(x,y);
}

void renderEngine::rCircleShape::setOrigin(float x, float y) {
    cs.setOrigin(x,y);
}

sf::CircleShape renderEngine::rCircleShape::getCircleShape() {
    return cs;
}

std::array<float, 2> renderEngine::rCircleShape::getPosition() {
    std::array<float,2> ret;
    
    ret[0] = cs.getPosition().x;
    ret[1] = cs.getPosition().y;
    
    return ret;
}













