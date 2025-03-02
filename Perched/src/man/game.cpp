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

#include "game.hpp"

// auto&& deduce referencia a rvalue o a lvalue
auto timedCall { [](std::string_view name, auto &&func)
{
    GameTimer_t timerc;
    func();
    //std::cout << "[" << name << "]" << timerc.ellapsed() << " ";
} };

void GameManager_t::createActionsIA()
{

    // Acciones del Aguila, valores(tipo, atacar, comer, hacer nido, proteger ):
    // Atacar
    action_container.emplace_back(Action_t(type_enemy::Aguila, -10, 3, 1, 2));
    // Comer
    action_container.emplace_back(Action_t(type_enemy::Aguila, 6, -10, 2, 1));
    // Hacer nido
    action_container.emplace_back(Action_t(type_enemy::Aguila, 6, 2, -10, 3));
    // Proteger
    action_container.emplace_back(Action_t(type_enemy::Aguila, 6, 2, 1, -10));

    // Acciones de la Cabra, valores(tipo, atacar, comer, hacer nido, proteger ):
    // Atacar
    action_container.emplace_back(Action_t(type_enemy::Cabra, -10, 4, 0, 2));
    // Comer
    action_container.emplace_back(Action_t(type_enemy::Cabra, 4, -10, 0, 2));
    // Proteger
    action_container.emplace_back(Action_t(type_enemy::Cabra, 4, 2, 0, -10));

    // Acciones de la Araña, valores(tipo, atacar, comer, hacer nido, proteger ):
    // Atacar
    action_container.emplace_back(Action_t(type_enemy::Aranya, -10, 4, 0, 2));
    // Comer
    action_container.emplace_back(Action_t(type_enemy::Aranya, 4, -10, 0, 2));
    // Proteger
    action_container.emplace_back(Action_t(type_enemy::Aranya, 4, 2, 0, -10));
}
void GameManager_t::createBT(BehaviourTree_t *tree)
{
    createActionsIA(); 
    tree->createNode<BTNodeSelector_t>(
        &tree->createNode<BTNodeSequence_t>(
            &tree->createNode<BTCheckType_t>(type_enemy::Cabra),
            &tree->createNode<BTChooseAction_t>(&action_container),
            &tree->createNode<BTNodeSelector_t>(
                // Rama Atacar
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Cabra, goal_types::Attack), // Atacar
                    &tree->createNode<BT_Apply_Goal_t>(),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 30.0),
                    &tree->createNode<BT_ACT_arrive_t>(),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>(),

                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 30.0),
                    &tree->createNode<BT_ACT_arrive_t>(),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>(),
                    
                    
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 30.0),
                    &tree->createNode<BT_ACT_arrive_t>(),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>(),
                    &tree->createNode<BT_Create_Terremoto_t>()
                    
                ),

                // Rama Comer
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Cabra, goal_types::Eat), // Comer
                    &tree->createNode<BT_Apply_Goal_t>(),
                    &tree->createNode<BT_Do_Action_t>(type_action::Comer, 5),
                    &tree->createNode<BT_Stop_t>(29)
                ),

                // Rama Proteger
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Cabra, goal_types::Protect), // Proteger
                    &tree->createNode<BT_Apply_Goal_t>(),
                    &tree->createNode<BTSearchTarget_t>(objects_type::Saliente),
                    &tree->createNode<BT_Check_See_Player_t>(),
                    &tree->createNode<BTSeekOneAxis_t>(),
                    &tree->createNode<BTResetWait_t>(),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>()
                )
            )
        ),

        &tree->createNode<BTNodeSequence_t>(
            &tree->createNode<BTCheckType_t>(type_enemy::Aranya),
            &tree->createNode<BTChooseAction_t>(&action_container),
            &tree->createNode<BTNodeSelector_t>(
                // Rama Atacar
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Aranya, goal_types::Attack), // Atacar
                    &tree->createNode<BT_Apply_Goal_t>(),
                    &tree->createNode<BT_Check_See_Player_t>(),
                    &tree->createNode<BT_ACT_seek_t>(),
                    &tree->createNode<BTResetWait_t>(),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>()),

                // Rama Comer
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Aranya, goal_types::Eat), // Comer
                    &tree->createNode<BT_Apply_Goal_t>(),
                    &tree->createNode<BT_Check_See_Player_t>(),
                    &tree->createNode<BTThrowObject_t>(objects_type::Telaranya),
                    &tree->createNode<BT_Do_Action_t>(type_action::Comer, 5)),

                // Rama Proteger
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Aranya, goal_types::Protect), // Proteger
                    &tree->createNode<BT_Apply_Goal_t>(),
                    // Change init para darle mas dinamismo al patrol

                    //&tree->createNode<BT_Change_Init_Prom_Pos_t>(),

                    &tree->createNode<BTNegateNode_t>(
                        &tree->createNode<BT_Check_See_Player_t>()
                    ),
                    &tree->createNode<BT_Change_Target_From_Init>(50.0, 0.0),
                    &tree->createNode<BT_Do_Action_t>(type_action::Vigilar, 5),
                    &tree->createNode<BT_ACT_arrive_t>(),


                    &tree->createNode<BTNegateNode_t>(
                        &tree->createNode<BT_Check_See_Player_t>()
                    ),
                    &tree->createNode<BT_Change_Target_From_Init>(50.0, -50.0),
                    &tree->createNode<BT_Do_Action_t>(type_action::Vigilar, 5),
                    &tree->createNode<BT_ACT_arrive_t>(),

                    &tree->createNode<BTNegateNode_t>(
                        &tree->createNode<BT_Check_See_Player_t>()
                    ),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, -50.0),
                    &tree->createNode<BT_Do_Action_t>(type_action::Vigilar, 5),
                    &tree->createNode<BT_ACT_arrive_t>(),

                    &tree->createNode<BTNegateNode_t>(
                        &tree->createNode<BT_Check_See_Player_t>()
                    ),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_Do_Action_t>(type_action::Vigilar, 5),
                    &tree->createNode<BT_ACT_arrive_t>()))),

        //        &tree->createNode<BTNodeSequence_t>(
        //            &tree->createNode<BTCheckType_t>(type_enemy::Aranya),
        //            &tree->createNode<BT_Check_See_Player_t>(),
        //            &tree->createNode<BT_ACT_seek_t>(),
        //            &tree->createNode<BTResetWait_t>(),
        //            &tree->createNode<BT_Change_Target_From_Init>(0.0 , -50.0),
        //            &tree->createNode<BT_ACT_arrive_t>()
        //            //&tree->createNode<BTThrowObject_t>(objects_type::Telaranya)
        //        ),
        &tree->createNode<BTNodeSequence_t>(
            &tree->createNode<BTCheckType_t>(type_enemy::Aguila),
            &tree->createNode<BTChooseAction_t>(&action_container),
            &tree->createNode<BTNodeSelector_t>(
                // Rama Atacar
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Aguila, goal_types::Attack), // Atacar
                    &tree->createNode<BT_Apply_Goal_t>(),
                    &tree->createNode<BT_Check_See_Player_t>(),
                    &tree->createNode<BT_ACT_seek_t>(),
                    &tree->createNode<BTResetWait_t>(),
                    &tree->createNode<BT_Do_Action_t>(type_action::Atacar, 2),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>()
                ),

                // Rama Comer
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Aguila, goal_types::Eat), // Comer
                    &tree->createNode<BT_Apply_Goal_t>(),
                    &tree->createNode<BTSearchTarget_t>(objects_type::Arbusto),
                    &tree->createNode<BT_ACT_arrive_t>(),
                    &tree->createNode<BT_Do_Action_t>(type_action::Comer, 5),
                    &tree->createNode<BT_Stop_t>(29),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>()
                ),

                // Rama Hacer_Nido
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Aguila, goal_types::Make_nido), // Hacer nido
                    &tree->createNode<BT_Apply_Goal_t>(),
                    &tree->createNode<BTSearchTarget_t>(objects_type::Palo),
                    &tree->createNode<BT_ACT_arrive_t>(),
                    &tree->createNode<BTThrowObject_t>(objects_type::Palo),
                    &tree->createNode<BTSearchTarget_t>(objects_type::Nido),
                    &tree->createNode<BT_ACT_arrive_t>(),
                    &tree->createNode<BTDropObject_t>(),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>()
                ),

                // Rama Proteger
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Aguila, goal_types::Protect), // Proteger
                    &tree->createNode<BT_Apply_Goal_t>(),
                    &tree->createNode<BT_Change_Target_To_Player>(),
                    &tree->createNode<BT_Change_Target_Relative>(-30.0, 20.0),
                    &tree->createNode<BT_ACT_arrive_t>(),
                    &tree->createNode<BT_Change_Target_Relative>(60.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>(),
                    &tree->createNode<BT_Change_Target_Relative>(-60.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>(),
                    &tree->createNode<BT_Change_Target_Relative>(60.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>(),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>()
                )
            )
        )
    );
}

