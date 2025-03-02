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

#include "blackboard.hpp"

template <typename GameCTX_t>
void BlackBoardSystem_t<GameCTX_t>::quitarColisiones(GameCTX_t& g) const {
    auto& bb { g.template getBlackBoard() };

    for (int x {0}; x < 90; ++x) {
		for (int y {0}; y < 40; ++y) { 
            bb.salientes[x][y] = 0;
            bb.tunel[x][y] = 0;
        }
    }
}

template <typename GameCTX_t>
void BlackBoardSystem_t<GameCTX_t>::buscarColisiones(GameCTX_t& g, int x, int y) const {
    auto& bb { g.template getBlackBoard() };

    for(auto& sal: bb.salientes_bb){

        auto* col { sal->template getComponent<ColliderComponent_t>() };
        auto* phy { sal->template getComponent<PhysicsComponent_t>() };

		if(col != nullptr && phy != nullptr && col->properties == ColliderComponent_t::P_Saliente){
            for (auto& box: col->boxes) {
                if(x*12 > (box.box.xLeft + box.disX)+phy->x && x*12 <= (box.box.xRight + box.disX)+phy->x
                && y*12 > (box.box.yUp + box.disY)+phy->y && y*12 <= (box.box.yDown + box.disY)+phy->y){

                    if (x < sizeof(bb.salientes) && y < sizeof(bb.salientes[0]))
                    {
                        bb.salientes[x][y] = 1;
                    }
                }
            }
		}
	}

    if (bb.tunel_bb != nullptr) {
        auto* col { bb.tunel_bb->template getComponent<ColliderComponent_t>() };
        auto* phy { bb.tunel_bb->template getComponent<PhysicsComponent_t>() };

        if(col != nullptr && phy != nullptr && col->properties == ColliderComponent_t::P_PlanoS){
            for (auto& box: col->boxes) {
                if(x*12 > (box.box.xLeft + box.disX)+phy->x && x*12 <= (box.box.xRight + box.disX)+phy->x
                && y*12 > (box.box.yUp + box.disY)+phy->y && y*12 <= (box.box.yDown + box.disY)+phy->y){

                    if (x < sizeof(bb.tunel) && y < sizeof(bb.tunel[0]))
                    {
                        bb.tunel[x][y] = 1;
                    }
                }
            }
        }
    }
}

template <typename GameCTX_t>
void BlackBoardSystem_t<GameCTX_t>::ponerColisiones(GameCTX_t& g) const {
    for (int x {0}; x < 90; ++x) {
		for (int y {0}; y < 40; ++y) { 
            buscarColisiones(g, x, y);
        }
    }
}

template <typename GameCTX_t>
void BlackBoardSystem_t<GameCTX_t>::changeEnganches(GameCTX_t& g) const {
    auto& bb { g.template getBlackBoard() };

    auto* player {g.template getEntityByID(bb.playerID)};

    if (player != nullptr) {
        auto* ct { player->template getComponent<ControlComponent_t>() };

        if (ct != nullptr) {
            if (ct->puntosControl.size() > 0) {
                
                for (size_t i {0}; i < static_cast<size_t>(ct->puntosControl.size()); ++i) {
                    const auto* enganche { g.template getEntityByID(ct->puntosControl.at(i)) };
                    
                    if (enganche != nullptr) {
                        auto* ren { enganche->template getComponent<RenderComponent_t>() }; 
                        
                        if (ren != nullptr) {
                            
                            if (i != ct->puntosControl.size()-1) {
                                //poner normal
                                ren->entityNodes.node.node->setFrame(0);
                            } else {
                                //poner cogido
                                ren->entityNodes.node.node->setFrame(1);
                            }
                        }            
                    }        
                }
            }
        }
    }
}

template <typename GameCTX_t>
void BlackBoardSystem_t<GameCTX_t>::update(GameCTX_t& g) const {
    auto& bb { g.template getBlackBoard() };

    bb.palos_bb.clear();
    bb.arbustos_bb.clear();
    bb.salientes_bb.clear();
    bb.tunel_bb = { nullptr };
    bb.nidos_bb.clear();

    if (bb.timeCuerda >= 1) {
        ++(bb.timeCuerda);

        if (bb.timeCuerda == 300) {
            bb.timeCuerda = 0;
            bb.cuerdaID = 0;
        }
    }

    changeEnganches(g);

    for (auto& col: g.template getComponents<ColliderComponent_t>()){
        auto* enty { g.template getEntityByID(col.getEntityID()) };

        if (enty != nullptr) {
            switch (col.properties) {
                case ColliderComponent_t::P_spPalos:
                    bb.palos_bb.push_back(enty);
                    break;

                case ColliderComponent_t::P_Arbusto:
                    bb.arbustos_bb.push_back(enty);
                    break;

                case ColliderComponent_t::P_Saliente:
                    bb.salientes_bb.push_back(enty);
                    break;

                case ColliderComponent_t::P_Nido:
                    bb.nidos_bb.push_back(enty);
                    break;

                case ColliderComponent_t::P_PlanoS:
                    ajustarSonidoTunel(g, enty);
                    break;

                default:
                    break;
            }
        }      
    }
}

template <typename GameCTX_t>
void BlackBoardSystem_t<GameCTX_t>::ajustarSonidoTunel(GameCTX_t& g, ECS::Entity_t* e) const {
    auto& bb { g.template getBlackBoard() };

    bb.tunel_bb = e;

    auto* sou { e->template getComponent<SoundComponent_t>() };

    if (sou != nullptr) {
        if (bb.volviPlanoNormal == false) {
            sou->marked_for_play = 1;
        } else {
            sou->marked_for_stop = 0;
        }
    }
}