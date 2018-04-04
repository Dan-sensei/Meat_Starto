/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   renderEngine.h
 * Author: pablomanez
 *
 * Created on 21 de marzo de 2018, 15:30
 */

#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <SFML/Graphics.hpp>
class renderEngine {
public:
    //<SINGLETON>
    static renderEngine& Instance(){
        static renderEngine instance;
        return instance;
    }
    //</SINGLETON>
    
    class rTexture {
        friend class renderEngine;
        public:
            rTexture();                             //CONSTRUCTOR SIN ARGUMENTOS
            rTexture(std::string path);             //CONSTRUCTOR CON ARGUMENTOS
            
            void loadFromFile(std::string path);    //APLICAR UNA IMAGEN A LA TEXTURA
            int getXSize();
            int getYSize();
            
        private:
            sf::Texture* getTexture();              //DEVUELVE LA TEXTURA (USAR SOLO INTERNAMENTE)
            sf::Texture text;
    };
    
    class rSprite {
        public:
            rSprite();                                  //CONSTRUCTOR
            
            void draw();
            
            void setTexture(rTexture &t);               //APLICAR UNA TEXTURA
            void setOrigin(float x, float y);           //ESTABLECER EL PUNTO ORIGEN
            void setScale(float x, float y);            //ESTABLECER LA ESCALA
            void setPosition(float x, float y);         //ESTABLECER LA POSICION
            void setRotation(float a);                  //ESTABLECER UNA ROTACION
            void rotate(float r);
            float getRotation();
            void setTextureRect(sf::IntRect& rect);
            std::array<float,2> getPosition();          //DEVUELVE LA POSICION
        private:
            sf::Sprite sprite;
    };
    
    
    class rView {
        friend class renderEngine;
        public:
            rView(float pos_x, float pos_y, float size_x, float size_y);        //CONSTRUCTOR
            
            void zoom(float z);                         //ZOOM A LA VISTA
            void setCenter(float x, float y);           //CENTRO DE LA VISTA
            std::array<float,2> getCenter();            //CENTRO DE LA VISTA
            void move(float x, float y);                //MOVER LA VISTA  
            
        private:
            sf::View getView();             //CONSIGUE LA VISTA. USO PRIVADO
            sf::View view;
    };
    
    class rTime {
        public:
            rTime();
            rTime(float sec);
            
            float asSeconds();                      //TIEMPO EN SEGUNDOS
            float asMilliseconds();                 //TIEMPO EN MILISEGUNDOS
            float asMicroseconds();                 //TIEMPO EN MICROSEGUNDOS
            void incrementTime(renderEngine::rTime t);
            void Zero();                            //TENER A 0 EL TIEMPO
            sf::Time getTime();
        private:
            sf::Time time;
    };
    
    class rClock {
        public:
            rClock();
            
            renderEngine::rTime restart();          //REINICIAR EL RELOJ
            renderEngine::rTime getElapsedTime();   //TIEMPO SIN REINICIAR EL RELOJ
        private:
            sf::Clock clock;
    };
    
    class rEvent {
        friend class renderEngine;
        public:
            rEvent();
            enum EventType{                //ENUMERACION CON LOS DISTINTOS EVENTOS (FALTA PONER LOS QUE SE VAYAN A UTILIZAR)
                KeyPressed      = sf::Event::EventType::KeyPressed,
                KeyReleased     = sf::Event::EventType::KeyReleased,
            };
            sf::Event::EventType sfType();
            
            
            int getKeyCode();                                                   //DEVUELVE EL CODIGO DEL EVENTO DE TECLADO
            
        private:
            sf::Event* getEvent();
            
            sf::Event event;
    };
    
    class rConvexShape {
        public:
            rConvexShape();
            
            void draw();
            void setPointCount(int s);                      //NUMERO DE PUNTOS
            void setPoint(int p, float x, float y);         //ESTABLECER UN PUNTO
            void setFillColor(char c);                      //ESTABLECER UN COLOR DE FONDO
            void setOutlineColor(char c);                   //ESTABLECER UN COLOR PARA EL BORDE
            void setOutlineThickness(float f);              //ESTABLECER UN ANCHO PARA EL BORDE
            std::array<float,2> getPosition();              //CONSEGUIR POSICION
            void setPosition(float x, float y);             //ESTABLECER LA POSICION
            void move(float x, float y);                    //MOVER
            void setTexture(rTexture &t);                   //ESTABLECER TEXTURAS
            
        private:
            sf::ConvexShape cs;
    };
    
    class rRectangleShape {
        public:
            rRectangleShape();
            rRectangleShape(float x, float y);
            
            void draw();                                    //DIBUJAR
            
            void setTexture(rTexture &t);                   //ESTABLECER TEXTURA
            void setPosition(float x, float y);             //ESTABLECER POSICION
            void setFillColor(char c);                      //ESTABLECER UN COLOR
            void setSize(float x, float y);                 //ESTABLECER UN TAMANYO
            void move(float x, float y);                    //MOVER
            
            std::array<float,2> getPosition();              //CONSEGUIR POSICION
        private:
            sf::RectangleShape rs;
    };
    
    //METODOS PUBLICOS
    bool isOpen();                                  //TRUE SI LA VENTANA ESTA ABIERTA
    void close();                                   //CIERRA LA VENTANA
    void clear(char c);                             //CLEAR DE SFML
    void display();                                 //DIBUJA LA VENTANA
    std::array<float,2> getSize();                  //DEVUELVE LAS DIMENSIONES DE LA VENTANA
    std::array<float,2> getViewCenter();            //DEVUELVE EL CENTRO DE LA VENTANA
    
    void setView(rView v);                          //ESTABLECER UNA VISTA
    bool pollEvent(rEvent &e);                      //PARA CONTROLAR LOS EVENTOS
    
    
private:
    
    //<SINGLETON>
    renderEngine();
    renderEngine(const renderEngine& orig);
    void operator=(renderEngine const& orig);
    //</SINGLETON>
    
    sf::RenderWindow* getWindow();                  //DEVUELVE LA VENTANA A LAS CLASES Nested DE renderEngine

    sf::RenderWindow window;
};

#endif /* RENDERENGINE_H */