void GameManager_t::clearHud() {
    //std::cout << "HE ENTRADO EN EL CLEAR HUD\n";
    for (auto& hud: EntityMan.getComponents<HudComponent_t>()) {
        //std::cout << "HE ENTRADO EN EL HUD\n";
        //for (size_t i {0}; i < hud.hearts_.size(); ++i) {
        //    hud.hearts_[i]->setAlpha(0.f);
        //}
        //for (size_t i {0}; i < hud.zaris_.size(); ++i) {
        //    hud.zaris_[i]->setAlpha(0.f);
        //}
        //hud.icon_stamina_->setAlpha(0.f);
        //hud.phdr_stamina_->setAlpha(0.f);
        //if (cartelnivel!=nullptr)
        //{
        //    cartelnivel->setAlpha(0.f);
        //}
        for (size_t i {0}; i < static_cast<size_t>(hud.hearts_.size()); ++i) {
            if (hud.hearts_[i]!=nullptr)
            {
                Render->getMotor()->removeSprite(hud.hearts_[i]);
                hud.hearts_[i] = nullptr; 
            }
        }
        for (size_t i {0}; i < static_cast<size_t>(hud.zaris_.size()); ++i) {
            if (hud.zaris_[i]!=nullptr)
            {
                Render->getMotor()->removeSprite(hud.zaris_[i]);
                hud.zaris_[i] = nullptr;
            }
        }
        if (hud.icon_bellotas_!=nullptr)
        {
            Render->getMotor()->removeSprite(hud.icon_bellotas_);
            hud.icon_bellotas_ = nullptr;
        }
        if (hud.icon_stamina_!=nullptr)
        {
            Render->getMotor()->removeSprite(hud.icon_stamina_);
            hud.icon_stamina_  = nullptr;
        }
        if (hud.phdr_stamina_!=nullptr)
        {
            Render->getMotor()->removeSprite(hud.phdr_stamina_);
            hud.phdr_stamina_  = nullptr;
        }
        if (cartelnivel!=nullptr)
        {
            Render->getMotor()->removeSprite(cartelnivel);
            cartelnivel = nullptr;
        }
    }
}

