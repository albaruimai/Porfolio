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

struct BT_Change_Target_To_Player : BTNode_t{
    BT_Change_Target_To_Player (){}
    //se usa para que el aguila haga circulos relativos al player en caso de verlo, si no lo ve, es un change from init normal

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        if(ectx.ia->visto){
            //std::cout<<"HE CAMBIADO \n";
            ectx.ia->tx = ectx.bb->player_tx;
            ectx.ia->ty = ectx.bb->player_ty;
            
        }



        return BTNodeStatus_t::success;

    }

    private:

};