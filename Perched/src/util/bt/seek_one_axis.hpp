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
#include "../stbe/Steering.hpp"

struct BTSeekOneAxis_t : BTNode_t{
    BTSeekOneAxis_t (){}

    //Comprueba si el player se encuentra cerca de la IA

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        ectx.ia->estadoIA = BTState::seek_one_axis;
        

        //Comprobar si el blackboard tiene target, que entonces significa que si ha visto al enemigo
        if(ectx.ia->wait > 0){
            if(ectx.ia->visto){
                Point2D_t target{ectx.bb->player_tx, ectx.phy->y};
                //std::cout<<"target x: "<<target.x<<" , target y: "<<target.y<<"\n";
                //std::cout<<"Mi pos x: "<<ectx.phy->x<<" , Mi pos y: "<<ectx.phy->y<<"\n";

                if(ectx.ia->has_object){
                    auto* enty      { ectx.EM->getEntityByID(ectx.ia->has_object) };
                    if(enty){

                        auto* enty_col  { enty->getComponent<ColliderComponent_t>() };
                        auto* enty_phy  { enty->getComponent<PhysicsComponent_t>() };
                        if(enty_phy && enty_col){
                    //std::cout<<"Tengo algo :3 \n";
                            BoundingBoxNode_t* my_sal { nullptr };
                            int min_dist {500};

                            for (auto &all_sal: enty_col->boxes){
                                double this_dist { std::sqrt(std::pow((enty_phy->y+all_sal.disY) - ectx.phy->y  , 2 ) + std::pow(ectx.phy->x - (enty_phy->x+all_sal.disX), 2))};
                                if(this_dist < min_dist ){
                                    min_dist = this_dist;
                                    my_sal = &all_sal;
                                }
                                
                            }
                            //std::cout<<"MIN_DIST: "<<min_dist<<" \n";
                            if(my_sal){
                                //std::cout<<"ENCONTRE SALIENTE CERCANO \n";
                                if(ectx.bb->player_tx < ((enty_phy->x + my_sal->disX + my_sal->box.xRight) + ectx.col->boxes[0].box.xLeft ) && ectx.bb->player_tx > ((enty_phy->x + my_sal->disX + my_sal->box.xLeft) + ectx.col->boxes[0].box.xRight)){
                                    target.x = ectx.bb->player_tx;
                                    //std::cout<<"Mi pos: "<<ectx.phy->x<<"POS del player: "<<target.x<<"\n";
                                }

                                if(ectx.bb->player_tx >= ((enty_phy->x+my_sal->disX+my_sal->box.xRight) + ectx.col->boxes[0].box.xLeft) ){
                                    //std::cout<<"VOY IZQUIERDA \n";
                                    target.x = (enty_phy->x+my_sal->disX+my_sal->box.xRight) + ectx.col->boxes[0].box.xLeft;
                                }

                                if(ectx.bb->player_tx <= (enty_phy->x+my_sal->disX+my_sal->box.xLeft + ectx.col->boxes[0].box.xRight)){
                                    //std::cout<<"VOY DERECHA\n";
                                    target.x = enty_phy->x+my_sal->disX+my_sal->box.xLeft + ectx.col->boxes[0].box.xRight;
                                }
                                    
                                do_seek_one(ectx, target);
                            }

                        }
                    }
                }
            }
            

            --(ectx.ia->wait);

            return BTNodeStatus_t::running;
        }else{
            return BTNodeStatus_t::success;
        }
    }

    void do_seek_one(EntityContext_t &ectx, Point2D_t target){

        auto st { STBEH::seek(ectx.phy, &target, ectx.ia->time2arrive, ectx.ia->arrivalRadius) };
        ectx.phy->v_linear= st.linear;
        ectx.phy->v_angular= st.angular;
    }

    private:
};