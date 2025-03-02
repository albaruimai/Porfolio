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

extern "C" {
    #include "../../../glad/glad.h"
    #include <GLFW/glfw3.h>
}
#include "../Shaders/Shader.hpp"
#include "../Sprite2D/SpriteRenderer.hpp"
#include <array>

#define GRAVITY 9.8

struct Particle
{
    SpriteRenderer * sp_;
    float life_  {1.f};
    float alpha_ {1.f};
    glm::vec2 origin {0.f};
    Particle(SpriteRenderer * sp);
};