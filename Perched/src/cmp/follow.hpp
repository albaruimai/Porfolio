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
#include "../Motor3D/Node.hpp"

struct FollowComponent_t : public ECS::ComponentBase_t<FollowComponent_t> {
    explicit FollowComponent_t(ECS::EntityID_t eid) : ComponentBase_t(eid)
    {};

    float x { 0 }, y { 0 }, z { 0 };
    ECS::EntityID_t followEntityID { 0 };
    bool folActive{true};

    int numcria {-1};
    bool meCogioPlayer {false};
};