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

struct BTDecisionAlternative_t : BTNode_t{
    BTDecisionAlternative_t (bool a = false) : alternative{a} {}

    //Permite a la IA no siempre ejecutar el mismo arbol en el mismo orden para darle variedad

    BTNodeStatus_t run(EntityContext_t &) noexcept final{
        alternative = !alternative;
        if (alternative) return BTNodeStatus_t::success;
        return BTNodeStatus_t::fail;
    }

    private:
        bool  alternative { false };

};