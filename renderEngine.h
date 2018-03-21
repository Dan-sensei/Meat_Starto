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
        public:
            rTexture();                             //CONSTRUCTOR SIN ARGUMENTOS
            rTexture(std::string path);             //CONSTRUCTOR CON ARGUMENTOS
            
            void loadFromFile(std::string path);    //APLICAR UNA IMAGEN A LA TEXTURA
            
            sf::Texture* getTexture();              //DEVUELVE LA TEXTURA (USAR SOLO INTERNAMENTE)
            
        private:
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
            
        private:
            sf::Sprite sprite;
    };
    
    class rView {
        public:
            rView(float pos_x, float pos_y, float size_x, float size_y);        //CONSTRUCTOR
            
            void zoom(float z);
            
            
        private:
            sf::View view;
    };
    
    //METODOS PUBLICOS
    bool isOpen();                                  //TRUE SI LA VENTANA ESTA ABIERTA
    void clear(char c);                             //CLEAR DE SFML
    void display();                                 //DIBUJA LA VENTANA
    std::array<float,2> getSize();                  //DEVUELVE LAS DIMENSIONES DE LA VENTANA
    
    //void setView(rView v);
    
    
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

