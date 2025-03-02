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

#include "stamina.hpp"
#include "../cmp/health.hpp"


template <typename GameCTX_t>
void StaminaSystem_t<GameCTX_t>::update(GameCTX_t& g) const noexcept {
    auto& bb { g.template getBlackBoard() };

    for(auto& sta : g.template getComponents<StaminaComponent_t>()){
        if (bb.andandoplayer == true) {
            //sta.cantStamina = sta.maxStamina;
            sta.cantStamina += 3;

            if (sta.cantStamina >= sta.maxStamina) {
                sta.cantStamina = sta.maxStamina;
            }            
        } else {            
            --sta.cantStamina;

            if(sta.cantStamina <= 0) {
                auto* hea { g.template getRequiredComponent<StaminaComponent_t, HealthComponent_t>(sta) };
                if(hea!=nullptr){
                    hea->damage = hea->maxHealth;
                    hea->muertepordanyo = false;

                    bb.muriendoplayer = true;
                }
            }
        }

        if (sta.cantStamina < sta.maxStamina/2) {
            auto* player { g.template getEntityByID(bb.playerID) };

            if (player != nullptr) {
                auto* sou { player->template getComponent<SoundComponent_t>() };

                if (sou != nullptr) {
                    std::string abuscar {""};

                    if (bb.volviPlanoNormal == true) {
                        abuscar = "event:/Personajes/Zacarias/Cansancio";
                    } else {
                        abuscar = "event:/Personajes/Zacarias Cueva/Cansancio";
                    }

                    auto encon = std::find(sou->my_events.begin(), sou->my_events.end(), abuscar);

                    if (encon != sou->my_events.end()) {
                        sou->event_id = sou->my_events.at(encon - sou->my_events.begin());
                        sou->isEvent3D = false;
                        sou->marked_for_init = 1;
                        sou->marked_for_play = 1;
                    }
                }
            }
        }
    }
}