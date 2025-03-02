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


struct BTThrowObject_t : BTNode_t{
    BTThrowObject_t (objects_type tipo) : crear{tipo} {}

    //Comprueba si stat que se va a comprobar (stamina, cansancio o ira) en el enemigo es menor que lo que se ha pasado como parametro

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::throw_object;

        auto vel{0};
        switch(crear){
            case objects_type::Telaranya:
                if(ectx.phy->x < ectx.bb->player_tx){
                    vel = 1;
                }else{
                    vel = -1;
                }
                ectx.gof->createTelaranya(ectx.phy->x-2, ectx.phy->y-2, vel);
                return BTNodeStatus_t::success;
            
            break;
            
            case objects_type::Palo:
                auto& pal { ectx.gof->createPalo(ectx.phy->x-2, ectx.phy->y-8, 1, ectx.ia->getEntityID()) };
                if(&pal){
                    ectx.ia->has_object = pal.getEntityID();
                }
                return BTNodeStatus_t::success;
            break;
        }
        return BTNodeStatus_t::fail;
    }

    private:
        objects_type crear {};
};

/*
        if(crear == objects_type::Telaranya){ectx.ia->my_object = objects_type::Telaranya;}
        if(crear == objects_type::Palo){ ectx.ia->my_object = objects_type::Palo;}
        return BTNodeStatus_t::success;
*/