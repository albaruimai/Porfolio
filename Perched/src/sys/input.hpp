//####################################################################
//# GNU Free Documentation License                                   #
//# Version 1.3, 3 November 2008                                     #
//#                                                                  #
//# Copyright (C) 2021 Lumina Studio                                 #
//# (Paula Garcia Morales, Laura Gil Lopez, Jorge Perez Dominguez,   #
//#  Alba Ruiz Maiques, Javier Sibada Lopez, Miguel Teruel Carvajal) #
//#                                                                  #
//# Everyone is permitted to copy and distribute verbatim copies     #
//# of this license document, but changing it is not allowed.        #
//####################################################################
//#                                                                  #
//# InputSystem sirve para actualizar las entidades que tienen       #
//#   componente de input y comprobar que teclas estan pulsadas      #
//#   para actualizar la velocidad de la entidad con input.          #
//#                                                                  #
//####################################################################

#pragma once

#include <chrono>
#include <iostream>
#include <sys/time.h>
#include <ctime>
#include <iostream>

#include "../util/typealiases.hpp"
#include "../cmp/input.hpp"
#include "../cmp/physics.hpp"
#include "../cmp/render.hpp"
#include "../cmp/health.hpp"
#include "../cmp/collider.hpp"
#include "../cmp/sound.hpp"
#include "../cmp/stamina.hpp"
#include "../cmp/follow.hpp"

#include "../util/typealiases.hpp"
#include "../util/keyboard.hpp"
#include "../util/timer.hpp"

#include "../Motor3D/Motor3DLUM/Motor3DLUM.hpp"

template <typename GameCTX_t>
struct InputSystem_t {
    //El explicit se recomienda ponerlo en todos los constructores
    //Sirve para que el programa no haga conversiones implicitas a la hora de construir objetos
    explicit InputSystem_t(Motor3DLUM* motor);  //Constructor
                                                //Destructor
    bool update(GameCTX_t& g,Motor3DLUM* motor);
    void setDirectionMoving(PhysicsComponent_t*);
    
    bool isKeyPressed (keys::KEY_CODE_G k);

    private:
        void checkMusgoHielo(GameCTX_t& g, int lf, int du, bool avoid, PhysicsComponent_t& phy);
        void sumarDistancia (PhysicsComponent_t& phy, RenderComponent_t& ren, size_t pos, float x, float y);
        void moverExtremidadesLeftRight (int lf, InputComponent_t& inp, PhysicsComponent_t& phy, RenderComponent_t& ren); 
        void moverExtremidadesDownUp (int du, InputComponent_t& inp, PhysicsComponent_t& phy, RenderComponent_t& ren);

        void animCuerda(GameCTX_t& g, RenderComponent_t& ren);

        void moveDiagonal(GameCTX_t& g, InputComponent_t& inp, PhysicsComponent_t& phy, RenderComponent_t& ren);
        void moveAvoid(GameCTX_t& g, InputComponent_t& inp, PhysicsComponent_t& phy, RenderComponent_t& ren);
        void moveLeft(GameCTX_t& g, InputComponent_t& inp, PhysicsComponent_t& phy, RenderComponent_t& ren);
        void moveRight(GameCTX_t& g, InputComponent_t& inp, PhysicsComponent_t& phy, RenderComponent_t& ren);
        void moveUp(GameCTX_t& g, InputComponent_t& inp, PhysicsComponent_t& phy, RenderComponent_t& ren);
        void moveDown(GameCTX_t& g, InputComponent_t& inp, PhysicsComponent_t& phy, RenderComponent_t& ren);

        static void onkeypress(keys::KEY_CODE_G k);
        //funcion static existe sin que haya un objeto InputSystem

        static void onkeyrelease(keys::KEY_CODE_G k);

        inline static ECS::Keyboard_t ms_Keyboard {};
        //static para que solo haya un ms_Keyboard en todo el codigo

        EventReceiver* eventReceiver; 

        int prubi {0};

        float sumax {0};

        bool leg_Front_I { false };
        bool leg_Front_D { false };
        bool leg_Back_I { false };
        bool leg_Back_D { false };


        temporizador characterTimer;

        const float *axes;
        const unsigned char* butons;
        int presentJoy;
};