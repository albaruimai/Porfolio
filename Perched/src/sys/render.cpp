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

#include "render.hpp"
    
template <typename GameCTX_t>
RenderSystem_t<GameCTX_t>::RenderSystem_t(uint32_t w, uint32_t h)
: m_w{ w }, m_h { h }
, motor{std::make_unique<Motor3DLUM>(m_w, m_h)}
{
    
};

template <typename GameCTX_t>
RenderSystem_t<GameCTX_t>::~RenderSystem_t() = default;

template <typename GameCTX_t>
void RenderSystem_t<GameCTX_t>::drawAllTexts(GameCTX_t& g) const {
    for (auto& hudcmp : g.template getComponents<HudComponent_t>())
    {
        for (auto& tx : hudcmp.textosHUD_) {
            motor.get()->getCreatorText()->draw(tx.texto, tx.x, tx.y, tx.scale, tx.color);
        }
    }
}

template <typename GameCTX_t>
void RenderSystem_t<GameCTX_t>::changeTextureIA(RenderComponent_t& ren, const char *path) const {
   // auto tex = std::unique_ptr<Texture>(motor->getTexture(path));
    //ren.entityNodes.node.node->setMaterialTexture(tex.get());
}

template <typename GameCTX_t>
void RenderSystem_t<GameCTX_t>::checkActionsIA(RenderComponent_t& ren, IAComponent_t& ia) const {
    if (ia.action_chosen != nullptr) {
        switch (ia.enemy) {
            case type_enemy::Aguila:
                //depuracion aguila
                if (ia.action_chosen->change_attack == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/aguila/atacar/pajaro-atacar.png");

                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/atacar/pajaro-atacar-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/atacar/pajaro-atacar-applyGoal.png");
                        break;
                        case BTState::check_see_player:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/atacar/pajaro-atacar-checkSeePlayer.png");
                        break;
                        case BTState::ACTseek:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/atacar/pajaro-atacar-actSeek.png");
                        break;
                        case BTState::reset_wait:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/atacar/pajaro-atacar-resetWait.png");
                        break;
                        case BTState::do_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/atacar/pajaro-atacar-doAct.png");
                        break;
                        case BTState::change_target_init:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/atacar/pajaro-atacar-changeTarget.png");
                        break;
                        case BTState::ACTarrive:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/atacar/pajaro-atacar-actArrive.png");
                        break;
                    }
                    break;
                }
                if (ia.action_chosen->change_eat == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/aguila/comer/pajaro-comer.png");

                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/comer/pajaro-comer-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/comer/pajaro-comer-applyGoal.png");
                        break;
                        case BTState::search_target:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/comer/pajaro-comer-searchTarget.png");
                        break;
                        case BTState::ACTarrive:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/comer/pajaro-comer-actArrive.png");
                        break;
                        case BTState::do_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/comer/pajaro-comer-doAct.png");
                        break;
                        case BTState::change_target_init:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/comer/pajaro-comer-changeTarget.png");
                        break;
                    }
                    break;
                }
                if (ia.action_chosen->change_make_nido == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/aguila/nidar/pajaro-nidar.png");
                    
                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/nidar/pajaro-nidar-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/nidar/pajaro-nidar-applyGoal.png");
                        break;
                        case BTState::change_target_init:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/nidar/pajaro-nidar-changeTarget.png");
                        break;
                        case BTState::ACTarrive:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/nidar/pajaro-nidar-actArrive.png");
                        break;
                    }
                    break;
                }
                if (ia.action_chosen->change_protect == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/aguila/proteger/pajaro-proteger.png");
                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/proteger/pajaro-proteger-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/proteger/pajaro-proteger-applyGoal.png");
                        break;
                        case BTState::change_target_init:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/proteger/pajaro-proteger-changeTarget.png");
                        break;
                        case BTState::do_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/proteger/pajaro-proteger-doAct.png");
                        break;
                        case BTState::ACTarrive:
                            changeTextureIA(ren, "assets/DepuracionIA/aguila/proteger/pajaro-proteger-actArrive.png");
                        break;
                    }
                    break;
                }
            break;
            case type_enemy::Aranya:
                //depuracion aranya
                if (ia.action_chosen->change_attack == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/aranya/atacar/aranya-atacar.png");

                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/atacar/aranya-atacar-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/atacar/aranya-atacar-applyGoal.png");
                        break;
                        case BTState::check_see_player:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/atacar/aranya-atacar-checkSeePlayer.png");
                        break;
                        case BTState::ACTseek:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/atacar/aranya-atacar-actSeek.png");
                        break;
                        case BTState::reset_wait:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/atacar/aranya-atacar-resetWait.png");
                        break;
                        case BTState::change_target_init:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/atacar/aranya-atacar-changeTarget.png");
                        break;
                        case BTState::ACTarrive:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/atacar/aranya-atacar-actArrive.png");
                        break;
                    }
                    break;
                }
                if (ia.action_chosen->change_eat == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/aranya/comer/aranya-comer.png");

                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/comer/aranya-comer-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/comer/aranya-comer-applyGoal.png");
                        break;
                        case BTState::check_see_player:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/comer/aranya-comer-checkSeePlayer.png");
                        break;
                        //case BTState::throw_object:
                        //    changeTextureIA(ren, "assets/DepuracionIA/aranya/comer/aranya-comer-throwObject.png");
                        //break;
                        case BTState::do_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/comer/aranya-comer-doAct.png");
                        break;
                        case BTState::change_target_init:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/comer/aranya-comer-changeTarget.png");
                        break;
                        case BTState::ACTarrive:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/comer/aranya-comer-actArrive.png");
                        break;
                    }
                    break;
                }
                if (ia.action_chosen->change_protect == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/aranya/proteger/aranya-proteger.png");

                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/proteger/aranya-proteger-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/proteger/aranya-proteger-applyGoal.png");
                        break;
                        case BTState::change_target_init:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/proteger/aranya-proteger-changeTarget.png");
                        break;
                        case BTState::do_action:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/proteger/aranya-proteger-doAct.png");
                        break;
                        case BTState::ACTarrive:
                            changeTextureIA(ren, "assets/DepuracionIA/aranya/proteger/aranya-proteger-actArrive.png");
                        break;
                    }
                    break;
                }
            break;
            case type_enemy::Cabra:
                //depuracion cabra
                if (ia.action_chosen->change_attack == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/cabra/atacar/cabra-atacar.png");

                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/atacar/cabra-atacar-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/atacar/cabra-atacar-applyGoal.png");
                        break;
                        case BTState::change_target_init:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/atacar/cabra-atacar-changeTarget.png");
                        break;
                        case BTState::ACTarrive:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/atacar/cabra-atacar-actArrive.png");
                        break;
                    }
                    break;
                }
                if (ia.action_chosen->change_eat == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/cabra/comer/cabra-comer.png");

                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/comer/cabra-comer-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/comer/cabra-comer-applyGoal.png");
                        break;
                        case BTState::do_action:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/comer/cabra-comer-doAct.png");
                        break;
                    }
                    break;
                }
                if (ia.action_chosen->change_protect == -10) {
                    changeTextureIA(ren, "assets/DepuracionIA/cabra/proteger/cabra-proteger.png");

                    switch (ia.estadoIA) {
                        case BTState::check_action:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/proteger/cabra-proteger-checkAct.png");
                        break;
                        case BTState::applygoal:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/proteger/cabra-proteger-applyGoal.png");
                        break;
                        case BTState::check_see_player:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/proteger/cabra-proteger-checkSeePlayer.png");
                        break;
                        case BTState::seek_one_axis:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/proteger/cabra-proteger-seekOneAxis.png");
                        break;
                        case BTState::reset_wait:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/proteger/cabra-proteger-resetWait.png");
                        break;
                        case BTState::change_target_init:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/proteger/cabra-proteger-changeTarget.png");
                        break;
                        case BTState::ACTarrive:
                            changeTextureIA(ren, "assets/DepuracionIA/cabra/proteger/cabra-proteger-actArrive.png");
                        break;
                    }
                    break;
                }
            break;
        }
    }
}

