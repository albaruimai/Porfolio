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

#include "physics.hpp"

template <typename GameCTX_t>
void PhysicsSystem_t<GameCTX_t>::physicsRoca(GameCTX_t& g, PhysicsComponent_t& phy, ColliderComponent_t& col) const {
    for(auto& phy1: g.template getComponents<PhysicsComponent_t>()){
        auto* col1 { g.template getRequiredComponent<PhysicsComponent_t, ColliderComponent_t>(phy1) };
        
        if (col1 != nullptr && col1->properties == ColliderComponent_t::P_IsPlayer) {
            float dist { static_cast<float>(sqrt(pow(phy.x - phy1.x, 2) + pow(phy.y - phy1.y, 2))) }; 

            /*crea una linea a la entidad con componente damages*/
            auto* rc { g.template getRequiredComponent<PhysicsComponent_t, RenderComponent_t>(phy) };
            //rc->entityNodes.ray = true;
            //rc->entityNodes.x = rc->entityNodes.node.node->getX();
            //rc->entityNodes.y = rc->entityNodes.node.node->getY();
            //rc->entityNodes.z = 15;
            //rc->entityNodes.rot = asin((phy.x+phy1.x)/dist)*180/PI;

            if (dist <= 1000) {
                if (col.nomover == true) {
                    phy.rotx += 20;

                    //gravedad
                    phy.vy -= phy.gravity/32;
                    phy.vy = std::clamp(phy.vy, phy.KminVy, phy.KmaxVy); //mantener valor en rango
                }
            } 
        }
    }
}

template <typename GameCTX_t>
void PhysicsSystem_t<GameCTX_t>::physicsPalo(GameCTX_t& g, PhysicsComponent_t& phy) const {
    //gravedad
    phy.vy -= phy.gravity;
    phy.vy = std::clamp(phy.vy, -2.0f, 2.0f); //mantener valor en rango
}

template <typename GameCTX_t>
void PhysicsSystem_t<GameCTX_t>::physicsIA(GameCTX_t& g, PhysicsComponent_t& phy) {
    auto* ia { g.template getRequiredComponent<PhysicsComponent_t, IAComponent_t>(phy) };

    if (ia != nullptr && (ia->estadoIA == BTState::change_target_init || ia->estadoIA == BTState::search_target) ) {
        //std::cout << "Inicio: " << phy.x << " " << phy.y << " Fin: " << ia->tx << " " << ia->ty << "\n";
        //std::cout << "InicioC: " << phy.x/20 << " " << phy.y/20 << " FinC: " << ia->tx/20 << " " << ia->ty/20 << "\n";

        Casilla ini;
        ini.x = phy.x / 12;
        ini.y = phy.y / 12;

        Casilla fin;
        fin.x = ia->tx / 12;
        fin.y = ia->ty / 12;

        if (std::abs(ini.x - fin.x) > 1 || std::abs(ini.y - fin.y) > 1) {

            auto& bb { g.template getBlackBoard() };

            if (ia->enemy == type_enemy::Aranya) {
                auto* player { g.template getEntityByID(bb.playerID) };

                if (player != nullptr) {
                    auto* phyP { player->template getComponent<PhysicsComponent_t>() };

                    if (phyP != nullptr) {
                        if (phy.z != phyP->z) {
                            return;
                        }
                    }
                }
            }         

            if (ia->enemy != type_enemy::Cabra) {

                PathP_t PathP{90, 40};

                std::vector<Casilla> ruta { PathP.buscar(ini.x, ini.y, fin.x, fin.y, phy.soyDeTunel, bb) };

                if (ruta.size() > 0)
                {
                    //std::cout << "encontrado\n";
                    ruta.push_back(fin);

                    ia->pathplaneo = true;
                    ia->ruta = ruta;
                } else {
                    if (ia->enemy == type_enemy::Aguila) {
                        PathA_t PathA{};
                        std::vector<Casilla> rutaA { PathA.aStar(ini, fin, bb.salientes_bb, bb.tunel_bb, phy.soyDeTunel) };

                        if (rutaA.size() > 0) {
                            rutaA.push_back(fin);

                            ia->pathplaneo = true;
                            ia->ruta = rutaA;
                        }
                    }
                }
            }
        }


    }

    phy.orientation += phy.v_angular;
    if (phy.orientation > 2*PI) phy.orientation -= 2*PI;
    if (phy.orientation < 0) phy.orientation += 2*PI;

    phy.vx = phy.v_linear * std::cos(phy.orientation);
    phy.vy = phy.v_linear * std::sin(phy.orientation);

    if (ia->apply_gravity) {
        switch (ia->enemy) {
            case type_enemy::Aguila:
                phy.vy = phy.vy - (std::abs(phy.vy)/4) ;
                break;

            case type_enemy::Cabra:
                phy.vy = (phy.vy - (std::abs(phy.Kgravity*2)))*2 ;
                break;
        }
    }
}



