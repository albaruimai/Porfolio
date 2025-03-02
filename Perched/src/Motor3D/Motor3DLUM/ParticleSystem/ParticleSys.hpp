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

#include "Particle.hpp"
#include "../Sprite2D/Texture2D.hpp"
#include <vector>

enum struct ParticleType
{
    RAIN = 0,
    SNOW
};

struct ParticleSys
{
    ParticleSys (std::vector<SpriteRenderer*> sp, uint32_t amount, ParticleType);
    ParticleSys ();
    void update ();
    
    std::vector<SpriteRenderer*> sprite_;

private:
    std::vector<Particle> particles_ {};
    uint32_t              amount_    {};
    ParticleType          partType   {ParticleType::SNOW};
};
