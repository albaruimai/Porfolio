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
//# TextComponent sirve para guardar los datos necesarios que        #
//#   necesita una entidad como el tamanyo del rectangulo, y que     #
//#   texto mostrar.                                                 #
//#                                                                  #
//####################################################################

#pragma once
#include "component.hpp"
#include "../Motor3D/Motor3DLUM/Motor3DLUM.hpp"
#include <iostream>
#include <array>
#include <vector>

#define LIVES    3

struct Texti {
    std::string texto;
    float x {0}, y {0};
    float scale {1.0};
    Vector3d color {0, 0, 0};
};

struct HudComponent_t : public ECS::ComponentBase_t<HudComponent_t> {
    explicit HudComponent_t(ECS::EntityID_t eid) : ComponentBase_t(eid)
    {};
    std::array<SpriteRenderer*, LIVES> hearts_{nullptr,nullptr,nullptr};
    std::vector<SpriteRenderer*> zaris_ {};
    /*bellotas*/
    SpriteRenderer* icon_bellotas_{nullptr};
    /*stamina*/
    SpriteRenderer* icon_stamina_ {nullptr};
    SpriteRenderer* phdr_stamina_ {nullptr};
    /*numeros*/
    bool init_{true};

    std::array<Texti, 2> textosHUD_{};
};