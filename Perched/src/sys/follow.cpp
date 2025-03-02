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

#include "follow.hpp"
#include "../cmp/follow.hpp"
#include "../cmp/physics.hpp"

template <typename GameCTX_t>
constexpr void FollowSystem_t<GameCTX_t>::update(GameCTX_t& g) const noexcept {
    for(auto& fol: g.template getComponents<FollowComponent_t>()){
        auto* entity { g.getEntityByID(fol.followEntityID) };
        if (!entity) { continue; }

        auto* entPhy { entity->template getComponent<PhysicsComponent_t>() };
        if (!entPhy) { continue; }

        auto* phy { g.template getRequiredComponent<FollowComponent_t, PhysicsComponent_t>(fol) };
        if (!phy) { continue; }
        if (!fol.folActive) { continue; }
        phy->vy=0;

        phy->x = entPhy->x + fol.x;
        phy->y = entPhy->y + fol.y;
        phy->z = entPhy->z + fol.z;
    }
} 