void GameManager_t::finishSoundGame() {
    Sound->stop("event:/Efectos/Naturaleza/Naturaleza");
    Sound->stop("event:/Musica/Juego/MusicaJuego");
    Sound->update(EntityMan);
}

void GameManager_t::resetAll() {
    BlackBoard.quitarColisiones(EntityMan);

    Sound->stop("event:/Efectos/Naturaleza/Naturaleza");
    Sound->stop("event:/Musica/Juego/MusicaJuego");

    for (auto& sou: EntityMan.getComponents<SoundComponent_t>()) {
        Sound->stop(sou.event_id);
    }

    clearHud();

    Render->getMotor()->removeSprite(teclaE);
    teclaE = nullptr;
    borradaE = false;

    for (size_t i {0}; i < static_cast<size_t>(EntityMan.getEntities().size()); ++i) {   
        if (EntityMan.getEntities().at(i).getComponent<CameraComponent_t>() == nullptr) {
            EntityMan.destroyEntityByID(EntityMan.getEntities().at(i).getEntityID());
        }   
    }

    for (size_t i {EntityMan.getComponents<PhysicsComponent_t>().size() - 1}; i>0; --i) {   
        if (EntityMan.getRequiredComponent<PhysicsComponent_t, CameraComponent_t>(EntityMan.getComponents<PhysicsComponent_t>().at(i)) == nullptr) {
            EntityMan.getComponents<PhysicsComponent_t>().erase(EntityMan.getComponents<PhysicsComponent_t>().begin() + i);
        }
    }


    EntityMan.getComponents<ColliderComponent_t>().clear();
    EntityMan.getComponents<ControlComponent_t>().clear();
    EntityMan.getComponents<FollowComponent_t>().clear();
    EntityMan.getComponents<HealthComponent_t>().clear();
    EntityMan.getComponents<IAComponent_t>().clear();
    EntityMan.getComponents<InputComponent_t>().clear();
    EntityMan.getComponents<PuntosComponent_t>().clear();
    EntityMan.getComponents<RenderComponent_t>().clear();
    EntityMan.getComponents<SoundComponent_t>().clear();
    EntityMan.getComponents<StaminaComponent_t>().clear();
    EntityMan.getComponents<HudComponent_t>().clear();

    for (size_t i {EntityMan.getEntities().size() - 1}; i>0; --i) {   
        if (EntityMan.getEntities().at(i).getComponent<CameraComponent_t>() == nullptr) {
            EntityMan.getEntities().erase(EntityMan.getEntities().begin() + i);
        }
    }

    using TextureIt = std::unordered_map<std::string, TextureLUM>::iterator;
    std::vector<std::string> nombres;

    for (TextureIt it { Render->getMotor()->getTMan()->texs3D_.begin() }; it != Render->getMotor()->getTMan()->texs3D_.end(); ++it)
    {
        if (it->first.find("sali") != std::string::npos)
        {
            nombres.push_back(it->first);
        }
    }

    for (size_t i {0}; i < nombres.size(); ++i)
    {
        Render->getMotor()->getTMan()->texs3D_.erase(nombres[i]);
    }
    
    //std::cout << "Size: " << EntityMan.getEntities().size() << "\n";
    
    Render->getMotor()->clearNodes();

    auto& bb { EntityMan.getBlackBoard() };
    bb.criasrescatadas.clear();
    bb.cuerdaID = 0;
}

