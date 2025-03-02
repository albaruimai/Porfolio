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

#include "hud.hpp"

template <typename GameCTX_t>
void HudSystem_t<GameCTX_t>::update(GameCTX_t& g) noexcept {
    auto& bb { g.template getBlackBoard() };

    for(auto& hud : g.template getComponents<HudComponent_t>()){

        auto* player { g.template getEntityByID(bb.playerID) };

        if (player != nullptr && &hud!=nullptr) {
            PhysicsComponent_t* player_ph { player->template getComponent<PhysicsComponent_t>() };
            RenderComponent_t*  player_re { player->template getComponent<RenderComponent_t>() };
            PuntosComponent_t*  player_pt { player->template getComponent<PuntosComponent_t>() };
            StaminaComponent_t* player_st { player->template getComponent<StaminaComponent_t>() };
            HealthComponent_t*  player_hl { player->template getComponent<HealthComponent_t >() };

            if (player_ph != nullptr && player_re != nullptr && player_pt != nullptr && player_st != nullptr && player_hl != nullptr && hud.textosHUD_.size()>0) {
                //hud.textosHUD_.at(1) = {std::to_string(player_pt->puntos), 1200.0, 500.0, 2.0, Vector3d{0.3f, 0.7f, 0.9f}};
                hud.textosHUD_.at(1) = {std::to_string(player_pt->puntos), 1220.0, 500.0, 1.0, Vector3d{1.0f, 0.039f, 0.125f}};

                ponerCrias(g, hud);
                
                ponerStamina(hud, player_st->cantStamina, player_st->maxStamina);

                ponerVidas(hud, player_hl->health);
            }
        }
    }
}

template <typename GameCTX_t>
void HudSystem_t<GameCTX_t>::setCrias(int crias)
{
    crias_ = crias;
}

template <typename GameCTX_t>
void HudSystem_t<GameCTX_t>::ponerCrias(GameCTX_t& g, HudComponent_t& hud) {
    if (&hud!= nullptr)
    {
        auto& bb { g.template getBlackBoard() };

        for (size_t i {0}; i < hud.zaris_.size(); ++i)
        {
            if (!hud.zaris_.empty() && hud.zaris_[i]!=nullptr)
            {
                if (bb.criasrescatadas.at(i) == true) {
                    hud.zaris_[i]->setAlpha(1.f);
                } 
                else {
                    hud.zaris_[i]->setAlpha(.5f);
                }
            }
        }
    }
}

template <typename GameCTX_t>
void HudSystem_t<GameCTX_t>::ponerStamina(HudComponent_t& hud, uint32_t cantStamina, uint32_t maxStamina) {
    float coeficiente { static_cast<float>(cantStamina) / static_cast<float>(maxStamina) };

    if (&hud!=nullptr && hud.icon_stamina_!=nullptr&& hud.phdr_stamina_!=nullptr && coeficiente > 0.f && coeficiente <= maxStamina)
    {
        hud.icon_stamina_->setSize(hud.phdr_stamina_->getSize() * coeficiente);
        hud.icon_stamina_->setPosition(hud.phdr_stamina_->getPosition()+((hud.phdr_stamina_->getSize()-hud.icon_stamina_->getSize()))/glm::vec2(2.f));
    }
}

template <typename GameCTX_t>
void HudSystem_t<GameCTX_t>::ponerVidas (HudComponent_t& hud, uint64_t lifes) {
    if (&hud != nullptr && !hud.hearts_.empty() && hud.hearts_[0] != nullptr && hud.hearts_[1] != nullptr && hud.hearts_[2] != nullptr)
    {
        switch (lifes)
        {
        case 0:
            hud.hearts_[0]->setAlpha(0.f);
            break;
        case 1:
            hud.hearts_[0]->setAlpha(1.f);
            hud.hearts_[1]->setAlpha(0.f);
            break;
        case 2:
            hud.hearts_[0]->setAlpha(1.f);
            hud.hearts_[1]->setAlpha(1.f);
            hud.hearts_[2]->setAlpha(0.f);
            break;
        case 3:
            hud.hearts_[0]->setAlpha(1.f);
            hud.hearts_[1]->setAlpha(1.f);
            hud.hearts_[2]->setAlpha(1.f);
            break;
        }
    }
}