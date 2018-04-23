/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   boss.cpp
 * Author: pablomanez
 * 
 * Created on 5 de abril de 2018, 16:11
 */

#include "boss.h"
#include "Juego.h"

#define DES 2000

boss::boss() {
}

void boss::init(int x_) {
    //x_ ES LA POSICION MAXIMA DEL ANTERIOR NODO DIBUJADO

    //COORDENADAS
    float a = 70;
    x_min = x_+(a*12);
    x_max = x_+(a*53);
    
    on = false;
    restart = false;
    
    //BOSS
    javi.r.setSize(70,70);
    javi.r.setPosition(x_min+(a*5),560);
    javi.r.setFillColor('r');
    javi.x_f = -1;
    javi.y_f = -1;
    javi.x_v = 0;
    javi.y_v = 0;
    javi.ir = NULL;
    javi.llegada = true;
    
    //CREO LA "PUERTA"
    puerta[0].r.setSize(a*12,a*5);
    puerta[0].r.setPosition(x_min-(a*8),(a*20)+DES);
    puerta[1].r.setPosition(x_min+(a*4),(a*20)+DES);
    puerta[2].r.setPosition(x_min+(a*4),(a*21)+DES);
    puerta[3].r.setPosition(x_min+(a*4),(a*22)+DES);
    puerta[4].r.setPosition(x_min+(a*4),(a*23)+DES);
    puerta[5].r.setPosition(x_min+(a*4),(a*24)+DES);
    puerta[6].r.setPosition(x_min+(a*5),(a*22)+DES);
    puerta[7].r.setPosition(x_min+(a*5),(a*23)+DES);
    puerta[8].r.setPosition(x_min+(a*5),(a*24)+DES);
    puerta[9].r.setPosition(x_min+(a*6),(a*23)+DES);
    puerta[10].r.setPosition(x_min+(a*6),(a*24)+DES);
    puerta[11].r.setPosition(x_min+(a*7),(a*24)+DES);
    
    for(int i=0 ; i<12 ; i++){
        if(i != 0){
            puerta[i].r.setSize(a,a);
        }
        puerta[i].r.setFillColor('r');
    }
    
    //---DEBUG
    
    //POSICION FINAL
    r_aux.setFillColor('g');
    r_aux.setPosition(-1,-1);
    r_aux.setSize(20,20);
    
    //INTRECT
    ir_aux.setFillColor('t');
    ir_aux.setOutlineColor('g');
    ir_aux.setOutlineThickness(5);
}

void boss::update() {
    renderEngine *sfml;
    
    float x_m = sfml->Instance().getViewCenter()[0];
    
    //x_ MARCA LA POSICION CENTRAL DE LA VISTA
    physicsEngine *world;
    if(x_m> (x_min+(70*20)) && x_m < x_max){
       //std::cout << " | ----------- Boss ON" << std::endl;
        //COMIENZA LA BATALLA FINAL
        on = true;
        
        if(!restart){
            //std::cout << " | ----------- Restart" << std::endl;
            //AQUI SOLO ENTRA UNA VEZ
            //CREO LAS COLISIONES DE LA PUERTA 
            for(int i=0 ; i<12 ; i++){
                float x = puerta[i].r.getPosition()[0];
                float y = puerta[i].r.getPosition()[1]-DES;
                puerta[i].r.setPosition(x,y);

                float w = puerta[i].r.getSize()[0];
                float h = puerta[i].r.getSize()[1];
                x = puerta[i].r.getPosition()[0]+(w/2);
                y = puerta[i].r.getPosition()[1]+(h/2);
                puerta[i].b = world->Instance().createBody(w,h,x,y,'k');
                
                t = new physicsEngine::type;
                t->id = 1;
                t->data = this;
                puerta[i].b.setUserData(t);
            }

            clock_boss.restart();   //REINICIO LOS RELOJES
            dt_boss.restart();
            dt_fan.restart();
            restart = true;
        }
        
        //HACER UNA ESPECIE DE ANIMACION
        
        //UPDATE DE JAVI
        //std::cout << " | ----------- Update de Javi" << std::endl;
        updateJavi();
        
        //std::cout << " | ----------- Fases del Boss" << std::endl;
        fasesBoss();
            
        //std::cout << " | ----------- Habilidades especiales" << std::endl;
        if(dt_fan.getElapsedTime().asSeconds()>0.1){
            //GENERO EL NUMERO ALEATORIO
            int rand = physicsEngine::Instance().genIntRandom(0, 100);
            if(rand>97)    crearAbanicoProyectiles();
            //if(distribution(gen)>40)    crearProyectilTele();
            
            dt_fan.restart();
        }

        //std::cout << " | ----------- Movimiento de proyectiles" << std::endl << std::endl;
        //MOVIMIENTO DE LOS PROYECTILES
        for(int i=0 ; i<javi.proy.size() ; i++){
            float vx = javi.proy[i]->v_x;
            float vy = javi.proy[i]->v_y;

            javi.proy[i]->r.move(vx,vy);
            
            //MILAGROSAMENTE FUNCIONA
            if( javi.proy[i]->r.getPosition()[1]>2600    || javi.proy[i]->r.getPosition()[1]<0 || 
                javi.proy[i]->r.getPosition()[0]>x_max+(70*5)   || javi.proy[i]->r.getPosition()[0]<x_min-(70*5)){
                    //std::cout << "Soy un proyectil y me destruyo" << std::endl;
                
                delete javi.proy[i];
                javi.proy[i] = NULL;
                
                javi.proy.erase(javi.proy.begin()+i); 
                if(i+1==javi.proy.size())   javi.proy.shrink_to_fit();
            }
        }
        
        //MOVIMIENTO DE LOS PROYECTILES TELEDIRIGIDOS
        /*
        for(int i=0 ; i<javi.proyT.size() ; i++){
            javi.proyT[i]->r.move(0,5);

            //javi.proyT[i]->r.rotate(javi.proyT[i]->angle);
            
            
            
            if( javi.proy[i]->r.getPosition()[1]>2100    || javi.proyT[i]->r.getPosition()[1]<0 || 
                javi.proy[i]->r.getPosition()[0]>x_max   || javi.proyT[i]->r.getPosition()[0]<x_min){
                    //std::cout << "Soy un proyectil y me destruyo" << std::endl;
                
                delete javi.proyT[i];
                javi.proyT[i] = NULL;
                
                javi.proyT.erase(javi.proyT.begin()+i);
                if(i+1==javi.proyT.size())   javi.proyT.shrink_to_fit();
            }
        }
        */


    }
    else{
        on = false;
    }
}

