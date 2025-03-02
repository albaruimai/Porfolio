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


struct BT_Stop_t : BTNode_t{
    BT_Stop_t (int tim) : time{tim}{
    }

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::do_action;
        ectx.ia->enemy_timer.count(true);
        if(ectx.ia->visto){
            if(ectx.ia->enemy == type_enemy::Cabra){
                if( ectx.ia->enemy_timer.getEllapsed()>=time/2){
                    ectx.ia->enemy_timer.reset();
                    return BTNodeStatus_t::success;
                }
            }
            if(ectx.ia->enemy == type_enemy::Aguila){
                ectx.ia->enemy_timer.reset();
                return BTNodeStatus_t::success;
                
            }
            
        }
        if( ectx.ia->enemy_timer.getEllapsed()>=time){
            ectx.ia->enemy_timer.reset();
            return BTNodeStatus_t::success;
        }
        return BTNodeStatus_t::running;


    };

    private:
        int time;
        //temporizador time_anim;
};
