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

    //Nodo INCOMPLETO, TENDRA USO CUANDO SE AÑADAN LAS ANIMACIONES

struct BT_Do_Action_t : BTNode_t{
    BT_Do_Action_t (type_action act, int tim) : action{act}{
        //time_anim.init(tim);
    }

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::do_action;

        switch(action){
            case type_action::Atacar:
                //Do ATACAR animation
                return BTNodeStatus_t::success;
            break;

            case type_action::Comer:
                //Do COMER animation
                return BTNodeStatus_t::success;
            break;

            case type_action::Descansar:
                //Do DESCANSAR animation
                return BTNodeStatus_t::success;
            break;

            case type_action::Dormir:
                //Do DORMIR animation
                return BTNodeStatus_t::success;
            break;

            case type_action::Vigilar:
                //Do VIGILAR animation
                return BTNodeStatus_t::success;
            break;
        }
        return BTNodeStatus_t::fail;
    };

    private:
        type_action action;
        //temporizador time_anim;
};

/*
    if(action == type_action::Atacar){
            //Do ATACAR animation
            return BTNodeStatus_t::success;
        }
        if(action == type_action::Comer){
            //Do COMER animation
            return BTNodeStatus_t::success;
        }
        if(action == type_action::Descansar){
            //Do DESCANSAR animation
            return BTNodeStatus_t::success;
        }
        if(action == type_action::Dormir){
            //Do DORMIR animation
            return BTNodeStatus_t::success;
        }
        if(action == type_action::Vigilar){
            //Do VIGILAR animation
            return BTNodeStatus_t::success;
        }
*/