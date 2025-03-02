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

#include "health.hpp"

template <typename GameCTX_t>
constexpr bool HealthSystem_t<GameCTX_t>::leafNodeCollided(const BoundingBoxNode_t& bn) const noexcept {
    return bn.collided;
}

template <typename GameCTX_t>
constexpr void HealthSystem_t<GameCTX_t>::deleteNodes(GameCTX_t& g, const HealthComponent_t& he, Motor3DLUM* motor) const noexcept {
    auto* ren { g.template getRequiredComponent<HealthComponent_t, RenderComponent_t>(he) };

    if (!ren) { return; }

    motor->removeNode(ren->entityNodes.node.node);

    if (!ren->entityNodes.childs.empty()) {
        for (size_t i {0}; i < static_cast<size_t>(ren->entityNodes.childs.size()); ++i) {
            motor->removeNode(ren->entityNodes.childs.at(i).node);
        }        
    }

    //std::cout << "Entity " << he.getEntityID() << " is dead1!\n";
    g.destroyEntityByID(he.getEntityID());
}

template <typename GameCTX_t>
constexpr void HealthSystem_t<GameCTX_t>::escalarSemilla(GameCTX_t& g, HealthComponent_t& he, Motor3DLUM* motor) {
    if(he.fpssemilla!= motor->getFPS()){
        he.fpssemilla = motor->getFPS();

        if (he.buclesemilla < 100) {
            auto* ren { g.template getRequiredComponent<HealthComponent_t, RenderComponent_t>(he) };

            if (ren != nullptr) {
                float sca { ren->entityNodes.node.node->getScale().getVectorX() };
                ren->entityNodes.node.node->setScale(Vector3d((sca/20)*19,(sca/20)*19,(sca/20)*19));
            }

            ++(he.buclesemilla);
        } else {
            auto* sou { g.template getRequiredComponent<HealthComponent_t, SoundComponent_t>(he) };
            if(sou != nullptr){
                if (sou->parado == false) {
                    sou->marked_for_stop = 1;
                } else {
                    he.health = 0;
                    he.damage = 0;
                    he.buclesemilla = 0;

                    deleteNodes(g, he, motor);
                }                
            }            
        }
    }
}

template <typename GameCTX_t>
constexpr void HealthSystem_t<GameCTX_t>::restaurarPlayer(GameCTX_t& g, PhysicsComponent_t& phy, const PhysicsComponent_t& phyC) const {
    phy.x = phyC.x;
    phy.y = phyC.y;

    auto* ren { g.template getRequiredComponent<PhysicsComponent_t, RenderComponent_t>(phy) };

    if (ren != nullptr && !ren->entityNodes.childs.empty()) {
        for (size_t i {0}; i < static_cast<size_t>(ren->entityNodes.childs.size()); ++i) {
            ren->entityNodes.childs.at(i).x = phy.x + ren->entityNodes.childs.at(i).disx;
            ren->entityNodes.childs.at(i).y = phy.y + ren->entityNodes.childs.at(i).disy;
            ren->entityNodes.childs.at(i).z = phy.z + ren->entityNodes.childs.at(i).disz;
        }
    }
}

template <typename GameCTX_t>
constexpr void HealthSystem_t<GameCTX_t>::voyamorir(GameCTX_t& g, HealthComponent_t& he, Motor3DLUM* motor) {
    auto& bb { g.template getBlackBoard() };
    bb.muriendoplayer = true;

    auto* ren { g.template getRequiredComponent<HealthComponent_t, RenderComponent_t>(he) };
    auto* phy { g.template getRequiredComponent<HealthComponent_t, PhysicsComponent_t>(he) };
    auto* sou { g.template getRequiredComponent<HealthComponent_t, SoundComponent_t>(he) };

    if (ren != nullptr && phy != nullptr && sou != nullptr) {
        if(fpsmuertePlayer!= motor->getFPS()){
            fpsmuertePlayer = motor->getFPS();

            std::string abuscar {""};
            if (he.muertepordanyo == true) {
                if (bb.volviPlanoNormal == true) {
                    abuscar = "event:/Personajes/Zacarias/MuerteDaño";
                } else {
                    abuscar = "event:/Personajes/Zacarias Cueva/MuerteDaño";
                }
            } else {
                if (bb.volviPlanoNormal == true) {
                    abuscar = "event:/Personajes/Zacarias/MuerteCaida";
                } else {
                    abuscar = "event:/Personajes/Zacarias Cueva/MuerteCaida";
                }
            }

            auto encon { std::find(sou->my_events.begin(), sou->my_events.end(), abuscar) };

            if (encon != sou->my_events.end()) {
                sou->event_id = sou->my_events.at(encon - sou->my_events.begin());
                sou->isEvent3D = false;
                sou->marked_for_init = 1;
                sou->marked_for_play = 1;
            }

//            if(ren->entityNodes.node.node->getAnimation() != "muerte"){
//                ren->entityNodes.node.node->ActualizarAnimation("muerte");
//            }

            if (buclemuerte < 60) {
//                if (ren->entityNodes.node.node->getActualFrame() == 0) {
                    phy->y -= 1;
                    ++buclemuerte;
//                } 

//                ren->entityNodes.node.node->ActualizarFrame(4);

                he.damage = he.health;
            } else {
                he.health = 0;
                he.damage = 0;

                deleteNodes(g, he, motor); 
            }
        }
    } else {
        he.health = 0;
        he.damage = 0;

        deleteNodes(g, he, motor); 
    }
}

