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

#pragma once
#include "../cmp/hud.hpp"
#include "../cmp/entity.hpp"
#include "../cmp/collider.hpp"
#include "../cmp/control.hpp"
#include "../cmp/health.hpp"
#include "../cmp/puntos.hpp"
#include "../cmp/stamina.hpp"
#include "../cmp/render.hpp"


template <typename GameCTX_t>
struct HudSystem_t {
    //El explicit se recomienda ponerlo en todos los constructores
    //Sirve para que el programa no haga conversiones implicitas a la hora de construir objetos
    //explicit HudSystem_t() = default; //Constructor por defecto
    explicit HudSystem_t() = default;   //Constructor

    void update(GameCTX_t& g) noexcept;
    void setCrias(int crias);

    private:
        void ponerCrias(GameCTX_t& g, HudComponent_t& hud);
        void ponerStamina(HudComponent_t& hud, uint32_t cantStamina, uint32_t maxStamina);
        void ponerVidas (HudComponent_t& hud, uint64_t lifes);
        int crias_{0};
};