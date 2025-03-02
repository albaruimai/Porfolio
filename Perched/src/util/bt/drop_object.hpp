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
#include <iostream>
#include "node.hpp"
#include "../typealiases.hpp"

// Este nodo sirve para cargarse el palo en caso de que no lo haya tirado el aguila antes de llegar al nido (no se ha encontrado al player)
struct BTDropObject_t : BTNode_t{
    BTDropObject_t () {}

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        if( ectx.ia->has_object){
            auto* my_palo { ectx.EM->getEntityByID(ectx.ia->has_object) }; 
            if(my_palo){
                auto* he { my_palo->template getComponent<HealthComponent_t>() };
                auto* fol { my_palo->template getComponent<FollowComponent_t>() };
                if(fol && he){
                    he->damage=20;
                    fol->folActive = false;
                    ectx.ia->has_object = 0;
                }
            }
        }
        return BTNodeStatus_t::success;

    }

    private:
};