void boss::fasesBoss() {
    int np = Juego::Instance().getPlayers()->size();
    int r = physicsEngine::Instance().genIntRandom(0,np-1);
    
    //std::cout << Juego::Instance().getPlayers()[0][r]->getName() << std::endl;
    float x_ = Juego::Instance().getPlayers()[0][r]->getXPosition();
    float y_ = Juego::Instance().getPlayers()[0][r]->getYPosition();
    
    if(clock_boss.getElapsedTime().asSeconds()<20 && clock_boss.getElapsedTime().asSeconds()>=0){
        if(dt_boss.getElapsedTime().asSeconds() > 0.2){
                //std::cout << "CREO BALA" << std::endl;
            crearProyectil(x_,y_);
            dt_boss.restart();
        }
    }
    else if(clock_boss.getElapsedTime().asSeconds()>25 && clock_boss.getElapsedTime().asSeconds()<=26){
        if(dt_boss.getElapsedTime().asSeconds() > 0.05){
                //std::cout << "CREO BALA" << std::endl;
            crearProyectil(x_,y_);
            dt_boss.restart();
        }
    }
    else if(clock_boss.getElapsedTime().asSeconds()>28 && clock_boss.getElapsedTime().asSeconds()<=30){
        if(dt_boss.getElapsedTime().asSeconds() > 0.5){
            crearAbanicoProyectiles();
            dt_boss.restart();
        }
    }
    else if(clock_boss.getElapsedTime().asSeconds()>30 && clock_boss.getElapsedTime().asSeconds()<31){
        if(dt_boss.getElapsedTime().asSeconds() > 0.002){
                //std::cout << "CREO BALA" << std::endl;
            crearProyectil(x_,y_);
            dt_boss.restart();
        }
    }
    else if(clock_boss.getElapsedTime().asSeconds()>=31){
        if(dt_boss.getElapsedTime().asSeconds() > 0.2){
                //std::cout << "CREO BALA" << std::endl;
            crearProyectil(x_,y_);
            dt_boss.restart();
        }
    }
}