template <typename GameCTX_t>
void RenderSystem_t<GameCTX_t>::drawAllEntities(GameCTX_t& g) const {
    //Con referencia (&) no usamos una copia usamos el array original
    auto& rencmps { g.template getComponents<RenderComponent_t>() };
    int last_fps{0};
    float x,y,z;
    
    std::for_each(begin(rencmps), end(rencmps), [&](auto& rc) {
        //getRequiredComponent devuelve un componente a partir de otro
        auto* phy { g.template getRequiredComponent<RenderComponent_t, PhysicsComponent_t>(rc) };

        if (phy != nullptr) {
            if(rc.entityNodes.node.node != nullptr){
                rc.entityNodes.node.node->setPosition(Vector3d(phy->x, phy->y, phy->z));
                rc.entityNodes.node.node->setRotation(Vector3d(phy->rotx, phy->roty, phy->rotz));

                /*cambia de color al personaje a verde cuando colisiona con algo*/
                auto* cc { g.template getRequiredComponent<RenderComponent_t, ColliderComponent_t>(rc) };

                if (cc->properties & ColliderComponent_t::P_IsPlayer)
                {
                    if (rc.entityNodes.collides)
                    {
                      //  auto verde   = std::unique_ptr<Texture>(motor->getTexture("assets/textures/green.png"));
                      //  rc.entityNodes.node.node->setMaterialTexture(verde.get());
                        rc.entityNodes.collides = false;
                    }
                    else
                    {
                      //  auto blanco  = std::unique_ptr<Texture>(motor->getTexture("assets/textures/cuadroblanco.jpg"));
                       // rc.entityNodes.node.node->setMaterialTexture(blanco.get());
                    }
                }

                if (cc->properties == ColliderComponent_t::P_Enemy) {
                    //depuracion IA
                    auto* ia { g.template getRequiredComponent<RenderComponent_t, IAComponent_t>(rc) };

                    if (ia != nullptr) {
                        checkActionsIA(rc, *ia);
                    }
                }
                
                if (!rc.entityNodes.childs.empty()) {
                    for (size_t i {0}; i < static_cast<size_t>(rc.entityNodes.childs.size()); ++i) {
                        rc.entityNodes.childs.at(i).node->setRotation(Vector3d(phy->rotx, phy->roty, phy->rotz));

                        rc.entityNodes.childs.at(i).node->setPosition(Vector3d(rc.entityNodes.childs.at(i).x, rc.entityNodes.childs.at(i).y, rc.entityNodes.childs.at(i).z));
                    }        
                }
            }
        }               
    });
   
    motor->drawAll();

}

