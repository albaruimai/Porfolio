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

struct BT_Apply_Goal_t : BTNode_t{
    BT_Apply_Goal_t ( ) {}
    // Le aplica los valores de la accion hecha a los goals para que vayan cambiando de acciones las ias

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::applygoal;

        if(!ectx.ia->action_chosen) return BTNodeStatus_t::fail;
        for(auto &goal : ectx.ia->my_goals){
            // order of my_goals vector: Eat, Attact, Protect, Make_nido
            if (goal.name == goal_types::Eat){
                int32_t to_add { ectx.ia->action_chosen->getGoalChange(goal) };
                ectx.ia->my_goals[0].value += to_add;
                if(to_add < 0) ectx.ia->my_goals[0].value = 0;
            }
            if (goal.name == goal_types::Attack){
                int32_t to_add { ectx.ia->action_chosen->getGoalChange(goal) };
                ectx.ia->my_goals[1].value += to_add;
                if(to_add < 0) ectx.ia->my_goals[1].value = 0;
            }
            if (goal.name == goal_types::Protect){
                int32_t to_add { ectx.ia->action_chosen->getGoalChange(goal) };
                ectx.ia->my_goals[2].value += to_add;
                if(to_add < 0) ectx.ia->my_goals[2].value = 0;
            }
            if (goal.name == goal_types::Make_nido){
                int32_t to_add { ectx.ia->action_chosen->getGoalChange(goal) };
                ectx.ia->my_goals[3].value += to_add;
                if(to_add < 0) ectx.ia->my_goals[3].value = 0;
            }

        }
        //if(ectx.ia->action_chosen->belongs_to == type_enemy::Cabra){
        //    std::cout<< "eat" <<ectx.ia->my_goals[0].value<< "atack" <<ectx.ia->my_goals[1].value<< "protect" <<ectx.ia->my_goals[2].value<< "make nido" <<ectx.ia->my_goals[3].value<<"\n";    
        //}
        return BTNodeStatus_t::success;
    }

    private:

};