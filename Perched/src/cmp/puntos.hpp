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
//#                                                                  #
//####################################################################

#pragma once
#include "component.hpp"
#include <iostream>

struct PuntosComponent_t : public ECS::ComponentBase_t<PuntosComponent_t> {
    explicit PuntosComponent_t(ECS::EntityID_t eid) : ComponentBase_t(eid)
    {};

    uint32_t puntos { 0 };
    uint32_t cantSumable { 10 };
};