template <typename GameCTX_t>
void PhysicsSystem_t<GameCTX_t>::checkTuto(GameCTX_t& g, PhysicsComponent_t& phy) {
    auto& bb { g.template getBlackBoard() };

    bb.ponTuto = false;
    if(bb.levelAct==0){ // Tutorial nivel 1
        if(phy.y < 60){ // cansarse
            bb.ponTuto = true;
            bb.queTuto = 1;
        }

        if(phy.y < 120 && phy.y > 70){ // salientes
            bb.ponTuto = true;
            bb.queTuto = 2;
        }

        if(phy.y < 170 && phy.y > 130){ // avellanas
            bb.ponTuto = true;
            bb.queTuto = 3;
        }

        if(phy.y < 250 && phy.y > 190){ // crias
            bb.ponTuto = true;
            bb.queTuto = 4;
        }

        if(phy.y < 450 && phy.y > 350){ // bandera
            bb.ponTuto = true;
            bb.queTuto = 5;
        }
        
    }else{
        if(bb.levelAct==1){ // Tutorial nivel 2
            if(phy.y < 60){ // rocas
                bb.ponTuto = true;
                bb.queTuto = 6;
            }

            if(phy.y < 150 && phy.y > 70){ // arbustos
                bb.ponTuto = true;
                bb.queTuto = 7;
            }

            if(phy.y < 340 && phy.y > 250){ // enganches
                bb.ponTuto = true;
                bb.queTuto = 8;
            }
            
        }else{
            bb.ponTuto = false;
        }
        
    }
}



template <typename GameCTX_t>
void PhysicsSystem_t<GameCTX_t>::physicsCria(GameCTX_t& g, PhysicsComponent_t& phy) {
    auto* fol { g.template getRequiredComponent<PhysicsComponent_t, FollowComponent_t>(phy) };

    if (fol != nullptr && fol->meCogioPlayer == false) {
        if (phy.contCria == 0) {
            switch(phy.posCria) {
                case 0:
                    ++fol->y;
                    phy.posCria = 1;
                    break;
                case 1:
                    ++fol->y;
                    phy.posCria = 2;
                    break;
                case 2:
                    --fol->y;
                    phy.posCria = 3;
                    break;
                case 3:
                    --fol->y;
                    phy.posCria = 0;
                    break;
            }

            phy.contCria = 1;
        } else {
            ++(phy.contCria);

            if (phy.contCria == 10) {
                phy.contCria = 0;
            }
        }
    }
}

template <typename GameCTX_t>
bool PhysicsSystem_t<GameCTX_t>::update(GameCTX_t& g) {
    for(auto& phy: g.template getComponents<PhysicsComponent_t>()){
        auto* col { g.template getRequiredComponent<PhysicsComponent_t, ColliderComponent_t>(phy) };

        if (col != nullptr) {
            switch (col->properties) {
                case ColliderComponent_t::P_IsPlayer:
                    if (phy.timeTunel > 0) {
                        --phy.timeTunel;
                    } else {
                        phy.timeTunel = 0;
                    }

                    if (phy.volverplanonormal == true || phy.volverplanotunel == true) {
                        //restaurar planos
                        restaurarTunelporMuerte(g);
                    }

                    checkTuto(g, phy);
                    break;

                case ColliderComponent_t::P_Damages: //rocas
                    physicsRoca(g, phy, *col);
                    break;

                case ColliderComponent_t::P_Enemy:
                    physicsIA(g, phy);
                    break;

                case ColliderComponent_t::P_Palo:
                    physicsPalo(g, phy);
                    break;

                case ColliderComponent_t::P_Cria:
                    physicsCria(g, phy);
                    break;

                case ColliderComponent_t::P_Semilla:
                    phy.roty += 3;
                    break;

                default:
                    break;
            }
        }

        
        //aceleracion
        //phy.vx += phy.ax;
        //phy.vx = std::clamp(phy.vx, phy.KminVx, phy.KmaxVx);

        
        //Normaliar la diagonal
        if(phy.vx != 0 && phy.vy!=0){
            float c { static_cast<float>(sqrt(pow(phy.vx,2)+pow(phy.vy,2))) };

            phy.vx = phy.vx * abs(phy.vx / c);
            phy.vy = phy.vy * abs(phy.vy / c); 
        }

        
        //Actualizar posicion
        phy.last_x = phy.x;
        phy.last_y = phy.y;
        
        phy.x += phy.vx;
        phy.y += phy.vy;

    }

    return true;
}      


