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

#include "CameraLUM.hpp"
#include "../../glm/gtx/string_cast.hpp"
#include "../../glm/gtx/matrix_decompose.hpp"

struct Shape
{
    glm::vec3 center_;
    float radius_;
    float top_;
    float bot_;
    float right_;
    float left_;
    float far_;
    float near_;

    Shape();
    Shape( float radius, glm::vec3 center );
    
    bool isOnFrustum(CameraLUM * cam, glm::mat4 const & mat) const;
    bool isOnForwardPlan(const glm::vec4& plan, Shape& s) const;
    
    bool inTopPlan(const glm::vec4& plan, Shape& s) const;
    bool inBotPlan(const glm::vec4& plan, Shape& s) const;
    bool inLftPlan(const glm::vec4& plan, Shape& s) const;
    bool inRhtPlan(const glm::vec4& plan, Shape& s) const;
    bool inNerPlan(const glm::vec4& plan, Shape& s) const;
    bool inFarPlan(const glm::vec4& plan, Shape& s) const;
};