template <typename GameCTX_t>
constexpr void HealthSystem_t<GameCTX_t>::voyavivir(GameCTX_t& g, HealthComponent_t& he, ControlComponent_t& ct, Motor3DLUM* motor) {
    g.template getBlackBoard().muriendoplayer = false;

    he.damage = 0;
    he.health = he.maxHealth;
    
    auto* phy { g.template getRequiredComponent<HealthComponent_t, PhysicsComponent_t>(he) };

    bool encontrado { false };
    int resta { 0 };

    for (std::size_t i {ct.puntosControl.size() - 1}; i > 0 && encontrado != true; --i) {
        const auto* punC { g.getEntityByID(ct.puntosControl.at(i)) };

        if (punC != nullptr) {
            auto* phyC { punC->template getComponent<PhysicsComponent_t>() };

            if (phy !=nullptr && phyC != nullptr) {

                //restauro al player en el enganche que este debajo de player
                if (phyC->y < phy->y) {
                    restaurarPlayer(g, *phy, *phyC);

                    if (phyC->z > phyC->zinicial) {
                        phy->volverplanonormal = true;
                    } else {
                        if (g.template getBlackBoard().volviPlanoNormal == true) {
                            if (phyC->z < phyC->zinicial) {
                                phy->volverplanotunel = true;
                            }
                        }
                    }                             

                    encontrado = true;
                }
            }                         
        }                    
    }

    if (encontrado == false) {
        const auto* punC { g.getEntityByID(ct.puntosControl.at(ct.puntosControl.size()-1)) };

        if (punC != nullptr) {
            auto* phyC { punC->template getComponent<PhysicsComponent_t>() };

            //restauro a player en el ultimo enganche cogido
            if (phy !=nullptr && phyC != nullptr) {
                restaurarPlayer(g, *phy, *phyC);

                if (phyC->z > phyC->zinicial) {
                    phy->volverplanonormal = true;
                } else {
                    if (g.template getBlackBoard().volviPlanoNormal == true) {
                        if (phyC->z < phyC->zinicial) {
                            phy->volverplanotunel = true;
                        }
                    }
                }                            

                encontrado = true;
            }
        }
    }

    auto* est { g.template getRequiredComponent<HealthComponent_t, StaminaComponent_t>(he) };

    if(est!=nullptr){
        est->cantStamina = est->maxStamina;
    }
}

template <typename GameCTX_t>
constexpr void HealthSystem_t<GameCTX_t>::checkControl(GameCTX_t& g, HealthComponent_t& he, Motor3DLUM* motor) noexcept {
    auto* c { g.template getRequiredComponent<HealthComponent_t, ColliderComponent_t>(he) };

    if (c->properties & ColliderComponent_t::P_IsPlayer) {
        auto* ct { g.template getRequiredComponent<HealthComponent_t, ControlComponent_t>(he) };

        if(ct){
            if (ct->puntosControl.size() == 0) {
                //animacion muerte
                voyamorir(g, he, motor);                
            } else {
                voyavivir(g, he, *ct, motor);
            } 
        }     
    } else {
        if (c->properties != ColliderComponent_t::P_Enemy) {
            if (c->properties == ColliderComponent_t::P_Semilla) {
                //escalar semilla
                
                escalarSemilla(g, he, motor);
            } else {
                he.health = 0;
                he.damage = 0;

                deleteNodes(g, he, motor);
            }
        }
    }
}

template <typename GameCTX_t>
constexpr void HealthSystem_t<GameCTX_t>::sumarVidaArbusto(HealthComponent_t& he) const noexcept {
    if (he.timefornextlife != 0) {
        --(he.timefornextlife);
    } else {
        he.vidasumada = false;
    }

    if (he.sumarvida == true && he.health < 3) {
        ++(he.health);
        he.sumarvida = false;
        he.vidasumada = true;

        he.timefornextlife = 100;
    }
}

template <typename GameCTX_t>
constexpr void HealthSystem_t<GameCTX_t>::texturizarporDanyo(GameCTX_t& g, HealthComponent_t& he, Motor3DLUM* motor) {
    if(! he.hurtCooldown == 0 ){ 
        --(he.hurtCooldown); 
    } else {
        auto& bb { g.template getBlackBoard() }; 
        bb.danyoplayer = false;
    }
}

template <typename GameCTX_t>
constexpr void HealthSystem_t<GameCTX_t>::update(GameCTX_t& g, Motor3DLUM* motor) noexcept {
    for(auto& he: g.template getComponents<HealthComponent_t>()){
        if (he.damage) {
            //std::cout << "Entity " << he.getEntityID() << " damage " << he.damage << " vida " << he.health <<"\n";
            
            if (he.damage < he.health) {
                auto* phy { g.template getRequiredComponent<HealthComponent_t, PhysicsComponent_t>(he) };

                if (phy != nullptr) {
                    if (phy->timeTunel == 0) {
                        he.health -= he.damage;
                    }
                }                

                he.damage = 0;
            } else {
                checkControl(g, he, motor);
            }
        }

        auto* re { g.template getRequiredComponent<HealthComponent_t, RenderComponent_t>(he) };
        auto* c { g.template getRequiredComponent<HealthComponent_t, ColliderComponent_t>(he) };

        if (!c) { continue; }

        if (c->properties & ColliderComponent_t::P_IsPlayer ){
            sumarVidaArbusto(he);

            texturizarporDanyo(g, he, motor);
        }

        for (auto& box: c->boxes) {
            if (he.health && leafNodeCollided(box)) {
                if (--he.health == 0) {
                    checkControl(g, he, motor);
                }

                box.collided = false;
            }
        }
    }
}   