template <typename GameCTX_t>
int PhysicsSystem_t<GameCTX_t>::comprobarTunel(int quesubirbajar, GameCTX_t& g){
    int subobajo {0};

    auto& bb { g.template getBlackBoard() };

    if (tunel == 1){
        auto* player { g.template getEntityByID(bb.playerID) };

        if (player) {
            auto* phyPlay { player->template getComponent<PhysicsComponent_t>() };

            if (phyPlay != nullptr) {
                phyPlay->timeTunel = 80;
            }
        }

        if(cambioplano==0){
            bb.volviPlanoNormal = false;
            subobajo = 1;

            entrarTunel(quesubirbajar, g);
            cambioplano=1;
        }else if(cambioplano==1){
            bb.volviPlanoNormal = true;
            subobajo = 2;

            salirTunel(quesubirbajar, g);
            cambioplano=0;
        }            
        ++contTunel;
    } else {
        contTunel = 0;
    }    

    return subobajo;    
}

template <typename GameCTX_t>
void PhysicsSystem_t<GameCTX_t>::resetTunel(GameCTX_t& g) noexcept {
    tunel = 0;
}

template <typename GameCTX_t>
void PhysicsSystem_t<GameCTX_t>::addTunel(GameCTX_t& g) noexcept {
    ++tunel;
}

template <typename GameCTX_t>
void PhysicsSystem_t<GameCTX_t>::calculozinicio(GameCTX_t& g){
    for(auto& phy: g.template getComponents<PhysicsComponent_t>()){
        phy.zinicial = phy.z;
    }
}

template <typename GameCTX_t>
bool PhysicsSystem_t<GameCTX_t>::entrarTunel(int quesubirbajar, GameCTX_t& g) const{
    for(auto& phy: g.template getComponents<PhysicsComponent_t>()){
        phy.z = phy.zvuelta;
    }
    return true;
}

template <typename GameCTX_t>
bool PhysicsSystem_t<GameCTX_t>::salirTunel(int quesubirbajar, GameCTX_t& g) const{
    for(auto& phy: g.template getComponents<PhysicsComponent_t>()){
        phy.z = phy.zida;
    }
    return true;
}

template <typename GameCTX_t>
bool PhysicsSystem_t<GameCTX_t>::restaurarTunelporMuerte(GameCTX_t& g) {
    for(auto& phy: g.template getComponents<PhysicsComponent_t>()){

        auto* col { g.template getRequiredComponent<PhysicsComponent_t,ColliderComponent_t>(phy) };

        if(col!=nullptr){
            if (col->properties == ColliderComponent_t::P_IsPlayer) {
                if (phy.volverplanonormal == true) {
                    phy.volverplanonormal = false;

                    cambioplano = 0;
                    
                    for(auto& phy1: g.template getComponents<PhysicsComponent_t>()){

                        auto* col1 { g.template getRequiredComponent<PhysicsComponent_t,ColliderComponent_t>(phy) };

                        if(col1!=nullptr){                          
                            phy1.z = phy1.zinicial;
                        }
                    }

                    return true;
                }

                if (phy.volverplanotunel == true) {
                    phy.volverplanotunel = false;

                    //std::cout << "entro\n";

                    cambioplano = 1;
                
                    for(auto& phy1: g.template getComponents<PhysicsComponent_t>()){

                        auto* col1 { g.template getRequiredComponent<PhysicsComponent_t,ColliderComponent_t>(phy) };

                        if(col1!=nullptr){                          
                            phy1.z = phy1.zvuelta;
                        }
                    }

                    return true;
                }
            }
        }
    }

    return false;
}