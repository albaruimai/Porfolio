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
#include "entity.hpp"
#include "../util/typealiases.hpp"
#include <iostream>

struct ControlComponent_t : public ECS::ComponentBase_t<ControlComponent_t> {
    explicit ControlComponent_t(ECS::EntityID_t eid) : ComponentBase_t(eid)
    {
        puntosControl.reserve(100);
    };

    ECS::Vec_t<ECS::EntityID_t> puntosControl {};
};