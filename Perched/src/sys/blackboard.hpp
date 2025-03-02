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
//#                                                                  #
//#                                                                  #
//#                                                                  #
//####################################################################

#pragma once
#include "../util/typealiases.hpp"
#include "../cmp/collider.hpp"
#include "../cmp/sound.hpp"
#include "../cmp/control.hpp"
#include "../cmp/physics.hpp"
#include "../cmp/collider.hpp"
#include "../cmp/entity.hpp"

#include <iostream>

template <typename GameCTX_t>
struct BlackBoardSystem_t {
    explicit BlackBoardSystem_t() = default;

    void update(GameCTX_t& g) const; //El GameContext no es const para que puedan modificarse los valores de las velocidades

    void changeEnganches(GameCTX_t& g) const;

    void ponerColisiones(GameCTX_t& g) const;
    void buscarColisiones(GameCTX_t& g, int x, int y) const;

    void quitarColisiones(GameCTX_t& g) const;

    void ajustarSonidoTunel(GameCTX_t& g, ECS::Entity_t* e) const;
};