void GameManager_t::ponerTeclaE() {
    cercaAgujero = Collision.checkAgujeros(EntityMan, 12);
    if (cercaAgujero != 0) {
        if (borradaE == true) {
            auto& bb { EntityMan.getBlackBoard() };

            teclaE = Render->getMotor()->create2dSprite("assets/teclaE.png", {(wWidth/2)-bb.distxAgujero, (wHeight/2)-bb.distyAgujero}, {30,30});
            borradaE = false;
        }            
    } else {
        Render->getMotor()->removeSprite(teclaE);
        teclaE = nullptr;
        borradaE = true;
    }
}


void GameManager_t::ponerTuto() {
    auto& bb { EntityMan.getBlackBoard() };
    if(bb.ponTuto){
        if(borradaTuto && tuto == nullptr){
            if(bb.queTuto == 1){tuto = Render->getMotor()->create2dSprite("assets/tutorial/1.png", {(wWidth/2)-400, (3 * wHeight/4) -100}, {250,150});}
            if(bb.queTuto == 2){tuto = Render->getMotor()->create2dSprite("assets/tutorial/2.png", {(wWidth/2)+300, (wHeight/2) -100}, {250,150});}
            if(bb.queTuto == 3){tuto = Render->getMotor()->create2dSprite("assets/tutorial/3.png", {(wWidth/2)-400, (wHeight/2) -100}, {250,150});}
            if(bb.queTuto == 4){tuto = Render->getMotor()->create2dSprite("assets/tutorial/4.png", {(wWidth/2)+300, (wHeight/2) -100}, {250,150});}
            if(bb.queTuto == 5){tuto = Render->getMotor()->create2dSprite("assets/tutorial/5.png", {(wWidth/2)+100, (wHeight/2) -100}, {250,150});}
            if(bb.queTuto == 6){tuto = Render->getMotor()->create2dSprite("assets/tutorial/6.png", {(wWidth/2)-450, (3 * wHeight/4) -100}, {250,150});}
            if(bb.queTuto == 7){tuto = Render->getMotor()->create2dSprite("assets/tutorial/7.png", {(wWidth/2)+300, (wHeight/2) -100}, {250,150});}
            if(bb.queTuto == 8){tuto = Render->getMotor()->create2dSprite("assets/tutorial/8.png", {(wWidth/2)-400, (wHeight/2) -100}, {250,150});}

            borradaTuto = false;
        }
        
    }else{
        if(tuto!=nullptr){
            Render->getMotor()->removeSprite(tuto);
            tuto = nullptr;
            borradaTuto = true;
        }
    }
}

