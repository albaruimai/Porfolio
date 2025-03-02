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

#include "colission.hpp"

template <typename GameCTX_t>
ColissionSystem_t<GameCTX_t>::ColissionSystem_t(int32_t xmin, int32_t xmax, int32_t ymin, int32_t ymax) 
    : m_xmin (xmin), m_xmax (xmax), m_ymin (ymin), m_ymax (ymax) {

    //std::cout << "mxmin: " << m_xmin << " mxmax: " << m_xmax << " mymin: " << m_ymin << " mymax: " << m_ymax << "\n";
}

template <typename GameCTX_t>
void ColissionSystem_t<GameCTX_t>::sizeMapa(GameCTX_t& g) noexcept {
    auto& bb { g.template getBlackBoard() };

    m_xmin = bb.xminM;
    m_xmax = bb.xmaxM;
    m_ymin = bb.yminM;
    m_ymax = bb.ymaxM;

    //std::cout << "mxmin: " << m_xmin << " mxmax: " << m_xmax << " mymin: " << m_ymin << " mymax: " << m_ymax << "\n";
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::borrarAlBorde(GameCTX_t& g, const ColliderComponent_t& inflicter) const noexcept {
    auto* inHe { g.template getRequiredComponent<ColliderComponent_t, HealthComponent_t>(inflicter) };

    if (!inHe) { return; }

    inHe->damage = 1;
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::checkMapColision(GameCTX_t& g, const ColliderComponent_t& col, PhysicsComponent_t& phy) const noexcept {
    
    if (phy.x < m_xmin || phy.x > m_xmax) {
        if (col.properties == ColliderComponent_t::P_Damages) {
            borrarAlBorde(g, col);
        } else {
            phy.x = phy.last_x;
            //std::cout << "choco x \n";
            //phy.x -= phy.vx; 
            //phy.vx = -phy.vx; 
        }
    }

    if (phy.y < m_ymin || phy.y > m_ymax) {
        if (col.properties == ColliderComponent_t::P_Damages) {
            borrarAlBorde(g, col);
        } else {
            phy.y = phy.last_y;
            //std::cout << "choco y\n";
            //phy.y -= phy.vy; 
            //phy.vy = -phy.vy;

            //if (phy.gravity) {
            //    phy.vy = 0;
            //} else {
            //    phy.vy = -phy.vy; 
            //}
        } 
    }
}

template <typename GameCTX_t>
BoundingBox_t<float> ColissionSystem_t<GameCTX_t>::moveToWorldCoords(const BoundingBox_t<float>& box, float x, float y, float z) const noexcept {
    BoundingBox_t<float> screenBox {
        x + box.xLeft,
        x + box.xRight,
        y + box.yUp,
        y + box.yDown,
        z + box.zFront,
        z + box.zBack
    };

    return screenBox;
}

/****************************************************************************************************/
/************************************COMPROBAR COLISION NORMAL***************************************/
/****************************************************************************************************/

template <typename GameCTX_t>
constexpr bool ColissionSystem_t<GameCTX_t>::checkObjectCercaCollision(float dist, BoundingBoxNode_t& bn1, BoundingBoxNode_t& bn2, const PhysicsComponent_t& phy1, const PhysicsComponent_t& phy2) const noexcept {
    auto b1 { moveToWorldCoords(bn1.box, phy1.x + bn1.disX, phy1.y + bn1.disY, phy1.z) };
    auto b2 { moveToWorldCoords(bn2.box, phy2.x + bn2.disX, phy2.y + bn2.disY, phy2.z) };

    auto checkIntervals { [](float L1, float R1, float L2, float R2) {
        if (L2 > R1) { return false; }
        if (L1 > R2) { return false; }

        return true;
    } };

    //E1  L1----R1                     L1----R1
    //E2           L2----R2  L2----R2

    if (checkIntervals(b1.xLeft - dist, b1.xRight + dist, b2.xLeft - dist, b2.xRight + dist)) {
        if (checkIntervals(b1.yUp - dist, b1.yDown + dist, b2.yUp - dist, b2.yDown + dist)) {
            if (checkIntervals(b1.zFront - dist, b1.zBack + dist, b2.zFront - dist, b2.zBack + dist)) {
                //collision
                bn1.collided = true;
                bn2.collided = true;

                return true;
            }
        }
    }

    return false;
}

/****************************************************************************************************/
/************************************COMPROBAR SAVE PLAYER*******************************************/
/****************************************************************************************************/
template <typename GameCTX_t>
constexpr bool ColissionSystem_t<GameCTX_t>::checkPlayerSave(BoundingBoxNode_t& saliente, BoundingBoxNode_t& player, const PhysicsComponent_t& salientephy, const PhysicsComponent_t& playerphy) const noexcept {
    auto saliente1 { moveToWorldCoords(saliente.box, salientephy.x + saliente.disX, salientephy.y + saliente.disY, salientephy.z) };
    auto player2   { moveToWorldCoords(player.box, playerphy.x + player.disX, playerphy.y + player.disY, playerphy.z) };

    auto checkIntervals { [](float L1, float R1, float L2, float R2) {
        if (L2 > R1) { return false; }
        if (L1 > R2) { return false; }

        return true;
    } };

    //E1  L1----R1                     L1----R1
    //E2           L2----R2  L2----R2

    if (checkIntervals(saliente1.xLeft, saliente1.xRight, player2.xLeft, player2.xRight)) {
        if (player2.yUp < saliente1.yDown) {
            //Debajo del saliente
            return true;
        }
        else{
            return false;
        }
    }

    return false;
}

template<typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::checkIfPlayerSave(GameCTX_t& g) const noexcept{
    //auto& bb = g.template getSingletonComponent<BlackboardComponent_t>();
    auto& bb { g.template getBlackBoard() };
    auto* player { g.template getEntityByID(bb.playerID) };

    if (player) {
        auto* phyPlay { player->template getComponent<PhysicsComponent_t>() };
        auto* collPlay { player->template getComponent<ColliderComponent_t>() };

        if (phyPlay &&  collPlay) {

            for(std::size_t i {0}; i < static_cast<size_t>(bb.salientes_bb.size()); ++i){
                auto* phySal { bb.salientes_bb[i]->template getComponent<PhysicsComponent_t>() };
                auto* collSal { bb.salientes_bb[i]->template getComponent<ColliderComponent_t>() };
                if (!phySal || !collSal) { continue; }

                for (auto& boxPlay: collPlay->boxes) {
                    for (auto& boxSal: collSal->boxes) {
                        if(checkPlayerSave(boxSal, boxPlay, *phySal, *phyPlay)){
                            bb.player_is_save = true;
                            break;
                        }
                        else{
                            bb.player_is_save = false;
                        }
                    }
                }
            }
        }
    }
}


/****************************************************************************************************/
/*******************************COMPROBAR COLISION AGUJERO-TRAMPOLIN*********************************/
/****************************************************************************************************/

template <typename GameCTX_t>
int ColissionSystem_t<GameCTX_t>::checkAgujeros(GameCTX_t& g, int dist){
    for(auto& c1 : g.template getComponents<ColliderComponent_t>()) {
        if (c1.properties & ColliderComponent_t::P_IsPlayer) {
            auto* phy { g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(c1) };

            for(auto& c2 : g.template getComponents<ColliderComponent_t>()) {
                if ((c2.properties == ColliderComponent_t::P_Agujero) || (c2.properties == ColliderComponent_t::P_Trampolin)) {
                    auto* phy2 { g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(c2) };

                    for (auto& boxC1: c1.boxes) {
                        for (auto& boxC2: c2.boxes) {
                            if (checkObjectCercaCollision(dist, boxC1, boxC2, *phy, *phy2)) {
                                boxC1.collided = false;
                                boxC2.collided = false;

                                auto& bb { g.template getBlackBoard() };
                                bb.distxAgujero = phy2->x - phy->x;

                                if (bb.distxAgujero > 0) {
                                    bb.distxAgujero += 12;
                                } else {
                                    bb.distxAgujero -= 12;
                                }

                                bb.distyAgujero = phy2->y - phy->y;

                                if (bb.distyAgujero > 0) {
                                    bb.distyAgujero += 12;
                                } else {
                                    bb.distyAgujero -= 12;
                                }

                                switch (c2.quesubirbajar) {
                                    case 1:
                                        return 1;
                                    case 2:
                                        return 2;
                                    case 3:
                                        return 3;
                                }           
                            }
                        }
                    }
                }
            }

            continue;
        }
    }
    return 0;
}

/****************************************************************************************************/
/***************************************EFECTO COLISION NORMAL***************************************/
/****************************************************************************************************/

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::inflictDamage(GameCTX_t& g, ColliderComponent_t& inflicter, ColliderComponent_t& receiver) const noexcept {
    auto* reHe { g.template getRequiredComponent<ColliderComponent_t, HealthComponent_t>(receiver) };
    auto* inHe { g.template getRequiredComponent<ColliderComponent_t, HealthComponent_t>(inflicter) };
    if(!reHe) { return; }
    if(receiver.properties == ColliderComponent_t::P_Damages && receiver.destroyable){
        reHe->damage = 5;

        //std::cout<<"Roca se muere \n";
        return;
    }
    if (!inHe) { return; }
    if (reHe->hurtCooldown == 0){
        reHe->damage += inHe->damageInflicted;
        reHe->hurtCooldown = 240;

        if (receiver.properties & ColliderComponent_t::P_IsPlayer) {
            auto* rePhy { g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(receiver) };

            if (rePhy != nullptr) {
                rePhy->y -= 12;
            }

            auto& bb { g.template getBlackBoard() };

            if (bb.danyoplayer == false) {
                bb.danyoplayer = true;

                auto* sou { g.template getRequiredComponent<ColliderComponent_t, SoundComponent_t>(receiver) };

                if (sou != nullptr) {
                    std::string abuscar {""};
                    if (bb.volviPlanoNormal == true) {
                        abuscar = "event:/Personajes/Zacarias/Daño";
                    } else {
                        abuscar = "event:/Personajes/Zacarias Cueva/Daño";
                    }

                    auto encon { std::find(sou->my_events.begin(), sou->my_events.end(), abuscar) };

                    if (encon != sou->my_events.end()) {
                        sou->event_id = sou->my_events.at(encon - sou->my_events.begin());
                        sou->isEvent3D = false;
                        sou->marked_for_init = 1;
                        sou->marked_for_play = 1;
                    }
                }

                auto* ren { g.template getRequiredComponent<ColliderComponent_t, RenderComponent_t>(receiver) };  

                if(ren != nullptr && ren->entityNodes.node.node->getAnimation() != "danyo"){
                    ren->entityNodes.node.node->setFrame(0); 
                    ren->entityNodes.node.node->ActualizarAnimation("danyo");
                    ren->entityNodes.node.node->setFrame(0);
                }
            }            
        }
    }
    
    inHe->damage += inHe->selfDamageOnInfliction;

    if (inflicter.properties == ColliderComponent_t::P_Enemy) {
        auto* ia { g.template getRequiredComponent<ColliderComponent_t, IAComponent_t>(inflicter) };

        if (ia != nullptr) {
            if (ia->enemy == type_enemy::Cabra) {
                auto* souC { g.template getRequiredComponent<ColliderComponent_t, SoundComponent_t>(inflicter) };

                if (souC != nullptr) {
                    souC->event_id = "event:/Personajes/Cabra/GolpeCabra";
                    souC->marked_for_init = 1;
                    souC->marked_for_play = 1;
                    
                    ia->meGolpean = true;
                }
            }
        }
    }
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::puntoControl(GameCTX_t& g, ColliderComponent_t& mobile, ColliderComponent_t& solid,Motor3DLUM* motor) noexcept {
    auto control { solid.getEntityID() };

    auto& bb { g.template getBlackBoard() };

    if (bb.enCuerda == false) {

        //comprobar si estoy en el mismo enganche
        if (bb.contCuerda == 0 && bb.cuerdaID != solid.getEntityID()) {
            bb.enCuerda = true;
            bb.cuerdaID = solid.getEntityID(); 

            bb.timeCuerda = 1;
        } else {
            if (bb.cuerdaID != solid.getEntityID()) {
                bb.sigoCuerda = true;
            }
        }   
    } else {
        bb.sigoCuerda = false;
    }

    auto* ct { g.template getRequiredComponent<ColliderComponent_t, ControlComponent_t>(mobile) };
//    auto* est = g.template getRequiredComponent<ColliderComponent_t, StaminaComponent_t>(mobile);
//
//    if(est!=nullptr){
//        est->cantStamina = est->maxStamina;
//    }

    if (std::find(ct->puntosControl.begin(), ct->puntosControl.end(), control) == ct->puntosControl.end()) {
        ct->puntosControl.emplace_back(control);
    } else {
        ct->puntosControl.erase(std::find(ct->puntosControl.begin(), ct->puntosControl.end(), control));
        ct->puntosControl.emplace_back(control);
    }  
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::semilla(GameCTX_t& g, ColliderComponent_t& mobile, ColliderComponent_t& solid) const noexcept {
    auto* pun { g.template getRequiredComponent<ColliderComponent_t, PuntosComponent_t>(mobile) };
    auto* sta { g.template getRequiredComponent<ColliderComponent_t, StaminaComponent_t>(mobile) };

    if (pun != nullptr && sta != nullptr) {
        if (solid.colisionable == true) {
            auto* sou { g.template getRequiredComponent<ColliderComponent_t, SoundComponent_t>(solid) };
            if(sou != nullptr){
                sou->marked_for_play = 1;
            }

            pun->puntos += pun->cantSumable;

            sta->cantStamina = sta->cantStamina + 100;
            if(sta->cantStamina > sta->maxStamina){
                sta->cantStamina = sta->maxStamina;
            }
    
            solid.colisionable = false;
        }

        auto* he { g.template getRequiredComponent<ColliderComponent_t, HealthComponent_t>(solid) };

        if (!he) { return; }

        ++(he->damage);       
    }   
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::acelerar(GameCTX_t& g, ColliderComponent_t& mobile, ColliderComponent_t& solid) const noexcept {
    auto* moPhy { g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(mobile) };
    moPhy->pasomusgo = true;
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::decelerar(GameCTX_t& g, ColliderComponent_t& mobile, ColliderComponent_t& solid) const noexcept {
    auto* moPhy { g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(mobile) };
    moPhy->pasohielo = true;
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::undoCollision(GameCTX_t& g, ColliderComponent_t& mobile, ColliderComponent_t& solid, BoundingBoxNode_t& col1, BoundingBoxNode_t& col2) const noexcept {
    auto* moPhy { g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(mobile) };
    auto* soPhy { g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(solid) };

    if (!moPhy || !soPhy) { return; }

    //transladar a coordenadas de pantalla
    auto solidBox  { moveToWorldCoords(col2.box, soPhy->x + col2.disX, soPhy->y + col2.disY, soPhy->z) };
    auto mobileBox { moveToWorldCoords(col1.box, moPhy->x + col1.disX, moPhy->y + col1.disY, moPhy->z) };
    
    col1.collided = false;
    col2.collided = false;

    //        |---|  //Right
    //|---|          //Left
    //|-----------|  //Center
    //    |---|      //Center
    //   |-----|
    // xLeft  xRight

    //calcular interseccion
    auto intervalIntersection { [](float Ml, float Mr, float Sl, float Sr) -> float {
        if (Ml < Sl) {
            if (Mr < Sr) {
                //left
                return Sl - Mr;
            }
        } else if (Mr > Sr) {
            //right
            return Sr - Ml;
        }

        return 0;
    } };

    float undoX { intervalIntersection (mobileBox.xLeft, mobileBox.xRight, solidBox.xLeft, solidBox.xRight) };
    float undoY { intervalIntersection (mobileBox.yUp, mobileBox.yDown, solidBox.yUp, solidBox.yDown) };
    float undoZ { intervalIntersection (mobileBox.zFront, mobileBox.zBack, solidBox.zFront, solidBox.zBack) };

    auto& bb { g.template getBlackBoard() };

    if (mobile.properties == ColliderComponent_t::P_IsPlayer 
        && (solid.properties == ColliderComponent_t::P_Saliente
        || solid.properties == ColliderComponent_t::P_PlanoS)) {

        if (undoX == 0 && undoY > 0) {
            //std::cout << "debo andar\n";
            //std::cout << "UndoX: " << undoX << " UndoY: " << undoY << "\n";

            auto* inp { g.template getRequiredComponent<ColliderComponent_t, InputComponent_t>(mobile) };

            if (inp != nullptr) {
                inp->xMinAndar = solidBox.xLeft;
                inp->xMaxAndar = solidBox.xRight;
            } 
            
            bb.andandoplayer = true;

            auto* ren { g.template getRequiredComponent<ColliderComponent_t, RenderComponent_t>(mobile) };  

            if(ren != nullptr && ren->entityNodes.node.node->getAnimation() != "caminarD"){
                ren->entityNodes.node.node->setFrame(0); 
                ren->entityNodes.node.node->ActualizarAnimation("caminarD");
                ren->entityNodes.node.node->setFrame(0);
            }
        } else {
            bb.andandoplayer = false;
        }
    }
    
    if (undoX == 0 || (undoY != 0 && std::abs(undoY) <= std::abs(undoX))) {
        moPhy->y += undoY+0.01;
        //moPhy->vy = 0;

        moPhy->vx *= (moPhy->friction * soPhy->friction);
    } else { //if (undoY == 0 || (std::abs(undoY) > std::abs(undoX)))
        moPhy->x += undoX+0.01;
        //moPhy->vx = 0;

        moPhy->vy *= (moPhy->friction * soPhy->friction);
    } 
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::changeCria(GameCTX_t& g, ColliderComponent_t& mobile, ColliderComponent_t& solid) noexcept {
    auto& bb { g.template getBlackBoard() };

    for (auto& fol : g.template getComponents<FollowComponent_t>()) {
        if (fol.followEntityID == solid.getEntityID()) {

            fol.followEntityID = mobile.getEntityID();
            fol.x = fol.x;
            fol.y = 0;
            fol.z = fol.z;
            fol.meCogioPlayer = true;

            bb.criasrescatadas.at(fol.numcria) = true;

            setCrias(g);

            auto* sound { g.template getRequiredComponent<FollowComponent_t, SoundComponent_t>(fol) };
            auto* phy { g.template getRequiredComponent<FollowComponent_t, PhysicsComponent_t>(fol) };

            if(sound != nullptr && phy != nullptr){
                if (sound->event_id_ant == "") {
                    sound->event_id_ant = sound->event_id;
                }
                
                if (phy->zida == 0) {
                    sound->event_id = "event:/Personajes/Crias/CriaRescatada";
                } else {
                    sound->event_id = "event:/Personajes/Crias Cueva/CriaRescatada";
                }

                sound->isEvent3D = false;
                sound->isEventParameter = true;
                sound->alwaysPlay = false;
                sound->marked_for_init = 1;
                sound->marked_for_play = 1;
            }
        }
    } 
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::sumarCascada(GameCTX_t& g, ColliderComponent_t& mobile) const noexcept {
    auto* sta { g.template getRequiredComponent<ColliderComponent_t, StaminaComponent_t>(mobile) };

    if (sta != nullptr) {
        sta->cantStamina = sta->maxStamina;
    } 
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::sumarVida(GameCTX_t& g, ColliderComponent_t& mobile) const noexcept {
    auto* plaHe { g.template getRequiredComponent<ColliderComponent_t, HealthComponent_t>(mobile) };

    if (plaHe != nullptr) {
        if (plaHe->vidasumada == false && plaHe->health < 3) {
            plaHe->sumarvida = true;
        }
    }
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::campoVision(GameCTX_t& g, ColliderComponent_t& player, ColliderComponent_t& other) const noexcept {
    auto& bb { g.template getBlackBoard() };
    auto* phy { g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(player) };

    if (phy != nullptr) {
        auto* ia { g.template getRequiredComponent<ColliderComponent_t, IAComponent_t>(other) };

        if (ia != nullptr) {
            ia->visto = true;

            bb.player_tx = phy->x;
            bb.player_ty = phy->y;
        }    
    }    
}

/****************************************************************************************************/
/***********************************ELEGIR EFECTO COLISION NORMAL************************************/
/****************************************************************************************************/

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::react2collision(GameCTX_t& g, ColliderComponent_t& c1, ColliderComponent_t& c2, BoundingBoxNode_t& col1, BoundingBoxNode_t& col2,Motor3DLUM* motor) noexcept {
    using CP = ColliderComponent_t;
    CP *player { &c1 }, *other { &c2 };

    bool isPlayer1 {true};

    if (c2.properties & CP::P_IsPlayer) {
        std::swap(player, other);
        isPlayer1 = false;
    } else if (!(c1.properties & CP::P_IsPlayer)) {
        // Miro a ver si alguno es ia para llamar a su comprobacion de colisiones
        if(c1.properties == CP::P_Enemy || c2.properties == CP::P_Enemy){
            react2collision_ia(g, c1, c2, col1, col2);
            return;
        }else{
            if(c1.properties == CP::P_Damages || c2.properties == CP::P_Damages ){
                react2collision_roca(g, c1, c2, col1, col2);
                return;
            }
            else{
                if (c1.properties == CP::P_Semilla) {
                    col1.collided = false;
                    col2.collided = false;
                    return;
                } else {
                    col1.collided = false;
                    col2.collided = false;
                    return;
                }  
            }
            
        }       
    }

    switch(other->properties) {
        case CP::P_Damages:
            //daño
            inflictDamage(g, *other, *player);
            col1.collided = false;
            col2.collided = false;
            break;

        case CP::P_EnemyVisual:
            //undoCollision(g, *player, *other);
            campoVision(g, *player, *other); 

            col1.collided = false;
            col2.collided = false; 
            
            break;

        case CP::P_Enemy:
            //daño
            inflictDamage(g, *other, *player);

            col1.collided = false;
            col2.collided = false;
            break;
        
        case CP::P_Agujero:
//            if (isPlayer1 == true) {
//                undoCollision(g, *player, *other, col1, col2);
//            } else {
//                undoCollision(g, *player, *other, col2, col1);
//            } 
            col1.collided = false;
            col2.collided = false;
            break;

        case CP::P_Trampolin:
            if (isPlayer1 == true) {
                undoCollision(g, *player, *other, col1, col2);
            } else {
                undoCollision(g, *player, *other, col2, col1);
            } 
            break;

        case CP::P_PlanoS:
            if (isPlayer1 == true) {
                undoCollision(g, *player, *other, col1, col2);
            } else {
                undoCollision(g, *player, *other, col2, col1);
            } 
            break;

        case CP::P_Saliente:
            if (isPlayer1 == true) {
                undoCollision(g, *player, *other, col1, col2);
            } else {
                undoCollision(g, *player, *other, col2, col1);
            } 
            break;

        case CP::P_IsSolid:
            if (isPlayer1 == true) {
                undoCollision(g, *player, *other, col1, col2);
            } else {
                undoCollision(g, *player, *other, col2, col1);
            } 
            break;

        case CP::P_Control:
            puntoControl(g, *player, *other, motor);

            col1.collided = false;
            col2.collided = false;
            break;

        case CP::P_Semilla:
            semilla(g, *player, *other);

            col1.collided = false;
            col2.collided = false;
            break;

        case CP::P_Nido:
            changeCria(g, *player, *other);

            col1.collided = false;
            col2.collided = false;
            break;

        case CP::P_Cria:
            col1.collided = false;
            col2.collided = false;
            break;

        case CP::P_Cascada:
            sumarCascada(g, *player);

            col1.collided = false;
            col2.collided = false;   
            break;

        case CP::P_Arbusto:
            sumarVida(g, *player);

            col1.collided = false;
            col2.collided = false;
            break;

        case CP::P_Accelerate:
            acelerar(g, *player, *other);

            col1.collided = false;
            col2.collided = false;
            break;

        case CP::P_Deccelerate:
            decelerar(g, *player, *other);

            col1.collided = false;
            col2.collided = false;
            break;

        case CP::P_Telaranya:
            inflictDamage(g, *other, *player);

            col1.collided = false;
            col2.collided = false;
            break;

        case CP::P_Palo:
            inflictDamage(g, *other, *player);

            col1.collided = false;
            col2.collided = false;
            break;

        case CP::P_Meta:
            if (isPlayer1 == true) {
                undoCollision(g, *player, *other, col1, col2);
            } else {
                undoCollision(g, *player, *other, col2, col1);
            } 
            setMeta(g, true);
            break;

        case CP::P_Arrow:
            if (isPlayer1 == true) {
                undoCollision(g, *player, *other, col1, col2);
            } else {
                undoCollision(g, *player, *other, col2, col1);
            } 
            col1.collided = false;
            col2.collided = false;
            break;

        case CP::P_spPalos:
            if (isPlayer1 == true) {
                undoCollision(g, *player, *other, col1, col2);
            } else {
                undoCollision(g, *player, *other, col2, col1);
            } 
            break;
    }
}

template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::react2collision_ia(GameCTX_t& g, ColliderComponent_t& c1, ColliderComponent_t& c2, BoundingBoxNode_t& col1, BoundingBoxNode_t& col2) noexcept {
    using CP = ColliderComponent_t;
    CP *enemy { &c1 }, *other { &c2 };

    bool isEnemy1 {true};

    if (c2.properties == CP::P_Enemy) {
        std::swap(enemy, other);
        isEnemy1 = false;
    } else if (!(c1.properties == CP::P_Enemy)) {
        
        return;
    }

    switch (other->properties) {
        case CP::P_Saliente:
//        if(ia->enemy==type_enemy::Cabra){
//
//            undoCollision_y(g, *enemy, *other);
//        }else{
            if (isEnemy1 == true) {
                auto * ia{g.template getRequiredComponent<ColliderComponent_t, IAComponent_t>(c1)};
                if(ia!=nullptr && ia->enemy!=type_enemy::Aguila){
                    undoCollision(g, *enemy, *other, col1, col2);
                }
            } else {
                auto * ia{g.template getRequiredComponent<ColliderComponent_t, IAComponent_t>(c2)};
                if(ia!=nullptr && ia->enemy!=type_enemy::Aguila){
                    undoCollision(g, *enemy, *other, col2, col1);
                }
                
            } 
//        }
            break;

        case CP::P_Telaranya:
            col1.collided = false;
            col2.collided = false;
            break;

        case CP::P_Semilla:
            col1.collided = false;
            col2.collided = false;
            break;

        case CP::P_Damages:
            col1.collided = false;
            col2.collided = false;
            break;

        case CP::P_PlanoS:
            if (isEnemy1 == true) {
                undoCollision(g, *enemy, *other, col1, col2);
            } else {
                undoCollision(g, *enemy, *other, col2, col1);
            } 
            break;
    }
}





template <typename GameCTX_t>
constexpr void ColissionSystem_t<GameCTX_t>::react2collision_roca(GameCTX_t& g, ColliderComponent_t& c1, ColliderComponent_t& c2, BoundingBoxNode_t& col1, BoundingBoxNode_t& col2) noexcept {
    using CP = ColliderComponent_t;
    CP *roca { &c1 }, *other { &c2 };


    if (c2.properties == CP::P_Damages) {
        std::swap(roca, other);
    } else if (!(c1.properties == CP::P_Damages)) {
        return;
    }

    if (roca->destroyable == true) {
        auto* sou { g.template getRequiredComponent<ColliderComponent_t, SoundComponent_t>(*roca) };
        if(sou != nullptr){
            sou->marked_for_play = 1;
        }
    }

    switch (other->properties) {
        case CP::P_Saliente:
            inflictDamage(g, *other, *roca);
            col1.collided = false;
            col2.collided = false;
            break;

        case CP::P_Enemy:
            col1.collided = false;
            col2.collided = false;
            break;

        default:
            col1.collided = false;
            col2.collided = false;
            break;
    
    }
}




template <typename GameCTX_t>
bool ColissionSystem_t<GameCTX_t>::update(GameCTX_t& g,Motor3DLUM* motor) {
    auto& colVeccmp { g.template getComponents<ColliderComponent_t>() };

    //auto& bb = g.template getSingletonComponent<BlackboardComponent_t>();
    auto& bb { g.template getBlackBoard() };
    bb.player_tx = 0;
    bb.player_ty = 0;    

    checkIfPlayerSave(g);

    std::function<void(BoundingBoxNode_t&)> collidersFalse { [&](BoundingBoxNode_t& b) {
        b.collided = false;
    } };

    for (auto& c : colVeccmp) {
        for (auto& box: c.boxes) {
            collidersFalse(box);
        }
    }

    for(std::size_t i {0}; i < static_cast<size_t>(colVeccmp.size()); ++i){
        auto& c1 { colVeccmp[i] };

        //getRequiredComponent devuelve un componente a partir de otro
        auto* phy { g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(c1) };

        if (!phy) { continue; }

        //limites con el mapa
        checkMapColision(g, c1, *phy); 

        //colisiones entre cosas
        for (std::size_t j {i+1}; j < static_cast<size_t>(colVeccmp.size()); ++j) {
            auto& c2 { colVeccmp[j] };

            auto* phy2 { g.template getRequiredComponent<ColliderComponent_t, PhysicsComponent_t>(c2) };

            if (!phy2) { continue; }
                
            RenderComponent_t* r1 { g.template getRequiredComponent<ColliderComponent_t, RenderComponent_t>(c1) };
            RenderComponent_t* r2  { g.template getRequiredComponent<ColliderComponent_t, RenderComponent_t>(c2) };
            bool colisionado { false };
            for (auto& boxC1: c1.boxes) {
                for (auto& boxC2: c2.boxes) {
                    if (!(c1.nomover == false || c2.nomover == false)) {
                        if (checkObjectCercaCollision(0, boxC1, boxC2, *phy, *phy2)) {
                            react2collision(g, c1, c2, boxC1, boxC2, motor);
                            if (c1.properties & ColliderComponent_t::P_IsPlayer)
                            {
                                r1->entityNodes.collides = true;
                            }
                            else if (c2.properties & ColliderComponent_t::P_IsPlayer)
                            {
                                r2->entityNodes.collides = true;
                            }

                            //solo las rocas pueden ser no destruibles asi que no hace falta la comprobacion de antes
                            if(c1.destroyable==false || c2.destroyable==false){
                                colisionado = true;
                            }
                        } 
                    }
                }
            } 

            if(!colisionado){
                // esta parte es por si acaso pero siempre se hace el otro if
                if(c1.properties == ColliderComponent_t::P_Damages && c1.destroyable==false){
                                
                    if(c2.properties == ColliderComponent_t::P_Saliente && c2.getEntityID() == c1.mySal){
                        ///std::cout<<"Soy roca 1 y ya permito ser destruida \n";
                        c1.destroyable = true;
                    }
                }

                if((c2.properties == ColliderComponent_t::P_Damages) && (c2.destroyable==false)){
                                // mirar que se espere a mirar todos los boxes para decidir si colisiona con el saliente o no
                    if((c1.properties == ColliderComponent_t::P_Saliente) && (c1.getEntityID() == c2.mySal)){

                    //std::cout<<"saliente que comparo: "<<c1.getEntityID()<< " y saliente que tengo: "<<c2.mySal<<"\n";
                    //    std::cout<<"Soy roca 2  y ya permito ser destruida \n";
                        c2.destroyable = true;
                    }
                }

            }


        }
    }

    return true;
}  

template <typename GameCTX_t>
bool ColissionSystem_t<GameCTX_t>::getMeta(GameCTX_t& g) noexcept {
    return llegaMeta;
}


template <typename GameCTX_t>
void ColissionSystem_t<GameCTX_t>::setMeta(GameCTX_t& g, bool llegar) noexcept {    
    llegaMeta = llegar;
}

template <typename GameCTX_t>
int ColissionSystem_t<GameCTX_t>::getCrias(GameCTX_t& g) noexcept {
    return criasRescatadas;
}

template <typename GameCTX_t>
void ColissionSystem_t<GameCTX_t>::setCrias(GameCTX_t& g) noexcept {
    ++criasRescatadas;
}

template <typename GameCTX_t>
void ColissionSystem_t<GameCTX_t>::resetCrias(GameCTX_t& g) noexcept {
    criasRescatadas = 0;
}