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

struct BT_ACT_seek_t : BTNode_t{
    BT_ACT_seek_t (){}

    //NO UTILIZAR POR AHORA
    //Sigue al target pasado por parametro 

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::ACTseek;

        if(ectx.ia->wait > 0){
            Point2D_t target{ectx.bb->player_tx, ectx.bb->player_ty};
            auto st { STBEH::seek(ectx.phy, &target, ectx.ia->time2arrive, ectx.ia->arrivalRadius) };

            ectx.phy->v_linear= st.linear;
            ectx.phy->v_angular= st.angular;

            --(ectx.ia->wait);

            return BTNodeStatus_t::running;
        }else{
            return BTNodeStatus_t::success;
        }


    }

    private:

};