void GameManager_t::animWin() {
    auto& bb { EntityMan.getBlackBoard() };
    auto* player { EntityMan.getEntityByID(bb.playerID) };

    if (player != nullptr) {
        auto* ren { player->template getComponent<RenderComponent_t>() };
        auto* phy { player->template getComponent<PhysicsComponent_t>() };

        if (phy != nullptr && ren != nullptr) {
            phy->y = phy->y - 12;
            phy->vx = 0;
            phy->vy = 0;
            Physics.update(EntityMan);

            auto* sou { player->template getComponent<SoundComponent_t>() };

            if (sou != nullptr) {
                std::string abuscar {""};

                if (bb.volviPlanoNormal == true) {
                    abuscar = "event:/Personajes/Zacarias/AlegriaFinal";
                } else {
                    abuscar = "event:/Personajes/Zacarias Cueva/AlegriaFinal";
                }

                auto encon { std::find(sou->my_events.begin(), sou->my_events.end(), abuscar) };

                if (encon != sou->my_events.end()) {
                    sou->event_id = sou->my_events.at(encon - sou->my_events.begin());
                    sou->isEvent3D = false;
                    sou->marked_for_init = 1;
                    sou->marked_for_play = 1;

                    Sound->update(EntityMan);
                }
            }
            if(ren->entityNodes.node.node->getAnimation() != "saltoVictoria"){
                ren->entityNodes.node.node->setFrame(0); 
                ren->entityNodes.node.node->ActualizarAnimation("saltoVictoria");
            } else {
                ren->entityNodes.node.node->setFrame(0); 
            }

            while (ren->entityNodes.node.node->getActualFrame() < ren->entityNodes.node.node->getFinalFrame()) {
                if(fpsSalto!= Render->getMotor()->getFPS() && ren->entityNodes.node.node!=nullptr){
                    fpsSalto = Render->getMotor()->getFPS();

                    ren->entityNodes.node.node->ActualizarFrame(4);

                    for(auto& fol: EntityMan.getComponents<FollowComponent_t>()){
                        auto* entity { EntityMan.getEntityByID(fol.followEntityID) };

                        if (entity != nullptr && player == entity) {
                            auto* phyCria { EntityMan.getRequiredComponent<FollowComponent_t, PhysicsComponent_t>(fol) };

                            if (phyCria != nullptr) {
                                if (phyCria->contCria == 0) {
                                    switch(phyCria->posCria) {
                                        case 0:
                                            ++fol.y;
                                            phyCria->posCria = 1;
                                            break;
                                        case 1:
                                            ++fol.y;
                                            phyCria->posCria = 2;
                                            break;
                                        case 2:
                                            --fol.y;
                                            phyCria->posCria = 3;
                                            break;
                                        case 3:
                                            --fol.y;
                                            phyCria->posCria = 0;
                                            break;
                                    }

                                    phyCria->contCria = 1;
                                } else {
                                    ++(phyCria->contCria);

                                    if (phyCria->contCria == 10) {
                                        phyCria->contCria = 0;
                                    }
                                }
                            }
                        }
                    }

                    bool renderi { Render->update(EntityMan) };
                    Physics.update(EntityMan);
                    Follow.update(EntityMan);
                }
                else
                {
                    //std::cout<<" game.cpp 488 OJO QUE ESTO ES NULL\n";
                }
            }     
            ren->entityNodes.node.node->setFrame(0);     
        }
    }
}

