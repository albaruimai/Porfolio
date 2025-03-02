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


struct BT_Create_Terremoto_t : BTNode_t{
    BT_Create_Terremoto_t () {}

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        if(!ectx.bb->salientes_bb.empty()){
            uint8_t max_rocas = 6; 
            uint8_t rocas_creadas = 0;
            for(auto* saliente:  ectx.bb->salientes_bb){
                if(saliente){  
                    auto* sal_col = saliente->template getComponent<ColliderComponent_t>();
                    if(sal_col){
                        for(auto &box_sal: sal_col->boxes){
                            if(box_sal.lanzadorrocas){
                                int tirar = rand() % 3;
                                if(!tirar){
                                    auto* sal_phy = saliente->template getComponent<PhysicsComponent_t>();

                                    if (sal_phy != nullptr) {
                                        //calculamos las casillas que caben en el saliente
                                        int cachos { static_cast<int>((box_sal.box.xRight - box_sal.box.xLeft)/24) };
                                        int cacho_ele {0};

                                        //como sabemos donde esta el jugador elegimos el punto de drop  mas cercano
                                        if(ectx.ia->visto){
                                            //comprobamos donde se encuentra el jugador en referencia al inicio del saliente
                                            float resta { static_cast<float>(ectx.bb->player_tx - (sal_phy->x +box_sal.disX+box_sal.box.xLeft)) };
                                            cacho_ele = resta/24;
                                            if(resta < 0){cacho_ele = 0;}
                                            if(resta > (box_sal.box.xRight-box_sal.box.xLeft)){cacho_ele = cachos-1;}

                                        }
                                        //como no vemos al jugador elegimos un cacho aleatorio para poner la roca
                                        else{
                                            cacho_ele = rand() % cachos;
                                        }


                                        
                                        float suma_sal { (cacho_ele*24) + 6 + box_sal.box.xLeft };
                                        ectx.gof->createRoca(sal_phy->x +box_sal.disX+suma_sal, sal_phy->y+box_sal.disY, sal_phy->z+5, 0.8, true,  saliente->getEntityID());
                                        ++rocas_creadas;
                                        
                                        //std::cout<<"Numero de entidades en EM: "<<ectx.EM->getEntities().size()<<"\n";
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
                if(rocas_creadas >= max_rocas){
                    break;
                }

            }
        }
        return BTNodeStatus_t::success;

    }

    private:
};