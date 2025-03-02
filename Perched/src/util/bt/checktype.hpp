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

struct BTCheckType_t : BTNode_t{
    BTCheckType_t (type_enemy condi) : type{condi} {}

    //Comprueba el tipo de enemigo que es la IA
    //Se usa para saber por que rama del BT hay que ir

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::check_type;

        if (ectx.ia->enemy == type) { return BTNodeStatus_t::success;}
        return BTNodeStatus_t::fail;
    }

    private:
        type_enemy  type { type_enemy::Aguila };

};