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

    //Se comprueba si el player esta en una posicion save 

struct BT_Check_See_Player_t : BTNode_t{
    BT_Check_See_Player_t (){}

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::check_see_player;
        
        if(ectx.ia->visto){
//            std::cout<<" x: "<< ectx.bb->player_tx<<" y: "<< ectx.bb->player_ty<<"\n";
            return BTNodeStatus_t::success;
        }
//            std::cout<<"NO HE ENCONTRADO AL PLAYER \n";
        return BTNodeStatus_t::fail;
    };
};