template <typename GameCTX_t>
bool RenderSystem_t<GameCTX_t>::update(GameCTX_t& g){
    auto start {std::chrono::system_clock::now()};
    auto m { motor.get() };
    if (m!=nullptr)
    {
        m->beginScene();
     
        auto& blackboard { g.template getBlackBoard() };
    
        if(blackboard.volviPlanoNormal == false){
            m->nubes=false;
            m->particulas=false;
            m->disableParticleSys();

            tunel(g);
        } else {
            if (m->Menunubes == true && m->Menuparticulas == true) {
                m->nubes=true;
                m->particulas=true;
                m->enableParticleSys();
            }

            switch (blackboard.levelAct) {
                case 0:
                    dia(g);
                    break;
                case 1:
                    dia(g);
                    break;
                case 2:
                    atardecer(g);
                    break;
                case 3:
                    atardecer(g);
                    break;
                case 4:
                    noche(g);
                    break;
                case 5:
                    noche(g);
                    break;
                case 6:
                    atardecer(g);
                    break;
                case 7:
                    atardecer(g);
                    break;
                case 8:
                    dia(g);
                    break;
                case 9:
                    dia(g);
                    break;
            }
        }   
        drawAllEntities(g);

        drawAllTexts(g);
        //std::cout<<"fps_"<<m->getFPS()<<"\n";
        m->endScene();
        auto end {std::chrono::system_clock::now()};
        std::chrono::duration<float,std::milli> duration { end - start };
        //std::cout << "Render time: " << duration.count() << " ms\n";
        return m->run();
    }
    else
    {
        return false;
    }
    
}



template <typename GameCTX_t>
void RenderSystem_t<GameCTX_t>::dia(GameCTX_t& g){
    motor.get()->light->setPosition(Vector3d(0.0f, 1600.0f, 1000.0f));
    li = static_cast<LightLUM*>( motor.get()->light->getEntity());
    luzLevel = Vector3d(1, 1, 1);
    li->setlightColor(luzLevel);
    motor.get()->cambiociclo = 0;
}


template <typename GameCTX_t>
void RenderSystem_t<GameCTX_t>::atardecer(GameCTX_t& g){
    motor.get()->light->setPosition(Vector3d(-800.0f, 0.0f, 1000.0f));
    li = static_cast<LightLUM*>( motor.get()->light->getEntity());
    luzLevel = Vector3d(1, 0.901, 0.580);
    li->setlightColor(luzLevel);
    motor.get()->cambiociclo = 2;
}


template <typename GameCTX_t>
void RenderSystem_t<GameCTX_t>::noche(GameCTX_t& g){
    li = static_cast<LightLUM*>( motor.get()->light->getEntity());

    luzLevel = Vector3d(0.560, 0.784, 1);
    li->setlightColor(luzLevel);
    motor.get()->cambiociclo=1;
}

template <typename GameCTX_t>
void RenderSystem_t<GameCTX_t>::tunel(GameCTX_t& g){
    li = static_cast<LightLUM*>( motor.get()->light->getEntity());

    luzLevel = Vector3d(0.560, 0.784, 1);
    li->setlightColor(luzLevel);
    motor.get()->cambiociclo=1;    
}