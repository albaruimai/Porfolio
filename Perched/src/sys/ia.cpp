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

#include "ia.hpp"



template <typename GameCTX_t>
bool IASystem_t<GameCTX_t>::update(GameCTX_t& g, Motor3DLUM* motor) {


    //Obtener el component Blackboard
    BlackboardComponent_t& bb { g.template getBlackBoard() };

    for(auto& ia: g.template getComponents<IAComponent_t>()){

        
        auto* phy { g.template getRequiredComponent<IAComponent_t, PhysicsComponent_t>(ia) };
        auto* hea { g.template getRequiredComponent<IAComponent_t, HealthComponent_t>(ia) };
        auto* col { g.template getRequiredComponent<IAComponent_t, ColliderComponent_t>(ia) };

        if(!phy || !hea || !col || !&bb) {return false;}
        if (ia.tree){
            // creo todo el contexto necesario para el bt y lo ejecuto
            EntityContext_t ectx {g.template getEntityByID(ia.getEntityID()) , &ia, phy, col, &bb, &g, my_gof};
            ia.tree->run(ectx);

            // Esto es para que independientemente de lo que este haciendo si el aguila tiene un palo intente tirarlo al jugador
            if(ia.visto && ia.has_object && ia.enemy==type_enemy::Aguila){
                this->drop_palo(g, phy, ia, bb); 
            }
            //reset de la vision para la siguiente ejecución
            ia.visto = false;

            if (ia.enemy==type_enemy::Aranya) {
                if(ia.fpsIA!= motor->getFPS()){
                    ia.fpsIA = motor->getFPS();

                    auto* ren { g.template getRequiredComponent<IAComponent_t, RenderComponent_t>(ia) };

                    if (ren != nullptr && ren->entityNodes.node.node !=nullptr) {
                        ren->entityNodes.node.node->ActualizarFrame(2);
                    }
                    else
                    {
                        std::cout<<" ia.cpp 59 OJO QUE ESTO ES NULL\n";
                    }
                }
            } else {
                if(fpsIA!= motor->getFPS()){
                    fpsIA = motor->getFPS();

                    auto* ren { g.template getRequiredComponent<IAComponent_t, RenderComponent_t>(ia) };

                    if (ren != nullptr && ren->entityNodes.node.node!=nullptr) {
                        ren->entityNodes.node.node->ActualizarFrame(2);
                    }
                    else
                    {
                        std::cout<<" ia.cpp 73 OJO QUE ESTO ES NULL\n";
                    }
                }
            }
            
            
            if (ia.action_chosen != nullptr) {
                auto* sound { g.template getRequiredComponent<IAComponent_t, SoundComponent_t>(ia) };
                if(sound != nullptr && ia.meGolpean == false){

                    switch (ia.enemy) {
                        case type_enemy::Aranya:
                            switch (ia.action_chosen->related_goal) {
                                case goal_types::Attack:
                                    sound->event_id = "event:/Personajes/Araña/AtaqueAranya";
                                    break;
                                case goal_types::Protect:
                                    sound->event_id = "event:/Personajes/Araña/SonidoAranya";
                                    break;
                                case goal_types::Eat:
                                    sound->event_id = "event:/Personajes/Araña/MovimientoAranya";
                                    break;
                            }
                            
                            break;

                        case type_enemy::Cabra:
                            if (ia.meGolpean == false) {
                                switch (ia.action_chosen->related_goal) {
                                    case goal_types::Attack:
                                        sound->event_id = "event:/Personajes/Cabra/Avalacha";
                                        break;
                                    case goal_types::Protect:
                                        sound->event_id = "event:/Personajes/Cabra/HierbaCabra";
                                        break;
                                    case goal_types::Eat:
                                        sound->event_id = "event:/Personajes/Cabra/PastarCabra";
                                        break;
                                }
                            }                            
                            break;

                        case type_enemy::Aguila:
                            switch (ia.action_chosen->related_goal) {
                                case goal_types::Attack:
                                    sound->event_id = "event:/Personajes/Aguila/Graznido";
                                    break;
                                case goal_types::Make_nido:
                                    sound->event_id = "event:/Personajes/Aguila/Ramas";
                                    break;
                                case goal_types::Eat:
                                    sound->event_id = "event:/Personajes/Aguila/Aleteo";
                                    break;
                                case goal_types::Protect:
                                    sound->event_id = "event:/Personajes/Aguila/Aleteo";
                                    break;
                            }
                            break;
                    }

                    sound->marked_for_init = 1;
                    sound->marked_for_play = 1;
                }
            }
        }

        
    }


    return true;
}      


template <typename GameCTX_t>
bool IASystem_t<GameCTX_t>::drop_palo (GameCTX_t& g, PhysicsComponent_t* phy, IAComponent_t& ia, BlackboardComponent_t& bb) const{
    if(phy->y > bb.player_ty && (phy->x-20 < bb.player_tx && phy->x+30 > bb.player_tx)){    //ajuste de la vision para tirar palo 
        auto* my_palo { g.template getEntityByID(ia.has_object) }; 
        if(my_palo){
            auto* fol { my_palo->template getComponent<FollowComponent_t>() };
            if(fol){
                fol->folActive = false;
                ia.has_object = 0;
                return true;
            }
        }
    }
    return false;
}