void GameManager_t::animCavar() {
    auto& bb { EntityMan.getBlackBoard() };
    auto* player { EntityMan.getEntityByID(bb.playerID) };

    if (player != nullptr) {
        auto* ren { player->template getComponent<RenderComponent_t>() };

        if (ren != nullptr) {
            if(ren->entityNodes.node.node->getAnimation() != "cavar"){
                ren->entityNodes.node.node->setFrame(0); 
                ren->entityNodes.node.node->ActualizarAnimation("cavar");
            } else {
                ren->entityNodes.node.node->setFrame(0); 
            }

            while (ren->entityNodes.node.node->getActualFrame() < ren->entityNodes.node.node->getFinalFrame()) {
                if(fpsCavar!= Render->getMotor()->getFPS() && ren->entityNodes.node.node!=nullptr){
                    fpsCavar = Render->getMotor()->getFPS();

                    ren->entityNodes.node.node->ActualizarFrame(4);

                    bool renderi { Render->update(EntityMan) };
                }
            } 

            ren->entityNodes.node.node->setFrame(0);    
        }
    }
}

void GameManager_t::createNextLevel() {
    if (levelAct < SM.wasPassed.size()) {
        SM.wasPassed.at(levelAct) = true;
    }
    
    if (levelAct < numlevels) {
        SM.guardarPartida();
        
        createLevelX(levelAct+1);

        SM.lastLevelUnlocked = levelAct;

        EntityMan.getBlackBoard().levelAct = levelAct;

        ++levelAct;
    } else {

        levelAct = 0;
        EntityMan.getBlackBoard().levelAct = levelAct;
        m_playing = false;

        Sound->stop("event:/Musica/Juego/MusicaJuego");
        Sound->update(EntityMan);

        SM.addState<CreditsMenuState_t>(SM, *Render, *Sound, wWidth, wHeight, true);
    }
}

void GameManager_t::createThings() {
    Collision.sizeMapa(EntityMan);

    auto& bb { EntityMan.getBlackBoard() };
    GOFact.createHud();
    Physics.calculozinicio(EntityMan);
}

void GameManager_t::ponerPause() {
    auto& sounds { Sound->getSounds() };

    for (size_t i {0}; i < sounds.size(); ++i) {
        Sound->stop(sounds.at(i));
    }
    
    Sound->noreproducir = true;

    SM.volverSonidos = false;

    Sound->stop("event:/Efectos/Naturaleza/Naturaleza");
    Sound->stop("event:/Musica/Juego/MusicaJuego");

    Sound->update(EntityMan);

    if(teclaE!=nullptr){
        Render->getMotor()->removeSprite(teclaE);
        borradaE = true;
    }
    if(tuto!=nullptr){
        Render->getMotor()->removeSprite(tuto);
        borradaTuto = true;
    }

    finishSoundGame();
    clearHud();
    SM.addState<PauseMenuState_t>(SM, *Render, *Sound, wWidth, wHeight, &GOFact);
    //GOFact.createHud();
}

void GameManager_t::createCartel(int level) {
    rutaCartel = "assets/PerchedCards/Nivel";

    int y{0};

    if (cartelGrande == true) {
        rutaCartel += std::to_string(level);
        y = -10;
    } else {
        rutaCartel += std::to_string(level);
        rutaCartel += "p";
        y = 0;
    }

    rutaCartel += ".png";

    cartelnivel = Render->getMotor()->create2dSprite(rutaCartel, {xCartel,yCartel+y}, {wCartel,hCartel});
    contCartel = 1;
}

void GameManager_t::createLevelX(int level) {
    auto& blackboard { EntityMan.getBlackBoard() };
    //std::cout << "nivel " << level << " creandose\n";

    if (level == 1 || level == 2) {
        Sound->InitEvent("event:/Efectos/Naturaleza/Naturaleza", true);
        Sound->iniciar("event:/Efectos/Naturaleza/Naturaleza");
    } else {
        Sound->InitEvent("event:/Musica/Juego/MusicaJuego", true);
        Sound->iniciar("event:/Musica/Juego/MusicaJuego");
    }

    rutaLevel = "";

    rutaLevel += "assets/levels/Mundo1/level";
    rutaLevel += std::to_string(level);
    rutaLevel += ".json";
    GOFact.loadLevelJSON(rutaLevel, &tree1);
    
    if(Render->getMotor()->Menunubes==true) {
        GOFact.createNubes(168,-400,-200,EntityMan.getBlackBoard().playerID);
    }
   
    BlackBoard.ponerColisiones(EntityMan);
   
   
    createThings();

    createCartel(level);
}