void boss::updateJavi() {
    //SI LLEGADA ES TRUE, ENTONCES ENCUENTRA OTRA POSICION DENTRO DE UN RANGO
        //std::cout << javi.llegada << std::endl;
    float factor = 100;
    float factor_v = 1;
    
    
    if(javi.llegada){
        //std::uniform_real_distribution<float> dv(1,3);
        
        //factor_v = dv(gen);
        javi.x_f = physicsEngine::Instance().genIntRandom(x_min+(70*3),x_min+(70*34));
        javi.y_f = physicsEngine::Instance().genIntRandom(70*7, 70*15);
        
        javi.x_v = (float) (javi.x_f-javi.r.getPosition()[0])/factor;
        javi.y_v = (float) (javi.y_f-javi.r.getPosition()[1])/factor;
        
        if(javi.ir == NULL){
            javi.ir = new renderEngine::rIntRect(javi.r.getPosition()[0],javi.r.getPosition()[1],javi.x_v * factor,javi.y_v * factor);
        }
        else{
            delete javi.ir;
            javi.ir = NULL;
            javi.ir = new renderEngine::rIntRect(javi.r.getPosition()[0],javi.r.getPosition()[1],javi.x_v * factor,javi.y_v * factor);
        }
            
        javi.llegada = false;
        
        //DEBUG
        r_aux.setPosition(javi.x_f,javi.y_f);
        ir_aux.setPosition(javi.r.getPosition()[0],javi.r.getPosition()[1]);
        ir_aux.setSize(javi.ir->widht,javi.ir->height);
            //std::cout   << "LEFT: " << javi.ir->left << ", TOP: " << javi.ir->top << ", WIDHT: " << javi.ir->widht << ", HEIGHT: " << javi.ir->height << std::endl;
            //std::cout << "X_f: " << javi.x_f << ", Y_f: " << javi.y_f << std::endl;
            //std::cout << "V(" << javi.x_v << "," << javi.y_v << ")" << std::endl;
    }
    
    javi.r.move(javi.x_v*factor_v,javi.y_v*factor_v);
        //std::cout << "V(" << javi.x_v*factor_v << "," << javi.y_v*factor_v << ")" << std::endl;
    
    if(!javi.ir->contains(javi.r.getPosition()[0],javi.r.getPosition()[1])){
        javi.llegada = true;
    }

}

void boss::crearProyectilTele() {
    // ------------ EN PRUEBAS ------------ //
    
    // x=y²/4, SE DEBE APLICAR UN OFFSET A LOS LADOS
    proyectilT *aux = new proyectilT;
    
    aux->r.setFillColor('b');
    aux->r.setSize(20,20);
    aux->angle = 45;
    
    aux->x_ini = javi.r.getPosition()[0];
    aux->y_ini = javi.r.getPosition()[1];
    aux->r.setPosition(aux->x_ini,aux->y_ini);
    aux->r.rotate(aux->angle);
    
    /*
    aux->a = 50;
    aux->a_1 = 100;
    aux->a_2 = 100;
    
    aux->x_fin = aux->x_ini+aux->a_1;
    aux->y_fin = aux->y_ini+aux->a_2;
    */
    
    javi.proyT.push_back(aux);
}

void boss::crearAbanicoProyectiles(){
        std::cout << "Javi used fan of bullets" << std::endl;

    float ang = 0.125;
    for(float i=0 ; i<4 ; i+=ang){
        int factor = 15;    //FACTOR VELOCIDAD
        int w = 25;
        int h = 25;

        float s_x = sin(M_PI/180*(90*i));
        float s_y = cos(M_PI/180*(90*i));

            //std::cout << "X-> sin(" << 90*i << ") : " << s_x << std::endl; //X
            //std::cout << "Y-> cos(" << 90*i << ") : " << s_y << std::endl; //Y
            //std::cout << std::endl;

        proyectil *p_aux = new proyectil;
        p_aux->v_x = s_x*factor;
        p_aux->v_y = s_y*factor;

        p_aux->r.setSize(w,h);
        p_aux->r.setPosition(javi.r.getPosition()[0],javi.r.getPosition()[1]);
        p_aux->r.setFillColor('b');

        javi.proy.push_back(p_aux);
    }
}

void boss::crearProyectil(float x_, float y_) {
    //CREO EL PROYECTIL
    //LO AÑADO AL VECTOR DEL JEFE
    int a = 70;
    float factor = 120;
    
    float w = 15;
    float h = 15;
    
    float x = javi.r.getPosition()[0];
    float y = javi.r.getPosition()[1];
    
    proyectil *aux = new proyectil;
    aux->r.setSize(w,h);
    aux->r.setPosition(x+(a/2),y+(a/2));
    aux->r.setFillColor('k');
    
    //AQUI SE DEBERIAN DE CONSEGUIR LAS POSICIONES DE LOS PERSONAJES
    //HE TENIDO QUE PASARLAS A TRAVES DE 3 FUNCIONES
        //std::cout << "X: " << x_ << std::endl;
        //std::cout << "Y: " << y_ << std::endl;
    aux->v_x = (x_ - x)/factor;
    aux->v_y = (y_ - y)/factor;
        //std::cout << "V (" << aux.v_x << "," << aux.v_y << ")" << std::endl;
    
    javi.proy.push_back(aux);
}

void boss::render() {
    
    if(on){
        //<DEBUG>
        /*
        r_aux.draw();
        ir_aux.draw();
        */
        //</DEBUG>
        
        for(int i=0 ; i<12 ; i++){
            puerta[i].r.draw();
        }
        for(int i=0 ; i<javi.proy.size() ; i++){
            javi.proy[i]->r.draw();
        }
        for(int i=0 ; i<javi.proyT.size() ; i++){
            javi.proyT[i]->r.draw();
        }
        javi.r.draw();
    }
}

bool boss::isBossOn() { return on;}




boss::boss(const boss& orig) {
}
