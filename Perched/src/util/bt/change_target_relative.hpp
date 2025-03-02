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

struct BT_Change_Target_Relative : BTNode_t{
    BT_Change_Target_Relative (double x, double y) : new_x{x} , new_y{y}{}

    //Ajusta el target a una posicion relativa al target actual
    //Se usa para que la IA por ahora se mueva

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::change_target_init;

        //std::cout<<"HE CAMBIADO \n";

        ectx.ia->tx = ectx.ia->tx + new_x;
        ectx.ia->ty = ectx.ia->ty + new_y;
        return BTNodeStatus_t::success;
    }

    private:
        double new_x {0.0};
        double new_y {0.0};

};